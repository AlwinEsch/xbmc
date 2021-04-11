/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GENERAL_H
#define C_API_GENERAL_H

#include "addon_base.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef enum StdKbButtons
  {
    STD_KB_BUTTONS_PER_ROW = 20,
    STD_KB_BUTTONS_MAX_ROWS = 4,
    STD_KB_BUTTONS_MAX_CHAR = 16,
    STD_KB_MODIFIER_KEY_NONE = 0x00,
    STD_KB_MODIFIER_KEY_SHIFT = 0x01,
    STD_KB_MODIFIER_KEY_SYMBOL = 0x02
  } StdKbButtons;

  typedef enum QueueMsg
  {
    QUEUE_INFO,
    QUEUE_WARNING,
    QUEUE_ERROR,
    QUEUE_OWN_STYLE
  } QueueMsg;

  typedef enum LangFormats
  {
    LANG_FMT_ISO_639_1,
    LANG_FMT_ISO_639_2,
    LANG_FMT_ENGLISH_NAME
  } LangFormats;

  typedef enum DigestType
  {
    DIGEST_MD5,
    DIGEST_SHA1,
    DIGEST_SHA256,
    DIGEST_SHA512
  } DigestType;

  typedef struct AddonKeyboardKeyTable
  {
    char* keys[STD_KB_BUTTONS_MAX_ROWS][STD_KB_BUTTONS_PER_ROW];
  } AddonKeyboardKeyTable;

  ATTR_DLL_EXPORT char* kodi_get_localized_string(long label_id) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_get_free_mem(long* free, long* total, bool as_bytes) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_unknown_to_utf8(const char* source, bool* ret, bool failOnBadChar) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_get_language(enum LangFormats format, bool region) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_queue_notification(enum QueueMsg type,
                                             const char* header,
                                             const char* message,
                                             const char* imageFile,
                                             unsigned int displayTime,
                                             bool withSound,
                                             unsigned int messageTime) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_get_digest(enum DigestType type, const char* text) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_get_region(const char* id) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT int kodi_get_global_idle_time() __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_is_addon_avilable(const char* id, char** version, bool* enabled) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_version(
      char** compile_name, int* major, int* minor, char** revision, char** tag, char** tagversion) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_get_current_skin_id() __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_get_keyboard_layout(int modifier_key,
                                              char** layout_name,
                                              struct AddonKeyboardKeyTable* layout) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_change_keyboard_layout(char** layout_name) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_play_sfx(const char* filename, bool use_cached) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_stop_sfx() __INTRODUCED_IN_KODI(1);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !C_API_GENERAL_H */
