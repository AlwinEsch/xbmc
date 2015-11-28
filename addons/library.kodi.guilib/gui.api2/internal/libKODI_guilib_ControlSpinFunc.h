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

/*
 * GUILib.h EOF header, passed there (out of normal code style) to reduce
 * not needed parts, to have only add-on programming related stuff there.
 */

namespace GUILIB
{
namespace V2
{
  inline CAddonGUISpinControl::CAddonGUISpinControl(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_Spin(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUISpinControl can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUISpinControl::~CAddonGUISpinControl()
  {
  }

  inline void CAddonGUISpinControl::SetVisible(bool yesNo)
  {
    m_cb->Control.Spin.SetVisible(m_Handle->addonData, m_ControlHandle, yesNo);
  }

  inline void CAddonGUISpinControl::SetText(const std::string& label)
  {
    m_cb->Control.Spin.SetText(m_Handle->addonData, m_ControlHandle, label.c_str());
  }

  inline void CAddonGUISpinControl::Clear()
  {
    m_cb->Control.Spin.Clear(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUISpinControl::AddLabel(const std::string& label, int iValue)
  {
    m_cb->Control.Spin.AddLabel(m_Handle->addonData, m_ControlHandle, label.c_str(), iValue);
  }

  inline int CAddonGUISpinControl::GetValue()
  {
    return m_cb->Control.Spin.GetValue(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUISpinControl::SetValue(int iValue)
  {
    m_cb->Control.Spin.SetValue(m_Handle->addonData, m_ControlHandle, iValue);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
