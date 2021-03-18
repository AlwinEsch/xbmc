/*
 *  Copyright (C) 2013 Arne Morten Kvarving
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ImageDecoder.h"

// Devkit API interface
#include "interface/api/addon-instance/imagedecoder.h"

// Kodi
#include "guilib/TextureFormats.h"

static const std::map<int, ADDON_IMG_FMT> KodiToAddonFormat = {
    {XB_FMT_A8R8G8B8, ADDON_IMG_FMT_A8R8G8B8},
    {XB_FMT_A8, ADDON_IMG_FMT_A8},
    {XB_FMT_RGBA8, ADDON_IMG_FMT_RGBA8},
    {XB_FMT_RGB8, ADDON_IMG_FMT_RGB8}};

namespace ADDON
{

CImageDecoder::CImageDecoder(const AddonInfoPtr& addonInfo, const std::string& mimetype)
  : IAddonInstanceHandler(ADDON_INSTANCE_IMAGEDECODER, addonInfo),
    m_mimetype(mimetype)
{
}

CImageDecoder::~CImageDecoder()
{
  DestroyInstance(m_addonInstance);
}

bool CImageDecoder::LoadImageFromMemory(unsigned char* buffer, unsigned int bufSize,
                                        unsigned int width, unsigned int height)
{
  m_width = width;
  m_height = height;
  return m_ifc->kodi_addoninstance_imagedecoder_h->kodi_addon_imagedecoder_load_image_from_memory_v1(m_addonInstance, buffer, bufSize, &m_width, &m_height);
}

bool CImageDecoder::Decode(unsigned char* const pixels, unsigned int width,
                           unsigned int height, unsigned int pitch,
                           unsigned int format)
{
  auto it = KodiToAddonFormat.find(format & XB_FMT_MASK);
  if (it == KodiToAddonFormat.end())
    return false;

  size_t size;
  switch (format)
  {
    case XB_FMT_A8:
      size = width * height * sizeof(uint8_t) * 1;
      break;
    case XB_FMT_RGB8:
      size = width * height * sizeof(uint8_t) * 3;
      break;
    case XB_FMT_A8R8G8B8:
    case XB_FMT_RGBA8:
    default:
      size = width * height * sizeof(uint8_t) * 4;
      break;
  }

  bool result = m_ifc->kodi_addoninstance_imagedecoder_h->kodi_addon_imagedecoder_decode_v1(m_addonInstance, pixels, size, width, height, pitch, it->second);
  m_width = width;
  m_height = height;

  return result;
}

bool CImageDecoder::Create()
{
  return (CreateInstance(this, m_addonInstance) == ADDON_STATUS_OK);
}

} /*namespace ADDON*/
