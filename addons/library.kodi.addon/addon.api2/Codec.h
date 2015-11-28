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
#include "internal/libKODI_addon_CodecHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{
  class CAddOnLib_Codec
  {
  public:
    /*!
     * @brief Get the codec id used by Kodi
     * @param strCodecName The name of the codec
     * @return The codec_id, or a codec_id with 0 values when not supported
     */
    static kodi_codec_t GetCodecByName(const std::string &strCodecName);

    /*!
     * @brief Allocate a demux packet. Free with FreeDemuxPacket
     * @param iDataSize The size of the data that will go into the packet
     * @return The allocated packet
     */
    static DemuxPacket* AllocateDemuxPacket(int iDataSize);

    /*!
     * @brief Free a packet that was allocated with AllocateDemuxPacket
     * @param pPacket The packet to free
     */
    static void FreeDemuxPacket(DemuxPacket* pPacket);
  }; /* class CAddOnLib_Codec */

  /*!
   * Adapter which converts codec names used by several backends into their.
   * FFmpeg equivalents.
   */
  class CodecDescriptor
  {
  public:
    CodecDescriptor(void)
    {
      m_codec.codec_id   = KODI_INVALID_CODEC_ID;
      m_codec.codec_type = KODI_CODEC_TYPE_UNKNOWN;
    }

    CodecDescriptor(kodi_codec_t codec, const char* name)
      : m_codec(codec),
        m_strName(name) {}
    virtual ~CodecDescriptor(void) {}

    const std::string& Name(void) const  { return m_strName; }
    kodi_codec_t Codec(void) const { return m_codec; }

    static CodecDescriptor GetCodecByName(const char* strCodecName)
    {
      CodecDescriptor retVal;
      // some of the backends codec names don't match ffmpeg's, so translate them to something ffmpeg understands
      if (!strcmp(strCodecName, "MPEG2AUDIO"))
        retVal = CodecDescriptor(CAddOnLib_Codec::GetCodecByName("MP2"), strCodecName);
      else if (!strcmp(strCodecName, "MPEGTS"))
        retVal = CodecDescriptor(CAddOnLib_Codec::GetCodecByName("MPEG2VIDEO"), strCodecName);
      else if (!strcmp(strCodecName, "TEXTSUB"))
        retVal = CodecDescriptor(CAddOnLib_Codec::GetCodecByName("TEXT"), strCodecName);
      else
        retVal = CodecDescriptor(CAddOnLib_Codec::GetCodecByName(strCodecName), strCodecName);

      return retVal;
    }

  private:
    kodi_codec_t m_codec;
    std::string  m_strName;
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_CodecFunc.h"
