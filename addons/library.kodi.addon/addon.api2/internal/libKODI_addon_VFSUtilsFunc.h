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

namespace AddOnLIB
{
namespace V2
{

  inline CVFSProperty::CVFSProperty(
    const std::string& name,
    const std::string& value)
    : m_name(name),
      m_value(value)
  {
  }

  inline CVFSProperty::~CVFSProperty()
  {

  }

  inline const std::string& CVFSProperty::Name(void) const
  {
    return m_name;
  }

  inline const std::string& CVFSProperty::Value(void) const
  {
    return m_value;
  }

  inline void CVFSProperty::SetName(const std::string& name)
  {
    m_name = name;
  }

  inline void CVFSProperty::SetValue(const std::string& value)
  {
    m_value = value;
  }

  /*\___________________________________________________________________________
  \*/

  inline CVFSDirEntry::CVFSDirEntry(
    const std::string& label,
    const std::string& path,
    bool               bFolder,
    int64_t            size)
    : m_label(label),
      m_path(path),
      m_bFolder(bFolder),
      m_size(size)
  {
  }

  inline CVFSDirEntry::CVFSDirEntry(const VFSDirEntry& dirEntry)
    : m_label(dirEntry.label ? dirEntry.label : ""),
      m_path(dirEntry.path   ? dirEntry.path  : ""),
      m_bFolder(dirEntry.folder),
      m_size(dirEntry.size)
  {
    for (unsigned int i = 0; i < dirEntry.num_props; ++i)
      m_properties.push_back(CVFSDirEntry(dirEntry.properties[i].name, dirEntry.properties[i].val));
  }

  inline const std::string& CVFSDirEntry::Label(void) const
  {
    return m_label;
  }

  inline const std::string& CVFSDirEntry::Path(void) const
  {
    return m_path;
  }

  inline bool CVFSDirEntry::IsFolder(void) const
  {
    return m_bFolder;
  }

  inline int64_t CVFSDirEntry::Size(void) const
  {
    return m_size;
  }

  inline const std::vector<CVFSDirEntry>& CVFSDirEntry::Properties(void) const
  {
    return m_properties;
  }

  inline void CVFSDirEntry::SetLabel(const std::string& label)
  {
    m_label = label;
  }

  inline void CVFSDirEntry::SetPath(const std::string& path)
  {
    m_path = path;
  }

  inline void CVFSDirEntry::SetFolder(bool bFolder)
  {
    m_bFolder = bFolder;
  }

  inline void CVFSDirEntry::SetSize(int64_t size)
  {
    m_size = size;
  }

  inline std::vector<CVFSDirEntry>& CVFSDirEntry::Properties(void)
  {
    return m_properties;
  }

  /*\___________________________________________________________________________
  \*/

  inline bool VFSUtils::GetDirectory(
    const std::string&          path,
    const std::string&          mask,
    std::vector<CVFSDirEntry>&  items)
  {
    VFSDirEntry* dir_list  = nullptr;
    unsigned int num_items = 0;
    if (CAddonLib::g_libKODI_Internal->GetVFSDirectory(path.c_str(), mask.c_str(), &dir_list, &num_items))
    {
      for (unsigned int i = 0; i < num_items; ++i)
        items.push_back(CVFSDirEntry(dir_list[i]));

      CAddonLib::g_libKODI_Internal->FreeVFSDirectory(dir_list, num_items);

      return true;
    }
    return false;
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
