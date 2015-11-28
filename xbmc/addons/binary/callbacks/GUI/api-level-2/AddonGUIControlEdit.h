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

  struct CAddonGUI_Control_Edit
  {
    static void Init(CB_GUILib *callbacks);

    static void SetLabel(void *addonData, GUIHANDLE handle, const char *label, unsigned int number /* = 0 */);
    static void GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize, unsigned int number /* = 0 */);
    static unsigned int GetCursorPosition(void *addonData, GUIHANDLE handle);
    static void SetCursorPosition(void *addonData, GUIHANDLE handle, unsigned int iPosition);
    static void SetInputType(void *addonData, GUIHANDLE handle, AddonGUIInputType type, const char *heading);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */
