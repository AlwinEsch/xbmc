/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "launcher/ILauncher.h"
#include "Interface.h"
#include "processinfo/ProcessInfo.h"
#include "RunningThread.h"
#include "addons/Addon.h"
#include "threads/SystemClock.h"
#include "threads/Thread.h"

#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

class CRunningThread;
class IAddonInstanceHandler;

class CRunningProcess : private CThread
{
public:
  CRunningProcess(const std::shared_ptr<ADDON::IAddon>& addon, const std::string& uuid, bool directDll, const KODI_HANDLE kodiInstancePtr);
  ~CRunningProcess();

  bool Launch(const std::vector<std::string>& argv, bool waitForExit);
  bool Kill();
  ChildStatus ProcessActive();

  bool FuncCall(int group,
                int func,
                const msgpack::unpacked& in,
                msgpack::sbuffer& out);

  bool SendMessage(int group, int func);
  bool SendMessage(int group, int func, const msgpack::sbuffer& in);
  bool SendMessage(int group, int func, const msgpack::sbuffer& in, msgpack::sbuffer& ret);
  bool SendMessageOnlyGetReturn(int group, int func, msgpack::sbuffer& ret);

  void RegisterClass(IInterfaceClassHdl* ifcClass);
  void UnregisterClass(IInterfaceClassHdl* ifcClass);

  void AddAddonInstance(IAddonInstanceHandler* handler);
  void ReleaseAddonInstance(IAddonInstanceHandler* handler);

  void InformStopReport(ChildStatus status);

  const std::string& GetUUID() const { return m_uuid; }
  const std::shared_ptr<ADDON::IAddon>& GetAddon() const { return m_addon; }
  std::string GetAddonID() const { return m_addon->ID(); }
  size_t UsedInstanceCount() const;

  CInterface& GetIfc() { return m_interface; }

  void SetEndtime(unsigned int milliseconds);
  unsigned int EndTimeLeft() const { return m_endTimer.MillisLeft(); }
  bool UseEndTime() const { return m_endMilliseconds > 0; }
  bool IsInUse() const;

  ProcessInfoData GetProcessInfoData();

  void* m_hdl;

private:
  void Process() override;

  const std::shared_ptr<ADDON::IAddon> m_addon;
  const std::string m_uuid;
  const bool m_directDll;
  const KODI_HANDLE m_kodiInitInstancePtr;
  std::atomic_bool m_startDone{false};
  bool m_startFailed{false};
  std::vector<std::string> m_argv;
  int64_t m_threadIdentfier{0};
  CRunningThread m_mainThread;
  CInterface m_interface;
  ILauncher* m_launcher;
  std::set<std::shared_ptr<CRunningThread>> m_runningSubThreads;
  std::unordered_set<IInterfaceClassHdl*> m_activeIfcClasses;
  std::unordered_set<IAddonInstanceHandler*> m_activeAddonHandlers;
  mutable std::mutex m_mutex;
  mutable std::mutex m_classRegisterMutex;
  unsigned int m_endMilliseconds{0};
  mutable XbmcThreads::EndTime m_endTimer;
  CProcessInfo* m_processInfo{nullptr};
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
