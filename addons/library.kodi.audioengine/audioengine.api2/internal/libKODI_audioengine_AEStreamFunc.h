#pragma once
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

namespace AudioEngineLIB
{
namespace V2
{

  inline CAddonAEStream::CAddonAEStream(
      AEDataFormat        DataFormat,
      unsigned int        SampleRate,
      unsigned int        EncodedSampleRate,
      CAEChannelInfo&     ChannelLayout,
      unsigned int        Options)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_Callbacks(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    m_StreamHandle = m_Callbacks->make_stream(m_Handle, DataFormat, SampleRate, EncodedSampleRate, ChannelLayout.m_channels, Options);
    if (!m_StreamHandle)
      fprintf(stderr, "libKODI_audioengine-ERROR: make_stream failed!\n");
  }

  inline CAddonAEStream::~CAddonAEStream()
  {
    m_Callbacks->free_stream(m_Handle, m_StreamHandle);
  }

  inline unsigned int CAddonAEStream::GetSpace()
  {
    return m_Callbacks->Stream.AEStream_GetSpace(m_AddonHandle, m_StreamHandle);
  }

  inline unsigned int CAddonAEStream::AddData(uint8_t* const *Data, unsigned int Offset, unsigned int Frames)
  {
    return m_Callbacks->Stream.AEStream_AddData(m_AddonHandle, m_StreamHandle, Data, Offset, Frames);
  }

  inline double CAddonAEStream::GetDelay()
  {
    return m_Callbacks->Stream.AEStream_GetDelay(m_AddonHandle, m_StreamHandle);
  }

  inline bool CAddonAEStream::IsBuffering()
  {
    return m_Callbacks->Stream.AEStream_IsBuffering(m_AddonHandle, m_StreamHandle);
  }

  inline double CAddonAEStream::GetCacheTime()
  {
    return m_Callbacks->Stream.AEStream_GetCacheTime(m_AddonHandle, m_StreamHandle);
  }

  inline double CAddonAEStream::GetCacheTotal()
  {
    return m_Callbacks->Stream.AEStream_GetCacheTotal(m_AddonHandle, m_StreamHandle);
  }

  inline void CAddonAEStream::Pause()
  {
    return m_Callbacks->Stream.AEStream_Pause(m_AddonHandle, m_StreamHandle);
  }

  inline void CAddonAEStream::Resume()
  {
    return m_Callbacks->Stream.AEStream_Resume(m_AddonHandle, m_StreamHandle);
  }

  inline void CAddonAEStream::Drain(bool Wait)
  {
    return m_Callbacks->Stream.AEStream_Drain(m_AddonHandle, m_StreamHandle, Wait);
  }

  inline bool CAddonAEStream::IsDraining()
  {
    return m_Callbacks->Stream.AEStream_IsDraining(m_AddonHandle, m_StreamHandle);
  }

  inline bool CAddonAEStream::IsDrained()
  {
    return m_Callbacks->Stream.AEStream_IsDrained(m_AddonHandle, m_StreamHandle);
  }

  inline void CAddonAEStream::Flush()
  {
    return m_Callbacks->Stream.AEStream_Flush(m_AddonHandle, m_StreamHandle);
  }

  inline float CAddonAEStream::GetVolume()
  {
    return m_Callbacks->Stream.AEStream_GetVolume(m_AddonHandle, m_StreamHandle);
  }

  inline void CAddonAEStream::SetVolume(float Volume)
  {
    return m_Callbacks->Stream.AEStream_SetVolume(m_AddonHandle, m_StreamHandle, Volume);
  }

  inline float CAddonAEStream::GetAmplification()
  {
    return m_Callbacks->Stream.AEStream_GetAmplification(m_AddonHandle, m_StreamHandle);
  }

  inline void CAddonAEStream::SetAmplification(float Amplify)
  {
    return m_Callbacks->Stream.AEStream_SetAmplification(m_AddonHandle, m_StreamHandle, Amplify);
  }

  inline const unsigned int CAddonAEStream::GetFrameSize() const
  {
    return m_Callbacks->Stream.AEStream_GetFrameSize(m_AddonHandle, m_StreamHandle);
  }

  inline const unsigned int CAddonAEStream::GetChannelCount() const
  {
    return m_Callbacks->Stream.AEStream_GetChannelCount(m_AddonHandle, m_StreamHandle);
  }

  inline const unsigned int CAddonAEStream::GetSampleRate() const
  {
    return m_Callbacks->Stream.AEStream_GetSampleRate(m_AddonHandle, m_StreamHandle);
  }

  inline const unsigned int CAddonAEStream::GetEncodedSampleRate() const
  {
    return m_Callbacks->Stream.AEStream_GetEncodedSampleRate(m_AddonHandle, m_StreamHandle);
  }

  inline const AEDataFormat CAddonAEStream::GetDataFormat() const
  {
    return m_Callbacks->Stream.AEStream_GetDataFormat(m_AddonHandle, m_StreamHandle);
  }

  inline double CAddonAEStream::GetResampleRatio()
  {
    return m_Callbacks->Stream.AEStream_GetResampleRatio(m_AddonHandle, m_StreamHandle);
  }

  inline bool CAddonAEStream::SetResampleRatio(double Ratio)
  {
    return m_Callbacks->Stream.AEStream_SetResampleRatio(m_AddonHandle, m_StreamHandle, Ratio);
  }

  inline void CAddonAEStream::Discontinuity()
  {
    return m_Callbacks->Stream.AEStream_Discontinuity(m_AddonHandle, m_StreamHandle);
  }

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
