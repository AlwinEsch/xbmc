/*
 *      Copyright (C) 2012-2014 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "URL.h"
#include "dbwrappers/dataset.h"
#include "settings/AdvancedSettings.h"
#include "settings/MediaSettings.h"
#include "settings/MediaSourceSettings.h"
#include "settings/Settings.h"
#include "video/VideoInfoTag.h"
#include "utils/log.h"
#include "utils/StringUtils.h"

#include "ActiveAEDSP.h"
#include "ActiveAEDSPMode.h"
#include "ActiveAEDSPAddon.h"
#include "ActiveAEDSPDatabase.h"
#include "ActiveAEDSPProcess.h"

using namespace std;
using namespace dbiplus;
using namespace ActiveAE;
using namespace ADDON;

#define ADSPDB_DEBUGGING 0

bool CActiveAEDSPDatabase::Open()
{
  return CDatabase::Open(g_advancedSettings.m_databaseADSP);
}

void CActiveAEDSPDatabase::CreateTables()
{
  BeginTransaction();
  CLog::Log(LOGINFO, "Audio DSP - %s - creating tables", __FUNCTION__);

  CLog::Log(LOGDEBUG, "Audio DSP - %s - creating table 'addons'", __FUNCTION__);
  m_pDS->exec(
      "CREATE TABLE addons ("
        "idAddon  integer primary key, "
        "sName    varchar(64), "
        "sUid     varchar(32)"
      ")"
  );

  CLog::Log(LOGDEBUG, "Audio DSP - %s - creating table 'modes'", __FUNCTION__);
  m_pDS->exec(
      "CREATE TABLE modes ("
        "idMode               integer primary key, "
        "iType                integer, "
        "iPosition            integer, "
        "iStreamTypeFlags     integer, "
        "iBaseType            integer, "
        "bIsHidden            bool, "
        "sOwnIconPath         varchar(255), "
        "sOverrideIconPath    varchar(255), "
        "iModeName            integer, "
        "iModeSetupName       integer, "
        "iModeHelp            integer, "
        "iModeDescription     integer, "
        "sAddonModeName       varchar(64), "
        "iAddonId             integer, "
        "iAddonModeNumber     integer, "
        "bHasSettings         bool"
      ")"
  );

  CLog::Log(LOGDEBUG, "Audio DSP - %s - create settings table", __FUNCTION__);
  m_pDS->exec(
      "CREATE TABLE settings ("
        "id                   integer primary key, "
        "strPath              varchar(255), "
        "strFileName          varchar(255), "
        "MasterStreamTypeSel  integer, "
        "MasterStreamType     integer, "
        "MasterBaseType       integer, "
        "MasterModeId         integer, "
        "InputResample        integer, "
        "OutputResample       integer"
      ")"
  );

  // disable all Audio DSP add-on when started the first time
  ADDON::VECADDONS addons;
  if (CAddonMgr::Get().GetAddons(ADDON_ADSPDLL, addons, true))
    CLog::Log(LOGERROR, "Audio DSP - %s - failed to get add-ons from the add-on manager", __FUNCTION__);
  else
  {
    for (IVECADDONS it = addons.begin(); it != addons.end(); it++)
      CAddonMgr::Get().DisableAddon(it->get()->ID());
  }
}

void CActiveAEDSPDatabase::CreateAnalytics()
{
  CLog::Log(LOGINFO, "Audio DSP - %s - creating indices", __FUNCTION__);
  m_pDS->exec("CREATE UNIQUE INDEX idx_mode_iAddonId_iAddonModeNumber on modes(iAddonId, iAddonModeNumber);");
  m_pDS->exec("CREATE UNIQUE INDEX ix_settings ON settings ( id )\n");
}

void CActiveAEDSPDatabase::UpdateTables(int iVersion)
{
  if (iVersion < 0)
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - updating from table versions < 0 not supported. please delete '%s'", __FUNCTION__, GetBaseDBName());
  }
}

/********** Mode methods **********/

bool CActiveAEDSPDatabase::DeleteModes(void)
{
  CLog::Log(LOGDEBUG, "Audio DSP - %s - deleting all modes from the database", __FUNCTION__);
  return DeleteValues("modes");
}

bool CActiveAEDSPDatabase::DeleteModes(int modeType)
{
  /* invalid addon Id */
  if (modeType <= 0)
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - invalid mode type id: %i", __FUNCTION__, modeType);
    return false;
  }

  CLog::Log(LOGDEBUG, "Audio DSP - %s - deleting all modes from type '%i' from the database", __FUNCTION__, modeType);

  Filter filter;
  filter.AppendWhere(PrepareSQL("iType = %u", modeType));

  return DeleteValues("modes", filter);
}

bool CActiveAEDSPDatabase::DeleteModes(const CActiveAEDSPAddon &addon)
{
  /* invalid addon Id */
  if (addon.GetID() <= 0)
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - invalid add-on id: %i", __FUNCTION__, addon.GetID());
    return false;
  }

  CLog::Log(LOGDEBUG, "Audio DSP - %s - deleting all modes from add-on '%i' from the database", __FUNCTION__, addon.GetID());

  Filter filter;
  filter.AppendWhere(PrepareSQL("iAddonId = %u", addon.GetID()));

  return DeleteValues("modes", filter);
}

bool CActiveAEDSPDatabase::DeleteMode(const CActiveAEDSPMode &mode)
{
  /* invalid mode */
  if (mode.ModeID() <= 0)
    return false;

  CLog::Log(LOGDEBUG, "Audio DSP - %s - deleting mode '%s' from the database", __FUNCTION__, mode.AddonModeName().c_str());

  Filter filter;
  filter.AppendWhere(PrepareSQL("idMode = %u", mode.ModeID()));

  return DeleteValues("modes", filter);
}

bool CActiveAEDSPDatabase::PersistModes(vector<CActiveAEDSPModePtr> &modes, int modeType)
{
  bool bReturn(true);

  for (unsigned int iModePtr = 0; iModePtr < modes.size(); iModePtr++)
  {
    CActiveAEDSPModePtr member = modes.at(iModePtr);
    if (member->IsChanged() || member->IsNew())
    {
      bReturn &= AddUpdateMode(*member);
    }
  }

  bReturn &= CommitInsertQueries();

  return bReturn;
}

bool CActiveAEDSPDatabase::UpdateMode(int modeType, bool active, int addonId, int addonModeNumber, int listNumber)
{
  bool bReturn(true);

  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    CStdString strSQL = PrepareSQL("update modes set iPosition=%i,bIsHidden='%i' WHERE modes.iAddonId='%i' AND modes.iAddonModeNumber='%i' AND modes.iType='%i'", listNumber, (active ? 0 : 1), addonId, addonModeNumber, modeType);
    bReturn = m_pDS->exec(strSQL.c_str());
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - (Addon='%i', Mode='%i') failed", __FUNCTION__, addonId, addonModeNumber);
  }
  return bReturn;
}

bool CActiveAEDSPDatabase::AddUpdateMode(CActiveAEDSPMode &mode)
{
  bool bReturn(true);

  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;
    CStdString strSQL = PrepareSQL("SELECT * FROM modes WHERE modes.iAddonId='%i' AND modes.iAddonModeNumber='%i' AND modes.iType='%i'", mode.AddonID(), mode.AddonModeNumber(), mode.ModeType());

    m_pDS->query( strSQL.c_str() );
    if (m_pDS->num_rows() > 0)
    {
      /* get user selected settings */
      mode.m_iModeId        = m_pDS->fv("idMode").get_asInt();
      mode.m_iModePosition  = m_pDS->fv("iPosition").get_asInt();
      mode.m_iBaseType      = (AE_DSP_BASETYPE)m_pDS->fv("iBaseType").get_asInt();
      mode.m_bIsHidden      = m_pDS->fv("bIsHidden").get_asBool();
      m_pDS->close();

      /* update addon related settings */
      strSQL = PrepareSQL(
      "UPDATE modes set "
        "iStreamTypeFlags=%i, "
        "sOwnIconPath='%s', "
        "sOverrideIconPath='%s', "
        "iModeName=%i, "
        "iModeSetupName=%i, "
        "iModeHelp=%i, "
        "iModeDescription=%i, "
        "sAddonModeName='%s', "
        "bHasSettings=%i "
        "WHERE modes.iAddonId='%i' AND modes.iAddonModeNumber='%i' AND modes.iType='%i'",
        mode.StreamTypeFlags(),
        mode.IconOwnModePath().c_str(),
        mode.IconOverrideModePath().c_str(),
        mode.ModeName(),
        mode.ModeSetupName(),
        mode.ModeHelp(),
        mode.ModeDescription(),
        mode.AddonModeName().c_str(),
        (mode.HasSettingsDialog() ? 1 : 0),
        mode.AddonID(), mode.AddonModeNumber(), mode.ModeType());
    }
    else
    { // add the items
      m_pDS->close();
      strSQL = PrepareSQL(
      "INSERT INTO modes ("
        "iType, "
        "iPosition, "
        "iStreamTypeFlags, "
        "bIsHidden, "
        "sOwnIconPath, "
        "sOverrideIconPath, "
        "iModeName, "
        "iModeSetupName, "
        "iModeHelp, "
        "iModeDescription, "
        "sAddonModeName, "
        "iAddonId, "
        "iAddonModeNumber, "
        "bHasSettings) "
        "VALUES (%i, %i, %i, %i, '%s', '%s', %i,  %i, %i, %i, '%s', %i, %i, %i)",
        mode.ModeType(),
        mode.ModePosition(),
        mode.StreamTypeFlags(),
        (mode.IsHidden() ? 1 : 0),
        mode.IconOwnModePath().c_str(),
        mode.IconOverrideModePath().c_str(),
        mode.ModeName(),
        mode.ModeSetupName(),
        mode.ModeHelp(),
        mode.ModeDescription(),
        mode.AddonModeName().c_str(),
        mode.AddonID(),
        mode.AddonModeNumber(),
        (mode.HasSettingsDialog() ? 1 : 0));
      bReturn = m_pDS->exec(strSQL.c_str());
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - (Addon='%i', Mode='%i', Name: %s) failed", __FUNCTION__, mode.AddonID(), mode.AddonModeNumber(), mode.AddonModeName().c_str());
  }
  return bReturn;
}

int CActiveAEDSPDatabase::GetModeId(const CActiveAEDSPMode &mode)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;
    int idMode = -1;

    CStdString strSQL = PrepareSQL("SELECT * from modes WHERE modes.iAddonId='%i' and modes.iAddonModeNumber='%i' and modes.iType='%i'", mode.AddonID(), mode.AddonModeNumber(), mode.ModeType());

    m_pDS->query(strSQL.c_str());
    if (m_pDS->num_rows() > 0)
      idMode = m_pDS->fv("idMode").get_asInt();
    m_pDS->close();
    return idMode;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (Addon='%i', Mode='%i', Name: %s) failed", __FUNCTION__, mode.AddonID(), mode.AddonModeNumber(), mode.AddonModeName().c_str());
  }
  return -1;
}

int CActiveAEDSPDatabase::GetModes(AE_DSP_MODELIST &results, int modeType)
{
  int iReturn(0);

  CStdString strQuery=PrepareSQL("SELECT * FROM modes WHERE modes.iType='%i' ORDER BY iPosition", modeType);

  m_pDS->query( strQuery.c_str() );
  if (m_pDS->num_rows() > 0)
  {
    try
    {
      while (!m_pDS->eof())
      {
        CActiveAEDSPModePtr mode = CActiveAEDSPModePtr(new CActiveAEDSPMode());

        mode->m_iModeId                 = m_pDS->fv("idMode").get_asInt();
        mode->m_iModeType               = (AE_DSP_MODE_TYPE)m_pDS->fv("iType").get_asInt();
        mode->m_iModePosition           = m_pDS->fv("iPosition").get_asInt();
        mode->m_iStreamTypeFlags        = m_pDS->fv("iStreamTypeFlags").get_asInt();
        mode->m_iBaseType               = (AE_DSP_BASETYPE)m_pDS->fv("iBaseType").get_asInt();
        mode->m_bIsHidden               = m_pDS->fv("bIsHidden").get_asBool();
        mode->m_strOwnIconPath          = m_pDS->fv("sOwnIconPath").get_asString();
        mode->m_strOverrideIconPath     = m_pDS->fv("sOverrideIconPath").get_asString();
        mode->m_iModeName               = m_pDS->fv("iModeName").get_asInt();
        mode->m_iModeSetupName          = m_pDS->fv("iModeSetupName").get_asInt();
        mode->m_iModeHelp               = m_pDS->fv("iModeHelp").get_asInt();
        mode->m_iModeDescription        = m_pDS->fv("iModeDescription").get_asInt();
        mode->m_strAddonModeName        = m_pDS->fv("sAddonModeName").get_asString();
        mode->m_iAddonId                = m_pDS->fv("iAddonId").get_asInt();
        mode->m_iAddonModeNumber        = m_pDS->fv("iAddonModeNumber").get_asInt();
        mode->m_bHasSettingsDialog      = m_pDS->fv("bHasSettings").get_asBool();

#ifdef ADSPDB_DEBUGGING
        CLog::Log(LOGDEBUG, "Audio DSP - %s - mode '%s' loaded from the database", __FUNCTION__, mode->m_strAddonModeName.c_str());
#endif
        AE_DSP_ADDON addon;
        if (CActiveAEDSP::Get().GetAudioDSPAddon(mode->m_iAddonId, addon))
          results.push_back(AE_DSP_MODEPAIR(mode, addon));

        m_pDS->next();
        ++iReturn;
      }
      m_pDS->close();
    }
    catch (...)
    {
      CLog::Log(LOGERROR, "Audio DSP - %s - couldn't load modes from the database", __FUNCTION__);
    }
  }
  else
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - query failed", __FUNCTION__);
  }

  m_pDS->close();
  return iReturn;
}

bool CActiveAEDSPDatabase::IsModeEnabled(const CActiveAEDSPMode &mode, int &position)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    CStdString strSQL = PrepareSQL("SELECT * from modes WHERE modes.iAddonId='%i' and modes.iAddonModeNumber='%i' and modes.iType='%i'", mode.AddonID(), mode.AddonModeNumber(), mode.ModeType());

    m_pDS->query(strSQL.c_str());
    if (m_pDS->num_rows() > 0)
    {
      if (!m_pDS->fv("bIsHidden").get_asBool())
        return false;
      position = m_pDS->fv("iPosition").get_asInt();
    }

    m_pDS->close();
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (Addon='%i', Mode='%i', Name: %s) failed", __FUNCTION__, mode.AddonID(), mode.AddonModeNumber(), mode.AddonModeName().c_str());
  }
  return false;
}

/********** Settings methods **********/

bool CActiveAEDSPDatabase::DeleteActiveDSPSettings()
{
  CLog::Log(LOGDEBUG, "Audio DSP - %s - deleting all active dsp settings from the database", __FUNCTION__);
  return DeleteValues("settings");
}

bool CActiveAEDSPDatabase::DeleteActiveDSPSettings(const CFileItem *file)
{
  CStdString strPath, strFileName;
  URIUtils::Split(file->GetPath(), strPath, strFileName);

  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    CStdString strSQL=PrepareSQL("DELETE FROM settings WHERE settings.strPath='%s' and settings.strFileName='%s'", strPath.c_str() , strFileName.c_str());
    m_pDS->exec(strSQL.c_str());
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

bool CActiveAEDSPDatabase::GetActiveDSPSettings(const CFileItem *file, CAudioSettings &settings)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;
    CStdString strPath, strFileName;
    URIUtils::Split(file->GetPath(), strPath, strFileName);
    CStdString strSQL=PrepareSQL("SELECT * FROM settings WHERE settings.strPath='%s' and settings.strFileName='%s'", strPath.c_str() , strFileName.c_str());

    m_pDS->query( strSQL.c_str() );
    if (m_pDS->num_rows() > 0)
    { // get the audio dsp settings info
      settings.m_InputResampleAddon       = m_pDS->fv("InputResample").get_asInt();
      settings.m_OutputResampleAddon      = m_pDS->fv("OutputResample").get_asInt();
      settings.m_MasterStreamTypeSel      = m_pDS->fv("MasterStreamTypeSel").get_asInt();
      int type                            = m_pDS->fv("MasterStreamType").get_asInt();
      int base                            = m_pDS->fv("MasterBaseType").get_asInt();
      settings.m_MasterStreamType         = type;
      settings.m_MasterStreamBase         = base;
      settings.m_MasterModes[type][base]  = m_pDS->fv("MasterModeId").get_asInt();

      /*! if auto mode is selected, copy the identifier of previous used processor to the auto mode entry */
      settings.m_MasterModes[settings.m_MasterStreamTypeSel][base] = settings.m_MasterModes[type][base];

      m_pDS->close();
      return true;
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

void CActiveAEDSPDatabase::SetActiveDSPSettings(const CFileItem *file, const CAudioSettings &setting)
{
  try
  {
    if (NULL == m_pDB.get()) return ;
    if (NULL == m_pDS.get()) return ;
    CStdString strPath, strFileName;
    URIUtils::Split(file->GetPath(), strPath, strFileName);
    CStdString strSQL = StringUtils::Format("select * from settings WHERE settings.strPath='%s' and settings.strFileName='%s'", strPath.c_str() , strFileName.c_str());
    m_pDS->query( strSQL.c_str() );
    if (m_pDS->num_rows() > 0)
    {
      m_pDS->close();
      // update the item
      strSQL=PrepareSQL(
        "update settings set "
          "MasterStreamTypeSel=%i,"
          "MasterStreamType=%i,"
          "MasterBaseType=%i,"
          "MasterModeId=%i,",
           setting.m_MasterStreamTypeSel,
           setting.m_MasterStreamType,
           setting.m_MasterStreamBase,
           setting.m_MasterModes[setting.m_MasterStreamType][setting.m_MasterStreamBase]);
      CStdString strSQL2;
      strSQL2=PrepareSQL(
            "InputResample=%i,"
            "OutputResample=%i "
          "WHERE settings.strPath='%s' and settings.strFileName='%s'\n",
            setting.m_InputResampleAddon,
            setting.m_OutputResampleAddon,
          strPath.c_str(),
          strFileName.c_str());
      strSQL += strSQL2;
      m_pDS->exec(strSQL.c_str());
      return ;
    }
    else
    { // add the items
      m_pDS->close();
      strSQL= "INSERT INTO settings ("
                "id, "
                "strPath,"
                "strFileName,"
                "MasterStreamTypeSel,"
                "MasterStreamType,"
                "MasterBaseType,"
                "MasterModeId,"
                "InputResample,"
                "OutputResample) "
              "VALUES ";
      strSQL += PrepareSQL("(NULL,'%s','%s',%i,%i,%i,%i,%i,%i)",
                           strPath.c_str(),
                           strFileName.c_str(),
                           setting.m_MasterStreamTypeSel,
                           setting.m_MasterStreamType,
                           setting.m_MasterStreamBase,
                           setting.m_MasterModes[setting.m_MasterStreamType][setting.m_MasterStreamBase],
                           setting.m_InputResampleAddon,
                           setting.m_OutputResampleAddon);
      m_pDS->exec(strSQL.c_str());
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, file->GetPath().c_str());
  }
}

void CActiveAEDSPDatabase::EraseActiveDSPSettings()
{
  try
  {
    CLog::Log(LOGINFO, "Deleting dsp settings information for all files");
    m_pDS->exec("delete from settings");
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
}

void CActiveAEDSPDatabase::SplitPath(const CStdString& strFileNameAndPath, CStdString& strPath, CStdString& strFileName)
{
  if (URIUtils::IsStack(strFileNameAndPath) || StringUtils::StartsWithNoCase(strFileNameAndPath, "rar://") || StringUtils::StartsWithNoCase(strFileNameAndPath, "zip://"))
  {
    URIUtils::GetParentPath(strFileNameAndPath,strPath);
    strFileName = strFileNameAndPath;
  }
  else if (URIUtils::IsPlugin(strFileNameAndPath))
  {
    CURL url(strFileNameAndPath);
    strPath = url.GetWithoutFilename();
    strFileName = strFileNameAndPath;
  }
  else
    URIUtils::Split(strFileNameAndPath,strPath, strFileName);
}

/********** Audio DSP add-on methods **********/

bool CActiveAEDSPDatabase::DeleteAddons()
{
  CLog::Log(LOGDEBUG, "Audio DSP - %s - deleting all add-on's from the database", __FUNCTION__);

  return DeleteValues("addons");
}

bool CActiveAEDSPDatabase::Delete(const CActiveAEDSPAddon &addon)
{
  /* invalid addon uid */
  if (addon.ID().empty())
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - invalid addon uid", __FUNCTION__);
    return false;
  }

  Filter filter;
  filter.AppendWhere(PrepareSQL("sUid = '%s'", addon.ID().c_str()));

  return DeleteValues("addons", filter);
}

int CActiveAEDSPDatabase::GetAudioDSPAddonId(const CStdString &strAddonUid)
{
  CStdString strWhereClause = PrepareSQL("sUid = '%s'", strAddonUid.c_str());
  CStdString strValue = GetSingleValue("addons", "idAddon", strWhereClause);

  if (strValue.empty())
    return -1;

  return atol(strValue.c_str());
}

int CActiveAEDSPDatabase::Persist(const AddonPtr addon)
{
  int iReturn(-1);

  /* invalid addon uid or name */
  if (addon->Name().empty() || addon->ID().empty())
  {
    CLog::Log(LOGERROR, "Audio DSP - %s - invalid add-on uid or name", __FUNCTION__);
    return iReturn;
  }

  CStdString strQuery = PrepareSQL("REPLACE INTO addons (sName, sUid) VALUES ('%s', '%s');",
      addon->Name().c_str(), addon->ID().c_str());

  if (ExecuteQuery(strQuery))
    iReturn = (int) m_pDS->lastinsertid();

  return iReturn;
}

