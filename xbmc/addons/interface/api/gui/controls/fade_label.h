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
#include "addons/kodi-dev-kit/include/kodi/c-api/gui/controls/fade_label.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct directFuncToAddon_gui_controls_fade_label_h;
struct directFuncToKodi_gui_controls_fade_label_h;

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

class CHdl_kodi_gui_controls_fade_label_h : public IMsgHdl
{
public:
  CHdl_kodi_gui_controls_fade_label_h(CInterface& interface) : IMsgHdl(interface) {}

  void InitDirect(directFuncToKodi_gui_controls_fade_label_h* ifcToKodi,
                  directFuncToAddon_gui_controls_fade_label_h* ifcToAddon);

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
  static void kodi_gui_controls_fade_label_set_visible_v1(void* thisClassHdl,
                                                          KODI_GUI_CONTROL_HANDLE handle,
                                                          bool visible); // Added with API 1

  static void kodi_gui_controls_fade_label_add_label_v1(void* thisClassHdl,
                                                        KODI_GUI_CONTROL_HANDLE handle,
                                                        const char* text); // Added with API 1

  static char* kodi_gui_controls_fade_label_get_label_v1(
      void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle); // Added with API 1

  static void kodi_gui_controls_fade_label_set_scrolling_v1(void* thisClassHdl,
                                                            KODI_GUI_CONTROL_HANDLE handle,
                                                            bool scroll); // Added with API 1

  static void kodi_gui_controls_fade_label_reset_v1(
      void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle); // Added with API 1


  directFuncToAddon_gui_controls_fade_label_h* m_ifcToAddon{nullptr};
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
