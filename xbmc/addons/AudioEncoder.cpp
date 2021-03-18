/*
 *  Copyright (C) 2013 Arne Morten Kvarving
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "AudioEncoder.h"

namespace ADDON
{

using namespace KODI::ADDONS::INTERFACE;

CAudioEncoder::CAudioEncoder(const AddonInfoPtr& addonInfo)
  : IAddonInstanceHandler(ADDON_INSTANCE_AUDIOENCODER, addonInfo)
{
}

bool CAudioEncoder::Init(AudioEncoderCB& callbacks)
{
  m_callbacks = callbacks;

  if (CreateInstance(this, m_addonInstance) != ADDON_STATUS_OK)
    return false;

  AUDIOENCODER_INFO_TAG tag;
  tag.channels = m_iInChannels;
  tag.samplerate = m_iInSampleRate;
  tag.bits_per_sample = m_iInBitsPerSample;
  tag.track_length = m_iTrackLength;
  tag.title = m_strTitle.c_str();
  tag.artist = m_strArtist.c_str();
  tag.album_artist = m_strAlbumArtist.c_str();
  tag.album = m_strAlbum.c_str();
  tag.release_date = m_strYear.c_str();
  tag.track = atoi(m_strTrack.c_str());
  tag.genre = m_strGenre.c_str();
  tag.comment = m_strComment.c_str();

  return m_ifc->kodi_addoninstance_audioencoder_h->kodi_addon_audioencoder_start_v1(m_addonInstance, &tag);
}

int CAudioEncoder::Encode(int nNumBytesRead, uint8_t* pbtStream)
{
  return m_ifc->kodi_addoninstance_audioencoder_h->kodi_addon_audioencoder_encode_v1(m_addonInstance, pbtStream, nNumBytesRead);
}

bool CAudioEncoder::Close()
{
  bool ret = m_ifc->kodi_addoninstance_audioencoder_h->kodi_addon_audioencoder_finish_v1(m_addonInstance);

  DestroyInstance(m_addonInstance);

  return ret;
}

int CAudioEncoder::Write(const uint8_t* data, int len)
{
  return m_callbacks.write(m_callbacks.kodiInstance, data, len);
}

int64_t CAudioEncoder::Seek(int64_t pos, int whence)
{
  return m_callbacks.seek(m_callbacks.kodiInstance, pos, whence);
}

} /* namespace ADDON */
