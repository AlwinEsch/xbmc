/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#pragma once

#include "../../../../../include/kodi/c-api/gui/controls/rendering.h"
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

typedef void(ATTR_INT_APIENTRYP PFN_INT_KODI_GUI_CONTROLS_RADIO_RENDERING_DESTROY_V1)(
    void*, KODI_GUI_CONTROL_HANDLE);

struct directFuncToKodi_gui_controls_rendering_h
{
  void* thisClassHdl;
  PFN_INT_KODI_GUI_CONTROLS_RADIO_RENDERING_DESTROY_V1 kodi_gui_controls_radio_rendering_destroy_v1;
};

//}}}

// Code here relates to direct API calls without use of shared mem from Kodi to addon.
//{{{


struct directFuncToAddon_gui_controls_rendering_h
{
  void* thisClassHdl;
};

//}}}

typedef enum funcParent_gui_controls_rendering_h : int
{
  funcParent_kodi_gui_controls_radio_rendering_destroy_v1,
} funcParent_gui_controls_rendering_h;

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES>---*/
// Original API call: ATTR_DLL_EXPORT void kodi_gui_controls_radio_rendering_destroy(KODI_GUI_CONTROL_HANDLE handle) __INTRODUCED_IN_KODI(1);
typedef std::tuple<PtrValue> msgParent__IN_kodi_gui_controls_radio_rendering_destroy_v1; /* Autogenerated */
typedef std::tuple<DummyValue> msgParent_OUT_kodi_gui_controls_radio_rendering_destroy_v1; /* Autogenerated */
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES_END>---*/
// clang-format on

//==============================================================================

typedef enum funcChild_gui_controls_rendering_h : int
{
  funcChild_gui_controls_rendering_h_dummy
} funcChild_gui_controls_rendering_h;

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES>---*/
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES_END>---*/
// clang-format on

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
