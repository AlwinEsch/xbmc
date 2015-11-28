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
#include "internal/libKODI_guilib_internal.h"
#include "internal/libKODI_guilib_ControlSpinHead.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUISpinControl
  {
  public:
    CAddonGUISpinControl(CAddonGUIWindow* window, int controlId);
    virtual ~CAddonGUISpinControl();

    virtual void SetVisible(bool visible);

    virtual void SetText(const std::string& label);

    virtual void AddLabel(const std::string& label, int iValue);
    virtual void Clear();

    virtual void SetValue(int iValue);
    virtual int GetValue();

    IMPL_GUI_SPIN_CONTROL;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlSpinFunc.h"
