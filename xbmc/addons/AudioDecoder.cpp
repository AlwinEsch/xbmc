/*
 *  Copyright (C) 2013 Arne Morten Kvarving
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "AudioDecoder.h"

// Devkit API interface
#include "interface/api/addon-instance/audiodecoder.h"
#include "interface/api/audio_engine.h"

// Kodi
#include "FileItem.h"
#include "cores/AudioEngine/Utils/AEUtil.h"
#include "music/tags/MusicInfoTag.h"
#include "music/tags/TagLoaderTagLib.h"
#include "utils/log.h"

using namespace KODI::ADDONS::INTERFACE;

namespace ADDON
{

CAudioDecoder::CAudioDecoder(const AddonInfoPtr& addonInfo)
  : IAddonInstanceHandler(ADDON_INSTANCE_AUDIODECODER, addonInfo)
{
  m_CodecName = addonInfo->Type(ADDON_AUDIODECODER)->GetValue("@name").asString();
  m_strExt = m_CodecName + "stream";
  m_hasTags = addonInfo->Type(ADDON_AUDIODECODER)->GetValue("@tags").asBoolean();
}

CAudioDecoder::~CAudioDecoder()
{
  DestroyInstance(m_addonInstance);
}

bool CAudioDecoder::CreateDecoder()
{
  return CreateInstance(this, m_addonInstance) == ADDON_STATUS_OK;
}

bool CAudioDecoder::Init(const CFileItem& file, unsigned int filecache)
{
  /// for replaygain
  /// @todo About audio decoder in most cases Kodi's one not work, add fallback
  /// to use addon if this fails. Need API change about addons music info tag!
  CTagLoaderTagLib tag;
  tag.Load(file.GetDynPath(), XFILE::CMusicFileDirectory::m_tag, nullptr);

  int channels = -1;
  int sampleRate = -1;
  AudioEngineDataFormat addonFormat = AUDIOENGINE_FMT_INVALID;

  AudioEngineChannel channelList[AUDIOENGINE_CH_MAX] = {AUDIOENGINE_CH_NULL};
  bool ret = m_ifc->kodi_addoninstance_audiodecoder_h->kodi_addon_audiodecoder_init_v1(
      m_addonInstance, file.GetDynPath().c_str(), filecache, &channels, &sampleRate, &m_bitsPerSample,
      &m_TotalTime, &m_bitRate, &addonFormat, channelList);
  if (ret)
  {
    if (channels <= 0 || sampleRate <= 0 || addonFormat == AUDIOENGINE_FMT_INVALID)
    {
      CLog::Log(LOGERROR,
                "CAudioDecoder::{} - Addon '{}' returned true without set of needed values",
                __func__, ID());
      return false;
    }

    m_format.m_dataFormat = TranslateAEFormatToKodi(addonFormat);
    m_format.m_sampleRate = sampleRate;
    if (channelList[0] != AUDIOENGINE_CH_NULL)
    {
      CAEChannelInfo layout;
      for (const auto& channel : channelList)
      {
        if (channel == AUDIOENGINE_CH_NULL)
          break;
        layout += TranslateAEChannelToKodi(channel);
      }

      m_format.m_channelLayout = layout;
    }
    else
      m_format.m_channelLayout = CAEUtil::GuessChLayout(channels);
  }

  return ret;
}

int CAudioDecoder::ReadPCM(uint8_t* buffer, size_t size, size_t* actualsize)
{
  return m_ifc->kodi_addoninstance_audiodecoder_h->kodi_addon_audiodecoder_read_pcm_v1(m_addonInstance, buffer, size, actualsize);
}

bool CAudioDecoder::Seek(int64_t time)
{
  m_ifc->kodi_addoninstance_audiodecoder_h->kodi_addon_audiodecoder_seek_v1(m_addonInstance, time);
  return true;
}

bool CAudioDecoder::Load(const std::string& fileName,
                         MUSIC_INFO::CMusicInfoTag& tag,
                         EmbeddedArt* art)
{
  AUDIODECODER_INFO_TAG ifcTag = {0};
  bool ret = m_ifc->kodi_addoninstance_audiodecoder_h->kodi_addon_audiodecoder_read_tag_v1(m_addonInstance, fileName.c_str(), &ifcTag);
  if (ret)
  {
    if (ifcTag.title)
    {
      tag.SetTitle(ifcTag.title);
      free(ifcTag.title);
    }
    if (ifcTag.artist)
    {
      tag.SetArtist(ifcTag.artist);
      free(ifcTag.artist);
    }
    if (ifcTag.album)
    {
      tag.SetAlbum(ifcTag.album);
      free(ifcTag.album);
    }
    if (ifcTag.album_artist)
    {
      tag.SetAlbumArtist(ifcTag.album_artist);
      free(ifcTag.album_artist);
    }
    if (ifcTag.media_type)
    {
      tag.SetType(ifcTag.media_type);
      free(ifcTag.media_type);
    }
    if (ifcTag.genre)
    {
      tag.SetGenre(ifcTag.genre);
      free(ifcTag.genre);
    }
    tag.SetDuration(ifcTag.duration);
    tag.SetTrackNumber(ifcTag.track);
    tag.SetDiscNumber(ifcTag.disc);
    if (ifcTag.disc_subtitle)
    {
      tag.SetDiscSubtitle(ifcTag.disc_subtitle);
      free(ifcTag.disc_subtitle);
    }
    tag.SetTotalDiscs(ifcTag.disc_total);
    if (ifcTag.release_date)
    {
      tag.SetReleaseDate(ifcTag.release_date);
      free(ifcTag.release_date);
    }
    if (ifcTag.lyrics)
    {
      tag.SetLyrics(ifcTag.lyrics);
      free(ifcTag.lyrics);
    }
    tag.SetSampleRate(ifcTag.samplerate);
    tag.SetNoOfChannels(ifcTag.channels);
    tag.SetBitRate(ifcTag.bitrate);
    if (ifcTag.comment)
    {
      tag.SetComment(ifcTag.comment);
      free(ifcTag.comment);
    }
  }

  return ret;
}

int CAudioDecoder::GetTrackCount(const std::string& strPath)
{
  int result = m_ifc->kodi_addoninstance_audiodecoder_h->kodi_addon_audiodecoder_track_count_v1(m_addonInstance, strPath.c_str());
  if (result > 1)
  {
    if (m_hasTags)
    {
      if (!Load(strPath, XFILE::CMusicFileDirectory::m_tag, nullptr))
        return 0;
    }
    else
      XFILE::CMusicFileDirectory::m_tag.SetTitle(CURL(strPath).GetFileNameWithoutPath());
    XFILE::CMusicFileDirectory::m_tag.SetLoaded(true);
  }

  return result;
}

} /* namespace ADDON */
