/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#include "progress.h"

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

void CHdl_kodi_gui_dialogs_progress_h::InitDirect(
    directFuncToAddon_gui_dialogs_progress_h* ifcToAddon)
{
  ifcToAddon->thisClassHdl = this;
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

/* NOTE: unused (no functions from Kodi to addon here) */

} /* namespace INTERNAL */
} /* namespace KODI_ADDON */

ATTR_DLL_EXPORT KODI_GUI_HANDLE kodi_gui_dialogs_progress_new_dialog()
{
  // Original API call: ATTR_DLL_EXPORT KODI_GUI_HANDLE kodi_gui_dialogs_progress_new_dialog() __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<DummyValue> msgParent__IN_kodi_gui_dialogs_progress_new_dialog_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<PtrValue> msgParent_OUT_kodi_gui_dialogs_progress_new_dialog_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer out;
    if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessageOnlyGetReturn(
            funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_new_dialog_v1,
            out))
      return nullptr;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgParent_OUT_kodi_gui_dialogs_progress_new_dialog_v1 t = ident.get().as<decltype(t)>();

    return reinterpret_cast<KODI_GUI_HANDLE>(std::get<0>(t));
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  return auto_gen_group.kodi_gui_dialogs_progress_new_dialog_v1(auto_gen_group.thisClassHdl);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_delete_dialog(KODI_GUI_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_delete_dialog(KODI_GUI_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_dialogs_progress_delete_dialog_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_delete_dialog_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_delete_dialog_v1(PtrValue(handle)));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_delete_dialog_v1,
        in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_delete_dialog_v1(auto_gen_group.thisClassHdl, handle);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_open(KODI_GUI_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_open(KODI_GUI_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_dialogs_progress_open_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_open_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_open_v1(PtrValue(handle)));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_open_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_open_v1(auto_gen_group.thisClassHdl, handle);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_heading(KODI_GUI_HANDLE handle,
                                                           const char* heading)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_heading(KODI_GUI_HANDLE handle, const char* heading) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_dialogs_progress_set_heading_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_set_heading_v1; /* Autogenerated */

  if (handle == nullptr || heading == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(
        in, msgParent__IN_kodi_gui_dialogs_progress_set_heading_v1(PtrValue(handle), heading));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_set_heading_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_set_heading_v1(auto_gen_group.thisClassHdl, handle,
                                                          heading);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_line(KODI_GUI_HANDLE handle,
                                                        unsigned int line_no,
                                                        const char* line)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_line(KODI_GUI_HANDLE handle, unsigned int line_no, const char* line) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, unsigned int, std::string> msgParent__IN_kodi_gui_dialogs_progress_set_line_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_set_line_v1; /* Autogenerated */

  if (handle == nullptr || line == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(
        in, msgParent__IN_kodi_gui_dialogs_progress_set_line_v1(PtrValue(handle), line_no, line));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_set_line_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_set_line_v1(auto_gen_group.thisClassHdl, handle, line_no,
                                                       line);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_can_cancel(KODI_GUI_HANDLE handle,
                                                              bool can_cancel)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_can_cancel(KODI_GUI_HANDLE handle, bool can_cancel) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, bool> msgParent__IN_kodi_gui_dialogs_progress_set_can_cancel_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_set_can_cancel_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_set_can_cancel_v1(PtrValue(handle),
                                                                                can_cancel));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_set_can_cancel_v1,
        in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_set_can_cancel_v1(auto_gen_group.thisClassHdl, handle,
                                                             can_cancel);
}

ATTR_DLL_EXPORT bool kodi_gui_dialogs_progress_is_canceled(KODI_GUI_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_progress_is_canceled(KODI_GUI_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_dialogs_progress_is_canceled_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<bool> msgParent_OUT_kodi_gui_dialogs_progress_is_canceled_v1; /* Autogenerated */

  if (handle == nullptr)
    return false;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_is_canceled_v1(PtrValue(handle)));
    if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
            funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_is_canceled_v1,
            in, out))
      return false;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgParent_OUT_kodi_gui_dialogs_progress_is_canceled_v1 t = ident.get().as<decltype(t)>();

    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  return auto_gen_group.kodi_gui_dialogs_progress_is_canceled_v1(auto_gen_group.thisClassHdl,
                                                                 handle);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_percentage(KODI_GUI_HANDLE handle,
                                                              int percentage)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_percentage(KODI_GUI_HANDLE handle, int percentage) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, int> msgParent__IN_kodi_gui_dialogs_progress_set_percentage_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_set_percentage_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_set_percentage_v1(PtrValue(handle),
                                                                                percentage));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_set_percentage_v1,
        in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_set_percentage_v1(auto_gen_group.thisClassHdl, handle,
                                                             percentage);
}

ATTR_DLL_EXPORT int kodi_gui_dialogs_progress_get_percentage(KODI_GUI_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT int kodi_gui_dialogs_progress_get_percentage(KODI_GUI_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_dialogs_progress_get_percentage_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<int> msgParent_OUT_kodi_gui_dialogs_progress_get_percentage_v1; /* Autogenerated */

  if (handle == nullptr)
    return -1;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_get_percentage_v1(PtrValue(handle)));
    if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
            funcGroup_gui_dialogs_progress_h,
            funcParent_kodi_gui_dialogs_progress_get_percentage_v1, in, out))
      return -1;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgParent_OUT_kodi_gui_dialogs_progress_get_percentage_v1 t = ident.get().as<decltype(t)>();

    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  return auto_gen_group.kodi_gui_dialogs_progress_get_percentage_v1(auto_gen_group.thisClassHdl,
                                                                    handle);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_show_progress_bar(KODI_GUI_HANDLE handle,
                                                                 bool on_off)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_show_progress_bar(KODI_GUI_HANDLE handle, bool on_off) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, bool> msgParent__IN_kodi_gui_dialogs_progress_show_progress_bar_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_show_progress_bar_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(
        in, msgParent__IN_kodi_gui_dialogs_progress_show_progress_bar_v1(PtrValue(handle), on_off));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_show_progress_bar_v1,
        in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_show_progress_bar_v1(auto_gen_group.thisClassHdl, handle,
                                                                on_off);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_progress_max(KODI_GUI_HANDLE handle, int max)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_progress_max(KODI_GUI_HANDLE handle, int max) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, int> msgParent__IN_kodi_gui_dialogs_progress_set_progress_max_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_set_progress_max_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(
        in, msgParent__IN_kodi_gui_dialogs_progress_set_progress_max_v1(PtrValue(handle), max));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_set_progress_max_v1,
        in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_set_progress_max_v1(auto_gen_group.thisClassHdl, handle,
                                                               max);
}

ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_progress_advance(KODI_GUI_HANDLE handle,
                                                                    int n_steps)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_gui_dialogs_progress_set_progress_advance(KODI_GUI_HANDLE handle, int n_steps) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue, int> msgParent__IN_kodi_gui_dialogs_progress_set_progress_advance_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_dialogs_progress_set_progress_advance_v1; /* Autogenerated */

  if (handle == nullptr)
    return;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_set_progress_advance_v1(
                          PtrValue(handle), n_steps));
    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
        funcGroup_gui_dialogs_progress_h,
        funcParent_kodi_gui_dialogs_progress_set_progress_advance_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  auto_gen_group.kodi_gui_dialogs_progress_set_progress_advance_v1(auto_gen_group.thisClassHdl,
                                                                   handle, n_steps);
}

ATTR_DLL_EXPORT bool kodi_gui_dialogs_progress_abort(KODI_GUI_HANDLE handle)
{
  // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_progress_abort(KODI_GUI_HANDLE handle) __INTRODUCED_IN_KODI(1);
  // Tuple in:          typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_dialogs_progress_abort_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<bool> msgParent_OUT_kodi_gui_dialogs_progress_abort_v1; /* Autogenerated */

  if (handle == nullptr)
    return false;

#ifndef KODI_INHIBIT_SHARED
  if (!AddonIfc::g_ifc->direct_used)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgParent__IN_kodi_gui_dialogs_progress_abort_v1(PtrValue(handle)));
    if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(
            funcGroup_gui_dialogs_progress_h, funcParent_kodi_gui_dialogs_progress_abort_v1, in,
            out))
      return false;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgParent_OUT_kodi_gui_dialogs_progress_abort_v1 t = ident.get().as<decltype(t)>();

    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.gui_dialogs_progress_h;
  return auto_gen_group.kodi_gui_dialogs_progress_abort_v1(auto_gen_group.thisClassHdl, handle);
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4_END>---*/
