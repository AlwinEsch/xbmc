/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#include "audiodecoder.h"

// Shared API
#include "addons/kodi-dev-kit/src/shared/api/addon-instance/audiodecoder.h"

// Kodi
#include "addons/interface/RunningProcess.h"
#include "utils/log.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

void CHdl_kodi_addoninstance_audiodecoder_h::InitDirect(
    directFuncToKodi_addoninstance_audiodecoder_h* ifcToKodi,
    directFuncToAddon_addoninstance_audiodecoder_h* ifcToAddon)
{
  ifcToKodi->thisClassHdl = this;
  m_ifcToAddon = ifcToAddon;
}

bool CHdl_kodi_addoninstance_audiodecoder_h::HandleMessage(int funcGroup,
                                                           int func,
                                                           const msgpack::unpacked& in,
                                                           msgpack::sbuffer& out)
{
  if (funcGroup != funcGroup_addoninstance_audiodecoder_h)
    return false;

  switch (func)
  {
    default:
      CLog::Log(LOGERROR,
                "CHdl_kodi_addoninstance_audiodecoder_h::{}: addon called with unknown function id "
                "'{}' on group 'addoninstance_audiodecoder_h'",
                __func__, func);
  }

  return false;
}

// Function calls from Kodi to addon

KODI_ADDON_AUDIODECODER_HDL CHdl_kodi_addoninstance_audiodecoder_h::
    kodi_addon_audiodecoder_create_v1(KODI_OWN_HDL kodi_hdl)
{
  // Original API call: typedef KODI_ADDON_AUDIODECODER_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIODECODER_CREATE_V1)(KODI_OWN_HDL kodi_hdl);
  // Tuple in:          typedef std::tuple<PtrValue> msgChild__IN_kodi_addon_audiodecoder_create_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<PtrValue> msgChild_OUT_kodi_addon_audiodecoder_create_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgChild__IN_kodi_addon_audiodecoder_create_v1(PtrValue(kodi_hdl)));
    if (!m_process->SendMessage(funcGroup_addoninstance_audiodecoder_h,
                                funcChild_kodi_addon_audiodecoder_create_v1, in, out))
      return nullptr;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audiodecoder_create_v1 t = ident.get().as<decltype(t)>();
    return reinterpret_cast<KODI_ADDON_AUDIODECODER_HDL>(std::get<0>(t));
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audiodecoder_create_v1(m_ifcToAddon->thisClassHdl, kodi_hdl);
}

void CHdl_kodi_addoninstance_audiodecoder_h::kodi_addon_audiodecoder_destroy_v1(
    KODI_ADDON_AUDIODECODER_HDL hdl)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIODECODER_DESTROY_V1)(KODI_ADDON_AUDIODECODER_HDL hdl);
  // Tuple in:          typedef std::tuple<PtrValue> msgChild__IN_kodi_addon_audiodecoder_destroy_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgChild_OUT_kodi_addon_audiodecoder_destroy_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgChild__IN_kodi_addon_audiodecoder_destroy_v1(PtrValue(hdl)));
    m_process->SendMessage(funcGroup_addoninstance_audiodecoder_h,
                           funcChild_kodi_addon_audiodecoder_destroy_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  m_ifcToAddon->kodi_addon_audiodecoder_destroy_v1(m_ifcToAddon->thisClassHdl, hdl);
}

bool CHdl_kodi_addoninstance_audiodecoder_h::kodi_addon_audiodecoder_init_v1(
    const KODI_ADDON_AUDIODECODER_HDL hdl,
    const char* file,
    unsigned int filecache,
    int* channels,
    int* samplerate,
    int* bitspersample,
    int64_t* totaltime,
    int* bitrate,
    enum AudioEngineDataFormat* format,
    enum AudioEngineChannel info[AUDIOENGINE_CH_MAX])
{
  // Original API call: typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIODECODER_INIT_V1)(const KODI_ADDON_AUDIODECODER_HDL hdl, const char* file, unsigned int filecache, int* channels, int* samplerate, int* bitspersample, int64_t* totaltime, int* bitrate, enum AudioEngineDataFormat* format, enum AudioEngineChannel info[AUDIOENGINE_CH_MAX]);
  // Tuple in:          typedef std::tuple<PtrValue, std::string, unsigned int, int, int, int, int64_t, int, AudioEngineDataFormat, std::array<AudioEngineChannel, AUDIOENGINE_CH_MAX>> msgChild__IN_kodi_addon_audiodecoder_init_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<bool, int, int, int, int64_t, int, AudioEngineDataFormat, std::array<AudioEngineChannel, AUDIOENGINE_CH_MAX>> msgChild_OUT_kodi_addon_audiodecoder_init_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    std::array<enum AudioEngineChannel, AUDIOENGINE_CH_MAX> ifc_info;
    std::memcpy(ifc_info.data(), info, sizeof(enum AudioEngineChannel) * AUDIOENGINE_CH_MAX);
    msgpack::pack(in, msgChild__IN_kodi_addon_audiodecoder_init_v1(
                          PtrValue(hdl), file, filecache, *channels, *samplerate, *bitspersample,
                          *totaltime, *bitrate, *format, ifc_info));
    if (!m_process->SendMessage(funcGroup_addoninstance_audiodecoder_h,
                                funcChild_kodi_addon_audiodecoder_init_v1, in, out))
      return false;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audiodecoder_init_v1 t = ident.get().as<decltype(t)>();
    *channels = std::get<1>(t);
    *samplerate = std::get<2>(t);
    *bitspersample = std::get<3>(t);
    *totaltime = std::get<4>(t);
    *bitrate = std::get<5>(t);
    *format = std::get<6>(t);
    std::memcpy(info, std::get<7>(t).data(), sizeof(enum AudioEngineChannel) * AUDIOENGINE_CH_MAX);
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audiodecoder_init_v1(
      m_ifcToAddon->thisClassHdl, hdl, file, filecache, channels, samplerate, bitspersample,
      totaltime, bitrate, format, info);
}

int CHdl_kodi_addoninstance_audiodecoder_h::kodi_addon_audiodecoder_read_pcm_v1(
    const KODI_ADDON_AUDIODECODER_HDL hdl, uint8_t* buffer, size_t size, size_t* actualsize)
{
  // Original API call: typedef int(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIODECODER_READ_PCM_V1)(const KODI_ADDON_AUDIODECODER_HDL hdl, uint8_t* buffer, size_t size, size_t* actualsize);
  // Tuple in:          typedef std::tuple<PtrValue, size_t, size_t> msgChild__IN_kodi_addon_audiodecoder_read_pcm_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<int, std::vector<uint8_t>, size_t> msgChild_OUT_kodi_addon_audiodecoder_read_pcm_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(
        in, msgChild__IN_kodi_addon_audiodecoder_read_pcm_v1(PtrValue(hdl), size, *actualsize));
    if (!m_process->SendMessage(funcGroup_addoninstance_audiodecoder_h,
                                funcChild_kodi_addon_audiodecoder_read_pcm_v1, in, out))
      return -1;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audiodecoder_read_pcm_v1 t = ident.get().as<decltype(t)>();
    std::memcpy(buffer, std::get<1>(t).data(), sizeof(uint8_t) * size);
    *actualsize = std::get<2>(t);
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audiodecoder_read_pcm_v1(m_ifcToAddon->thisClassHdl, hdl, buffer,
                                                           size, actualsize);
}

int64_t CHdl_kodi_addoninstance_audiodecoder_h::kodi_addon_audiodecoder_seek_v1(
    const KODI_ADDON_AUDIODECODER_HDL hdl, int64_t time)
{
  // Original API call: typedef int64_t(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIODECODER_SEEK_V1)(const KODI_ADDON_AUDIODECODER_HDL hdl, int64_t time);
  // Tuple in:          typedef std::tuple<PtrValue, int64_t> msgChild__IN_kodi_addon_audiodecoder_seek_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<int64_t> msgChild_OUT_kodi_addon_audiodecoder_seek_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgChild__IN_kodi_addon_audiodecoder_seek_v1(PtrValue(hdl), time));
    if (!m_process->SendMessage(funcGroup_addoninstance_audiodecoder_h,
                                funcChild_kodi_addon_audiodecoder_seek_v1, in, out))
      return -1;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audiodecoder_seek_v1 t = ident.get().as<decltype(t)>();
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audiodecoder_seek_v1(m_ifcToAddon->thisClassHdl, hdl, time);
}

bool CHdl_kodi_addoninstance_audiodecoder_h::kodi_addon_audiodecoder_read_tag_v1(
    const KODI_ADDON_AUDIODECODER_HDL hdl, const char* file, struct AUDIODECODER_INFO_TAG* tag)
{
  // Original API call: typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIODECODER_READ_TAG_V1)(const KODI_ADDON_AUDIODECODER_HDL hdl, const char* file, struct AUDIODECODER_INFO_TAG* tag);
  // Tuple in:          typedef std::tuple<PtrValue, std::string> msgChild__IN_kodi_addon_audiodecoder_read_tag_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<bool, IFC_AUDIODECODER_INFO_TAG> msgChild_OUT_kodi_addon_audiodecoder_read_tag_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgChild__IN_kodi_addon_audiodecoder_read_tag_v1(PtrValue(hdl), file));
    if (!m_process->SendMessage(funcGroup_addoninstance_audiodecoder_h,
                                funcChild_kodi_addon_audiodecoder_read_tag_v1, in, out))
      return false;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audiodecoder_read_tag_v1 t = ident.get().as<decltype(t)>();
    std::get<1>(t).SetCStructure(tag);
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audiodecoder_read_tag_v1(m_ifcToAddon->thisClassHdl, hdl, file,
                                                           tag);
}

int CHdl_kodi_addoninstance_audiodecoder_h::kodi_addon_audiodecoder_track_count_v1(
    const KODI_ADDON_AUDIODECODER_HDL hdl, const char* file)
{
  // Original API call: typedef int(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIODECODER_TRACK_COUNT_V1)(const KODI_ADDON_AUDIODECODER_HDL hdl, const char* file);
  // Tuple in:          typedef std::tuple<PtrValue, std::string> msgChild__IN_kodi_addon_audiodecoder_track_count_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<int> msgChild_OUT_kodi_addon_audiodecoder_track_count_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgChild__IN_kodi_addon_audiodecoder_track_count_v1(PtrValue(hdl), file));
    if (!m_process->SendMessage(funcGroup_addoninstance_audiodecoder_h,
                                funcChild_kodi_addon_audiodecoder_track_count_v1, in, out))
      return -1;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audiodecoder_track_count_v1 t = ident.get().as<decltype(t)>();
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audiodecoder_track_count_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                              file);
}

// Callbacks from addon to Kodi
/* NOTE: unused (no callbacks here) */

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
