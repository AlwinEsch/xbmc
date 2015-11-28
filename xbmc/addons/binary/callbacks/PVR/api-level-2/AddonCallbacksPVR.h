#pragma once
/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "system.h"
#include "pvr.api2/PVRLib.h"

#include "addons/binary/callbacks/IAddonCallback.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "addons/include/xbmc_pvr_types.h"

namespace PVR
{
  class CPVRClient;
}

namespace ADDON
{
  class CAddon;
};

namespace PVRLIB
{
namespace V2
{

/*!
 * Callbacks for a PVR add-on to XBMC.
 *
 * Also translates the addon's C structures to XBMC's C++ structures.
 */
class CAddonCallbacksPVR : public ADDON::IAddonCallback
{
public:
  CAddonCallbacksPVR(ADDON::CAddon* addon);
  virtual ~CAddonCallbacksPVR(void);

  static int APILevel() { return m_apiLevel; }
  static std::string Version() { return m_version; }

  /*!
   * @return The callback table.
   */
  CB_PVRLib *GetCallbacks() { return m_callbacks; }
  /*\___________________________________________________________________________
  \*/
  static void add_menu_hook(void* hdl, PVR_MENUHOOK* hook);
  static void recording(void* hdl, const char* strName, const char* strFileName, bool bOnOff);
  /*\___________________________________________________________________________
  \*/
  static void transfer_epg_entry(void *hdl, const ADDON_HANDLE handle, const EPG_TAG* epgentry);
  static void transfer_channel_entry(void *hdl, const ADDON_HANDLE handle, const PVR_CHANNEL* channel);
  static void transfer_channel_group(void *hdl, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* group);
  static void transfer_channel_group_member(void *hdl, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* member);
  static void transfer_timer_entry(void *hdl, const ADDON_HANDLE handle, const PVR_TIMER* timer);
  static void transfer_recording_entry(void *hdl, const ADDON_HANDLE handle, const PVR_RECORDING* recording);
  /*\___________________________________________________________________________
  \*/
  static void trigger_channel_update(void* hdl);
  static void trigger_channel_groups_update(void* hdl);
  static void trigger_timer_update(void* hdl);
  static void trigger_recording_update(void* hdl);
  static void trigger_epg_update(void* hdl, unsigned int iChannelUid);

private:
  static constexpr const int   m_apiLevel = 2;
  static constexpr const char* m_version  = "4.1.0";

  static PVR::CPVRClient* GetPVRClient(void* hdl);

  CB_PVRLib    *m_callbacks; /*!< callback addresses */
};

}; /* namespace V2 */
}; /* namespace PVRLIB */
