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

  struct CB_GUILib;

  struct CAddonGUI_Control_Label
  {
    static void Init(CB_GUILib *callbacks);

    static void SetVisible(void *addonData, GUIHANDLE handle, bool visible);
    static void SetLabel(void *addonData, GUIHANDLE handle, const char *text);
    static void GetDescription(void *addonData, GUIHANDLE handle, char &text, unsigned int &iMaxStringSize);
    static float GetWidth(void *addonData, GUIHANDLE handle);
    static void SetWidth(void *addonData, GUIHANDLE handle, float width);
    static void ShowCursor(void *addonData, GUIHANDLE handle, bool bShow /* = true */);
    static void SetCursorPos(void *addonData, GUIHANDLE handle, int iPos);
    static int GetCursorPos(void *addonData, GUIHANDLE handle);
    static void SetWidthControl(void *addonData, GUIHANDLE handle, float minWidth, bool bScroll);
    static void SetAlignment(void *addonData, GUIHANDLE handle, uint32_t align);
    static void SetHighlight(void *addonData, GUIHANDLE handle, unsigned int start, unsigned int end);
    static void SetSelection(void *addonData, GUIHANDLE handle, unsigned int start, unsigned int end);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */
