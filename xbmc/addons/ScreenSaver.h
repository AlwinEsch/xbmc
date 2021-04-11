/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/kodi-dev-kit/include/kodi/c-api/addon-instance/screensaver.h"
#include "interface/InstanceHandler.h"

namespace ADDON
{

class CScreenSaver : public KODI::ADDONS::INTERFACE::IAddonInstanceHandler
{
public:
  explicit CScreenSaver(const AddonInfoPtr& addonInfo);
  ~CScreenSaver() override;

  bool Start();
  void Stop();
  void Render();

  void GetProperties(struct SCREENSAVER_PROPS* props);
  /*---AUTO_GEN_PARSE<CB:kodi_addon_screensaver_get_properties>---*/

private:
  KODI_HANDLE m_addonInstance;
};

} /* namespace ADDON */
