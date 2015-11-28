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

#include "definations.h"
#include "internal/libKODI_addon_AudioHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{
  class CAddonSoundPlay
  {
  public:
    CAddonSoundPlay(const char *filename);
    virtual ~CAddonSoundPlay(void);

    virtual void Play();
    virtual void Stop();
    virtual bool IsPlaying();
    virtual void SetChannel(audio_channel_t channel);
    virtual audio_channel_t GetChannel();
    virtual void SetVolume(float volume);
    virtual float GetVolume();

    IMPL_ADDONSOUNDPLAY;
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_AudioFunc.h"
