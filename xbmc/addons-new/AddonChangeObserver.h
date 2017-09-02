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

#include "AddonInfo.h"

namespace ADDON_NEW
{

  typedef enum AddonChangeEvent
  {
    AddonChangeEvent_Disable,
    AddonChangeEvent_Enable,
    AddonChangeEvent_UpdateBegin,
    AddonChangeEvent_UpdateEnd,
    AddonChangeEvent_InstallBegin,
    AddonChangeEvent_InstallEnd,
    AddonChangeEvent_UninstallBegin,
    AddonChangeEvent_UninstallEnd
  } AddonChangeEvent;

#define GET_ADDON_CHANGE_EVENT_AS_STRING(event) \
  #event

  class CAddonChangeObserver
  {
  public:
    CAddonChangeObserver(ADDON_TYPE type);
    virtual ~CAddonChangeObserver();

    const ADDON_TYPE Type() const { return m_type; }

    virtual void AddonChangeEvent(AddonChangeEvent event, const AddonInfoPtr& addonInfo, bool lastCall) = 0;
    virtual bool WaitingForUserInput() const { return false; }

  private:
    const ADDON_TYPE m_type;
  };

} /* namespace ADDONS_NEW */
