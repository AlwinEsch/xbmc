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

  inline CAddonGUIEditControl::CAddonGUIEditControl(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_Edit(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIEditControl can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUIEditControl::~CAddonGUIEditControl()
  {
  }

  inline void CAddonGUIEditControl::SetVisible(bool yesNo)
  {
    m_cb->Control.Edit.SetVisible(m_Handle->addonData, m_ControlHandle, yesNo);
  }

  inline void CAddonGUIEditControl::SetLabel(const std::string& label)
  {
    m_cb->Control.Edit.SetLabel(m_Handle->addonData, m_ControlHandle, label.c_str(), 0);
  }

  inline std::string CAddonGUIEditControl::GetLabel() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.Edit.GetLabel(m_Handle->addonData, m_ControlHandle, text[0], size, 0);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIEditControl::SetLabel2(const std::string& label)
  {
    m_cb->Control.Edit.SetLabel(m_Handle->addonData, m_ControlHandle, label.c_str(), 1);
  }

  inline std::string CAddonGUIEditControl::GetLabel2() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.Edit.GetLabel(m_Handle->addonData, m_ControlHandle, text[0], size, 1);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIEditControl::SetCursorPosition(unsigned int iPosition)
  {
    m_cb->Control.Edit.SetCursorPosition(m_Handle->addonData, m_ControlHandle, iPosition);
  }

  inline unsigned int CAddonGUIEditControl::GetCursorPosition()
  {
    return m_cb->Control.Edit.GetCursorPosition(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIEditControl::SetInputType(AddonGUIInputType type, const std::string& heading)
  {
    m_cb->Control.Edit.SetInputType(m_Handle->addonData, m_ControlHandle, type, heading.c_str());
  }

  inline void CAddonGUIEditControl::SetSelected(bool selected)
  {
    m_cb->Control.Edit.SetSelected(m_Handle->addonData, m_ControlHandle, selected);
  }

  inline float CAddonGUIEditControl::GetWidth()
  {
    return m_cb->Control.Edit.GetWidth(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIEditControl::SetMinWidth(float minWidth)
  {
    m_cb->Control.Edit.SetMinWidth(m_Handle->addonData, m_ControlHandle, minWidth);
  }

  inline void CAddonGUIEditControl::SetAlpha(unsigned char alpha)
  {
    m_cb->Control.Edit.SetAlpha(m_Handle->addonData, m_ControlHandle, alpha);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
