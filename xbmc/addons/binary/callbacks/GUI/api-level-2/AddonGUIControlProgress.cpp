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

#include "addons/Addon.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "guilib/GUIProgressControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlProgress.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_Progress::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Progress.SetPercentage = CAddonGUI_Control_Progress::SetPercentage;
  callbacks->Control.Progress.GetPercentage = CAddonGUI_Control_Progress::GetPercentage;
  callbacks->Control.Progress.SetInfo       = CAddonGUI_Control_Progress::SetInfo;
  callbacks->Control.Progress.GetInfo       = CAddonGUI_Control_Progress::GetInfo;
}

void CAddonGUI_Control_Progress::SetPercentage(void *addonData, GUIHANDLE handle, float fPercent)
{
  if (handle)
    static_cast<CGUIProgressControl*>(handle)->SetPercentage(fPercent);
}

float CAddonGUI_Control_Progress::GetPercentage(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0.0;

  return static_cast<CGUIProgressControl*>(handle)->GetPercentage();
}

void CAddonGUI_Control_Progress::SetInfo(void *addonData, GUIHANDLE handle, int iInfo)
{
  if (handle)
    static_cast<CGUIProgressControl*>(handle)->SetInfo(iInfo);
}

int CAddonGUI_Control_Progress::GetInfo(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return -1;

  return static_cast<CGUIProgressControl*>(handle)->GetInfo();
}

void CAddonGUI_Control_Progress::GetDescription(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  if (!handle)
    return;

  std::string text = static_cast<CGUIProgressControl*>(handle)->GetDescription();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

}; /* namespace V2 */
}; /* namespace GUILIB */
