#pragma once
/*
 *      Copyright (C) 2015 Team KODI
 *      Copyright (C) 2005-2013 Team XBMC
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
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "internal/libKODI_pvr_Internal.h"

namespace PVRLIB
{
namespace V2
{
  #define DVD_TIME_BASE 1000000
  #define DVD_NOPTS_VALUE    (-1LL<<52) // should be possible to represent in both double and __int64

  class CPVRLib : protected CPVRLib_Internal
  {
  public:
    /*!
     * @brief Resolve all callback methods
     * @param handle Pointer to the add-on
     * @return True when all methods were resolved, false otherwise.
     */
    static bool RegisterMe(void *handle);

    /*!
     * @brief Release all callback methods and close handling with them
     */
    static void UnRegisterMe();

    /*!
     * @brief Add or replace a menu hook for the context menu for this add-on
     * @param hook The hook to add
     */
    static void AddMenuHook(
                         PVR_MENUHOOK*      hook);

    /*!
     * @brief Display a notification in Kodi that a recording started or stopped
     *        on the server
     * @param strRecordingName The name of the recording to display
     * @param strFileName The filename of the recording
     * @param bOn True when recording started, false when it stopped
     */
    static void Recording(
                         const char*        strRecordingName,
                         const char*        strFileName,
                         bool               bOn);

    KODI_PVR_LIBRARY;
  };
  /*\___________________________________________________________________________
  \*/
  class CPVRLib_Transfer
  {
  public:
    /*!
     * @brief Transfer an EPG tag from the add-on to Kodi
     * @param handle The handle parameter that Kodi used when requesting the
     *               EPG data
     * @param entry The entry to transfer to Kodi
     */
    static void EpgEntry(
                         const ADDON_HANDLE handle,
                         const EPG_TAG*     entry);

    /*!
     * @brief Transfer a channel entry from the add-on to Kodi
     * @param handle The handle parameter that Kodi used when requesting the
     *               channel list
     * @param entry The entry to transfer to Kodi
     */
    static void ChannelEntry(
                         const ADDON_HANDLE handle,
                         const PVR_CHANNEL* entry);

    /*!
     * @brief Transfer a timer entry from the add-on to Kodi
     * @param handle The handle parameter that Kodi used when requesting the
     *               timers list
     * @param entry The entry to transfer to Kodi
     */
    static void TimerEntry(
                         const ADDON_HANDLE handle,
                         const PVR_TIMER*   entry);

    /*!
     * @brief Transfer a recording entry from the add-on to Kodi
     * @param handle The handle parameter that Kodi used when requesting the
     *               recordings list
     * @param entry The entry to transfer to Kodi
     */
    static void RecordingEntry(
                         const ADDON_HANDLE handle,
                         const PVR_RECORDING* entry);

    /*!
     * @brief Transfer a channel group from the add-on to Kodi. The group will
     * be created if it doesn't exist.
     * @param handle The handle parameter that Kodi used when requesting the
     *               channel groups list
     * @param entry The entry to transfer to Kodi
     */
    static void ChannelGroup(
                         const ADDON_HANDLE handle,
                         const PVR_CHANNEL_GROUP* entry);

    /*!
     * @brief Transfer a channel group member entry from the add-on to Kodi. The
     * channel will be added to the group if the group can be found.
     * @param handle The handle parameter that Kodi used when requesting the
     *               channel group members list
     * @param entry The entry to transfer to Kodi
     */
    static void ChannelGroupMember(
                         const ADDON_HANDLE handle,
                         const PVR_CHANNEL_GROUP_MEMBER* entry);
  };
  /*\___________________________________________________________________________
  \*/
  class CPVRLib_Trigger
  {
  public:
    /*!
     * @brief Request Kodi to update it's list of timers
     */
    static void TimerUpdate(void);

    /*!
     * @brief Request Kodi to update it's list of recordings
     */
    static void RecordingUpdate(void);

    /*!
     * @brief Request Kodi to update it's list of channels
     */
    static void ChannelUpdate(void);

    /*!
     * @brief Schedule an EPG update for the given channel channel
     * @param iChannelUid The unique id of the channel for this add-on
     */
    static void EpgUpdate(unsigned int iChannelUid);

    /*!
     * @brief Request Kodi to update it's list of channel groups
     */
    static void ChannelGroupsUpdate(void);
  };
  /*\___________________________________________________________________________
  \*/

}; /* namespace V2 */
}; /* namespace PVRLIB */
#include "internal/libKODI_pvr_LibFunc.h"
