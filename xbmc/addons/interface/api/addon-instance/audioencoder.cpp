/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#include "audioencoder.h"

// Shared API
#include "addons/kodi-dev-kit/src/shared/api/addon-instance/audioencoder.h"

// Kodi
#include "addons/AudioEncoder.h"
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

void CHdl_kodi_addoninstance_audioencoder_h::InitDirect(
    directFuncToKodi_addoninstance_audioencoder_h* ifcToKodi,
    directFuncToAddon_addoninstance_audioencoder_h* ifcToAddon)
{
  ifcToKodi->thisClassHdl = this;
  m_ifcToAddon = ifcToAddon;
  ifcToKodi->kodi_addon_audioencoder_write_v1 = kodi_addon_audioencoder_write_v1;
  ifcToKodi->kodi_addon_audioencoder_seek_v1 = kodi_addon_audioencoder_seek_v1;
}

bool CHdl_kodi_addoninstance_audioencoder_h::HandleMessage(int funcGroup,
                                                           int func,
                                                           const msgpack::unpacked& in,
                                                           msgpack::sbuffer& out)
{
  if (funcGroup != funcGroup_addoninstance_audioencoder_h)
    return false;

  switch (func)
  {
    case funcParent_kodi_addon_audioencoder_write_v1:
    {
      // Original API call: ATTR_DLL_EXPORT ssize_t kodi_addon_audioencoder_write(KODI_OWN_HDL hdl, const uint8_t* data, size_t len) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue, std::vector<uint8_t>, size_t> msgParent__IN_kodi_addon_audioencoder_write_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<ssize_t> msgParent_OUT_kodi_addon_audioencoder_write_v1; /* Autogenerated */
      msgParent__IN_kodi_addon_audioencoder_write_v1 t = in.get().as<decltype(t)>();
      KODI_OWN_HDL hdl = reinterpret_cast<KODI_OWN_HDL>(std::get<0>(t));
      const std::vector<uint8_t>& data = std::get<1>(t);
      size_t len = std::get<2>(t);
      ssize_t auto_gen_ret = kodi_addon_audioencoder_write_v1(this, hdl, data.data(), len);
      msgpack::pack(out, msgParent_OUT_kodi_addon_audioencoder_write_v1(auto_gen_ret));
      return true;
    }
    case funcParent_kodi_addon_audioencoder_seek_v1:
    {
      // Original API call: ATTR_DLL_EXPORT ssize_t kodi_addon_audioencoder_seek(KODI_OWN_HDL hdl, size_t pos, int whence) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<PtrValue, size_t, int> msgParent__IN_kodi_addon_audioencoder_seek_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<ssize_t> msgParent_OUT_kodi_addon_audioencoder_seek_v1; /* Autogenerated */
      msgParent__IN_kodi_addon_audioencoder_seek_v1 t = in.get().as<decltype(t)>();
      KODI_OWN_HDL hdl = reinterpret_cast<KODI_OWN_HDL>(std::get<0>(t));
      size_t pos = std::get<1>(t);
      int whence = std::get<2>(t);
      ssize_t auto_gen_ret = kodi_addon_audioencoder_seek_v1(this, hdl, pos, whence);
      msgpack::pack(out, msgParent_OUT_kodi_addon_audioencoder_seek_v1(auto_gen_ret));
      return true;
    }
    default:
      CLog::Log(LOGERROR,
                "CHdl_kodi_addoninstance_audioencoder_h::{}: addon called with unknown function id "
                "'{}' on group 'addoninstance_audioencoder_h'",
                __func__, func);
  }

  return false;
}

// Function calls from Kodi to addon

KODI_ADDON_AUDIOENCODER_HDL CHdl_kodi_addoninstance_audioencoder_h::
    kodi_addon_audioencoder_create_v1(KODI_OWN_HDL kodi_hdl)
{
  // Original API call: typedef KODI_ADDON_AUDIOENCODER_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIOENCODER_CREATE_V1)(KODI_OWN_HDL kodi_hdl);
  // Tuple in:          typedef std::tuple<PtrValue> msgChild__IN_kodi_addon_audioencoder_create_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<PtrValue> msgChild_OUT_kodi_addon_audioencoder_create_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgChild__IN_kodi_addon_audioencoder_create_v1(PtrValue(kodi_hdl)));
    if (!m_process->SendMessage(funcGroup_addoninstance_audioencoder_h,
                                funcChild_kodi_addon_audioencoder_create_v1, in, out))
      return nullptr;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audioencoder_create_v1 t = ident.get().as<decltype(t)>();
    return reinterpret_cast<KODI_ADDON_AUDIOENCODER_HDL>(std::get<0>(t));
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audioencoder_create_v1(m_ifcToAddon->thisClassHdl, kodi_hdl);
}

void CHdl_kodi_addoninstance_audioencoder_h::kodi_addon_audioencoder_destroy_v1(
    KODI_ADDON_AUDIOENCODER_HDL hdl)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIOENCODER_DESTROY_V1)(KODI_ADDON_AUDIOENCODER_HDL hdl);
  // Tuple in:          typedef std::tuple<PtrValue> msgChild__IN_kodi_addon_audioencoder_destroy_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<DummyValue> msgChild_OUT_kodi_addon_audioencoder_destroy_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::pack(in, msgChild__IN_kodi_addon_audioencoder_destroy_v1(PtrValue(hdl)));
    m_process->SendMessage(funcGroup_addoninstance_audioencoder_h,
                           funcChild_kodi_addon_audioencoder_destroy_v1, in);
    return;
  }
#endif /* !KODI_INHIBIT_SHARED */

  m_ifcToAddon->kodi_addon_audioencoder_destroy_v1(m_ifcToAddon->thisClassHdl, hdl);
}

bool CHdl_kodi_addoninstance_audioencoder_h::kodi_addon_audioencoder_start_v1(
    KODI_ADDON_AUDIOENCODER_HDL hdl, const struct AUDIOENCODER_INFO_TAG* tag)
{
  // Original API call: typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIOENCODER_START_V1)(KODI_ADDON_AUDIOENCODER_HDL hdl, const struct AUDIOENCODER_INFO_TAG* tag);
  // Tuple in:          typedef std::tuple<PtrValue, IFC_AUDIOENCODER_INFO_TAG> msgChild__IN_kodi_addon_audioencoder_start_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<bool> msgChild_OUT_kodi_addon_audioencoder_start_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgChild__IN_kodi_addon_audioencoder_start_v1(PtrValue(hdl), tag));
    if (!m_process->SendMessage(funcGroup_addoninstance_audioencoder_h,
                                funcChild_kodi_addon_audioencoder_start_v1, in, out))
      return false;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audioencoder_start_v1 t = ident.get().as<decltype(t)>();
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audioencoder_start_v1(m_ifcToAddon->thisClassHdl, hdl, tag);
}

ssize_t CHdl_kodi_addoninstance_audioencoder_h::kodi_addon_audioencoder_encode_v1(
    KODI_ADDON_AUDIOENCODER_HDL hdl, const uint8_t* pbt_stream, size_t num_bytes_read)
{
  // Original API call: typedef ssize_t(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIOENCODER_ENCODE_V1)(KODI_ADDON_AUDIOENCODER_HDL hdl, const uint8_t* pbt_stream, size_t num_bytes_read);
  // Tuple in:          typedef std::tuple<PtrValue, std::vector<uint8_t>, size_t> msgChild__IN_kodi_addon_audioencoder_encode_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<ssize_t> msgChild_OUT_kodi_addon_audioencoder_encode_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in,
                  msgChild__IN_kodi_addon_audioencoder_encode_v1(
                      PtrValue(hdl), std::vector<uint8_t>(pbt_stream, pbt_stream + num_bytes_read),
                      num_bytes_read));
    if (!m_process->SendMessage(funcGroup_addoninstance_audioencoder_h,
                                funcChild_kodi_addon_audioencoder_encode_v1, in, out))
      return -1;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audioencoder_encode_v1 t = ident.get().as<decltype(t)>();
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audioencoder_encode_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                         pbt_stream, num_bytes_read);
}

bool CHdl_kodi_addoninstance_audioencoder_h::kodi_addon_audioencoder_finish_v1(
    KODI_ADDON_AUDIOENCODER_HDL hdl)
{
  // Original API call: typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_AUDIOENCODER_FINISH_V1)(KODI_ADDON_AUDIOENCODER_HDL hdl);
  // Tuple in:          typedef std::tuple<PtrValue> msgChild__IN_kodi_addon_audioencoder_finish_v1; /* Autogenerated */
  // Tuple out:         typedef std::tuple<bool> msgChild_OUT_kodi_addon_audioencoder_finish_v1; /* Autogenerated */

#ifndef KODI_INHIBIT_SHARED
  if (!m_interface.m_directDll)
  {
    msgpack::sbuffer in;
    msgpack::sbuffer out;
    msgpack::pack(in, msgChild__IN_kodi_addon_audioencoder_finish_v1(PtrValue(hdl)));
    if (!m_process->SendMessage(funcGroup_addoninstance_audioencoder_h,
                                funcChild_kodi_addon_audioencoder_finish_v1, in, out))
      return false;
    msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());
    msgChild_OUT_kodi_addon_audioencoder_finish_v1 t = ident.get().as<decltype(t)>();
    return std::get<0>(t);
  }
#endif /* !KODI_INHIBIT_SHARED */

  return m_ifcToAddon->kodi_addon_audioencoder_finish_v1(m_ifcToAddon->thisClassHdl, hdl);
}

// Callbacks from addon to Kodi

ssize_t CHdl_kodi_addoninstance_audioencoder_h::kodi_addon_audioencoder_write_v1(
    void* thisClassHdl, KODI_OWN_HDL hdl, const uint8_t* data, size_t len)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_audioencoder_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return -1;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_AUDIOENCODER_WRITE>---*/
  // AUTOGENERATED - Used by class "ADDON::CAudioEncoder" with "int Write(const uint8_t* data, int len); /*---AUTO_GEN_PARSE<CB:kodi_addon_audioencoder_write>---*/" on "addons/AudioEncoder.h".

  ADDON::CAudioEncoder* cb = static_cast<ADDON::CAudioEncoder*>(hdl);
  return cb->Write(data, len);
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_AUDIOENCODER_WRITE_END>---*/
}

ssize_t CHdl_kodi_addoninstance_audioencoder_h::kodi_addon_audioencoder_seek_v1(void* thisClassHdl,
                                                                                KODI_OWN_HDL hdl,
                                                                                size_t pos,
                                                                                int whence)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_audioencoder_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return -1;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_AUDIOENCODER_SEEK>---*/
  // AUTOGENERATED - Used by class "ADDON::CAudioEncoder" with "int64_t Seek(int64_t pos, int whence); /*---AUTO_GEN_PARSE<CB:kodi_addon_audioencoder_seek>---*/" on "addons/AudioEncoder.h".

  ADDON::CAudioEncoder* cb = static_cast<ADDON::CAudioEncoder*>(hdl);
  return cb->Seek(pos, whence);
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_AUDIOENCODER_SEEK_END>---*/
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
