#pragma once
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

#include "AddonChangeObserver.h"

#include "threads/Thread.h"

#include <set>

namespace ADDON_NEW
{

  class CAddonManager;

  typedef enum ProcessFlowPlace
  {
    FlowPlaceBegin = (1<<0),
    FlowPlaceContinued = (1<<1),
    FlowPlaceEnd = (1<<2)
  } ProcessFlowPlace;
  typedef int ProcessFlowPlaceData;

  typedef enum ProcessAddonWork
  {
    AddonWorkDisable = (1<<0),
    AddonWorkEnable = (1<<1),
    AddonWorkInstall = (1<<2),
    AddonWorkUninstall = (1<<3),
    AddonWorkUpdate = (1<<4)
  } ProcessWork;
  typedef int ProcessAddonWorkData;

  class CAddonChangeProcessor : public CThread
  {
  public:
    CAddonChangeProcessor(const AddonInfoPtr& addonInfo, ProcessFlowPlaceData flowPlace,
                          ProcessAddonWorkData addonWork, const std::set<CAddonChangeObserver*>& observers);

    bool DoWork(bool waitToSet);
    bool InProgress() const { return m_inProgress; }
    time_t StartTime() const { return m_startTime; }
    const std::string AddonId() const { return m_addonInfo->ID(); }
    const AddonChangeEvent LastStartedEvent() const { return m_lastEvent; }
    bool WaitingForUserInput();
    void ResetWaitTime();

  protected:
    void Process(void) override;

  private:
    void DoDisableJob();
    void DoUninstallJob();
    void DoUpdateJob();
    void DoInstallJob();
    void DoEnableJob();
    void CallEventObserver(AddonChangeEvent event, const AddonInfoPtr& addonInfo, bool lastCall);

    const ProcessFlowPlaceData m_flowPlace;
    const ProcessAddonWorkData m_addonWork;
    const std::set<CAddonChangeObserver*>& m_observers;
    time_t m_startTime;
    AddonInfoPtr m_addonInfo;
    CAddonManager& m_manager;
    bool m_inProgress;
    bool m_waitToSet;
    CEvent m_event;
    AddonChangeEvent m_lastEvent;
  };

} /* namespace ADDONS_NEW */
