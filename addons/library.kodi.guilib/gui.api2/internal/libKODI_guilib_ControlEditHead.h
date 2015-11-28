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

namespace GUILIB
{
namespace V2
{

  class CAddonGUIWindow;
  class CAddonGUIEditControl;

  typedef void GUIControl_Edit_SetVisible
      (void         *addonData,
       GUIHANDLE     handle,
       bool          visible);

  typedef void GUIControl_Edit_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label,
       unsigned int  number /* = 0 */);

  typedef void GUIControl_Edit_GetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       char         &label,
       unsigned int &iMaxStringSize,
       unsigned int  number /* = 0 */);

  typedef void GUIControl_Edit_SetCursorPosition
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned int  iPosition);

  typedef unsigned int GUIControl_Edit_GetCursorPosition
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Edit_SetSelected
      (void         *addonData,
       GUIHANDLE     handle,
       bool          selected);

  typedef float GUIControl_Edit_GetWidth
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Edit_SetMinWidth
      (void         *addonData,
       GUIHANDLE     handle,
       float         minWidth);

  typedef void GUIControl_Edit_SetAlpha
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned char alpha);

  typedef void GUIControl_Edit_SetInputType
      (void         *addonData,
       GUIHANDLE     handle,
       AddonGUIInputType type,
       const char   *heading);

  typedef struct CB_GUILib_Control_Edit
  {
    GUIControl_Edit_SetVisible*        SetVisible;
    GUIControl_Edit_SetLabel*          SetLabel;
    GUIControl_Edit_GetLabel*          GetLabel;
    GUIControl_Edit_SetCursorPosition* SetCursorPosition;
    GUIControl_Edit_GetCursorPosition* GetCursorPosition;
    GUIControl_Edit_SetSelected*       SetSelected;
    GUIControl_Edit_GetWidth*          GetWidth;
    GUIControl_Edit_SetMinWidth*       SetMinWidth;
    GUIControl_Edit_SetAlpha*          SetAlpha;
    GUIControl_Edit_SetInputType*      SetInputType;
  } CB_GUILib_Control_Edit;

  #define IMPL_GUI_EDIT_CONTROL                 \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* namespace V2 */
}; /* namespace GUILIB */
