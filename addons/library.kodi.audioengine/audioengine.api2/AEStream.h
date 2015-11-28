#pragma once
/*
 *      Copyright (C) 2005-2014 Team KODI
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

#include "internal/libKODI_audioengine_LibHead.h"
#include "internal/libKODI_audioengine_Internal.h"

namespace AudioEngineLIB
{
namespace V2
{

  // Audio Engine Stream Class
  class CAddonAEStream
  {
  public:
    CAddonAEStream(
          AEDataFormat        DataFormat,
          unsigned int        SampleRate,
          unsigned int        EncodedSampleRate,
          CAEChannelInfo&     ChannelLayout,
          unsigned int        Options = 0);
    virtual ~CAddonAEStream();

    /**
    * Returns the amount of space available in the stream
    * @return The number of bytes AddData will consume
    */
    virtual unsigned int GetSpace();

    /**
    * Add planar or interleaved PCM data to the stream
    * @param Data array of pointers to the planes
    * @param Offset to frame in frames
    * @param Frames number of frames
    * @return The number of frames consumed
    */
    virtual unsigned int AddData(uint8_t* const *Data, unsigned int Offset, unsigned int Frames);

    /**
    * Returns the time in seconds that it will take
    * for the next added packet to be heard from the speakers.
    * @return seconds
    */
    virtual double GetDelay();

    /**
    * Returns if the stream is buffering
    * @return True if the stream is buffering
    */
    virtual bool IsBuffering();

    /**
    * Returns the time in seconds that it will take
    * to underrun the cache if no sample is added.
    * @return seconds
    */
    virtual double GetCacheTime();

    /**
    * Returns the total time in seconds of the cache
    * @return seconds
    */
    virtual double GetCacheTotal();

    /**
    * Pauses the stream playback
    */
    virtual void Pause();

    /**
    * Resumes the stream after pausing
    */
    virtual void Resume();

    /**
    * Start draining the stream
    * @note Once called AddData will not consume more data.
    */
    virtual void Drain(bool Wait);

    /**
    * Returns true if the is stream draining
    */
    virtual bool IsDraining();

    /**
    * Returns true if the is stream has finished draining
    */
    virtual bool IsDrained();

    /**
    * Flush all buffers dropping the audio data
    */
    virtual void Flush();

    /**
    * Return the stream's current volume level
    * @return The volume level between 0.0 and 1.0
    */
    virtual float GetVolume();

    /**
    * Set the stream's volume level
    * @param volume The new volume level between 0.0 and 1.0
    */
    virtual void  SetVolume(float Volume);

    /**
    * Gets the stream's volume amplification in linear units.
    * @return The volume amplification factor between 1.0 and 1000.0
    */
    virtual float GetAmplification();

    /**
    * Sets the stream's volume amplification in linear units.
    * @param The volume amplification factor between 1.0 and 1000.0
    */
    virtual void SetAmplification(float Amplify);

    /**
    * Returns the size of one audio frame in bytes (channelCount * resolution)
    * @return The size in bytes of one frame
    */
    virtual const unsigned int GetFrameSize() const;

    /**
    * Returns the number of channels the stream is configured to accept
    * @return The channel count
    */
    virtual const unsigned int GetChannelCount() const;

    /**
    * Returns the stream's sample rate, if the stream is using a dynamic sample
    * rate, this value will NOT reflect any changes made by calls to
    * SetResampleRatio()
    * @return The stream's sample rate (eg, 48000)
    */
    virtual const unsigned int GetSampleRate() const;

    /**
    * Returns the stream's encoded sample rate if the stream is RAW
    * @return The stream's encoded sample rate
    */
    virtual const unsigned int GetEncodedSampleRate() const;

    /**
    * Return the data format the stream has been configured with
    * @return The stream's data format (eg, AE_FMT_S16LE)
    */
    virtual const AEDataFormat GetDataFormat() const;

    /**
    * Return the resample ratio
    * @note This will return an undefined value if the stream is not resampling
    * @return the current resample ratio or undefined if the stream is not
    *         resampling
    */
    virtual double GetResampleRatio();

    /**
    * Sets the resample ratio
    * @note This function may return false if the stream is not resampling, if you
    * wish to use this be sure to set the AESTREAM_FORCE_RESAMPLE option
    * @param ratio the new sample rate ratio, calculated by
    *              ((double)desiredRate / (double)GetSampleRate())
    */
    virtual bool SetResampleRatio(double Ratio);

    /**
    * Sginal a clock change
    */
    virtual void Discontinuity();

    IMPLEMENT_ADDON_AE_STREAM;
  };

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
#include "internal/libKODI_audioengine_AEStramFunc.h"
