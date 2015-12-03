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

  inline bool CAddOnLib_General::GetSettingString(
      const std::string& settingName,
      std::string&       settingValue)
  {
    char * buffer = (char*) malloc(1024);
    buffer[0] = 0; /* Set the end of string */
    bool ret = CAddonLib::g_libKODI_Internal->GetSetting(settingName, buffer);
    if (ret)
      settingValue = buffer;
    free(buffer);
    return ret;
  }

  inline bool CAddOnLib_General::GetSettingInt(
      const std::string& settingName,
      int&               settingValue)
  {
    return CAddonLib::g_libKODI_Internal->GetSetting(settingName, &settingValue);
  }

  inline bool CAddOnLib_General::GetSettingBoolean(
      const std::string& settingName,
      bool&              settingValue)
  {
    return CAddonLib::g_libKODI_Internal->GetSetting(settingName, &settingValue);
  }

  inline bool CAddOnLib_General::GetSettingFloat(
      const std::string& settingName,
      float&             settingValue)
  {
    return CAddonLib::g_libKODI_Internal->GetSetting(settingName, &settingValue);
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

  inline std::string CAddOnLib_General::GetLocalizedString(uint32_t labelId, const std::string& strDefault)
  {
    return CAddonLib::g_libKODI_Internal->GetLocalizedString(labelId, strDefault);
  }

  inline std::string CAddOnLib_General::GetDVDMenuLanguage()
  {
    return CAddonLib::g_libKODI_Internal->GetDVDMenuLanguage();
  }

  inline float CAddOnLib_General::GetVolume(bool percentage)
  {
    return CAddonLib::g_libKODI_Internal->GetVolume(percentage);
  }

  inline void CAddOnLib_General::SetVolume(float value, bool isPercentage)
  {
    CAddonLib::g_libKODI_Internal->SetVolume(value, isPercentage);
  }

  inline bool CAddOnLib_General::IsMuted()
  {
    return CAddonLib::g_libKODI_Internal->IsMuted();
  }

  inline void CAddOnLib_General::ToggleMute(void)
  {
    CAddonLib::g_libKODI_Internal->ToggleMute();
  }

  inline void CAddOnLib_General::SetMute(bool mute)
  {
    CAddonLib::g_libKODI_Internal->SetMute(mute);
  }

  inline bool CAddOnLib_General::EjectOpticalDrive()
  {
    return CAddonLib::g_libKODI_Internal->EjectOpticalDrive();
  }

  inline void CAddOnLib_General::KodiVersion(kodi_version_t& version)
  {
    CAddonLib::g_libKODI_Internal->KodiVersion(version);
  }

  inline void CAddOnLib_General::KodiQuit()
  {
    CAddonLib::g_libKODI_Internal->KodiQuit();
  }

  inline std::string TranslateAddonStatus(ADDON_STATUS status)
  {
    return CAddonLib::g_libKODI_Internal->TranslateAddonStatus(status);
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
