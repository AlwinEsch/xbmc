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

  inline kodi_codec_t CAddOnLib_Codec::GetCodecByName(const std::string &strCodecName)
  {
    return CAddonLib::g_libKODI_Internal->GetCodecByName(strCodecName.c_str());
  }

  inline DemuxPacket* CAddOnLib_Codec::AllocateDemuxPacket(int iDataSize)
  {
    return CAddonLib::g_libKODI_Internal->AllocateDemuxPacket(iDataSize);
  }

  inline void CAddOnLib_Codec::FreeDemuxPacket(DemuxPacket* pPacket)
  {
    return CAddonLib::g_libKODI_Internal->FreeDemuxPacket(pPacket);
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
