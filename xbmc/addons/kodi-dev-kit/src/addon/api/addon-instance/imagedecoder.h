/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#pragma once

#include "core/IMsgHdl.h"
#include "src/shared/api/addon-instance/imagedecoder.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct directFuncToAddon_addoninstance_imagedecoder_h;
struct directFuncToKodi_addoninstance_imagedecoder_h;

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */

namespace KODI_ADDON
{
namespace INTERNAL
{

class ATTR_DLL_LOCAL CHdl_kodi_addoninstance_imagedecoder_h : public IMsgHdl
{
public:
  CHdl_kodi_addoninstance_imagedecoder_h(AddonIfc* ifc) : IMsgHdl(ifc) {}

  void InitDirect(
      KODI::ADDONS::INTERFACE::directFuncToAddon_addoninstance_imagedecoder_h* ifcToAddon);

#ifndef KODI_INHIBIT_SHARED
  bool HandleMessage(int funcGroup,
                     int func,
                     const msgpack::unpacked& in,
                     msgpack::sbuffer& out) override;
#endif /* !KODI_INHIBIT_SHARED */

  /* Code below becomes on auto generation reused, hand edited parts should included here */
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

  // Calls from Kodi to addon
  static KODI_ADDON_IMAGEDECODER_HDL kodi_addon_imagedecoder_create_v1(
      void* thisClassHdl, KODI_OWN_HDL kodi_hdl); // Added with API 1

  static void kodi_addon_imagedecoder_destroy_v1(
      void* thisClassHdl, KODI_ADDON_IMAGEDECODER_HDL hdl); // Added with API 1

  static bool kodi_addon_imagedecoder_load_image_from_memory_v1(
      void* thisClassHdl,
      KODI_ADDON_IMAGEDECODER_HDL hdl,
      const uint8_t* buffer,
      size_t buf_size,
      unsigned int* width,
      unsigned int* height); // Added with API 1

  static bool kodi_addon_imagedecoder_decode_v1(void* thisClassHdl,
                                                KODI_ADDON_IMAGEDECODER_HDL hdl,
                                                uint8_t* pixels,
                                                size_t pixels_size,
                                                unsigned int width,
                                                unsigned int height,
                                                unsigned int pitch,
                                                enum ADDON_IMG_FMT format); // Added with API 1
};

} /* namespace INTERNAL */
} /* namespace KODI_ADDON */
