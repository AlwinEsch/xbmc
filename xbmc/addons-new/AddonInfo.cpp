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

#include "AddonInfo.h"

#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "utils/XBMCTinyXML.h"

using namespace ADDON_NEW;

CAddonInfo::CAddonInfo()
{

}

bool CAddonInfo::Load(const std::string& addonPath)
{
  m_path = CSpecialProtocol::TranslatePath(addonPath);
  StringUtils::TrimRight(m_path, "/\\");

  auto addonXmlPath = URIUtils::AddFileToFolder(m_path, "addon.xml");

  CXBMCTinyXML xmlDoc;
  if (!xmlDoc.LoadFile(addonXmlPath))
  {
    CLog::Log(LOGERROR, "CAddonInfo::%s: Unable to load '%s', Line %d\n%s",
                __FUNCTION__,
                m_path.c_str(),
                xmlDoc.ErrorRow(),
                xmlDoc.ErrorDesc());
    return false;
  }

  return LoadAddonXML(xmlDoc.RootElement(), addonXmlPath);
}

const bool CAddonInfo::SupportType(ADDON_TYPE type) const
{

  return false;
}

bool CAddonInfo::LoadAddonXML(const TiXmlElement* baseElement, const std::string& addonPath)
{
  const char* cstring; /* "C" string point where parts from TinyXML becomes
                          stored, is used as this to prevent double use of
                          calls and to prevent not wanted "C++" throws if
                          std::string want to become set with nullptr! */

  if (!StringUtils::EqualsNoCase(baseElement->Value(), "addon"))
  {
    CLog::Log(LOGERROR, "CAddonInfo::%s: file '%s' doesnt contain <addon>", __FUNCTION__, addonPath.c_str());
    return false;
  }

  cstring = baseElement->Attribute("id");
  m_id = cstring ? cstring : "";
  cstring = baseElement->Attribute("version");
  m_version = AddonVersion(cstring ? cstring : "");
  if (m_id.empty() || m_version.empty())
  {
    CLog::Log(LOGERROR, "CAddonInfo::%s: file '%s' doesnt contain required values on <addon ... > id='%s', version='%s'",
                __FUNCTION__,
                addonPath.c_str(),
                m_id.empty() ? "missing" : m_id.c_str(),
                m_version.empty() ? "missing" : m_version.asString().c_str());
    return false;
  }

  return true;
}

