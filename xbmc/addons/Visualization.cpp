/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Visualization.h"

#include "addons/interface/api/addon-instance/visualization.h"
#include "filesystem/SpecialProtocol.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

CVisualization::CVisualization(const AddonInfoPtr& addonInfo, float x, float y, float w, float h)
  : IAddonInstanceHandler(ADDON_INSTANCE_VISUALIZATION, addonInfo)
{
  /* Open the class "kodi::addon::CInstanceVisualization" on add-on side */
  if (CreateInstance(this, m_addonInstance) != ADDON_STATUS_OK)
  {
    CLog::Log(LOGFATAL, "Visualization: failed to create instance for '%s' and not usable!", ID().c_str());
    return;
  }

  /* presets becomes send with "transfer_preset" during call of function below */
  m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_get_presets_v1(m_addonInstance);
}

CVisualization::~CVisualization()
{
  /* Destroy the class "kodi::addon::CInstanceVisualization" on add-on side */
  DestroyInstance(m_addonInstance);
}

bool CVisualization::Start(int channels, int samplesPerSec, int bitsPerSample, const std::string& songName)
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_start_v1(m_addonInstance, channels, samplesPerSec, bitsPerSample, songName.c_str());
}

void CVisualization::Stop()
{
  m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_stop_v1(m_addonInstance);
}

void CVisualization::AudioData(const float* audioData, int audioDataLength, float *freqData, int freqDataLength)
{
  m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_audio_data_v1(m_addonInstance, audioData, audioDataLength, freqData, freqDataLength);
}

bool CVisualization::IsDirty()
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_is_dirty_v1(m_addonInstance);
}

void CVisualization::Render()
{
  m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_render_v1(m_addonInstance);
}

void CVisualization::GetInfo(VIS_INFO *info)
{
  m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_get_info_v1(m_addonInstance, info);
}

bool CVisualization::NextPreset()
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_next_preset_v1(m_addonInstance);
}

bool CVisualization::PrevPreset()
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_prev_preset_v1(m_addonInstance);
}

bool CVisualization::LoadPreset(int select)
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_load_preset_v1(m_addonInstance, select);
}

bool CVisualization::RandomPreset()
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_random_preset_v1(m_addonInstance);
}

bool CVisualization::LockPreset()
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_lock_preset_v1(m_addonInstance);
}

bool CVisualization::RatePreset(bool plus_minus)
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_rate_preset_v1(m_addonInstance, plus_minus);
}

bool CVisualization::UpdateAlbumart(const char* albumart)
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_update_albumart_v1(m_addonInstance, albumart);
}

bool CVisualization::UpdateTrack(const VIS_TRACK* track)
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_update_track_v1(m_addonInstance, track);
}

bool CVisualization::HasPresets()
{
  return !m_presets.empty();
}

bool CVisualization::GetPresetList(std::vector<std::string> &vecpresets)
{
  vecpresets = m_presets;
  return !m_presets.empty();
}

int CVisualization::GetActivePreset()
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_get_active_preset_v1(m_addonInstance);
}

std::string CVisualization::GetActivePresetName()
{
  if (!m_presets.empty())
    return m_presets[GetActivePreset()];
  return "";
}

bool CVisualization::IsLocked()
{
  return m_ifc->kodi_addoninstance_visualization_h->kodi_addon_visualization_is_locked_v1(m_addonInstance);
}

void CVisualization::get_properties(struct VIS_PROPS* props)
{
  if (!props)
    return;

  props->x = 0;
  props->y = 0;
  props->device = CServiceBroker::GetWinSystem()->GetHWContext();
  props->width = CServiceBroker::GetWinSystem()->GetGfxContext().GetWidth();
  props->height = CServiceBroker::GetWinSystem()->GetGfxContext().GetHeight();
  props->pixelRatio = CServiceBroker::GetWinSystem()->GetGfxContext().GetResInfo().fPixelRatio;
  props->name = strdup(Name().c_str());
  props->presets = strdup(CSpecialProtocol::TranslatePath(Path()).c_str());
  props->profile = strdup(CSpecialProtocol::TranslatePath(Profile()).c_str());
}

void CVisualization::transfer_preset(const char* preset)
{
  m_presets.emplace_back(preset);
}

void CVisualization::clear_presets()
{
  m_presets.clear();
}

} /* namespace ADDON */
