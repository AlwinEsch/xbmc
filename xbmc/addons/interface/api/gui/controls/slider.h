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
#include "addons/kodi-dev-kit/include/kodi/c-api/gui/controls/slider.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct directFuncToAddon_gui_controls_slider_h;
struct directFuncToKodi_gui_controls_slider_h;

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

class CHdl_kodi_gui_controls_slider_h : public IMsgHdl
{
public:
  CHdl_kodi_gui_controls_slider_h(CInterface& interface) : IMsgHdl(interface) {}

  void InitDirect(directFuncToKodi_gui_controls_slider_h* ifcToKodi,
                  directFuncToAddon_gui_controls_slider_h* ifcToAddon);

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
  static void kodi_gui_controls_slider_set_visible_v1(void* thisClassHdl,
                                                      KODI_GUI_CONTROL_HANDLE handle,
                                                      bool visible); // Added with API 1

  static void kodi_gui_controls_slider_set_enabled_v1(void* thisClassHdl,
                                                      KODI_GUI_CONTROL_HANDLE handle,
                                                      bool enabled); // Added with API 1

  static void kodi_gui_controls_slider_reset_v1(void* thisClassHdl,
                                                KODI_GUI_CONTROL_HANDLE handle); // Added with API 1

  static char* kodi_gui_controls_slider_get_description_v1(
      void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle); // Added with API 1

  static void kodi_gui_controls_slider_set_int_range_v1(void* thisClassHdl,
                                                        KODI_GUI_CONTROL_HANDLE handle,
                                                        int start,
                                                        int end); // Added with API 1

  static void kodi_gui_controls_slider_set_int_value_v1(void* thisClassHdl,
                                                        KODI_GUI_CONTROL_HANDLE handle,
                                                        int value); // Added with API 1

  static int kodi_gui_controls_slider_get_int_value_v1(
      void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle); // Added with API 1

  static void kodi_gui_controls_slider_set_int_interval_v1(void* thisClassHdl,
                                                           KODI_GUI_CONTROL_HANDLE handle,
                                                           int interval); // Added with API 1

  static void kodi_gui_controls_slider_set_percentage_v1(void* thisClassHdl,
                                                         KODI_GUI_CONTROL_HANDLE handle,
                                                         float percent); // Added with API 1

  static float kodi_gui_controls_slider_get_percentage_v1(
      void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle); // Added with API 1

  static void kodi_gui_controls_slider_set_float_range_v1(void* thisClassHdl,
                                                          KODI_GUI_CONTROL_HANDLE handle,
                                                          float start,
                                                          float end); // Added with API 1

  static void kodi_gui_controls_slider_set_float_value_v1(void* thisClassHdl,
                                                          KODI_GUI_CONTROL_HANDLE handle,
                                                          float value); // Added with API 1

  static float kodi_gui_controls_slider_get_float_value_v1(
      void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle); // Added with API 1

  static void kodi_gui_controls_slider_set_float_interval_v1(void* thisClassHdl,
                                                             KODI_GUI_CONTROL_HANDLE handle,
                                                             float interval); // Added with API 1


  directFuncToAddon_gui_controls_slider_h* m_ifcToAddon{nullptr};
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
