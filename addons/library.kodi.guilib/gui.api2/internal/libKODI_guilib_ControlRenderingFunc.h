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

  inline CAddonGUIRenderingControl::CAddonGUIRenderingControl(
        CAddonGUIWindow*      window,
        int                   controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_RenderAddon(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (m_ControlHandle)
        m_cb->Control.Rendering.SetCallbacks(m_Handle->addonData, m_ControlHandle, this,
                                             OnCreateCB, OnRenderCB, OnStopCB, OnDirtyCB);
      else
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIRenderingControl can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUIRenderingControl::~CAddonGUIRenderingControl()
  {
    m_cb->Control.Rendering.Delete(m_Handle->addonData, m_ControlHandle);
  }

  /*!
   * Kodi to add-on override defination function to use if class becomes used
   * independet.
   */

  inline void CAddonGUIRenderingControl::SetIndependentCallbacks(
        GUIHANDLE             cbhdl,
        bool      (*CBCreate)(GUIHANDLE cbhdl,
                              int       x,
                              int       y,
                              int       w,
                              int       h,
                              void*     device),
        void      (*CBRender)(GUIHANDLE cbhdl),
        void      (*CBStop)  (GUIHANDLE cbhdl),
        bool      (*CBDirty) (GUIHANDLE cbhdl))
  {
    if (!m_Handle || !m_cb || !cbhdl ||
        !CBCreate || !CBRender || !CBStop || !CBDirty)
    {
        fprintf(stderr, "libKODI_gui-ERROR: SetIndependentCallbacks called with nullptr !!!\n");
        return;
    }

    m_cb->Control.Rendering.SetCallbacks(m_Handle->addonData, m_ControlHandle, cbhdl,
                                         CBCreate, CBRender, CBStop, CBDirty);
  }

  /*!
   * Defined callback functions from Kodi to add-on, for use in parent / child system
   * (is private)!
   */

  inline bool CAddonGUIRenderingControl::OnCreateCB(GUIHANDLE cbhdl, int x, int y, int w, int h, void* device)
  {
    return static_cast<CAddonGUIRenderingControl*>(cbhdl)->Create(x, y, w, h, device);
  }

  inline void CAddonGUIRenderingControl::OnRenderCB(GUIHANDLE cbhdl)
  {
    static_cast<CAddonGUIRenderingControl*>(cbhdl)->Render();
  }

  inline void CAddonGUIRenderingControl::OnStopCB(GUIHANDLE cbhdl)
  {
    static_cast<CAddonGUIRenderingControl*>(cbhdl)->Stop();
  }

  inline bool CAddonGUIRenderingControl::OnDirtyCB(GUIHANDLE cbhdl)
  {
    return static_cast<CAddonGUIRenderingControl*>(cbhdl)->Dirty();
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
