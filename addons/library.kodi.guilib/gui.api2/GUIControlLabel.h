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
#include "internal/libKODI_guilib_ControlLabelHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUILabelControl
  {
  public:
    CAddonGUILabelControl(CAddonGUIWindow* window, int controlId);
    virtual ~CAddonGUILabelControl();

    virtual void SetVisible(bool visible);

    virtual void SetLabel(const std::string& text);

    virtual std::string GetDescription();

    virtual void SetWidth(float width);
    virtual float GetWidth();

    virtual void ShowCursor(bool bShow = true);
    virtual void SetCursorPos(int iPos);
    virtual int GetCursorPos();

    virtual void SetWidthControl(float minWidth, bool bScroll);
    virtual void SetAlignment(uint32_t align);
    virtual void SetHighlight(unsigned int start, unsigned int end);
    virtual void SetSelection(unsigned int start, unsigned int end);

    IMPL_GUI_LABEL_CONTROL;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlLabelFunc.h"
