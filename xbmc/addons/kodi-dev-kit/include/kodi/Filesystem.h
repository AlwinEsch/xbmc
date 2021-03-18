/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "AddonBase.h"
#include "c-api/filesystem.h"

#ifdef __cplusplus

#include <cstring>
#include <map>
#include <vector>

namespace kodi
{
namespace vfs
{

class FileStatus : public kodi::addon::CStructHdl<FileStatus, VFS_STAT_STRUCTURE>
{
public:
  FileStatus() { memset(m_cStructure, 0, sizeof(VFS_STAT_STRUCTURE)); }
  FileStatus(const FileStatus& channel) : CStructHdl(channel) {}
  FileStatus(const VFS_STAT_STRUCTURE* channel) : CStructHdl(channel) {}
  FileStatus(VFS_STAT_STRUCTURE* channel) : CStructHdl(channel) {}

  void SetDeviceId(uint32_t deviceId) { m_cStructure->deviceId = deviceId; }
  uint32_t GetDeviceId() const { return m_cStructure->deviceId; }

  void SetFileSerialNumber(uint64_t fileSerialNumber) { m_cStructure->fileSerialNumber = fileSerialNumber; }
  uint64_t GetFileSerialNumber() const { return m_cStructure->fileSerialNumber; }

  void SetSize(uint64_t size) { m_cStructure->size = size; }
  uint64_t GetSize() const { return m_cStructure->size; }

  void SetAccessTime(time_t accessTime) { m_cStructure->accessTime = accessTime; }
  time_t GetAccessTime() const { return m_cStructure->accessTime; }

  void SetModificationTime(time_t modificationTime)
  {
    m_cStructure->modificationTime = modificationTime;
  }
  time_t GetModificationTime() const { return m_cStructure->modificationTime; }

  void SetStatusTime(time_t statusTime) { m_cStructure->statusTime = statusTime; }
  time_t GetStatusTime() const { return m_cStructure->statusTime; }

  void SetIsDirectory(bool isDirectory) { m_cStructure->isDirectory = isDirectory; }
  bool GetIsDirectory() const { return m_cStructure->isDirectory; }

  void SetIsSymLink(bool isSymLink) { m_cStructure->isSymLink = isSymLink; }
  bool GetIsSymLink() const { return m_cStructure->isSymLink; }

  void SetIsBlock(bool isBlock) { m_cStructure->isBlock = isBlock; }
  bool GetIsBlock() const { return m_cStructure->isBlock; }

  void SetIsCharacter(bool isCharacter) { m_cStructure->isCharacter = isCharacter; }
  bool GetIsCharacter() const { return m_cStructure->isCharacter; }

  void SetIsFifo(bool isFifo) { m_cStructure->isFifo = isFifo; }
  bool GetIsFifo() const { return m_cStructure->isFifo; }

  void SetIsRegular(bool isRegular) { m_cStructure->isRegular = isRegular; }
  bool GetIsRegular() const { return m_cStructure->isRegular; }

  void SetIsSocket(bool isSocket) { m_cStructure->isSocket = isSocket; }
  bool GetIsSocket() const { return m_cStructure->isSocket; }
};

class CacheStatus
  : public kodi::addon::CStructHdl<CacheStatus, VFS_CACHE_STATUS>
{
public:
  CacheStatus() { memset(m_cStructure, 0, sizeof(VFS_CACHE_STATUS)); }
  CacheStatus(const CacheStatus& channel) : CStructHdl(channel) {}
  CacheStatus(const VFS_CACHE_STATUS* channel) : CStructHdl(channel) {}
  CacheStatus(VFS_CACHE_STATUS* channel) : CStructHdl(channel) {}

  void SetForward(uint64_t forward) { m_cStructure->forward = forward; }
  uint64_t GetForward() { return m_cStructure->forward; }

  void SetMaxRate(unsigned int maxrate) { m_cStructure->maxrate = maxrate; }
  unsigned int GetMaxRate() { return m_cStructure->maxrate; }

  void SetCurrentRate(unsigned int currate) { m_cStructure->currate = currate; }
  unsigned int GetCurrentRate() { return m_cStructure->currate; }

  void SetLowspeed(bool lowspeed) { m_cStructure->lowspeed = lowspeed; }
  bool GetLowspeed() { return m_cStructure->lowspeed; }
};

class HttpHeader
{
public:
  HttpHeader()
  {
  }

  ~HttpHeader()
  {
    kodi::dl::api.kodi_vfs_http_header_close(m_handle);
  }

  std::string GetValue(const std::string& param) const
  {
    if (!m_handle)
      return "";

    std::string protoLine;
    char* string = kodi::dl::api.kodi_vfs_http_header_get_value(m_handle, param.c_str());
    if (string != nullptr)
    {
      protoLine = string;
      free(
                                                   string);
    }
    return protoLine;
  }

  std::vector<std::string> GetValues(const std::string& param) const
  {
    if (!m_handle)
      return std::vector<std::string>();

    size_t numValues = 0;
    char** res(kodi::dl::api.kodi_vfs_http_header_get_values(m_handle,
                                   param.c_str(), &numValues));
    if (res)
    {
      std::vector<std::string> vecReturn;
      vecReturn.reserve(numValues);
      for (size_t i = 0; i < numValues; ++i)
      {
        vecReturn.emplace_back(res[i]);
        free(res[i]);
      }
      free(res);

      return vecReturn;
    }
    return std::vector<std::string>();
  }

  std::string GetHeader() const
  {
    using namespace ::kodi::addon;

    if (!m_handle)
      return "";

    std::string header;
    char* string = kodi::dl::api.kodi_vfs_http_header_get_header(m_handle);
    if (string != nullptr)
    {
      header = string;
      free(string);
    }
    return header;
  }

  std::string GetMimeType() const
  {
    using namespace ::kodi::addon;

    if (!m_handle)
      return "";

    std::string protoLine;
    char* string =
        kodi::dl::api.kodi_vfs_http_header_get_mime_type(m_handle);
    if (string != nullptr)
    {
      protoLine = string;
      free(string);
    }
    return protoLine;
  }

  std::string GetCharset() const
  {
    using namespace ::kodi::addon;

    if (!m_handle)
      return "";

    std::string protoLine;
    char* string = kodi::dl::api.kodi_vfs_http_header_get_charset(m_handle);
    if (string != nullptr)
    {
      protoLine = string;
      free(string);
    }
    return protoLine;
  }

  std::string GetProtoLine() const
  {
    using namespace ::kodi::addon;

    if (!m_handle)
      return "";

    std::string protoLine;
    char* string = kodi::dl::api.kodi_vfs_http_header_get_proto_line(m_handle);
    if (string != nullptr)
    {
      protoLine = string;
      free(string);
    }
    return protoLine;
  }

  KODI_HTTP_HEADER_HDL m_handle;
};

class CDirEntry
{
public:

  CDirEntry(const std::string& label = "",
            const std::string& path = "",
            bool folder = false,
            int64_t size = -1,
            time_t dateTime = 0)
    : m_label(label), m_path(path), m_folder(folder), m_size(size), m_dateTime(dateTime)
  {
  }

  explicit CDirEntry(const VFS_DIR_ENTRY& dirEntry)
    : m_label(dirEntry.label ? dirEntry.label : ""),
      m_path(dirEntry.path ? dirEntry.path : ""),
      m_folder(dirEntry.folder),
      m_size(dirEntry.size),
      m_dateTime(dirEntry.date_time)
  {
  }

  const std::string& Label(void) const { return m_label; }
  const std::string& Title(void) const { return m_title; }
  const std::string& Path(void) const { return m_path; }
  bool IsFolder(void) const { return m_folder; }
  int64_t Size(void) const { return m_size; }
  time_t DateTime() { return m_dateTime; }
  void SetLabel(const std::string& label) { m_label = label; }
  void SetTitle(const std::string& title) { m_title = title; }
  void SetPath(const std::string& path) { m_path = path; }
  void SetFolder(bool folder) { m_folder = folder; }
  void SetSize(int64_t size) { m_size = size; }
  void SetDateTime(time_t dateTime) { m_dateTime = dateTime; }
  void AddProperty(const std::string& id, const std::string& value) { m_properties[id] = value; }
  void ClearProperties() { m_properties.clear(); }
  const std::map<std::string, std::string>& GetProperties() const { return m_properties; }

private:
  std::string m_label;
  std::string m_title;
  std::string m_path;
  std::map<std::string, std::string> m_properties;
  bool m_folder;
  int64_t m_size;
  time_t m_dateTime;
};

inline bool CreateDirectory(const std::string& path)
{
  return kodi::dl::api.kodi_vfs_create_directory(path.c_str());
}

inline bool DirectoryExists(const std::string& path)
{
  return kodi::dl::api.kodi_vfs_directory_exists(path.c_str());
}

inline bool RemoveDirectory(const std::string& path, bool recursive = false)
{
  if (!recursive)
    return kodi::dl::api.kodi_vfs_remove_directory(path.c_str());
  else
    return kodi::dl::api.kodi_vfs_remove_directory_recursive(path.c_str());
}

inline bool GetDirectory(const std::string& path,
                                          const std::string& mask,
                                          std::vector<kodi::vfs::CDirEntry>& items)
{
  VFS_DIR_ENTRY* dir_list = nullptr;
  size_t num_items = 0;
  if (kodi::dl::api.kodi_vfs_get_directory(path.c_str(), mask.c_str(), &dir_list, &num_items))
  {
    if (dir_list)
    {
      for (size_t i = 0; i < num_items; ++i)
        items.emplace_back(dir_list[i]);

      kodi::dl::api.kodi_vfs_free_directory(dir_list, num_items);
    }

    return true;
  }
  return false;
}

inline bool FileExists(const std::string& filename, bool usecache = false)
{
  return kodi::dl::api.kodi_vfs_file_exists(filename.c_str(), usecache);
}

inline bool StatFile(const std::string& filename, kodi::vfs::FileStatus& buffer)
{
  return kodi::dl::api.kodi_vfs_stat_file(filename.c_str(), buffer);
}

inline bool DeleteFile(const std::string& filename)
{
  return kodi::dl::api.kodi_vfs_delete_file(filename.c_str());
}

inline bool RenameFile(const std::string& filename, const std::string& newFileName)
{
  return kodi::dl::api.kodi_vfs_rename_file(filename.c_str(), newFileName.c_str());
}

inline bool CopyFile(const std::string& filename, const std::string& destination)
{
  return kodi::dl::api.kodi_vfs_copy_file(filename.c_str(), destination.c_str());
}

inline std::string GetFileMD5(const std::string& path)
{

  std::string strReturn;
  char* strMd5 = kodi::dl::api.kodi_vfs_get_file_md5(path.c_str());
  if (strMd5 != nullptr)
  {
    if (std::strlen(strMd5))
      strReturn = strMd5;
    free(strMd5);
  }
  return strReturn;
}

inline std::string GetCacheThumbName(const std::string& filename)
{
  std::string strReturn;
  char* strThumbName = kodi::dl::api.kodi_vfs_get_cache_thumb_name(filename.c_str());
  if (strThumbName != nullptr)
  {
    if (std::strlen(strThumbName))
      strReturn = strThumbName;
    free(strThumbName);
  }
  return strReturn;
}

inline std::string MakeLegalFileName(const std::string& filename)
{
  std::string strReturn;
  char* strLegalFileName = kodi::dl::api.kodi_vfs_make_legal_filename(filename.c_str());
  if (strLegalFileName != nullptr)
  {
    if (std::strlen(strLegalFileName))
      strReturn = strLegalFileName;
    free(strLegalFileName);
  }
  return strReturn;
}

inline std::string MakeLegalPath(const std::string& path)
{
  std::string strReturn;
  char* strLegalPath = kodi::dl::api.kodi_vfs_make_legal_path(path.c_str());
  if (strLegalPath != nullptr)
  {
    if (std::strlen(strLegalPath))
      strReturn = strLegalPath;
    free(strLegalPath);
  }
  return strReturn;
}

inline std::string TranslateSpecialProtocol(const std::string& source)
{
  std::string strReturn;
  char* protocol = kodi::dl::api.kodi_vfs_translate_special_protocol(source.c_str());
  if (protocol != nullptr)
  {
    if (std::strlen(protocol))
      strReturn = protocol;
    free(protocol);
  }
  return strReturn;
}

// inline bool GetDiskSpace(const std::string& path,
//                                           uint64_t& capacity,
//                                           uint64_t& free,
//                                           uint64_t& available)
// {
//   return kodi::dl::api.kodi_vfs_get_disk_space(
//       path.c_str(), &capacity, &free, &available);
// }

inline std::string GetFileName(const std::string& path)
{
  /* find the last slash */
  const size_t slash = path.find_last_of("/\\");
  return path.substr(slash + 1);
}

inline std::string GetDirectoryName(const std::string& path)
{
  // Will from a full filename return the directory the file resides in.
  // Keeps the final slash at end and possible |option=foo options.

  size_t iPosSlash = path.find_last_of("/\\");
  if (iPosSlash == std::string::npos)
    return ""; // No slash, so no path (ignore any options)

  size_t iPosBar = path.rfind('|');
  if (iPosBar == std::string::npos)
    return path.substr(0, iPosSlash + 1); // Only path

  return path.substr(0, iPosSlash + 1) + path.substr(iPosBar); // Path + options
}

inline void RemoveSlashAtEnd(std::string& path)
{
  if (!path.empty())
  {
    char last = path[path.size() - 1];
    if (last == '/' || last == '\\')
      path.erase(path.size() - 1);
  }
}

inline unsigned int GetChunkSize(unsigned int chunk, unsigned int minimum)
{
  if (chunk)
    return chunk * ((minimum + chunk - 1) / chunk);
  else
    return minimum;
}

inline bool IsInternetStream(const std::string& path, bool strictCheck = false)
{
  return kodi::dl::api.kodi_vfs_is_internet_stream(path.c_str(), strictCheck);
}

inline bool IsOnLAN(const std::string& path)
{
  return kodi::dl::api.kodi_vfs_is_on_lan(path.c_str());
}

inline bool IsRemote(const std::string& path)
{
  return kodi::dl::api.kodi_vfs_is_remote(path.c_str());
}

inline bool IsLocal(const std::string& path)
{
  return kodi::dl::api.kodi_vfs_is_local(path.c_str());
}

inline bool IsURL(const std::string& path)
{
  return kodi::dl::api.kodi_vfs_is_url(path.c_str());
}

inline bool GetHttpHeader(const std::string& url, HttpHeader& header)
{
  header.m_handle = kodi::dl::api.kodi_vfs_http_header_open(url.c_str());
  return header.m_handle != nullptr;
}

inline bool GetMimeType(const std::string& url,
                                         std::string& mimeType,
                                         const std::string& useragent = "")
{
  char* cMimeType = nullptr;
  bool ret = kodi::dl::api.kodi_vfs_get_mime_type(url.c_str(), &cMimeType, useragent.c_str());
  if (cMimeType != nullptr)
  {
    mimeType = cMimeType;
    free(cMimeType);
  }
  return ret;
}

inline bool GetContentType(const std::string& url,
                                            std::string& content,
                                            const std::string& useragent = "")
{
  char* cContent = nullptr;
  bool ret = kodi::dl::api.kodi_vfs_get_content_type(url.c_str(), &cContent, useragent.c_str());
  if (cContent != nullptr)
  {
    content = cContent;
    free( cContent);
  }
  return ret;
}

inline bool GetCookies(const std::string& url, std::string& cookies)
{
  char* cCookies = nullptr;
  bool ret = kodi::dl::api.kodi_vfs_get_cookies(url.c_str(), &cCookies);
  if (cCookies != nullptr)
  {
    cookies = cCookies;
    free(cCookies);
  }
  return ret;
}

class CFile
{
public:
  CFile() = default;
  virtual ~CFile() { Close(); }

  bool OpenFile(const std::string& filename, unsigned int flags = 0)
  {
    Close();
    m_file = kodi::dl::api.kodi_vfs_file_open(filename.c_str(), flags);
    return m_file != nullptr;
  }

  bool OpenFileForWrite(const std::string& filename, bool overwrite = false)
  {
    Close();

    // Try to open the file. If it fails, check if we need to create the directory first
    // This way we avoid checking if the directory exists every time
    m_file = kodi::dl::api.kodi_vfs_file_open_for_write(
        filename.c_str(), overwrite);
    if (!m_file)
    {
      std::string cacheDirectory = kodi::vfs::GetDirectoryName(filename);
      if (kodi::dl::api.kodi_vfs_directory_exists(cacheDirectory.c_str()) ||
          kodi::dl::api.kodi_vfs_create_directory(cacheDirectory.c_str()))
        m_file = kodi::dl::api.kodi_vfs_file_open_for_write(filename.c_str(), overwrite);
    }
    return m_file != nullptr;
  }

  bool IsOpen() const { return m_file != nullptr; }

  void Close()
  {
    if (!m_file)
      return;
    kodi::dl::api.kodi_vfs_file_close(m_file);
    m_file = nullptr;
  }

  bool CURLCreate(const std::string& url)
  {
    m_file = kodi::dl::api.kodi_vfs_file_curl_create(url.c_str());
    return m_file != nullptr;
  }

  bool CURLAddOption(CURLOptiontype type, const std::string& name, const std::string& value)
  {
    if (!m_file)
    {
      kodi_log(ADDON_LOG_ERROR, "kodi::vfs::CURLCreate(...) needed to call before!");
      return false;
    }
    return kodi::dl::api.kodi_vfs_file_curl_add_option(m_file, type, name.c_str(), value.c_str());
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Open the curl file created with CURLCreate.
  ///
  /// @param[in] flags [opt] The flags to pass, see @ref OpenFileFlags
  /// @return True on success or false on failure
  ///
  bool CURLOpen(unsigned int flags = 0)
  {
    if (!m_file)
    {
      kodi_log(ADDON_LOG_ERROR, "kodi::vfs::CURLCreate(...) needed to call before!");
      return false;
    }
    return kodi::dl::api.kodi_vfs_file_curl_open(m_file, flags);
  }

  ssize_t Read(uint8_t* ptr, size_t size)
  {
    if (!m_file)
      return -1;
    return kodi::dl::api.kodi_vfs_file_read(m_file, ptr, size);
  }

  bool ReadLine(std::string& line)
  {
    line.clear();
    if (!m_file)
      return false;
    // TODO: Read 1024 chars into buffer. If file position advanced that many
    // chars, we didn't hit a newline. Otherwise, if file position is 1 or 2
    // past the number of bytes read, we read (and skipped) a newline sequence.
    char buffer[1025];
    if (kodi::dl::api.kodi_vfs_file_read_line(m_file, buffer, sizeof(buffer)))
    {
      line = buffer;
      return !line.empty();
    }
    return false;
  }

  ssize_t Write(const uint8_t* ptr, size_t size)
  {
    if (!m_file)
      return -1;
    return kodi::dl::api.kodi_vfs_file_write(m_file, ptr, size);
  }

  void Flush()
  {
    if (!m_file)
      return;
    kodi::dl::api.kodi_vfs_file_flush(m_file);
  }

  int64_t Seek(int64_t position, int whence = SEEK_SET)
  {
    if (!m_file)
      return -1;
    return kodi::dl::api.kodi_vfs_file_seek(m_file, position, whence);
  }

  int Truncate(int64_t size)
  {
    if (!m_file)
      return -1;
    return kodi::dl::api.kodi_vfs_file_truncate(m_file, size);
  }

  int64_t GetPosition() const
  {
    if (!m_file)
      return -1;
    return kodi::dl::api.kodi_vfs_file_get_position(m_file);
  }

  int64_t GetLength() const
  {
    if (!m_file)
      return -1;
    return kodi::dl::api.kodi_vfs_file_get_length(m_file);
  }

  bool AtEnd() const
  {
    return kodi::dl::api.kodi_vfs_file_at_end(m_file);
  }

  int GetChunkSize() const
  {
    if (!m_file)
      return -1;
    return kodi::dl::api.kodi_vfs_file_get_chunk_size(m_file);
  }

  bool IoControlGetSeekPossible() const
  {
    if (!m_file)
      return false;
    return kodi::dl::api.kodi_vfs_file_io_ctl_get_seek_possible(m_file);
  }

  bool IoControlGetCacheStatus(CacheStatus& status) const
  {
    if (!m_file)
      return false;
    return kodi::dl::api.kodi_vfs_file_io_ctl_get_cache_status(m_file, status);
  }

  bool IoControlSetCacheRate(unsigned int rate)
  {
    if (!m_file)
      return false;
    return kodi::dl::api.kodi_vfs_file_io_ctl_set_cache_rate(m_file, rate);
  }

  bool IoControlSetRetry(bool retry)
  {
    if (!m_file)
      return false;
    return kodi::dl::api.kodi_vfs_file_io_ctl_set_retry(m_file, retry);
  }

  const std::string GetPropertyValue(FilePropertyTypes type, const std::string& name) const
  {
    if (!m_file)
    {
      kodi_log(ADDON_LOG_ERROR,
                "kodi::vfs::CURLCreate(...) needed to call before GetPropertyValue!");
      return "";
    }
    std::vector<std::string> values = GetPropertyValues(type, name);
    if (values.empty())
    {
      return "";
    }
    return values[0];
  }

  const std::vector<std::string> GetPropertyValues(FilePropertyTypes type,
                                                   const std::string& name) const
  {
    if (!m_file)
    {
      kodi_log(ADDON_LOG_ERROR,
                "kodi::vfs::CURLCreate(...) needed to call before GetPropertyValues!");
      return std::vector<std::string>();
    }
    size_t numValues = 0;
    char** res(kodi::dl::api.kodi_vfs_file_get_property_values(
        m_file, type, name.c_str(), &numValues));
    if (res)
    {
      std::vector<std::string> vecReturn;
      vecReturn.reserve(numValues);
      for (size_t i = 0; i < numValues; ++i)
      {
        vecReturn.emplace_back(res[i]);
        free(res[i]);
      }

      free(res);

      return vecReturn;
    }
    return std::vector<std::string>();
  }

  double GetFileDownloadSpeed() const
  {
    if (!m_file)
      return 0.0;
    return kodi::dl::api.kodi_vfs_file_get_download_speed(m_file);
  }

private:
  KODI_FILE_HDL m_file = nullptr;
};

} /* namespace vfs */
} /* namespace kodi */

#endif /* __cplusplus */
