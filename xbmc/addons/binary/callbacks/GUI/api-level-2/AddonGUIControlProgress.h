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

#include "../../../../../../addons/library.kodi.guilib/gui.api2/GUILib.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUI_Control_Progress
  {
  public:
    static void Init(CB_GUILib *callbacks);

    static void SetPercentage(void *addonData, GUIHANDLE handle, float fPercent);
    static float GetPercentage(void *addonData, GUIHANDLE handle);
    static void SetInfo(void *addonData, GUIHANDLE handle, int iInfo);
    static int GetInfo(void *addonData, GUIHANDLE handle);
    static void GetDescription(void *addonData, GUIHANDLE handle, char &text, unsigned int &iMaxStringSize);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */
