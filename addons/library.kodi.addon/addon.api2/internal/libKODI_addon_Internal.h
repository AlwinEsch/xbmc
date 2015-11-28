#pragma once
/*
 *      Copyright (C) 2015 Team KODI
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
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <memory>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "../definations.h"
#include "libKODI_addon_GeneralHead.h"
#include "libKODI_addon_AudioHead.h"
#include "libKODI_addon_CodecHead.h"
#include "libKODI_addon_DirectoryHead.h"
#include "libKODI_addon_FileHead.h"
#include "libKODI_addon_NetworkHead.h"

#ifdef _WIN32                   // windows
  #ifndef _SSIZE_T_DEFINED
    typedef intptr_t      ssize_t;
    #define _SSIZE_T_DEFINED
  #endif // !_SSIZE_T_DEFINED

  #if defined(BUILD_KODI_ADDON)
      #include "platform/windows/dlfcn-win32.h"
  #else
      #include "dlfcn-win32.h"
  #endif
#else
  #include <dlfcn.h>              // linux+osx
#endif
#if defined(ANDROID)
  #include <sys/stat.h>
#endif

#ifdef LOG_DEBUG
#undef LOG_DEBUG
#endif
#ifdef LOG_INFO
#undef LOG_INFO
#endif
#ifdef LOG_NOTICE
#undef LOG_NOTICE
#endif
#ifdef LOG_ERROR
#undef LOG_ERROR
#endif

#ifdef BUILD_KODI_ADDON
namespace ADDON
{
  typedef struct AddonCB
  {
    const char* libBasePath;  ///< Never, never change this!!!
    void*       addonData;
  } AddonCB;
}
#endif

#define IMPLEMENT_KODI_ADDON_LIBRARY                                           \
namespace AddOnLIB                                                             \
{                                                                              \
namespace V2                                                                   \
{                                                                              \
  std::shared_ptr<CAddonLib_Internal> CAddonLib::g_libKODI_Internal;           \
}; /* namespace V2 */                                                          \
}; /* namespace AddOnLIB */

#define KODI_ADDON_LIBRARY                                                     \
  public:                                                                      \
    static std::shared_ptr<CAddonLib_Internal> g_libKODI_Internal;             \
  public:                                                                      \
    CAddonLib() { }                                                            \
    virtual ~CAddonLib() { }

class IAESound;

namespace AddOnLIB
{
namespace V2
{
  class CAddonSoundPlay;

  typedef struct CB_AddOnLib
  {
    CB_AddOnLib_General     General;
    CB_AddOnLib_Audio       Audio;
    CB_AddOnLib_Codec       Codec;
    CB_AddOnLib_Directory   Directory;
    CB_AddOnLib_File        File;
    CB_AddOnLib_Network     Network;
  } CB_AddOnLib;

  typedef CB_AddOnLib*  _register_level(void *HANDLE, int level);
  typedef void          _unregister_me(void* HANDLE, void* CB);

  class CAddonLib_Internal
  {
  public:
    CAddonLib_Internal()
      : m_libKODI_addon(nullptr),
        m_Handle(nullptr) { }

    virtual ~CAddonLib_Internal()
    {
      UnRegisterMe();
    }

    bool RegisterMe(void *Handle)
    {
      m_Handle = Handle;

      m_libKODI_addon = dlopen(nullptr, RTLD_LAZY);
      if (m_libKODI_addon == nullptr)
      {
        fprintf(stderr, "Unable to load %s\n", dlerror());
        return false;
      }

      KODI_register = (_register_level*)
        dlsym(m_libKODI_addon, "ADDONLIB_V2_register_level");
      if (KODI_register == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      KODI_unregister = (_unregister_me*)
        dlsym(m_libKODI_addon, "ADDONLIB_V2_unregister");
      if (KODI_unregister == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      m_Callbacks = KODI_register(m_Handle, 2);
      return m_Callbacks != nullptr;
    }

    void UnRegisterMe()
    {
      if (m_libKODI_addon)
      {
        KODI_unregister(m_Handle, m_Callbacks);
        dlclose(m_libKODI_addon);
        m_libKODI_addon = nullptr;
      }
    }
    /*\
    | |_________________________________________________________________________
    | |
    \*/
    bool GetSetting(const std::string& settingName, void *settingValue)
    {
      return m_Callbacks->General.get_setting(m_Handle, settingName.c_str(), settingValue);
    }

    void Log(const addon_log_t loglevel, const char *format, va_list &args)
    {
      char buffer[16384];
      vsprintf (buffer, format, args);
      va_end (args);
      m_Callbacks->General.addon_log(m_Handle, loglevel, buffer);
    }

    void QueueNotification(const queue_msg_t type, const char *format, va_list &args)
    {
      char buffer[16384];
      vsprintf(buffer, format, args);
      va_end(args);
      m_Callbacks->General.queue_notification(m_Handle, type, buffer);
    }

    void QueueNotification
            (const queue_msg_t  type,
             const std::string& aCaption,
             const std::string& aDescription,
             unsigned int       displayTime,
             bool               withSound,
             unsigned int       messageTime)
    {
      m_Callbacks->General.queue_notification_from_type(m_Handle,
                                        type, aCaption.c_str(), aDescription.c_str(),
                                        displayTime, withSound, messageTime);
    }

    void QueueNotification
            (const std::string& aCaption,
             const std::string& aDescription)
    {
      m_Callbacks->General.queue_notification_with_image(m_Handle, "",
                                        aCaption.c_str(), aDescription.c_str(),
                                        5000, false, 1000);
    }

    void QueueNotification
          (const std::string& aImageFile,
           const std::string& aCaption,
           const std::string& aDescription,
           unsigned int       displayTime,
           bool               withSound,
           unsigned int       messageTime)
    {
      m_Callbacks->General.queue_notification_with_image(m_Handle, aImageFile.c_str(),
                                        aCaption.c_str(), aDescription.c_str(),
                                        displayTime, withSound, messageTime);
    }

    bool UnknownToUTF8
          (const std::string& stringSrc,
           std::string&       utf8StringDst,
           bool               failOnBadChar = false)
    {
      bool ret = false;
      char* retString = m_Callbacks->General.unknown_to_utf8(m_Handle, stringSrc.c_str(), ret, failOnBadChar);
      if (ret)
        utf8StringDst = retString;
      m_Callbacks->General.free_string(m_Handle, retString);
      return ret;
    }

    std::string GetLocalizedString(uint32_t labelId)
    {
      char* string = m_Callbacks->General.get_localized_string(m_Handle, labelId);
      std::string retString = string;
      m_Callbacks->General.free_string(m_Handle, string);
      return retString;
    }

    const std::string GetDVDMenuLanguage()
    {
      std::string language;
      language.resize(16);
      unsigned int size = (unsigned int)language.capacity();
      m_Callbacks->General.get_dvd_menu_language(m_Handle, language[0], size);
      language.resize(size);
      language.shrink_to_fit();
      return language;
    }
    /*\
    | |_________________________________________________________________________
    | |
    \*/
    bool WakeOnLan(const char* mac)
    {
      return m_Callbacks->Network.wake_on_lan(m_Handle, mac);
    }

    const std::string GetIPAddress()
    {
      std::string ip;
      ip.resize(32);
      unsigned int size = (unsigned int)ip.capacity();
      m_Callbacks->Network.get_ip_address(m_Handle, ip[0], size);
      ip.resize(size);
      ip.shrink_to_fit();
      return ip;
    }

    bool DNSLookup(const std::string& strHostName, std::string& strIpAddress)
    {
      bool ret = false;
      char* ipAddress = m_Callbacks->Network.dns_lookup(m_Handle, strHostName.c_str(), ret);
      strIpAddress = ipAddress;
      m_Callbacks->General.free_string(m_Handle, ipAddress);
      return ret;
    }

    std::string URLEncode(const std::string& url)
    {
      char* string = m_Callbacks->Network.url_encode(m_Handle, url.c_str());
      std::string retString = string;
      m_Callbacks->General.free_string(m_Handle, string);
      return retString;
    }
    /*\
    | |_________________________________________________________________________
    | |
    \*/
    void* OpenFile(const std::string& strFileName, unsigned int flags)
    {
      return m_Callbacks->File.open_file(m_Handle, strFileName.c_str(), flags);
    }

    void* OpenFileForWrite(const std::string& strFileName, bool bOverWrite)
    {
      return m_Callbacks->File.open_file_for_write(m_Handle, strFileName.c_str(), bOverWrite);
    }

    ssize_t ReadFile(void* file, void* lpBuf, size_t uiBufSize)
    {
      return m_Callbacks->File.read_file(m_Handle, file, lpBuf, uiBufSize);
    }

    bool ReadFileString(void* file, char *szLine, int iLineLength)
    {
      return m_Callbacks->File.read_file_string(m_Handle, file, szLine, iLineLength);
    }

    ssize_t WriteFile(void* file, const void* lpBuf, size_t uiBufSize)
    {
      return m_Callbacks->File.write_file(m_Handle, file, lpBuf, uiBufSize);
    }

    void FlushFile(void* file)
    {
       return m_Callbacks->File.flush_file(m_Handle, file);
    }

    int64_t SeekFile(void* file, int64_t iFilePosition, int iWhence)
    {
      return m_Callbacks->File.seek_file(m_Handle, file, iFilePosition, iWhence);
    }

    int TruncateFile(void* file, int64_t iSize)
    {
      return m_Callbacks->File.truncate_file(m_Handle, file, iSize);
    }

    int64_t GetFilePosition(void* file)
    {
      return m_Callbacks->File.get_file_position(m_Handle, file);
    }

    int64_t GetFileLength(void* file)
    {
      return m_Callbacks->File.get_file_length(m_Handle, file);
    }

    void CloseFile(void* file)
    {
      return m_Callbacks->File.close_file(m_Handle, file);
    }

    int GetFileChunkSize(void* file)
    {
      return m_Callbacks->File.get_file_chunk_size(m_Handle, file);
    }

    bool FileExists(const std::string& strFileName, bool bUseCache)
    {
      return m_Callbacks->File.file_exists(m_Handle, strFileName.c_str(), bUseCache);
    }

    int StatFile(const std::string& strFileName, struct __stat64* buffer)
    {
      return m_Callbacks->File.stat_file(m_Handle, strFileName.c_str(), buffer);
    }

    bool DeleteFile(const std::string& strFileName)
    {
      return m_Callbacks->File.delete_file(m_Handle, strFileName.c_str());
    }
    /*\
    | |_________________________________________________________________________
    | |
    \*/
    bool CanOpenDirectory(const std::string& strUrl)
    {
      return m_Callbacks->Directory.can_open_directory(m_Handle, strUrl.c_str());
    }

    bool CreateDirectory(const std::string& strPath)
    {
      return m_Callbacks->Directory.create_directory(m_Handle, strPath.c_str());
    }

    bool DirectoryExists(const std::string& strPath)
    {
      return m_Callbacks->Directory.directory_exists(m_Handle, strPath.c_str());
    }

    bool RemoveDirectory(const std::string& strPath)
    {
      return m_Callbacks->Directory.remove_directory(m_Handle, strPath.c_str());
    }
    /*\
    | |_________________________________________________________________________
    | |
    \*/
    kodi_codec_t GetCodecByName(const char* strCodecName)
    {
      return m_Callbacks->Codec.get_codec_by_name(m_Handle, strCodecName);
    }

    DemuxPacket* AllocateDemuxPacket(int iDataSize)
    {
      return m_Callbacks->Codec.allocate_demux_packet(m_Handle, iDataSize);
    }

    void FreeDemuxPacket(DemuxPacket* pPacket)
    {
      return m_Callbacks->Codec.free_demux_packet(m_Handle, pPacket);
    }
    /*\
    | |_________________________________________________________________________
    | |
    \*/

  protected:
    _register_level*  KODI_register;
    _unregister_me*   KODI_unregister;

  private:
    friend class CAddonSoundPlay;

    void*         m_libKODI_addon;
    void*         m_Handle;
    CB_AddOnLib*  m_Callbacks;
    struct cb_array
    {
      const char* libPath;
    };
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
