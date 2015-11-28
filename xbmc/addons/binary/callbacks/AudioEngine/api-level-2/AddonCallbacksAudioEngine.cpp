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

#include "AddonCallbacksAudioEngine.h"
#include "cores/AudioEngine/AEFactory.h"
#include "cores/AudioEngine/DSPAddons/ActiveAEDSP.h"
#include "cores/AudioEngine/DSPAddons/ActiveAEDSPMode.h"
#include "cores/AudioEngine/Interfaces/AEStream.h"
#include "cores/AudioEngine/Utils/AEChannelData.h"
#include "utils/log.h"
#include "addons/include/kodi_audioengine_types.h"

using namespace ADDON;
using namespace ActiveAE;

namespace AudioEngineLIB
{
namespace V2
{

CAddonCallbacksAudioEngine::CAddonCallbacksAudioEngine(CAddon* addon)
  : ADDON::IAddonCallback(addon, m_apiLevel, m_version),
    m_callbacks(new CB_AudioEngineLib)
{
  m_callbacks->add_dsp_menu_hook        = CAddonCallbacksAudioEngine::add_dsp_menu_hook;
  m_callbacks->remove_dsp_menu_hook     = CAddonCallbacksAudioEngine::remove_dsp_menu_hook;

  m_callbacks->register_dsp_mode        = CAddonCallbacksAudioEngine::register_dsp_mode;
  m_callbacks->unregister_dsp_Mode      = CAddonCallbacksAudioEngine::unregister_dsp_Mode;

  m_callbacks->get_current_sink_format  = CAddonCallbacksAudioEngine::get_current_sink_format;

  m_callbacks->make_stream              = CAddonCallbacksAudioEngine::make_stream;
  m_callbacks->free_stream              = CAddonCallbacksAudioEngine::free_stream;

  CAudioEngineCB_Stream::Init(&m_callbacks->Stream);
}

CAddonCallbacksAudioEngine::~CAddonCallbacksAudioEngine()
{
  /* delete the callback table */
  delete m_callbacks;
}

A_DLLEXPORT CB_AudioEngineLib* AudioEngineLIB_V2_register_level(void *hdl, int level)
{
  CB_AudioEngineLib *cb = nullptr;
  if (!hdl)
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - is called with NULL handle !!!", __FUNCTION__);
  else
  {
    cb = static_cast<CB_AudioEngineLib*>(CAddonCallbacks::AudioEngineLib_RegisterLevel(((AddonCB*)hdl)->addonData, level));
    if (!cb)
      CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - can't get callback table from Kodi !!!", __FUNCTION__);
  }
  return cb;
}

A_DLLEXPORT bool AudioEngineLIB_V2_unregister(void *hdl, void* cb)
{
  if (hdl && cb)
    CAddonCallbacks::AudioEngineLib_UnRegisterMe(((AddonCB*)hdl)->addonData, ((CB_AudioEngineLib*)cb));
}
/*\_____________________________________________________________________________
\*/
CActiveAEDSPAddon *CAddonCallbacksAudioEngine::GetAudioDSPAddon(void *hdl)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
  if (!addon || !addon->AudioEngineLib_GetHelper())
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - called with a null pointer", __FUNCTION__);
    return NULL;
  }

  return dynamic_cast<CActiveAEDSPAddon*>(static_cast<CAddonCallbacksAudioEngine*>(addon->AudioEngineLib_GetHelper())->m_addon);
}
/*\_____________________________________________________________________________
\*/
void CAddonCallbacksAudioEngine::add_dsp_menu_hook(void *hdl, AE_DSP_MENUHOOK *hook)
{
  CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
  if (!hook || !addon)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - invalid handler data", __FUNCTION__);
    return;
  }

  AE_DSP_MENUHOOKS *hooks = addon->GetMenuHooks();
  if (hooks)
  {
    AE_DSP_MENUHOOK hookInt;
    hookInt.iHookId            = hook->iHookId;
    hookInt.iLocalizedStringId = hook->iLocalizedStringId;
    hookInt.category           = hook->category;
    hookInt.iRelevantModeId    = hook->iRelevantModeId;
    hookInt.bNeedPlayback      = hook->bNeedPlayback;

    /* add this new hook */
    hooks->push_back(hookInt);
  }
}

void CAddonCallbacksAudioEngine::remove_dsp_menu_hook(void *hdl, AE_DSP_MENUHOOK *hook)
{
  CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
  if (!hook || !addon)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - invalid handler data", __FUNCTION__);
    return;
  }

  AE_DSP_MENUHOOKS *hooks = addon->GetMenuHooks();
  if (hooks)
  {
    for (unsigned int i = 0; i < hooks->size(); i++)
    {
      if (hooks->at(i).iHookId == hook->iHookId)
      {
        /* remove this hook */
        hooks->erase(hooks->begin()+i);
        break;
      }
    }
  }
}
/*\_____________________________________________________________________________
\*/
void CAddonCallbacksAudioEngine::register_dsp_mode(void* hdl, AE_DSP_MODES::AE_DSP_MODE* mode)
{
  CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
  if (!mode || !addon)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - invalid mode data", __FUNCTION__);
    return;
  }

  CActiveAEDSPMode transferMode(*mode, addon->GetID());
  int idMode = transferMode.AddUpdate();
  mode->iUniqueDBModeId = idMode;

  if (idMode > AE_DSP_INVALID_ADDON_ID)
  {
	  CLog::Log(LOGDEBUG, "CAddonCallbacksAudioEngine - %s - successfull registered mode %s of %s adsp-addon", __FUNCTION__, mode->strModeName, addon->Name().c_str());
  }
  else
  {
	  CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - failed to register mode %s of %s adsp-addon", __FUNCTION__, mode->strModeName, addon->Name().c_str());
  }
}

void CAddonCallbacksAudioEngine::unregister_dsp_Mode(void* hdl, AE_DSP_MODES::AE_DSP_MODE* mode)
{
  CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
  if (!mode || !addon)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - invalid mode data", __FUNCTION__);
    return;
  }

  CActiveAEDSPMode transferMode(*mode, addon->GetID());
  transferMode.Delete();
}
/*\_____________________________________________________________________________
\*/

AEStreamHandle* CAddonCallbacksAudioEngine::make_stream(void* hdl, AEDataFormat DataFormat, unsigned int SampleRate, unsigned int EncodedSampleRate, enum AEChannel *Channels, unsigned int Options)
{
  if (!Channels)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - Invalid input! Channels is a NULL pointer!", __FUNCTION__);
    return NULL;
  }

  CAEChannelInfo channelInfo(Channels);
  return CAEFactory::MakeStream(DataFormat, SampleRate, EncodedSampleRate, channelInfo, Options);
}

void CAddonCallbacksAudioEngine::free_stream(void* hdl, AEStreamHandle *StreamHandle)
{
  if (!StreamHandle)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - invalid stream data", __FUNCTION__);
    return;
  }

  CAEFactory::FreeStream((IAEStream*)StreamHandle);
}

bool CAddonCallbacksAudioEngine::get_current_sink_format(void *hdl, AudioEngineFormat *SinkFormat)
{
  if (!SinkFormat)
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - invalid input data!", __FUNCTION__);
    return false;
  }

  AEAudioFormat AESinkFormat;
  if (!CAEFactory::GetEngine() || !CAEFactory::GetEngine()->GetCurrentSinkFormat(AESinkFormat))
  {
    CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - failed to get current sink format from AE!", __FUNCTION__);
    return false;
  }

  SinkFormat->m_channelCount = AESinkFormat.m_channelLayout.Count();
  for (unsigned int ch = 0; ch < SinkFormat->m_channelCount; ch++)
  {
    SinkFormat->m_channels[ch] = AESinkFormat.m_channelLayout[ch];
  }

  SinkFormat->m_dataFormat   = AESinkFormat.m_dataFormat;
  SinkFormat->m_sampleRate   = AESinkFormat.m_sampleRate;
  SinkFormat->m_encodedRate  = AESinkFormat.m_encodedRate;
  SinkFormat->m_frames       = AESinkFormat.m_frames;
  SinkFormat->m_frameSamples = AESinkFormat.m_frameSamples;
  SinkFormat->m_frameSize    = AESinkFormat.m_frameSize;

  return true;
}


}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
