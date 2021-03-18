/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "RunningProcess.h"
#include "addons/AddonVersion.h"
#include "addons/IAddon.h"
#include "addons/kodi-dev-kit/include/kodi/c-api/addon_base.h"

#include <memory>
#include <mutex>

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

class CInterface;
typedef void* ADDON_HANDLE;
typedef void* KODI_HANDLE;

class IAddonInstanceHandler
{
public:
  IAddonInstanceHandler(ADDON_INSTANCE type,
                        const std::shared_ptr<ADDON::CAddonInfo>& addonInfo,
                        ADDON_HANDLE parentInstance = nullptr,
                        const std::string& instanceID = "");
  virtual ~IAddonInstanceHandler();

  ADDON_INSTANCE UsedType() const { return m_type; }
  const std::string& InstanceID() { return m_instanceId; }

  std::string ID() const;
  std::string Name() const;
  std::string Author() const;
  std::string Icon() const;
  std::string Path() const;
  std::string Profile() const;
  ADDON::AddonVersion Version() const;

  ADDON_STATUS CreateInstance(const KODI_HANDLE kodi, ADDON_HANDLE& instance);
  void DestroyInstance(ADDON_HANDLE instance);
  const std::shared_ptr<ADDON::IAddon>& Addon() const { return m_addon; }
  const std::shared_ptr<ADDON::CAddonInfo>& GetAddonInfo() const { return m_addonInfo; };
  const std::shared_ptr<CRunningProcess>& GetProcess() const { return m_process; };

  virtual void StopReport(ChildStatus status) {}
  virtual void OnPreInstall() {}
  virtual void OnPostInstall(bool update, bool modal) {}
  virtual void OnPreUnInstall() {}
  virtual void OnPostUnInstall() {}

protected:
  CInterface* m_ifc;

private:
  ADDON_INSTANCE m_type;
  std::string m_instanceId;
  ADDON_HANDLE m_parentInstance;
  std::shared_ptr<CRunningProcess> m_process;
  std::shared_ptr<ADDON::CAddonInfo> m_addonInfo;
  std::shared_ptr<ADDON::IAddon> m_addon;
  static std::mutex m_cdSec;
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
