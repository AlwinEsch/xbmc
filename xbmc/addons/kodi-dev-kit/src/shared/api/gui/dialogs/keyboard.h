/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#pragma once

#include "../../../../../include/kodi/c-api/gui/dialogs/keyboard.h"
#include "src/shared/SharedGroups.h"

#include <string.h>
#include <string>
#include <tuple>
#include <vector>

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

// Code here relates to direct API calls without use of shared mem from addon to Kodi.
//{{{

typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_IS_KEYBOARD_ACTIVATED_V1)(void*);
typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SEND_TEXT_TO_ACTIVE_KEYBOARD_V1)(
    void*, const char*, bool);
typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_FILTER_V1)(
    void*, const char*, char**, bool, unsigned int);
typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_INPUT_V1)(
    void*, const char*, char**, bool, unsigned int);
typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_INPUT_WITH_HEAD_V1)(
    void*, const char*, char**, const char*, bool, bool, unsigned int);
typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_NEW_PASSWORD_V1)(
    void*, const char*, char**, unsigned int);
typedef bool(
    ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_NEW_PASSWORD_WITH_HEAD_V1)(
    void*, const char*, char**, const char*, bool, unsigned int);
typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_VERIFY_NEW_PASSWORD_V1)(
    void*, char**, unsigned int);
typedef bool(
    ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_VERIFY_NEW_PASSWORD_WITH_HEAD_V1)(
    void*, char**, const char*, bool, unsigned int);
typedef int(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_VERIFY_PASSWORD_V1)(
    void*, const char*, char**, const char*, int, unsigned int);

struct directFuncToKodi_gui_dialogs_keyboard_h
{
  void* thisClassHdl;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_IS_KEYBOARD_ACTIVATED_V1
      kodi_gui_dialogs_keyboard_is_keyboard_activated_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SEND_TEXT_TO_ACTIVE_KEYBOARD_V1
      kodi_gui_dialogs_keyboard_send_text_to_active_keyboard_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_FILTER_V1
      kodi_gui_dialogs_keyboard_show_and_get_filter_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_INPUT_V1
      kodi_gui_dialogs_keyboard_show_and_get_input_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_INPUT_WITH_HEAD_V1
      kodi_gui_dialogs_keyboard_show_and_get_input_with_head_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_NEW_PASSWORD_V1
      kodi_gui_dialogs_keyboard_show_and_get_new_password_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_GET_NEW_PASSWORD_WITH_HEAD_V1
      kodi_gui_dialogs_keyboard_show_and_get_new_password_with_head_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_VERIFY_NEW_PASSWORD_V1
      kodi_gui_dialogs_keyboard_show_and_verify_new_password_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_VERIFY_NEW_PASSWORD_WITH_HEAD_V1
      kodi_gui_dialogs_keyboard_show_and_verify_new_password_with_head_v1;
  PFN_INT_KODI_GUI_DIALOGS_KEYBOARD_SHOW_AND_VERIFY_PASSWORD_V1
      kodi_gui_dialogs_keyboard_show_and_verify_password_v1;
};

//}}}

// Code here relates to direct API calls without use of shared mem from Kodi to addon.
//{{{


struct directFuncToAddon_gui_dialogs_keyboard_h
{
  void* thisClassHdl;
};

//}}}

typedef enum funcParent_gui_dialogs_keyboard_h : int
{
  funcParent_kodi_gui_dialogs_keyboard_show_and_get_input_with_head_v1,
  funcParent_kodi_gui_dialogs_keyboard_show_and_get_input_v1,
  funcParent_kodi_gui_dialogs_keyboard_show_and_get_new_password_with_head_v1,
  funcParent_kodi_gui_dialogs_keyboard_show_and_get_new_password_v1,
  funcParent_kodi_gui_dialogs_keyboard_show_and_verify_new_password_with_head_v1,
  funcParent_kodi_gui_dialogs_keyboard_show_and_verify_new_password_v1,
  funcParent_kodi_gui_dialogs_keyboard_show_and_verify_password_v1,
  funcParent_kodi_gui_dialogs_keyboard_show_and_get_filter_v1,
  funcParent_kodi_gui_dialogs_keyboard_send_text_to_active_keyboard_v1,
  funcParent_kodi_gui_dialogs_keyboard_is_keyboard_activated_v1,
} funcParent_gui_dialogs_keyboard_h;

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES>---*/
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_show_and_get_input_with_head( const char* text_in, char** text_out, const char* heading, bool allow_empty_result, bool hidden_input, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, std::string, bool, bool, unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_get_input_with_head_v1; /* Autogenerated */
typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_get_input_with_head_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_show_and_get_input(const char* text_in, char** text_out, bool allow_empty_result, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, bool, unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_get_input_v1; /* Autogenerated */
typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_get_input_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_show_and_get_new_password_with_head( const char* password_in, char** password_out, const char* heading, bool allow_empty_result, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, std::string, bool, unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_get_new_password_with_head_v1; /* Autogenerated */
typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_get_new_password_with_head_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_show_and_get_new_password( const char* password_in, char** password_out, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_get_new_password_v1; /* Autogenerated */
typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_get_new_password_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_show_and_verify_new_password_with_head( char** password_out, const char* heading, bool allow_empty_result, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, bool, unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_verify_new_password_with_head_v1; /* Autogenerated */
typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_verify_new_password_with_head_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_show_and_verify_new_password( char** password_out, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_verify_new_password_v1; /* Autogenerated */
typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_verify_new_password_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT int kodi_gui_dialogs_keyboard_show_and_verify_password(const char* password_in, char** password_out, const char* heading, int retries, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, std::string, int, unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_verify_password_v1; /* Autogenerated */
typedef std::tuple<int, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_verify_password_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_show_and_get_filter(const char* text_in, char** text_out, bool searching, unsigned int auto_close_ms) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, bool, unsigned int> msgParent__IN_kodi_gui_dialogs_keyboard_show_and_get_filter_v1; /* Autogenerated */
typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_keyboard_show_and_get_filter_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_send_text_to_active_keyboard(const char* text, bool close_keyboard) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, bool> msgParent__IN_kodi_gui_dialogs_keyboard_send_text_to_active_keyboard_v1; /* Autogenerated */
typedef std::tuple<bool> msgParent_OUT_kodi_gui_dialogs_keyboard_send_text_to_active_keyboard_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_keyboard_is_keyboard_activated() __INTRODUCED_IN_KODI(1);
typedef std::tuple<DummyValue> msgParent__IN_kodi_gui_dialogs_keyboard_is_keyboard_activated_v1; /* Autogenerated */
typedef std::tuple<bool> msgParent_OUT_kodi_gui_dialogs_keyboard_is_keyboard_activated_v1; /* Autogenerated */
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES_END>---*/
// clang-format on

//==============================================================================

typedef enum funcChild_gui_dialogs_keyboard_h : int
{
  funcChild_gui_dialogs_keyboard_h_dummy
} funcChild_gui_dialogs_keyboard_h;

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES>---*/
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES_END>---*/
// clang-format on

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
