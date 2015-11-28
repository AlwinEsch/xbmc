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

  class CAddonGUI_Control_Spin
  {
  public:
    static void Init(CB_GUILib *callbacks);

    static void SetVisible(void *addonData, GUIHANDLE spinhandle, bool yesNo);
    static void SetText(void *addonData, GUIHANDLE spinhandle, const char *label);
    static void Clear(void *addonData, GUIHANDLE spinhandle);
    static void AddLabel(void *addonData, GUIHANDLE spinhandle, const char *label, int iValue);
    static int GetValue(void *addonData, GUIHANDLE spinhandle);
    static void SetValue(void *addonData, GUIHANDLE spinhandle, int iValue);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */
