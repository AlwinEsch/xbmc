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

#include "Application.h"
#include "addons/Addon.h"
#include "AddonCallbacksAddon.h"
#include "utils/log.h"

using namespace ADDON;

namespace AddOnLIB
{
namespace V2
{

CAddonCallbacksAddon::CAddonCallbacksAddon(CAddon* addon)
  : ADDON::IAddonCallback(addon, m_apiLevel, m_version),
    m_callbacks(new CB_AddOnLib)
{
  CAddonCB_Audio::Init(m_callbacks);
  CAddonCB_Codec::Init(m_callbacks);
  CAddonCB_Directory::Init(m_callbacks);
  CAddonCB_File::Init(m_callbacks);
  CAddonCB_General::Init(m_callbacks);
  CAddonCB_Network::Init(m_callbacks);
}

CAddonCallbacksAddon::~CAddonCallbacksAddon()
{
  delete m_callbacks;
}

A_DLLEXPORT CB_AddOnLib* ADDONLIB_V2_register_level(void *hdl, int level)
{
  CB_AddOnLib *cb = nullptr;
  if (!hdl)
    CLog::Log(LOGERROR, "libKODI_addon-ERROR: %s is called with NULL handle !!!", __FUNCTION__);
  else
  {
    cb = static_cast<CB_AddOnLib*>(CAddonCallbacks::AddOnLib_RegisterLevel(((AddonCB*)hdl)->addonData, level));
    if (!cb)
      CLog::Log(LOGERROR, "libKODI_addon-ERROR: %s can't get callback table from Kodi !!!", __FUNCTION__);
  }
  return cb;
}

A_DLLEXPORT bool ADDONLIB_V2_unregister(void *hdl, void* cb)
{
  if (hdl && cb)
    CAddonCallbacks::AddOnLib_UnRegisterMe(((AddonCB*)hdl)->addonData, ((CB_AddOnLib*)cb));
}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
