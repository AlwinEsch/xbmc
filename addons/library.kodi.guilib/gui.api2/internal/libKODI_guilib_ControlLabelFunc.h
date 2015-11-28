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

  inline CAddonGUILabelControl::CAddonGUILabelControl(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_Label(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIEditControl can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUILabelControl::~CAddonGUILabelControl()
  {
  }

  inline void CAddonGUILabelControl::SetVisible(bool visible)
  {
    m_cb->Control.Label.SetVisible(m_Handle->addonData, m_ControlHandle, visible);
  }

  inline void CAddonGUILabelControl::SetLabel(const std::string& text)
  {
    m_cb->Control.Label.SetLabel(m_Handle->addonData, m_ControlHandle, text.c_str());
  }

  inline std::string CAddonGUIEditControl::GetDescription() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.Edit.GetDescription(m_Handle->addonData, m_ControlHandle, text[0], size);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline float CAddonGUILabelControl::GetWidth()
  {
    return m_cb->Control.Label.GetWidth(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUILabelControl::SetWidth(float width)
  {
    m_cb->Control.Label.SetWidth(m_Handle->addonData, m_ControlHandle, width);
  }

  inline void CAddonGUILabelControl::ShowCursor(bool bShow /* = true */)
  {
    m_cb->Control.Label.ShowCursor(m_Handle->addonData, m_ControlHandle, bShow);
  }

  inline void CAddonGUILabelControl::SetCursorPos(int iPos)
  {
    m_cb->Control.Label.SetCursorPos(m_Handle->addonData, m_ControlHandle, iPos);
  }

  inline int CAddonGUILabelControl::GetCursorPos()
  {
    return m_cb->Control.Label.GetCursorPos(m_Handle->addonData, m_ControlHandle);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
