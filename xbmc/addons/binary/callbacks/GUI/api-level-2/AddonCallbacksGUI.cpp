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

#include "addons/Addon.h"
#include "AddonCallbacksGUI.h"
#include "utils/log.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

CAddonCallbacksGUI::CAddonCallbacksGUI(CAddon* addon)
  : ADDON::IAddonCallback(addon, m_apiLevel, m_version),
    m_callbacks(new CB_GUILib)
{
  CAddonGUI_General                    ::Init(m_callbacks);
  CAddonGUI_Control_Button             ::Init(m_callbacks);
  CAddonGUI_Control_CheckMark          ::Init(m_callbacks);
  CAddonGUI_Control_Edit               ::Init(m_callbacks);
  CAddonGUI_Control_Label              ::Init(m_callbacks);
  CAddonGUI_Control_Progress           ::Init(m_callbacks);
  CAddonGUI_Control_RadioButton        ::Init(m_callbacks);
  CAddonGUI_Control_Rendering          ::Init(m_callbacks);
  CAddonGUI_Control_SettingsSlider     ::Init(m_callbacks);
  CAddonGUI_Control_Slider             ::Init(m_callbacks);
  CAddonGUI_Control_Spin               ::Init(m_callbacks);
  CAddonGUI_Dialog_ExtendedProgress    ::Init(m_callbacks);
  CAddonGUI_Dialog_FileBrowser         ::Init(m_callbacks);
  CAddonGUI_Dialog_Keyboard            ::Init(m_callbacks);
  CAddonGUI_Dialog_Numeric             ::Init(m_callbacks);
  CAddonGUI_Dialog_OK                  ::Init(m_callbacks);
  CAddonGUI_Dialog_Progress            ::Init(m_callbacks);
  CAddonGUI_Dialog_Select              ::Init(m_callbacks);
  CAddonGUI_Dialog_TextViewer          ::Init(m_callbacks);
  CAddonGUI_Dialog_YesNo               ::Init(m_callbacks);
  CAddonGUI_ListItem                   ::Init(m_callbacks);
  CAddonGUI_Window                     ::Init(m_callbacks);
}

CAddonCallbacksGUI::~CAddonCallbacksGUI()
{
  delete m_callbacks;
}

A_DLLEXPORT CB_GUILib* GUILIB_V2_register_level(void *hdl, int level)
{
  CB_GUILib *cb = nullptr;
  if (!hdl)
    CLog::Log(LOGERROR, "CAddonCallbacksGUI - %s - Invalid input! Channels is a NULL pointer!", __FUNCTION__);
  else
  {
    cb = static_cast<CB_GUILib*>(CAddonCallbacks::GUILib_RegisterLevel(((AddonCB*)hdl)->addonData, level));
    if (!cb)
      CLog::Log(LOGERROR, "CAddonCallbacksGUI - %s -  GUILIB_V2_register_level can't get callback table from Kodi !!!", __FUNCTION__);
  }
  return cb;
}

A_DLLEXPORT bool GUILIB_V2_unregister(void *hdl, void* cb)
{
  if (hdl && cb)
    CAddonCallbacks::GUILib_UnRegisterMe(((AddonCB*)hdl)->addonData, ((CB_GUILib*)cb));
}

}; /* namespace V2 */
}; /* namespace GUILIB */
