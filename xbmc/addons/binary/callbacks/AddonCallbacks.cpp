/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AddonCallbacks.h"

#include "addons/Addon.h"
#include "addons/binary/callbacks/Addon/AddonCallbacksAddonBase.h"
#include "addons/binary/callbacks/AudioDSP/AddonCallbacksAudioDSPBase.h"
#include "addons/binary/callbacks/AudioEngine/AddonCallbacksAudioEngineBase.h"
#include "addons/binary/callbacks/Codec/AddonCallbacksCodecBase.h"
#include "addons/binary/callbacks/GUI/AddonCallbacksGUIBase.h"
#include "addons/binary/callbacks/PVR/AddonCallbacksPVRBase.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"

namespace ADDON
{

CAddonCallbacks::CAddonCallbacks(CAddon* addon)
  : m_callbacks(new AddonCB),
    m_addon(addon),
    m_helperAddOn(nullptr),
    m_helperADSP(nullptr),
    m_helperAudioEngine(nullptr),
    m_helperCODEC(nullptr),
    m_helperGUI(nullptr),
    m_helperPVR(nullptr)
{
fprintf(stderr, "---------------- %s\n", __PRETTY_FUNCTION__);

  m_callbacks->libBasePath                  = strdup(CSpecialProtocol::TranslatePath("special://xbmcbin/addons").c_str());
  m_callbacks->addonData                    = this;

  m_callbacks->AddOnLib_RegisterMe          = CAddonCallbacks::AddOnLib_RegisterMe;
  m_callbacks->AddOnLib_RegisterLevel       = CAddonCallbacks::AddOnLib_RegisterLevel;
  m_callbacks->AddOnLib_UnRegisterMe        = CAddonCallbacks::AddOnLib_UnRegisterMe;

  m_callbacks->AudioEngineLib_RegisterMe    = CAddonCallbacks::AudioEngineLib_RegisterMe;
  m_callbacks->AudioEngineLib_RegisterLevel = CAddonCallbacks::AudioEngineLib_RegisterLevel;
  m_callbacks->AudioEngineLib_UnRegisterMe  = CAddonCallbacks::AudioEngineLib_UnRegisterMe;

  m_callbacks->GUILib_RegisterMe            = CAddonCallbacks::GUILib_RegisterMe;
  m_callbacks->GUILib_RegisterLevel         = CAddonCallbacks::GUILib_RegisterLevel;
  m_callbacks->GUILib_UnRegisterMe          = CAddonCallbacks::GUILib_UnRegisterMe;

  m_callbacks->PVRLib_RegisterMe            = CAddonCallbacks::PVRLib_RegisterMe;
  m_callbacks->PVRLib_RegisterLevel         = CAddonCallbacks::PVRLib_RegisterLevel;
  m_callbacks->PVRLib_UnRegisterMe          = CAddonCallbacks::PVRLib_UnRegisterMe;

  /*!
   * Deprecated old libraries
   */
  m_callbacks->ADSPLib_RegisterMe           = CAddonCallbacks::ADSPLib_RegisterMe;
  m_callbacks->ADSPLib_UnRegisterMe         = CAddonCallbacks::ADSPLib_UnRegisterMe;

  m_callbacks->CodecLib_RegisterMe          = CAddonCallbacks::CodecLib_RegisterMe;
  m_callbacks->CodecLib_UnRegisterMe        = CAddonCallbacks::CodecLib_UnRegisterMe;
}

CAddonCallbacks::~CAddonCallbacks()
{
  fprintf(stderr, "---------------- %s\n", __PRETTY_FUNCTION__);

  CAddonCallbacksAddonBase::DestroyHelper(this);
  CAddonCallbacksAudioEngineBase::DestroyHelper(this);
  CAddonCallbacksGUIBase::DestroyHelper(this);
  CAddonCallbacksPVRBase::DestroyHelper(this);

  delete static_cast<ADSPLIB::V1::CAddonCallbacksADSP*>(m_helperADSP);
  delete static_cast<CodecLib::V1::CAddonCallbacksCodec*>(m_helperCODEC);

  free((char*)m_callbacks->libBasePath);
  delete m_callbacks;
}

/*\_____________________________________________________________________________
\*/

void* CAddonCallbacks::AddOnLib_RegisterMe(void *addonData)
{
  return AddOnLib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::AddOnLib_RegisterLevel(void *addonData, int level)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks *>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return nullptr;
  }

  void* cb = CAddonCallbacksAddonBase::CreateHelper(addon, level);
  fprintf(stderr, "-------55--- %s %p\n", __PRETTY_FUNCTION__, cb);
  if (!cb)
    CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                          __FUNCTION__,
                          TranslateType(addon->m_addon->Type()).c_str(),
                          addon->m_addon->Name().c_str(), level);
  return cb;
}

void CAddonCallbacks::AddOnLib_UnRegisterMe(void *addonData, void *cbTable)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  fprintf(stderr, "...---> %s\n", __PRETTY_FUNCTION__);
  CAddonCallbacksAddonBase::DestroyHelper(addon);
}

int CAddonCallbacks::AddOnLib_APILevel()
{
  return CAddonCallbacksAddonBase::APILevel();
}

int CAddonCallbacks::AddOnLib_MinAPILevel()
{
  return CAddonCallbacksAddonBase::MinAPILevel();
}

std::string CAddonCallbacks::AddOnLib_Version()
{
  return CAddonCallbacksAddonBase::Version();
}

std::string CAddonCallbacks::AddOnLib_MinVersion()
{
  return CAddonCallbacksAddonBase::MinVersion();
}

/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::AudioEngineLib_RegisterMe(void *addonData)
{
  return AudioEngineLib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::AudioEngineLib_RegisterLevel(void *addonData, int level)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return nullptr;
  }

  void* cb = CAddonCallbacksAudioEngineBase::CreateHelper(addon, level);
  if (!cb)
    CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                          __FUNCTION__,
                          TranslateType(addon->m_addon->Type()).c_str(),
                          addon->m_addon->Name().c_str(), level);
  return cb;
}

void CAddonCallbacks::AudioEngineLib_UnRegisterMe(void *addonData, void *cbTable)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  CAddonCallbacksAudioEngineBase::DestroyHelper(addon);
}

int CAddonCallbacks::AudioEngineLib_APILevel()
{
  return CAddonCallbacksAudioEngineBase::APILevel();
}

int CAddonCallbacks::AudioEngineLib_MinAPILevel()
{
  return CAddonCallbacksAudioEngineBase::MinAPILevel();
}

std::string CAddonCallbacks::AudioEngineLib_Version()
{
  return CAddonCallbacksAudioEngineBase::Version();
}

std::string CAddonCallbacks::AudioEngineLib_MinVersion()
{
  return CAddonCallbacksAudioEngineBase::MinVersion();
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::GUILib_RegisterMe(void *addonData)
{
  return GUILib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::GUILib_RegisterLevel(void *addonData, int level)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return nullptr;
  }

  void* cb = CAddonCallbacksGUIBase::CreateHelper(addon, level);
  if (!cb)
    CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                          __FUNCTION__,
                          TranslateType(addon->m_addon->Type()).c_str(),
                          addon->m_addon->Name().c_str(), level);
  return cb;
}

void CAddonCallbacks::GUILib_UnRegisterMe(void *addonData, void *cbTable)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  CAddonCallbacksGUIBase::DestroyHelper(addon);
}

int CAddonCallbacks::GUILib_APILevel()
{
  return CAddonCallbacksGUIBase::APILevel();
}

int CAddonCallbacks::GUILib_MinAPILevel()
{
  return CAddonCallbacksGUIBase::MinAPILevel();
}

std::string CAddonCallbacks::GUILib_Version()
{
  return CAddonCallbacksGUIBase::Version();
}

std::string CAddonCallbacks::GUILib_MinVersion()
{
  return CAddonCallbacksGUIBase::MinVersion();
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::PVRLib_RegisterMe(void *addonData)
{
  return PVRLib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::PVRLib_RegisterLevel(void *addonData, int level)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return nullptr;
  }

  void* cb = CAddonCallbacksPVRBase::CreateHelper(addon, level);
  if (!cb)
    CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                          __FUNCTION__,
                          TranslateType(addon->m_addon->Type()).c_str(),
                          addon->m_addon->Name().c_str(), level);
  return cb;
}

void CAddonCallbacks::PVRLib_UnRegisterMe(void *addonData, void *cbTable)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  CAddonCallbacksPVRBase::DestroyHelper(addon);
}

int CAddonCallbacks::PVRLib_APILevel()
{
  return CAddonCallbacksPVRBase::APILevel();
}

int CAddonCallbacks::PVRLib_MinAPILevel()
{
  return CAddonCallbacksPVRBase::MinAPILevel();
}

std::string CAddonCallbacks::PVRLib_Version()
{
  return CAddonCallbacksPVRBase::Version();
}

std::string CAddonCallbacks::PVRLib_MinVersion()
{
  return CAddonCallbacksPVRBase::MinVersion();
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::ADSPLib_RegisterMe(void *addonData)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return nullptr;
  }

  addon->m_helperCODEC = new ADSPLIB::V1::CAddonCallbacksADSP(addon->m_addon);
  return static_cast<ADSPLIB::V1::CAddonCallbacksADSP*>(addon->m_helperADSP)->GetCallbacks();
}

void CAddonCallbacks::ADSPLib_UnRegisterMe(void *addonData, void *cbTable)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  delete static_cast<ADSPLIB::V1::CAddonCallbacksADSP*>(addon->m_helperADSP);
  addon->m_helperADSP = nullptr;
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::CodecLib_RegisterMe(void *addonData)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return NULL;
  }

  addon->m_helperCODEC = new CodecLib::V1::CAddonCallbacksCodec(addon->m_addon);
  return static_cast<CodecLib::V1::CAddonCallbacksCodec*>(addon->m_helperCODEC)->GetCallbacks();
}

void CAddonCallbacks::CodecLib_UnRegisterMe(void *addonData, void *cbTable)
{
  CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
  if (addon == nullptr)
  {
    CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
    return;
  }

  delete static_cast<CodecLib::V1::CAddonCallbacksCodec*>(addon->m_helperCODEC);
  addon->m_helperCODEC = nullptr;
}

}; /* namespace ADDON */
