/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#pragma once

#include "../../../../include/kodi/c-api/gui/list_item.h"
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

typedef KODI_GUI_LISTITEM_HANDLE(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_CREATE_V1)(
    void*, const char*, const char*, const char*);
typedef bool(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_IS_SELECTED_V1)(void*,
                                                                          KODI_GUI_LISTITEM_HANDLE);
typedef char*(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_GET_ART_V1)(void*,
                                                                       KODI_GUI_LISTITEM_HANDLE,
                                                                       const char*);
typedef char*(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_GET_LABEL2_V1)(void*,
                                                                          KODI_GUI_LISTITEM_HANDLE);
typedef char*(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_GET_LABEL_V1)(void*,
                                                                         KODI_GUI_LISTITEM_HANDLE);
typedef char*(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_GET_PATH_V1)(void*,
                                                                        KODI_GUI_LISTITEM_HANDLE);
typedef char*(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_GET_PROPERTY_V1)(
    void*, KODI_GUI_LISTITEM_HANDLE, const char*);
typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_DESTROY_V1)(void*,
                                                                      KODI_GUI_LISTITEM_HANDLE);
typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_SELECT_V1)(void*,
                                                                     KODI_GUI_LISTITEM_HANDLE,
                                                                     bool);
typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_SET_ART_V1)(void*,
                                                                      KODI_GUI_LISTITEM_HANDLE,
                                                                      const char*,
                                                                      const char*);
typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_SET_LABEL2_V1)(void*,
                                                                         KODI_GUI_LISTITEM_HANDLE,
                                                                         const char*);
typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_SET_LABEL_V1)(void*,
                                                                        KODI_GUI_LISTITEM_HANDLE,
                                                                        const char*);
typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_SET_PATH_V1)(void*,
                                                                       KODI_GUI_LISTITEM_HANDLE,
                                                                       const char*);
typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_LISTITEM_SET_PROPERTY_V1)(void*,
                                                                           KODI_GUI_LISTITEM_HANDLE,
                                                                           const char*,
                                                                           const char*);

struct directFuncToKodi_gui_list_item_h
{
  void* thisClassHdl;
  PFN_INT_KODI_GUI_LISTITEM_CREATE_V1 kodi_gui_listitem_create_v1;
  PFN_INT_KODI_GUI_LISTITEM_DESTROY_V1 kodi_gui_listitem_destroy_v1;
  PFN_INT_KODI_GUI_LISTITEM_GET_ART_V1 kodi_gui_listitem_get_art_v1;
  PFN_INT_KODI_GUI_LISTITEM_GET_LABEL2_V1 kodi_gui_listitem_get_label2_v1;
  PFN_INT_KODI_GUI_LISTITEM_GET_LABEL_V1 kodi_gui_listitem_get_label_v1;
  PFN_INT_KODI_GUI_LISTITEM_GET_PATH_V1 kodi_gui_listitem_get_path_v1;
  PFN_INT_KODI_GUI_LISTITEM_GET_PROPERTY_V1 kodi_gui_listitem_get_property_v1;
  PFN_INT_KODI_GUI_LISTITEM_IS_SELECTED_V1 kodi_gui_listitem_is_selected_v1;
  PFN_INT_KODI_GUI_LISTITEM_SELECT_V1 kodi_gui_listitem_select_v1;
  PFN_INT_KODI_GUI_LISTITEM_SET_ART_V1 kodi_gui_listitem_set_art_v1;
  PFN_INT_KODI_GUI_LISTITEM_SET_LABEL2_V1 kodi_gui_listitem_set_label2_v1;
  PFN_INT_KODI_GUI_LISTITEM_SET_LABEL_V1 kodi_gui_listitem_set_label_v1;
  PFN_INT_KODI_GUI_LISTITEM_SET_PATH_V1 kodi_gui_listitem_set_path_v1;
  PFN_INT_KODI_GUI_LISTITEM_SET_PROPERTY_V1 kodi_gui_listitem_set_property_v1;
};

//}}}

// Code here relates to direct API calls without use of shared mem from Kodi to addon.
//{{{


struct directFuncToAddon_gui_list_item_h
{
  void* thisClassHdl;
};

//}}}

typedef enum funcParent_gui_list_item_h : int
{
  funcParent_kodi_gui_listitem_create_v1,
  funcParent_kodi_gui_listitem_destroy_v1,
  funcParent_kodi_gui_listitem_get_label_v1,
  funcParent_kodi_gui_listitem_set_label_v1,
  funcParent_kodi_gui_listitem_get_label2_v1,
  funcParent_kodi_gui_listitem_set_label2_v1,
  funcParent_kodi_gui_listitem_get_art_v1,
  funcParent_kodi_gui_listitem_set_art_v1,
  funcParent_kodi_gui_listitem_get_path_v1,
  funcParent_kodi_gui_listitem_set_path_v1,
  funcParent_kodi_gui_listitem_get_property_v1,
  funcParent_kodi_gui_listitem_set_property_v1,
  funcParent_kodi_gui_listitem_select_v1,
  funcParent_kodi_gui_listitem_is_selected_v1,
} funcParent_gui_list_item_h;

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES>---*/
// Original API call: ATTR_DLL_EXPORT KODI_GUI_LISTITEM_HANDLE kodi_gui_listitem_create(const char* label, const char* label2, const char* path) __INTRODUCED_IN_KODI(1);
typedef std::tuple<std::string, std::string, std::string> msgParent__IN_kodi_gui_listitem_create_v1; /* Autogenerated */
typedef std::tuple<PtrValue> msgParent_OUT_kodi_gui_listitem_create_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT void kodi_gui_listitem_destroy(KODI_GUI_LISTITEM_HANDLE handle) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_listitem_destroy_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_listitem_destroy_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT char* kodi_gui_listitem_get_label(KODI_GUI_LISTITEM_HANDLE handle) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_listitem_get_label_v1; /* Autogenerated */
typedef std::tuple<std::string> msgParent_OUT_kodi_gui_listitem_get_label_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT void kodi_gui_listitem_set_label(KODI_GUI_LISTITEM_HANDLE handle, const char* label) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_listitem_set_label_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_listitem_set_label_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT char* kodi_gui_listitem_get_label2(KODI_GUI_LISTITEM_HANDLE handle) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_listitem_get_label2_v1; /* Autogenerated */
typedef std::tuple<std::string> msgParent_OUT_kodi_gui_listitem_get_label2_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT void kodi_gui_listitem_set_label2(KODI_GUI_LISTITEM_HANDLE handle, const char* label) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_listitem_set_label2_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_listitem_set_label2_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT char* kodi_gui_listitem_get_art(KODI_GUI_LISTITEM_HANDLE handle, const char* type) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_listitem_get_art_v1; /* Autogenerated */
typedef std::tuple<std::string> msgParent_OUT_kodi_gui_listitem_get_art_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT void kodi_gui_listitem_set_art(KODI_GUI_LISTITEM_HANDLE handle, const char* type, const char* image) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, std::string, std::string> msgParent__IN_kodi_gui_listitem_set_art_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_listitem_set_art_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT char* kodi_gui_listitem_get_path(KODI_GUI_LISTITEM_HANDLE handle) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_listitem_get_path_v1; /* Autogenerated */
typedef std::tuple<std::string> msgParent_OUT_kodi_gui_listitem_get_path_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT void kodi_gui_listitem_set_path(KODI_GUI_LISTITEM_HANDLE handle, const char* path) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_listitem_set_path_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_listitem_set_path_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT char* kodi_gui_listitem_get_property(KODI_GUI_LISTITEM_HANDLE handle, const char* key) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, std::string> msgParent__IN_kodi_gui_listitem_get_property_v1; /* Autogenerated */
typedef std::tuple<std::string> msgParent_OUT_kodi_gui_listitem_get_property_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT void kodi_gui_listitem_set_property(KODI_GUI_LISTITEM_HANDLE handle, const char* key, const char* value) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, std::string, std::string> msgParent__IN_kodi_gui_listitem_set_property_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_listitem_set_property_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT void kodi_gui_listitem_select(KODI_GUI_LISTITEM_HANDLE handle, bool select) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue, bool> msgParent__IN_kodi_gui_listitem_select_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_listitem_select_v1; /* Autogenerated */
// Original API call: ATTR_DLL_EXPORT bool kodi_gui_listitem_is_selected(KODI_GUI_LISTITEM_HANDLE handle) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_listitem_is_selected_v1; /* Autogenerated */
typedef std::tuple<bool> msgParent_OUT_kodi_gui_listitem_is_selected_v1; /* Autogenerated */
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES_END>---*/
// clang-format on

//==============================================================================

typedef enum funcChild_gui_list_item_h : int
{
  funcChild_gui_list_item_h_dummy
} funcChild_gui_list_item_h;

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES>---*/
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES_END>---*/
// clang-format on

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
