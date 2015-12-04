# *<p align="center">Kodi development</p>*
#### *<p align="center">Group: ```General```</p>*

----------

Functions
-------------

The with ```#include <kodi/addon.api2/General.h``` given functions are basically used to allow add-on access to Kodi's general functions

1. [void Log(const addon_log_t loglevel, const char* format, ...);](#CAddOnLib_General_Log) 
* [bool GetSettingString(const std::string& settingName, std::string& settingValue);](#CAddOnLib_General_GetSettingString) 
* [bool GetSettingInt(const std::string& settingName, int& settingValue);](#CAddOnLib_General_GetSettingInt)
* [bool GetSettingBoolean(const std::string& settingName, bool& settingValue);](#CAddOnLib_General_GetSettingBoolean)
* [bool GetSettingFloat(const std::string& settingName, float& settingValue);](#CAddOnLib_General_GetSettingFloat)
* [void QueueNotification(const queue_msg_t type, const char* format, ...);](#CAddOnLib_General_QueueNotification_1)
* [void QueueNotification(const queue_msg_t type, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](#CAddOnLib_General_QueueNotification_2)
* [void QueueNotification(const std::string& aCaption, const std::string& aDescription);](#CAddOnLib_General_QueueNotification_3)
* [void QueueNotification(const std::string& aImageFile, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](#CAddOnLib_General_QueueNotification_4)
* [bool UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar = false);](#CAddOnLib_General_UnknownToUTF8)
* [std::string GetLocalizedString(uint32_t labelId, const std::string& strDefault = "");](#CAddOnLib_General_GetLocalizedString)
* [std::string GetDVDMenuLanguage();](#CAddOnLib_General_GetDVDMenuLanguage)
* [float GetVolume(bool percentage = true);](#CAddOnLib_General_GetVolume)
* [void SetVolume(float value, bool isPercentage = true);](#CAddOnLib_General_SetVolume)
* [bool IsMuted();](#CAddOnLib_General_IsMuted)
* [void ToggleMute(void);](#CAddOnLib_General_ToggleMute)
* [void SetMute(bool mute);](#CAddOnLib_General_SetMute)
* [bool EjectOpticalDrive();](#CAddOnLib_General_EjectOpticalDrive)
* [void KodiVersion(kodi_version_t& version);](#CAddOnLib_General_KodiVersion)
* [void KodiQuit();](#CAddOnLib_General_KodiQuit)
* [std::string TranslateAddonStatus(ADDON_STATUS status);](#CAddOnLib_General_TranslateAddonStatus)

-------------

*  <a id="CAddOnLib_General_Log"></a><b>```void CAddOnLib_General::Log(const addon_log_t loglevel, const char* format, ...);```</b>
    * Add a message to KODI's log.
	    * <b>```loglevel```</b>The log level of the message.
		    *     LOG_DEBUG,
				  LOG_INFO,
				  LOG_NOTICE,
				  LOG_WARNING,
				  LOG_ERROR,
				  LOG_SEVERE,
				  LOG_FATAL
	    * <b>```format```</b>The format of the message to pass to KODI.
	    * <b>```...```</b>Added string values

*  <a id="CAddOnLib_General_GetSettingString"></a><b>```bool CAddOnLib_General::GetSettingString(const std::string& settingName, std::string& settingValue);```</b>
    * Get a string settings value for this add-on.
	    * <b>```settingName```</b>The name of the setting to get.
	    * <b>```settingValue```</b>The value.
		* <b>return:</b> true if successfull done

*  <a id="CAddOnLib_General_GetSettingInt"></a><b>```bool CAddOnLib_General::GetSettingInt(const std::string& settingName, int& settingValue);```</b>
    * Get a integer settings value for this add-on.
	    * <b>```settingName```</b>The name of the setting to get.
	    * <b>```settingValue```</b>The value.
		* <b>return:</b> true if successfull done

*  <a id="CAddOnLib_General_GetSettingBoolean"></a><b>```bool CAddOnLib_General::GetSettingBoolean(const std::string& settingName, bool& settingValue);```</b>
    * Get a boolean settings value for this add-on.
	    * <b>```settingName```</b>The name of the setting to get.
	    * <b>```settingValue```</b>The value.
		* <b>return:</b> true if successfull done

*  <a id="CAddOnLib_General_GetSettingFloat"></a><b>```bool CAddOnLib_General::GetSettingFloat(const std::string& settingName, float& settingValue);```</b>
    * Get a float settings value for this add-on.
	    * <b>```settingName```</b>The name of the setting to get.
	    * <b>```settingValue```</b>The value.
		* <b>return:</b> true if successful done

*  <a id="CAddOnLib_General_QueueNotification_1"></a><b>```void CAddOnLib_General::QueueNotification(const queue_msg_t  type, const char* format, ...);```</b>
    * Queue a notification in the GUI.
	    * <b>```type```</b>The message type.
		    *     QUEUE_INFO,
				  QUEUE_WARNING,
				  QUEUE_ERROR
	    * <b>```format```</b>The format of the message to pass to display in Kodi.
	    * <b>```...```</b>Added string values

*  <a id="CAddOnLib_General_QueueNotification_2"></a><b>```void CAddOnLib_General::QueueNotification(const queue_msg_t  type, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime = 5000, bool withSound   = true, unsigned int messageTime = 1000);```</b>
    * Queue a notification in the GUI.
	    * <b>```type```</b>The message type.
		    *     QUEUE_INFO,
				  QUEUE_WARNING,
				  QUEUE_ERROR
	    * <b>```aCaption```</b>Header Name
	    * <b>```aDescription```</b>Message to display on Kodi
	    * <b>```displayTime```</b>The time how long message is displayed (default 5 sec)
	    * <b>```withSound```</b>if true also warning sound becomes played
	    * <b>```messageTime```</b>how many milli seconds start show of notification

*  <a id="CAddOnLib_General_QueueNotification_3"></a><b>```void CAddOnLib_General::QueueNotification(const std::string& aCaption, const std::string& aDescription);```</b>
    * Queue a notification in the GUI.
	    * <b>```aCaption```</b>Header Name
	    * <b>```aDescription```</b>Message to display on Kodi

*  <a id="CAddOnLib_General_QueueNotification_4"></a><b>```void CAddOnLib_General::QueueNotification(const std::string& aImageFile, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime = 5000, bool withSound   = true, unsigned int messageTime = 1000);```</b>
    * Queue a notification in the GUI.
	    * <b>```aImageFile```</b>The image file to show on message
	    * <b>```aCaption```</b>Header Name
	    * <b>```aDescription```</b>Message to display on Kodi
	    * <b>```displayTime```</b>The time how long message is displayed (default 5 sec)
	    * <b>```withSound```</b> true also warning sound becomes played
	    * <b>```messageTime```</b>in how many milli seconds start show of notification

*  <a id="CAddOnLib_General_UnknownToUTF8"></a><b>```bool CAddOnLib_General::UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar = false);```</b>
    * Translate a string with an unknown encoding to UTF8.
	    * <b>```stringSrc```</b>The string to translate.
	    * <b>```utf8StringDst```</b>The translated string.
	    * <b>```failOnBadChar```</b>return failed if bad character is inside
		* <b>return:</b> true if OK

*  <a id="CAddOnLib_General_GetLocalizedString"></a><b>```std::string CAddOnLib_General::GetLocalizedString(uint32_t labelId, const std::string&  strDefault = "");```</b>
    * Get a localized message.
	    * <b>```labelId```</b>The code of the message to get.
	    * <b>```strDefault```</b>The default message, also helps to identify the code that is used
		* <b>return:</b> The localized message, or strDefault if the add-on helper fails to return a message

*  <a id="CAddOnLib_General_GetDVDMenuLanguage"></a><b>```std::string CAddOnLib_General::GetDVDMenuLanguage();```</b>
    * Get the DVD menu language.
		* <b>return:</b> The DVD menu langauge, or empty if unknown

*  <a id="CAddOnLib_General_GetVolume"></a><b>```float CAddOnLib_General::GetVolume(bool percentage = true);```</b>
    * Get the current global Kodi audio volume
	    * <b>```percentage```</b>if set to false becomes amplication level returned
		* <b>return:</b> The volume value

*  <a id="CAddOnLib_General_SetVolume"></a><b>```void CAddOnLib_General::SetVolume(float value, bool isPercentage = true);```</b>
    * Set the current global Kodi audio volume
	    * <b>```value```</b>the volume to use
	    * <b>```isPercentage```</b>if set to false becomes amplication level use

*  <a id="CAddOnLib_General_IsMuted"></a><b>```bool CAddOnLib_General::IsMuted();```</b>
    * Ask if Kodi audio is muted
		* <b>return:</b> true if audio is muted

*  <a id="CAddOnLib_General_ToggleMute"></a><b>```void CAddOnLib_General::ToggleMute(void);```</b>
    * Toggle the audio volume between on and off

*  <a id="CAddOnLib_General_SetMute"></a><b>```void CAddOnLib_General::SetMute(bool mute);```</b>
    * Set Kodi's mute
	    * <b>```mute```</b>with set to true becomes it muted otherwise audio is present

*  <a id="CAddOnLib_General_EjectOpticalDrive"></a><b>```bool CAddOnLib_General::EjectOpticalDrive();```</b>
    * Send eject signal to optical drive
		* <b>return:</b> true if successfull done

*  <a id="CAddOnLib_General_KodiVersion"></a><b>```void CAddOnLib_General::KodiVersion(kodi_version_t& version);```</b>
	```C++
	  typedef struct kodi_version
	  {
	    std::string compile_name;
	
	    int         major;
	    int         minor;
	    std::string revision;
	    std::string tag;
	    std::string tag_revision;
	  } kodi_version_t;
	```
    * Get current Kodi informations and versions, returned data from the following
        ```kodi_version_t version; CAddOnLib_General::KodiVersion(version);```
      is e.g.:
	```C++
		version.compile_name = Kodi
		version.major        = 16
		version.minor        = 0
		version.revision     = 2015-11-30-74edffb-dirty
		version.tag          = beta
		version.tag_revision = 1
	```
	*  <b>```version```</b>version structure to store data from kodi
	*  Example:
	```C++
  kodi_version_t version;
  CAddOnLib_General::KodiVersion(version);
  fprintf(stderr,
	    "kodi_version_t version;\n"
	    "CAddOnLib_General::KodiVersion(version);\n"
	    " - version.compile_name = %s\n"
	    " - version.major        = %i\n"
	    " - version.minor        = %i\n"
	    " - version.revision     = %s\n"
	    " - version.tag          = %s\n"
	    " - version.tag_revision = %s\n",
	    	    version.compile_name.c_str(), version.major, version.minor,
	    	    version.revision.c_str(), version.tag.c_str(), version.tag_revision.c_str());
	```
*  <a id="CAddOnLib_General_KodiQuit"></a><b>```void CAddOnLib_General::KodiQuit();```</b>
    * Tell Kodi to stop work, go to exit and stop his work.
      <b>WARNING:</b> Kodi is really quited!

*  <a id="CAddOnLib_General_TranslateAddonStatus"></a><b>```std::string CAddOnLib_General::TranslateAddonStatus(ADDON_STATUS status);```</b>
    * Translate an add-on status return code into a human-readable string
	    * <b>```status```</b> The return code
		* <b>return:</b> A human-readable string suitable for logging
