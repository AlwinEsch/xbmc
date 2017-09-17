#pragma once
/*
 *      Copyright (C) 2010-2015 Team KODI
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

#include <stddef.h>

#include "AddonToKodi.h"

#define DEFAULT_SHARED_MEM_SIZE 10*1024

struct apiShareData;

class CBinaryAddonSharedMemory
{
public:
  CBinaryAddonSharedMemory(size_t size = DEFAULT_SHARED_MEM_SIZE);
  virtual ~CBinaryAddonSharedMemory() = default;

  virtual bool CreateSharedMemory() = 0;
  virtual void DestroySharedMemory() = 0;

  virtual bool Lock_AddonToKodi_Addon() = 0;
  virtual void Unlock_AddonToKodi_Kodi() = 0;

  virtual bool Lock_KodiToAddon_Addon() = 0;
  virtual void Unlock_KodiToAddon_Kodi() = 0;
  virtual void Unlock_KodiToAddon_Addon() = 0;

  apiShareData* m_sharedMem_AddonToKodi;
  apiShareData* m_sharedMem_KodiToAddon;

protected:
  int m_randomConnectionNumber;
  size_t m_sharedMem_Size;
};
