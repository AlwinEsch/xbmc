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

#include "AddonCallbacksPVR.h"

#include "Application.h"
#include "cores/dvdplayer/DVDDemuxers/DVDDemuxUtils.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "epg/EpgContainer.h"
#include "events/EventLog.h"
#include "events/NotificationEvent.h"
#include "pvr/PVRManager.h"
#include "pvr/channels/PVRChannelGroupsContainer.h"
#include "pvr/channels/PVRChannelGroupInternal.h"
#include "pvr/addons/PVRClient.h"
#include "pvr/recordings/PVRRecordings.h"
#include "pvr/timers/PVRTimers.h"
#include "pvr/timers/PVRTimerInfoTag.h"
#include "utils/log.h"
#include "utils/StringUtils.h"

using namespace ADDON;
using namespace PVR;
using namespace EPG;

namespace PVRLIB
{
namespace V2
{

CAddonCallbacksPVR::CAddonCallbacksPVR(CAddon* addon)
  : ADDON::IAddonCallback(addon, m_apiLevel, m_version),
    m_callbacks(new CB_PVRLib)
{
  /* write Kodi PVR specific add-on function addresses to callback table */
  m_callbacks->add_menu_hook                  = CAddonCallbacksPVR::add_menu_hook;
  m_callbacks->recording                      = CAddonCallbacksPVR::recording;

  m_callbacks->transfer_epg_entry             = CAddonCallbacksPVR::transfer_epg_entry;
  m_callbacks->transfer_channel_entry         = CAddonCallbacksPVR::transfer_channel_entry;
  m_callbacks->transfer_channel_group         = CAddonCallbacksPVR::transfer_channel_group;
  m_callbacks->transfer_channel_group_member  = CAddonCallbacksPVR::transfer_channel_group_member;
  m_callbacks->transfer_timer_entry           = CAddonCallbacksPVR::transfer_timer_entry;
  m_callbacks->transfer_recording_entry       = CAddonCallbacksPVR::transfer_recording_entry;

  m_callbacks->trigger_channel_update         = CAddonCallbacksPVR::trigger_channel_update;
  m_callbacks->trigger_channel_groups_update  = CAddonCallbacksPVR::trigger_channel_groups_update;
  m_callbacks->trigger_timer_update           = CAddonCallbacksPVR::trigger_timer_update;
  m_callbacks->trigger_recording_update       = CAddonCallbacksPVR::trigger_recording_update;
  m_callbacks->trigger_epg_update             = CAddonCallbacksPVR::trigger_epg_update;
}

CAddonCallbacksPVR::~CAddonCallbacksPVR()
{
  /* delete the callback table */
  delete m_callbacks;
}
/*\_____________________________________________________________________________
\*/
A_DLLEXPORT CB_PVRLib* PVRLIB_V2_register_level(void *hdl, int level)
{
  CB_PVRLib *cb = nullptr;
  if (!hdl)
    CLog::Log(LOGERROR, "libKODI_pvr-ERROR: %s is called with NULL handle !!!", __FUNCTION__);
  else
  {
    cb = static_cast<CB_PVRLib*>(CAddonCallbacks::PVRLib_RegisterLevel(((AddonCB*)hdl)->addonData, level));
    if (!cb)
      CLog::Log(LOGERROR, "libKODI_pvr-ERROR: %s can't get callback table from Kodi !!!", __FUNCTION__);
  }
  return cb;
}

A_DLLEXPORT bool PVRLIB_V2_unregister(void *hdl, void* cb)
{
  if (hdl && cb)
    CAddonCallbacks::PVRLib_UnRegisterMe(((AddonCB*)hdl)->addonData, ((CB_PVRLib*)cb));
}
/*\_____________________________________________________________________________
\*/
CPVRClient *CAddonCallbacksPVR::GetPVRClient(void* hdl)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (!addon || !addon->PVRLib_GetHelper())
  {
    CLog::Log(LOGERROR, "PVR - %s - called with a null pointer", __FUNCTION__);
    return NULL;
  }

  return dynamic_cast<CPVRClient *>(static_cast<CAddonCallbacksPVR*>(addon->PVRLib_GetHelper())->m_addon);
}
/*\_____________________________________________________________________________
\*/
void CAddonCallbacksPVR::add_menu_hook(void* hdl, PVR_MENUHOOK* hook)
{
  CPVRClient *client = GetPVRClient(hdl);
  if (!hook || !client)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  PVR_MENUHOOKS *hooks = client->GetMenuHooks();
  if (hooks)
  {
    PVR_MENUHOOK hookInt;
    hookInt.iHookId            = hook->iHookId;
    hookInt.iLocalizedStringId = hook->iLocalizedStringId;
    hookInt.category           = hook->category;

    /* add this new hook */
    hooks->push_back(hookInt);
  }
}

void CAddonCallbacksPVR::recording(void* hdl, const char* strName, const char* strFileName, bool bOnOff)
{
  CPVRClient *client = GetPVRClient(hdl);
  if (!client || !strFileName)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  std::string strLine1 = StringUtils::Format(g_localizeStrings.Get(bOnOff ? 19197 : 19198).c_str(), client->Name().c_str());
  std::string strLine2;
  if (strName)
    strLine2 = strName;
  else if (strFileName)
    strLine2 = strFileName;

  /* display a notification for 5 seconds */
  CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Info, strLine1, strLine2, 5000, false);
  CEventLog::GetInstance().Add(EventPtr(new CNotificationEvent(client->Name(), strLine1, client->Icon(), strLine2)));

  CLog::Log(LOGDEBUG, "PVR - %s - recording %s on client '%s'. name='%s' filename='%s'",
      __FUNCTION__, bOnOff ? "started" : "finished", client->Name().c_str(), strName, strFileName);
}
/*\_____________________________________________________________________________
\*/
void CAddonCallbacksPVR::transfer_epg_entry(void *userData, const ADDON_HANDLE handle, const EPG_TAG *epgentry)
{
  if (!handle)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  CEpg *kodiEpg = static_cast<CEpg *>(handle->dataAddress);
  if (!kodiEpg)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  /* transfer this entry to the epg */
  kodiEpg->UpdateEntry(epgentry, handle->dataIdentifier == 1 /* update db */);
}

void CAddonCallbacksPVR::transfer_channel_entry(void* hdl, const ADDON_HANDLE handle, const PVR_CHANNEL *channel)
{
  if (!handle)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  CPVRClient *client                     = GetPVRClient(hdl);
  CPVRChannelGroupInternal *kodiChannels = static_cast<CPVRChannelGroupInternal *>(handle->dataAddress);
  if (!channel || !client || !kodiChannels)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  /* transfer this entry to the internal channels group */
  CPVRChannelPtr transferChannel(new CPVRChannel(*channel, client->GetID()));
  kodiChannels->UpdateFromClient(transferChannel);
}

void CAddonCallbacksPVR::transfer_channel_group(void* hdl, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* group)
{
  if (!handle)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  CPVRChannelGroups *kodiGroups = static_cast<CPVRChannelGroups *>(handle->dataAddress);
  if (!group || !kodiGroups)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  if (strlen(group->strGroupName) == 0)
  {
    CLog::Log(LOGERROR, "PVR - %s - empty group name", __FUNCTION__);
    return;
  }

  /* transfer this entry to the groups container */
  CPVRChannelGroup transferGroup(*group);
  kodiGroups->UpdateFromClient(transferGroup);
}

void CAddonCallbacksPVR::transfer_channel_group_member(void* hdl, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* member)
{
  if (!handle)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  CPVRClient *client      = GetPVRClient(hdl);
  CPVRChannelGroup *group = static_cast<CPVRChannelGroup *>(handle->dataAddress);
  if (!member || !client || !group)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  CPVRChannelPtr channel  = g_PVRChannelGroups->GetByUniqueID(member->iChannelUniqueId, client->GetID());
  if (!channel)
  {
    CLog::Log(LOGERROR, "PVR - %s - cannot find group '%s' or channel '%d'", __FUNCTION__, member->strGroupName, member->iChannelUniqueId);
  }
  else if (group->IsRadio() == channel->IsRadio())
  {
    /* transfer this entry to the group */
    group->AddToGroup(channel, member->iChannelNumber);
  }
}

void CAddonCallbacksPVR::transfer_timer_entry(void* hdl, const ADDON_HANDLE handle, const PVR_TIMER *timer)
{
  if (!handle)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  CPVRClient *client     = GetPVRClient(hdl);
  CPVRTimers *kodiTimers = static_cast<CPVRTimers *>(handle->dataAddress);
  if (!timer || !client || !kodiTimers)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  /* Note: channel can be NULL here, for instance for epg-based repeating timers ("record on any channel" condition). */
  CPVRChannelPtr channel = g_PVRChannelGroups->GetByUniqueID(timer->iClientChannelUid, client->GetID());

  /* transfer this entry to the timers container */
  CPVRTimerInfoTagPtr transferTimer(new CPVRTimerInfoTag(*timer, channel, client->GetID()));
  kodiTimers->UpdateFromClient(transferTimer);
}

void CAddonCallbacksPVR::transfer_recording_entry(void* hdl, const ADDON_HANDLE handle, const PVR_RECORDING *recording)
{
  if (!handle)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  CPVRClient *client             = GetPVRClient(hdl);
  CPVRRecordings *kodiRecordings = static_cast<CPVRRecordings *>(handle->dataAddress);
  if (!recording || !client || !kodiRecordings)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  /* transfer this entry to the recordings container */
  CPVRRecordingPtr transferRecording(new CPVRRecording(*recording, client->GetID()));
  kodiRecordings->UpdateFromClient(transferRecording);
}
/*\_____________________________________________________________________________
\*/
void CAddonCallbacksPVR::trigger_channel_update(void* hdl)
{
  /* update the channels table in the next iteration of the pvrmanager's main loop */
  g_PVRManager.TriggerChannelsUpdate();
}

void CAddonCallbacksPVR::trigger_channel_groups_update(void* hdl)
{
  /* update all channel groups in the next iteration of the pvrmanager's main loop */
  g_PVRManager.TriggerChannelGroupsUpdate();
}

void CAddonCallbacksPVR::trigger_timer_update(void* hdl)
{
  /* update the timers table in the next iteration of the pvrmanager's main loop */
  g_PVRManager.TriggerTimersUpdate();
}

void CAddonCallbacksPVR::trigger_recording_update(void* hdl)
{
  /* update the recordings table in the next iteration of the pvrmanager's main loop */
  g_PVRManager.TriggerRecordingsUpdate();
}

void CAddonCallbacksPVR::trigger_epg_update(void* hdl, unsigned int iChannelUid)
{
  // get the client
  CPVRClient *client = GetPVRClient(hdl);
  if (!client)
  {
    CLog::Log(LOGERROR, "PVR - %s - invalid handler data", __FUNCTION__);
    return;
  }

  g_EpgContainer.UpdateRequest(client->GetID(), iChannelUid);
}

}; /* namespace V2 */
}; /* namespace PVRLIB */
