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
  class CAddonGUILabelControl;

  typedef void GUIControl_Label_SetVisible
      (void         *addonData,
       GUIHANDLE     handle,
       bool          visible);

  typedef void GUIControl_Label_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *text);

  typedef void GUIControl_Label_GetDescription
      (void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef float GUIControl_Label_GetWidth
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Label_SetWidth
      (void         *addonData,
       GUIHANDLE     handle,
       float         width);

  typedef void GUIControl_Label_ShowCursor
      (void         *addonData,
       GUIHANDLE     handle,
       bool          bShow);

  typedef void GUIControl_Label_SetCursorPos
      (void         *addonData,
       GUIHANDLE     handle,
       int           iPos);

  typedef int  GUIControl_Label_GetCursorPos
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Label_SetWidthControl
      (void         *addonData,
       GUIHANDLE     handle,
       float         minWidth,
       bool          bScroll);

  typedef void GUIControl_Label_SetAlignment
      (void         *addonData,
       GUIHANDLE     handle,
       uint32_t align);

  typedef void GUIControl_Label_SetHighlight
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned int  start,
       unsigned int  end);

  typedef void GUIControl_Label_SetSelection
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned int  start,
       unsigned int  end);

  typedef struct CB_GUILib_Control_Label
  {
    GUIControl_Label_SetVisible*       SetVisible;
    GUIControl_Label_SetLabel*         SetLabel;
    GUIControl_Label_GetDescription*   GetDescription;
    GUIControl_Label_GetWidth*         GetWidth;
    GUIControl_Label_SetWidth*         SetWidth;
    GUIControl_Label_ShowCursor*       ShowCursor;
    GUIControl_Label_SetCursorPos*     SetCursorPos;
    GUIControl_Label_GetCursorPos*     GetCursorPos;
    GUIControl_Label_SetWidthControl*  SetWidthControl;
    GUIControl_Label_SetAlignment*     SetAlignment;
    GUIControl_Label_SetHighlight*     SetHighlight;
    GUIControl_Label_SetSelection*     SetSelection;
  } CB_GUILib_Control_Label;

  #define IMPL_GUI_LABEL_CONTROL                \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* namespace V2 */
}; /* namespace GUILIB */
