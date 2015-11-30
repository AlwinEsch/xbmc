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

#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{
  class CGUILib : protected CGUILib_Internal
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

    /*\_________________________________________________________________________
    \*/

    /*!
     * @brief Performs a graphical lock of rendering engine
     */
    static void Lock();

    /*!
     * @brief Performs a graphical unlock of previous locked rendering engine
     */
    static void Unlock();

    /*\_________________________________________________________________________
    \*/

    /*!
     * @brief Return the the current screen height with pixel
     */
    static int GetScreenHeight();

    /*!
     * @brief Return the the current screen width with pixel
     */
    static int GetScreenWidth();

    /*!
     * @brief Return the the current screen rendering resolution
     */
    static int GetVideoResolution();

    KODI_GUI_LIBRARY;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */
#include "internal/libKODI_guilib_LibFunc.h"
