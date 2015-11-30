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

  inline void CAddOnLib_General::Log(const addon_log_t loglevel, const char *format, ... )
  {
    va_list args;
    va_start(args, format);
    CAddonLib::g_libKODI_Internal->Log(loglevel, format, args);
  }

  inline bool CAddOnLib_General::GetSetting(const std::string& settingName, void *settingValue)
  {
    return CAddonLib::g_libKODI_Internal->GetSetting(settingName, settingValue);
  }

  inline void CAddOnLib_General::QueueNotification(const queue_msg_t type, const char *format, ... )
  {
    va_list args;
    va_start(args, format);
    CAddonLib::g_libKODI_Internal->QueueNotification(type, format, args);
  }

  inline void CAddOnLib_General::QueueNotification(
    const queue_msg_t  type,
    const std::string& aCaption,
    const std::string& aDescription,
    unsigned int       displayTime,
    bool               withSound,
    unsigned int       messageTime)
  {
    CAddonLib::g_libKODI_Internal->QueueNotification(
                          type, aCaption, aDescription,
                          displayTime, withSound, messageTime);
  }

  inline void CAddOnLib_General::QueueNotification(
    const std::string& aCaption,
    const std::string& aDescription)
  {
    CAddonLib::g_libKODI_Internal->QueueNotification(aCaption, aDescription);
  }

  inline void CAddOnLib_General::QueueNotification(
    const std::string& aImageFile,
    const std::string& aCaption,
    const std::string& aDescription,
    unsigned int       displayTime,
    bool               withSound,
    unsigned int       messageTime)
  {
    CAddonLib::g_libKODI_Internal->QueueNotification(
                          aImageFile, aCaption, aDescription,
                          displayTime, withSound, messageTime);
  }

  inline bool CAddOnLib_General::UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar)
  {
    return CAddonLib::g_libKODI_Internal->UnknownToUTF8(stringSrc, utf8StringDst, failOnBadChar);
  }

  inline std::string CAddOnLib_General::GetLocalizedString(uint32_t labelId)
  {
    return CAddonLib::g_libKODI_Internal->GetLocalizedString(labelId);
  }

  inline const std::string CAddOnLib_General::GetDVDMenuLanguage()
  {
    return CAddonLib::g_libKODI_Internal->GetDVDMenuLanguage();
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
