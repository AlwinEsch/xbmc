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
#include "guilib/GUIButtonControl.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlButton.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_Button::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Button.SetVisible     = CAddonGUI_Control_Button::SetVisible;
  callbacks->Control.Button.SetLabel       = CAddonGUI_Control_Button::SetLabel;
  callbacks->Control.Button.GetLabel       = CAddonGUI_Control_Button::GetLabel;
  callbacks->Control.Button.GetDescription = CAddonGUI_Control_Button::GetDescription;
  callbacks->Control.Button.SetSelected    = CAddonGUI_Control_Button::SetSelected;
  callbacks->Control.Button.GetWidth       = CAddonGUI_Control_Button::GetWidth;
  callbacks->Control.Button.SetMinWidth    = CAddonGUI_Control_Button::SetMinWidth;
  callbacks->Control.Button.SetAlpha       = CAddonGUI_Control_Button::SetAlpha;
}

void CAddonGUI_Control_Button::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIButtonControl* pButton = static_cast<CGUIButtonControl *>(handle);
  pButton->SetVisible(visible);
}

void CAddonGUI_Control_Button::SetLabel(void *addonData, GUIHANDLE handle, const char *label, unsigned int number /* = 0 */)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIButtonControl* pButton = static_cast<CGUIButtonControl *>(handle);
  (number == 0) ? pButton->SetLabel(label) : pButton->SetLabel2(label);
}

void CAddonGUI_Control_Button::GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize, unsigned int number /* = 0 */)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIButtonControl* pButton = static_cast<CGUIButtonControl *>(handle);
  std::string text = (number == 0) ? pButton->GetLabel() : pButton->GetLabel2();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

void CAddonGUI_Control_Button::GetDescription(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  if (!handle)
    return;

  std::string text = static_cast<CGUIButtonControl*>(handle)->GetDescription();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

void CAddonGUI_Control_Button::SetSelected(void *addonData, GUIHANDLE handle, bool selected)
{
  if (handle)
    static_cast<CGUIButtonControl*>(handle)->SetSelected(selected);
}

float CAddonGUI_Control_Button::GetWidth(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0.0f;

  return static_cast<CGUIButtonControl *>(handle)->GetWidth();
}

void CAddonGUI_Control_Button::SetMinWidth(void *addonData, GUIHANDLE handle, float minWidth)
{
  if (handle)
    static_cast<CGUIButtonControl*>(handle)->SetMinWidth(minWidth);
}

void CAddonGUI_Control_Button::SetAlpha(void *addonData, GUIHANDLE handle, unsigned char alpha)
{
  if (handle)
    static_cast<CGUIButtonControl*>(handle)->SetAlpha(alpha);
}

}; /* namespace V2 */
}; /* namespace GUILIB */
