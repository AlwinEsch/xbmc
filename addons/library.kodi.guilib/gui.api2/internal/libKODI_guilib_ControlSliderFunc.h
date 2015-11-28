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
  inline CAddonGUISliderControl::CAddonGUISliderControl(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_Slider(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUISliderControl can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUISliderControl::~CAddonGUISliderControl()
  {
  }

  inline void CAddonGUISliderControl::SetVisible(bool yesNo)
  {
    m_cb->Control.Slider.SetVisible(m_Handle->addonData, m_ControlHandle, yesNo);
  }

  inline std::string CAddonGUISliderControl::GetDescription() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.Slider.GetDescription(m_Handle->addonData, m_ControlHandle, text[0], size);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUISliderControl::SetIntRange(int iStart, int iEnd)
  {
    m_cb->Control.Slider.SetIntRange(m_Handle->addonData, m_ControlHandle, iStart, iEnd);
  }

  inline void CAddonGUISliderControl::SetIntValue(int iValue)
  {
    m_cb->Control.Slider.SetIntValue(m_Handle->addonData, m_ControlHandle, iValue);
  }

  inline int CAddonGUISliderControl::GetIntValue() const
  {
    return m_cb->Control.Slider.GetIntValue(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUISliderControl::SetIntInterval(int iInterval)
  {
    m_cb->Control.Slider.SetIntInterval(m_Handle->addonData, m_ControlHandle, iInterval);
  }

  inline void CAddonGUISliderControl::SetPercentage(float fPercent)
  {
    m_cb->Control.Slider.SetPercentage(m_Handle->addonData, m_ControlHandle, fPercent);
  }

  inline float CAddonGUISliderControl::GetPercentage() const
  {
    return m_cb->Control.Slider.GetPercentage(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUISliderControl::SetFloatRange(float fStart, float fEnd)
  {
    m_cb->Control.Slider.SetFloatRange(m_Handle->addonData, m_ControlHandle, fStart, fEnd);
  }

  inline void CAddonGUISliderControl::SetFloatValue(float fValue)
  {
    m_cb->Control.Slider.SetFloatValue(m_Handle->addonData, m_ControlHandle, fValue);
  }

  inline float CAddonGUISliderControl::GetFloatValue() const
  {
    return m_cb->Control.Slider.GetFloatValue(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUISliderControl::SetFloatInterval(float fInterval)
  {
    m_cb->Control.Slider.SetFloatInterval(m_Handle->addonData, m_ControlHandle, fInterval);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
