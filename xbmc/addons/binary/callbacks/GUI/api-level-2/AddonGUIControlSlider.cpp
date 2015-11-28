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
#include "guilib/GUISliderControl.h"
#include "guilib/GUISpinControl.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlSlider.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_Slider::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Slider.SetVisible        = CAddonGUI_Control_Slider::SetVisible;
  callbacks->Control.Slider.GetDescription    = CAddonGUI_Control_Slider::GetDescription;
  callbacks->Control.Slider.SetIntRange       = CAddonGUI_Control_Slider::SetIntRange;
  callbacks->Control.Slider.SetIntValue       = CAddonGUI_Control_Slider::SetIntValue;
  callbacks->Control.Slider.GetIntValue       = CAddonGUI_Control_Slider::GetIntValue;
  callbacks->Control.Slider.SetIntInterval    = CAddonGUI_Control_Slider::SetIntInterval;
  callbacks->Control.Slider.SetPercentage     = CAddonGUI_Control_Slider::SetPercentage;
  callbacks->Control.Slider.GetPercentage     = CAddonGUI_Control_Slider::GetPercentage;
  callbacks->Control.Slider.SetFloatRange     = CAddonGUI_Control_Slider::SetFloatRange;
  callbacks->Control.Slider.SetFloatValue     = CAddonGUI_Control_Slider::SetFloatValue;
  callbacks->Control.Slider.GetFloatValue     = CAddonGUI_Control_Slider::GetFloatValue;
  callbacks->Control.Slider.SetFloatInterval  = CAddonGUI_Control_Slider::SetFloatInterval;
}

void CAddonGUI_Control_Slider::SetVisible(void *addonData, GUIHANDLE handle, bool yesNo)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIControl *pControl = (CGUIControl*)handle;
  pControl->SetVisible(yesNo);
}

void CAddonGUI_Control_Slider::GetDescription(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  if (!handle)
    return;

  std::string text = static_cast<CGUISliderControl*>(handle)->GetDescription();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

void CAddonGUI_Control_Slider::SetIntRange(void *addonData, GUIHANDLE handle, int iStart, int iEnd)
{
  if (handle)
    static_cast<CGUISliderControl*>(handle)->SetRange(iStart, iEnd);
}

void CAddonGUI_Control_Slider::SetIntValue(void *addonData, GUIHANDLE handle, int iValue)
{
  if (!handle)
    return;

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SPIN_CONTROL_TYPE_INT);
  pControl->SetIntValue(iValue);
}

int CAddonGUI_Control_Slider::GetIntValue(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0;

  return static_cast<CGUISliderControl*>(handle)->GetIntValue();
}

void CAddonGUI_Control_Slider::SetIntInterval(void *addonData, GUIHANDLE handle, int iInterval)
{
  if (handle)
    static_cast<CGUISliderControl*>(handle)->SetIntInterval(iInterval);
}

void CAddonGUI_Control_Slider::SetPercentage(void *addonData, GUIHANDLE handle, float fPercent)
{
  if (!handle)
    return;

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SPIN_CONTROL_TYPE_FLOAT);
  pControl->SetPercentage(fPercent);
}

float CAddonGUI_Control_Slider::GetPercentage(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return 0.0f;

  return static_cast<CGUISliderControl*>(handle)->GetPercentage();
}

void CAddonGUI_Control_Slider::SetFloatRange(void *addonData, GUIHANDLE handle, float fStart, float fEnd)
{
  if (handle)
    static_cast<CGUISliderControl*>(handle)->SetFloatRange(fStart, fEnd);
}

void CAddonGUI_Control_Slider::SetFloatValue(void *addonData, GUIHANDLE handle, float iValue)
{
  if (!handle)
    return;

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SPIN_CONTROL_TYPE_FLOAT);
  pControl->SetFloatValue(iValue);
}

float CAddonGUI_Control_Slider::GetFloatValue(void *addonData, GUIHANDLE handle)
{
  if (!!handle)
    return 0.0f;

  return static_cast<CGUISliderControl*>(handle)->GetFloatValue();
}

void CAddonGUI_Control_Slider::SetFloatInterval(void *addonData, GUIHANDLE handle, float fInterval)
{
  if (handle)
    static_cast<CGUISliderControl*>(handle)->SetFloatInterval(fInterval);
}

}; /* namespace V2 */
}; /* namespace GUILIB */
