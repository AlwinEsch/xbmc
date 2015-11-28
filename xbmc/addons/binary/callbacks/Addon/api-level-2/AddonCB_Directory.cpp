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

#include "AddonCB_Directory.h"
#include "AddonCallbacksAddon.h"

#include "FileItem.h"
#include "filesystem/File.h"
#include "filesystem/Directory.h"

using namespace XFILE;

namespace AddOnLIB
{
namespace V2
{

CAddonCB_Directory::CAddonCB_Directory()
{

}

void CAddonCB_Directory::Init(CB_AddOn_Directory *callbacks)
{
  callbacks->can_open_directory  = CAddonCB_Directory::can_open_directory;
  callbacks->create_directory    = CAddonCB_Directory::create_directory;
  callbacks->directory_exists    = CAddonCB_Directory::directory_exists;
  callbacks->remove_directory    = CAddonCB_Directory::remove_directory;
}

bool CAddonCB_Directory::can_open_directory(
        void*                     hdl,
        const char*               strURL)
{
  CFileItemList items;
  return CDirectory::GetDirectory(strURL, items);
}

bool CAddonCB_Directory::create_directory(
        void*                     hdl,
        const char*               strPath)
{
  return CDirectory::Create(strPath);
}

bool CAddonCB_Directory::directory_exists(
        void*                     hdl,
        const char*               strPath)
{
  return CDirectory::Exists(strPath);
}

bool CAddonCB_Directory::remove_directory(
        void*                     hdl,
        const char*               strPath)
{
  // Empty directory
  CFileItemList fileItems;
  CDirectory::GetDirectory(strPath, fileItems);
  for (int i = 0; i < fileItems.Size(); ++i)
    CFile::Delete(fileItems.Get(i)->GetPath());

  return CDirectory::Remove(strPath);
}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
