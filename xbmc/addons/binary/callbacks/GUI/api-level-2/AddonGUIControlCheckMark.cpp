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
#include "guilib/GUICheckMarkControl.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlCheckMark.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_CheckMark::Init(CB_GUILib *callbacks)
{
  callbacks->Control.CheckMark.SetVisible  = CAddonGUI_Control_CheckMark::SetVisible;
  callbacks->Control.CheckMark.SetLabel    = CAddonGUI_Control_CheckMark::SetLabel;
  callbacks->Control.CheckMark.GetLabel    = CAddonGUI_Control_CheckMark::GetLabel;
  callbacks->Control.CheckMark.SetSelected = CAddonGUI_Control_CheckMark::SetSelected;
  callbacks->Control.CheckMark.GetSelected = CAddonGUI_Control_CheckMark::GetSelected;
}

void CAddonGUI_Control_CheckMark::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUICheckMarkControl* pCheckMark = static_cast<CGUICheckMarkControl *>(handle);
  pCheckMark->SetVisible(visible);
}

void CAddonGUI_Control_CheckMark::SetLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUICheckMarkControl* pCheckMark = static_cast<CGUICheckMarkControl *>(handle);
  pCheckMark->SetLabel(label);
}

void CAddonGUI_Control_CheckMark::GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUICheckMarkControl* pCheckMark = static_cast<CGUICheckMarkControl *>(handle);
  strncpy(&label, pCheckMark->GetLabel().c_str(), iMaxStringSize);
  iMaxStringSize = pCheckMark->GetLabel().length();
}

void CAddonGUI_Control_CheckMark::SetSelected(void *addonData, GUIHANDLE handle, bool selected)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUICheckMarkControl* pCheckMark = static_cast<CGUICheckMarkControl *>(handle);
  pCheckMark->SetSelected(selected);
}

bool CAddonGUI_Control_CheckMark::GetSelected(void *addonData, GUIHANDLE handle)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return false;

  CGUICheckMarkControl* pCheckMark = static_cast<CGUICheckMarkControl *>(handle);
  return pCheckMark->GetSelected();
}

}; /* namespace V2 */
}; /* namespace GUILIB */
