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
  inline CAddonGUIButtonControl::CAddonGUIButtonControl(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_Button(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIButtonControl can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUIButtonControl::~CAddonGUIButtonControl()
  {
  }

  inline void CAddonGUIButtonControl::SetVisible(bool yesNo)
  {
    m_cb->Control.Button.SetVisible(m_Handle->addonData, m_ControlHandle, yesNo);
  }

  inline void CAddonGUIButtonControl::SetLabel(const std::string& label)
  {
    m_cb->Control.Button.SetLabel(m_Handle->addonData, m_ControlHandle, label.c_str(), 0);
  }

  inline std::string CAddonGUIButtonControl::GetLabel() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.Button.GetLabel(m_Handle->addonData, m_ControlHandle, text[0], size, 0);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIButtonControl::SetLabel2(const std::string& label)
  {
    m_cb->Control.Button.SetLabel(m_Handle->addonData, m_ControlHandle, label.c_str(), 1);
  }

  inline std::string CAddonGUIButtonControl::GetLabel2() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.Button.GetLabel(m_Handle->addonData, m_ControlHandle, text[0], size, 1);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIButtonControl::SetSelected(bool selected)
  {
    m_cb->Control.Button.SetSelected(m_Handle->addonData, m_ControlHandle, selected);
  }

  inline float CAddonGUIButtonControl::GetWidth()
  {
    return m_cb->Control.Button.GetWidth(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIButtonControl::SetMinWidth(float minWidth)
  {
    m_cb->Control.Button.SetMinWidth(m_Handle->addonData, m_ControlHandle, minWidth);
  }

  inline void CAddonGUIButtonControl::SetAlpha(unsigned char alpha)
  {
    m_cb->Control.Button.SetAlpha(m_Handle->addonData, m_ControlHandle, alpha);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
