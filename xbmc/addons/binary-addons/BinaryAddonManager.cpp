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
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "BinaryAddonManager.h"
#include "BinaryAddonBase.h"

#include "addons/AddonManager.h"
#include "threads/SingleLock.h"
#include "utils/log.h"

using namespace ADDON;

CBinaryAddonManager::~CBinaryAddonManager()
{
  CAddonMgr::GetInstance().Events().Unsubscribe(this);
}

bool CBinaryAddonManager::Init()
{
  CAddonMgr::GetInstance().Events().Subscribe(this, &CBinaryAddonManager::OnEvent);

  std::vector<std::tuple<std::string, bool, std::string>> binaryAddonList;
  if (!CAddonMgr::GetInstance().GetInstalledBinaryAddonPaths(binaryAddonList))
  {
    CLog::Log(LOGNOTICE, "Binary Addons: No binary addons present and related manager, init not necessary");
    return true;
  }

  for (auto addon : binaryAddonList)
  {
    BinaryAddonBasePtr base = std::make_shared<CBinaryAddonBase>();
    if (!base->Create(std::get<0>(addon)))
    {
      CLog::Log(LOGERROR, "Binary Addons: Failed to create base for '%s' and addon not usable", std::get<0>(addon).c_str());
      continue;
    }
    m_installedAddons[base->ID()] = base;
    if (std::get<1>(addon))
      m_enabledAddons[base->ID()] = base;
  }

  return true;
}

bool CBinaryAddonManager::HasInstalledAddons(const TYPE &type)
{
  CSingleLock lock(m_critSection);
  for (auto info : m_installedAddons)
  {
    if (info.second->IsType(type))
      return true;
  }
  return false;
}

bool CBinaryAddonManager::HasEnabledAddons(const TYPE &type)
{
  CSingleLock lock(m_critSection);
  for (auto info : m_enabledAddons)
  {
    if (info.second->IsType(type))
      return true;
  }
  return false;
}

void CBinaryAddonManager::GetAddonInfos(BinaryAddonBaseList& addonInfos, bool enabledOnly, const TYPE &type)
{
  CSingleLock lock(m_critSection);

  BinaryAddonMgrBaseList* addons;
  if (enabledOnly)
    addons = &m_enabledAddons;
  else
    addons = &m_installedAddons;

  for (auto& info : *addons)
  {
    if (type == ADDON_UNKNOWN || info.second->IsType(type))
    {
      addonInfos.push_back(info.second);
    }
  }
}

const BinaryAddonBasePtr CBinaryAddonManager::GetInstalledAddonInfo(const std::string& addonId, const TYPE &type/* = ADDON_UNKNOWN*/)
{
  CSingleLock lock(m_critSection);

  const auto& addon = m_installedAddons.find(addonId);
  if (addon != m_installedAddons.end() && (type == ADDON_UNKNOWN || addon->second->IsType(type)))
    return addon->second;

  CLog::Log(LOGERROR, "Binary Addons: Requested addon '%s' unknown as binary", addonId.c_str());
  return nullptr;
}

AddonPtr CBinaryAddonManager::GetRunningAddon(const std::string& addonId) const
{
  CSingleLock lock(m_critSection);

  BinaryAddonBasePtr base;
  const auto& addon = m_installedAddons.find(addonId);
  if (addon != m_installedAddons.end())
    base = addon->second;

  if (base)
  {
    return base->GetActiveAddon();
  }

  return nullptr;
}

void CBinaryAddonManager::OnEvent(const AddonEvent& event)
{
  if (auto enableEvent = dynamic_cast<const AddonEvents::Enabled*>(&event))
  {
    EnableEvent(enableEvent->id);
  }
  else if (auto disableEvent = dynamic_cast<const AddonEvents::Disabled*>(&event))
  {
    DisableEvent(disableEvent->id);
  }
  else if (auto metadataChanged = dynamic_cast<const AddonEvents::MetadataChanged*>(&event))
  {
  }
  else if (typeid(event) == typeid(AddonEvents::InstalledChanged))
  {
    InstalledChangeEvent();
  }
}

void CBinaryAddonManager::EnableEvent(const std::string& addonId)
{
  CSingleLock lock(m_critSection);

  BinaryAddonBasePtr base;
  const auto& addon = m_installedAddons.find(addonId);
  if (addon != m_installedAddons.end())
    base = addon->second;
  else
    return;

  CLog::Log(LOGDEBUG, "Binary addons: Enable addon '%s' on binary addon manager", base->ID().c_str());
  m_enabledAddons[base->ID()] = base;

  /**
   * @todo add way to inform type addon manager (e.g. for PVR) and parts about changed addons
   *
   * Currently only Screensaver and Visualization use the new way and not need informed.
   */
}

void CBinaryAddonManager::DisableEvent(const std::string& addonId)
{
  CSingleLock lock(m_critSection);

  BinaryAddonBasePtr base;
  const auto& addon = m_installedAddons.find(addonId);
  if (addon != m_installedAddons.end())
    base = addon->second;
  else
    return;

  CLog::Log(LOGDEBUG, "Binary addons: Disable addon '%s' on binary addon manager", base->ID().c_str());
  m_enabledAddons.erase(base->ID());

  /**
   * @todo add way to inform type addon manager (e.g. for PVR) and parts about changed addons
   *
   * Currently only Screensaver and Visualization use the new way and not need informed.
   */
}

void CBinaryAddonManager::InstalledChangeEvent()
{
  CSingleLock lock(m_critSection);

  std::vector<std::tuple<std::string, bool, std::string>> binaryAddonList;
  CAddonMgr::GetInstance().GetInstalledBinaryAddonPaths(binaryAddonList);

  BinaryAddonMgrBaseList deletedAddons = m_installedAddons;
  for (auto addon : binaryAddonList)
  {
    const auto& knownAddon = m_installedAddons.find(std::get<2>(addon));
    if (knownAddon == m_installedAddons.end())
    {
      CLog::Log(LOGDEBUG, "Binary addons: Adding new binary addon '%s'", std::get<2>(addon).c_str());

      BinaryAddonBasePtr base = std::make_shared<CBinaryAddonBase>();
      if (!base->Create(std::get<0>(addon)))
      {
        CLog::Log(LOGERROR, "Binary Addons: Failed to create base for '%s' and addon not usable", std::get<0>(addon).c_str());
        continue;
      }
      m_installedAddons[base->ID()] = base;
      if (std::get<1>(addon))
        m_enabledAddons[base->ID()] = base;

      /**
       * @todo add way to inform type addon manager (e.g. for PVR) and parts about changed addons
       *
       * Currently only Screensaver and Visualization use the new way and not need informed.
       */
    }
    else
    {
      deletedAddons.erase(knownAddon);
    }
  }

  for (auto addon : deletedAddons)
  {
    CLog::Log(LOGDEBUG, "Binary addons: Removing binary addon '%s'", addon.first.c_str());

    m_installedAddons.erase(addon.first);
    m_enabledAddons.erase(addon.first); // Normally should the addon disabled by another event, but to make sure also erased here

    /**
     * @todo add way to inform type addon manager (e.g. for PVR) and parts about changed addons
     *
     * Currently only Screensaver and Visualization use the new way and not need informed.
     */
  }
}
