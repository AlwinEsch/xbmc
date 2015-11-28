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

#include "AddonCB_Codec.h"
#include "AddonCallbacksAddon.h"

#include "addons/Addon.h"
#include "cores/dvdplayer/DVDDemuxers/DVDDemuxUtils.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "utils/StringUtils.h"

extern "C" {
#include "libavcodec/avcodec.h"
}

#include <map>
#include <utility>

namespace AddOnLIB
{
namespace V2
{

class CCodecIds
{
public:
  virtual ~CCodecIds(void) {}

  static CCodecIds& GetInstance()
  {
    static CCodecIds _instance;
    return _instance;
  }

  kodi_codec_t GetCodecByName(const char* strCodecName)
  {
    kodi_codec_t retVal = KODI_INVALID_CODEC;
    if (strlen(strCodecName) == 0)
      return retVal;

    std::string strUpperCodecName = strCodecName;
    StringUtils::ToUpper(strUpperCodecName);

    std::map<std::string, kodi_codec_t>::const_iterator it = m_lookup.find(strUpperCodecName);
    if (it != m_lookup.end())
      retVal = it->second;

    return retVal;
  }

private:
  CCodecIds(void)
  {
    // get ids and names
    AVCodec* codec = nullptr;
    kodi_codec_t tmp;
    while ((codec = av_codec_next(codec)))
    {
      if (av_codec_is_decoder(codec))
      {
        tmp.codec_type = (kodi_codec_type_t)codec->type;
        tmp.codec_id   = codec->id;

        std::string strUpperCodecName = codec->name;
        StringUtils::ToUpper(strUpperCodecName);

        m_lookup.insert(std::make_pair(strUpperCodecName, tmp));
      }
    }

    // teletext is not returned by av_codec_next. we got our own decoder
    tmp.codec_type = KODI_CODEC_TYPE_SUBTITLE;
    tmp.codec_id   = AV_CODEC_ID_DVB_TELETEXT;
    m_lookup.insert(std::make_pair("TELETEXT", tmp));

    // rds is not returned by av_codec_next. we got our own decoder
    tmp.codec_type = KODI_CODEC_TYPE_RDS;
    tmp.codec_id   = AV_CODEC_ID_NONE;
    m_lookup.insert(std::make_pair("RDS", tmp));
  }

  std::map<std::string, kodi_codec_t> m_lookup;
};

CAddonCB_Codec::CAddonCB_Codec()
{

}
void CAddonCB_Codec::Init(CB_AddOnLib_Codec *callbacks)
{
  /* write Kodi specific add-on function addresses to the callback table */
  callbacks->get_codec_by_name      = get_codec_by_name;
  callbacks->allocate_demux_packet  = allocate_demux_packet;
  callbacks->free_demux_packet      = free_demux_packet;
}

kodi_codec_t CAddonCB_Codec::get_codec_by_name(void* addonData, const char* strCodecName)
{
  return CCodecIds::GetInstance().GetCodecByName(strCodecName);
}

DemuxPacket* CAddonCB_Codec::allocate_demux_packet(void *addonData, int iDataSize)
{
  return CDVDDemuxUtils::AllocateDemuxPacket(iDataSize);
}

void CAddonCB_Codec::free_demux_packet(void *addonData, DemuxPacket* pPacket)
{
  CDVDDemuxUtils::FreeDemuxPacket(pPacket);
}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
