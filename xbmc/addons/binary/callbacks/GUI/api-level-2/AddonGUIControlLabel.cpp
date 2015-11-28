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
#include "guilib/GUILabelControl.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlLabel.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_Label::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Label.SetVisible     = CAddonGUI_Control_Label::SetVisible;
  callbacks->Control.Label.GetDescription = CAddonGUI_Control_Label::GetDescription;
  callbacks->Control.Label.SetLabel       = CAddonGUI_Control_Label::SetLabel;
  callbacks->Control.Label.GetWidth       = CAddonGUI_Control_Label::GetWidth;
  callbacks->Control.Label.SetWidth       = CAddonGUI_Control_Label::SetWidth;
  callbacks->Control.Label.ShowCursor     = CAddonGUI_Control_Label::ShowCursor;
  callbacks->Control.Label.SetCursorPos   = CAddonGUI_Control_Label::SetCursorPos;
  callbacks->Control.Label.GetCursorPos   = CAddonGUI_Control_Label::GetCursorPos;
  callbacks->Control.Label.SetWidthControl= CAddonGUI_Control_Label::SetWidthControl;
  callbacks->Control.Label.SetAlignment   = CAddonGUI_Control_Label::SetAlignment;
  callbacks->Control.Label.SetHighlight   = CAddonGUI_Control_Label::SetHighlight;
  callbacks->Control.Label.SetSelection   = CAddonGUI_Control_Label::SetSelection;
}

void CAddonGUI_Control_Label::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetVisible(visible);
}

void CAddonGUI_Control_Label::GetDescription(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  if (!handle)
    return;

  std::string text = static_cast<CGUILabelControl*>(handle)->GetDescription();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

void CAddonGUI_Control_Label::SetLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetLabel(label);
}

float CAddonGUI_Control_Label::GetWidth(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0.0f;

  return static_cast<CGUILabelControl*>(handle)->GetWidth();
}

void CAddonGUI_Control_Label::SetWidth(void *addonData, GUIHANDLE handle, float width)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetWidth(width);
}

void CAddonGUI_Control_Label::ShowCursor(void *addonData, GUIHANDLE handle, bool bShow /* = true */)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->ShowCursor(bShow);
}

void CAddonGUI_Control_Label::SetCursorPos(void *addonData, GUIHANDLE handle, int iPos)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetCursorPos(iPos);
}

int CAddonGUI_Control_Label::GetCursorPos(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0;

  return static_cast<CGUILabelControl*>(handle)->GetCursorPos();
}

void CAddonGUI_Control_Label::SetWidthControl(void *addonData, GUIHANDLE handle, float minWidth, bool bScroll)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetWidthControl(minWidth, bScroll);
}

void CAddonGUI_Control_Label::SetAlignment(void *addonData, GUIHANDLE handle, uint32_t align)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetAlignment(align);
}

void CAddonGUI_Control_Label::SetHighlight(void *addonData, GUIHANDLE handle, unsigned int start, unsigned int end)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetHighlight(start, end);
}

void CAddonGUI_Control_Label::SetSelection(void *addonData, GUIHANDLE handle, unsigned int start, unsigned int end)
{
  if (handle)
    static_cast<CGUILabelControl*>(handle)->SetSelection(start, end);
}

}; /* namespace V2 */
}; /* namespace GUILIB */
