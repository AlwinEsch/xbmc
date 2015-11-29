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
#include "internal/libKODI_addon_DirectoryHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{
  /*\___________________________________________________________________________
  | |
  | |
  | |___________________________________________________________________________
  \*/
  class CAddOnLib_Directory
  {
  public:
    /*!
     * @brief Checks whether a directory can be opened.
     * @param strUrl The URL of the directory to check.
     * @return True when it can be opened, false otherwise.
     */
    static bool CanOpenDirectory(const char* strUrl);

    /*!
     * @brief Creates a directory.
     * @param strPath Path to the directory.
     * @return True when it was created, false otherwise.
     */
    static bool CreateDirectory(const char *strPath);

    /*!
     * @brief Checks if a directory exists.
     * @param strPath Path to the directory.
     * @return True when it exists, false otherwise.
     */
    static bool DirectoryExists(const char *strPath);

    /*!
     * @brief Removes a directory.
     * @param strPath Path to the directory.
     * @return True when it was removed, false otherwise.
     */
    static bool RemoveDirectory(const char *strPath);
  }; /* class CAddOnLib_Directory */
  /*\__________________________________________________________________________/
  \*/

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_DirectoryFunc.h"
