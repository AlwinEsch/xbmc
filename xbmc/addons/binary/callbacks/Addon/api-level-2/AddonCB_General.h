#pragma once
/*
 *      Copyright (C) 2015 Team KODI
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

#include "PlatformDefs.h" // for __stat64, ssize_t
#include "addon.api2/AddonLib.h"

extern "C"
{
namespace AddOnLIB
{
namespace V2
{

class CAddonCB_General
{
public:
  CAddonCB_General();

  void Init(CB_AddOnLib_General *callbacks);

  static void addon_log(
        void*                     hdl,
        const addon_log_t         addonLogLevel,
        const char*               strMessage);

  static void queue_notification(
        void*                     hdl,
        const queue_msg_t         type,
        const char*               strMessage);

  static bool get_setting(
        void*                     hdl,
        const char*               strSettingName,
        void*                     settingValue);

  static void queue_notification_from_type(
        void*                     hdl,
        const queue_msg_t         type,
        const char*               aCaption,
        const char*               aDescription,
        unsigned int              displayTime,
        bool                      withSound,
        unsigned int              messageTime);

  static void queue_notification_with_image(
        void*                     hdl,
        const char*               aImageFile,
        const char*               aCaption,
        const char*               aDescription,
        unsigned int              displayTime,
        bool                      withSound,
        unsigned int              messageTime);

  static char* unknown_to_utf8(
        void*                     hdl,
        const char*               strSource,
        bool&                     ret,
        bool                      failOnBadChar);

  static char* get_localized_string(
        void*                     hdl,
        uint32_t                  labelId);

  static void get_dvd_menu_language(
        void*                     hdl,
        char&                     language,
        unsigned int&             iMaxStringSize);

  static void free_string(
        void*                     hdl,
        char*                     str);

  static float get_volume(
        void*                     hdl,
        bool                      percentage);

  static void set_volume(
        void*                     hdl,
        float                     value,
        bool                      isPercentage);

  static bool is_muted(
        void*                     hdl);

  static void toggle_mute(
        void*                     hdl);

  static void kodi_version(
        void*                     hdl,
        char*&                    compile_name,
        int&                      major,
        int&                      minor,
        char*&                    revision,
        char*&                    tag,
        char*&                    tagversion);

  static void kodi_quit(
        void*                     hdl);
};

}; /* namespace V2 */
}; /* namespace AddOnLIB */
}; /* extern "C" */
