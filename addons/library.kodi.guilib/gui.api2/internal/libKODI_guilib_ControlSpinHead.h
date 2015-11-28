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
  class CAddonGUISpinControl;

  typedef void GUIControl_Spin_SetVisible
      (void         *addonData,
       GUIHANDLE     spinhandle,
       bool          yesNo);

  typedef void GUIControl_Spin_SetText
      (void         *addonData,
       GUIHANDLE     spinhandle,
       const char   *label);

  typedef void GUIControl_Spin_Clear
      (void         *addonData,
       GUIHANDLE     spinhandle);

  typedef void GUIControl_Spin_AddLabel
      (void         *addonData,
       GUIHANDLE     spinhandle,
       const char   *label,
       int           iValue);

  typedef int  GUIControl_Spin_GetValue
      (void         *addonData,
       GUIHANDLE     spinhandle);

  typedef void GUIControl_Spin_SetValue
      (void         *addonData,
       GUIHANDLE     spinhandle,
       int           iValue);

  typedef struct CB_GUILib_Control_Spin
  {
    GUIControl_Spin_SetVisible*          SetVisible;
    GUIControl_Spin_SetText*             SetText;
    GUIControl_Spin_Clear*               Clear;
    GUIControl_Spin_AddLabel*            AddLabel;
    GUIControl_Spin_GetValue*            GetValue;
    GUIControl_Spin_SetValue*            SetValue;
  } CB_GUILib_Control_Spin;

  #define IMPL_GUI_SPIN_CONTROL                 \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* namespace V2 */
}; /* namespace GUILIB */
