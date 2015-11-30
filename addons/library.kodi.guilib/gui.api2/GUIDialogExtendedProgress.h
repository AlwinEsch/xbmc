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
#include "internal/libKODI_guilib_DialogExtendedProgressHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUIDialogExtendedProgress
  {
  public:
    CAddonGUIDialogExtendedProgress(const std::string& title = "");
    virtual ~CAddonGUIDialogExtendedProgress();

    virtual std::string Title() const;
    virtual void SetTitle(const std::string& strTitle);

    virtual std::string Text() const;
    virtual void SetText(const std::string& strText);

    virtual bool IsFinished() const;
    virtual void MarkFinished();

    virtual float Percentage() const;
    virtual void SetPercentage(float fPercentage);
    virtual void SetProgress(int currentItem, int itemCount);

    IMPL_GUI_EXTENDED_PROGRESS_DIALOG;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogExtendedProgressFunc.h"
