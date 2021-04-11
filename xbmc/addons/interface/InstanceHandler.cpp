/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "InstanceHandler.h"

#include "Controller.h"

#include "ServiceBroker.h"
#include "utils/StringUtils.h"
#include "utils/log.h"
#include "api/addon_base.h"

using namespace ADDON;

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

std::mutex IAddonInstanceHandler::m_cdSec;

IAddonInstanceHandler::IAddonInstanceHandler(ADDON_INSTANCE type,
                                             const AddonInfoPtr& addonInfo,
                                             ADDON_HANDLE parentInstance /* = nullptr*/,
                                             const std::string& instanceID /* = ""*/)
  : m_type(type), m_parentInstance(parentInstance), m_addonInfo(addonInfo)
{
  // if no special instance ID is given generate one from class pointer (is
  // faster as unique id and also safe enough for them).
  m_instanceId = !instanceID.empty() ? instanceID : StringUtils::Format("%p", static_cast<void*>(this));
}

IAddonInstanceHandler::~IAddonInstanceHandler()
{
}

std::string IAddonInstanceHandler::ID() const
{
  return m_addonInfo ? m_addonInfo->ID() : "";
}

std::string IAddonInstanceHandler::Name() const
{
  return m_addonInfo ? m_addonInfo->Name() : "";
}

std::string IAddonInstanceHandler::Author() const
{
  return m_addonInfo ? m_addonInfo->Author() : "";
}

std::string IAddonInstanceHandler::Icon() const
{
  return m_addonInfo ? m_addonInfo->Icon() : "";
}

std::string IAddonInstanceHandler::Path() const
{
  return m_addonInfo ? m_addonInfo->Path() : "";
}

std::string IAddonInstanceHandler::Profile() const
{
  return m_addonInfo ? m_addonInfo->Profile() : "";
}

AddonVersion IAddonInstanceHandler::Version() const
{
  return m_addonInfo ? m_addonInfo->Version() : AddonVersion();
}

ADDON_STATUS IAddonInstanceHandler::CreateInstance(const KODI_HANDLE kodi, ADDON_HANDLE& instance)
{
  m_process = CServiceBroker::GetAddonIfcCtrl().GetAddonProcess(m_addonInfo, this, kodi, m_addon);
  if (!m_process)
  {
    CLog::Log(LOGERROR, "IAddonInstanceHandler::{}: {} failed to get addon process during instance creation",
                __func__,
                m_addonInfo->ID());
    return ADDON_STATUS_UNKNOWN;
  }
  m_ifc = &m_process->GetIfc();

  if (!m_addon || ! m_ifc)
    return ADDON_STATUS_UNKNOWN;

  std::unique_lock<std::mutex> lock(m_cdSec);

  ADDON_STATUS status = m_ifc->kodi_addon_base_h->kodi_addon_create_instance_v1(m_process->m_hdl, m_type, m_instanceId, kodi, &instance, m_parentInstance);
  if (status != ADDON_STATUS_OK)
  {
    CLog::Log(LOGERROR, "IAddonInstanceHandler::{}: {} returned bad status \"{}\" during instance creation",
                __func__,
                m_addonInfo->ID(),
                status);
  }
  return status;
}

void IAddonInstanceHandler::DestroyInstance(ADDON_HANDLE instance)
{
  std::unique_lock<std::mutex> lock(m_cdSec);
  if (m_addon && m_ifc)
  {
    m_ifc->kodi_addon_base_h->kodi_addon_destroy_instance_v1(m_process->m_hdl, m_type, instance);
    m_ifc = nullptr;
  }

  CServiceBroker::GetAddonIfcCtrl().ReleaseAddonProcess(m_process, this);
  m_process = nullptr;
}

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
