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
#include "internal/libKODI_addon_VFSUtilsHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{
  /*\___________________________________________________________________________
  | |
  | | C++ wrappers for Kodi's VFS operations
  | |___________________________________________________________________________
  \*/
  class CVFSProperty
  {
  public:
    CVFSProperty(const std::string& name, const std::string& value);

    const std::string& Name(void) const;
    const std::string& Value(void) const;

    void SetName(const std::string& name);
    void SetValue(const std::string& value);

    IMPL_VFS_PROPERTY;
  };

  class CVFSDirEntry
  {
  public:
    CVFSDirEntry(
        const std::string&  label   = "",
        const std::string&  path    = "",
        bool                bFolder = false,
        int64_t             size    = -1);

    CVFSDirEntry(const VFSDirEntry&  dirEntry);

    const std::string& Label(void) const;
    const std::string& Path(void) const;
    bool IsFolder(void) const;
    int64_t Size(void) const;
    const std::vector<CVFSProperty>& Properties(void);

    void SetLabel(const std::string& label);
    void SetPath(const std::string& path);
    void SetFolder(bool bFolder);
    void SetSize(int64_t size);
    std::vector<CVFSProperty>& Properties(void);

    IMPL_VFS_DIR_ENTRY;
  };

  class CAddOnLib_VFSUtils
  {
  public:
    /*!
     * @brief Lists a directory.
     * @param path Path to the directory.
     * @param mask File mask
     * @param items The directory entries
     * @return True if listing was successful, false otherwise.
     */
    static bool GetDirectory(
               const std::string&          path,
               const std::string&          mask,
               std::vector<CVFSDirEntry>&  items);
  };
  /*\__________________________________________________________________________/
  \*/

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_VFSUtilsFunc.h"
