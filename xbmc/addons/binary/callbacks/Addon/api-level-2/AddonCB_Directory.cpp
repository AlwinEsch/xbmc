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

void CAddonCB_Directory::Init(CB_AddOnLib *callbacks)
{
  callbacks->Directory.can_open_directory    = CAddonCB_Directory::can_open_directory;
  callbacks->Directory.create_directory      = CAddonCB_Directory::create_directory;
  callbacks->Directory.directory_exists      = CAddonCB_Directory::directory_exists;
  callbacks->Directory.remove_directory      = CAddonCB_Directory::remove_directory;
  callbacks->DirectoryVFS.get_vfs_directory  = CAddonCB_Directory::get_vfs_directory;
  callbacks->DirectoryVFS.free_vfs_directory = CAddonCB_Directory::free_vfs_directory;
}

/*\_____________________________________________________________________________
| |
| |
| |_____________________________________________________________________________
\*/
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
/*\____________________________________________________________________________/
\*/

/*\_____________________________________________________________________________
| |
| | C++ wrappers for Kodi's VFS operations
| |_____________________________________________________________________________
\*/
bool CAddonCB_Directory::get_vfs_directory(
        void*                     hdl,
        const char*               strPath,
        const char*               mask,
        VFSDirEntry**             items,
        unsigned int*             num_items)
{
  CFileItemList fileItems;
  if (!CDirectory::GetDirectory(strPath, fileItems, mask, DIR_FLAG_NO_FILE_DIRS))
    return false;

  if (fileItems.Size() > 0)
  {
    *num_items = static_cast<unsigned int>(fileItems.Size());
    *items = new VFSDirEntry[fileItems.Size()];
  }
  else
  {
    *num_items = 0;
    *items = nullptr;
  }

  CFileItemListToVFSDirEntries(*items, fileItems);
  return true;
}

void CAddonCB_Directory::free_vfs_directory(
        void*                     hdl,
        VFSDirEntry*              items,
        unsigned int              num_items)
{
  for (unsigned int i = 0; i < num_items; ++i)
  {
    free(items[i].label);
    free(items[i].path);
  }
  delete[] items;
}

void CAddonCB_Directory::CFileItemListToVFSDirEntries(
        VFSDirEntry*              entries,
        const CFileItemList&      items)
{
  for (int i = 0; i < items.Size(); ++i)
  {
    entries[i].label  = strdup(items[i]->GetLabel().c_str());
    entries[i].path   = strdup(items[i]->GetPath().c_str());
    entries[i].size   = items[i]->m_dwSize;
    entries[i].folder = items[i]->m_bIsFolder;
  }
}

/*\____________________________________________________________________________/
\*/

}; /* namespace V2 */
}; /* namespace AddOnLIB */
