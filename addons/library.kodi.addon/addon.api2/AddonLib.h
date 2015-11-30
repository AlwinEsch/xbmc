#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
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

#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{

  class CAddonLib : protected CAddonLib_Internal
  {
  public:
    /*!
     * @brief Resolve all callback methods
     * @param handle Pointer to the add-on
     * @return True when all methods were resolved, false otherwise.
     */
    static bool RegisterMe(void *handle);

    /*!
     * @brief Release all callback methods and close handling with them
     */
    static void UnRegisterMe();

    KODI_ADDON_LIBRARY;
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_AddonLibFunc.h"
