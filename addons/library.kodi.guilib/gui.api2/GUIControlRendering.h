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

#include "definations.h"
#include "internal/libKODI_guilib_ControlRenderingHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUIRenderingControl
  {
  public:
    CAddonGUIRenderingControl(CAddonGUIWindow* window, int controlId);
    virtual ~CAddonGUIRenderingControl();

    /*
     * Callback functions from Kodi to add-on
     */
    virtual bool Create(int x, int y, int w, int h, void* device) { return false; }
    virtual void Render() { }
    virtual void Stop() { }
    virtual bool Dirty() { return false; }

    /*!
     * @brief If the class is used independent (with "new CAddonGUIRenderingControl")
     * and not as parent (with "cCLASS_own : CAddonGUIRenderingControl") from own must
     * be the callback from Kodi to add-on overdriven with own functions!
     */
    void SetIndependentCallbacks(
        GUIHANDLE             cbhdl,
        bool      (*CBCreate)(GUIHANDLE cbhdl,
                              int       x,
                              int       y,
                              int       w,
                              int       h,
                              void*     device),
        void      (*CBRender)(GUIHANDLE cbhdl),
        void      (*CBStop)  (GUIHANDLE cbhdl),
        bool      (*CBDirty) (GUIHANDLE cbhdl));

    IMPL_GUI_RENDERING_CONTROL;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlRenderingFunc.h"
