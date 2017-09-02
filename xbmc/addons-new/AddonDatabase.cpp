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

#include "XBDateTime.h"
#include "dbwrappers/dataset.h"
#include "utils/log.h"

#include <algorithm>

using namespace ADDON_NEW;

bool CAddonDatabase::Open()
{
  return CDatabase::Open();
}

void CAddonDatabase::CreateTables()
{
  CLog::Log(LOGINFO, "CAddonDatabase::%s: create table", __FUNCTION__);

  m_pDS->exec("CREATE TABLE installed ("
      "id INTEGER PRIMARY KEY,"
      "addonID TEXT UNIQUE,"
      "enabled BOOLEAN,"
      "installDate TEXT,"
      "lastUpdated TEXT,"
      "lastUsed TEXT, "
      "origin TEXT NOT NULL DEFAULT '')");
}

void CAddonDatabase::CreateAnalytics()
{
  CLog::Log(LOGINFO, "%s - creating indices", __FUNCTION__);

}

void CAddonDatabase::UpdateTables(int version)
{

}

void CAddonDatabase::SyncInstalled(const std::set<std::string>& ids,
                                   const std::set<std::string>& system,
                                   const std::set<std::string>& optional)
{
  try
  {
    if (nullptr == m_pDB.get())
      return;
    if (nullptr == m_pDS.get())
      return;

    std::set<std::string> db;
    m_pDS->query(PrepareSQL("SELECT addonID FROM installed"));
    while (!m_pDS->eof())
    {
      db.insert(m_pDS->fv(0).get_asString());
      m_pDS->next();
    }
    m_pDS->close();

    std::set<std::string> added;
    std::set<std::string> removed;
    std::set_difference(ids.begin(), ids.end(), db.begin(), db.end(), std::inserter(added, added.end()));
    std::set_difference(db.begin(), db.end(), ids.begin(), ids.end(), std::inserter(removed, removed.end()));

    for (const auto& id : added)
      CLog::Log(LOGDEBUG, "CAddonDatabase::%s: %s has been installed.", __FUNCTION__, id.c_str());

    for (const auto& id : removed)
      CLog::Log(LOGDEBUG, "CAddonDatabase::%s: %s has been uninstalled.", __FUNCTION__, id.c_str());

    std::string now = CDateTime::GetCurrentDateTime().GetAsDBDateTime();
    BeginTransaction();
    for (const auto& id : added)
    {
      int enable = 0;

      if (system.find(id) != system.end() || optional.find(id) != optional.end())
        enable = 1;

      m_pDS->exec(PrepareSQL("INSERT INTO installed(addonID, enabled, installDate) "
        "VALUES('%s', %d, '%s')", id.c_str(), enable, now.c_str()));
    }

    for (const auto& id : removed)
    {
      m_pDS->exec(PrepareSQL("DELETE FROM installed WHERE addonID='%s'", id.c_str()));
    }

    for (const auto& id : system)
    {
      m_pDS->exec(PrepareSQL("UPDATE installed SET enabled=1 WHERE addonID='%s'", id.c_str()));
      // Set origin *only* for addons that do not have one yet as it may have been changed by an update.
      m_pDS->exec(PrepareSQL("UPDATE installed SET origin='%s' WHERE addonID='%s' AND origin=''", ORIGIN_SYSTEM, id.c_str()));
    }

    CommitTransaction();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "CAddonDatabase::%s: failed", __FUNCTION__);
    RollbackTransaction();
  }
}

bool CAddonDatabase::GetEnabled(std::set<std::string>& addons)
{
  try
  {
    if (nullptr == m_pDB.get())
      return false;
    if (nullptr == m_pDS.get())
      return false;

    std::string sql = PrepareSQL("SELECT addonID FROM installed WHERE enabled=1");
    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      addons.insert(m_pDS->fv(0).get_asString());
      m_pDS->next();
    }
    m_pDS->close();
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "CAddonDatabase::%s: failed", __FUNCTION__);
  }
  return false;
}
