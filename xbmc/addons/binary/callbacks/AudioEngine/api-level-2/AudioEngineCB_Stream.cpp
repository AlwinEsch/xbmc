/*
 *      Copyright (C) 2015 Team KODI
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

#include "AudioEngineCB_Stream.h"
#include "AddonCallbacksAudioEngine.h"

#include "cores/AudioEngine/AEFactory.h"
#include "cores/AudioEngine/Interfaces/AEStream.h"
#include "cores/AudioEngine/Utils/AEChannelData.h"
#include "utils/log.h"

using namespace ADDON;

namespace AudioEngineLIB
{
namespace V2
{

  CAudioEngineCB_Stream::CAudioEngineCB_Stream()
  {

  }

  void CAudioEngineCB_Stream::Init(CB_AudioEngineLib_Stream *callbacks)
  {
    callbacks->AEStream_GetSpace              = AEStream_GetSpace;
    callbacks->AEStream_AddData               = AEStream_AddData;
    callbacks->AEStream_GetDelay              = AEStream_GetDelay;
    callbacks->AEStream_IsBuffering           = AEStream_IsBuffering;
    callbacks->AEStream_GetCacheTime          = AEStream_GetCacheTime;
    callbacks->AEStream_GetCacheTotal         = AEStream_GetCacheTotal;
    callbacks->AEStream_Pause                 = AEStream_Pause;
    callbacks->AEStream_Resume                = AEStream_Resume;
    callbacks->AEStream_Drain                 = AEStream_Drain;
    callbacks->AEStream_IsDraining            = AEStream_IsDraining;
    callbacks->AEStream_IsDrained             = AEStream_IsDrained;
    callbacks->AEStream_Flush                 = AEStream_Flush;
    callbacks->AEStream_GetVolume             = AEStream_GetVolume;
    callbacks->AEStream_SetVolume             = AEStream_SetVolume;
    callbacks->AEStream_GetAmplification      = AEStream_GetAmplification;
    callbacks->AEStream_SetAmplification      = AEStream_SetAmplification;
    callbacks->AEStream_GetFrameSize          = AEStream_GetFrameSize;
    callbacks->AEStream_GetChannelCount       = AEStream_GetChannelCount;
    callbacks->AEStream_GetSampleRate         = AEStream_GetSampleRate;
    callbacks->AEStream_GetEncodedSampleRate  = AEStream_GetEncodedSampleRate;
    callbacks->AEStream_GetDataFormat         = AEStream_GetDataFormat;
    callbacks->AEStream_GetResampleRatio      = AEStream_GetResampleRatio;
    callbacks->AEStream_SetResampleRatio      = AEStream_SetResampleRatio;
    callbacks->AEStream_Discontinuity         = AEStream_Discontinuity;
  }

  unsigned int CAudioEngineCB_Stream::AEStream_GetSpace(void *AddonData, AEStreamHandle *StreamHandle)
  {
    if (!AddonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return 0;
    }

    return ((IAEStream*)StreamHandle)->GetSpace();
  }

  unsigned int CAudioEngineCB_Stream::AEStream_AddData(void *AddonData, AEStreamHandle *StreamHandle, uint8_t* const *Data, unsigned int Offset, unsigned int Frames)
  {
    if (!AddonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return 0;
    }

    return ((IAEStream*)StreamHandle)->AddData(Data, Offset, Frames);
  }

  double CAudioEngineCB_Stream::AEStream_GetDelay(void *AddonData, AEStreamHandle *StreamHandle)
  {
    if (!AddonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return -1.0;
    }

    return ((IAEStream*)StreamHandle)->GetDelay();
  }

  bool CAudioEngineCB_Stream::AEStream_IsBuffering(void *AddonData, AEStreamHandle *StreamHandle)
  {
    if (!AddonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return false;
    }

    return ((IAEStream*)StreamHandle)->IsBuffering();
  }

  double CAudioEngineCB_Stream::AEStream_GetCacheTime(void *AddonData, AEStreamHandle *StreamHandle)
  {
    if (!AddonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return -1.0;
    }

    return ((IAEStream*)StreamHandle)->GetCacheTime();
  }

  double CAudioEngineCB_Stream::AEStream_GetCacheTotal(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return -1.0;
    }

    return ((IAEStream*)StreamHandle)->GetCacheTotal();
  }

  void CAudioEngineCB_Stream::AEStream_Pause(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return;
    }

    ((IAEStream*)StreamHandle)->Pause();
  }

  void CAudioEngineCB_Stream::AEStream_Resume(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return;
    }

    ((IAEStream*)StreamHandle)->Resume();
  }

  void CAudioEngineCB_Stream::AEStream_Drain(void *AddonData, AEStreamHandle *StreamHandle, bool Wait)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return;
    }

    ((IAEStream*)StreamHandle)->Drain(Wait);
  }

  bool CAudioEngineCB_Stream::AEStream_IsDraining(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return false;
    }

    return ((IAEStream*)StreamHandle)->IsDraining();
  }

  bool CAudioEngineCB_Stream::AEStream_IsDrained(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return false;
    }

    return ((IAEStream*)StreamHandle)->IsDrained();
  }

  void CAudioEngineCB_Stream::AEStream_Flush(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return;
    }

    ((IAEStream*)StreamHandle)->Flush();
  }

  float CAudioEngineCB_Stream::AEStream_GetVolume(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return -1.0f;
    }

    return ((IAEStream*)StreamHandle)->GetVolume();
  }

  void  CAudioEngineCB_Stream::AEStream_SetVolume(void *AddonData, AEStreamHandle *StreamHandle, float Volume)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return;
    }

    ((IAEStream*)StreamHandle)->SetVolume(Volume);
  }

  float CAudioEngineCB_Stream::AEStream_GetAmplification(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return -1.0f;
    }

    return ((IAEStream*)StreamHandle)->GetAmplification();
  }

  void CAudioEngineCB_Stream::AEStream_SetAmplification(void *AddonData, AEStreamHandle *StreamHandle, float Amplify)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return;
    }

    ((IAEStream*)StreamHandle)->SetAmplification(Amplify);
  }

  const unsigned int CAudioEngineCB_Stream::AEStream_GetFrameSize(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return 0;
    }

    return ((IAEStream*)StreamHandle)->GetFrameSize();
  }

  const unsigned int CAudioEngineCB_Stream::AEStream_GetChannelCount(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return 0;
    }

    return ((IAEStream*)StreamHandle)->GetChannelCount();
  }

  const unsigned int CAudioEngineCB_Stream::AEStream_GetSampleRate(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return 0;
    }

    return ((IAEStream*)StreamHandle)->GetSampleRate();
  }

  const unsigned int CAudioEngineCB_Stream::AEStream_GetEncodedSampleRate(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return 0;
    }

    return ((IAEStream*)StreamHandle)->GetEncodedSampleRate();
  }

  const AEDataFormat CAudioEngineCB_Stream::AEStream_GetDataFormat(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return AE_FMT_INVALID;
    }

    return ((IAEStream*)StreamHandle)->GetDataFormat();
  }

  double CAudioEngineCB_Stream::AEStream_GetResampleRatio(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return -1.0f;
    }

    return ((IAEStream*)StreamHandle)->GetResampleRatio();
  }

  bool CAudioEngineCB_Stream::AEStream_SetResampleRatio(void *AddonData, AEStreamHandle *StreamHandle, double Ratio)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return false;
    }

    return ((IAEStream*)StreamHandle)->SetResampleRatio(Ratio);
  }

  void CAudioEngineCB_Stream::AEStream_Discontinuity(void *AddonData, AEStreamHandle *StreamHandle)
  {
    // prevent compiler warnings
    void *addonData = AddonData;
    if (!addonData || !StreamHandle)
    {
      CLog::Log(LOGERROR, "libKODI_audioengine - %s - invalid stream data", __FUNCTION__);
      return;
    }

    ((IAEStream*)StreamHandle)->Discontinuity();
  }

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
