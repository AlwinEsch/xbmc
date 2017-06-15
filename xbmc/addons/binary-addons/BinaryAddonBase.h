#pragma once
/*
 *      Copyright (C) 2005-2017 Team Kodi
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
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AddonInstanceHandler.h"
#include "BinaryAddonType.h"

#include "addons/AddonInfo.h"
#include "threads/CriticalSection.h"
#include "utils/StringUtils.h"

#include <memory>
#include <string>
#include <unordered_set>

class TiXmlElement;

namespace ADDON
{

  class IAddonInstanceHandler;

  class CAddonDll;
  typedef std::shared_ptr<CAddonDll> AddonDllPtr;

  class CBinaryAddonBase;
  typedef std::shared_ptr<CBinaryAddonBase> BinaryAddonBasePtr;
  typedef std::vector<BinaryAddonBasePtr> BinaryAddonBaseList;

  class CBinaryAddonBase : public std::enable_shared_from_this<CBinaryAddonBase>
  {
  public:
    CBinaryAddonBase() : m_mainType(ADDON_UNKNOWN) { }

    bool Create(const std::string& addonPath);

    const std::string& ID() { return m_id; }
    const std::string& Path() { return m_path; }

    TYPE MainType() const { return m_mainType; }
    const std::string& MainLibName() const { return m_mainLibName; }
    bool IsType(TYPE type) const;

    const AddonVersion& Version() const { return m_version; }
    const AddonVersion& MinVersion() const { return m_minversion; }
    const std::string& Name() const { return m_name; }
    const std::string& Summary() const { return m_summary; }
    const std::string& Description() const { return m_description; }
    const std::string& Author() const { return m_author; }
    const std::string& Path() const { return m_path; }
    const std::string& ChangeLog() const { return m_changelog; }
    const std::string& Icon() const { return m_icon; }
    const ArtMap& Art() const { return m_art; }
    const std::string& Disclaimer() const { return m_disclaimer; }

    bool ProvidesSubContent(const TYPE& content, const TYPE& mainType = ADDON_UNKNOWN) const;
    bool ProvidesSeveralSubContents() const;

    bool MeetsVersion(const AddonVersion &version) const;

    AddonDllPtr GetAddon(const IAddonInstanceHandler* handler);
    void ReleaseAddon(const IAddonInstanceHandler* handler);

    AddonDllPtr GetActiveAddon();

  private:
    bool LoadAddonXML(const TiXmlElement* element, const std::string& addonPath);

    TYPE m_mainType;
    std::string m_mainLibName;
    std::string m_id;
    std::string m_path;
    std::vector<CBinaryAddonType> m_types;

    AddonVersion m_version{"0.0.0"};
    AddonVersion m_minversion{"0.0.0"};
    std::string m_author;
    std::string m_changelog;
    std::string m_description;
    std::string m_disclaimer;
    std::string m_icon;
    std::string m_name;
    std::string m_summary;
    ArtMap m_art;

    CCriticalSection m_critSection;
    AddonDllPtr m_activeAddon;
    std::unordered_set<const IAddonInstanceHandler*> m_activeAddonHandlers;
  };

} /* namespace ADDON */
