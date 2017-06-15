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

#include "BinaryAddonBase.h"
#include "AddonDll.h"

#include "filesystem/SpecialProtocol.h"
#include "threads/SingleLock.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "utils/XMLUtils.h"

using namespace ADDON;

bool CBinaryAddonBase::Create(const std::string& addonPath)
{
  m_path = CSpecialProtocol::TranslatePath(addonPath);

  StringUtils::TrimRight(m_path, "/\\");

  auto addonXmlPath = URIUtils::AddFileToFolder(m_path, "addon.xml");

  CXBMCTinyXML xmlDoc;
  if (!xmlDoc.LoadFile(addonXmlPath))
  {
    CLog::Log(LOGERROR, "CBinaryAddonBase: Unable to load '%s', Line %d\n%s",
                                               m_path.c_str(),
                                               xmlDoc.ErrorRow(),
                                               xmlDoc.ErrorDesc());
    return false;
  }

  return LoadAddonXML(xmlDoc.RootElement(), m_path);
}

bool CBinaryAddonBase::IsType(TYPE type) const
{
  return (m_mainType == type || ProvidesSubContent(type));
}


bool CBinaryAddonBase::ProvidesSubContent(const TYPE& content, const TYPE& mainType/* = ADDON_UNKNOWN*/) const
{
  if (content == ADDON_UNKNOWN)
    return false;

  for (auto addonType : m_types)
  {
    if ((mainType == ADDON_UNKNOWN || addonType.Type() == mainType) && addonType.ProvidesSubContent(content))
      return true;
  }

  return false;
}

bool CBinaryAddonBase::ProvidesSeveralSubContents() const
{
  int contents = 0;
  for (auto addonType : m_types)
    contents += addonType.ProvidedSubContents();
  return contents > 0 ? true : false;
}

bool CBinaryAddonBase::MeetsVersion(const AddonVersion &version) const
{
  return m_minversion <= version && version <= m_version;
}

AddonDllPtr CBinaryAddonBase::GetAddon(const IAddonInstanceHandler* handler)
{
  if (handler == nullptr)
  {
    CLog::Log(LOGERROR, "ADDONS: GetAddon for Id '%s' called with empty instance handler", ID().c_str());
    return nullptr;
  }

  CSingleLock lock(m_critSection);

  // If no 'm_activeAddon' is defined create it new.
  if (m_activeAddon == nullptr)
  {
    CAddonInfo addonInfo;
    addonInfo.id = m_id;
    addonInfo.name = m_name;
    addonInfo.summary = m_summary;
    addonInfo.description = m_description;
    addonInfo.disclaimer = m_disclaimer;
    addonInfo.author = m_author;
    addonInfo.icon = m_icon;
    addonInfo.art = m_art;
    addonInfo.changelog = m_changelog;
    addonInfo.path = m_path;
    addonInfo.libname = m_mainLibName;
    addonInfo.version = m_version;
    addonInfo.minversion = m_minversion;
    addonInfo.type = m_mainType;
    m_activeAddon = std::make_shared<CAddonDll>(std::move(addonInfo), shared_from_this());
 }

  // add the instance handler to the info to know used amount on addon
  m_activeAddonHandlers.insert(handler);

  return m_activeAddon;
}

void CBinaryAddonBase::ReleaseAddon(const IAddonInstanceHandler* handler)
{
  if (handler == nullptr)
  {
    CLog::Log(LOGERROR, "ADDONS: ReleaseAddon for Id '%s' called with empty instance handler", ID().c_str());
    return;
  }

  CSingleLock lock(m_critSection);

  const auto& presentHandler = m_activeAddonHandlers.find(handler);
  if (presentHandler == m_activeAddonHandlers.end())
    return;

  m_activeAddonHandlers.erase(presentHandler);

  // if no handler is present anymore reset and delete the add-on class on informations
  if (m_activeAddonHandlers.empty())
  {
    m_activeAddon.reset();
  }

}

AddonDllPtr CBinaryAddonBase::GetActiveAddon()
{
  CSingleLock lock(m_critSection);
  return m_activeAddon;
}

bool CBinaryAddonBase::LoadAddonXML(const TiXmlElement* baseElement, const std::string& addonPath)
{
  const char* cstring; /* "C" string point where parts from TinyXML becomes
                          stored, is used as this to prevent double use of
                          calls and to prevent not wanted "C++" throws if
                          std::string want to become set with nullptr! */

  if (!StringUtils::EqualsNoCase(baseElement->Value(), "addon"))
  {
    CLog::Log(LOGERROR, "CBinaryAddonBase: file from '%s' doesnt contain <addon>", addonPath.c_str());
    return false;
  }

  /*
   * Parse addon.xml:
   * <addon id="???"
   *        name="???"
   *        version="???"
   *        provider-name="???">
   */
  cstring = baseElement->Attribute("id");
  m_id = cstring ? cstring : "";
  cstring = baseElement->Attribute("name");
  m_name = cstring ? cstring : "";
  cstring = baseElement->Attribute("version");
  m_version = AddonVersion(cstring ? cstring : "");
  cstring = baseElement->Attribute("provider-name");
  m_author = cstring ? cstring : "";
  if (m_id.empty() || m_version.empty())
  {
    CLog::Log(LOGERROR, "CBinaryAddonBase: file '%s' doesnt contain required values on <addon ... > id='%s', version='%s'",
              addonPath.c_str(),
              m_id.empty() ? "missing" : m_id.c_str(),
              m_version.empty() ? "missing" : m_version.asString().c_str());
    return false;
  }

  /*
   * Parse addon.xml:
   * <backwards-compatibility abi="???"/>
   */
  const TiXmlElement* backwards = baseElement->FirstChildElement("backwards-compatibility");
  if (backwards)
  {
    cstring = backwards->Attribute("abi");
    m_minversion = AddonVersion(cstring ? cstring : "");
  }

  /*
   * Parse addon.xml:
   * <extension>
   *   ...
   * </extension>
   */
  for (const TiXmlElement* child = baseElement->FirstChildElement("extension"); child != nullptr; child = child->NextSiblingElement("extension"))
  {
    cstring = child->Attribute("point");
    std::string point = cstring ? cstring : "";

    if (point == "kodi.addon.metadata" || point == "xbmc.addon.metadata")
    {
      /*
       * Parse addon.xml "<summary lang="..">...</summary>"
       */
      const char* strSummary = nullptr;
      for (const TiXmlElement* element = child->FirstChildElement("summary"); element != nullptr; element = element->NextSiblingElement("summary"))
      {
        cstring = element->Attribute("lang");
        if (cstring != nullptr)
        {
          std::string lang = cstring;
          if (g_langInfo.GetLocale().Matches(lang))
          {
            strSummary = element->GetText();
            break;
          }
          else if (lang == "en" || lang == "en_GB" || strSummary == nullptr)
          {
            strSummary = element->GetText();
          }
        }
        else
          strSummary = element->GetText();
      }
      m_summary = strSummary ? strSummary : "";

      /*
       * Parse addon.xml "<description lang="..">...</description>"
       */
      const char* strDescription = nullptr;
      for (const TiXmlElement* element = child->FirstChildElement("description"); element != nullptr; element = element->NextSiblingElement("description"))
      {
        cstring = element->Attribute("lang");
        if (cstring != nullptr)
        {
          std::string lang = cstring;
          if (g_langInfo.GetLocale().Matches(lang))
          {
            strDescription = element->GetText();
            break;
          }
          else if (lang == "en" || lang == "en_GB" || strDescription == nullptr)
          {
            strDescription = element->GetText();
          }
        }
        else
          strDescription = element->GetText();
      }
      m_description = strDescription ? strDescription : "";

      /*
       * Parse addon.xml "<disclaimer lang="..">...</disclaimer>"
       */
      const char* strDisclaimer = nullptr;
      for (const TiXmlElement* element = child->FirstChildElement("disclaimer"); element != nullptr; element = element->NextSiblingElement("disclaimer"))
      {
        cstring = element->Attribute("lang");
        if (cstring != nullptr)
        {
          std::string lang = cstring;
          if (g_langInfo.GetLocale().Matches(lang))
          {
            strDisclaimer = element->GetText();
            break;
          }
          else if (lang == "en" || lang == "en_GB" || strDisclaimer == nullptr)
          {
            strDisclaimer = element->GetText();
          }
        }
        else
          strDisclaimer = element->GetText();
      }
      m_disclaimer = strDisclaimer ? strDisclaimer : "";

      /*
       * Parse addon.xml "<assets>...</assets>"
       */
      const TiXmlElement* element = child->FirstChildElement("assets");
      if (element)
      {
        for (const TiXmlElement* elementsAssets = element->FirstChildElement(); elementsAssets != nullptr; elementsAssets = elementsAssets->NextSiblingElement())
        {
          std::string value = elementsAssets->Value();
          if (value == "icon")
          {
            if (elementsAssets->GetText() != nullptr)
              m_icon = elementsAssets->GetText();
          }
          else if (value == "fanart")
          {
            if (elementsAssets->GetText() != nullptr)
              m_art[value] = elementsAssets->GetText();
          }
          else if (value == "banner")
          {
            if (elementsAssets->GetText() != nullptr)
              m_art[value] = elementsAssets->GetText();
          }
          else if (value == "clearlogo")
          {
            if (elementsAssets->GetText() != nullptr)
              m_art[value] = elementsAssets->GetText();
          }
        }
      }

      /* Parse addon.xml "<noicon">...</noicon>" */
      if (m_icon.empty())
      {
        element = child->FirstChildElement("noicon");
        m_icon = (element && strcmp(element->GetText() , "true") == 0) ? "" : "icon.png";
      }

      /* Parse addon.xml "<nofanart">...</nofanart>" */
      if (m_art.empty())
      {
        element = child->FirstChildElement("nofanart");
        if (!element || strcmp(element->GetText(), "true") != 0)
          m_art["fanart"] = URIUtils::AddFileToFolder(addonPath, "fanart.jpg");
      }

      /* Parse addon.xml "<news lang="..">...</news>" */
      const char* strChangelog = nullptr;
      element = child->FirstChildElement("news");
      while (element)
      {
        const char *lang = element->Attribute("lang");
        if (lang != nullptr && g_langInfo.GetLocale().Matches(lang))
        {
          strChangelog = element->GetText();
          break;
        }
        else if (lang == nullptr || strcmp(lang, "en") == 0 || strcmp(lang, "en_GB") == 0)
        {
          strChangelog = element->GetText();
        }

        element = element->NextSiblingElement("news");
      }
      m_changelog = strChangelog ? strChangelog : "";
    }
    else
    {
      TYPE type = CAddonInfo::TranslateType(point);
      if (type == ADDON_UNKNOWN || type >= ADDON_MAX)
      {
        CLog::Log(LOGERROR, "CBinaryAddonBase: file '%s' doesn't contain a valid add-on type name (%s)", addonPath.c_str(), point.c_str());
        return false;
      }

      m_types.push_back(CBinaryAddonType(type, this, child));
    }
  }

  /*
   * If nothing is defined in addon.xml set this as unknown to have minimum one
   * instance type present.
   */
  if (m_types.empty())
  {
    CBinaryAddonType addonType(ADDON_UNKNOWN, this, nullptr);
    m_types.push_back(addonType);
  }

  m_mainType = m_types[0].Type();
  m_mainLibName = m_types[0].LibName();

  return true;
}
