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

#include "AddonDatabase.h"
#include "AddonInfo.h"

#include "threads/Thread.h"
#include "threads/platform/CriticalSection.h"

#include <unordered_map>
#include <set>
#include <string>

namespace ADDON_NEW
{

  class CAddonChangeObserver;
  class CAddonChangeProcessor;

  class CAddonManager : public CThread
  {
  public:
    CAddonManager();

    bool Init();
    void Deinit();

    bool EnableAddon(const std::string& addonId, bool waitToSet);
    bool DisableAddon(const std::string& addonId, bool waitToSet);

    bool IsAddonInstalled(const std::string& addonId) const;
    bool IsAddonEnabled(const std::string& addonId) const;
    AddonInfoPtr GetInstalledAddonInfo(const std::string& addonId) const;

    void RegisterAddonChangeObserver(CAddonChangeObserver* observer);
    void UnregisterAddonChangeObserver(CAddonChangeObserver* observer);

  protected:
    void Process(void) override;

  private:
    typedef std::unordered_map<std::string, AddonInfoPtr> AddonInfoList;

    void FindAddons(AddonInfoList& addonmap, const std::string& path);
    bool LoadManifest(std::set<std::string>& system, std::set<std::string>& optional);

    CCriticalSection m_critSection;
    CAddonDatabase m_database;
    AddonInfoList m_installedAddons;
    AddonInfoList m_enabledAddons;
    std::set<std::string> m_systemAddons;
    std::set<std::string> m_optionalAddons;
    std::set<CAddonChangeObserver*> m_addonChangeObserver;
    std::vector<CAddonChangeProcessor*> m_activeAddonChangeProcessors;

  private:
    friend class CAddonChangeProcessor;

    bool PerformDisableJob(const AddonInfoPtr& addonInfo);
    bool PerformUninstallJob(const AddonInfoPtr& addonInfo);
    bool PerformUpdateJob(const AddonInfoPtr& addonInfo);
    bool PerformInstallJob(const AddonInfoPtr& addonInfo);
    bool PerformEnableJob(const AddonInfoPtr& addonInfo);
  };

} /* namespace ADDONS_NEW */
