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
#include "guilib/GUISettingsSliderControl.h"
#include "guilib/GUISpinControl.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlSettingsSlider.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_SettingsSlider::Init(CB_GUILib *callbacks)
{
  callbacks->Control.SettingsSlider.SetVisible            = CAddonGUI_Control_SettingsSlider::SetVisible;
  callbacks->Control.SettingsSlider.GetDescription        = CAddonGUI_Control_SettingsSlider::GetDescription;
  callbacks->Control.SettingsSlider.SetLabel              = CAddonGUI_Control_SettingsSlider::SetLabel;
  callbacks->Control.SettingsSlider.SetIntRange           = CAddonGUI_Control_SettingsSlider::SetIntRange;
  callbacks->Control.SettingsSlider.SetIntValue           = CAddonGUI_Control_SettingsSlider::SetIntValue;
  callbacks->Control.SettingsSlider.GetIntValue           = CAddonGUI_Control_SettingsSlider::GetIntValue;
  callbacks->Control.SettingsSlider.SetIntInterval        = CAddonGUI_Control_SettingsSlider::SetIntInterval;
  callbacks->Control.SettingsSlider.SetPercentage         = CAddonGUI_Control_SettingsSlider::SetPercentage;
  callbacks->Control.SettingsSlider.GetPercentage         = CAddonGUI_Control_SettingsSlider::GetPercentage;
  callbacks->Control.SettingsSlider.SetFloatRange         = CAddonGUI_Control_SettingsSlider::SetFloatRange;
  callbacks->Control.SettingsSlider.SetFloatValue         = CAddonGUI_Control_SettingsSlider::SetFloatValue;
  callbacks->Control.SettingsSlider.GetFloatValue         = CAddonGUI_Control_SettingsSlider::GetFloatValue;
  callbacks->Control.SettingsSlider.SetFloatInterval      = CAddonGUI_Control_SettingsSlider::SetFloatInterval;
}

void CAddonGUI_Control_SettingsSlider::SetVisible(void *addonData, GUIHANDLE handle, bool yesNo)
{
  if (!handle)
    return;

  CGUIControl *pControl = (CGUIControl*)handle;
  pControl->SetVisible(yesNo);
}

void CAddonGUI_Control_SettingsSlider::GetDescription(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  if (!handle)
    return;

  std::string text = static_cast<CGUISettingsSliderControl*>(handle)->GetDescription();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

void CAddonGUI_Control_SettingsSlider::SetLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  if (handle)
    static_cast<CGUISettingsSliderControl*>(handle)->SetText(label);
}

void CAddonGUI_Control_SettingsSlider::SetIntRange(void *addonData, GUIHANDLE handle, int iStart, int iEnd)
{
  if (handle)
    static_cast<CGUISettingsSliderControl*>(handle)->SetRange(iStart, iEnd);
}

void CAddonGUI_Control_SettingsSlider::SetIntValue(void *addonData, GUIHANDLE handle, int iValue)
{
  if (!handle)
    return;

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
  pControl->SetType(SPIN_CONTROL_TYPE_INT);
  pControl->SetIntValue(iValue);
}

int CAddonGUI_Control_SettingsSlider::GetIntValue(void *addonData, GUIHANDLE handle)
{
  if (handle)
    static_cast<CGUISettingsSliderControl*>(handle)->GetIntValue();
}

void CAddonGUI_Control_SettingsSlider::SetIntInterval(void *addonData, GUIHANDLE handle, int iInterval)
{
  if (handle)
    static_cast<CGUISettingsSliderControl*>(handle)->SetIntInterval(iInterval);
}

void CAddonGUI_Control_SettingsSlider::SetPercentage(void *addonData, GUIHANDLE handle, float fPercent)
{
  if (!handle)
    return;

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
  pControl->SetType(SPIN_CONTROL_TYPE_FLOAT);
  pControl->SetPercentage(fPercent);
}

float CAddonGUI_Control_SettingsSlider::GetPercentage(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0.0f;

  return static_cast<CGUISettingsSliderControl*>(handle)->GetPercentage();
}

void CAddonGUI_Control_SettingsSlider::SetFloatRange(void *addonData, GUIHANDLE handle, float fStart, float fEnd)
{
  if (handle)
    static_cast<CGUISettingsSliderControl*>(handle)->SetFloatRange(fStart, fEnd);
}

void CAddonGUI_Control_SettingsSlider::SetFloatValue(void *addonData, GUIHANDLE handle, float fValue)
{
  if (!handle)
    return;

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
  pControl->SetType(SPIN_CONTROL_TYPE_FLOAT);
  pControl->SetFloatValue(fValue);
}

float CAddonGUI_Control_SettingsSlider::GetFloatValue(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0.0f;

  return static_cast<CGUISettingsSliderControl*>(handle)->GetFloatValue();
}

void CAddonGUI_Control_SettingsSlider::SetFloatInterval(void *addonData, GUIHANDLE handle, float fInterval)
{
  if (handle)
    static_cast<CGUISettingsSliderControl*>(handle)->SetFloatInterval(fInterval);
}

}; /* namespace V2 */
}; /* namespace GUILIB */
