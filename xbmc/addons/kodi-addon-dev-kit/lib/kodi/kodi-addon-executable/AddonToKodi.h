#pragma once
/*
 *      Copyright (C) 2017 Team KODI
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

#include "AddonBase.h"
#include "exe/definitions.h"

#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>
#include <string>
#ifdef BUILD_KODI_ADDON
#include <p8-platform/util/StringUtils.h>
#else
#include "utils/StringUtils.h"
#endif

/**
  * @brief Currently fixed size for global shared memory between Kodi and Add-on.
  */
#define DEFAULT_SHARED_MEM_SIZE 10*1024

typedef struct apiMessageIn
{
  uint32_t m_channel;
  uint32_t m_serialNumber;
  uint32_t m_opcode;
  uint32_t m_dataLength;
  uint8_t data[DEFAULT_SHARED_MEM_SIZE-(sizeof(uint32_t)*10)];
} apiMessageIn;

typedef struct apiMessageOut
{
  uint32_t m_channelId;
  uint32_t m_requestID;
  uint32_t m_dataLength;
  uint8_t data[DEFAULT_SHARED_MEM_SIZE-(sizeof(uint32_t)*10)];
} apiMessageOut;

typedef union msgType
{
  apiMessageIn in;
  apiMessageOut out;
} msgType;

typedef struct apiShareData
{
#if (defined TARGET_WINDOWS)
  HANDLE shmSegmentToAddon;
  HANDLE shmSegmentToKodi;
#elif (defined TARGET_POSIX)
  sem_t shmSegmentToAddon;
  sem_t shmSegmentToKodi;
#endif
  msgType message;
} apiShareData;

#define MAX_SEM_COUNT 10 // To use for windows CreateSemaphore(...)

/* Warning: Auto generated code, do not change by hand! */

typedef enum AddonToKodiInterfaceCalls
{
  ADDONTOKODIFUNCTABLE_KODI__GET_ADDON_INFO = 0,
  ADDONTOKODIFUNCTABLE_KODI__OPEN_SETTINGS_DIALOG = 1,
  ADDONTOKODIFUNCTABLE_KODI__UNKNOWN_TO_UTF8 = 2,
  ADDONTOKODIFUNCTABLE_KODI__GET_LOCALIZED_STRING = 3,
  ADDONTOKODIFUNCTABLE_KODI__GET_LANGUAGE = 4,
  ADDONTOKODIFUNCTABLE_KODI__QUEUE_NOTIFICATION = 5,
  ADDONTOKODIFUNCTABLE_KODI__GET_MD5 = 6,
  ADDONTOKODIFUNCTABLE_KODI__GET_TEMP_PATH = 7,
  ADDONTOKODIFUNCTABLE_KODI__GET_REGION = 8,
  ADDONTOKODIFUNCTABLE_KODI__GET_FREE_MEM = 9,
  ADDONTOKODIFUNCTABLE_KODI__GET_GLOBAL_IDLE_TIME = 10,
  ADDONTOKODIFUNCTABLE_KODI__KODI_VERSION = 11,
  ADDONTOKODIFUNCTABLE_ADDON__FREE_STRING = 30000,
  ADDONTOKODIFUNCTABLE_ADDON__GET_ADDON_PATH = 30001,
  ADDONTOKODIFUNCTABLE_ADDON__GET_BASE_USER_PATH = 30002,
  ADDONTOKODIFUNCTABLE_ADDON__ADDON_LOG_MSG = 30003,
  ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_BOOL = 30004,
  ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_INT = 30005,
  ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_FLOAT = 30006,
  ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_STRING = 30007,
  ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_BOOL = 30008,
  ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_INT = 30009,
  ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_FLOAT = 30010,
  ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_STRING = 30011,
  ADDONTOKODIFUNCTABLE_KODI_NETWORK__WAKE_ON_LAN = 100000,
  ADDONTOKODIFUNCTABLE_KODI_NETWORK__GET_IP_ADDRESS = 100001,
  ADDONTOKODIFUNCTABLE_KODI_NETWORK__DNS_LOOKUP = 100002,
  ADDONTOKODIFUNCTABLE_KODI_NETWORK__URL_ENCODE = 100003,
}AddonToKodiInterfaceCalls;

#include "General.h"
#include "AddonBase.h"
#include "Network.h"

/* Interface: AddonToKodiFuncTable_kodi */
extern char* AddonToKodiFuncTable_kodi__get_addon_info(void* kodiBase, const char* id);
extern bool AddonToKodiFuncTable_kodi__open_settings_dialog(void* kodiBase);
extern char* AddonToKodiFuncTable_kodi__unknown_to_utf8(void* kodiBase, const char* source, bool* ret, bool failOnBadChar);
extern char* AddonToKodiFuncTable_kodi__get_localized_string(void* kodiBase, long dwCode);
extern char* AddonToKodiFuncTable_kodi__get_language(void* kodiBase, int format, bool region);
extern bool AddonToKodiFuncTable_kodi__queue_notification(void* kodiBase, int type, const char* header, const char* message, const char* imageFile, unsigned int displayTime, bool withSound, unsigned int messageTime);
extern void AddonToKodiFuncTable_kodi__get_md5(void* kodiBase, const char* text, char* md5);
extern char* AddonToKodiFuncTable_kodi__get_temp_path(void* kodiBase);
extern char* AddonToKodiFuncTable_kodi__get_region(void* kodiBase, const char* id);
extern void AddonToKodiFuncTable_kodi__get_free_mem(void* kodiBase, long* free, long* total, bool as_bytes);
extern int AddonToKodiFuncTable_kodi__get_global_idle_time(void* kodiBase);
extern void AddonToKodiFuncTable_kodi__kodi_version(void* kodiBase, char** compile_name, int* major, int* minor, char** revision, char** tag, char** tagversion);

/* Interface: AddonToKodiFuncTable_Addon */
extern void AddonToKodiFuncTable_Addon__free_string(void* kodiBase, char* str);
extern char* AddonToKodiFuncTable_Addon__get_addon_path(void* kodiBase);
extern char* AddonToKodiFuncTable_Addon__get_base_user_path(void* kodiBase);
extern void AddonToKodiFuncTable_Addon__addon_log_msg(void* kodiBase, const int loglevel, const char *msg);
extern bool AddonToKodiFuncTable_Addon__get_setting_bool(void* kodiBase, const char* id, bool* value);
extern bool AddonToKodiFuncTable_Addon__get_setting_int(void* kodiBase, const char* id, int* value);
extern bool AddonToKodiFuncTable_Addon__get_setting_float(void* kodiBase, const char* id, float* value);
extern bool AddonToKodiFuncTable_Addon__get_setting_string(void* kodiBase, const char* id, char** value);
extern bool AddonToKodiFuncTable_Addon__set_setting_bool(void* kodiBase, const char* id, bool value);
extern bool AddonToKodiFuncTable_Addon__set_setting_int(void* kodiBase, const char* id, int value);
extern bool AddonToKodiFuncTable_Addon__set_setting_float(void* kodiBase, const char* id, float value);
extern bool AddonToKodiFuncTable_Addon__set_setting_string(void* kodiBase, const char* id, const char* value);

/* Interface: AddonToKodiFuncTable_kodi_network */
extern bool AddonToKodiFuncTable_kodi_network__wake_on_lan(void* kodiBase, const char *mac);
extern char* AddonToKodiFuncTable_kodi_network__get_ip_address(void* kodiBase);
extern char* AddonToKodiFuncTable_kodi_network__dns_lookup(void* kodiBase, const char* url, bool* ret);
extern char* AddonToKodiFuncTable_kodi_network__url_encode(void* kodiBase, const char* url);
