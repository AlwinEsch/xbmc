/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../AddonBase.h"
#include "../c-api/addon-instance/audioencoder.h"

#ifdef __cplusplus

#include <stdexcept>

namespace kodi
{
namespace addon
{

class CInstanceAudioEncoder;

class ATTR_DLL_LOCAL AudioEncoderInfoTag
{
public:
  AudioEncoderInfoTag() = default;

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

  void SetBitsPerSample(int bits_per_sample) { m_bits_per_sample = bits_per_sample; }
  int GetBitsPerSample() const { return m_bits_per_sample; }

  void SetTrackLength(int track_length) { m_track_length = track_length; }
  int GetTrackLength() const { return m_track_length; }

  void SetComment(const std::string& comment)
  {
    m_comment = comment;
  }
  const std::string& GetComment() const { return m_comment; }

private:
  friend class CInstanceAudioEncoder;

  AudioEncoderInfoTag(const struct AUDIOENCODER_INFO_TAG* tag)
  {
    m_title = tag->title;
    m_artist = tag->artist;
    m_album = tag->album;
    m_album_artist = tag->album_artist;
    m_media_type = tag->media_type;
    m_genre = tag->genre;
    m_duration = tag->duration;
    m_track = tag->track;
    m_disc = tag->disc;
    m_disc_subtitle = tag->artist;
    m_disc_total = tag->disc_total;
    m_release_date = tag->release_date;
    m_lyrics = tag->lyrics;
    m_samplerate = tag->samplerate;
    m_channels = tag->channels;
    m_bits_per_sample = tag->bits_per_sample;
    m_track_length = tag->track_length;
    m_comment = tag->comment;
  }

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
  int m_bits_per_sample{0};
  int m_track_length{0};
  std::string m_comment;
};

class ATTR_DLL_LOCAL CInstanceAudioEncoder : public IAddonInstance
{
public:
  explicit CInstanceAudioEncoder(KODI_HANDLE instance)
    : IAddonInstance(ADDON_INSTANCE_AUDIOENCODER)
  {
    if (CAddonBase::m_globalSingleInstance != nullptr)
      throw std::logic_error("kodi::addon::CInstanceAudioEncoder: Creation of multiple together "
                             "with single instance way is not allowed!");

    SetAddonStruct(instance);
  }

  virtual bool Start(const AudioEncoderInfoTag& tag) = 0;

  virtual ssize_t Encode(const uint8_t* pbtStream, size_t numBytesRead) = 0;

  virtual bool Finish() { return true; }

  inline ssize_t Write(const uint8_t* data, size_t length)
  {
    return kodi_addon_audioencoder_write(m_kodi, data, length);
  }

  inline ssize_t Seek(int64_t position, size_t whence = SEEK_SET)
  {
    return kodi_addon_audioencoder_seek(m_kodi, position, whence);
  }

private:
  void SetAddonStruct(KODI_HANDLE instance) override
  {
    if (instance == nullptr)
      throw std::logic_error("kodi::addon::CInstanceAudioEncoder: Creation with empty addon "
                             "structure not allowed, table must be given from Kodi!");

    KODI_INSTANCE_HDL* instanceKodi = static_cast<KODI_INSTANCE_HDL*>(instance);
    instanceKodi->type = ADDON_INSTANCE_AUDIOENCODER;
    instanceKodi->instance = this;
    instanceKodi->audioencoder->start = ADDON_start;
    instanceKodi->audioencoder->encode = ADDON_encode;
    instanceKodi->audioencoder->finish = ADDON_finish;
    m_kodi = instanceKodi->kodi;
  }

  inline static bool ADDON_start(const KODI_ADDON_AUDIOENCODER_HDL hdl,
                                 const struct AUDIOENCODER_INFO_TAG* tag)
  {
    return static_cast<CInstanceAudioEncoder*>(hdl)->Start(tag);
  }

  inline static ssize_t ADDON_encode(const KODI_ADDON_AUDIOENCODER_HDL hdl,
                                 const uint8_t* pbtStream,
                                 size_t numBytesRead)
  {
    return static_cast<CInstanceAudioEncoder*>(hdl)->Encode(pbtStream, numBytesRead);
  }

  inline static bool ADDON_finish(const KODI_ADDON_AUDIOENCODER_HDL hdl)
  {
    return static_cast<CInstanceAudioEncoder*>(hdl)->Finish();
  }

  KODI_OWN_HDL m_kodi;
};

} /* namespace addon */
} /* namespace kodi */

#endif /* __cplusplus */
