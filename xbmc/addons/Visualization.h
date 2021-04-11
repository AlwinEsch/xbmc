/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/kodi-dev-kit/include/kodi/c-api/addon-instance/visualization.h"
#include "interface/InstanceHandler.h"

namespace ADDON
{

class CVisualization : public KODI::ADDONS::INTERFACE::IAddonInstanceHandler
{
public:
  CVisualization(const AddonInfoPtr& addonInfo, float x, float y, float w, float h);
  ~CVisualization() override;

  bool Start(int channels, int samplesPerSec, int bitsPerSample, const std::string& songName);
  void Stop();
  void AudioData(const float* audioData, int audioDataLength, float *freqData, int freqDataLength);
  bool IsDirty();
  void Render();
  void GetInfo(VIS_INFO *info);
  bool NextPreset();
  bool PrevPreset();
  bool LoadPreset(int select);
  bool RandomPreset();
  bool LockPreset();
  bool RatePreset(bool plus_minus);
  bool UpdateAlbumart(const char* albumart);
  bool UpdateTrack(const VIS_TRACK* track);
  bool HasPresets();
  bool GetPresetList(std::vector<std::string>& vecpresets);
  int GetActivePreset();
  std::string GetActivePresetName();
  bool IsLocked();

  void get_properties(struct VIS_PROPS* props);
  /*---AUTO_GEN_PARSE<CB:kodi_addon_visualization_get_properties>---*/
  void transfer_preset(const char* preset);
  /*---AUTO_GEN_PARSE<CB:kodi_addon_visualization_transfer_preset>---*/
  void clear_presets();
  /*---AUTO_GEN_PARSE<CB:kodi_addon_visualization_clear_presets>---*/

private:
  std::vector<std::string> m_presets; /*!< cached preset list */

  KODI_HANDLE m_addonInstance;
};

} /* namespace ADDON */
