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
#include "guilib/GUIEditControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlButton.h"
#include "AddonGUIControlEdit.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Control_Edit::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Edit.SetVisible              = CAddonGUI_Control_Button::SetVisible;
  callbacks->Control.Edit.SetLabel                = CAddonGUI_Control_Edit::SetLabel;
  callbacks->Control.Edit.GetLabel                = CAddonGUI_Control_Edit::GetLabel;
  callbacks->Control.Edit.SetCursorPosition       = CAddonGUI_Control_Edit::SetCursorPosition;
  callbacks->Control.Edit.GetCursorPosition       = CAddonGUI_Control_Edit::GetCursorPosition;
  callbacks->Control.Edit.SetSelected             = CAddonGUI_Control_Button::SetSelected;
  callbacks->Control.Edit.GetWidth                = CAddonGUI_Control_Button::GetWidth;
  callbacks->Control.Edit.SetMinWidth             = CAddonGUI_Control_Button::SetMinWidth;
  callbacks->Control.Edit.SetAlpha                = CAddonGUI_Control_Button::SetAlpha;
  callbacks->Control.Edit.SetInputType            = CAddonGUI_Control_Edit::SetInputType;
}

void CAddonGUI_Control_Edit::SetLabel(void *addonData, GUIHANDLE handle, const char *label, unsigned int number /* = 0 */)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIEditControl* pControl = static_cast<CGUIEditControl *>(handle);
  (number == 0) ? pControl->SetLabel(label) : pControl->SetLabel2(label);
}

void CAddonGUI_Control_Edit::GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize, unsigned int number /* = 0 */)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIEditControl* pControl = static_cast<CGUIEditControl *>(handle);
  std::string text = (number == 0) ? pControl->GetLabel() : pControl->GetLabel2();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

unsigned int CAddonGUI_Control_Edit::GetCursorPosition(void *addonData, GUIHANDLE handle)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return 0;

  CGUIEditControl* pControl = static_cast<CGUIEditControl *>(handle);
  return pControl->GetCursorPosition();
}

void CAddonGUI_Control_Edit::SetCursorPosition(void *addonData, GUIHANDLE handle, unsigned int iPosition)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIEditControl* pControl = static_cast<CGUIEditControl *>(handle);
  pControl->SetCursorPosition(iPosition);
}

void CAddonGUI_Control_Edit::SetInputType(void *addonData, GUIHANDLE handle, AddonGUIInputType type, const char *heading)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper || !handle)
    return;

  CGUIEditControl::INPUT_TYPE kodiType;
  switch (type)
  {
    case ADDON_INPUT_TYPE_TEXT:
      kodiType = CGUIEditControl::INPUT_TYPE_TEXT;
      break;
    case ADDON_INPUT_TYPE_NUMBER:
      kodiType = CGUIEditControl::INPUT_TYPE_NUMBER;
      break;
    case ADDON_INPUT_TYPE_SECONDS:
      kodiType = CGUIEditControl::INPUT_TYPE_SECONDS;
      break;
    case ADDON_INPUT_TYPE_TIME:
      kodiType = CGUIEditControl::INPUT_TYPE_TIME;
      break;
    case ADDON_INPUT_TYPE_DATE:
      kodiType = CGUIEditControl::INPUT_TYPE_DATE;
      break;
    case ADDON_INPUT_TYPE_IPADDRESS:
      kodiType = CGUIEditControl::INPUT_TYPE_IPADDRESS;
      break;
    case ADDON_INPUT_TYPE_PASSWORD:
      kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD;
      break;
    case ADDON_INPUT_TYPE_PASSWORD_MD5:
      kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD_MD5;
      break;
    case ADDON_INPUT_TYPE_SEARCH:
      kodiType = CGUIEditControl::INPUT_TYPE_SEARCH;
      break;
    case ADDON_INPUT_TYPE_FILTER:
      kodiType = CGUIEditControl::INPUT_TYPE_FILTER;
      break;
    case ADDON_INPUT_TYPE_READONLY:
    default:
      kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW;
  }

  CGUIEditControl* pControl = static_cast<CGUIEditControl *>(handle);
  pControl->SetInputType(kodiType, -1); //!< @todo: add support to use standard string heading!
}

}; /* namespace V2 */
}; /* namespace GUILIB */
