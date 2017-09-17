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

#include "AddonToKodi.h"

#include "InterProcess.h"
#include "RequestPacket.h"
#include "ResponsePacket.h"

#include <iostream>

#define PROCESS_HANDLE_EXCEPTION \
  catch (const std::out_of_range& oor) \
  { \
    fprintf(stderr, "Binary AddOn - %s: Thread out of Range error: %s\n", __FUNCTION__, oor.what()); \
    std::cerr << __FUNCTION__ << " - Thread out of Range error: " << oor.what() << '\n'; \
    exit(1); \
  } \
  catch (uint32_t err) \
  { \
    kodi::Log(ADDON_LOG_ERROR, StringUtils::Format("Binary AddOn - %s: Addon received error after send of log entry to Kodi: %s", \
                    __FUNCTION__, errorTranslator[err].errorName).c_str()); \
  }

/* Interface: AddonToKodiFuncTable_kodi */

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi__get_addon_info(void* kodiBase, const char* id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_ADDON_INFO - 0 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_ADDON_INFO, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_kodi__open_settings_dialog(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__OPEN_SETTINGS_DIALOG - 1 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__OPEN_SETTINGS_DIALOG, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi__unknown_to_utf8(void* kodiBase, const char* source, bool* ret, bool failOnBadChar)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__UNKNOWN_TO_UTF8 - 2 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__UNKNOWN_TO_UTF8, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &source);
    vrp.push(API_BOOL_PTR, &ret);
    vrp.push(API_BOOL, &failOnBadChar);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
    vresp->pop(API_BOOL, &failOnBadChar);
    vresp->pop(API_BOOL_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi__get_localized_string(void* kodiBase, long dwCode)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_LOCALIZED_STRING - 3 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_LOCALIZED_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_LONG, &dwCode);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
    vresp->pop(API_LONG, &dwCode);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi__get_language(void* kodiBase, int format, bool region)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_LANGUAGE - 4 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_LANGUAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_INT, &format);
    vrp.push(API_BOOL, &region);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
    vresp->pop(API_BOOL, &region);
    vresp->pop(API_INT, &format);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_kodi__queue_notification(void* kodiBase, int type, const char* header, const char* message, const char* imageFile, unsigned int displayTime, bool withSound, unsigned int messageTime)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__QUEUE_NOTIFICATION - 5 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__QUEUE_NOTIFICATION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_INT, &type);
    vrp.push(API_CONST_CHAR_PTR, &header);
    vrp.push(API_CONST_CHAR_PTR, &message);
    vrp.push(API_CONST_CHAR_PTR, &imageFile);
    vrp.push(API_UNSIGNED_INT, &displayTime);
    vrp.push(API_BOOL, &withSound);
    vrp.push(API_UNSIGNED_INT, &messageTime);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_UNSIGNED_INT, &messageTime);
    vresp->pop(API_BOOL, &withSound);
    vresp->pop(API_UNSIGNED_INT, &displayTime);
    vresp->pop(API_INT, &type);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
void AddonToKodiFuncTable_kodi__get_md5(void* kodiBase, const char* text, char* md5)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_MD5 - 6 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_MD5, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &text);
    vrp.push(API_CHAR_PTR, &md5);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &md5);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi__get_temp_path(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_TEMP_PATH - 7 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_TEMP_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi__get_region(void* kodiBase, const char* id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_REGION - 8 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_REGION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
void AddonToKodiFuncTable_kodi__get_free_mem(void* kodiBase, long* free, long* total, bool as_bytes)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_FREE_MEM - 9 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_FREE_MEM, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_LONG_PTR, &free);
    vrp.push(API_LONG_PTR, &total);
    vrp.push(API_BOOL, &as_bytes);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &as_bytes);
    vresp->pop(API_LONG_PTR, &total);
    vresp->pop(API_LONG_PTR, &free);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
int AddonToKodiFuncTable_kodi__get_global_idle_time(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_GLOBAL_IDLE_TIME - 10 */
  int retValue = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_GLOBAL_IDLE_TIME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
void AddonToKodiFuncTable_kodi__kodi_version(void* kodiBase, char** compile_name, int* major, int* minor, char** revision, char** tag, char** tagversion)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__KODI_VERSION - 11 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__KODI_VERSION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CHAR_PTR_PTR, &compile_name);
    vrp.push(API_INT_PTR, &major);
    vrp.push(API_INT_PTR, &minor);
    vrp.push(API_CHAR_PTR_PTR, &revision);
    vrp.push(API_CHAR_PTR_PTR, &tag);
    vrp.push(API_CHAR_PTR_PTR, &tagversion);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR_PTR, &tagversion);
    vresp->pop(API_CHAR_PTR_PTR, &tag);
    vresp->pop(API_CHAR_PTR_PTR, &revision);
    vresp->pop(API_INT_PTR, &minor);
    vresp->pop(API_INT_PTR, &major);
    vresp->pop(API_CHAR_PTR_PTR, &compile_name);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_Addon */

/* Warning: Auto generated code, do not change by hand! */
void AddonToKodiFuncTable_Addon__free_string(void* kodiBase, char* str)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__FREE_STRING - 30000 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__FREE_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CHAR_PTR, &str);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &str);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_Addon__get_addon_path(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_ADDON_PATH - 30001 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_ADDON_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_Addon__get_base_user_path(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_BASE_USER_PATH - 30002 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_BASE_USER_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
void AddonToKodiFuncTable_Addon__addon_log_msg(void* kodiBase, const int loglevel, const char *msg)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__ADDON_LOG_MSG - 30003 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__ADDON_LOG_MSG, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_INT, &loglevel);
    vrp.push(API_CONST_CHAR_PTR, &msg);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__get_setting_bool(void* kodiBase, const char* id, bool* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_BOOL - 30004 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_BOOL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_BOOL_PTR, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_BOOL_PTR, &value);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__get_setting_int(void* kodiBase, const char* id, int* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_INT - 30005 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_INT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_INT_PTR, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_INT_PTR, &value);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__get_setting_float(void* kodiBase, const char* id, float* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_FLOAT - 30006 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_FLOAT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_FLOAT_PTR, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_FLOAT_PTR, &value);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__get_setting_string(void* kodiBase, const char* id, char** value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_STRING - 30007 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_CHAR_PTR_PTR, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_CHAR_PTR_PTR, &value);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__set_setting_bool(void* kodiBase, const char* id, bool value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_BOOL - 30008 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_BOOL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_BOOL, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_BOOL, &value);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__set_setting_int(void* kodiBase, const char* id, int value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_INT - 30009 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_INT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_INT, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_INT, &value);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__set_setting_float(void* kodiBase, const char* id, float value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_FLOAT - 30010 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_FLOAT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_FLOAT, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
    vresp->pop(API_FLOAT, &value);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_Addon__set_setting_string(void* kodiBase, const char* id, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_STRING - 30011 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Interface: AddonToKodiFuncTable_kodi_network */

/* Warning: Auto generated code, do not change by hand! */
bool AddonToKodiFuncTable_kodi_network__wake_on_lan(void* kodiBase, const char *mac)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__WAKE_ON_LAN - 100000 */
  bool retValue = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__WAKE_ON_LAN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &mac);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi_network__get_ip_address(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__GET_IP_ADDRESS - 100001 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__GET_IP_ADDRESS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi_network__dns_lookup(void* kodiBase, const char* url, bool* ret)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__DNS_LOOKUP - 100002 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__DNS_LOOKUP, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &url);
    vrp.push(API_BOOL_PTR, &ret);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
    vresp->pop(API_BOOL_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

/* Warning: Auto generated code, do not change by hand! */
char* AddonToKodiFuncTable_kodi_network__url_encode(void* kodiBase, const char* url)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__URL_ENCODE - 100003 */
  char* retValue = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__URL_ENCODE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &url);
    uint32_t retCode;
    P8PLATFORM::CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &retValue);
  }
  PROCESS_HANDLE_EXCEPTION;

  return retValue ? strdup(retValue) : retValue;
}

