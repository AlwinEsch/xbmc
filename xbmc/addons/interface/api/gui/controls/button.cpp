/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#include "button.h"

// Shared API
#include "addons/kodi-dev-kit/src/shared/api/gui/controls/button.h"

// Kodi
#include "addons/interface/RunningProcess.h"
#include "utils/log.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/

#include "guilib/GUIButtonControl.h"
#include "utils/StringUtils.h"

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

void CHdl_kodi_gui_controls_button_h::InitDirect(
    directFuncToKodi_gui_controls_button_h* ifcToKodi,
    directFuncToAddon_gui_controls_button_h* ifcToAddon)
{
  ifcToKodi->thisClassHdl = this;
  m_ifcToAddon = ifcToAddon;
  ifcToKodi->kodi_gui_controls_button_set_visible_v1 = kodi_gui_controls_button_set_visible_v1;
  ifcToKodi->kodi_gui_controls_button_set_enabled_v1 = kodi_gui_controls_button_set_enabled_v1;
  ifcToKodi->kodi_gui_controls_button_set_label_v1 = kodi_gui_controls_button_set_label_v1;
  ifcToKodi->kodi_gui_controls_button_get_label_v1 = kodi_gui_controls_button_get_label_v1;
  ifcToKodi->kodi_gui_controls_button_set_label2_v1 = kodi_gui_controls_button_set_label2_v1;
  ifcToKodi->kodi_gui_controls_button_get_label2_v1 = kodi_gui_controls_button_get_label2_v1;
}

bool CHdl_kodi_gui_controls_button_h::HandleMessage(int funcGroup,
                                                    int func,
                                                    const msgpack::unpacked& in,
                                                    msgpack::sbuffer& out)
{
  if (funcGroup != funcGroup_gui_controls_button_h)
    return false;

  switch (func)
  {
    case funcParent_kodi_gui_controls_button_set_visible_v1:
    {
      // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_button_set_visible(KODI_GUI_CONTROL_HANDLE handle, bool visible) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue, bool> msgParent__IN_kodi_gui_controls_button_set_visible_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_button_set_visible_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_controls_button_set_visible_v1 t = in.get().as<decltype(t)>();
      KODI_GUI_CONTROL_HANDLE handle = reinterpret_cast<KODI_GUI_CONTROL_HANDLE>(std::get<0>(t));
      bool visible = std::get<1>(t);
      kodi_gui_controls_button_set_visible_v1(this, handle, visible);
      return true;
    }
    case funcParent_kodi_gui_controls_button_set_enabled_v1:
    {
      // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_button_set_enabled(KODI_GUI_CONTROL_HANDLE handle, bool enabled) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue, bool> msgParent__IN_kodi_gui_controls_button_set_enabled_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_button_set_enabled_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_controls_button_set_enabled_v1 t = in.get().as<decltype(t)>();
      KODI_GUI_CONTROL_HANDLE handle = reinterpret_cast<KODI_GUI_CONTROL_HANDLE>(std::get<0>(t));
      bool enabled = std::get<1>(t);
      kodi_gui_controls_button_set_enabled_v1(this, handle, enabled);
      return true;
    }
    case funcParent_kodi_gui_controls_button_set_label_v1:
    {
      // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_button_set_label(KODI_GUI_CONTROL_HANDLE handle, const char* label) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_controls_button_set_label_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_button_set_label_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_controls_button_set_label_v1 t = in.get().as<decltype(t)>();
      KODI_GUI_CONTROL_HANDLE handle = reinterpret_cast<KODI_GUI_CONTROL_HANDLE>(std::get<0>(t));
      const std::string& label = std::get<1>(t);
      kodi_gui_controls_button_set_label_v1(this, handle, label.c_str());
      return true;
    }
    case funcParent_kodi_gui_controls_button_get_label_v1:
    {
      // Original API call: ATTR_DLL_EXPORT char* kodi_gui_controls_button_get_label(KODI_GUI_CONTROL_HANDLE handle) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_controls_button_get_label_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<std::string> msgParent_OUT_kodi_gui_controls_button_get_label_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_controls_button_get_label_v1 t = in.get().as<decltype(t)>();
      KODI_GUI_CONTROL_HANDLE handle = reinterpret_cast<KODI_GUI_CONTROL_HANDLE>(std::get<0>(t));
      char* auto_gen_ret = kodi_gui_controls_button_get_label_v1(this, handle);
      msgpack::pack(out, msgParent_OUT_kodi_gui_controls_button_get_label_v1(
                             auto_gen_ret ? auto_gen_ret : ""));
      if (auto_gen_ret)
        free(auto_gen_ret);
      return true;
    }
    case funcParent_kodi_gui_controls_button_set_label2_v1:
    {
      // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_button_set_label2(KODI_GUI_CONTROL_HANDLE handle, const char* label) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_controls_button_set_label2_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_button_set_label2_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_controls_button_set_label2_v1 t = in.get().as<decltype(t)>();
      KODI_GUI_CONTROL_HANDLE handle = reinterpret_cast<KODI_GUI_CONTROL_HANDLE>(std::get<0>(t));
      const std::string& label = std::get<1>(t);
      kodi_gui_controls_button_set_label2_v1(this, handle, label.c_str());
      return true;
    }
    case funcParent_kodi_gui_controls_button_get_label2_v1:
    {
      // Original API call: ATTR_DLL_EXPORT char* kodi_gui_controls_button_get_label2(KODI_GUI_CONTROL_HANDLE handle) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_controls_button_get_label2_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<std::string> msgParent_OUT_kodi_gui_controls_button_get_label2_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_controls_button_get_label2_v1 t = in.get().as<decltype(t)>();
      KODI_GUI_CONTROL_HANDLE handle = reinterpret_cast<KODI_GUI_CONTROL_HANDLE>(std::get<0>(t));
      char* auto_gen_ret = kodi_gui_controls_button_get_label2_v1(this, handle);
      msgpack::pack(out, msgParent_OUT_kodi_gui_controls_button_get_label2_v1(
                             auto_gen_ret ? auto_gen_ret : ""));
      if (auto_gen_ret)
        free(auto_gen_ret);
      return true;
    }
    default:
      CLog::Log(LOGERROR,
                "CHdl_kodi_gui_controls_button_h::{}: addon called with unknown function id '{}' "
                "on group 'gui_controls_button_h'",
                __func__, func);
  }

  return false;
}

// Function calls from Kodi to addon
/* NOTE: unused (no functions here) */

// Callbacks from addon to Kodi

void CHdl_kodi_gui_controls_button_h::kodi_gui_controls_button_set_visible_v1(
    void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle, bool visible)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_controls_button_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_VISIBLE>---*/

  static_cast<CGUIButtonControl*>(handle)->SetVisible(visible);

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_VISIBLE_END>---*/
}

void CHdl_kodi_gui_controls_button_h::kodi_gui_controls_button_set_enabled_v1(
    void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle, bool enabled)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_controls_button_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_ENABLED>---*/

  static_cast<CGUIButtonControl*>(handle)->SetEnabled(enabled);

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_ENABLED_END>---*/
}

void CHdl_kodi_gui_controls_button_h::kodi_gui_controls_button_set_label_v1(
    void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle, const char* label)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_controls_button_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_LABEL>---*/

  static_cast<CGUIButtonControl*>(handle)->SetLabel(label);

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_LABEL_END>---*/
}

char* CHdl_kodi_gui_controls_button_h::kodi_gui_controls_button_get_label_v1(
    void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_controls_button_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return nullptr;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_GET_LABEL>---*/

  return strdup(static_cast<CGUIButtonControl*>(handle)->GetLabel().c_str());

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_GET_LABEL_END>---*/
}

void CHdl_kodi_gui_controls_button_h::kodi_gui_controls_button_set_label2_v1(
    void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle, const char* label)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_controls_button_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_LABEL2>---*/

  static_cast<CGUIButtonControl*>(handle)->SetLabel2(label);

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_SET_LABEL2_END>---*/
}

char* CHdl_kodi_gui_controls_button_h::kodi_gui_controls_button_get_label2_v1(
    void* thisClassHdl, KODI_GUI_CONTROL_HANDLE handle)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_controls_button_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return nullptr;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_GET_LABEL2>---*/

  return strdup(static_cast<CGUIButtonControl*>(handle)->GetLabel2().c_str());

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_CONTROLS_BUTTON_GET_LABEL2_END>---*/
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
