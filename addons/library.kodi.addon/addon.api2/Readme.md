# *<p align="center">Kodi development</p>*
#### *<p align="center">Binary add-on library, Version Level: 2</p>*

-------------
##### Binary classes and function to use on add-on's

Below is a code example do show what must be done on add-on base function to become support for library:

```cpp
#include "kodi/addon.api2/General.h"

using namespace AddOnLIB::V2;

# Insert one macro on your add-on for it
IMPLEMENT_KODI_ADDON_LIBRARY;

...

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!hdl || !props)
    return ADDON_STATUS_UNKNOWN;

  # Enable access to all add-on to Kodi functions
  if (!CAddonLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;

  ...
  
  # Example lib call
  CAddOnLib_General::Log(LOG_INFO, "My add-on creation done");

  return ADDON_STATUS_OK;
}

void ADDON_Destroy()
{
  ...
  CAddonLib::UnRegisterMe();
  ...
}
```

-------------

Below is showing you a description and usage of parts which becomes usable on add-on. Also a small 
demonstration code is inserted there.

###### Functions
1. [CAddOnLib_General](docs/General.md) - Generak functions
  * [void CAddOnLib_General::Log(const addon_log_t loglevel, const char* format, ...);](docs/General.md) 
    - Kodi log file write
  * [bool CAddOnLib_General::GetSettingString(const std::string& settingName, std::string& settingValue);](docs/General.md)   
    - Settings read
  * [bool CAddOnLib_General::GetSettingInt(const std::string& settingName, int& settingValue);](docs/General.md)
    - Settings read
  * [bool CAddOnLib_General::GetSettingBoolean(const std::string& settingName, bool& settingValue);](docs/General.md)
    - Settings read
  * [bool CAddOnLib_General::GetSettingFloat(const std::string& settingName, float& settingValue);](docs/General.md)
    - Settings read
  * [void CAddOnLib_General::QueueNotification(const queue_msg_t type, const char* format, ...);](docs/General.md)
    - Notification message
  * [void CAddOnLib_General::QueueNotification(const queue_msg_t type, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](docs/General.md)
    - Notification message
  * [void CAddOnLib_General::QueueNotification(const std::string& aCaption, const std::string& aDescription);](docs/General.md)
    - Notification message
  * [void CAddOnLib_General::QueueNotification(const std::string& aImageFile, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](docs/General.md)
    - Notification message
  * [bool CAddOnLib_General::UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar = false);](docs/General.md)
    - String convert to UTF8
  * [std::string CAddOnLib_General::GetLocalizedString(uint32_t labelId, const std::string& strDefault = "");](docs/General.md)
    - Localized string return
  * [std::string CAddOnLib_General::GetDVDMenuLanguage();](docs/General.md)
    - DVD language
  * [float CAddOnLib_General::GetVolume(bool percentage = true);](docs/General.md)
    - Current volume
  * [void CAddOnLib_General::SetVolume(float value, bool isPercentage = true);](docs/General.md)
    - Set volume
  * [bool CAddOnLib_General::IsMuted();](docs/General.md)
    - Is muted?
  * [void CAddOnLib_General::ToggleMute(void);](docs/General.md)
    - Toogle mute
  * [void CAddOnLib_General::SetMute(bool mute);](docs/General.md)
    - Set mute
  * [bool CAddOnLib_General::EjectOpticalDrive();](docs/General.md)
    - Eject a drive
  * [void CAddOnLib_General::KodiVersion(kodi_version_t& version);](docs/General.md)
    - Current version
  * [void CAddOnLib_General::KodiQuit();](docs/General.md)
    - Quit Kodi
  * [std::string CAddOnLib_General::TranslateAddonStatus(ADDON_STATUS status);](docs/General.md)
    - Become string about error
- [CAddOnLib_Codec](docs/Codec.md) - Codec functions
  * [kodi_codec_t CAddOnLib_Codec::GetCodecByName(const std::string &strCodecName);](docs/Codec.md) 
    - Get the codec id used by Kodi
  * [DemuxPacket* CAddOnLib_Codec::AllocateDemuxPacket(int iDataSize);](docs/Codec.md) 
    - Allocate a demux packet. Free with FreeDemuxPacket
  * [void CAddOnLib_Codec::FreeDemuxPacket(DemuxPacket* pPacket);](docs/Codec.md) 
    - Free a packet that was allocated with AllocateDemuxPacket
* [CAddOnLib_Directory](docs/Directory.md) - Directory functions
  * [bool CAddOnLib_Directory::CanOpenDirectory(const std::string& strUrl);](docs/Directory.md) 
    - Checks whether a directory can be opened.
  * [bool CAddOnLib_Directory::CreateDirectory(const std::string& strPath);](docs/Directory.md) 
    - Creates a directory.
  * [bool CAddOnLib_Directory::DirectoryExists(const std::string& strPath);](docs/Directory.md) 
    - Checks if a directory exists.
  * [bool CAddOnLib_Directory::RemoveDirectory(const std::string& strPath);](docs/Directory.md) 
    - Removes a directory.
* [CAddOnLib_File](docs/File.md) - File functions
  * [bool CAddOnLib_File::FileExists(const std::string& strFileName, bool bUseCache);](docs/File.md) 
    - Check if a file exists
  * [int CAddOnLib_File::StatFile(const std::string& strFileName, struct __stat64* buffer);](docs/File.md) 
    - Reads file status
  * [bool CAddOnLib_File::DeleteFile(const std::string& strFileName);](docs/File.md) 
    - Deletes a file
  * [std::string CAddOnLib_File::GetFileMD5(const std::string& strPath);](docs/File.md) 
    - Retrieve MD5sum of a file
  * [unsigned int CAddOnLib_File::GetChunkSize(unsigned int chunk, unsigned int minimum);](docs/File.md) 
    - Return a size aligned to the chunk size
  * [std::string CAddOnLib_File::GetFileName(const std::string& path, char separator = PATH_SEPARATOR_CHAR);](docs/File.md)
    - Return the file name from given complete path string
  * [std::string CAddOnLib_File::GetDirectoryName(const std::string& path, char separator = PATH_SEPARATOR_CHAR)](docs/File.md) 
    - Return the directory name from given complete path string
* [CAddOnLib_Network](docs/Network.md) - Network functions
  * [bool CAddOnLib_Network::WakeOnLan(const char* mac);](docs/Network.md)
    - Send WakeOnLan magic packet
  * [std::string CAddOnLib_Network::GetIPAddress();](docs/Network.md)
    - Returns the current IP address as a string
  * [std::string CAddOnLib_Network::URLEncode(const std::string& url);](docs/Network.md)
    - Encode an URL
  * [bool CAddOnLib_Network::DNSLookup(const std::string& strHostName, std::string& strIpAddress);](docs/Network.md)
    - Lookup URL in DNS cache
* [CAddOnLib_VFSUtils](docs/VFSUtils.md) - Virtual file system (VFS) functions
  * [bool CAddOnLib_VFSUtils::GetDirectory(const std::string& path, const std::string& mask, std::vector<CVFSDirEntry>& items);](docs/VFSUtils.md)
    - Lists a directory

###### Classes

1. File operation classes
  * [CVFSFile](docs/File.md)
* Background sound play classes
  * [CAddonSoundPlay](docs/SoundPlay.md)
* Stream util classes (currently used only for PVR)
  * [CStreamProperties](docs/StreamUtils.md)
  * [CPVRStream](docs/StreamUtils.md)
* Virtual file system (VFS) classes
  * [CVFSDirEntry](docs/VFSUtils.md)
  * [CVFSProperty](docs/VFSUtils.md)
