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

namespace AddOnLIB
{
namespace V2
{
  inline CAddonSoundPlay::CAddonSoundPlay(const char *filename)
   : m_PlayHandle(nullptr),
     m_Handle(g_libKODI_Internal->hdl),
     m_Callbacks(g_libKODI_Internal->cb)
  {
    if (!m_Handle || !m_Callbacks)
      fprintf(stderr, "libKODI_addon-ERROR: CAddonSoundPlay is called with NULL handle !!!\n");
    else
    {
      m_PlayHandle = m_Callbacks->Audio.soundplay_get_handle(m_Handle, filename);
      if (!m_PlayHandle)
        fprintf(stderr, "libKODI_addon-ERROR: CAddonSoundPlay can't get callback table from KODI !!!\n");
    }
  }

  inline CAddonSoundPlay::~CAddonSoundPlay()
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_release_handle(m_Handle, m_PlayHandle);   
  }

  inline void CAddonSoundPlay::Play()
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_play(m_Handle, m_PlayHandle);
  }

  inline void CAddonSoundPlay::Stop()
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_stop(m_Handle, m_PlayHandle);
  }

  inline bool CAddonSoundPlay::IsPlaying()
  {
    if (!m_PlayHandle)
      return false;
    return m_Callbacks->Audio.soundplay_is_playing(m_Handle, m_PlayHandle);
  }

  inline void CAddonSoundPlay::SetChannel(audio_channel_t channel)
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_set_channel(m_Handle, m_PlayHandle, channel);
  }

  inline audio_channel_t CAddonSoundPlay::GetChannel()
  {
    if (!m_PlayHandle)
      return AUDIO_CH_INVALID;
    return m_Callbacks->Audio.soundplay_get_channel(m_Handle, m_PlayHandle);
  }

  inline void CAddonSoundPlay::SetVolume(float volume)
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_set_volume(m_Handle, m_PlayHandle, volume);
  }

  inline float CAddonSoundPlay::GetVolume()
  {
    if (!m_PlayHandle)
      return 0.0f;
    return m_Callbacks->Audio.soundplay_get_volume(m_Handle, m_PlayHandle);
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
