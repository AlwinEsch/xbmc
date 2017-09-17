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

/* Interface: AddonToKodiFuncTable_kodi */

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi__get_addon_info(void* kodiBase, const char* id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_ADDON_INFO - 0 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_ADDON_INFO, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi__open_settings_dialog(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__OPEN_SETTINGS_DIALOG - 1 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__OPEN_SETTINGS_DIALOG, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi__unknown_to_utf8(void* kodiBase, const char* source, bool* ret, bool failOnBadChar)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__UNKNOWN_TO_UTF8 - 2 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__UNKNOWN_TO_UTF8, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &source);
    vrp.push(API_BOOL_PTR, &ret);
    vrp.push(API_BOOL, &failOnBadChar);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi__get_localized_string(void* kodiBase, long dwCode)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_LOCALIZED_STRING - 3 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_LOCALIZED_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_LONG, &dwCode);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi__get_language(void* kodiBase, int format, bool region)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_LANGUAGE - 4 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_LANGUAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_INT, &format);
    vrp.push(API_BOOL, &region);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi__queue_notification(void* kodiBase, int type, const char* header, const char* message, const char* imageFile, unsigned int displayTime, bool withSound, unsigned int messageTime)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__QUEUE_NOTIFICATION - 5 */
  bool ret = false;

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
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi__get_md5(void* kodiBase, const char* text, char* md5)
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
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi__get_temp_path(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_TEMP_PATH - 7 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_TEMP_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi__get_region(void* kodiBase, const char* id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_REGION - 8 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_REGION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi__get_free_mem(void* kodiBase, long* free, long* total, bool as_bytes)
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
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi__get_global_idle_time(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI__GET_GLOBAL_IDLE_TIME - 10 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI__GET_GLOBAL_IDLE_TIME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi__kodi_version(void* kodiBase, char** compile_name, int* major, int* minor, char** revision, char** tag, char** tagversion)
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
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_PVR */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TransferEpgEntry(void* kodiInstance, const ADDON_HANDLE handle, const EPG_TAG *epgentry)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRANSFEREPGENTRY - 10000 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRANSFEREPGENTRY, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_ADDON_HANDLE, &handle);
    vrp.push(API_CONST_EPG_TAG_PTR, &epgentry);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TransferChannelEntry(void* kodiInstance, const ADDON_HANDLE handle, const PVR_CHANNEL *chan)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRANSFERCHANNELENTRY - 10001 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRANSFERCHANNELENTRY, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_ADDON_HANDLE, &handle);
    vrp.push(API_CONST_PVR_CHANNEL_PTR, &chan);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TransferTimerEntry(void* kodiInstance, const ADDON_HANDLE handle, const PVR_TIMER *timer)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRANSFERTIMERENTRY - 10002 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRANSFERTIMERENTRY, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_ADDON_HANDLE, &handle);
    vrp.push(API_CONST_PVR_TIMER_PTR, &timer);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TransferRecordingEntry(void* kodiInstance, const ADDON_HANDLE handle, const PVR_RECORDING *recording)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRANSFERRECORDINGENTRY - 10003 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRANSFERRECORDINGENTRY, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_ADDON_HANDLE, &handle);
    vrp.push(API_CONST_PVR_RECORDING_PTR, &recording);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__AddMenuHook(void* kodiInstance, PVR_MENUHOOK *hook)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__ADDMENUHOOK - 10004 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__ADDMENUHOOK, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_PVR_MENUHOOK_PTR, &hook);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__Recording(void* kodiInstance, const char *Name, const char *FileName, bool On)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__RECORDING - 10005 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__RECORDING, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_CHAR_PTR, &Name);
    vrp.push(API_CONST_CHAR_PTR, &FileName);
    vrp.push(API_BOOL, &On);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TriggerChannelUpdate(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRIGGERCHANNELUPDATE - 10006 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRIGGERCHANNELUPDATE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TriggerTimerUpdate(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRIGGERTIMERUPDATE - 10007 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRIGGERTIMERUPDATE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TriggerRecordingUpdate(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRIGGERRECORDINGUPDATE - 10008 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRIGGERRECORDINGUPDATE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TriggerChannelGroupsUpdate(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRIGGERCHANNELGROUPSUPDATE - 10009 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRIGGERCHANNELGROUPSUPDATE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TriggerEpgUpdate(void* kodiInstance, unsigned int iChannelUid)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRIGGEREPGUPDATE - 10010 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRIGGEREPGUPDATE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_UNSIGNED_INT, &iChannelUid);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TransferChannelGroup(void* kodiInstance, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP *group)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRANSFERCHANNELGROUP - 10011 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRANSFERCHANNELGROUP, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_ADDON_HANDLE, &handle);
    vrp.push(API_CONST_PVR_CHANNEL_GROUP_PTR, &group);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__TransferChannelGroupMember(void* kodiInstance, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER *member)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__TRANSFERCHANNELGROUPMEMBER - 10012 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__TRANSFERCHANNELGROUPMEMBER, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_ADDON_HANDLE, &handle);
    vrp.push(API_CONST_PVR_CHANNEL_GROUP_MEMBER_PTR, &member);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__FreeDemuxPacket(void* kodiInstance, DemuxPacket* pPacket)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__FREEDEMUXPACKET - 10013 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__FREEDEMUXPACKET, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_DEMUXPACKET_PTR, &pPacket);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static DemuxPacket* AddonToKodiFuncTable_PVR__AllocateDemuxPacket(void* kodiInstance, int iDataSize)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__ALLOCATEDEMUXPACKET - 10014 */
  DemuxPacket* ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__ALLOCATEDEMUXPACKET, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_INT, &iDataSize);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DEMUXPACKET_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__ConnectionStateChange(void* kodiInstance, const char* strConnectionString, PVR_CONNECTION_STATE newState, const char *strMessage)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__CONNECTIONSTATECHANGE - 10015 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__CONNECTIONSTATECHANGE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_CHAR_PTR, &strConnectionString);
    vrp.push(API_PVR_CONNECTION_STATE, &newState);
    vrp.push(API_CONST_CHAR_PTR, &strMessage);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_PVR__EpgEventStateChange(void* kodiInstance, EPG_TAG* tag, EPG_EVENT_STATE newState)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__EPGEVENTSTATECHANGE - 10016 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__EPGEVENTSTATECHANGE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_EPG_TAG_PTR, &tag);
    vrp.push(API_EPG_EVENT_STATE, &newState);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static xbmc_codec_t AddonToKodiFuncTable_PVR__GetCodecByName(const void* kodiInstance, const char* strCodecName)
{
  /* ID: ADDONTOKODIFUNCTABLE_PVR__GETCODECBYNAME - 10017 */
  xbmc_codec_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PVR__GETCODECBYNAME, session);
    vrp.push(API_CONST_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_CHAR_PTR, &strCodecName);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_XBMC_CODEC_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_Addon */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Addon__free_string(void* kodiBase, char* str)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__FREE_STRING - 30000 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__FREE_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CHAR_PTR, &str);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_Addon__get_addon_path(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_ADDON_PATH - 30001 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_ADDON_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_Addon__get_base_user_path(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_BASE_USER_PATH - 30002 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_BASE_USER_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Addon__addon_log_msg(void* kodiBase, const int loglevel, const char *msg)
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
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__get_setting_bool(void* kodiBase, const char* id, bool* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_BOOL - 30004 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_BOOL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_BOOL_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__get_setting_int(void* kodiBase, const char* id, int* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_INT - 30005 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_INT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_INT_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__get_setting_float(void* kodiBase, const char* id, float* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_FLOAT - 30006 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_FLOAT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_FLOAT_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__get_setting_string(void* kodiBase, const char* id, char** value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_STRING - 30007 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__GET_SETTING_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_CHAR_PTR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__set_setting_bool(void* kodiBase, const char* id, bool value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_BOOL - 30008 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_BOOL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_BOOL, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__set_setting_int(void* kodiBase, const char* id, int value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_INT - 30009 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_INT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_INT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__set_setting_float(void* kodiBase, const char* id, float value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_FLOAT - 30010 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_FLOAT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_FLOAT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Addon__set_setting_string(void* kodiBase, const char* id, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_STRING - 30011 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_ADDON__SET_SETTING_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &id);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_audioengine */

/* Warning: Auto generated code, do not change by hand! */
static AEStreamHandle* AddonToKodiFuncTable_kodi_audioengine__make_stream(void *kodiBase, AudioEngineFormat* format, unsigned int options)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__MAKE_STREAM - 90000 */
  AEStreamHandle* ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__MAKE_STREAM, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_AUDIOENGINEFORMAT_PTR, &format);
    vrp.push(API_UNSIGNED_INT, &options);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_AESTREAMHANDLE_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__free_stream(void *kodiBase, AEStreamHandle *stream)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__FREE_STREAM - 90001 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__FREE_STREAM, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* stream2 = reinterpret_cast<void*>(stream);
    vrp.push(API_VOID_PTR, &stream2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_audioengine__get_current_sink_format(void *kodiBase, AudioEngineFormat* sink_format)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__GET_CURRENT_SINK_FORMAT - 90002 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__GET_CURRENT_SINK_FORMAT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_AUDIOENGINEFORMAT_PTR, &sink_format);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static unsigned int AddonToKodiFuncTable_kodi_audioengine__aestream_get_space(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_SPACE - 90003 */
  unsigned int ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_SPACE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UNSIGNED_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static unsigned int AddonToKodiFuncTable_kodi_audioengine__aestream_add_data(void *kodiBase, AEStreamHandle *handle, uint8_t* const *data, unsigned int offset, unsigned int frames, double pts)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_ADD_DATA - 90004 */
  unsigned int ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_ADD_DATA, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    vrp.push(API_UINT8_T_PTR_CONST_PTR, &data);
    vrp.push(API_UNSIGNED_INT, &offset);
    vrp.push(API_UNSIGNED_INT, &frames);
    vrp.push(API_DOUBLE, &pts);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UNSIGNED_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static double AddonToKodiFuncTable_kodi_audioengine__aestream_get_delay(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_DELAY - 90005 */
  double ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_DELAY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DOUBLE, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_audioengine__aestream_is_buffering(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_IS_BUFFERING - 90006 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_IS_BUFFERING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static double AddonToKodiFuncTable_kodi_audioengine__aestream_get_cache_time(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_CACHE_TIME - 90007 */
  double ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_CACHE_TIME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DOUBLE, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static double AddonToKodiFuncTable_kodi_audioengine__aestream_get_cache_total(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_CACHE_TOTAL - 90008 */
  double ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_CACHE_TOTAL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DOUBLE, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__aestream_pause(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_PAUSE - 90009 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_PAUSE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__aestream_resume(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_RESUME - 90010 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_RESUME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__aestream_drain(void *kodiBase, AEStreamHandle *handle, bool wait)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_DRAIN - 90011 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_DRAIN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    vrp.push(API_BOOL, &wait);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_audioengine__aestream_is_draining(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_IS_DRAINING - 90012 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_IS_DRAINING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_audioengine__aestream_is_drained(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_IS_DRAINED - 90013 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_IS_DRAINED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__aestream_flush(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_FLUSH - 90014 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_FLUSH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_audioengine__aestream_get_volume(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_VOLUME - 90015 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_VOLUME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__aestream_set_volume(void *kodiBase, AEStreamHandle *handle, float volume)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_SET_VOLUME - 90016 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_SET_VOLUME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    vrp.push(API_FLOAT, &volume);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_audioengine__aestream_get_amplification(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_AMPLIFICATION - 90017 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_AMPLIFICATION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__aestream_set_amplification(void *kodiBase, AEStreamHandle *handle, float amplify)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_SET_AMPLIFICATION - 90018 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_SET_AMPLIFICATION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    vrp.push(API_FLOAT, &amplify);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static unsigned int AddonToKodiFuncTable_kodi_audioengine__aestream_get_frame_size(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_FRAME_SIZE - 90019 */
  unsigned int ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_FRAME_SIZE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UNSIGNED_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static unsigned int AddonToKodiFuncTable_kodi_audioengine__aestream_get_channel_count(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_CHANNEL_COUNT - 90020 */
  unsigned int ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_CHANNEL_COUNT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UNSIGNED_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static unsigned int AddonToKodiFuncTable_kodi_audioengine__aestream_get_sample_rate(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_SAMPLE_RATE - 90021 */
  unsigned int ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_SAMPLE_RATE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UNSIGNED_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static AEDataFormat AddonToKodiFuncTable_kodi_audioengine__aestream_get_data_format(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_DATA_FORMAT - 90022 */
  AEDataFormat ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_DATA_FORMAT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_AEDATAFORMAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static double AddonToKodiFuncTable_kodi_audioengine__aestream_get_resample_ratio(void *kodiBase, AEStreamHandle *handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_RESAMPLE_RATIO - 90023 */
  double ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_GET_RESAMPLE_RATIO, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DOUBLE, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_audioengine__aestream_set_resample_ratio(void *kodiBase, AEStreamHandle *handle, double ratio)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_SET_RESAMPLE_RATIO - 90024 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_AUDIOENGINE__AESTREAM_SET_RESAMPLE_RATIO, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    void* handle2 = reinterpret_cast<void*>(handle);
    vrp.push(API_VOID_PTR, &handle2);
    vrp.push(API_DOUBLE, &ratio);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_network */

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_network__wake_on_lan(void* kodiBase, const char *mac)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__WAKE_ON_LAN - 100000 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__WAKE_ON_LAN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &mac);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_network__get_ip_address(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__GET_IP_ADDRESS - 100001 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__GET_IP_ADDRESS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_network__dns_lookup(void* kodiBase, const char* url, bool* ret)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__DNS_LOOKUP - 100002 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__DNS_LOOKUP, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &url);
    vrp.push(API_BOOL_PTR, &ret);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_network__url_encode(void* kodiBase, const char* url)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_NETWORK__URL_ENCODE - 100003 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_NETWORK__URL_ENCODE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &url);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Interface: AddonToKodiFuncTable_kodi_filesystem */

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__can_open_directory(void* kodiBase, const char* url)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CAN_OPEN_DIRECTORY - 110000 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CAN_OPEN_DIRECTORY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &url);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__create_directory(void* kodiBase, const char* path)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CREATE_DIRECTORY - 110001 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CREATE_DIRECTORY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &path);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__remove_directory(void* kodiBase, const char* path)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__REMOVE_DIRECTORY - 110002 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__REMOVE_DIRECTORY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &path);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__directory_exists(void* kodiBase, const char* path)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__DIRECTORY_EXISTS - 110003 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__DIRECTORY_EXISTS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &path);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__get_directory(void* kodiBase, const char* path, const char* mask, VFSDirEntry** items, unsigned int* num_items)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_DIRECTORY - 110004 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_DIRECTORY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &path);
    vrp.push(API_CONST_CHAR_PTR, &mask);
    vrp.push(API_VFSDIRENTRY_PTR_PTR, &items);
    vrp.push(API_UNSIGNED_INT_PTR, &num_items);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_filesystem__free_directory(void* kodiBase, VFSDirEntry* items, unsigned int num_items)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__FREE_DIRECTORY - 110005 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__FREE_DIRECTORY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VFSDIRENTRY_PTR, &items);
    vrp.push(API_UNSIGNED_INT, &num_items);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__file_exists(void* kodiBase, const char *filename, bool useCache)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__FILE_EXISTS - 110006 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__FILE_EXISTS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    vrp.push(API_BOOL, &useCache);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_filesystem__stat_file(void* kodiBase, const char *filename, struct __stat64* buffer)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__STAT_FILE - 110007 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__STAT_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    vrp.push(API_STRUCT___STAT64_PTR, &buffer);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__delete_file(void* kodiBase, const char *filename)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__DELETE_FILE - 110008 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__DELETE_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__rename_file(void* kodiBase, const char *filename, const char *newFileName)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__RENAME_FILE - 110009 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__RENAME_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    vrp.push(API_CONST_CHAR_PTR, &newFileName);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__copy_file(void* kodiBase, const char *filename, const char *dest)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__COPY_FILE - 110010 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__COPY_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    vrp.push(API_CONST_CHAR_PTR, &dest);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_filesystem__get_file_md5(void* kodiBase, const char* filename)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_MD5 - 110011 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_MD5, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_filesystem__get_cache_thumb_name(void* kodiBase, const char* filename)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_CACHE_THUMB_NAME - 110012 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_CACHE_THUMB_NAME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_filesystem__make_legal_filename(void* kodiBase, const char* filename)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__MAKE_LEGAL_FILENAME - 110013 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__MAKE_LEGAL_FILENAME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_filesystem__make_legal_path(void* kodiBase, const char* path)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__MAKE_LEGAL_PATH - 110014 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__MAKE_LEGAL_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &path);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_filesystem__translate_special_protocol(void* kodiBase, const char *strSource)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__TRANSLATE_SPECIAL_PROTOCOL - 110015 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__TRANSLATE_SPECIAL_PROTOCOL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &strSource);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_filesystem__open_file(void* kodiBase, const char* filename, unsigned int flags)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__OPEN_FILE - 110016 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__OPEN_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    vrp.push(API_UNSIGNED_INT, &flags);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_filesystem__open_file_for_write(void* kodiBase, const char* filename, bool overwrite)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__OPEN_FILE_FOR_WRITE - 110017 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__OPEN_FILE_FOR_WRITE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    vrp.push(API_BOOL, &overwrite);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static ssize_t AddonToKodiFuncTable_kodi_filesystem__read_file(void* kodiBase, void* file, void* ptr, size_t size)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__READ_FILE - 110018 */
  ssize_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__READ_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_VOID_PTR, &ptr);
    vrp.push(API_SIZE_T, &size);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_SSIZE_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__read_file_string(void* kodiBase, void* file, char *szLine, int iLineLength)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__READ_FILE_STRING - 110019 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__READ_FILE_STRING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_CHAR_PTR, &szLine);
    vrp.push(API_INT, &iLineLength);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static ssize_t AddonToKodiFuncTable_kodi_filesystem__write_file(void* kodiBase, void* file, const void* ptr, size_t size)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__WRITE_FILE - 110020 */
  ssize_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__WRITE_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_CONST_VOID_PTR, &ptr);
    vrp.push(API_SIZE_T, &size);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_SSIZE_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_filesystem__flush_file(void* kodiBase, void* file)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__FLUSH_FILE - 110021 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__FLUSH_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int64_t AddonToKodiFuncTable_kodi_filesystem__seek_file(void* kodiBase, void* file, int64_t position, int whence)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__SEEK_FILE - 110022 */
  int64_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__SEEK_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_INT64_T, &position);
    vrp.push(API_INT, &whence);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT64_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_filesystem__truncate_file(void* kodiBase, void* file, int64_t size)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__TRUNCATE_FILE - 110023 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__TRUNCATE_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_INT64_T, &size);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int64_t AddonToKodiFuncTable_kodi_filesystem__get_file_position(void* kodiBase, void* file)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_POSITION - 110024 */
  int64_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_POSITION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT64_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int64_t AddonToKodiFuncTable_kodi_filesystem__get_file_length(void* kodiBase, void* file)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_LENGTH - 110025 */
  int64_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_LENGTH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT64_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static double AddonToKodiFuncTable_kodi_filesystem__get_file_download_speed(void* kodiBase, void* file)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_DOWNLOAD_SPEED - 110026 */
  double ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_DOWNLOAD_SPEED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DOUBLE, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_filesystem__close_file(void* kodiBase, void* file)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CLOSE_FILE - 110027 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CLOSE_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_filesystem__get_file_chunk_size(void* kodiBase, void* file)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_CHUNK_SIZE - 110028 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_FILE_CHUNK_SIZE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_filesystem__get_property(void* kodiBase, void* file, int type, const char *name)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_PROPERTY - 110029 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__GET_PROPERTY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_INT, &type);
    vrp.push(API_CONST_CHAR_PTR, &name);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_filesystem__curl_create(void* kodiBase, const char* url)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CURL_CREATE - 110030 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CURL_CREATE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &url);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__curl_add_option(void* kodiBase, void* file, int type, const char* name, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CURL_ADD_OPTION - 110031 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CURL_ADD_OPTION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_INT, &type);
    vrp.push(API_CONST_CHAR_PTR, &name);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_filesystem__curl_open(void* kodiBase, void* file, unsigned int flags)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CURL_OPEN - 110032 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_FILESYSTEM__CURL_OPEN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &file);
    vrp.push(API_UNSIGNED_INT, &flags);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_Game */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Game__CloseGame(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__CLOSEGAME - 130000 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__CLOSEGAME, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_Game__OpenPixelStream(void* kodiInstance, GAME_PIXEL_FORMAT format, unsigned int width, unsigned int height, GAME_VIDEO_ROTATION rotation)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__OPENPIXELSTREAM - 130001 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__OPENPIXELSTREAM, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_GAME_PIXEL_FORMAT, &format);
    vrp.push(API_UNSIGNED_INT, &width);
    vrp.push(API_UNSIGNED_INT, &height);
    vrp.push(API_GAME_VIDEO_ROTATION, &rotation);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_Game__OpenVideoStream(void* kodiInstance, GAME_VIDEO_CODEC codec)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__OPENVIDEOSTREAM - 130002 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__OPENVIDEOSTREAM, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_GAME_VIDEO_CODEC, &codec);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_Game__OpenPCMStream(void* kodiInstance, GAME_PCM_FORMAT format, const GAME_AUDIO_CHANNEL* channel_map)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__OPENPCMSTREAM - 130003 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__OPENPCMSTREAM, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_GAME_PCM_FORMAT, &format);
    vrp.push(API_CONST_GAME_AUDIO_CHANNEL_PTR, &channel_map);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_Game__OpenAudioStream(void* kodiInstance, GAME_AUDIO_CODEC codec, const GAME_AUDIO_CHANNEL* channel_map)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__OPENAUDIOSTREAM - 130004 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__OPENAUDIOSTREAM, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_GAME_AUDIO_CODEC, &codec);
    vrp.push(API_CONST_GAME_AUDIO_CHANNEL_PTR, &channel_map);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Game__AddStreamData(void* kodiInstance, GAME_STREAM_TYPE stream, const uint8_t* data, unsigned int size)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__ADDSTREAMDATA - 130005 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__ADDSTREAMDATA, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_GAME_STREAM_TYPE, &stream);
    vrp.push(API_CONST_UINT8_T_PTR, &data);
    vrp.push(API_UNSIGNED_INT, &size);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Game__CloseStream(void* kodiInstance, GAME_STREAM_TYPE stream)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__CLOSESTREAM - 130006 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__CLOSESTREAM, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_GAME_STREAM_TYPE, &stream);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Game__EnableHardwareRendering(void* kodiInstance, const game_hw_info* hw_info)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__ENABLEHARDWARERENDERING - 130007 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__ENABLEHARDWARERENDERING, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_GAME_HW_INFO_PTR, &hw_info);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static uintptr_t AddonToKodiFuncTable_Game__HwGetCurrentFramebuffer(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__HWGETCURRENTFRAMEBUFFER - 130008 */
  uintptr_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__HWGETCURRENTFRAMEBUFFER, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UINTPTR_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static game_proc_address_t AddonToKodiFuncTable_Game__HwGetProcAddress(void* kodiInstance, const char* symbol)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__HWGETPROCADDRESS - 130009 */
  game_proc_address_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__HWGETPROCADDRESS, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_CHAR_PTR, &symbol);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_GAME_PROC_ADDRESS_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Game__RenderFrame(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__RENDERFRAME - 130010 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__RENDERFRAME, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Game__OpenPort(void* kodiInstance, unsigned int port)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__OPENPORT - 130011 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__OPENPORT, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_UNSIGNED_INT, &port);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Game__ClosePort(void* kodiInstance, unsigned int port)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__CLOSEPORT - 130012 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__CLOSEPORT, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_UNSIGNED_INT, &port);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_Game__InputEvent(void* kodiInstance, const game_input_event* event)
{
  /* ID: ADDONTOKODIFUNCTABLE_GAME__INPUTEVENT - 130013 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_GAME__INPUTEVENT, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_GAME_INPUT_EVENT_PTR, &event);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_VFSEntry */

/* Interface: AddonToKodiFuncTable_VideoCodec */

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_VideoCodec__get_frame_buffer(void* kodiInstance, VIDEOCODEC_PICTURE *picture)
{
  /* ID: ADDONTOKODIFUNCTABLE_VIDEOCODEC__GET_FRAME_BUFFER - 210000 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_VIDEOCODEC__GET_FRAME_BUFFER, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_VIDEOCODEC_PICTURE_PTR, &picture);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_VideoCodec__release_frame_buffer(void* kodiInstance, void *buffer)
{
  /* ID: ADDONTOKODIFUNCTABLE_VIDEOCODEC__RELEASE_FRAME_BUFFER - 210001 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_VIDEOCODEC__RELEASE_FRAME_BUFFER, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_VOID_PTR, &buffer);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_Visualization */

/* Interface: AddonToKodiFuncTable_InputStream */

/* Warning: Auto generated code, do not change by hand! */
static DemuxPacket* AddonToKodiFuncTable_InputStream__allocate_demux_packet(void* kodiInstance, int data_size)
{
  /* ID: ADDONTOKODIFUNCTABLE_INPUTSTREAM__ALLOCATE_DEMUX_PACKET - 230000 */
  DemuxPacket* ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_INPUTSTREAM__ALLOCATE_DEMUX_PACKET, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_INT, &data_size);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DEMUXPACKET_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static DemuxPacket* AddonToKodiFuncTable_InputStream__allocate_encrypted_demux_packet(void* kodiInstance, unsigned int data_size, unsigned int encrypted_subsample_count)
{
  /* ID: ADDONTOKODIFUNCTABLE_INPUTSTREAM__ALLOCATE_ENCRYPTED_DEMUX_PACKET - 230001 */
  DemuxPacket* ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_INPUTSTREAM__ALLOCATE_ENCRYPTED_DEMUX_PACKET, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_UNSIGNED_INT, &data_size);
    vrp.push(API_UNSIGNED_INT, &encrypted_subsample_count);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DEMUXPACKET_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_InputStream__free_demux_packet(void* kodiInstance, DemuxPacket* packet)
{
  /* ID: ADDONTOKODIFUNCTABLE_INPUTSTREAM__FREE_DEMUX_PACKET - 230002 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_INPUTSTREAM__FREE_DEMUX_PACKET, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_DEMUXPACKET_PTR, &packet);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_Peripheral */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Peripheral__trigger_scan(void* kodiInstance)
{
  /* ID: ADDONTOKODIFUNCTABLE_PERIPHERAL__TRIGGER_SCAN - 240000 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PERIPHERAL__TRIGGER_SCAN, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_Peripheral__refresh_button_maps(void* kodiInstance, const char* device_name, const char* controller_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_PERIPHERAL__REFRESH_BUTTON_MAPS - 240001 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PERIPHERAL__REFRESH_BUTTON_MAPS, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_CHAR_PTR, &device_name);
    vrp.push(API_CONST_CHAR_PTR, &controller_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static unsigned int AddonToKodiFuncTable_Peripheral__feature_count(void* kodiInstance, const char* controller_id, JOYSTICK_FEATURE_TYPE type)
{
  /* ID: ADDONTOKODIFUNCTABLE_PERIPHERAL__FEATURE_COUNT - 240002 */
  unsigned int ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PERIPHERAL__FEATURE_COUNT, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_CHAR_PTR, &controller_id);
    vrp.push(API_JOYSTICK_FEATURE_TYPE, &type);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UNSIGNED_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static JOYSTICK_FEATURE_TYPE AddonToKodiFuncTable_Peripheral__feature_type(void* kodiInstance, const char* controller_id, const char* feature_name)
{
  /* ID: ADDONTOKODIFUNCTABLE_PERIPHERAL__FEATURE_TYPE - 240003 */
  JOYSTICK_FEATURE_TYPE ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_PERIPHERAL__FEATURE_TYPE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_CHAR_PTR, &controller_id);
    vrp.push(API_CONST_CHAR_PTR, &feature_name);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_JOYSTICK_FEATURE_TYPE, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_VFSEntry */

/* Interface: AddonToKodiFuncTable_Screensaver */

/* Interface: AddonToKodiFuncTable_AudioDSP */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_AudioDSP__add_menu_hook(void* kodiInstance, AE_DSP_MENUHOOK *hook)
{
  /* ID: ADDONTOKODIFUNCTABLE_AUDIODSP__ADD_MENU_HOOK - 280000 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_AUDIODSP__ADD_MENU_HOOK, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_AE_DSP_MENUHOOK_PTR, &hook);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_AudioDSP__remove_menu_hook(void* kodiInstance, AE_DSP_MENUHOOK *hook)
{
  /* ID: ADDONTOKODIFUNCTABLE_AUDIODSP__REMOVE_MENU_HOOK - 280001 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_AUDIODSP__REMOVE_MENU_HOOK, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_AE_DSP_MENUHOOK_PTR, &hook);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_AudioDSP__register_mode(void* kodiInstance, AE_DSP_MODES::AE_DSP_MODE *mode)
{
  /* ID: ADDONTOKODIFUNCTABLE_AUDIODSP__REGISTER_MODE - 280002 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_AUDIODSP__REGISTER_MODE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_AE_DSP_MODES::AE_DSP_MODE_PTR, &mode);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_AudioDSP__unregister_mode(void* kodiInstance, AE_DSP_MODES::AE_DSP_MODE *mode)
{
  /* ID: ADDONTOKODIFUNCTABLE_AUDIODSP__UNREGISTER_MODE - 280003 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_AUDIODSP__UNREGISTER_MODE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_AE_DSP_MODES::AE_DSP_MODE_PTR, &mode);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_AudioEncoder */

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_AudioEncoder__write(void* kodiInstance, const uint8_t* data, int len)
{
  /* ID: ADDONTOKODIFUNCTABLE_AUDIOENCODER__WRITE - 290000 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_AUDIOENCODER__WRITE, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_CONST_UINT8_T_PTR, &data);
    vrp.push(API_INT, &len);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int64_t AddonToKodiFuncTable_AudioEncoder__seek(void* kodiInstance, int64_t pos, int whence)
{
  /* ID: ADDONTOKODIFUNCTABLE_AUDIOENCODER__SEEK - 290001 */
  int64_t ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_AUDIOENCODER__SEEK, session);
    vrp.push(API_VOID_PTR, &kodiInstance);
    vrp.push(API_INT64_T, &pos);
    vrp.push(API_INT, &whence);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT64_T, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_AudioDecoder */

/* Interface: AddonToKodiFuncTable_ImageDecoder */

/* Interface: AddonToKodiFuncTable_kodi_gui_general */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_general__lock()
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__LOCK - 340000 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__LOCK, session);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_general__unlock()
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__UNLOCK - 340001 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__UNLOCK, session);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_general__get_screen_height(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_SCREEN_HEIGHT - 340002 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_SCREEN_HEIGHT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_general__get_screen_width(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_SCREEN_WIDTH - 340003 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_SCREEN_WIDTH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_general__get_video_resolution(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_VIDEO_RESOLUTION - 340004 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_VIDEO_RESOLUTION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_general__get_current_window_dialog_id(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_CURRENT_WINDOW_DIALOG_ID - 340005 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_CURRENT_WINDOW_DIALOG_ID, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_general__get_current_window_id(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_CURRENT_WINDOW_ID - 340006 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_GENERAL__GET_CURRENT_WINDOW_ID, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_button */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_button__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_VISIBLE - 340207 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_button__set_enabled(void* kodiBase, void* handle, bool enabled)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_ENABLED - 340208 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_ENABLED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &enabled);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_button__set_label(void* kodiBase, void* handle, const char* label)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_LABEL - 340209 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_button__get_label(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__GET_LABEL - 340210 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__GET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_button__set_label2(void* kodiBase, void* handle, const char *label)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_LABEL2 - 340211 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__SET_LABEL2, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_button__get_label2(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__GET_LABEL2 - 340212 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_BUTTON__GET_LABEL2, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_edit */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_edit__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_VISIBLE - 340413 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_edit__set_enabled(void* kodiBase, void* handle, bool enabled)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_ENABLED - 340414 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_ENABLED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &enabled);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_edit__set_label(void* kodiBase, void* handle, const char* label)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_LABEL - 340415 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_edit__get_label(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__GET_LABEL - 340416 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__GET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_edit__set_text(void* kodiBase, void* handle, const char* text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_TEXT - 340417 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_edit__get_text(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__GET_TEXT - 340418 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__GET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_edit__set_cursor_position(void* kodiBase, void* handle, unsigned int position)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_CURSOR_POSITION - 340419 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_CURSOR_POSITION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_UNSIGNED_INT, &position);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static unsigned int AddonToKodiFuncTable_kodi_gui_control_edit__get_cursor_position(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__GET_CURSOR_POSITION - 340420 */
  unsigned int ret;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__GET_CURSOR_POSITION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_UNSIGNED_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_edit__set_input_type(void* kodiBase, void* handle, int type, const char* heading)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_INPUT_TYPE - 340421 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_EDIT__SET_INPUT_TYPE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &type);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_fade_label */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_fade_label__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__SET_VISIBLE - 340622 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_fade_label__add_label(void* kodiBase, void* handle, const char* text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__ADD_LABEL - 340623 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__ADD_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_fade_label__get_label(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__GET_LABEL - 340624 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__GET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_fade_label__set_scrolling(void* kodiBase, void* handle, bool scroll)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__SET_SCROLLING - 340625 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__SET_SCROLLING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &scroll);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_fade_label__reset(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__RESET - 340626 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_FADE_LABEL__RESET, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_image */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_image__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_IMAGE__SET_VISIBLE - 340827 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_IMAGE__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_image__set_filename(void* kodiBase, void* handle, const char* filename, bool use_cache)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_IMAGE__SET_FILENAME - 340828 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_IMAGE__SET_FILENAME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &filename);
    vrp.push(API_BOOL, &use_cache);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_image__set_color_diffuse(void* kodiBase, void* handle, uint32_t color_diffuse)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_IMAGE__SET_COLOR_DIFFUSE - 340829 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_IMAGE__SET_COLOR_DIFFUSE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_UINT32_T, &color_diffuse);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_label */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_label__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_LABEL__SET_VISIBLE - 341030 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_LABEL__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_label__set_label(void* kodiBase, void* handle, const char* text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_LABEL__SET_LABEL - 341031 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_LABEL__SET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_label__get_label(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_LABEL__GET_LABEL - 341032 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_LABEL__GET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_progress */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_progress__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_PROGRESS__SET_VISIBLE - 341233 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_PROGRESS__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_progress__set_percentage(void* kodiBase, void* handle, float percent)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_PROGRESS__SET_PERCENTAGE - 341234 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_PROGRESS__SET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &percent);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_gui_control_progress__get_percentage(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_PROGRESS__GET_PERCENTAGE - 341235 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_PROGRESS__GET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_radio_button */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_radio_button__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_VISIBLE - 341436 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_radio_button__set_enabled(void* kodiBase, void* handle, bool enabled)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_ENABLED - 341437 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_ENABLED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &enabled);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_radio_button__set_label(void* kodiBase, void* handle, const char* text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_LABEL - 341438 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_radio_button__get_label(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__GET_LABEL - 341439 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__GET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_radio_button__set_selected(void* kodiBase, void* handle, bool selected)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_SELECTED - 341440 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__SET_SELECTED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &selected);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_control_radio_button__is_selected(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__IS_SELECTED - 341441 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RADIO_BUTTON__IS_SELECTED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_rendering */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_rendering__set_callbacks(void* kodiBase, void* handle, void* clienthandle, bool (*createCB)(void*,int,int,int,int,void*), void (*renderCB)(void*), void (*stopCB)(void*), bool (*dirtyCB)(void*))
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RENDERING__SET_CALLBACKS - 341642 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RENDERING__SET_CALLBACKS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_VOID_PTR, &clienthandle);
    vrp.push(API_BOOL, &(*createCB)(void*,int,int,int,int,void*));
    vrp.push(API_VOID, &(*renderCB)(void*));
    vrp.push(API_VOID, &(*stopCB)(void*));
    vrp.push(API_BOOL, &(*dirtyCB)(void*));
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_rendering__destroy(void *kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RENDERING__DESTROY - 341643 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_RENDERING__DESTROY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_settings_slider */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_VISIBLE - 341844 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_enabled(void* kodiBase, void* handle, bool enabled)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_ENABLED - 341845 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_ENABLED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &enabled);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_text(void* kodiBase, void* handle, const char* label)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_TEXT - 341846 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__reset(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__RESET - 341847 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__RESET, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_int_range(void* kodiBase, void* handle, int start, int end)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_INT_RANGE - 341848 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_INT_RANGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &start);
    vrp.push(API_INT, &end);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_int_value(void* kodiBase, void* handle, int value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_INT_VALUE - 341849 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_INT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_control_settings_slider__get_int_value(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__GET_INT_VALUE - 341850 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__GET_INT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_int_interval(void* kodiBase, void* handle, int interval)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_INT_INTERVAL - 341851 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_INT_INTERVAL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &interval);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_percentage(void* kodiBase, void* handle, float percent)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_PERCENTAGE - 341852 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &percent);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_gui_control_settings_slider__get_percentage(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__GET_PERCENTAGE - 341853 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__GET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_float_range(void* kodiBase, void* handle, float start, float end)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_FLOAT_RANGE - 341854 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_FLOAT_RANGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &start);
    vrp.push(API_FLOAT, &end);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_float_value(void* kodiBase, void* handle, float value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_FLOAT_VALUE - 341855 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_FLOAT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_gui_control_settings_slider__get_float_value(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__GET_FLOAT_VALUE - 341856 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__GET_FLOAT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_settings_slider__set_float_interval(void* kodiBase, void* handle, float interval)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_FLOAT_INTERVAL - 341857 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SETTINGS_SLIDER__SET_FLOAT_INTERVAL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &interval);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_slider */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_VISIBLE - 342058 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_enabled(void* kodiBase, void* handle, bool enabled)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_ENABLED - 342059 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_ENABLED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &enabled);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__reset(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__RESET - 342060 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__RESET, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_slider__get_description(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_DESCRIPTION - 342061 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_DESCRIPTION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_int_range(void* kodiBase, void* handle, int start, int end)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_INT_RANGE - 342062 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_INT_RANGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &start);
    vrp.push(API_INT, &end);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_int_value(void* kodiBase, void* handle, int value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_INT_VALUE - 342063 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_INT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_control_slider__get_int_value(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_INT_VALUE - 342064 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_INT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_int_interval(void* kodiBase, void* handle, int interval)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_INT_INTERVAL - 342065 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_INT_INTERVAL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &interval);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_percentage(void* kodiBase, void* handle, float percent)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_PERCENTAGE - 342066 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &percent);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_gui_control_slider__get_percentage(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_PERCENTAGE - 342067 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_float_range(void* kodiBase, void* handle, float start, float end)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_FLOAT_RANGE - 342068 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_FLOAT_RANGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &start);
    vrp.push(API_FLOAT, &end);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_float_value(void* kodiBase, void* handle, float value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_FLOAT_VALUE - 342069 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_FLOAT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_gui_control_slider__get_float_value(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_FLOAT_VALUE - 342070 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__GET_FLOAT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_slider__set_float_interval(void* kodiBase, void* handle, float interval)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_FLOAT_INTERVAL - 342071 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SLIDER__SET_FLOAT_INTERVAL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &interval);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_spin */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_VISIBLE - 342272 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_enabled(void* kodiBase, void* handle, bool enabled)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_ENABLED - 342273 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_ENABLED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &enabled);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_text(void* kodiBase, void* handle, const char* text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_TEXT - 342274 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__reset(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__RESET - 342275 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__RESET, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_type(void* kodiBase, void* handle, int type)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_TYPE - 342276 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_TYPE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &type);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__add_string_label(void* kodiBase, void* handle, const char* label, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__ADD_STRING_LABEL - 342277 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__ADD_STRING_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_string_value(void* kodiBase, void* handle, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_STRING_VALUE - 342278 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_STRING_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_spin__get_string_value(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__GET_STRING_VALUE - 342279 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__GET_STRING_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__add_int_label(void* kodiBase, void* handle, const char* label, int value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__ADD_INT_LABEL - 342280 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__ADD_INT_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    vrp.push(API_INT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_int_range(void* kodiBase, void* handle, int start, int end)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_INT_RANGE - 342281 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_INT_RANGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &start);
    vrp.push(API_INT, &end);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_int_value(void* kodiBase, void* handle, int value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_INT_VALUE - 342282 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_INT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_control_spin__get_int_value(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__GET_INT_VALUE - 342283 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__GET_INT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_float_range(void* kodiBase, void* handle, float start, float end)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_FLOAT_RANGE - 342284 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_FLOAT_RANGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &start);
    vrp.push(API_FLOAT, &end);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_float_value(void* kodiBase, void* handle, float value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_FLOAT_VALUE - 342285 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_FLOAT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_gui_control_spin__get_float_value(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__GET_FLOAT_VALUE - 342286 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__GET_FLOAT_VALUE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_spin__set_float_interval(void* kodiBase, void* handle, float interval)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_FLOAT_INTERVAL - 342287 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_SPIN__SET_FLOAT_INTERVAL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &interval);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_control_text_box */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_text_box__set_visible(void* kodiBase, void* handle, bool visible)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SET_VISIBLE - 342488 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SET_VISIBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &visible);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_text_box__reset(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__RESET - 342489 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__RESET, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_text_box__set_text(void* kodiBase, void* handle, const char* text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SET_TEXT - 342490 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_control_text_box__get_text(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__GET_TEXT - 342491 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__GET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_text_box__scroll(void* kodiBase, void* handle, unsigned int scroll)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SCROLL - 342492 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SCROLL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_UNSIGNED_INT, &scroll);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_control_text_box__set_auto_scrolling(void* kodiBase, void* handle, int delay, int time, int repeat)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SET_AUTO_SCROLLING - 342493 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_CONTROL_TEXT_BOX__SET_AUTO_SCROLLING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &delay);
    vrp.push(API_INT, &time);
    vrp.push(API_INT, &repeat);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogContextMenu */

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_dialogContextMenu__open(void* kodiBase, const char *heading, const char *entries[], unsigned int size)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGCONTEXTMENU__OPEN - 342694 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGCONTEXTMENU__OPEN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &entries[]);
    vrp.push(API_UNSIGNED_INT, &size);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress */

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__new_dialog(void* kodiBase, const char *title)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__NEW_DIALOG - 342895 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__NEW_DIALOG, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &title);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__delete_dialog(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__DELETE_DIALOG - 342896 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__DELETE_DIALOG, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__get_title(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__GET_TITLE - 342897 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__GET_TITLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__set_title(void* kodiBase, void* handle, const char *title)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_TITLE - 342898 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_TITLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &title);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__get_text(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__GET_TEXT - 342899 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__GET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__set_text(void* kodiBase, void* handle, const char *text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_TEXT - 342900 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__is_finished(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__IS_FINISHED - 342901 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__IS_FINISHED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__mark_finished(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__MARK_FINISHED - 342902 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__MARK_FINISHED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static float AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__get_percentage(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__GET_PERCENTAGE - 342903 */
  float ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__GET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_FLOAT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__set_percentage(void* kodiBase, void* handle, float percentage)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_PERCENTAGE - 342904 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_FLOAT, &percentage);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress__set_progress(void* kodiBase, void* handle, int currentItem, int itemCount)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_PROGRESS - 342905 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGEXTENDEDPROGRESS__SET_PROGRESS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &currentItem);
    vrp.push(API_INT, &itemCount);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogFileBrowser */

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__show_and_get_directory(void* kodiBase, const char* shares, const char* heading, const char* path_in, char** path_out, bool writeOnly)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_DIRECTORY - 343106 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_DIRECTORY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &shares);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &path_in);
    vrp.push(API_CHAR_PTR_PTR, &path_out);
    vrp.push(API_BOOL, &writeOnly);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__show_and_get_file(void* kodiBase, const char* shares, const char* mask, const char* heading, const char* path_in, char** path_out, bool use_thumbs, bool use_file_directories)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_FILE - 343107 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_FILE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &shares);
    vrp.push(API_CONST_CHAR_PTR, &mask);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &path_in);
    vrp.push(API_CHAR_PTR_PTR, &path_out);
    vrp.push(API_BOOL, &use_thumbs);
    vrp.push(API_BOOL, &use_file_directories);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__show_and_get_file_from_dir(void* kodiBase, const char* directory, const char* mask, const char* heading, const char* path_in, char** path_out, bool use_thumbs, bool use_file_directories, bool singleList)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_FILE_FROM_DIR - 343108 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_FILE_FROM_DIR, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &directory);
    vrp.push(API_CONST_CHAR_PTR, &mask);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &path_in);
    vrp.push(API_CHAR_PTR_PTR, &path_out);
    vrp.push(API_BOOL, &use_thumbs);
    vrp.push(API_BOOL, &use_file_directories);
    vrp.push(API_BOOL, &singleList);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__show_and_get_file_list(void* kodiBase, const char* shares, const char* mask, const char* heading, char*** file_list, unsigned int* entries, bool use_thumbs, bool use_file_directories)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_FILE_LIST - 343109 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_FILE_LIST, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &shares);
    vrp.push(API_CONST_CHAR_PTR, &mask);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CHAR_PTR_PTR_PTR, &file_list);
    vrp.push(API_UNSIGNED_INT_PTR, &entries);
    vrp.push(API_BOOL, &use_thumbs);
    vrp.push(API_BOOL, &use_file_directories);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__show_and_get_source(void* kodiBase, const char* path_in, char** path_out, bool allow_network_shares, const char* additional_share, const char* type)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_SOURCE - 343110 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_SOURCE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &path_in);
    vrp.push(API_CHAR_PTR_PTR, &path_out);
    vrp.push(API_BOOL, &allow_network_shares);
    vrp.push(API_CONST_CHAR_PTR, &additional_share);
    vrp.push(API_CONST_CHAR_PTR, &type);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__show_and_get_image(void* kodiBase, const char* shares, const char* heading, const char* path_in, char** path_out)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_IMAGE - 343111 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_IMAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &shares);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &path_in);
    vrp.push(API_CHAR_PTR_PTR, &path_out);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__show_and_get_image_list(void* kodiBase, const char* shares, const char* heading, char*** file_list, unsigned int* entries)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_IMAGE_LIST - 343112 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__SHOW_AND_GET_IMAGE_LIST, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &shares);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CHAR_PTR_PTR_PTR, &file_list);
    vrp.push(API_UNSIGNED_INT_PTR, &entries);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogFileBrowser__clear_file_list(void* kodiBase, char*** file_list, unsigned int entries)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__CLEAR_FILE_LIST - 343113 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGFILEBROWSER__CLEAR_FILE_LIST, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CHAR_PTR_PTR_PTR, &file_list);
    vrp.push(API_UNSIGNED_INT, &entries);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogKeyboard */

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_get_input_with_head(void* kodiBase, const char* text_in, char** text_out, const char* heading, bool allow_empty_result, bool hiddenInput, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_INPUT_WITH_HEAD - 343314 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_INPUT_WITH_HEAD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &text_in);
    vrp.push(API_CHAR_PTR_PTR, &text_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_BOOL, &allow_empty_result);
    vrp.push(API_BOOL, &hiddenInput);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_get_input(void* kodiBase, const char* text_in, char** text_out, bool allow_empty_result, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_INPUT - 343315 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_INPUT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &text_in);
    vrp.push(API_CHAR_PTR_PTR, &text_out);
    vrp.push(API_BOOL, &allow_empty_result);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_get_new_password_with_head(void* kodiBase, const char* password_in, char** password_out, const char* heading, bool allow_empty_result, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_NEW_PASSWORD_WITH_HEAD - 343316 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_NEW_PASSWORD_WITH_HEAD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &password_in);
    vrp.push(API_CHAR_PTR_PTR, &password_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_BOOL, &allow_empty_result);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_get_new_password(void* kodiBase, const char* password_in, char** password_out, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_NEW_PASSWORD - 343317 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_NEW_PASSWORD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &password_in);
    vrp.push(API_CHAR_PTR_PTR, &password_out);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_verify_new_password_with_head(void* kodiBase, char** password_out, const char* heading, bool allow_empty_result, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_VERIFY_NEW_PASSWORD_WITH_HEAD - 343318 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_VERIFY_NEW_PASSWORD_WITH_HEAD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CHAR_PTR_PTR, &password_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_BOOL, &allow_empty_result);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_verify_new_password(void* kodiBase, char** password_out, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_VERIFY_NEW_PASSWORD - 343319 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_VERIFY_NEW_PASSWORD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CHAR_PTR_PTR, &password_out);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_verify_password(void* kodiBase, const char* password_in, char** password_out, const char* heading, int retries, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_VERIFY_PASSWORD - 343320 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_VERIFY_PASSWORD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &password_in);
    vrp.push(API_CHAR_PTR_PTR, &password_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_INT, &retries);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__show_and_get_filter(void* kodiBase, const char* text_in, char** text_out, bool searching, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_FILTER - 343321 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SHOW_AND_GET_FILTER, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &text_in);
    vrp.push(API_CHAR_PTR_PTR, &text_out);
    vrp.push(API_BOOL, &searching);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__send_text_to_active_keyboard(void* kodiBase, const char* text, bool close_keyboard)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SEND_TEXT_TO_ACTIVE_KEYBOARD - 343322 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__SEND_TEXT_TO_ACTIVE_KEYBOARD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &text);
    vrp.push(API_BOOL, &close_keyboard);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogKeyboard__is_keyboard_activated(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__IS_KEYBOARD_ACTIVATED - 343323 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGKEYBOARD__IS_KEYBOARD_ACTIVATED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogNumeric */

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_verify_new_password(void* kodiBase, char** password)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_VERIFY_NEW_PASSWORD - 343524 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_VERIFY_NEW_PASSWORD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CHAR_PTR_PTR, &password);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_verify_password(void* kodiBase, const char* password, const char *heading, int retries)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_VERIFY_PASSWORD - 343525 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_VERIFY_PASSWORD, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &password);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_INT, &retries);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_verify_input(void* kodiBase, const char* verify_in, char** verify_out, const char* heading, bool verify_input)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_VERIFY_INPUT - 343526 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_VERIFY_INPUT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &verify_in);
    vrp.push(API_CHAR_PTR_PTR, &verify_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_BOOL, &verify_input);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_get_time(void* kodiBase, tm *time, const char *heading)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_TIME - 343527 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_TIME, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_TM_PTR, &time);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_get_date(void* kodiBase, tm *date, const char *heading)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_DATE - 343528 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_DATE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_TM_PTR, &date);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_get_ip_address(void* kodiBase, const char* ip_address_in, char** ip_address_out, const char *heading)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_IP_ADDRESS - 343529 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_IP_ADDRESS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &ip_address_in);
    vrp.push(API_CHAR_PTR_PTR, &ip_address_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_get_number(void* kodiBase, const char* input_in, char** input_out, const char *heading, unsigned int auto_close_ms)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_NUMBER - 343530 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_NUMBER, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &input_in);
    vrp.push(API_CHAR_PTR_PTR, &input_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_UNSIGNED_INT, &auto_close_ms);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogNumeric__show_and_get_seconds(void* kodiBase, const char* time_in, char** time_out, const char *heading)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_SECONDS - 343531 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGNUMERIC__SHOW_AND_GET_SECONDS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &time_in);
    vrp.push(API_CHAR_PTR_PTR, &time_out);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogOK */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogOK__show_and_get_input_single_text(void* kodiBase, const char *heading, const char *text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGOK__SHOW_AND_GET_INPUT_SINGLE_TEXT - 343732 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGOK__SHOW_AND_GET_INPUT_SINGLE_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogOK__show_and_get_input_line_text(void* kodiBase, const char *heading, const char *line0, const char *line1, const char *line2)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGOK__SHOW_AND_GET_INPUT_LINE_TEXT - 343733 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGOK__SHOW_AND_GET_INPUT_LINE_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &line0);
    vrp.push(API_CONST_CHAR_PTR, &line1);
    vrp.push(API_CONST_CHAR_PTR, &line2);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogProgress */

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_dialogProgress__new_dialog(void* kodiBase)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__NEW_DIALOG - 343934 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__NEW_DIALOG, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__delete_dialog(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__DELETE_DIALOG - 343935 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__DELETE_DIALOG, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__open(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__OPEN - 343936 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__OPEN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__set_heading(void* kodiBase, void* handle, const char* heading)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_HEADING - 343937 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_HEADING, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__set_line(void* kodiBase, void* handle, unsigned int lineNo, const char* line)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_LINE - 343938 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_LINE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_UNSIGNED_INT, &lineNo);
    vrp.push(API_CONST_CHAR_PTR, &line);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__set_can_cancel(void* kodiBase, void* handle, bool canCancel)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_CAN_CANCEL - 343939 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_CAN_CANCEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &canCancel);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogProgress__is_canceled(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__IS_CANCELED - 343940 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__IS_CANCELED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__set_percentage(void* kodiBase, void* handle, int percentage)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_PERCENTAGE - 343941 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &percentage);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_dialogProgress__get_percentage(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__GET_PERCENTAGE - 343942 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__GET_PERCENTAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__show_progress_bar(void* kodiBase, void* handle, bool pnOff)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SHOW_PROGRESS_BAR - 343943 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SHOW_PROGRESS_BAR, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &pnOff);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__set_progress_max(void* kodiBase, void* handle, int max)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_PROGRESS_MAX - 343944 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_PROGRESS_MAX, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &max);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogProgress__set_progress_advance(void* kodiBase, void* handle, int nSteps)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_PROGRESS_ADVANCE - 343945 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__SET_PROGRESS_ADVANCE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &nSteps);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogProgress__abort(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__ABORT - 343946 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGPROGRESS__ABORT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogSelect */

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_dialogSelect__open(void* kodiBase, const char *heading, const char *entries[], unsigned int size, int selected, unsigned int autoclose)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGSELECT__OPEN - 344147 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGSELECT__OPEN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &entries[]);
    vrp.push(API_UNSIGNED_INT, &size);
    vrp.push(API_INT, &selected);
    vrp.push(API_UNSIGNED_INT, &autoclose);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogSelect__open_multi_select(void* kodiBase, const char* heading, const char* entryIDs[], const char* entryNames[], bool entriesSelected[], unsigned int size, unsigned int autoclose)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGSELECT__OPEN_MULTI_SELECT - 344148 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGSELECT__OPEN_MULTI_SELECT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &entryIDs[]);
    vrp.push(API_CONST_CHAR_PTR, &entryNames[]);
    vrp.push(API_BOOL, &entriesSelected[]);
    vrp.push(API_UNSIGNED_INT, &size);
    vrp.push(API_UNSIGNED_INT, &autoclose);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogTextViewer */

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_dialogTextViewer__open(void* kodiBase, const char *heading, const char *text)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGTEXTVIEWER__OPEN - 344349 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGTEXTVIEWER__OPEN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &text);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_dialogYesNo */

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogYesNo__show_and_get_input_single_text(void* kodiBase, const char *heading, const char *text, bool *canceled, const char *noLabel, const char *yesLabel)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGYESNO__SHOW_AND_GET_INPUT_SINGLE_TEXT - 344550 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGYESNO__SHOW_AND_GET_INPUT_SINGLE_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &text);
    vrp.push(API_BOOL_PTR, &canceled);
    vrp.push(API_CONST_CHAR_PTR, &noLabel);
    vrp.push(API_CONST_CHAR_PTR, &yesLabel);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogYesNo__show_and_get_input_line_text(void* kodiBase, const char *heading, const char *line0, const char *line1, const char *line2, const char *noLabel, const char *yesLabel)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGYESNO__SHOW_AND_GET_INPUT_LINE_TEXT - 344551 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGYESNO__SHOW_AND_GET_INPUT_LINE_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &line0);
    vrp.push(API_CONST_CHAR_PTR, &line1);
    vrp.push(API_CONST_CHAR_PTR, &line2);
    vrp.push(API_CONST_CHAR_PTR, &noLabel);
    vrp.push(API_CONST_CHAR_PTR, &yesLabel);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_dialogYesNo__show_and_get_input_line_button_text(void* kodiBase, const char *heading, const char *line0, const char *line1, const char *line2, bool *canceled, const char *noLabel, const char *yesLabel)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGYESNO__SHOW_AND_GET_INPUT_LINE_BUTTON_TEXT - 344552 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_DIALOGYESNO__SHOW_AND_GET_INPUT_LINE_BUTTON_TEXT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &heading);
    vrp.push(API_CONST_CHAR_PTR, &line0);
    vrp.push(API_CONST_CHAR_PTR, &line1);
    vrp.push(API_CONST_CHAR_PTR, &line2);
    vrp.push(API_BOOL_PTR, &canceled);
    vrp.push(API_CONST_CHAR_PTR, &noLabel);
    vrp.push(API_CONST_CHAR_PTR, &yesLabel);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_listItem */

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_listItem__create(void* kodiBase, const char* label, const char* label2, const char* icon_image, const char* path)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__CREATE - 344753 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__CREATE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &label);
    vrp.push(API_CONST_CHAR_PTR, &label2);
    vrp.push(API_CONST_CHAR_PTR, &icon_image);
    vrp.push(API_CONST_CHAR_PTR, &path);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__destroy(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__DESTROY - 344754 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__DESTROY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_listItem__get_label(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_LABEL - 344755 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__set_label(void* kodiBase, void* handle, const char* label)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_LABEL - 344756 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_listItem__get_label2(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_LABEL2 - 344757 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_LABEL2, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__set_label2(void* kodiBase, void* handle, const char* label)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_LABEL2 - 344758 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_LABEL2, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &label);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_listItem__get_icon_image(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_ICON_IMAGE - 344759 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_ICON_IMAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__set_icon_image(void* kodiBase, void* handle, const char* image)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_ICON_IMAGE - 344760 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_ICON_IMAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &image);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_listItem__get_art(void* kodiBase, void* handle, const char* type)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_ART - 344761 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_ART, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &type);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__set_art(void* kodiBase, void* handle, const char* type, const char* image)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_ART - 344762 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_ART, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &type);
    vrp.push(API_CONST_CHAR_PTR, &image);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_listItem__get_path(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_PATH - 344763 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__set_path(void* kodiBase, void* handle, const char* path)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_PATH - 344764 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_PATH, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &path);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_listItem__get_property(void* kodiBase, void* handle, const char* key)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_PROPERTY - 344765 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__GET_PROPERTY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__set_property(void* kodiBase, void* handle, const char* key, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_PROPERTY - 344766 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SET_PROPERTY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_listItem__select(void* kodiBase, void* handle, bool select)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SELECT - 344767 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__SELECT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_BOOL, &select);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_listItem__is_selected(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__IS_SELECTED - 344768 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_LISTITEM__IS_SELECTED, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui_window */

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__create(void* kodiBase, const char* xml_filename, const char* default_skin, bool as_dialog, bool is_media)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CREATE - 344969 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CREATE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_CONST_CHAR_PTR, &xml_filename);
    vrp.push(API_CONST_CHAR_PTR, &default_skin);
    vrp.push(API_BOOL, &as_dialog);
    vrp.push(API_BOOL, &is_media);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__destroy(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__DESTROY - 344970 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__DESTROY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_callbacks(void* kodiBase, void* handle, void* clienthandle, bool (*show)(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CALLBACKS - 344971 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CALLBACKS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_VOID_PTR, &clienthandle);
    vrp.push(API_BOOL_(_PTRSHOW)(VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_window__close(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLOSE - 344972 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLOSE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_window__do_modal(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__DO_MODAL - 344973 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__DO_MODAL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_window__set_focus_id(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_FOCUS_ID - 344974 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_FOCUS_ID, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_window__get_focus_id(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_FOCUS_ID - 344975 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_FOCUS_ID, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_control_label(void* kodiBase, void* handle, int control_id, const char* label)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CONTROL_LABEL - 344976 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CONTROL_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    vrp.push(API_CONST_CHAR_PTR, &label);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_property(void* kodiBase, void* handle, const char* key, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY - 344977 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_property_int(void* kodiBase, void* handle, const char* key, int value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY_INT - 344978 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY_INT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    vrp.push(API_INT, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_property_bool(void* kodiBase, void* handle, const char* key, bool value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY_BOOL - 344979 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY_BOOL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    vrp.push(API_BOOL, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_property_double(void* kodiBase, void* handle, const char* key, double value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY_DOUBLE - 344980 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_PROPERTY_DOUBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    vrp.push(API_DOUBLE, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static char* AddonToKodiFuncTable_kodi_gui_window__get_property(void* kodiBase, void* handle, const char* key)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY - 344981 */
  char* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_CHAR_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret ? strdup(ret) : ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_window__get_property_int(void* kodiBase, void* handle, const char* key)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY_INT - 344982 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY_INT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static bool AddonToKodiFuncTable_kodi_gui_window__get_property_bool(void* kodiBase, void* handle, const char* key)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY_BOOL - 344983 */
  bool ret = false;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY_BOOL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_BOOL, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static double AddonToKodiFuncTable_kodi_gui_window__get_property_double(void* kodiBase, void* handle, const char* key)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY_DOUBLE - 344984 */
  double ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_PROPERTY_DOUBLE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_DOUBLE, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__clear_properties(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLEAR_PROPERTIES - 344985 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLEAR_PROPERTIES, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__clear_property(void* kodiBase, void* handle, const char* key)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLEAR_PROPERTY - 344986 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLEAR_PROPERTY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__clear_item_list(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLEAR_ITEM_LIST - 344987 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__CLEAR_ITEM_LIST, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__add_list_item(void* kodiBase, void* handle, void* item, int list_position)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__ADD_LIST_ITEM - 344988 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__ADD_LIST_ITEM, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_VOID_PTR, &item);
    vrp.push(API_INT, &list_position);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__remove_list_item_from_position(void* kodiBase, void* handle, int list_position)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__REMOVE_LIST_ITEM_FROM_POSITION - 344989 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__REMOVE_LIST_ITEM_FROM_POSITION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &list_position);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__remove_list_item(void* kodiBase, void* handle, void* item)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__REMOVE_LIST_ITEM - 344990 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__REMOVE_LIST_ITEM, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_VOID_PTR, &item);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_list_item(void* kodiBase, void* handle, int list_position)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_LIST_ITEM - 344991 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_LIST_ITEM, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &list_position);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_current_list_position(void* kodiBase, void* handle, int list_position)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CURRENT_LIST_POSITION - 344992 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CURRENT_LIST_POSITION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &list_position);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_window__get_current_list_position(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CURRENT_LIST_POSITION - 344993 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CURRENT_LIST_POSITION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_window__get_list_size(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_LIST_SIZE - 344994 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_LIST_SIZE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_container_property(void* kodiBase, void* handle, const char* key, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CONTAINER_PROPERTY - 344995 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CONTAINER_PROPERTY, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &key);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__set_container_content(void* kodiBase, void* handle, const char* value)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CONTAINER_CONTENT - 344996 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__SET_CONTAINER_CONTENT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_CONST_CHAR_PTR, &value);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static int AddonToKodiFuncTable_kodi_gui_window__get_current_container_id(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CURRENT_CONTAINER_ID - 344997 */
  int ret = 0;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CURRENT_CONTAINER_ID, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void AddonToKodiFuncTable_kodi_gui_window__mark_dirty_region(void* kodiBase, void* handle)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__MARK_DIRTY_REGION - 344998 */
  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__MARK_DIRTY_REGION, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
  }
  PROCESS_HANDLE_EXCEPTION;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_button(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_BUTTON - 344999 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_BUTTON, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_edit(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_EDIT - 345000 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_EDIT, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_fade_label(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_FADE_LABEL - 345001 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_FADE_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_image(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_IMAGE - 345002 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_IMAGE, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_label(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_LABEL - 345003 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_LABEL, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_progress(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_PROGRESS - 345004 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_PROGRESS, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_radio_button(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_RADIO_BUTTON - 345005 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_RADIO_BUTTON, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_render_addon(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_RENDER_ADDON - 345006 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_RENDER_ADDON, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_settings_slider(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_SETTINGS_SLIDER - 345007 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_SETTINGS_SLIDER, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_slider(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_SLIDER - 345008 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_SLIDER, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_spin(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_SPIN - 345009 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_SPIN, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_text_box(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_TEXT_BOX - 345010 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_TEXT_BOX, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy1(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY1 - 345011 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY1, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy2(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY2 - 345012 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY2, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy3(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY3 - 345013 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY3, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy4(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY4 - 345014 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY4, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy5(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY5 - 345015 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY5, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy6(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY6 - 345016 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY6, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy7(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY7 - 345017 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY7, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy8(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY8 - 345018 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY8, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy9(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY9 - 345019 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY9, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Warning: Auto generated code, do not change by hand! */
static void* AddonToKodiFuncTable_kodi_gui_window__get_control_dummy10(void* kodiBase, void* handle, int control_id)
{
  /* ID: ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY10 - 345020 */
  void* ret = nullptr;

  try
  {
    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());
    CRequestPacket vrp(ADDONTOKODIFUNCTABLE_KODI_GUI_WINDOW__GET_CONTROL_DUMMY10, session);
    vrp.push(API_VOID_PTR, &kodiBase);
    vrp.push(API_VOID_PTR, &handle);
    vrp.push(API_INT, &control_id);
    uint32_t retCode;
    CLockObject lock(session->m_callMutex);
    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_BUFFER;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_VOID_PTR, &ret);
  }
  PROCESS_HANDLE_EXCEPTION;

  return ret;
}

/* Interface: AddonToKodiFuncTable_kodi_gui */

