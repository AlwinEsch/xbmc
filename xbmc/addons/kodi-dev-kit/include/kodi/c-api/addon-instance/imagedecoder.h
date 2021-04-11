/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_ADDONINSTANCE_IMAGEDECODER_H
#define C_API_ADDONINSTANCE_IMAGEDECODER_H

#include "../addon_base.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* KODI_ADDON_IMAGEDECODER_HDL;

  typedef enum ADDON_IMG_FMT
  {
    ADDON_IMG_FMT_A8R8G8B8 = 1,
    ADDON_IMG_FMT_A8 = 2,
    ADDON_IMG_FMT_RGBA8 = 3,
    ADDON_IMG_FMT_RGB8 = 4
  } ADDON_IMG_FMT;

  typedef KODI_ADDON_IMAGEDECODER_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_IMAGEDECODER_CREATE_V1)(KODI_OWN_HDL kodi_hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_IMAGEDECODER_DESTROY_V1)(KODI_ADDON_IMAGEDECODER_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_IMAGEDECODER_LOAD_IMAGE_FROM_MEMORY_V1)(
      KODI_ADDON_IMAGEDECODER_HDL hdl, const uint8_t* buffer, size_t buf_size, unsigned int* width, unsigned int* height);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_IMAGEDECODER_DECODE_V1)(KODI_ADDON_IMAGEDECODER_HDL hdl,
                                                               uint8_t* pixels,
                                                               size_t pixels_size,
                                                               unsigned int width,
                                                               unsigned int height,
                                                               unsigned int pitch,
                                                               enum ADDON_IMG_FMT format);

  typedef struct KODI_ADDON_IMAGEDECODER_FUNC
  {
    PFN_KODI_ADDON_IMAGEDECODER_CREATE_V1 create;
    PFN_KODI_ADDON_IMAGEDECODER_DESTROY_V1 destroy;
    PFN_KODI_ADDON_IMAGEDECODER_LOAD_IMAGE_FROM_MEMORY_V1 load_image_from_memory;
    PFN_KODI_ADDON_IMAGEDECODER_DECODE_V1 decode;
  } KODI_ADDON_IMAGEDECODER_FUNC;

  ATTR_DLL_EXPORT char* kodi_addon_imagedecoder_mimetype(KODI_OWN_HDL hdl) __INTRODUCED_IN_KODI(1);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_IMAGEDECODER_H */
