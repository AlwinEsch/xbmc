/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_ADDONINSTANCE_SCREENSAVER_H
#define C_API_ADDONINSTANCE_SCREENSAVER_H

#include "../addon_base.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* KODI_ADDON_SCREENSAVER_HDL;

  struct SCREENSAVER_PROPS
  {
    ADDON_HARDWARE_CONTEXT2 device;
    int x;
    int y;
    int width;
    int height;
    float pixelRatio;
    char* name;
    char* presets;
    char* profile;
  };

  typedef KODI_ADDON_SCREENSAVER_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_SCREENSAVER_CREATE_V1)(KODI_OWN_HDL kodi_hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_SCREENSAVER_DESTROY_V1)(KODI_ADDON_SCREENSAVER_HDL hdl);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_SCREENSAVER_START_V1)(KODI_ADDON_SCREENSAVER_HDL hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_SCREENSAVER_STOP_V1)(KODI_ADDON_SCREENSAVER_HDL hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_SCREENSAVER_RENDER_V1)(KODI_ADDON_SCREENSAVER_HDL hdl);

  typedef struct KODI_ADDON_SCREENSAVER_FUNC
  {
    PFN_KODI_ADDON_SCREENSAVER_CREATE_V1 create;
    PFN_KODI_ADDON_SCREENSAVER_DESTROY_V1 destroy;
    PFN_KODI_ADDON_SCREENSAVER_START_V1 start;
    PFN_KODI_ADDON_SCREENSAVER_STOP_V1 stop;
    PFN_KODI_ADDON_SCREENSAVER_RENDER_V1 render;
  } KODI_ADDON_SCREENSAVER_FUNC;

  ATTR_DLL_EXPORT void kodi_addon_screensaver_get_properties(KODI_OWN_HDL hdl, struct SCREENSAVER_PROPS* props) __INTRODUCED_IN_KODI(1);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_SCREENSAVER_H */
