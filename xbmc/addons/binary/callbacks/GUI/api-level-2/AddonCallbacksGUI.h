#pragma once
/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "PlatformDefs.h" // for __stat64, ssize_t
#include "addons/binary/callbacks/IAddonCallback.h"
#include "addons/binary/callbacks/AddonCallbacks.h"

#include "AddonGUIGeneral.h"
#include "AddonGUIControlButton.h"
#include "AddonGUIControlCheckMark.h"
#include "AddonGUIControlEdit.h"
#include "AddonGUIControlLabel.h"
#include "AddonGUIControlProgress.h"
#include "AddonGUIControlRadioButton.h"
#include "AddonGUIControlRendering.h"
#include "AddonGUIControlSettingsSlider.h"
#include "AddonGUIControlSlider.h"
#include "AddonGUIControlSpin.h"
#include "AddonGUIDialogExtendedProgressBar.h"
#include "AddonGUIDialogFileBrowser.h"
#include "AddonGUIDialogKeyboard.h"
#include "AddonGUIDialogNumeric.h"
#include "AddonGUIDialogOK.h"
#include "AddonGUIDialogProgress.h"
#include "AddonGUIDialogSelect.h"
#include "AddonGUIDialogTextViewer.h"
#include "AddonGUIDialogYesNo.h"
#include "AddonGUIListItem.h"
#include "AddonGUIWindow.h"

#include "../../../../../../addons/library.kodi.guilib/gui.api2/GUILib.h"

namespace ADDON
{
  class CAddon;
};

namespace GUILIB
{
namespace V2
{

  class CAddonCallbacksGUI : public ADDON::IAddonCallback
  {
  public:
    CAddonCallbacksGUI(ADDON::CAddon* addon);
    ~CAddonCallbacksGUI();

    static int APILevel() { return m_apiLevel; }
    static std::string Version() { return m_version; }

    /**! \name General Functions */
    CB_GUILib* GetCallbacks() { return m_callbacks; }

  private:
    static constexpr const int   m_apiLevel = 2;
    static constexpr const char* m_version  = "5.8.0";

    CB_GUILib* m_callbacks;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */
