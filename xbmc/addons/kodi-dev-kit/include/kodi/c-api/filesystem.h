/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_FILESYSTEM_H
#define C_API_FILESYSTEM_H

#include "addon_base.h"

#include <time.h>

#ifdef _WIN32 // windows
#ifndef _SSIZE_T_DEFINED
typedef intptr_t ssize_t;
#define _SSIZE_T_DEFINED
#endif // !_SSIZE_T_DEFINED

// Prevent conflicts with Windows macros where have this names.
#ifdef CreateDirectory
#undef CreateDirectory
#endif // CreateDirectory
#ifdef DeleteFile
#undef DeleteFile
#endif // DeleteFile
#ifdef RemoveDirectory
#undef RemoveDirectory
#endif // RemoveDirectory
#endif // _WIN32

#ifdef TARGET_POSIX // Linux, Mac, FreeBSD
#include <sys/types.h>
#endif // TARGET_POSIX

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* KODI_FILE_HDL;
  typedef void* KODI_HTTP_HEADER_HDL;

  typedef enum OpenFileFlags
  {
    ADDON_READ_TRUNCATED = 0x01,
    ADDON_READ_CHUNKED = 0x02,
    ADDON_READ_CACHED = 0x04,
    ADDON_READ_NO_CACHE = 0x08,
    ADDON_READ_BITRATE = 0x10,
    ADDON_READ_MULTI_STREAM = 0x20,
    ADDON_READ_AUDIO_VIDEO = 0x40,
    ADDON_READ_AFTER_WRITE = 0x80,
    ADDON_READ_REOPEN = 0x100
  } OpenFileFlags;

  typedef enum CURLOptiontype
  {
    ADDON_CURL_OPTION_OPTION,
    ADDON_CURL_OPTION_PROTOCOL,
    ADDON_CURL_OPTION_CREDENTIALS,
    ADDON_CURL_OPTION_HEADER
  } CURLOptiontype;

  typedef enum FilePropertyTypes
  {
    ADDON_FILE_PROPERTY_RESPONSE_PROTOCOL,
    ADDON_FILE_PROPERTY_RESPONSE_HEADER,
    ADDON_FILE_PROPERTY_CONTENT_TYPE,
    ADDON_FILE_PROPERTY_CONTENT_CHARSET,
    ADDON_FILE_PROPERTY_MIME_TYPE,
    ADDON_FILE_PROPERTY_EFFECTIVE_URL
  } FilePropertyTypes;

  struct VFS_STAT_STRUCTURE
  {
    uint32_t deviceId;
    uint64_t size;
    time_t accessTime;
    time_t modificationTime;
    time_t statusTime;
    bool isDirectory;
    bool isSymLink;
    bool isBlock;
    bool isCharacter;
    bool isFifo;
    bool isRegular;
    bool isSocket;
    uint64_t fileSerialNumber;
  };

  struct VFS_CACHE_STATUS
  {
    uint64_t forward;
    unsigned int maxrate;
    unsigned int currate;
    bool lowspeed;
  };

  struct VFS_PROPERTY
  {
    char* name;
    char* val;
  };

  struct VFS_DIR_ENTRY
  {
    char* label;
    char* title;
    char* path;
    size_t num_props;
    struct VFS_PROPERTY* properties;
    time_t date_time;
    bool folder;
    uint64_t size;
  };

  /*!@{*/
  ATTR_DLL_EXPORT bool kodi_vfs_can_open_directory(const char* url) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_create_directory(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_remove_directory(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_remove_directory_recursive(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_directory_exists(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_get_directory(const char* path,
                                                   const char* mask,
                                                   struct VFS_DIR_ENTRY** items,
                                                   size_t* num_items) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_vfs_free_directory(struct VFS_DIR_ENTRY* items,
                                                    size_t num_items) __INTRODUCED_IN_KODI(1);
  /*---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL=kodi_vfs_free_directory>---*/
  /*!@}*/

  /*!@{*/
  ATTR_DLL_EXPORT bool kodi_vfs_file_exists(const char* filename, bool useCache) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_stat_file(const char* filename,
                                               struct VFS_STAT_STRUCTURE* buffer) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_delete_file(const char* filename) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_rename_file(const char* filename, const char* newFileName) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_copy_file(const char* filename, const char* dest) __INTRODUCED_IN_KODI(1);
  /*!@}*/

  /*!@{*/
  ATTR_DLL_EXPORT char* kodi_vfs_get_file_md5(const char* filename) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_get_cache_thumb_name(const char* filename) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_make_legal_filename(const char* filename) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_make_legal_path(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_translate_special_protocol(const char* strSource) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_is_internet_stream(const char* path, bool strictCheck) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_is_on_lan(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_is_remote(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_is_local(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_is_url(const char* path) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_get_mime_type(const char* url,
                                                   char** content,
                                                   const char* useragent) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_get_content_type(const char* url,
                                                      char** content,
                                                      const char* useragent) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_get_cookies(const char* url, char** cookies) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_get_disk_space(const char* path, uint64_t* capacity, uint64_t* free, uint64_t* available) __INTRODUCED_IN_KODI(1);
  /*!@}*/

  /*!@{*/
  ATTR_DLL_EXPORT KODI_HTTP_HEADER_HDL kodi_vfs_http_header_open(const char* url) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_vfs_http_header_close(KODI_HTTP_HEADER_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_http_header_get_value(KODI_HTTP_HEADER_HDL hdl,
                                                            const char* param) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char** kodi_vfs_http_header_get_values(KODI_HTTP_HEADER_HDL hdl,
                                                              const char* param,
                                                              size_t* length) __INTRODUCED_IN_KODI(1);

  ATTR_DLL_EXPORT char* kodi_vfs_http_header_get_header(KODI_HTTP_HEADER_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_http_header_get_mime_type(KODI_HTTP_HEADER_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_http_header_get_charset(KODI_HTTP_HEADER_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_http_header_get_proto_line(KODI_HTTP_HEADER_HDL hdl) __INTRODUCED_IN_KODI(1);
  /*!@}*/

  /*!@{*/
  ATTR_DLL_EXPORT KODI_FILE_HDL kodi_vfs_file_open(const char* filename, unsigned int flags) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT KODI_FILE_HDL kodi_vfs_file_open_for_write(const char* filename,
                                                                  bool overwrite) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT KODI_FILE_HDL kodi_vfs_file_curl_create(const char* url) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_curl_add_option(KODI_FILE_HDL hdl,
                                                          enum CURLOptiontype type,
                                                          const char* name,
                                                          const char* value) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_curl_open(KODI_FILE_HDL hdl, unsigned int flags) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_vfs_file_close(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT ssize_t kodi_vfs_file_read(KODI_FILE_HDL hdl, uint8_t* ptr, size_t size) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_read_line(KODI_FILE_HDL hdl,
                                                    char* szLine,
                                                    size_t lineLength) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT ssize_t kodi_vfs_file_write(KODI_FILE_HDL hdl, const uint8_t* ptr, size_t size) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_vfs_file_flush(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT int64_t kodi_vfs_file_seek(KODI_FILE_HDL hdl, int64_t position, int whence) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT int kodi_vfs_file_truncate(KODI_FILE_HDL hdl, int64_t size) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT int64_t kodi_vfs_file_get_position(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT int64_t kodi_vfs_file_get_length(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_at_end(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT double kodi_vfs_file_get_download_speed(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT int kodi_vfs_file_get_chunk_size(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_io_ctl_get_seek_possible(KODI_FILE_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_io_ctl_get_cache_status(KODI_FILE_HDL hdl,
                                                                  struct VFS_CACHE_STATUS* status) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_io_ctl_set_cache_rate(KODI_FILE_HDL hdl,
                                                                unsigned int rate) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT bool kodi_vfs_file_io_ctl_set_retry(KODI_FILE_HDL hdl, bool retry) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char* kodi_vfs_file_get_property_value(KODI_FILE_HDL hdl,
                                                              enum FilePropertyTypes type,
                                                              const char* name) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT char** kodi_vfs_file_get_property_values(KODI_FILE_HDL hdl,
                                                                enum FilePropertyTypes type,
                                                                const char* name,
                                                                size_t* length) __INTRODUCED_IN_KODI(1);
  /*!@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !C_API_FILESYSTEM_H */
