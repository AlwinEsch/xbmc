/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#pragma once

#include "core/IMsgHdl.h"
#include "src/shared/api/addon-instance/pvr.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct directFuncToAddon_addoninstance_pvr_h;
struct directFuncToKodi_addoninstance_pvr_h;

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */

namespace KODI_ADDON
{
namespace INTERNAL
{

class ATTR_DLL_LOCAL CHdl_kodi_addoninstance_pvr_h : public IMsgHdl
{
public:
  CHdl_kodi_addoninstance_pvr_h(AddonIfc* ifc) : IMsgHdl(ifc) {}

  void InitDirect(KODI::ADDONS::INTERFACE::directFuncToAddon_addoninstance_pvr_h* ifcToAddon);

#ifndef KODI_INHIBIT_SHARED
  bool HandleMessage(int funcGroup,
                     int func,
                     const msgpack::unpacked& in,
                     msgpack::sbuffer& out) override;
#endif /* !KODI_INHIBIT_SHARED */

  /* Code below becomes on auto generation reused, hand edited parts should included here */
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

  // Calls from Kodi to addon
  static enum PVR_ERROR kodi_addon_pvr_get_capabilities_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      struct PVR_ADDON_CAPABILITIES* capabilities); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_backend_name_v1(void* thisClassHdl,
                                                           KODI_ADDON_PVR_HDL hdl,
                                                           char* str,
                                                           size_t mem_size); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_backend_version_v1(void* thisClassHdl,
                                                              KODI_ADDON_PVR_HDL hdl,
                                                              char* str,
                                                              size_t mem_size); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_backend_hostname_v1(void* thisClassHdl,
                                                               KODI_ADDON_PVR_HDL hdl,
                                                               char* str,
                                                               size_t mem_size); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_connection_string_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl, char* str, size_t mem_size); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_drive_space_v1(void* thisClassHdl,
                                                          KODI_ADDON_PVR_HDL hdl,
                                                          uint64_t* total,
                                                          uint64_t* used); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_call_settings_menu_hook_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_MENUHOOK* menuhook); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_channels_amount_v1(void* thisClassHdl,
                                                              KODI_ADDON_PVR_HDL hdl,
                                                              int* amount); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_channels_v1(void* thisClassHdl,
                                                       KODI_ADDON_PVR_HDL hdl,
                                                       KODI_ADDON_PVR_TRANSFER_HDL handle,
                                                       bool radio); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_channel_stream_properties_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_CHANNEL* channel,
      struct PVR_NAMED_VALUE* properties,
      size_t* properties_count); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_signal_status_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      int channel_uid,
      struct PVR_SIGNAL_STATUS* signal_status); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_descramble_info_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      int channel_uid,
      struct PVR_DESCRAMBLE_INFO* descramble_info); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_channel_groups_amount_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl, int* amount); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_channel_groups_v1(void* thisClassHdl,
                                                             KODI_ADDON_PVR_HDL hdl,
                                                             KODI_ADDON_PVR_TRANSFER_HDL handle,
                                                             bool radio); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_channel_group_members_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      KODI_ADDON_PVR_TRANSFER_HDL handle,
      const struct PVR_CHANNEL_GROUP* group); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_delete_channel_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_CHANNEL* channel); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_rename_channel_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_CHANNEL* channel); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_open_dialog_channel_settings_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_CHANNEL* channel); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_open_dialog_channel_add_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_CHANNEL* channel); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_open_dialog_channel_scan_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_call_channel_menu_hook_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_MENUHOOK* menuhook,
      const struct PVR_CHANNEL* channel); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_epg_for_channel_v1(void* thisClassHdl,
                                                              KODI_ADDON_PVR_HDL hdl,
                                                              KODI_ADDON_PVR_TRANSFER_HDL handle,
                                                              int channel_uid,
                                                              time_t start,
                                                              time_t end); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_is_epg_tag_recordable_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct EPG_TAG* tag,
      bool* is_recordable); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_is_epg_tag_playable_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct EPG_TAG* tag,
      bool* is_playable); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_epg_tag_edl_v1(void* thisClassHdl,
                                                          KODI_ADDON_PVR_HDL hdl,
                                                          const struct EPG_TAG* tag,
                                                          struct PVR_EDL_ENTRY edl[],
                                                          size_t* size); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_epg_tag_stream_properties_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct EPG_TAG* tag,
      struct PVR_NAMED_VALUE* properties,
      size_t* properties_count); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_set_epg_max_past_days_v1(void* thisClassHdl,
                                                                KODI_ADDON_PVR_HDL hdl,
                                                                int past_days); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_set_epg_max_future_days_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl, int future_days); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_call_epg_menu_hook_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_MENUHOOK* menuhook,
      const struct EPG_TAG* tag); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_recordings_amount_v1(void* thisClassHdl,
                                                                KODI_ADDON_PVR_HDL hdl,
                                                                bool deleted,
                                                                int* amount); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_recordings_v1(void* thisClassHdl,
                                                         KODI_ADDON_PVR_HDL hdl,
                                                         KODI_ADDON_PVR_TRANSFER_HDL handle,
                                                         bool deleted); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_delete_recording_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_undelete_recording_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_delete_all_recordings_from_trash_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_rename_recording_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_set_recording_lifetime_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_set_recording_play_count_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording,
      int count); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_set_recording_last_played_position_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording,
      int last_played_position); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_recording_last_played_position_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording,
      int* last_played_position); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_recording_edl_v1(void* thisClassHdl,
                                                            KODI_ADDON_PVR_HDL hdl,
                                                            const struct PVR_RECORDING* recording,
                                                            struct PVR_EDL_ENTRY edl[],
                                                            size_t* size); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_recording_size_v1(void* thisClassHdl,
                                                             KODI_ADDON_PVR_HDL hdl,
                                                             const struct PVR_RECORDING* recording,
                                                             int64_t* size); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_recording_stream_properties_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_RECORDING* recording,
      struct PVR_NAMED_VALUE* properties,
      size_t* properties_count); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_call_recording_menu_hook_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_MENUHOOK* menuhook,
      const struct PVR_RECORDING* recording); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_timer_types_v1(void* thisClassHdl,
                                                          KODI_ADDON_PVR_HDL hdl,
                                                          struct PVR_TIMER_TYPE types[],
                                                          size_t* types_count); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_timers_amount_v1(void* thisClassHdl,
                                                            KODI_ADDON_PVR_HDL hdl,
                                                            int* amount); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_get_timers_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      KODI_ADDON_PVR_TRANSFER_HDL handle); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_add_timer_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_TIMER* timer); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_delete_timer_v1(void* thisClassHdl,
                                                       KODI_ADDON_PVR_HDL hdl,
                                                       const struct PVR_TIMER* timer,
                                                       bool force_delete); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_update_timer_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_TIMER* timer); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_call_timer_menu_hook_v1(
      void* thisClassHdl,
      KODI_ADDON_PVR_HDL hdl,
      const struct PVR_MENUHOOK* menuhook,
      const struct PVR_TIMER* timer); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_on_system_sleep_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_on_system_wake_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_on_power_saving_activated_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl); // Added with API 1

  static enum PVR_ERROR kodi_addon_pvr_on_power_saving_deactivated_v1(
      void* thisClassHdl, KODI_ADDON_PVR_HDL hdl); // Added with API 1
};

} /* namespace INTERNAL */
} /* namespace KODI_ADDON */
