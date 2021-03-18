/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_ADDONINSTANCE_VISUALIZATION_H
#define C_API_ADDONINSTANCE_VISUALIZATION_H

#include "../addon_base.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* KODI_ADDON_VISUALIZATION_HDL;

  struct VIS_INFO
  {
    bool wants_freq;
    int sync_delay;
  };

  struct VIS_TRACK
  {
    const char* title;
    const char* artist;
    const char* album;
    const char* albumArtist;
    const char* genre;
    const char* comment;
    const char* lyrics;

    const char* reserved1;
    const char* reserved2;

    int trackNumber;
    int discNumber;
    int duration;
    int year;
    int rating;

    int reserved3;
    int reserved4;
  };

  struct VIS_PROPS
  {
    ADDON_HARDWARE_CONTEXT2 device;
    int x;
    int y;
    int width;
    int height;
    float pixelRatio;
    char* name;
    char* presets;
    char* profile;
  };

  typedef KODI_ADDON_VISUALIZATION_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_CREATE_V1)(KODI_OWN_HDL kodi_hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_DESTROY_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_START_V1)(KODI_ADDON_VISUALIZATION_HDL hdl,
                                                     int channels,
                                                     int samples_per_sec,
                                                     int bits_per_sample,
                                                     const char* song_name);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_STOP_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);

  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_GET_INFO_V1)(KODI_ADDON_VISUALIZATION_HDL hdl, struct VIS_INFO* info);

  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_AUDIO_DATA_V1)(KODI_ADDON_VISUALIZATION_HDL hdl,
                                                          const float* audio_data,
                                                          size_t audio_data_length,
                                                          const float* freq_data,
                                                          size_t freq_data_length);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_IS_DIRTY_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_RENDER_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);

  typedef unsigned int(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_GET_PRESETS_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef int(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_GET_ACTIVE_PRESET_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_PREV_PRESET_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_NEXT_PRESET_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_LOAD_PRESET_V1)(KODI_ADDON_VISUALIZATION_HDL hdl, int select);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_RANDOM_PRESET_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_LOCK_PRESET_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_RATE_PRESET_V1)(KODI_ADDON_VISUALIZATION_HDL hdl, bool plus_minus);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_IS_LOCKED_V1)(KODI_ADDON_VISUALIZATION_HDL hdl);

  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_UPDATE_ALBUMART_V1)(KODI_ADDON_VISUALIZATION_HDL hdl,
                                                               const char* albumart);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VISUALIZATION_UPDATE_TRACK_V1)(KODI_ADDON_VISUALIZATION_HDL hdl,
                                                            const struct VIS_TRACK* track);

  typedef struct KODI_ADDON_VISUALIZATION_FUNC
  {
    PFN_KODI_ADDON_VISUALIZATION_CREATE_V1 create;
    PFN_KODI_ADDON_VISUALIZATION_DESTROY_V1 destroy;
    PFN_KODI_ADDON_VISUALIZATION_START_V1 start;
    PFN_KODI_ADDON_VISUALIZATION_STOP_V1 stop;

    PFN_KODI_ADDON_VISUALIZATION_GET_INFO_V1 get_info;

    PFN_KODI_ADDON_VISUALIZATION_AUDIO_DATA_V1 audio_data;
    PFN_KODI_ADDON_VISUALIZATION_IS_DIRTY_V1 is_dirty;
    PFN_KODI_ADDON_VISUALIZATION_RENDER_V1 render;

    PFN_KODI_ADDON_VISUALIZATION_GET_PRESETS_V1 get_presets;
    PFN_KODI_ADDON_VISUALIZATION_GET_ACTIVE_PRESET_V1 get_active_preset;
    PFN_KODI_ADDON_VISUALIZATION_PREV_PRESET_V1 prev_preset;
    PFN_KODI_ADDON_VISUALIZATION_NEXT_PRESET_V1 next_preset;
    PFN_KODI_ADDON_VISUALIZATION_LOAD_PRESET_V1 load_preset;
    PFN_KODI_ADDON_VISUALIZATION_RANDOM_PRESET_V1 random_preset;
    PFN_KODI_ADDON_VISUALIZATION_LOCK_PRESET_V1 lock_preset;
    PFN_KODI_ADDON_VISUALIZATION_RATE_PRESET_V1 rate_preset;
    PFN_KODI_ADDON_VISUALIZATION_IS_LOCKED_V1 is_locked;

    PFN_KODI_ADDON_VISUALIZATION_UPDATE_ALBUMART_V1 update_albumart;
    PFN_KODI_ADDON_VISUALIZATION_UPDATE_TRACK_V1 update_track;
  } KODI_ADDON_VISUALIZATION_FUNC;

  ATTR_DLL_EXPORT void kodi_addon_visualization_get_properties(KODI_OWN_HDL hdl, struct VIS_PROPS* props) __INTRODUCED_IN_KODI(1);

  ATTR_DLL_EXPORT void kodi_addon_visualization_transfer_preset(KODI_OWN_HDL hdl,
                                                                        const char* preset)
      __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_addon_visualization_clear_presets(KODI_OWN_HDL hdl)
      __INTRODUCED_IN_KODI(1);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_VISUALIZATION_H */
