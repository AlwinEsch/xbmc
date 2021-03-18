/*
 *  Copyright (C) 2013 Arne Morten Kvarving
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "interface/api/addon-instance/audioencoder.h"
#include "interface/InstanceHandler.h"
#include "cdrip/IEncoder.h"

namespace ADDON
{

  class CAudioEncoder : public IEncoder, public KODI::ADDONS::INTERFACE::IAddonInstanceHandler
  {
  public:
    explicit CAudioEncoder(const AddonInfoPtr& addonInfo);
    ~CAudioEncoder() override = default;

    // Child functions related to IEncoder
    bool Init(AudioEncoderCB& callbacks) override;
    int Encode(int nNumBytesRead, uint8_t* pbtStream) override;
    bool Close() override;

    int Write(const uint8_t* data, int len); /*---AUTO_GEN_PARSE<CB:kodi_addon_audioencoder_write>---*/
    int64_t Seek(int64_t pos, int whence); /*---AUTO_GEN_PARSE<CB:kodi_addon_audioencoder_seek>---*/

  private:
    KODI_HANDLE m_addonInstance;
    AudioEncoderCB m_callbacks;
  };

} /* namespace ADDON */
