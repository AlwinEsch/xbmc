/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#include "filebrowser.h"

// Shared API
#include "addons/kodi-dev-kit/src/shared/api/gui/dialogs/filebrowser.h"

// Kodi
#include "addons/interface/RunningProcess.h"
#include "utils/log.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/

#include "URL.h"
#include "dialogs/GUIDialogFileBrowser.h"
#include "settings/MediaSourceSettings.h"
#include "storage/MediaManager.h"
#include "utils/URIUtils.h"

/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/

namespace
{

void GetVECShares(VECSOURCES& vecShares, const std::string& strShares, const std::string& strPath)
{
  std::size_t found;
  found = strShares.find("local");
  if (found != std::string::npos)
    CServiceBroker::GetMediaManager().GetLocalDrives(vecShares);
  found = strShares.find("network");
  if (found != std::string::npos)
    CServiceBroker::GetMediaManager().GetNetworkLocations(vecShares);
  found = strShares.find("removable");
  if (found != std::string::npos)
    CServiceBroker::GetMediaManager().GetRemovableDrives(vecShares);
  found = strShares.find("programs");
  if (found != std::string::npos)
  {
    VECSOURCES* sources = CMediaSourceSettings::GetInstance().GetSources("programs");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("files");
  if (found != std::string::npos)
  {
    VECSOURCES* sources = CMediaSourceSettings::GetInstance().GetSources("files");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("music");
  if (found != std::string::npos)
  {
    VECSOURCES* sources = CMediaSourceSettings::GetInstance().GetSources("music");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("video");
  if (found != std::string::npos)
  {
    VECSOURCES* sources = CMediaSourceSettings::GetInstance().GetSources("video");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("pictures");
  if (found != std::string::npos)
  {
    VECSOURCES* sources = CMediaSourceSettings::GetInstance().GetSources("pictures");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }

  if (vecShares.empty())
  {
    CMediaSource share;
    std::string basePath = strPath;
    std::string tempPath;
    while (URIUtils::GetParentPath(basePath, tempPath))
      basePath = tempPath;
    share.strPath = basePath;
    // don't include the user details in the share name
    CURL url(share.strPath);
    share.strName = url.GetWithoutUserDetails();
    vecShares.push_back(share);
  }
}

} /* namespace */

/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

void CHdl_kodi_gui_dialogs_filebrowser_h::InitDirect(
    directFuncToKodi_gui_dialogs_filebrowser_h* ifcToKodi,
    directFuncToAddon_gui_dialogs_filebrowser_h* ifcToAddon)
{
  ifcToKodi->thisClassHdl = this;
  m_ifcToAddon = ifcToAddon;
  ifcToKodi->kodi_gui_dialogs_file_browser_show_and_get_directory_v1 =
      kodi_gui_dialogs_file_browser_show_and_get_directory_v1;
  ifcToKodi->kodi_gui_dialogs_file_browser_show_and_get_file_v1 =
      kodi_gui_dialogs_file_browser_show_and_get_file_v1;
  ifcToKodi->kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1 =
      kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1;
  ifcToKodi->kodi_gui_dialogs_file_browser_show_and_get_file_list_v1 =
      kodi_gui_dialogs_file_browser_show_and_get_file_list_v1;
  ifcToKodi->kodi_gui_dialogs_file_browser_show_and_get_source_v1 =
      kodi_gui_dialogs_file_browser_show_and_get_source_v1;
  ifcToKodi->kodi_gui_dialogs_file_browser_show_and_get_image_v1 =
      kodi_gui_dialogs_file_browser_show_and_get_image_v1;
  ifcToKodi->kodi_gui_dialogs_file_browser_show_and_get_image_list_v1 =
      kodi_gui_dialogs_file_browser_show_and_get_image_list_v1;
  // Unused "kodi_gui_dialogs_file_browser_clear_file_list", done only in addon lib
}

bool CHdl_kodi_gui_dialogs_filebrowser_h::HandleMessage(int funcGroup,
                                                        int func,
                                                        const msgpack::unpacked& in,
                                                        msgpack::sbuffer& out)
{
  if (funcGroup != funcGroup_gui_dialogs_filebrowser_h)
    return false;

  switch (func)
  {
    case funcParent_kodi_gui_dialogs_file_browser_show_and_get_directory_v1:
    {
      // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_file_browser_show_and_get_directory( const char* shares, const char* heading, const char* path_in, char** path_out, bool write_only) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<std::string, std::string, std::string, bool> msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_directory_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_directory_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_directory_v1 t =
          in.get().as<decltype(t)>();
      const std::string& shares = std::get<0>(t);
      const std::string& heading = std::get<1>(t);
      const std::string& path_in = std::get<2>(t);
      char* path_out = nullptr;
      bool write_only = std::get<3>(t);
      bool auto_gen_ret = kodi_gui_dialogs_file_browser_show_and_get_directory_v1(
          this, shares.c_str(), heading.c_str(), path_in.c_str(), &path_out, write_only);
      msgpack::pack(out, msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_directory_v1(
                             auto_gen_ret, path_out ? path_out : ""));
      if (path_out)
        free(path_out);
      return true;
    }
    case funcParent_kodi_gui_dialogs_file_browser_show_and_get_file_v1:
    {
      // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_file_browser_show_and_get_file(const char* shares, const char* mask, const char* heading, const char* path_in, char** path_out, bool use_thumbs, bool use_file_directories) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<std::string, std::string, std::string, std::string, bool, bool> msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_file_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_file_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_file_v1 t =
          in.get().as<decltype(t)>();
      const std::string& shares = std::get<0>(t);
      const std::string& mask = std::get<1>(t);
      const std::string& heading = std::get<2>(t);
      const std::string& path_in = std::get<3>(t);
      char* path_out = nullptr;
      bool use_thumbs = std::get<4>(t);
      bool use_file_directories = std::get<5>(t);
      bool auto_gen_ret = kodi_gui_dialogs_file_browser_show_and_get_file_v1(
          this, shares.c_str(), mask.c_str(), heading.c_str(), path_in.c_str(), &path_out,
          use_thumbs, use_file_directories);
      msgpack::pack(out, msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_file_v1(
                             auto_gen_ret, path_out ? path_out : ""));
      if (path_out)
        free(path_out);
      return true;
    }
    case funcParent_kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1:
    {
      // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_file_browser_show_and_get_file_from_dir( const char* directory, const char* mask, const char* heading, const char* path_in, char** path_out, bool use_thumbs, bool use_file_directories, bool single_list) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<std::string, std::string, std::string, std::string, bool, bool, bool> msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1 t =
          in.get().as<decltype(t)>();
      const std::string& directory = std::get<0>(t);
      const std::string& mask = std::get<1>(t);
      const std::string& heading = std::get<2>(t);
      const std::string& path_in = std::get<3>(t);
      char* path_out = nullptr;
      bool use_thumbs = std::get<4>(t);
      bool use_file_directories = std::get<5>(t);
      bool single_list = std::get<6>(t);
      bool auto_gen_ret = kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1(
          this, directory.c_str(), mask.c_str(), heading.c_str(), path_in.c_str(), &path_out,
          use_thumbs, use_file_directories, single_list);
      msgpack::pack(out, msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1(
                             auto_gen_ret, path_out ? path_out : ""));
      if (path_out)
        free(path_out);
      return true;
    }
    case funcParent_kodi_gui_dialogs_file_browser_show_and_get_file_list_v1:
    {
      // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_file_browser_show_and_get_file_list( const char* shares, const char* mask, const char* heading, char*** file_list, size_t* entries, bool use_thumbs, bool use_file_directories) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<std::string, std::string, std::string, size_t, bool, bool> msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_file_list_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<bool, std::vector<std::string>, size_t> msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_file_list_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_file_list_v1 t =
          in.get().as<decltype(t)>();
      const std::string& shares = std::get<0>(t);
      const std::string& mask = std::get<1>(t);
      const std::string& heading = std::get<2>(t);
      char** file_list = nullptr;
      size_t entries = std::get<3>(t);
      bool use_thumbs = std::get<4>(t);
      bool use_file_directories = std::get<5>(t);
      bool auto_gen_ret = kodi_gui_dialogs_file_browser_show_and_get_file_list_v1(
          this, shares.c_str(), mask.c_str(), heading.c_str(), &file_list, &entries, use_thumbs,
          use_file_directories);
      std::vector<std::string> cpp_file_list;
      cpp_file_list.reserve(entries);
      if (file_list)
      {
        for (size_t i = 0; i < entries; ++i)
        {
          if (file_list[i])
          {
            cpp_file_list.emplace_back(file_list[i]);
            free(file_list[i]);
          }
          else
          {
            cpp_file_list.emplace_back("");
          }
        }
        free(file_list);
      }
      msgpack::pack(out, msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_file_list_v1(
                             auto_gen_ret, cpp_file_list, entries));
      return true;
    }
    case funcParent_kodi_gui_dialogs_file_browser_show_and_get_source_v1:
    {
      // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_file_browser_show_and_get_source( const char* path_in, char** path_out, bool allow_network_shares, const char* additional_share, const char* type) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<std::string, bool, std::string, std::string> msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_source_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_source_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_source_v1 t =
          in.get().as<decltype(t)>();
      const std::string& path_in = std::get<0>(t);
      char* path_out = nullptr;
      bool allow_network_shares = std::get<1>(t);
      const std::string& additional_share = std::get<2>(t);
      const std::string& type = std::get<3>(t);
      bool auto_gen_ret = kodi_gui_dialogs_file_browser_show_and_get_source_v1(
          this, path_in.c_str(), &path_out, allow_network_shares, additional_share.c_str(),
          type.c_str());
      msgpack::pack(out, msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_source_v1(
                             auto_gen_ret, path_out ? path_out : ""));
      if (path_out)
        free(path_out);
      return true;
    }
    case funcParent_kodi_gui_dialogs_file_browser_show_and_get_image_v1:
    {
      // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_file_browser_show_and_get_image(const char* shares, const char* heading, const char* path_in, char** path_out) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<std::string, std::string, std::string> msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_image_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<bool, std::string> msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_image_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_image_v1 t =
          in.get().as<decltype(t)>();
      const std::string& shares = std::get<0>(t);
      const std::string& heading = std::get<1>(t);
      const std::string& path_in = std::get<2>(t);
      char* path_out = nullptr;
      bool auto_gen_ret = kodi_gui_dialogs_file_browser_show_and_get_image_v1(
          this, shares.c_str(), heading.c_str(), path_in.c_str(), &path_out);
      msgpack::pack(out, msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_image_v1(
                             auto_gen_ret, path_out ? path_out : ""));
      if (path_out)
        free(path_out);
      return true;
    }
    case funcParent_kodi_gui_dialogs_file_browser_show_and_get_image_list_v1:
    {
      // Original API call: ATTR_DLL_EXPORT bool kodi_gui_dialogs_file_browser_show_and_get_image_list(const char* shares, const char* heading, char*** file_list, size_t* entries) __INTRODUCED_IN_KODI(1);
      // Tuple in:          typedef std::tuple<std::string, std::string, size_t> msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_image_list_v1; /* Autogenerated */
      // Tuple out:         typedef std::tuple<bool, std::vector<std::string>, size_t> msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_image_list_v1; /* Autogenerated */
      msgParent__IN_kodi_gui_dialogs_file_browser_show_and_get_image_list_v1 t =
          in.get().as<decltype(t)>();
      const std::string& shares = std::get<0>(t);
      const std::string& heading = std::get<1>(t);
      char** file_list = nullptr;
      size_t entries = std::get<2>(t);
      bool auto_gen_ret = kodi_gui_dialogs_file_browser_show_and_get_image_list_v1(
          this, shares.c_str(), heading.c_str(), &file_list, &entries);
      std::vector<std::string> cpp_file_list;
      cpp_file_list.reserve(entries);
      if (file_list)
      {
        for (size_t i = 0; i < entries; ++i)
        {
          if (file_list[i])
          {
            cpp_file_list.emplace_back(file_list[i]);
            free(file_list[i]);
          }
          else
          {
            cpp_file_list.emplace_back("");
          }
        }
        free(file_list);
      }
      msgpack::pack(out, msgParent_OUT_kodi_gui_dialogs_file_browser_show_and_get_image_list_v1(
                             auto_gen_ret, cpp_file_list, entries));
      return true;
    }
    default:
      CLog::Log(LOGERROR,
                "CHdl_kodi_gui_dialogs_filebrowser_h::{}: addon called with unknown function id "
                "'{}' on group 'gui_dialogs_filebrowser_h'",
                __func__, func);
  }

  return false;
}

// Function calls from Kodi to addon
/* NOTE: unused (no functions here) */

// Callbacks from addon to Kodi

bool CHdl_kodi_gui_dialogs_filebrowser_h::kodi_gui_dialogs_file_browser_show_and_get_directory_v1(
    void* thisClassHdl,
    const char* shares,
    const char* heading,
    const char* path_in,
    char** path_out,
    bool write_only)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_dialogs_filebrowser_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_DIRECTORY>---*/

  std::string strPath = path_in;

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, strPath);
  bool bRet = CGUIDialogFileBrowser::ShowAndGetDirectory(vecShares, heading, strPath, write_only);
  if (bRet)
    *path_out = strdup(strPath.c_str());
  return bRet;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_DIRECTORY_END>---*/
}

bool CHdl_kodi_gui_dialogs_filebrowser_h::kodi_gui_dialogs_file_browser_show_and_get_file_v1(
    void* thisClassHdl,
    const char* shares,
    const char* mask,
    const char* heading,
    const char* path_in,
    char** path_out,
    bool use_thumbs,
    bool use_file_directories)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_dialogs_filebrowser_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_FILE>---*/

  std::string strPath = path_in;

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, strPath);
  bool bRet = CGUIDialogFileBrowser::ShowAndGetFile(vecShares, mask, heading, strPath, use_thumbs,
                                                    use_file_directories);
  if (bRet)
    *path_out = strdup(strPath.c_str());
  return bRet;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_FILE_END>---*/
}

bool CHdl_kodi_gui_dialogs_filebrowser_h::
    kodi_gui_dialogs_file_browser_show_and_get_file_from_dir_v1(void* thisClassHdl,
                                                                const char* directory,
                                                                const char* mask,
                                                                const char* heading,
                                                                const char* path_in,
                                                                char** path_out,
                                                                bool use_thumbs,
                                                                bool use_file_directories,
                                                                bool single_list)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_dialogs_filebrowser_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_FILE_FROM_DIR>---*/

  std::string strPath = path_in;
  bool bRet = CGUIDialogFileBrowser::ShowAndGetFile(directory, mask, heading, strPath, use_thumbs,
                                                    use_file_directories, single_list);
  if (bRet)
    *path_out = strdup(strPath.c_str());
  return bRet;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_FILE_FROM_DIR_END>---*/
}

bool CHdl_kodi_gui_dialogs_filebrowser_h::kodi_gui_dialogs_file_browser_show_and_get_file_list_v1(
    void* thisClassHdl,
    const char* shares,
    const char* mask,
    const char* heading,
    char*** file_list,
    size_t* entries,
    bool use_thumbs,
    bool use_file_directories)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_dialogs_filebrowser_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_FILE_LIST>---*/

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, "");

  std::vector<std::string> pathsInt;
  bool bRet = CGUIDialogFileBrowser::ShowAndGetFileList(vecShares, mask, heading, pathsInt,
                                                        use_thumbs, use_file_directories);
  if (bRet)
  {
    *entries = pathsInt.size();
    *file_list = static_cast<char**>(malloc(*entries * sizeof(char*)));
    for (unsigned int i = 0; i < *entries; ++i)
      (*file_list)[i] = strdup(pathsInt[i].c_str());
  }
  else
    *entries = 0;
  return bRet;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_FILE_LIST_END>---*/
}

bool CHdl_kodi_gui_dialogs_filebrowser_h::kodi_gui_dialogs_file_browser_show_and_get_source_v1(
    void* thisClassHdl,
    const char* path_in,
    char** path_out,
    bool allow_network_shares,
    const char* additional_share,
    const char* type)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_dialogs_filebrowser_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_SOURCE>---*/

  std::string strPath = path_in;

  VECSOURCES vecShares;
  if (additional_share)
    GetVECShares(vecShares, additional_share, strPath);
  bool bRet =
      CGUIDialogFileBrowser::ShowAndGetSource(strPath, allow_network_shares, &vecShares, type);
  if (bRet)
    *path_out = strdup(strPath.c_str());
  return bRet;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_SOURCE_END>---*/
}

bool CHdl_kodi_gui_dialogs_filebrowser_h::kodi_gui_dialogs_file_browser_show_and_get_image_v1(
    void* thisClassHdl,
    const char* shares,
    const char* heading,
    const char* path_in,
    char** path_out)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_dialogs_filebrowser_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_IMAGE>---*/

  std::string strPath = path_in;

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, strPath);
  bool bRet = CGUIDialogFileBrowser::ShowAndGetImage(vecShares, heading, strPath);
  if (bRet)
    *path_out = strdup(strPath.c_str());
  return bRet;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_IMAGE_END>---*/
}

bool CHdl_kodi_gui_dialogs_filebrowser_h::kodi_gui_dialogs_file_browser_show_and_get_image_list_v1(
    void* thisClassHdl, const char* shares, const char* heading, char*** file_list, size_t* entries)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_gui_dialogs_filebrowser_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_IMAGE_LIST>---*/

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, "");

  std::vector<std::string> pathsInt;
  bool bRet = CGUIDialogFileBrowser::ShowAndGetImageList(vecShares, heading, pathsInt);
  if (bRet)
  {
    *entries = pathsInt.size();
    *file_list = static_cast<char**>(malloc(*entries * sizeof(char*)));
    for (unsigned int i = 0; i < *entries; ++i)
      (*file_list)[i] = strdup(pathsInt[i].c_str());
  }
  else
    *entries = 0;
  return bRet;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_GUI_DIALOGS_FILE_BROWSER_SHOW_AND_GET_IMAGE_LIST_END>---*/
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
