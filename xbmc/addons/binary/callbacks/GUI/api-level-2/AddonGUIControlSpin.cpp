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
#include "guilib/GUISpinControlEx.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlSpin.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_Spin::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Spin.SetVisible        = CAddonGUI_Control_Spin::SetVisible;
  callbacks->Control.Spin.SetText           = CAddonGUI_Control_Spin::SetText;
  callbacks->Control.Spin.Clear             = CAddonGUI_Control_Spin::Clear;
  callbacks->Control.Spin.AddLabel          = CAddonGUI_Control_Spin::AddLabel;
  callbacks->Control.Spin.GetValue          = CAddonGUI_Control_Spin::GetValue;
  callbacks->Control.Spin.SetValue          = CAddonGUI_Control_Spin::SetValue;
}

void CAddonGUI_Control_Spin::SetVisible(void *addonData, GUIHANDLE handle, bool yesNo)
{
  if (handle)
    static_cast<CGUISpinControlEx*>(handle)->SetVisible(yesNo);
}

void CAddonGUI_Control_Spin::SetText(void *addonData, GUIHANDLE handle, const char *label)
{
  if (handle)
    static_cast<CGUISpinControlEx*>(handle)->SetText(label);
}

void CAddonGUI_Control_Spin::Clear(void *addonData, GUIHANDLE handle)
{
  if (handle)
    static_cast<CGUISpinControlEx*>(handle)->Clear();
}

void CAddonGUI_Control_Spin::AddLabel(void *addonData, GUIHANDLE handle, const char *label, int iValue)
{
  if (handle)
    static_cast<CGUISpinControlEx*>(handle)->AddLabel(label, iValue);
}

int CAddonGUI_Control_Spin::GetValue(void *addonData, GUIHANDLE handle)
{
  if (!handle)
    return -1;

  return static_cast<CGUISpinControlEx*>(handle)->GetValue();
}

void CAddonGUI_Control_Spin::SetValue(void *addonData, GUIHANDLE handle, int iValue)
{
  if (handle)
    static_cast<CGUISpinControlEx*>(handle)->SetValue(iValue);
}

}; /* namespace V2 */
}; /* namespace GUILIB */
