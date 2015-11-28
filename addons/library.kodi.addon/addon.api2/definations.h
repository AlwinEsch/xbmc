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
  typedef enum addon_log
  {
    LOG_DEBUG,
    LOG_INFO,
    LOG_NOTICE,
    LOG_WARNING,
    LOG_ERROR,
    LOG_SEVERE,
    LOG_FATAL
  } addon_log_t;

  typedef enum queue_msg
  {
    QUEUE_INFO,
    QUEUE_WARNING,
    QUEUE_ERROR
  } queue_msg_t;

  typedef enum audio_channel
  {
    AUDIO_CH_INVALID = -1,
    AUDIO_CH_FL = 0,
    AUDIO_CH_FR,
    AUDIO_CH_FC,
    AUDIO_CH_LFE,
    AUDIO_CH_BL,
    AUDIO_CH_BR,
    AUDIO_CH_FLOC,
    AUDIO_CH_FROC,
    AUDIO_CH_BC,
    AUDIO_CH_SL,
    AUDIO_CH_SR,
    AUDIO_CH_TFL,
    AUDIO_CH_TFR,
    AUDIO_CH_TFC,
    AUDIO_CH_TC,
    AUDIO_CH_TBL,
    AUDIO_CH_TBR,
    AUDIO_CH_TBC,
    AUDIO_CH_BLOC,
    AUDIO_CH_BROC,

    AUDIO_CH_MAX
  } audio_channel_t;

  /*
   * Codecs definations
   */
  typedef unsigned int kodi_codec_id_t;

  typedef enum
  {
    KODI_CODEC_TYPE_UNKNOWN = -1,
    KODI_CODEC_TYPE_VIDEO,
    KODI_CODEC_TYPE_AUDIO,
    KODI_CODEC_TYPE_DATA,
    KODI_CODEC_TYPE_SUBTITLE,
    KODI_CODEC_TYPE_RDS,
    KODI_CODEC_TYPE_NB
  } kodi_codec_type_t;

  typedef struct
  {
    kodi_codec_type_t codec_type;
    kodi_codec_id_t   codec_id;
  } kodi_codec_t;

  #define KODI_INVALID_CODEC_ID   0
  #define KODI_INVALID_CODEC      { KODI_CODEC_TYPE_UNKNOWN, KODI_INVALID_CODEC_ID }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
