/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#include "edit.h"

// Shared API
#include "src/shared/Instances.h"

// Lib code
#include "core/addon_control.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

using namespace KODI::ADDONS::INTERFACE;
using namespace KODI_ADDON::INTERNAL;

namespace KODI_ADDON
{
namespace INTERNAL
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

void CHdl_kodi_gui_controls_edit_h::InitDirect(directFuncToAddon_gui_controls_edit_h* ifcToAddon)
{
  ifcToAddon->thisClassHdl = this;
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

/* NOTE: unused (no functions from Kodi to addon here) */

} /* namespace INTERNAL */
} /* namespace KODI_ADDON */

ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_visible(KODI_GUI_CONTROL_HANDLE handle,
                                                        bool visible)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_visible(KODI_GUI_CONTROL_HANDLE handle, bool visible) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, bool> msgParent__IN_kodi_gui_controls_edit_set_visible_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_edit_set_visible_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in,
                  msgParent__IN_kodi_gui_controls_edit_set_visible_v1(PtrValue(handle), visible));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_set_visible_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  auto_gen_group.kodi_gui_controls_edit_set_visible_v1(auto_gen_group.thisClassHdl, handle,
                                                       visible);
}

ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_enabled(KODI_GUI_CONTROL_HANDLE handle,
                                                        bool enabled)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_enabled(KODI_GUI_CONTROL_HANDLE handle, bool enabled) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, bool> msgParent__IN_kodi_gui_controls_edit_set_enabled_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_edit_set_enabled_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in,
                  msgParent__IN_kodi_gui_controls_edit_set_enabled_v1(PtrValue(handle), enabled));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_set_enabled_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  auto_gen_group.kodi_gui_controls_edit_set_enabled_v1(auto_gen_group.thisClassHdl, handle,
                                                       enabled);
}

ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_label(KODI_GUI_CONTROL_HANDLE handle,
                                                      const char* label)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_label(KODI_GUI_CONTROL_HANDLE handle, const char* label) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_controls_edit_set_label_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_edit_set_label_v1; /* Autogenerated */

  if (handle == nullptr || label == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_controls_edit_set_label_v1(PtrValue(handle), label));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_set_label_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  auto_gen_group.kodi_gui_controls_edit_set_label_v1(auto_gen_group.thisClassHdl, handle, label);
}

ATTR_DLL_EXPORT char* kodi_gui_controls_edit_get_label(KODI_GUI_CONTROL_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT char* kodi_gui_controls_edit_get_label(KODI_GUI_CONTROL_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_controls_edit_get_label_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<std::string> msgParent_OUT_kodi_gui_controls_edit_get_label_v1; /* Autogenerated */

  if (handle == nullptr)
    return nullptr;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgParent__IN_kodi_gui_controls_edit_get_label_v1(PtrValue(handle)));
    if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
            funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_get_label_v1, in, out))
      return nullptr;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgParent_OUT_kodi_gui_controls_edit_get_label_v1 t = ident.get().as<decltype(t)>();

    return strdup(std::get<0>(t).c_str());
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  return auto_gen_group.kodi_gui_controls_edit_get_label_v1(auto_gen_group.thisClassHdl, handle);
}

ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_text(KODI_GUI_CONTROL_HANDLE handle,
                                                     const char* text)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_text(KODI_GUI_CONTROL_HANDLE handle, const char* text) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_controls_edit_set_text_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_edit_set_text_v1; /* Autogenerated */

  if (handle == nullptr || text == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_controls_edit_set_text_v1(PtrValue(handle), text));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_set_text_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  auto_gen_group.kodi_gui_controls_edit_set_text_v1(auto_gen_group.thisClassHdl, handle, text);
}

ATTR_DLL_EXPORT char* kodi_gui_controls_edit_get_text(KODI_GUI_CONTROL_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT char* kodi_gui_controls_edit_get_text(KODI_GUI_CONTROL_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_controls_edit_get_text_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<std::string> msgParent_OUT_kodi_gui_controls_edit_get_text_v1; /* Autogenerated */

  if (handle == nullptr)
    return nullptr;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgParent__IN_kodi_gui_controls_edit_get_text_v1(PtrValue(handle)));
    if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
            funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_get_text_v1, in, out))
      return nullptr;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgParent_OUT_kodi_gui_controls_edit_get_text_v1 t = ident.get().as<decltype(t)>();

    return strdup(std::get<0>(t).c_str());
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  return auto_gen_group.kodi_gui_controls_edit_get_text_v1(auto_gen_group.thisClassHdl, handle);
}

ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_cursor_position(KODI_GUI_CONTROL_HANDLE handle,
                                                                unsigned int position)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_cursor_position(KODI_GUI_CONTROL_HANDLE handle, unsigned int position) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, unsigned int> msgParent__IN_kodi_gui_controls_edit_set_cursor_position_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_edit_set_cursor_position_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_controls_edit_set_cursor_position_v1(PtrValue(handle),
                                                                                  position));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_set_cursor_position_v1,
        in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  auto_gen_group.kodi_gui_controls_edit_set_cursor_position_v1(auto_gen_group.thisClassHdl, handle,
                                                               position);
}

ATTR_DLL_EXPORT unsigned int kodi_gui_controls_edit_get_cursor_position(
    KODI_GUI_CONTROL_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT unsigned int kodi_gui_controls_edit_get_cursor_position( KODI_GUI_CONTROL_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_controls_edit_get_cursor_position_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<unsigned int> msgParent_OUT_kodi_gui_controls_edit_get_cursor_position_v1; /* Autogenerated */

  if (handle == nullptr)
    return 0;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in,
                  msgParent__IN_kodi_gui_controls_edit_get_cursor_position_v1(PtrValue(handle)));
    if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
            funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_get_cursor_position_v1,
            in, out))
      return 0;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgParent_OUT_kodi_gui_controls_edit_get_cursor_position_v1 t = ident.get().as<decltype(t)>();

    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  return auto_gen_group.kodi_gui_controls_edit_get_cursor_position_v1(auto_gen_group.thisClassHdl,
                                                                      handle);
}

ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_input_type(KODI_GUI_CONTROL_HANDLE handle,
                                                           int type,
                                                           const char* heading)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_edit_set_input_type(KODI_GUI_CONTROL_HANDLE handle, int type, const char* heading) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, int, std::string> msgParent__IN_kodi_gui_controls_edit_set_input_type_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_edit_set_input_type_v1; /* Autogenerated */

  if (handle == nullptr || heading == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_controls_edit_set_input_type_v1(PtrValue(handle), type,
                                                                             heading));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_controls_edit_h, funcParent_kodi_gui_controls_edit_set_input_type_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_controls_edit_h;
  auto_gen_group.kodi_gui_controls_edit_set_input_type_v1(auto_gen_group.thisClassHdl, handle, type,
                                                          heading);
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4_END>---*/
