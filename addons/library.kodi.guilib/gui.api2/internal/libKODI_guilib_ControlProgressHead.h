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
  class CAddonGUIProgressControl;

  typedef void GUIControl_Progress_SetPercentage
      (void       *addonData,
       GUIHANDLE   handle,
       float       fPercent);

  typedef float GUIControl_Progress_GetPercentage
      (void       *addonData,
       GUIHANDLE   handle);

  typedef void GUIControl_Progress_SetInfo
      (void       *addonData,
       GUIHANDLE   handle,
       int         iInfo);

  typedef int GUIControl_Progress_GetInfo
      (void       *addonData,
       GUIHANDLE   handle);

  typedef void GUIControl_Progress_GetDescription
      (void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef struct CB_GUILib_Control_Progress
  {
    GUIControl_Progress_SetPercentage*   SetPercentage;
    GUIControl_Progress_GetPercentage*   GetPercentage;
    GUIControl_Progress_SetInfo*         SetInfo;
    GUIControl_Progress_GetInfo*         GetInfo;
    GUIControl_Progress_GetDescription*  GetDescription;
  } CB_GUILib_Control_Progress;

  #define IMPL_GUI_PROGRESS_CONTROL             \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* namespace V2 */
}; /* namespace GUILIB */
