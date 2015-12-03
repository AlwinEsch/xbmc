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

#include "AddonCB_General.h"
#include "AddonCallbacksAddon.h"

#include "Application.h"
#include "CompileInfo.h"
#include "LangInfo.h"
#include "addons/Addon.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "interfaces/builtins/Builtins.h"
#include "messaging/ApplicationMessenger.h"
#include "utils/CharsetConverter.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "utils/XMLUtils.h"

using namespace ADDON;

namespace AddOnLIB
{
namespace V2
{
extern "C"
{

CAddonCB_General::CAddonCB_General()
{

}

void CAddonCB_General::Init(CB_AddOnLib *callbacks)
{
  callbacks->General.get_setting                    = CAddonCB_General::get_setting;
  callbacks->General.addon_log                      = CAddonCB_General::addon_log;
  callbacks->General.queue_notification             = CAddonCB_General::queue_notification;
  callbacks->General.queue_notification_from_type   = CAddonCB_General::queue_notification_from_type;
  callbacks->General.queue_notification_with_image  = CAddonCB_General::queue_notification_with_image;
  callbacks->General.unknown_to_utf8                = CAddonCB_General::unknown_to_utf8;
  callbacks->General.get_localized_string           = CAddonCB_General::get_localized_string;
  callbacks->General.get_dvd_menu_language          = CAddonCB_General::get_dvd_menu_language;
  callbacks->General.free_string                    = CAddonCB_General::free_string;
  callbacks->General.get_volume                     = CAddonCB_General::get_volume;
  callbacks->General.set_volume                     = CAddonCB_General::set_volume;
  callbacks->General.is_muted                       = CAddonCB_General::is_muted;
  callbacks->General.toggle_mute                    = CAddonCB_General::toggle_mute;
  callbacks->General.eject_optical_drive            = CAddonCB_General::eject_optical_drive;
  callbacks->General.kodi_version                   = CAddonCB_General::kodi_version;
  callbacks->General.kodi_quit                      = CAddonCB_General::kodi_quit;
}

bool CAddonCB_General::get_setting(
        void*                     hdl,
        const char*               strSettingName,
        void*                     settingValue)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (addon == nullptr || strSettingName == nullptr || settingValue == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - called with a null pointer", __FUNCTION__);
    return false;
  }

  CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(addon->AddOnLib_GetHelper());

  try
  {
    CLog::Log(LOGDEBUG, "CAddonCallbacksAddon - %s - add-on '%s' requests setting '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strSettingName);

    if (strcasecmp(strSettingName, "__addonpath__") == 0)
    {
      strcpy((char*) settingValue, addonHelper->GetAddon()->Path().c_str());
      return true;
    }

    if (!addonHelper->GetAddon()->ReloadSettings())
    {
      CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - could't get settings for add-on '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str());
      return false;
    }

    const TiXmlElement *category = addonHelper->GetAddon()->GetSettingsXML()->FirstChildElement("category");
    if (!category) // add a default one...
      category = addonHelper->GetAddon()->GetSettingsXML();

    while (category)
    {
      const TiXmlElement *setting = category->FirstChildElement("setting");
      while (setting)
      {
        const std::string   id = XMLUtils::GetAttribute(setting, "id");
        const std::string type = XMLUtils::GetAttribute(setting, "type");

        if (id == strSettingName && !type.empty())
        {
          if (type == "text"     || type == "ipaddress" ||
              type == "folder"   || type == "action"    ||
              type == "music"    || type == "pictures"  ||
              type == "programs" || type == "fileenum"  ||
              type == "file"     || type == "labelenum")
          {
            strcpy((char*) settingValue, addonHelper->GetAddon()->GetSetting(id).c_str());
            return true;
          }
          else if (type == "number" || type == "enum")
          {
            *(int*) settingValue = (int) atoi(addonHelper->GetAddon()->GetSetting(id).c_str());
            return true;
          }
          else if (type == "bool")
          {
            *(bool*) settingValue = (bool) (addonHelper->GetAddon()->GetSetting(id) == "true" ? true : false);
            return true;
          }
          else if (type == "slider")
          {
            const char *option = setting->Attribute("option");
            if (option && strcmpi(option, "int") == 0)
            {
              *(int*) settingValue = (int) atoi(addonHelper->GetAddon()->GetSetting(id).c_str());
              return true;
            }
            else
            {
              *(float*) settingValue = (float) atof(addonHelper->GetAddon()->GetSetting(id).c_str());
              return true;
            }
          }
        }
        setting = setting->NextSiblingElement("setting");
      }
      category = category->NextSiblingElement("category");
    }
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - can't find setting '%s' in '%s'", __FUNCTION__, strSettingName, addonHelper->GetAddon()->Name().c_str());
  }
  catch (std::exception &e)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - exception '%s' caught in call in add-on '%s'. please contact the developer of this addon: %s",
        __FUNCTION__, e.what(), addonHelper->GetAddon()->Name().c_str(), addonHelper->GetAddon()->Author().c_str());
  }

  return false;
}

void CAddonCB_General::addon_log(
        void*                     hdl,
        const addon_log_t         addonLogLevel,
        const char*               strMessage)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (addon == nullptr || strMessage == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(addon->AddOnLib_GetHelper());

  try
  {
    int logLevel = LOGNONE;
    switch (addonLogLevel)
    {
      case LOG_FATAL:
        logLevel = LOGFATAL;
        break;
      case LOG_SEVERE:
        logLevel = LOGSEVERE;
        break;
      case LOG_ERROR:
        logLevel = LOGERROR;
        break;
      case LOG_WARNING:
        logLevel = LOGWARNING;
        break;
      case LOG_NOTICE:
        logLevel = LOGNOTICE;
        break;
      case LOG_INFO:
        logLevel = LOGINFO;
        break;
      case LOG_DEBUG:
        logLevel = LOGDEBUG;
        break;
      default:
        break;
    }

    CLog::Log(logLevel, "AddOnLog: %s: %s", addonHelper->GetAddon()->Name().c_str(), strMessage);
  }
  catch (std::exception &e)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - exception '%s' caught in call in add-on '%s'. please contact the developer of this addon: %s",
        __FUNCTION__, e.what(), addonHelper->GetAddon()->Name().c_str(), addonHelper->GetAddon()->Author().c_str());
  }
}

void CAddonCB_General::queue_notification(
        void*                     hdl,
        const queue_msg_t         type,
        const char*               strMessage)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (addon == nullptr || strMessage == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(addon->AddOnLib_GetHelper());

  try
  {
    switch (type)
    {
      case QUEUE_WARNING:
        CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Warning, addonHelper->GetAddon()->Name(), strMessage, 3000, true);
        CLog::Log(LOGDEBUG, "CAddonCallbacksAddon - %s - %s - Warning Message: '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strMessage);
        break;

      case QUEUE_ERROR:
        CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Error, addonHelper->GetAddon()->Name(), strMessage, 3000, true);
        CLog::Log(LOGDEBUG, "CAddonCallbacksAddon - %s - %s - Error Message : '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strMessage);
        break;

      case QUEUE_INFO:
      default:
        CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Info, addonHelper->GetAddon()->Name(), strMessage, 3000, false);
        CLog::Log(LOGDEBUG, "CAddonCallbacksAddon - %s - %s - Info Message : '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strMessage);
        break;
    }
  }
  catch (std::exception &e)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - exception '%s' caught in call in add-on '%s'. please contact the developer of this addon: %s",
        __FUNCTION__, e.what(), addonHelper->GetAddon()->Name().c_str(), addonHelper->GetAddon()->Author().c_str());
  }
}

void CAddonCB_General::queue_notification_from_type(
        void*                     hdl,
        const queue_msg_t         type,
        const char*               aCaption,
        const char*               aDescription,
        unsigned int              displayTime,
        bool                      withSound,
        unsigned int              messageTime)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (addon == nullptr || aCaption == nullptr || aDescription == nullptr)
  {
    CLog::Log(LOGERROR, "CInternalAddOnLib_General - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(static_cast<CAddonCallbacks*>(addon)->AddOnLib_GetHelper());
  try
  {
    CGUIDialogKaiToast::eMessageType usedType;
    switch (type)
    {
    case QUEUE_WARNING:
      usedType = CGUIDialogKaiToast::Warning;
      break;
    case QUEUE_ERROR:
      usedType = CGUIDialogKaiToast::Error;
      break;
    case QUEUE_INFO:
    default:
      usedType = CGUIDialogKaiToast::Info;
      break;
    }
    CGUIDialogKaiToast::QueueNotification(usedType, aCaption, aDescription, displayTime, withSound, messageTime);
  }
  catch (std::exception &e)
  {
    CLog::Log(LOGERROR, "CInternalAddOnLib_General - %s - exception '%s' caught in call in add-on '%s'. please contact the developer of this addon: %s",
        __FUNCTION__, e.what(), addonHelper->GetAddon()->Name().c_str(), addonHelper->GetAddon()->Author().c_str());
  }
}

void CAddonCB_General::queue_notification_with_image(
        void*                     hdl,
        const char*               aImageFile,
        const char*               aCaption,
        const char*               aDescription,
        unsigned int              displayTime,
        bool                      withSound,
        unsigned int              messageTime)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (addon == nullptr || aImageFile == nullptr || aCaption == nullptr  || aDescription == nullptr)
  {
    CLog::Log(LOGERROR, "CInternalAddOnLib_General - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(static_cast<CAddonCallbacks*>(addon)->AddOnLib_GetHelper());

  try
  {
    CGUIDialogKaiToast::QueueNotification(aImageFile, aCaption, aDescription, displayTime, withSound, messageTime);
  }
  catch (std::exception &e)
  {
    CLog::Log(LOGERROR, "CInternalAddOnLib_General - %s - exception '%s' caught in call in add-on '%s'. please contact the developer of this addon: %s",
        __FUNCTION__, e.what(), addonHelper->GetAddon()->Name().c_str(), addonHelper->GetAddon()->Author().c_str());
  }
}

char* CAddonCB_General::unknown_to_utf8(
        void*                     hdl,
        const char*               strSource,
        bool&                     ret,
        bool                      failOnBadChar)
{
  std::string string;
  if (strSource != nullptr)
    ret = g_charsetConverter.unknownToUTF8(strSource, string, failOnBadChar);
  else
  {
    string = "";
    ret = false;
  }
  char* buffer = strdup(string.c_str());
  return buffer;
}

char* CAddonCB_General::get_localized_string(
        void*                     hdl,
        uint32_t                  labelId)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (addon == nullptr || g_application.m_bStop)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAddon - %s - called with a null pointer", __FUNCTION__);
    return nullptr;
  }

  CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(static_cast<CAddonCallbacks*>(addon)->AddOnLib_GetHelper());

  std::string string;
  if (labelId >= 30000 && labelId <= 30999)
    string = addonHelper->GetAddon()->GetString(labelId).c_str();
  else if (labelId >= 32000 && labelId <= 32999)
    string = addonHelper->GetAddon()->GetString(labelId).c_str();
  else
    string = g_localizeStrings.Get(labelId).c_str();

  char* buffer = strdup(string.c_str());
  return buffer;
}

void CAddonCB_General::get_dvd_menu_language(
        void*                     hdl,
        char&                     language,
        unsigned int&             iMaxStringSize)
{
  strncpy(&language, g_langInfo.GetDVDMenuLanguage().c_str(), iMaxStringSize);
}

void CAddonCB_General::free_string(
        void*                     hdl,
        char*                     str)
{
  free(str);
}

float CAddonCB_General::get_volume(
        void*                     hdl,
        bool                      percentage)
{
  return g_application.GetVolume(percentage);
}

void CAddonCB_General::set_volume(
        void*                     hdl,
        float                     value,
        bool                      isPercentage)
{
  g_application.SetVolume(value, isPercentage);
}

bool CAddonCB_General::is_muted(
        void*                     hdl)
{
  return g_application.IsMutedInternal();
}

void CAddonCB_General::toggle_mute(
        void*                     hdl)
{
  g_application.ToggleMute();
}

bool CAddonCB_General::eject_optical_drive(
      void*                     hdl)
{
  return CBuiltins::GetInstance().Execute("EjectTray") == 0 ? true : false;
}

void CAddonCB_General::kodi_version(
      void*                     hdl,
      char*&                    compile_name,
      int&                      major,
      int&                      minor,
      char*&                    revision,
      char*&                    tag,
      char*&                    tagversion)
{
  compile_name = strdup(CCompileInfo::GetAppName());
  major        = CCompileInfo::GetMajor();
  minor        = CCompileInfo::GetMinor();
  revision     = strdup(CCompileInfo::GetSCMID());
  std::string tagStr = CCompileInfo::GetSuffix();
  if (StringUtils::StartsWithNoCase(tagStr, "alpha"))
  {
    tag = strdup("alpha");
    tagversion = strdup(StringUtils::Mid(tagStr, 5).c_str());
  }
  else if (StringUtils::StartsWithNoCase(tagStr, "beta"))
  {
    tag = strdup("beta");
    tagversion = strdup(StringUtils::Mid(tagStr, 4).c_str());
  }
  else if (StringUtils::StartsWithNoCase(tagStr, "rc"))
  {
    tag = strdup("releasecandidate");
    tagversion = strdup(StringUtils::Mid(tagStr, 2).c_str());
  }
  else if (tagStr.empty())
    tag = strdup("stable");
  else
    tag = strdup("prealpha");
}

void CAddonCB_General::kodi_quit(
        void*                     hdl)
{
  KODI::MESSAGING::CApplicationMessenger::GetInstance().PostMsg(TMSG_QUIT);
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AddOnLIB */
