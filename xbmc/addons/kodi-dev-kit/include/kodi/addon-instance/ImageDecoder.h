/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../AddonBase.h"
#include "../c-api/addon-instance/imagedecoder.h"

#ifdef __cplusplus

#include <stdexcept>

namespace kodi
{
namespace addon
{

using ImageFormat = ADDON_IMG_FMT;

class ATTR_DLL_LOCAL CInstanceImageDecoder : public IAddonInstance
{
public:
  explicit CInstanceImageDecoder(KODI_HANDLE instance)
    : IAddonInstance(ADDON_INSTANCE_IMAGEDECODER)
  {
    if (CAddonBase::m_globalSingleInstance != nullptr)
      throw std::logic_error("kodi::addon::CInstanceImageDecoder: Creation of multiple together "
                             "with single instance way is not allowed!");

    SetAddonStruct(instance);
  }

  ~CInstanceImageDecoder() override = default;

  virtual bool LoadImageFromMemory(const uint8_t* buffer,
                                   size_t bufSize,
                                   unsigned int& width,
                                   unsigned int& height) = 0;

  virtual bool Decode(uint8_t* pixels,
                      unsigned int width,
                      unsigned int height,
                      unsigned int pitch,
                      kodi::addon::ImageFormat format) = 0;

  inline std::string MimeType()
  {
    char* mimetype = kodi_addon_imagedecoder_mimetype(m_kodi);
    if (!mimetype)
      return "";

    std::string ret = mimetype;
    free(mimetype);
    return ret;
  }

private:
  void SetAddonStruct(KODI_HANDLE instance)
  {
    if (instance == nullptr)
      throw std::logic_error("kodi::addon::CInstanceImageDecoder: Creation with empty addon "
                             "structure not allowed, table must be given from Kodi!");

    KODI_INSTANCE_HDL* instanceKodi = static_cast<KODI_INSTANCE_HDL*>(instance);
    instanceKodi->type = ADDON_INSTANCE_IMAGEDECODER;
    instanceKodi->instance = this;
    instanceKodi->imagedecoder->load_image_from_memory = ADDON_LoadImageFromMemory;
    instanceKodi->imagedecoder->decode = ADDON_Decode;
  }

  inline static bool ADDON_LoadImageFromMemory(KODI_ADDON_IMAGEDECODER_HDL hdl,
                                               const uint8_t* buffer,
                                               size_t buf_size,
                                               unsigned int* width,
                                               unsigned int* height)
  {
    return static_cast<CInstanceImageDecoder*>(hdl)->LoadImageFromMemory(buffer, buf_size, *width, *height);
  }

  inline static bool ADDON_Decode(KODI_ADDON_IMAGEDECODER_HDL hdl,
                                  uint8_t* pixels,
                                  size_t pixels_size,
                                  unsigned int width,
                                  unsigned int height,
                                  unsigned int pitch,
                                  enum ADDON_IMG_FMT format)
  {
    return static_cast<CInstanceImageDecoder*>(hdl)->Decode(pixels, width, height, pitch, format);
  }

  KODI_OWN_HDL m_kodi;
};

} /* namespace addon */
} /* namespace kodi */
#endif /* __cplusplus */
