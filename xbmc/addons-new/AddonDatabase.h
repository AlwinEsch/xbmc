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

#include "dbwrappers/Database.h"

#include <set>

namespace ADDON_NEW
{

  class CAddonDatabase : public CDatabase
  {
  public:
    CAddonDatabase() = default;

    bool Open() override;

    void SyncInstalled(const std::set<std::string>& ids,
                       const std::set<std::string>& system,
                       const std::set<std::string>& optional);
    bool GetEnabled(std::set<std::string>& addons);

  protected:
    void CreateTables() override;
    void CreateAnalytics() override;
    void UpdateTables(int version) override;
    int GetSchemaVersion() const override { return 0; }
    const char *GetBaseDBName() const override { return "addons-new"; }
  };

} /* namespace ADDONS_NEW */
