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

namespace AddOnLIB
{
namespace V2
{

  typedef bool    _get_setting(void* HANDLE, const char* settingName, void *settingValue);
  typedef void    _addon_log(void* HANDLE, const addon_log_t loglevel, const char *msg);
  typedef void    _queue_notification(void* HANDLE, const queue_msg_t type, const char *msg);
  typedef void    _queue_notification_from_type(void* HANDLE, const queue_msg_t type, const char* aCaption, const char* aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);
  typedef void    _queue_notification_with_image(void* HANDLE, const char* aImageFile, const char* aCaption, const char* aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);
  typedef char*   _unknown_to_utf8(void* HANDLE, const char* str, bool &ret, bool failOnBadChar);
  typedef char*   _get_localized_string(void* HANDLE, uint32_t labelId);
  typedef void    _get_dvd_menu_language(void* HANDLE, char &language, unsigned int &iMaxStringSize);
  typedef void    _free_string(void* HANDLE, char* str);

  typedef struct CB_AddOn_General
  {
    _get_setting*                   get_setting;
    _addon_log*                     addon_log;
    _queue_notification*            queue_notification;
    _queue_notification_from_type*  queue_notification_from_type;
    _queue_notification_with_image* queue_notification_with_image;
    _unknown_to_utf8*               unknown_to_utf8;
    _get_localized_string*          get_localized_string;
    _get_dvd_menu_language*         get_dvd_menu_language;
    _free_string*                   free_string;
  } CB_AddOnLib_General;

}; /* namespace V2 */
}; /* namespace AddOnLIB */
