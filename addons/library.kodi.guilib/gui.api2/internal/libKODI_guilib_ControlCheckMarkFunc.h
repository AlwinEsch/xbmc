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
  inline CAddonGUICheckMarkControl::CAddonGUICheckMarkControl(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_CheckMark(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIButtonControl can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUICheckMarkControl::~CAddonGUICheckMarkControl()
  {
  }

  inline void CAddonGUICheckMarkControl::SetVisible(bool yesNo)
  {
    m_cb->Control.CheckMark.SetVisible(m_Handle->addonData, m_ControlHandle, yesNo);
  }

  inline void CAddonGUICheckMarkControl::SetLabel(const std::string& label)
  {
    m_cb->Control.CheckMark.SetLabel(m_Handle->addonData, m_ControlHandle, label.c_str());
  }

  inline std::string CAddonGUICheckMarkControl::GetLabel() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.CheckMark.GetLabel(m_Handle->addonData, m_ControlHandle, text[0], size);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUICheckMarkControl::SetSelected(bool selected)
  {
    m_cb->Control.CheckMark.SetSelected(m_Handle->addonData, m_ControlHandle, selected);
  }

  inline bool CAddonGUICheckMarkControl::GetSelected()
  {
    return m_cb->Control.CheckMark.GetSelected(m_Handle->addonData, m_ControlHandle);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
