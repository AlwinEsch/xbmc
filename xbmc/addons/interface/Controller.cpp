/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Controller.h"

#include "CompileInfo.h"
#include "GUICrashReporter.h"
#include "RunningProcess.h"

#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "utils/StringUtils.h"

#include <regex>

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

CController::CController(ADDON::CAddonMgr& addonMgr)
  : CThread("KODI::ADDONS::INTERFACE::CController"),
    m_addonMgr(addonMgr),
    m_devkitLib(CSpecialProtocol::TranslatePath("special://xbmcbinaddons/kodi.binary.devkit/" DEVKIT_LIBRARY))
{
}

CController::~CController()
{
  Deinit();
}

bool CController::Init()
{
  CThread::Create();
  m_running = true;
  return true;
}

void CController::Deinit()
{
  if (m_running)
  {
    m_running = false;
    CThread::StopThread();
  }
}

bool CController::AddonLanguageSupported(const std::shared_ptr<ADDON::IAddon>& addon) const
{
  if (addon->Type(addon->Type())->Language() != ADDON::AddonLanguage::Unknown)
    return true;
  return false;
}

bool CController::LaunchAddon(const std::shared_ptr<ADDON::IAddon>& addon, std::vector<std::string>& argv, bool waitForExit, std::shared_ptr<CRunningProcess>& process)
{
  std::shared_ptr<CRunningProcess> newProcess;
  {
    std::unique_lock<std::mutex> lock(m_lock);
    newProcess = std::make_shared<CRunningProcess>(addon,
                                                   "kodi-subproc-" + StringUtils::CreateUUID(),
                                                   CheckNeedDirectDll(addon),
                                                   nullptr);
    m_runningProcesses.emplace(addon->ID(), newProcess);
  }

  if (!newProcess->Launch(argv, waitForExit))
  {
    return false;
  }

  if (waitForExit)
  {
    std::unique_lock<std::mutex> lock(m_lock);
    m_runningProcesses.erase(newProcess->GetAddonID());
  }

  process = newProcess;
  return true;
}

std::shared_ptr<CRunningProcess> CController::GetAddonProcess(const std::shared_ptr<ADDON::CAddonInfo>& addonInfo,
                                                              IAddonInstanceHandler* handler,
                                                              const KODI_HANDLE kodiInstancePtr,
                                                              std::shared_ptr<ADDON::IAddon>& addon)
{
  std::unique_lock<std::mutex> lock(m_lock);

  std::shared_ptr<CRunningProcess> newProcess;

  const auto& addonInstances = m_runningProcesses.find(addonInfo->ID());
  if (addonInstances != m_runningProcesses.end())
  {
    newProcess = addonInstances->second;
    addon = newProcess->GetAddon();
  }
  else
  {
    addon = std::make_shared<ADDON::CAddon>(addonInfo, addonInfo->MainType());
    newProcess = std::make_shared<CRunningProcess>(addon,
                                                   "kodi-subproc-" + StringUtils::CreateUUID(),
                                                   CheckNeedDirectDll(addon),
                                                   kodiInstancePtr);
    std::vector<std::string> argv;
    if (!newProcess->Launch(argv, false))
    {
      return nullptr;
    }

    m_runningProcesses.emplace(addonInfo->ID(), newProcess);
  }

  newProcess->SetEndtime(30000);
  newProcess->AddAddonInstance(handler);

  if (!addon)
  {
    CLog::Log(LOGFATAL, "CController:{}: Tried to get add-on '{}' who not available!",
              __func__, addonInfo->ID());
  }

  return newProcess;
}

void CController::ReleaseAddonProcess(const std::shared_ptr<CRunningProcess>& process, IAddonInstanceHandler* handler)
{
  std::unique_lock<std::mutex> lock(m_lock);

  const auto& addon = m_runningProcesses.find(process->GetAddonID());
  if (addon == m_runningProcesses.end())
    return;

  process->ReleaseAddonInstance(handler);

  if (process->UsedInstanceCount() > 0)
    return;

  if (!process->UseEndTime())
  {
    process->Kill();

    m_runningProcesses.erase(addon);
  }
}

std::shared_ptr<CRunningProcess> CController::GetRunningAddonProcess(const std::string& addonId) const
{
  std::unique_lock<std::mutex> lock(m_lock);

  const auto& addonInstances = m_runningProcesses.find(addonId);
  if (addonInstances != m_runningProcesses.end())
    return addonInstances->second;

  return nullptr;
}

std::shared_ptr<ADDON::IAddon> CController::GetRunningAddon(const std::string& addonId) const
{
  const std::shared_ptr<CRunningProcess> process = GetRunningAddonProcess(addonId);
  if (process)
    return process->GetAddon();

  return nullptr;
}

std::vector<ProcessInfoData> CController::GetProcessInfoData()
{
  std::vector<ProcessInfoData> data;

  std::unique_lock<std::mutex> lock(m_lock);

  for (const auto& process : m_runningProcesses)
  {
    data.emplace_back(process.second->GetProcessInfoData());
  }

  return data;
}

void CController::Process()
{
  while (!m_bStop)
  {
    CThread::Sleep(500);

    std::unique_lock<std::mutex> lock(m_lock);

    for (auto it = m_runningProcesses.cbegin(); it != m_runningProcesses.cend();)
    {
      /*
       * Check the addon stopped itself, e.g. by normal way or with a crash.
       */
      ChildStatus status = it->second->ProcessActive();
      if (it->second->ProcessActive() != ChildStatus::Running)
      {
        fprintf(stderr, "Stopped!!!!!!!!!!!!! %i\n", status);
        CLog::Log(LOGFATAL, "CController::{}: Addon '{}' process was uncontrolled stopped!", __func__, it->second->GetAddonID());
        it->second->InformStopReport(status);
        it->second->Kill();
        m_runningProcesses.erase(it++);
        continue;
      }

      /*
       * Check run of addon, if it is ununsed a amount of time do a stop of it.
       * This mainly relates to addons where processed by Kodi, e.g. PVR, audiodecoder
       * and so on related addons.
       */
      if (it->second->UseEndTime() && !it->second->IsInUse())
      {
        if (it->second->EndTimeLeft() == 0)
        {
          fprintf(stderr, "-------------- %i\n", it->second->EndTimeLeft());
          CLog::Log(LOGDEBUG, "CController::{}: Addon '{}' process was inactive and becomes stopped", __func__, it->second->GetAddonID());
          it->second->Kill();
          m_runningProcesses.erase(it++);
          continue;
        }
      }

      it++;
    }
  }
}

bool CController::CheckNeedDirectDll(const std::shared_ptr<ADDON::IAddon>& addon)
{
  try
  {
    // linux is different and has the version number after the suffix
    static const std::regex libRegex("^.*" +
                                    CCompileInfo::CCompileInfo::GetSharedLibrarySuffix() +
                                    "\\.?[0-9]*\\.?[0-9]*\\.?[0-9]*$");
    if (std::regex_match(addon->Type(addon->MainType())->LibPath(), libRegex))
    {
      return true;
    }
  }
  catch (const std::regex_error& e)
  {
    CLog::Log(LOGERROR, "CAddonInfoBuilder::{}: Regex error caught: {}", __func__,
              e.what());
  }

  return false;
}

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
