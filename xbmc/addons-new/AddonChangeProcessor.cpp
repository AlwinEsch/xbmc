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

#include "AddonChangeProcessor.h"
#include "AddonManager.h"

#include "ServiceBroker.h"
#include "utils/log.h"
#include "utils/TimeUtils.h"

using namespace ADDON_NEW;

CAddonChangeProcessor::CAddonChangeProcessor(const AddonInfoPtr& addonInfo, ProcessFlowPlaceData flowPlace,
                                             ProcessAddonWorkData addonWork, const std::set<CAddonChangeObserver*>& observers)
  : CThread("AddonChangeProcessor"),
    m_flowPlace(flowPlace),
    m_addonWork(addonWork),
    m_observers(observers),
    m_startTime(CTimeUtils::GetFrameTime()),
    m_addonInfo(addonInfo),
    m_manager(CServiceBroker::GetAddonManager()),
    m_inProgress(false)
{
}

bool CAddonChangeProcessor::DoWork(bool waitToSet)
{
  m_waitToSet = waitToSet;
  Create();
  if (m_waitToSet)
    return m_event.WaitMSec(1000);
  return true;
}

bool CAddonChangeProcessor::WaitingForUserInput()
{
  for (const auto& observer : m_observers)
  {
    if (observer->WaitingForUserInput())
    {
      m_startTime = CTimeUtils::GetFrameTime();
      return true;
    }
  }
  return false;
}

void CAddonChangeProcessor::ResetWaitTime()
{
  m_startTime = CTimeUtils::GetFrameTime();
}

void CAddonChangeProcessor::Process(void)
{
  CLog::Log(LOGINFO, "CAddonChangeProcessor::%s: Addon change process started", __FUNCTION__);
  m_inProgress = true;

  if (m_addonWork & AddonWorkDisable)
    DoDisableJob();

  if (m_addonWork & AddonWorkUninstall)
    DoUninstallJob();

  if (m_addonWork & AddonWorkUpdate)
    DoUpdateJob();

  if (m_addonWork & AddonWorkInstall)
    DoInstallJob();

  if (m_addonWork & AddonWorkEnable)
    DoEnableJob();

  m_inProgress = false;
  CLog::Log(LOGINFO, "CAddonChangeProcessor::%s: Addon change process finished", __FUNCTION__);
}

void CAddonChangeProcessor::DoDisableJob()
{
  m_manager.PerformDisableJob(m_addonInfo);
  if (m_waitToSet && m_flowPlace == FlowPlaceBegin)
    m_event.Set();
  CallEventObserver(AddonChangeEvent_Disable, m_addonInfo, m_flowPlace == FlowPlaceEnd);
}

void CAddonChangeProcessor::DoUninstallJob()
{
  CallEventObserver(AddonChangeEvent_UninstallBegin, m_addonInfo, m_flowPlace == FlowPlaceEnd);
  m_manager.PerformUninstallJob(m_addonInfo);
  if (m_waitToSet && m_flowPlace == FlowPlaceBegin)
    m_event.Set();
  CallEventObserver(AddonChangeEvent_UninstallEnd, m_addonInfo, m_flowPlace == FlowPlaceEnd);
}

void CAddonChangeProcessor::DoUpdateJob()
{
  CallEventObserver(AddonChangeEvent_UpdateBegin, m_addonInfo, m_flowPlace == FlowPlaceEnd);
  m_manager.PerformUpdateJob(m_addonInfo);
  if (m_waitToSet && m_flowPlace == FlowPlaceBegin)
    m_event.Set();
  m_addonInfo = m_manager.GetInstalledAddonInfo(m_addonInfo->ID());
  CallEventObserver(AddonChangeEvent_UpdateEnd, m_addonInfo, m_flowPlace == FlowPlaceEnd);
}

void CAddonChangeProcessor::DoInstallJob()
{
  CallEventObserver(AddonChangeEvent_InstallBegin, m_addonInfo, m_flowPlace == FlowPlaceEnd);
  m_manager.PerformInstallJob(m_addonInfo);
  if (m_waitToSet && m_flowPlace == FlowPlaceBegin)
    m_event.Set();
  m_addonInfo = m_manager.GetInstalledAddonInfo(m_addonInfo->ID());
  CallEventObserver(AddonChangeEvent_InstallEnd, m_addonInfo, m_flowPlace == FlowPlaceEnd);
}

void CAddonChangeProcessor::DoEnableJob()
{
  m_manager.PerformEnableJob(m_addonInfo);
  if (m_waitToSet && m_flowPlace == FlowPlaceBegin)
    m_event.Set();
  CallEventObserver(AddonChangeEvent_Enable, m_addonInfo, m_flowPlace == FlowPlaceEnd);
}

void CAddonChangeProcessor::CallEventObserver(AddonChangeEvent event, const AddonInfoPtr& addonInfo, bool lastCall)
{
  for (const auto& observer : m_observers)
  {
    if (observer->Type() == ADDON_TYPE_UNDEFINED || addonInfo->SupportType(observer->Type()))
      observer->AddonChangeEvent(event, addonInfo, lastCall);
  }
}
