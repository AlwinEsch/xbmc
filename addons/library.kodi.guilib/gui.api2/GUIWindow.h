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
#include "GUIListItem.h"
#include "internal/libKODI_guilib_WindowHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUIWindow
  {
  public:
    CAddonGUIWindow(
        const std::string&          xmlFilename,
        const std::string&          defaultSkin,
        bool                        forceFallback,
        bool                        asDialog);
    virtual ~CAddonGUIWindow();

    virtual bool Show();
    virtual void Close();

    virtual void DoModal();

    virtual bool SetFocusId(int iControlId);
    virtual int GetFocusId();

    virtual void SetControlLabel(int controlId, const std::string& label);
    virtual bool SetCoordinateResolution(int res);

    virtual void SetProperty(const std::string& key, const std::string& value);
    virtual std::string GetProperty(const std::string& key) const;

    virtual void SetPropertyInt(const std::string& key, int value);
    virtual int GetPropertyInt(const std::string& key) const;

    virtual void SetPropertyBool(const std::string& key, bool value);
    virtual bool GetPropertyBool(const std::string& key) const;

    virtual void SetPropertyDouble(const std::string& key, double value);
    virtual double GetPropertyDouble(const std::string& key) const;

    virtual void ClearProperties();

    virtual GUIHANDLE AddStringItem(const std::string& name, int itemPosition = -1);
    virtual void AddItem(GUIHANDLE item, int itemPosition = -1);
    virtual void AddItem(CAddonGUIListItem *item, int itemPosition = -1);
    virtual void RemoveItem(int itemPosition);
    virtual GUIHANDLE GetListItem(int listPos);
    virtual void SetCurrentListPosition(int listPos);
    virtual int GetCurrentListPosition();
    virtual int GetListSize();
    virtual void ClearList();

    virtual void MarkDirtyRegion();

    /*
     * Callback functions from Kodi to add-on
     */
    virtual bool OnClick(int controlId) { }
    virtual bool OnFocus(int controlId) { }
    virtual bool OnInit() { }
    virtual bool OnAction(int actionId) { }

    /*!
     * @brief If the class is used independent (with "new CAddonGUIWindow") and
     * not as parent (with "cCLASS_own : CAddonGUIWindow") from own must be the
     * callback from Kodi to add-on overdriven with own functions!
     */
    void SetIndependentCallbacks(
      GUIHANDLE     cbhdl,                                          //!< @param The pointer to own handle data structure / class
      bool          (*CBOnInit)  (GUIHANDLE cbhdl),                 //!< @param Own defined window init function
      bool          (*CBOnFocus) (GUIHANDLE cbhdl, int controlId),  //!< @param Own defined focus function
      bool          (*CBOnClick) (GUIHANDLE cbhdl, int controlId),  //!< @param Own defined click function
      bool          (*CBOnAction)(GUIHANDLE cbhdl, int actionId));  //!< @param Own defined action function

    IMPLEMENT_ADDON_GUI_WINDOW;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_WindowFunc.h"
