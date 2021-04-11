/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ScreenSaver.h"

#include "addons/interface/api/addon-instance/screensaver.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "windowing/GraphicContext.h"
#include "windowing/WinSystem.h"

namespace ADDON
{

CScreenSaver::CScreenSaver(const AddonInfoPtr& addonInfo)
  : IAddonInstanceHandler(ADDON_INSTANCE_SCREENSAVER, addonInfo)
{
  if (CreateInstance(this, m_addonInstance) != ADDON_STATUS_OK)
    CLog::Log(LOGFATAL, "Screensaver: failed to create instance for '{}' and not usable!", ID());
}

CScreenSaver::~CScreenSaver()
{
  /* Destroy the class "kodi::addon::CInstanceScreensaver" on add-on side */
  DestroyInstance(m_addonInstance);
}

bool CScreenSaver::Start()
{
  return m_ifc->kodi_addoninstance_screensaver_h->kodi_addon_screensaver_start_v1(m_addonInstance);
}

void CScreenSaver::Stop()
{
  return m_ifc->kodi_addoninstance_screensaver_h->kodi_addon_screensaver_stop_v1(m_addonInstance);
}

void CScreenSaver::Render()
{
  return m_ifc->kodi_addoninstance_screensaver_h->kodi_addon_screensaver_render_v1(m_addonInstance);
}

void CScreenSaver::GetProperties(struct SCREENSAVER_PROPS* props)
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

} /* namespace ADDON */
