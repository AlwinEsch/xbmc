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
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AddonVersion.h"

#include <memory>

class TiXmlElement;

namespace ADDON_NEW
{

  const char* const ORIGIN_SYSTEM = "b6a50484-93a0-4afb-a01c-8d17e059feda";

  typedef enum
  {
    ADDON_TYPE_UNDEFINED,
    ADDON_TYPE_SERVICE,
    ADDON_TYPE_MAX
  } ADDON_TYPE;

  class CAddonInfo;
  typedef std::shared_ptr<CAddonInfo> AddonInfoPtr;

  class CAddonInfo
  {
  public:
    CAddonInfo();

    bool Load(const std::string& addonPath);

    const std::string& ID() const { return m_id; }
    const std::string& Path() const { return m_path; }
    const AddonVersion& Version() const { return m_version; }
    const AddonVersion& MinVersion() const { return m_minversion; }
    const bool SupportType(ADDON_TYPE type) const;

  private:
    bool LoadAddonXML(const TiXmlElement* baseElement, const std::string& addonPath);

    std::string m_id;
    std::string m_path;
    AddonVersion m_version{"0.0.0"};
    AddonVersion m_minversion{"0.0.0"};
  };

} /* namespace ADDONS_NEW */
