/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../AddonBase.h"
#include "../AudioEngine.h"
#include "../c-api/addon-instance/audiodecoder.h"

#ifdef __cplusplus

#include <stdexcept>
#include <string.h>

namespace kodi
{
namespace addon
{

class CInstanceAudioDecoder;

class AudioDecoderInfoTag
{
public:
  AudioDecoderInfoTag() = default;

  void SetTitle(const std::string& title)
  {
    m_title = title;
  }
  const std::string& GetTitle() const { return m_title; }

  void SetArtist(const std::string& artist)
  {
    m_artist = artist;
  }
  const std::string& GetArtist() const { return m_artist; }

  void SetAlbum(const std::string& album)
  {
    m_album = album;
  }
  const std::string& GetAlbum() const { return m_album; }

  void SetAlbumArtist(const std::string& albumArtist)
  {
    m_album_artist = albumArtist;
  }
  const std::string& GetAlbumArtist() const { return m_album_artist; }

  void SetMediaType(const std::string& mediaType)
  {
    m_media_type = mediaType;
  }
  const std::string& GetMediaType() const { return m_media_type; }

  void SetGenre(const std::string& genre)
  {
    m_genre = genre;
  }
  const std::string& GetGenre() const { return m_genre; }

  void SetDuration(int duration) { m_duration = duration; }
  int GetDuration() const { return m_duration; }

  void SetTrack(int track) { m_track = track; }
  int GetTrack() const { return m_track; }

  void SetDisc(int disc) { m_disc = disc; }
  int GetDisc() const { return m_disc; }

  void SetDiscSubtitle(const std::string& discSubtitle)
  {
    m_disc_subtitle = discSubtitle;
  }
  const std::string& GetDiscSubtitle() const { return m_disc_subtitle; }

  void SetDiscTotal(int discTotal) { m_disc_total = discTotal; }
  int GetDiscTotal() const { return m_disc_total; }

  void SetReleaseDate(const std::string& releaseDate)
  {
    m_release_date = releaseDate;
  }
  const std::string& GetReleaseDate() const { return m_release_date; }

  void SetLyrics(const std::string& lyrics)
  {
    m_lyrics = lyrics;
  }
  const std::string& GetLyrics() const { return m_lyrics; }

  void SetSamplerate(int samplerate) { m_samplerate = samplerate; }
  int GetSamplerate() const { return m_samplerate; }

  void SetChannels(int channels) { m_channels = channels; }
  int GetChannels() const { return m_channels; }

  void SetBitrate(int bitrate) { m_bitrate = bitrate; }
  int GetBitrate() const { return m_bitrate; }

  void SetComment(const std::string& comment)
  {
    m_comment = comment;
  }
  const std::string& GetComment() const { return m_comment; }

private:
  std::string m_title;
  std::string m_artist;
  std::string m_album;
  std::string m_album_artist;
  std::string m_media_type;
  std::string m_genre;
  int m_duration{0};
  int m_track{0};
  int m_disc{0};
  std::string m_disc_subtitle;
  int m_disc_total{0};
  std::string m_release_date;
  std::string m_lyrics;
  int m_samplerate{0};
  int m_channels{0};
  int m_bitrate{0};
  std::string m_comment;
};

class ATTR_DLL_LOCAL CInstanceAudioDecoder : public IAddonInstance
{
public:
  explicit CInstanceAudioDecoder(KODI_HANDLE instance)
    : IAddonInstance(ADDON_INSTANCE_AUDIODECODER)
  {
    if (CAddonBase::ifc.m_globalSingleInstance != nullptr)
      throw std::logic_error("kodi::addon::CInstanceAudioDecoder: Creation of multiple together with single instance way is not allowed!");

    SetAddonStruct(instance);
  }

  virtual bool Init(const std::string& filename,
                    unsigned int filecache,
                    int& channels,
                    int& samplerate,
                    int& bitspersample,
                    int64_t& totaltime,
                    int& bitrate,
                    AudioEngineDataFormat& format,
                    std::vector<AudioEngineChannel>& channellist) = 0;
  virtual int ReadPCM(uint8_t* buffer, size_t size, size_t& actualsize) = 0;
  virtual int64_t Seek(int64_t time) { return time; }
  virtual bool ReadTag(const std::string& file, kodi::addon::AudioDecoderInfoTag& tag)
  {
    return false;
  }
  virtual int TrackCount(const std::string& file) { return 1; }

private:
  void SetAddonStruct(KODI_HANDLE instance) override
  {
    if (instance == nullptr)
      throw std::logic_error("kodi::addon::CInstanceAudioDecoder: Creation with empty addon structure not allowed, table must be given from Kodi!");

    KODI_INSTANCE_HDL* instanceKodi = static_cast<KODI_INSTANCE_HDL*>(instance);
    instanceKodi->type = ADDON_INSTANCE_AUDIODECODER;
    instanceKodi->instance = this;
    instanceKodi->audiodecoder->init = ADDON_init;
    instanceKodi->audiodecoder->read_pcm = ADDON_read_pcm;
    instanceKodi->audiodecoder->seek = ADDON_seek;
    instanceKodi->audiodecoder->read_tag = ADDON_read_tag;
    instanceKodi->audiodecoder->track_count = ADDON_track_count;
  }

  inline static bool ADDON_init(const KODI_ADDON_AUDIODECODER_HDL hdl,
                                const char* file,
                                unsigned int filecache,
                                int* channels,
                                int* samplerate,
                                int* bitspersample,
                                int64_t* totaltime,
                                int* bitrate,
                                AudioEngineDataFormat* format,
                                enum AudioEngineChannel info[AUDIOENGINE_CH_MAX])
  {
    CInstanceAudioDecoder* thisClass =static_cast<CInstanceAudioDecoder*>(hdl);

    std::vector<AudioEngineChannel> channelList;

    channelList.clear();
    bool ret = thisClass->Init(file, filecache, *channels, *samplerate, *bitspersample, *totaltime,
                               *bitrate, *format, channelList);
    if (!channelList.empty())
    {
      if (channelList.back() != AUDIOENGINE_CH_NULL)
        channelList.push_back(AUDIOENGINE_CH_NULL);

      for (unsigned int i = 0; i < channelList.size(); ++i)
      {
        info[i] = channelList[i];
      }
    }
    return ret;
  }

  inline static int ADDON_read_pcm(const KODI_ADDON_AUDIODECODER_HDL hdl, uint8_t* buffer, size_t size, size_t* actualsize)
  {
    return static_cast<CInstanceAudioDecoder*>(hdl)
        ->ReadPCM(buffer, size, *actualsize);
  }

  inline static int64_t ADDON_seek(const KODI_ADDON_AUDIODECODER_HDL hdl, int64_t time)
  {
    return static_cast<CInstanceAudioDecoder*>(hdl)->Seek(time);
  }

  inline static bool ADDON_read_tag(const KODI_ADDON_AUDIODECODER_HDL hdl,
                                    const char* file,
                                    struct AUDIODECODER_INFO_TAG* tag)
  {
    kodi::addon::AudioDecoderInfoTag cppTag;
    bool ret = static_cast<CInstanceAudioDecoder*>(hdl)->ReadTag(file, cppTag);
    if (ret)
    {
      tag->title = strdup(cppTag.GetTitle().c_str());
      tag->artist = strdup(cppTag.GetArtist().c_str());
      tag->album = strdup(cppTag.GetAlbum().c_str());
      tag->album_artist = strdup(cppTag.GetAlbumArtist().c_str());
      tag->media_type = strdup(cppTag.GetMediaType().c_str());
      tag->genre = strdup(cppTag.GetGenre().c_str());
      tag->duration = cppTag.GetDuration();
      tag->track = cppTag.GetTrack();
      tag->disc = cppTag.GetDisc();
      tag->disc_subtitle = strdup(cppTag.GetDiscSubtitle().c_str());
      tag->disc_total = cppTag.GetDiscTotal();
      tag->release_date = strdup(cppTag.GetReleaseDate().c_str());
      tag->lyrics = strdup(cppTag.GetLyrics().c_str());
      tag->samplerate = cppTag.GetSamplerate();
      tag->channels = cppTag.GetChannels();
      tag->bitrate = cppTag.GetBitrate();
      tag->comment = strdup(cppTag.GetComment().c_str());
    }
    return ret;
  }

  inline static int ADDON_track_count(const KODI_ADDON_AUDIODECODER_HDL hdl, const char* file)
  {
    return static_cast<CInstanceAudioDecoder*>(hdl)->TrackCount(file);
  }
};

} /* namespace addon */
} /* namespace kodi */
#endif /* __cplusplus */
