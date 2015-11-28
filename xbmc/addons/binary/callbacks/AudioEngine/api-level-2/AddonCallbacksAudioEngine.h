#pragma once
/*
 *      Copyright (C) 2014 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "system.h"
#include "audioengine.api2/AudioEngineLib.h"

#include "addons/binary/callbacks/IAddonCallback.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "addons/include/kodi_audioengine_types.h"

#include "AudioEngineCB_Stream.h"

namespace ActiveAE
{
  class CActiveAEDSPAddon;
}

namespace AudioEngineLIB
{
namespace V2
{

/*!
 * Callbacks for Kodi's AudioEngine.
 */
class CAddonCallbacksAudioEngine
  : public ADDON::IAddonCallback,
    private CAudioEngineCB_Stream
{
public:
  CAddonCallbacksAudioEngine(ADDON::CAddon* Addon);
  ~CAddonCallbacksAudioEngine();

  static int APILevel() { return m_apiLevel; }
  static std::string Version() { return m_version; }

  /*!
   * @return The callback table.
   */
  CB_AudioEngineLib *GetCallbacks() { return m_callbacks; }

  static void add_dsp_menu_hook(
        void*                       hdl,
        AE_DSP_MENUHOOK*            hook);

  static void remove_dsp_menu_hook(
        void*                       hdl,
        AE_DSP_MENUHOOK*            hook);

  static void register_dsp_mode(
        void*                       hdl,
        AE_DSP_MODES::AE_DSP_MODE*  mode);

  static void unregister_dsp_Mode(
        void*                       hdl,
        AE_DSP_MODES::AE_DSP_MODE*  mode);

  static AEStreamHandle* make_stream(
        void*                       hdl,
        AEDataFormat                DataFormat,
        unsigned int                SampleRate,
        unsigned int                EncodedSampleRate,
        enum AEChannel*             Channels,
        unsigned int                Options);

  static void free_stream(
        void*                       hdl,
        AEStreamHandle*             StreamHandle);

  static bool get_current_sink_format(
        void*                       hdl,
        AudioEngineFormat*          SinkFormat);

private:
  static constexpr const int   m_apiLevel = 2;
  static constexpr const char* m_version  = "0.0.1";

  static ActiveAE::CActiveAEDSPAddon *GetAudioDSPAddon(void *hdl);

  CB_AudioEngineLib   *m_callbacks; /*!< callback addresses */
};

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
