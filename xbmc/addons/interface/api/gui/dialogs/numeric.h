/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#pragma once

#include "addons/interface/IMsgHdl.h"

// API include
#include "addons/kodi-dev-kit/include/kodi/c-api/gui/dialogs/numeric.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct directFuncToAddon_gui_dialogs_numeric_h;
struct directFuncToKodi_gui_dialogs_numeric_h;

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

class CHdl_kodi_gui_dialogs_numeric_h : public IMsgHdl
{
public:
  CHdl_kodi_gui_dialogs_numeric_h(CInterface& interface) : IMsgHdl(interface) {}

  void InitDirect(directFuncToKodi_gui_dialogs_numeric_h* ifcToKodi,
                  directFuncToAddon_gui_dialogs_numeric_h* ifcToAddon);

  // To handle callbacks from addon by shared sandbox API (static functions below in private becomes used)
  bool HandleMessage(int funcGroup,
                     int func,
                     const msgpack::unpacked& in,
                     msgpack::sbuffer& out) override;

  /* Code below becomes on auto generation reused, hand edited parts should included here */
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

  // Function calls from Kodi to addon

private:
  /* Code below becomes on auto generation reused, hand edited parts should included here */
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4>---*/
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4_END>---*/

  // Callbacks from addon to Kodi
  static bool kodi_gui_dialogs_numeric_show_and_verify_new_password_v1(
      void* thisClassHdl, char** password); // Added with API 1

  static int kodi_gui_dialogs_numeric_show_and_verify_password_v1(void* thisClassHdl,
                                                                  const char* password,
                                                                  const char* heading,
                                                                  int retries); // Added with API 1

  static bool kodi_gui_dialogs_numeric_show_and_verify_input_v1(
      void* thisClassHdl,
      const char* verify_in,
      char** verify_out,
      const char* heading,
      bool verify_input); // Added with API 1

  static bool kodi_gui_dialogs_numeric_show_and_get_time_v1(
      void* thisClassHdl, struct tm* time, const char* heading); // Added with API 1

  static bool kodi_gui_dialogs_numeric_show_and_get_date_v1(
      void* thisClassHdl, struct tm* date, const char* heading); // Added with API 1

  static bool kodi_gui_dialogs_numeric_show_and_get_ip_address_v1(
      void* thisClassHdl,
      const char* ip_address_in,
      char** ip_address_out,
      const char* heading); // Added with API 1

  static bool kodi_gui_dialogs_numeric_show_and_get_number_v1(
      void* thisClassHdl,
      const char* number_in,
      char** number_out,
      const char* heading,
      unsigned int auto_close_ms); // Added with API 1

  static bool kodi_gui_dialogs_numeric_show_and_get_seconds_v1(
      void* thisClassHdl,
      const char* time_in,
      char** time_out,
      const char* heading); // Added with API 1


  directFuncToAddon_gui_dialogs_numeric_h* m_ifcToAddon{nullptr};
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
