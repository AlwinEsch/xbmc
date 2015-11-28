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

#include <string>

#include "definations.h"
#include "internal/libKODI_addon_GeneralHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{
  class CAddOnLib_General
  {
  public:
    /*!
     * @brief Add a message to KODI's log.
     * @param loglevel The log level of the message.
     * @param format The format of the message to pass to KODI.
     */
    static void Log(
                         const addon_log_t  loglevel,
                         const char*        format,
                         ... );

    /*!
     * @brief Get a settings value for this add-on.
     * @param settingName The name of the setting to get.
     * @param settingValue The value.
     * @return True if the settings was fetched successfully, false otherwise.
     */
    static bool GetSetting(
                         const std::string& settingName,
                         void*              settingValue);

    /*!
     * @brief Queue a notification in the GUI.
     * @param type The message type.
     * @param format The format of the message to pass to display in KODI.
     */
    static void QueueNotification(
                         const queue_msg_t  type,
                         const char*        format,
                         ... );

    /*!
     * @brief Queue a notification in the GUI.
     * @param type The message type.
     * @param aCaption Header Name
     * @param aDescription Message to display on Kodi
     * @param displayTime The time how long message is displayed (default 5 sec)
     * @param withSound is true also warning sound becomes played
     * @param messageTime in how many milli seconds start show of notification
     */
    static void QueueNotification(
                         const queue_msg_t  type,
                         const std::string& aCaption,
                         const std::string& aDescription,
                         unsigned int       displayTime = 5000,
                         bool               withSound   = true,
                         unsigned int       messageTime = 1000);

    /*!
     * @brief Queue a notification in the GUI.
     * @param aCaption Header Name
     * @param aDescription Message to display on Kodi
     */
    static void QueueNotification(
                         const std::string& aCaption,
                         const std::string& aDescription);

    /*!
     * @brief Queue a notification in the GUI.
     * @param aImageFile The image file to show on message
     * @param aCaption Header Name
     * @param aDescription Message to display on Kodi
     * @param displayTime The time how long message is displayed (default 5 sec)
     * @param withSound is true also warning sound becomes played
     * @param messageTime in how many milli seconds start show of notification
     */
    static void QueueNotification(
                         const std::string& aImageFile,
                         const std::string& aCaption,
                         const std::string& aDescription,
                         unsigned int       displayTime = 5000,
                         bool               withSound   = true,
                         unsigned int       messageTime = 1000);

    /*!
     * @brief Translate a string with an unknown encoding to UTF8.
     * @param stringSrc The string to translate.
     * @param utf8StringDst The translated string.
     * @param failOnBadChar return failed if bad character is inside
     * @return true if OK
     */
    static bool UnknownToUTF8(
                         const std::string& stringSrc,
                         std::string&       utf8StringDst,
                         bool               failOnBadChar = false);

    /*!
     * @brief Get a localised message.
     * @param labelId The code of the message to get.
     * @return The message.
     */
    static std::string GetLocalizedString(
                         uint32_t labelId);

    /*!
     * @brief Get the DVD menu language.
     * @return The language.
     */
    static const std::string GetDVDMenuLanguage();
  }; /* class CAddOnLib_General */

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_GeneralFunc.h"
