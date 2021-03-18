/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/*---AUTO_GEN_PARSE<OVERRIDE;USE_DIRECT_API_ONLY>---*/

#ifndef C_API_ADDONINSTANCE_VIDEOCODEC_H
#define C_API_ADDONINSTANCE_VIDEOCODEC_H

#include "../addon_base.h"
#include "inputstream/demux_packet.h"
#include "inputstream/stream_codec.h"
#include "inputstream/stream_crypto.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* KODI_ADDON_VIDEOCODEC_HDL;

  enum VIDEOCODEC_RETVAL
  {
    VC_NONE = 0,
    VC_ERROR,
    VC_BUFFER,
    VC_PICTURE,
    VC_EOF,
  };

  enum VIDEOCODEC_FORMAT
  {
    VIDEOCODEC_FORMAT_UNKNOWN = 0,
    VIDEOCODEC_FORMAT_YV12,
    VIDEOCODEC_FORMAT_I420,
    VIDEOCODEC_FORMAT_MAXFORMATS
  };

  enum VIDEOCODEC_TYPE
  {
    VIDEOCODEC_UNKNOWN = 0,
    VIDEOCODEC_VP8,
    VIDEOCODEC_H264,
    VIDEOCODEC_VP9
  };

  enum VIDEOCODEC_PLANE
  {
    VIDEOCODEC_PICTURE_Y_PLANE = 0,
    VIDEOCODEC_PICTURE_U_PLANE,
    VIDEOCODEC_PICTURE_V_PLANE,
    VIDEOCODEC_PICTURE_MAXPLANES = 3,
  };

  enum VIDEOCODEC_PICTURE_FLAG
  {
    VIDEOCODEC_PICTURE_FLAG_NONE = 0,
    VIDEOCODEC_PICTURE_FLAG_DROP = (1 << 0),
    VIDEOCODEC_PICTURE_FLAG_DRAIN = (1 << 1),
  };

  struct VIDEOCODEC_PICTURE
  {
    enum VIDEOCODEC_FORMAT video_format;
    uint32_t flags;
    uint32_t width;
    uint32_t height;
    uint8_t* decoded_data;
    size_t decoded_data_size;
    uint32_t plane_offsets[VIDEOCODEC_PICTURE_MAXPLANES];
    uint32_t stride[VIDEOCODEC_PICTURE_MAXPLANES];
    int64_t pts;
    KODI_OWN_HDL video_buffer_handle;
  };

  struct VIDEOCODEC_INITDATA
  {
    enum VIDEOCODEC_TYPE codec;
    enum STREAMCODEC_PROFILE codec_profile;
    enum VIDEOCODEC_FORMAT* video_formats;
    uint32_t width;
    uint32_t height;
    const uint8_t* extra_data;
    unsigned int extra_data_size;
    struct STREAM_CRYPTO_SESSION crypto_session;
  };

  typedef KODI_ADDON_VIDEOCODEC_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_CREATE_V1)(KODI_OWN_HDL kodi_hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_DESTROY_V1)(KODI_ADDON_VIDEOCODEC_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_OPEN_V1)(KODI_ADDON_VIDEOCODEC_HDL hdl,
                                                           struct VIDEOCODEC_INITDATA* initData);

  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_RECONFIGURE_V1)(
      KODI_ADDON_VIDEOCODEC_HDL hdl, struct VIDEOCODEC_INITDATA* initData);

  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_ADD_DATA_V1)(KODI_ADDON_VIDEOCODEC_HDL hdl,
                                                               const struct DEMUX_PACKET* packet);

  typedef enum VIDEOCODEC_RETVAL(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_GET_PICTURE_V1)(
      KODI_ADDON_VIDEOCODEC_HDL hdl, struct VIDEOCODEC_PICTURE* picture);
  typedef const char*(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_GET_NAME_V1)(KODI_ADDON_VIDEOCODEC_HDL hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_VIDEOCODEC_RESET_V1)(KODI_ADDON_VIDEOCODEC_HDL hdl);

  typedef struct KODI_ADDON_VIDEOCODEC_FUNC
  {
    PFN_KODI_ADDON_VIDEOCODEC_CREATE_V1 create;
    PFN_KODI_ADDON_VIDEOCODEC_DESTROY_V1 destroy;
    PFN_KODI_ADDON_VIDEOCODEC_OPEN_V1 open;
    PFN_KODI_ADDON_VIDEOCODEC_RECONFIGURE_V1 reconfigure;
    PFN_KODI_ADDON_VIDEOCODEC_ADD_DATA_V1 add_data;
    PFN_KODI_ADDON_VIDEOCODEC_GET_PICTURE_V1 get_picture;
    PFN_KODI_ADDON_VIDEOCODEC_GET_NAME_V1 get_name;
    PFN_KODI_ADDON_VIDEOCODEC_RESET_V1 reset;
  } KODI_ADDON_VIDEOCODEC_FUNC;

  ATTR_DLL_EXPORT bool kodi_addon_videocodec_get_frame_buffer(
      KODI_OWN_HDL hdl, struct VIDEOCODEC_PICTURE* picture) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_addon_videocodec_release_frame_buffer(
      KODI_OWN_HDL hdl, struct VIDEOCODEC_PICTURE* picture) __INTRODUCED_IN_KODI(1);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_VIDEOCODEC_H */
