/*
 *      Copyright (C) 2005-2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AddonManager.h"
#include "AddonChangeProcessor.h"

#include "FileItem.h"
#include "filesystem/Directory.h"
#include "filesystem/File.h"
#include "filesystem/SpecialProtocol.h"
#include "dialogs/GUIDialogOK.h"
#include "utils/log.h"
#include "utils/TimeUtils.h"
#include "utils/XMLUtils.h"

using namespace ADDON_NEW;

#define DEBUG 1

CAddonManager::CAddonManager()
  : CThread("AddonObserver")
{

}

bool CAddonManager::Init()
{
  CSingleLock lock(m_critSection);

  if (!LoadManifest(m_systemAddons, m_optionalAddons))
  {
    CLog::Log(LOGFATAL, "CAddonManager::%s: Failed to read manifest", __FUNCTION__);
    return false;
  }

  if (!m_database.Open())
  {
    CLog::Log(LOGFATAL, "CAddonManager::%s: Failed to open database", __FUNCTION__);
    return false;
  }

  // Load addon infos from system
  AddonInfoList installedAddons;
  FindAddons(installedAddons, "special://xbmcbin/addons");
  FindAddons(installedAddons, "special://xbmc/addons");
  FindAddons(installedAddons, "special://home/addons");
  m_installedAddons = std::move(installedAddons);

  // Synchronize system addons with database
  std::set<std::string> installed;
  for (auto& addonInfo : m_installedAddons)
    installed.insert(addonInfo.first);
  m_database.SyncInstalled(installed, m_systemAddons, m_optionalAddons);

  // Set list with enabled addons on system
  std::set<std::string> tmp;
  m_database.GetEnabled(tmp);
  AddonInfoList enabledAddons;
  for (auto addonId : tmp)
  {
    AddonInfoPtr info = GetInstalledAddonInfo(addonId);
    if (info == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonManager::%s: Addon Id '%s' does not mach installed map", __FUNCTION__, addonId.c_str());
      continue;
    }
    enabledAddons[addonId] = info;
  }
  m_enabledAddons = std::move(enabledAddons);

#ifdef DEBUG
  CLog::Log(LOGDEBUG, "CAddonManager::%s: Found following amount '%i' of installed addons:", __FUNCTION__, m_installedAddons.size());
  for (const auto& addon : m_installedAddons)
  {
    CLog::Log(LOGDEBUG, " - ID='%s'; Path='%s'", addon.first.c_str(), addon.second->Path().c_str());
  }
#endif

  //Ensure required add-ons are installed and enabled
  for (const auto& id : m_systemAddons)
  {
    if (!IsAddonEnabled(id))
    {
      CLog::Log(LOGFATAL, "CAddonManager::%s: Required system addon '%s' not installed or not enabled", __FUNCTION__, id.c_str());
      return false;
    }
  }

  Create();
  SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
  return true;
}

void CAddonManager::Deinit()
{
  CSingleLock lock(m_critSection);

  StopThread();

  m_database.Close();
  m_installedAddons.clear();
  m_enabledAddons.clear();
}

bool CAddonManager::EnableAddon(const std::string& addonId, bool waitToSet)
{
  AddonInfoPtr addon = GetInstalledAddonInfo(addonId);
  if (addon == nullptr)
    return false;

  if (IsAddonEnabled(addonId))
    return true;

  CAddonChangeProcessor* process = new CAddonChangeProcessor(addon, FlowPlaceBegin | FlowPlaceEnd, AddonWorkDisable, m_addonChangeObserver);
  m_activeAddonChangeProcessors.push_back(process);
  return process->DoWork(waitToSet);
}

bool CAddonManager::DisableAddon(const std::string& addonId, bool waitToSet)
{
  AddonInfoPtr addon = GetInstalledAddonInfo(addonId);
  if (addon == nullptr)
    return false;

  if (!IsAddonEnabled(addonId))
    return true;

  CAddonChangeProcessor* process = new CAddonChangeProcessor(addon, FlowPlaceBegin | FlowPlaceEnd, AddonWorkEnable, m_addonChangeObserver);
  m_activeAddonChangeProcessors.push_back(process);
  return process->DoWork(waitToSet);
}

bool CAddonManager::IsAddonInstalled(const std::string& addonId) const
{
  CSingleLock lock(m_critSection);

  return m_installedAddons.find(addonId) != m_installedAddons.end() ? true : false;
}

bool CAddonManager::IsAddonEnabled(const std::string& addonId) const
{
  CSingleLock lock(m_critSection);

  return m_enabledAddons.find(addonId) != m_enabledAddons.end() ? true : false;
}

AddonInfoPtr CAddonManager::GetInstalledAddonInfo(const std::string& addonId) const
{
  const auto& addon = m_installedAddons.find(addonId);
  if (addon != m_installedAddons.end())
    return addon->second;

  return nullptr;
}

void CAddonManager::RegisterAddonChangeObserver(CAddonChangeObserver* observer)
{
  m_addonChangeObserver.insert(observer);
}

void CAddonManager::UnregisterAddonChangeObserver(CAddonChangeObserver* observer)
{
  m_addonChangeObserver.erase(observer);
}

void CAddonManager::Process(void)
{
  while (!m_bStop)
  {
    if (!m_activeAddonChangeProcessors.empty())
    {
      for (auto itr = m_activeAddonChangeProcessors.begin() ; itr != m_activeAddonChangeProcessors.end() ; )
      {
        CAddonChangeProcessor* process = *itr;
        if (process->InProgress())
        {
          if (!process->WaitingForUserInput() && process->StartTime() + 10000 < CTimeUtils::GetFrameTime())
          {
            CLog::Log(LOGERROR, "CAddonManager::%s: Addon change for '%s' reached wait time with last job '%s'",
                        __FUNCTION__, process->AddonId().c_str(), GET_ADDON_CHANGE_EVENT_AS_STRING(process->LastStartedEvent()));
            if (CGUIDialogOK::ShowAndGetInput("Warning", "Addon change reached wait time, do you want to cancel?"))
            {

            }
            else
            {
              process->ResetWaitTime();
            }
          }
          ++itr;
        }
        else
        {
          delete process;
          m_activeAddonChangeProcessors.erase(itr);
        }
      }
    }
    Sleep(20);
  }
}

void CAddonManager::FindAddons(AddonInfoList& addonmap, const std::string& path)
{
  CFileItemList items;
  if (XFILE::CDirectory::GetDirectory(path, items, "", XFILE::DIR_FLAG_NO_FILE_DIRS))
  {
    for (int i = 0; i < items.Size(); ++i)
    {
      std::string path = items[i]->GetPath();
      if (XFILE::CFile::Exists(path + "addon.xml"))
      {
        AddonInfoPtr addonInfo = std::make_shared<CAddonInfo>();
        if (addonInfo->Load(path))
        {
          addonmap[addonInfo->ID()] = addonInfo;
        }
      }
    }
  }
}

bool CAddonManager::LoadManifest(std::set<std::string>& system, std::set<std::string>& optional)
{
  CXBMCTinyXML doc;
  if (!doc.LoadFile("special://xbmc/system/addon-manifest.xml"))
  {
    CLog::Log(LOGERROR, "CAddonManager::%s: Manifest missing", __FUNCTION__);
    return false;
  }

  auto root = doc.RootElement();
  if (!root || root->ValueStr() != "addons")
  {
    CLog::Log(LOGERROR, "CAddonManager::%s: Malformed manifest", __FUNCTION__);
    return false;
  }

  auto elem = root->FirstChildElement("addon");
  while (elem)
  {
    if (elem->FirstChild())
    {
      if (XMLUtils::GetAttribute(elem, "optional") == "true")
        optional.insert(elem->FirstChild()->ValueStr());
      else
        system.insert(elem->FirstChild()->ValueStr());
    }
    elem = elem->NextSiblingElement("addon");
  }
  return true;
}

bool CAddonManager::PerformDisableJob(const AddonInfoPtr& addonInfo)
{
  return true;
}

bool CAddonManager::PerformUninstallJob(const AddonInfoPtr& addonInfo)
{
  return true;
}

bool CAddonManager::PerformUpdateJob(const AddonInfoPtr& addonInfo)
{
  return true;
}

bool CAddonManager::PerformInstallJob(const AddonInfoPtr& addonInfo)
{
  return true;
}

bool CAddonManager::PerformEnableJob(const AddonInfoPtr& addonInfo)
{
  return true;
}
