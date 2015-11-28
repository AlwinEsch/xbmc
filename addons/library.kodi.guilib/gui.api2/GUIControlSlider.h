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
#include "internal/libKODI_guilib_ControlSliderHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUISliderControl
  {
  public:
    CAddonGUISliderControl(CAddonGUIWindow* window, int controlId);
    virtual ~CAddonGUISliderControl();

    virtual void        SetVisible(bool yesNo);

    virtual std::string GetDescription();

    virtual void        SetIntRange(int iStart, int iEnd);
    virtual void        SetIntValue(int iValue);
    virtual int         GetIntValue() const;
    virtual void        SetIntInterval(int iInterval);

    virtual void        SetPercentage(float fPercent);
    virtual float       GetPercentage() const;

    virtual void        SetFloatRange(float fStart, float fEnd);
    virtual void        SetFloatValue(float fValue);
    virtual float       GetFloatValue() const;
    virtual void        SetFloatInterval(float fInterval);

    IMPL_GUI_SLIDER_CONTROL;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlSliderFunc.h"
