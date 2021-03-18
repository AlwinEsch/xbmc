/*
 *  Copyright (C) 2013 Arne Morten Kvarving
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "interface/InstanceHandler.h"
#include "guilib/iimage.h"

namespace ADDON
{
  class CImageDecoder : public KODI::ADDONS::INTERFACE::IAddonInstanceHandler,
                        public IImage
  {
  public:
    explicit CImageDecoder(const AddonInfoPtr& addonInfo, const std::string& mimetype);
    ~CImageDecoder() override;

    bool Create();
    const std::string& GetMimeType() const { return m_mimetype; } /*---AUTO_GEN_PARSE<CB:kodi_addon_imagedecoder_mimetype>---*/

    bool CreateThumbnailFromSurface(unsigned char*, unsigned int, unsigned int,
                                    unsigned int, unsigned int, const std::string&,
                                    unsigned char*&, unsigned int&) override { return false; }

    bool LoadImageFromMemory(unsigned char* buffer, unsigned int bufSize,
                             unsigned int width, unsigned int height) override;
    bool Decode(unsigned char* const pixels, unsigned int width,
                unsigned int height, unsigned int pitch,
                unsigned int format) override;

  private:
    const std::string m_mimetype;
    KODI_HANDLE m_addonInstance;
  };

} /*namespace ADDON*/
