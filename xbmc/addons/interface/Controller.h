/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "Interface.h"
#include "processinfo/ProcessInfo.h"

#include "threads/Thread.h"

#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

namespace ADDON
{
class CAddonInfo;
class CAddonMgr;
class IAddon;
} /* namespace ADDON */

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

class CRunningProcess;
class IAddonInstanceHandler;

class CController : private CThread
{
public:
  CController(ADDON::CAddonMgr& addonMgr);
  ~CController();

  bool Init();
  void Deinit();

  bool AddonLanguageSupported(const std::shared_ptr<ADDON::IAddon>& addon) const;
  bool LaunchAddon(const std::shared_ptr<ADDON::IAddon>& addon,
                   std::vector<std::string>& argv,
                   bool waitForExit,
                   std::shared_ptr<CRunningProcess>& process);
  std::shared_ptr<CRunningProcess> GetAddonProcess(const std::shared_ptr<ADDON::CAddonInfo>& addonInfo,
                                                   IAddonInstanceHandler* handler,
                                                   const KODI_HANDLE kodiInstancePtr,
                                                   std::shared_ptr<ADDON::IAddon>& addon);
  void ReleaseAddonProcess(const std::shared_ptr<CRunningProcess>& process, IAddonInstanceHandler* handler);
  std::shared_ptr<CRunningProcess> GetRunningAddonProcess(const std::string& addonId) const;
  std::shared_ptr<ADDON::IAddon> GetRunningAddon(const std::string& addonId) const;

  std::vector<ProcessInfoData> GetProcessInfoData();
  const std::string& GetDevkitLibPath() const { return m_devkitLib; }

private:
  void Process() override;

  bool CheckNeedDirectDll(const std::shared_ptr<ADDON::IAddon>& addon);

  ADDON::CAddonMgr& m_addonMgr;
  const std::string m_devkitLib;
  std::atomic_bool m_running{false};
  mutable std::mutex m_lock;
  std::map<std::string, std::shared_ptr<CRunningProcess>> m_runningProcesses;
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
