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
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "../AddonBase.h"

/*! @note Define "USE_DEMUX" at compile time if demuxing in the PVR add-on is used.
 *        Also XBMC's "DVDDemuxPacket.h" file must be in the include path of the add-on,
 *        and the add-on should set bHandlesDemuxing to true.
 */
#ifdef USE_DEMUX
#include "../DVDDemuxPacket.h"
#else
struct DemuxPacket;
#endif

namespace kodi { namespace addon { class CInstancePVRClient; } }

#define PVR_ADDON_NAME_STRING_LENGTH          1024
#define PVR_ADDON_URL_STRING_LENGTH           1024
#define PVR_ADDON_DESC_STRING_LENGTH          1024
#define PVR_ADDON_INPUT_FORMAT_STRING_LENGTH  32
#define PVR_ADDON_EDL_LENGTH                  32
#define PVR_ADDON_TIMERTYPE_ARRAY_SIZE        32
#define PVR_ADDON_TIMERTYPE_VALUES_ARRAY_SIZE 512
#define PVR_ADDON_TIMERTYPE_VALUES_ARRAY_SIZE_SMALL 128
#define PVR_ADDON_TIMERTYPE_STRING_LENGTH     64
#define PVR_ADDON_ATTRIBUTE_DESC_LENGTH 64
#define PVR_ADDON_ATTRIBUTE_VALUES_ARRAY_SIZE 512
#define PVR_ADDON_DESCRAMBLE_INFO_STRING_LENGTH 64

#define XBMC_INVALID_CODEC_ID   0
#define XBMC_INVALID_CODEC      { XBMC_CODEC_TYPE_UNKNOWN, XBMC_INVALID_CODEC_ID }

/* using the default avformat's MAX_STREAMS value to be safe */
#define PVR_STREAM_MAX_STREAMS 20

#ifdef __cplusplus
extern "C" {
#endif

  typedef unsigned int xbmc_codec_id_t;

  typedef enum
  {
      XBMC_CODEC_TYPE_UNKNOWN = -1,
      XBMC_CODEC_TYPE_VIDEO,
      XBMC_CODEC_TYPE_AUDIO,
      XBMC_CODEC_TYPE_DATA,
      XBMC_CODEC_TYPE_SUBTITLE,
      XBMC_CODEC_TYPE_RDS,
      XBMC_CODEC_TYPE_NB
  } xbmc_codec_type_t;

  typedef struct
  {
    xbmc_codec_type_t codec_type;
    xbmc_codec_id_t   codec_id;
  } xbmc_codec_t;


  /*! @name EPG entry content event types */
  //@{
  /* These IDs come from the DVB-SI EIT table "content descriptor"
  * Also known under the name "E-book genre assignments"
  */
  #define EPG_EVENT_CONTENTMASK_UNDEFINED                0x00
  #define EPG_EVENT_CONTENTMASK_MOVIEDRAMA               0x10
  #define EPG_EVENT_CONTENTMASK_NEWSCURRENTAFFAIRS       0x20
  #define EPG_EVENT_CONTENTMASK_SHOW                     0x30
  #define EPG_EVENT_CONTENTMASK_SPORTS                   0x40
  #define EPG_EVENT_CONTENTMASK_CHILDRENYOUTH            0x50
  #define EPG_EVENT_CONTENTMASK_MUSICBALLETDANCE         0x60
  #define EPG_EVENT_CONTENTMASK_ARTSCULTURE              0x70
  #define EPG_EVENT_CONTENTMASK_SOCIALPOLITICALECONOMICS 0x80
  #define EPG_EVENT_CONTENTMASK_EDUCATIONALSCIENCE       0x90
  #define EPG_EVENT_CONTENTMASK_LEISUREHOBBIES           0xA0
  #define EPG_EVENT_CONTENTMASK_SPECIAL                  0xB0
  #define EPG_EVENT_CONTENTMASK_USERDEFINED              0xF0
  //@}

  /* Set EPGTAG.iGenreType to EPG_GENRE_USE_STRING to transfer genre strings to XBMC */
  #define EPG_GENRE_USE_STRING                           0x100

  /* EPG_TAG.iFlags values */
  const unsigned int EPG_TAG_FLAG_UNDEFINED = 0x00000000; /*!< @brief nothing special to say about this entry */
  const unsigned int EPG_TAG_FLAG_IS_SERIES = 0x00000001; /*!< @brief this EPG entry is part of a series */

  /* Special EPG_TAG.iUniqueBroadcastId value */

  /*!
   * @brief special EPG_TAG.iUniqueBroadcastId value to indicate that a tag has not a valid EPG event uid.
   */
  const unsigned int EPG_TAG_INVALID_UID = 0;

  /*!
   * @brief EPG event states. Used with EpgEventStateChange callback.
   */
  typedef enum
  {
    EPG_EVENT_CREATED = 0,  /*!< @brief event created */
    EPG_EVENT_UPDATED = 1,  /*!< @brief event updated */
    EPG_EVENT_DELETED = 2,  /*!< @brief event deleted */
  } EPG_EVENT_STATE;

  /*!
   * @brief numeric PVR timer type definitions (PVR_TIMER.iTimerType values)
   */
  const unsigned int PVR_TIMER_TYPE_NONE = 0; /*!< @brief "Null" value for a numeric timer type. */

  /*!
   * @brief special PVR_TIMER.iClientIndex value to indicate that a timer has not (yet) a valid client index.
   */
  const unsigned int PVR_TIMER_NO_CLIENT_INDEX = 0; /*!< @brief timer has not (yet) a valid client index. */

  /*!
   * @brief special PVR_TIMER.iParentClientIndex value to indicate that a timer has no parent.
   */
  const unsigned int PVR_TIMER_NO_PARENT = PVR_TIMER_NO_CLIENT_INDEX; /*!< @brief timer has no parent; it was not scheduled by a repeating timer. */

  /*!
   * @brief special PVR_TIMER.iEpgUid value to indicate that a timer has no EPG event uid.
   */
  const unsigned int PVR_TIMER_NO_EPG_UID = EPG_TAG_INVALID_UID; /*!< @brief timer has no EPG event uid. */

  /*!
   * @brief special PVR_TIMER.iClientChannelUid value to indicate "any channel". Useful for some repeating timer types.
   */
  const int PVR_TIMER_ANY_CHANNEL = -1; /*!< @brief denotes "any channel", not a specific one. */

  /*!
   * @brief PVR timer type attributes (PVR_TIMER_TYPE.iAttributes values)
   */
  const unsigned int PVR_TIMER_TYPE_ATTRIBUTE_NONE                    = 0x00000000;

  const unsigned int PVR_TIMER_TYPE_IS_MANUAL                         = 0x00000001; /*!< @brief defines whether this is a type for manual (time-based) or epg-based timers */
  const unsigned int PVR_TIMER_TYPE_IS_REPEATING                      = 0x00000002; /*!< @brief defines whether this is a type for repeating or one-shot timers */
  const unsigned int PVR_TIMER_TYPE_IS_READONLY                       = 0x00000004; /*!< @brief timers of this type must not be edited by Kodi */
  const unsigned int PVR_TIMER_TYPE_FORBIDS_NEW_INSTANCES             = 0x00000008; /*!< @brief timers of this type must not be created by Kodi. All other operations are allowed, though */

  const unsigned int PVR_TIMER_TYPE_SUPPORTS_ENABLE_DISABLE           = 0x00000010; /*!< @brief this type supports enabling/disabling of the timer (PVR_TIMER.state SCHEDULED|DISABLED) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_CHANNELS                 = 0x00000020; /*!< @brief this type supports channels (PVR_TIMER.iClientChannelUid) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_START_TIME               = 0x00000040; /*!< @brief this type supports a recording start time (PVR_TIMER.startTime) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_TITLE_EPG_MATCH          = 0x00000080; /*!< @brief this type supports matching epg episode title using PVR_TIMER.strEpgSearchString */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_FULLTEXT_EPG_MATCH       = 0x00000100; /*!< @brief this type supports matching "more" epg data (not just episode title) using PVR_TIMER.strEpgSearchString. Setting FULLTEXT_EPG_MATCH implies TITLE_EPG_MATCH */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_FIRST_DAY                = 0x00000200; /*!< @brief this type supports a first day the timer gets active (PVR_TIMER.firstday) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_WEEKDAYS                 = 0x00000400; /*!< @brief this type supports weekdays for defining the recording schedule (PVR_TIMER.iWeekdays) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_RECORD_ONLY_NEW_EPISODES = 0x00000800; /*!< @brief this type supports the "record only new episodes" feature (PVR_TIMER.iPreventDuplicateEpisodes) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_START_END_MARGIN         = 0x00001000; /*!< @brief this type supports pre and post record time (PVR_TIMER.iMarginStart, PVR_TIMER.iMarginEnd) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_PRIORITY                 = 0x00002000; /*!< @brief this type supports recording priority (PVR_TIMER.iPriority) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_LIFETIME                 = 0x00004000; /*!< @brief this type supports recording lifetime (PVR_TIMER.iLifetime) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_RECORDING_FOLDERS        = 0x00008000; /*!< @brief this type supports placing recordings in user defined folders (PVR_TIMER.strDirectory) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_RECORDING_GROUP          = 0x00010000; /*!< @brief this type supports a list of recording groups (PVR_TIMER.iRecordingGroup) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_END_TIME                 = 0x00020000; /*!< @brief this type supports a recording end time (PVR_TIMER.endTime) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_START_ANYTIME            = 0x00040000; /*!< @brief enables an 'Any Time' over-ride option for startTime (using PVR_TIMER.bStartAnyTime) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_END_ANYTIME              = 0x00080000; /*!< @brief enables a separate 'Any Time' over-ride for endTime (using PVR_TIMER.bEndAnyTime) */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_MAX_RECORDINGS           = 0x00100000; /*!< @brief this type supports specifying a maximum recordings setting' (PVR_TIMER.iMaxRecordings) */
  const unsigned int PVR_TIMER_TYPE_REQUIRES_EPG_TAG_ON_CREATE        = 0x00200000; /*!< @brief this type shold not appear on any create menus which don't provide an associated EPG tag */
  const unsigned int PVR_TIMER_TYPE_FORBIDS_EPG_TAG_ON_CREATE         = 0x00400000; /*!< @brief this type should not appear on any create menus which provide an associated EPG tag */
  const unsigned int PVR_TIMER_TYPE_REQUIRES_EPG_SERIES_ON_CREATE     = 0x00800000; /*!< @brief this type should not appear on any create menus unless associated with an EPG tag with 'series' attributes (EPG_TAG.iFlags & EPG_TAG_FLAG_IS_SERIES || EPG_TAG.iSeriesNumber > 0 || EPG_TAG.iEpisodeNumber > 0 || EPG_TAG.iEpisodePartNumber > 0). Implies PVR_TIMER_TYPE_REQUIRES_EPG_TAG_ON_CREATE */
  const unsigned int PVR_TIMER_TYPE_SUPPORTS_ANY_CHANNEL              = 0x01000000; /*!< @brief this type supports 'any channel', for example when defining a timer rule that should match any channel instaed of a particular channel */

  /*!
   * @brief PVR timer weekdays (PVR_TIMER.iWeekdays values)
   */
  const unsigned int PVR_WEEKDAY_NONE      = 0x00;
  const unsigned int PVR_WEEKDAY_MONDAY    = 0x01;
  const unsigned int PVR_WEEKDAY_TUESDAY   = 0x02;
  const unsigned int PVR_WEEKDAY_WEDNESDAY = 0x04;
  const unsigned int PVR_WEEKDAY_THURSDAY  = 0x08;
  const unsigned int PVR_WEEKDAY_FRIDAY    = 0x10;
  const unsigned int PVR_WEEKDAY_SATURDAY  = 0x20;
  const unsigned int PVR_WEEKDAY_SUNDAY    = 0x40;
  const unsigned int PVR_WEEKDAY_ALLDAYS   = PVR_WEEKDAY_MONDAY   | PVR_WEEKDAY_TUESDAY | PVR_WEEKDAY_WEDNESDAY |
                                             PVR_WEEKDAY_THURSDAY | PVR_WEEKDAY_FRIDAY  | PVR_WEEKDAY_SATURDAY  |
                                             PVR_WEEKDAY_SUNDAY;

  /*!
   * @brief timeframe value for use with SetEPGTimeFrame function to indicate "no timeframe".
   */
  const int EPG_TIMEFRAME_UNLIMITED = -1;

  /*!
   * @brief special PVR_TIMER.iClientChannelUid and PVR_RECORDING.iChannelUid value to indicate that no channel uid is available.
   */
  const int PVR_CHANNEL_INVALID_UID = -1; /*!< @brief denotes that no channel uid is available. */

  /*!
   * @brief special PVR_DESCRAMBLE_INFO value to indicate that a struct member's value is not available.
   */
  const int PVR_DESCRAMBLE_INFO_NOT_AVAILABLE = -1;

  /*
   * @brief PVR add-on error codes
   */
  typedef enum
  {
    PVR_ERROR_NO_ERROR           = 0,  /*!< @brief no error occurred */
    PVR_ERROR_UNKNOWN            = -1, /*!< @brief an unknown error occurred */
    PVR_ERROR_NOT_IMPLEMENTED    = -2, /*!< @brief the method that XBMC called is not implemented by the add-on */
    PVR_ERROR_SERVER_ERROR       = -3, /*!< @brief the backend reported an error, or the add-on isn't connected */
    PVR_ERROR_SERVER_TIMEOUT     = -4, /*!< @brief the command was sent to the backend, but the response timed out */
    PVR_ERROR_REJECTED           = -5, /*!< @brief the command was rejected by the backend */
    PVR_ERROR_ALREADY_PRESENT    = -6, /*!< @brief the requested item can not be added, because it's already present */
    PVR_ERROR_INVALID_PARAMETERS = -7, /*!< @brief the parameters of the method that was called are invalid for this operation */
    PVR_ERROR_RECORDING_RUNNING  = -8, /*!< @brief a recording is running, so the timer can't be deleted without doing a forced delete */
    PVR_ERROR_FAILED             = -9, /*!< @brief the command failed */
  } PVR_ERROR;

  /*!
   * @brief PVR timer states
   */
  typedef enum
  {
    PVR_TIMER_STATE_NEW          = 0, /*!< @brief the timer was just created on the backend and is not yet active. This state must not be used for timers just created on the client side. */
    PVR_TIMER_STATE_SCHEDULED    = 1, /*!< @brief the timer is scheduled for recording */
    PVR_TIMER_STATE_RECORDING    = 2, /*!< @brief the timer is currently recordings */
    PVR_TIMER_STATE_COMPLETED    = 3, /*!< @brief the recording completed successfully */
    PVR_TIMER_STATE_ABORTED      = 4, /*!< @brief recording started, but was aborted */
    PVR_TIMER_STATE_CANCELLED    = 5, /*!< @brief the timer was scheduled, but was canceled */
    PVR_TIMER_STATE_CONFLICT_OK  = 6, /*!< @brief the scheduled timer conflicts with another one, but will be recorded */
    PVR_TIMER_STATE_CONFLICT_NOK = 7, /*!< @brief the scheduled timer conflicts with another one and won't be recorded */
    PVR_TIMER_STATE_ERROR        = 8, /*!< @brief the timer is scheduled, but can't be recorded for some reason */
    PVR_TIMER_STATE_DISABLED     = 9, /*!< @brief the timer was disabled by the user, can be enabled via setting the state to PVR_TIMER_STATE_SCHEDULED */
  } PVR_TIMER_STATE;

  /*!
   * @brief PVR menu hook categories
   */
  typedef enum
  {
    PVR_MENUHOOK_UNKNOWN           =-1, /*!< @brief unknown menu hook */
    PVR_MENUHOOK_ALL               = 0, /*!< @brief all categories */
    PVR_MENUHOOK_CHANNEL           = 1, /*!< @brief for channels */
    PVR_MENUHOOK_TIMER             = 2, /*!< @brief for timers */
    PVR_MENUHOOK_EPG               = 3, /*!< @brief for EPG */
    PVR_MENUHOOK_RECORDING         = 4, /*!< @brief for recordings */
    PVR_MENUHOOK_DELETED_RECORDING = 5, /*!< @brief for deleted recordings */
    PVR_MENUHOOK_SETTING           = 6, /*!< @brief for settings */
  } PVR_MENUHOOK_CAT;

  /*!
   * @brief PVR backend connection states. Used with ConnectionStateChange callback.
   */
  typedef enum
  {
    PVR_CONNECTION_STATE_UNKNOWN            = 0,  /*!< @brief unknown state (e.g. not yet tried to connect) */
    PVR_CONNECTION_STATE_SERVER_UNREACHABLE = 1,  /*!< @brief backend server is not reachable (e.g. server not existing or network down)*/
    PVR_CONNECTION_STATE_SERVER_MISMATCH    = 2,  /*!< @brief backend server is reachable, but there is not the expected type of server running (e.g. HTSP required, but FTP running at given server:port) */
    PVR_CONNECTION_STATE_VERSION_MISMATCH   = 3,  /*!< @brief backend server is reachable, but server version does not match client requirements */
    PVR_CONNECTION_STATE_ACCESS_DENIED      = 4,  /*!< @brief backend server is reachable, but denies client access (e.g. due to wrong credentials) */
    PVR_CONNECTION_STATE_CONNECTED          = 5,  /*!< @brief connection to backend server is established */
    PVR_CONNECTION_STATE_DISCONNECTED       = 6,  /*!< @brief no connection to backend server (e.g. due to network errors or client initiated disconnect)*/
    PVR_CONNECTION_STATE_CONNECTING         = 7,  /*!< @brief connecting to backend */
  } PVR_CONNECTION_STATE;

  /*!
   * @brief PVR recording channel types
   */
  typedef enum
  {
    PVR_RECORDING_CHANNEL_TYPE_UNKNOWN = 0, /*!< @brief unknown */
    PVR_RECORDING_CHANNEL_TYPE_TV      = 1, /*!< @brief TV channel */
    PVR_RECORDING_CHANNEL_TYPE_RADIO   = 2, /*!< @brief radio channel */
  } PVR_RECORDING_CHANNEL_TYPE;

  /*!
   * @brief Representation of a general attribute integer value.
   */
  typedef struct PVR_ATTRIBUTE_INT_VALUE
  {
    int iValue;                                           /*!< @brief (required) an integer value for a certain attribute */
    char strDescription[PVR_ADDON_ATTRIBUTE_DESC_LENGTH]; /*!< @brief (optional) a localized string describing the value. If left blank, Kodi will generate a suitable representation (like the integer value as string) */
  } ATTRIBUTE_PACKED PVR_ATTRIBUTE_INT_VALUE;

  /*!
   * @brief PVR add-on capabilities. All capabilities are set to "false" or 0 as default
   * If a capability is set to true, then the corresponding methods from xbmc_pvr_dll.h need to be implemented.
   */
  typedef struct PVR_ADDON_CAPABILITIES
  {
    bool bSupportsEPG;                  /*!< @brief true if the add-on provides EPG information */
    bool bSupportsTV;                   /*!< @brief true if this add-on provides TV channels */
    bool bSupportsRadio;                /*!< @brief true if this add-on supports radio channels */
    bool bSupportsRecordings;           /*!< @brief true if this add-on supports playback of recordings stored on the backend */
    bool bSupportsRecordingsUndelete;   /*!< @brief true if this add-on supports undelete of recordings stored on the backend */
    bool bSupportsTimers;               /*!< @brief true if this add-on supports the creation and editing of timers */
    bool bSupportsChannelGroups;        /*!< @brief true if this add-on supports channel groups */
    bool bSupportsChannelScan;          /*!< @brief true if this add-on support scanning for new channels on the backend */
    bool bSupportsChannelSettings;      /*!< @brief true if this add-on supports the following functions: DeleteChannel, RenameChannel, MoveChannel, DialogChannelSettings and DialogAddChannel */
    bool bHandlesInputStream;           /*!< @brief true if this add-on provides an input stream. false if XBMC handles the stream. */
    bool bHandlesDemuxing;              /*!< @brief true if this add-on demultiplexes packets. */
    bool bSupportsRecordingPlayCount;   /*!< @brief true if the backend supports play count for recordings. */
    bool bSupportsLastPlayedPosition;   /*!< @brief true if the backend supports store/retrieve of last played position for recordings. */
    bool bSupportsRecordingEdl;         /*!< @brief true if the backend supports retrieving an edit decision list for recordings. */
    bool bSupportsRecordingsRename;     /*!< @brief true if the backend supports renaming recordings. */
    bool bSupportsRecordingsLifetimeChange; /*!< @brief true if the backend supports changing lifetime for recordings. */
    bool bSupportsDescrambleInfo;       /*!< @brief true if the backend supports descramble information for playing channels. */

    unsigned int iRecordingsLifetimesSize; /*!< @brief (required) Count of possible values for PVR_RECORDING.iLifetime. 0 means lifetime is not supported for recordings or no own value definition wanted, but to use Kodi defaults of 1..365. */
    PVR_ATTRIBUTE_INT_VALUE recordingsLifetimeValues[PVR_ADDON_ATTRIBUTE_VALUES_ARRAY_SIZE]; /*!< @brief (optional) Array containing the possible values for PVR_RECORDING.iLifetime. Must be filled if iLifetimesSize > 0 */
  } ATTRIBUTE_PACKED PVR_ADDON_CAPABILITIES;

  /*!
   * @brief PVR stream properties
   */
  typedef struct PVR_STREAM_PROPERTIES
  {
    unsigned int iStreamCount;
    struct PVR_STREAM
    {
      unsigned int      iPID;               /*!< @brief (required) PID */
      xbmc_codec_type_t iCodecType;         /*!< @brief (required) codec type this stream */
      xbmc_codec_id_t   iCodecId;           /*!< @brief (required) codec id of this stream */
      char              strLanguage[4];     /*!< @brief (required) language id */
      int               iSubtitleInfo;      /*!< @brief (required) Subtitle Info */
      int               iFPSScale;          /*!< @brief (required) scale of 1000 and a rate of 29970 will result in 29.97 fps */
      int               iFPSRate;           /*!< @brief (required) FPS rate */
      int               iHeight;            /*!< @brief (required) height of the stream reported by the demuxer */
      int               iWidth;             /*!< @brief (required) width of the stream reported by the demuxer */
      float             fAspect;            /*!< @brief (required) display aspect ratio of the stream */
      int               iChannels;          /*!< @brief (required) amount of channels */
      int               iSampleRate;        /*!< @brief (required) sample rate */
      int               iBlockAlign;        /*!< @brief (required) block alignment */
      int               iBitRate;           /*!< @brief (required) bit rate */
      int               iBitsPerSample;     /*!< @brief (required) bits per sample */
     } stream[PVR_STREAM_MAX_STREAMS];      /*!< @brief (required) the streams */
   } ATTRIBUTE_PACKED PVR_STREAM_PROPERTIES;

  /*!
   * @brief Signal status information
   */
  typedef struct PVR_SIGNAL_STATUS
  {
    char   strAdapterName[PVR_ADDON_NAME_STRING_LENGTH];   /*!< @brief (optional) name of the adapter that's being used */
    char   strAdapterStatus[PVR_ADDON_NAME_STRING_LENGTH]; /*!< @brief (optional) status of the adapter that's being used */
    char   strServiceName[PVR_ADDON_NAME_STRING_LENGTH];   /*!< @brief (optional) name of the current service */
    char   strProviderName[PVR_ADDON_NAME_STRING_LENGTH];  /*!< @brief (optional) name of the current service's provider */
    char   strMuxName[PVR_ADDON_NAME_STRING_LENGTH];       /*!< @brief (optional) name of the current mux */
    int    iSNR;                                           /*!< @brief (optional) signal/noise ratio */
    int    iSignal;                                        /*!< @brief (optional) signal strength */
    long   iBER;                                           /*!< @brief (optional) bit error rate */
    long   iUNC;                                           /*!< @brief (optional) uncorrected blocks */
  } ATTRIBUTE_PACKED PVR_SIGNAL_STATUS;

  /*!
   * @brief descramble information
   */
  typedef struct PVR_DESCRAMBLE_INFO
  {
    int iPid;     /*!< @brief (optional) pid; PVR_DESCRAMBLE_INFO_NOT_AVAILABLE if not available */
    int iCaid;    /*!< @brief (optional) caid; PVR_DESCRAMBLE_INFO_NOT_AVAILABLE if not available */
    int iProvid;  /*!< @brief (optional) provid; PVR_DESCRAMBLE_INFO_NOT_AVAILABLE if not available */
    int iEcmTime; /*!< @brief (optional) ecm time; PVR_DESCRAMBLE_INFO_NOT_AVAILABLE if not available */
    int iHops;    /*!< @brief (optional) hops; PVR_DESCRAMBLE_INFO_NOT_AVAILABLE if not available */
    char strCardSystem[PVR_ADDON_DESCRAMBLE_INFO_STRING_LENGTH];  /*!< @brief (optional); empty string if not available */
    char strReader[PVR_ADDON_DESCRAMBLE_INFO_STRING_LENGTH];      /*!< @brief (optional); empty string if not available */
    char strFrom[PVR_ADDON_DESCRAMBLE_INFO_STRING_LENGTH];        /*!< @brief (optional); empty string if not available */
    char strProtocol[PVR_ADDON_DESCRAMBLE_INFO_STRING_LENGTH];    /*!< @brief (optional); empty string if not available */
  } ATTRIBUTE_PACKED PVR_DESCRAMBLE_INFO;

  /*!
   * @brief Menu hooks that are available in the context menus while playing a stream via this add-on.
   * And in the Live TV settings dialog
   */
  typedef struct PVR_MENUHOOK
  {
    unsigned int     iHookId;              /*!< @brief (required) this hook's identifier */
    unsigned int     iLocalizedStringId;   /*!< @brief (required) the id of the label for this hook in g_localizeStrings */
    PVR_MENUHOOK_CAT category;             /*!< @brief (required) category of menu hook */
  } ATTRIBUTE_PACKED PVR_MENUHOOK;

  /*!
   * @brief Representation of a TV or radio channel.
   */
  typedef struct PVR_CHANNEL
  {
    unsigned int iUniqueId;                                            /*!< @brief (required) unique identifier for this channel */
    bool         bIsRadio;                                             /*!< @brief (required) true if this is a radio channel, false if it's a TV channel */
    unsigned int iChannelNumber;                                       /*!< @brief (optional) channel number of this channel on the backend */
    unsigned int iSubChannelNumber;                                    /*!< @brief (optional) sub channel number of this channel on the backend (ATSC) */
    char         strChannelName[PVR_ADDON_NAME_STRING_LENGTH];         /*!< @brief (optional) channel name given to this channel */
    char         strInputFormat[PVR_ADDON_INPUT_FORMAT_STRING_LENGTH]; /*!< @brief (optional) input format type. types can be found in ffmpeg/libavformat/allformats.c
                                                                                   leave empty if unknown */
    char         strStreamURL[PVR_ADDON_URL_STRING_LENGTH];            /*!< @brief (optional) the URL to use to access this channel.
                                                                                   leave empty to use this add-on to access the stream.
                                                                                   set to a path that's supported by XBMC otherwise. */
    unsigned int iEncryptionSystem;                                    /*!< @brief (optional) the encryption ID or CaID of this channel */
    char         strIconPath[PVR_ADDON_URL_STRING_LENGTH];             /*!< @brief (optional) path to the channel icon (if present) */
    bool         bIsHidden;                                            /*!< @brief (optional) true if this channel is marked as hidden */
  } ATTRIBUTE_PACKED PVR_CHANNEL;

  typedef struct PVR_CHANNEL_GROUP
  {
    char         strGroupName[PVR_ADDON_NAME_STRING_LENGTH]; /*!< @brief (required) name of this channel group */
    bool         bIsRadio;                                   /*!< @brief (required) true if this is a radio channel group, false otherwise. */
    unsigned int iPosition;                                  /*!< @brief (optional) sort position of the group (0 indicates that the backend doesn't support sorting of groups) */
  } ATTRIBUTE_PACKED PVR_CHANNEL_GROUP;

  typedef struct PVR_CHANNEL_GROUP_MEMBER
  {
    char         strGroupName[PVR_ADDON_NAME_STRING_LENGTH]; /*!< @brief (required) name of the channel group to add the channel to */
    unsigned int iChannelUniqueId;                           /*!< @brief (required) unique id of the member */
    unsigned int iChannelNumber;                             /*!< @brief (optional) channel number within the group */
  } ATTRIBUTE_PACKED PVR_CHANNEL_GROUP_MEMBER;

  /*!
   * @brief Representation of a timer type's attribute integer value.
   */
  typedef PVR_ATTRIBUTE_INT_VALUE PVR_TIMER_TYPE_ATTRIBUTE_INT_VALUE;

  /*!
   * @brief Representation of a timer type.
   */
  typedef struct PVR_TIMER_TYPE
  {
    unsigned int iId;                                       /*!< @brief (required) this type's identifier. Ids must be > PVR_TIMER_TYPE_NONE. */
    unsigned int iAttributes;                               /*!< @brief (required) defines the attributes for this type (PVR_TIMER_TYPE_* constants). */
    char strDescription[PVR_ADDON_TIMERTYPE_STRING_LENGTH]; /*!< @brief (optional) a short localized string describing the purpose of the type. (e.g.
                                                              "Any time at this channel if title matches"). If left blank, Kodi will generate a
                                                              description based on the attributes REPEATING and MANUAL. (e.g. "Repeating EPG-based." */
    /* priority value definitions */
    unsigned int iPrioritiesSize;                           /*!< @brief (required) Count of possible values for PVR_TMER.iPriority. 0 means priority
                                                              is not supported by this timer type or no own value definition wanted, but to use Kodi defaults
                                                              of 1..100. */
    PVR_TIMER_TYPE_ATTRIBUTE_INT_VALUE
      priorities[PVR_ADDON_TIMERTYPE_VALUES_ARRAY_SIZE];    /*!< @brief (optional) Array containing the possible values for PVR_TMER.iPriority. Must be
                                                              filled if iPrioritiesSize > 0 */
    int          iPrioritiesDefault;                        /*!< @brief (optional) The default value for PVR_TMER.iPriority. Must be filled if iPrioritiesSize > 0 */

    /* lifetime value definitions */
    unsigned int iLifetimesSize;                            /*!< @brief (required) Count of possible values for PVR_TMER.iLifetime. 0 means lifetime
                                                              is not supported by this timer type or no own value definition wanted, but to use Kodi defaults
                                                              of 1..365. */
    PVR_TIMER_TYPE_ATTRIBUTE_INT_VALUE
      lifetimes[PVR_ADDON_TIMERTYPE_VALUES_ARRAY_SIZE];     /*!< @brief (optional) Array containing the possible values for PVR_TMER.iLifetime. Must be
                                                              filled if iLifetimesSize > 0 */
    int          iLifetimesDefault;                         /*!< @brief (optional) The default value for PVR_TMER.iLifetime. Must be filled if iLifetimesSize > 0 */

    /* prevent duplicate episodes value definitions */
    unsigned int iPreventDuplicateEpisodesSize;             /*!< @brief (required) Count of possible values for PVR_TMER.iPreventDuplicateEpisodes. 0 means duplicate
                                                              episodes prevention is not supported by this timer type or no own value definition wanted, but to use
                                                              Kodi defaults. */
    PVR_TIMER_TYPE_ATTRIBUTE_INT_VALUE
      preventDuplicateEpisodes[PVR_ADDON_TIMERTYPE_VALUES_ARRAY_SIZE];
                                                            /*!< @brief (optional) Array containing the possible values for PVR_TMER.iPreventDuplicateEpisodes.. Must
                                                              be filled if iPreventDuplicateEpisodesSize > 0 */
    unsigned int iPreventDuplicateEpisodesDefault;          /*!< @brief (optional) The default value for PVR_TMER.iPreventDuplicateEpisodesSize. Must be filled if iPreventDuplicateEpisodesSize > 0 */

    /* recording folder list value definitions */
    unsigned int iRecordingGroupSize;                       /*!< @brief (required) Count of possible values of PVR_TIMER.iRecordingGroup. 0 means folder lists are not supported by this timer type */
    PVR_TIMER_TYPE_ATTRIBUTE_INT_VALUE
      recordingGroup[PVR_ADDON_TIMERTYPE_VALUES_ARRAY_SIZE];
                                                            /*!< @brief (optional) Array containing the possible values of PVR_TMER.iRecordingGroup. Must be filled if iRecordingGroupSize > 0 */
    unsigned int iRecordingGroupDefault;                    /*!< @brief (optional) The default value for PVR_TIMER.iRecordingGroup. Must be filled in if PVR_TIMER.iRecordingGroupSize > 0 */

    /* max recordings value definitions */
    unsigned int iMaxRecordingsSize;                        /*!< @brief (required) Count of possible values of PVR_TIMER.iMaxRecordings. 0 means max recordings are not supported by this timer type */
    PVR_TIMER_TYPE_ATTRIBUTE_INT_VALUE
      maxRecordings[PVR_ADDON_TIMERTYPE_VALUES_ARRAY_SIZE_SMALL];
                                                            /*!< @brief (optional) Array containing the possible values of PVR_TMER.iMaxRecordings. */
    int iMaxRecordingsDefault;                              /*!< @brief (optional) The default value for PVR_TIMER.iMaxRecordings. Must be filled in if PVR_TIMER.iMaxRecordingsSize > 0 */

  } ATTRIBUTE_PACKED PVR_TIMER_TYPE;

  /*!
   * @brief Representation of a timer event.
   */
  typedef struct PVR_TIMER {
    unsigned int    iClientIndex;                              /*!< @brief (required) the index of this timer given by the client. PVR_TIMER_NO_CLIENT_INDEX indicates that the index was not yet set by the client, for example for new timers created by
                                                                    Kodi and passed the first time to the client. A valid index must be greater than PVR_TIMER_NO_CLIENT_INDEX. */
    unsigned int    iParentClientIndex;                        /*!< @brief (optional) for timers scheduled by a repeating timer, the index of the repeating timer that scheduled this timer (it's PVR_TIMER.iClientIndex value). Use PVR_TIMER_NO_PARENT
                                                                    to indicate that this timer was no scheduled by a repeating timer. */
    int             iClientChannelUid;                         /*!< @brief (optional) unique identifier of the channel to record on. PVR_TIMER_ANY_CHANNEL will denote "any channel", not a specific one. PVR_CHANNEL_INVALID_UID denotes that channel uid is not available.*/
    time_t          startTime;                                 /*!< @brief (optional) start time of the recording in UTC. Instant timers that are sent to the add-on by Kodi will have this value set to 0.*/
    time_t          endTime;                                   /*!< @brief (optional) end time of the recording in UTC. */
    bool            bStartAnyTime;                             /*!< @brief (optional) for EPG based (not Manual) timers indicates startTime does not apply. Default = false */
    bool            bEndAnyTime;                               /*!< @brief (optional) for EPG based (not Manual) timers indicates endTime does not apply. Default = false */
    PVR_TIMER_STATE state;                                     /*!< @brief (required) the state of this timer */
    unsigned int    iTimerType;                                /*!< @brief (required) the type of this timer. It is private to the addon and can be freely defined by the addon. The value must be greater than PVR_TIMER_TYPE_NONE.
                                                                    Kodi does not interpret this value (except for checking for PVR_TIMER_TYPE_NONE), but will pass the right id to the addon with every PVR_TIMER instance, thus the addon easily can determine
                                                                    the timer type. */
    char            strTitle[PVR_ADDON_NAME_STRING_LENGTH];    /*!< @brief (required) a title for this timer */
    char            strEpgSearchString[PVR_ADDON_NAME_STRING_LENGTH]; /*!< @brief (optional) a string used to search epg data for repeating epg-based timers. Format is backend-dependent, for example regexp */
    bool            bFullTextEpgSearch;                        /*!< @brief (optional) indicates, whether strEpgSearchString is to match against the epg episode title only or also against "other" epg data (backend-dependent) */
    char            strDirectory[PVR_ADDON_URL_STRING_LENGTH]; /*!< @brief (optional) the (relative) directory where the recording will be stored in */
    char            strSummary[PVR_ADDON_DESC_STRING_LENGTH];  /*!< @brief (optional) the summary for this timer */
    int             iPriority;                                 /*!< @brief (optional) the priority of this timer */
    int             iLifetime;                                 /*!< @brief (optional) lifetime of recordings created by this timer. > 0 days after which recordings will be deleted by the backend, < 0 addon defined integer list reference, == 0 disabled */
    int             iMaxRecordings;                            /*!< @brief (optional) maximum number of recordings this timer shall create. > 0 number of recordings, < 0 addon defined integer list reference, == 0 disabled */
    unsigned int    iRecordingGroup;                           /*!< @brief (optional) integer ref to addon/backend defined list of recording groups*/
    time_t          firstDay;                                  /*!< @brief (optional) the first day this timer is active, for repeating timers */
    unsigned int    iWeekdays;                                 /*!< @brief (optional) week days, for repeating timers */
    unsigned int    iPreventDuplicateEpisodes;                 /*!< @brief (optional) 1 if backend should only record new episodes in case of a repeating epg-based timer, 0 if all episodes shall be recorded (no duplicate detection). Actual algorithm for
                                                                    duplicate detection is defined by the backend. Addons may define own values for different duplicate detection algorithms, thus this is not just a bool.*/
    unsigned int    iEpgUid;                                   /*!< @brief (optional) EPG event id associated with this timer. Event ids must be unique for a channel. Valid ids must be greater than EPG_TAG_INVALID_UID. */
    unsigned int    iMarginStart;                              /*!< @brief (optional) if set, the backend starts the recording iMarginStart minutes before startTime. */
    unsigned int    iMarginEnd;                                /*!< @brief (optional) if set, the backend ends the recording iMarginEnd minutes after endTime. */
    int             iGenreType;                                /*!< @brief (optional) genre type */
    int             iGenreSubType;                             /*!< @brief (optional) genre sub type */
  } ATTRIBUTE_PACKED PVR_TIMER;

  /*!
   * @brief Representation of a recording.
   */
  typedef struct PVR_RECORDING {
    char   strRecordingId[PVR_ADDON_NAME_STRING_LENGTH];  /*!< @brief (required) unique id of the recording on the client. */
    char   strTitle[PVR_ADDON_NAME_STRING_LENGTH];        /*!< @brief (required) the title of this recording */
    char   strEpisodeName[PVR_ADDON_NAME_STRING_LENGTH];  /*!< @brief (optional) episode name (also known as subtitle) */
    int    iSeriesNumber;                                 /*!< @brief (optional) series number (usually called season). Set to "0" for specials/pilot. For 'invalid' see iEpisodeNumber or set to -1 */
    int    iEpisodeNumber;                                /*!< @brief (optional) episode number within the "iSeriesNumber" season. For 'invalid' set to -1 or iSeriesNumber=iEpisodeNumber=0 to show both are invalid */
    int    iYear;                                         /*!< @brief (optional) year of first release (use to identify a specific movie re-make) / first airing for TV shows. Set to '0' for invalid. */
    char   strStreamURL[PVR_ADDON_URL_STRING_LENGTH];     /*!< @brief (required) stream URL to access this recording */
    char   strDirectory[PVR_ADDON_URL_STRING_LENGTH];     /*!< @brief (optional) directory of this recording on the client */
    char   strPlotOutline[PVR_ADDON_DESC_STRING_LENGTH];  /*!< @brief (optional) plot outline */
    char   strPlot[PVR_ADDON_DESC_STRING_LENGTH];         /*!< @brief (optional) plot */
    char   strGenreDescription[PVR_ADDON_DESC_STRING_LENGTH]; /*!< @brief (optional) genre. Will be used only when iGenreType = EPG_GENRE_USE_STRING */
    char   strChannelName[PVR_ADDON_NAME_STRING_LENGTH];  /*!< @brief (optional) channel name */
    char   strIconPath[PVR_ADDON_URL_STRING_LENGTH];      /*!< @brief (optional) icon path */
    char   strThumbnailPath[PVR_ADDON_URL_STRING_LENGTH]; /*!< @brief (optional) thumbnail path */
    char   strFanartPath[PVR_ADDON_URL_STRING_LENGTH];    /*!< @brief (optional) fanart path */
    time_t recordingTime;                                 /*!< @brief (optional) start time of the recording */
    int    iDuration;                                     /*!< @brief (optional) duration of the recording in seconds */
    int    iPriority;                                     /*!< @brief (optional) priority of this recording (from 0 - 100) */
    int    iLifetime;                                     /*!< @brief (optional) life time in days of this recording */
    int    iGenreType;                                    /*!< @brief (optional) genre type */
    int    iGenreSubType;                                 /*!< @brief (optional) genre sub type */
    int    iPlayCount;                                    /*!< @brief (optional) play count of this recording on the client */
    int    iLastPlayedPosition;                           /*!< @brief (optional) last played position of this recording on the client */
    bool   bIsDeleted;                                    /*!< @brief (optional) shows this recording is deleted and can be undelete */
    unsigned int iEpgEventId;                             /*!< @brief (optional) EPG event id associated with this recording. Valid ids must be greater than EPG_TAG_INVALID_UID. */
    int    iChannelUid;                                   /*!< @brief (optional) unique identifier of the channel for this recording. PVR_CHANNEL_INVALID_UID denotes that channel uid is not available. */
    PVR_RECORDING_CHANNEL_TYPE channelType;               /*!< @brief (optional) channel type. Set to PVR_RECORDING_CHANNEL_TYPE_UNKNOWN if the type cannot be determined. */
  } ATTRIBUTE_PACKED PVR_RECORDING;

  /*!
   * @brief Edit definition list (EDL)
   */
  typedef enum
  {
    PVR_EDL_TYPE_CUT      = 0, /*!< @brief cut (completely remove content) */
    PVR_EDL_TYPE_MUTE     = 1, /*!< @brief mute audio */
    PVR_EDL_TYPE_SCENE    = 2, /*!< @brief scene markers (chapter seeking) */
    PVR_EDL_TYPE_COMBREAK = 3  /*!< @brief commercial breaks */
  } PVR_EDL_TYPE;

  typedef struct PVR_EDL_ENTRY
  {
    int64_t start;     // ms
    int64_t end;       // ms
    PVR_EDL_TYPE type;
  } ATTRIBUTE_PACKED PVR_EDL_ENTRY;

  /*!
   * @brief PVR menu hook data
   */
  typedef struct PVR_MENUHOOK_DATA
  {
    PVR_MENUHOOK_CAT cat;
    union data {
      int iEpgUid;
      PVR_CHANNEL channel;
      PVR_TIMER timer;
      PVR_RECORDING recording;
    } data;
  } ATTRIBUTE_PACKED PVR_MENUHOOK_DATA;

  /*!
   * @brief Representation of an EPG event.
   */
  typedef struct EPG_TAG {
    unsigned int  iUniqueBroadcastId;  /*!< @brief (required) identifier for this event. Event uids must be unique for a channel. Valid uids must be greater than EPG_TAG_INVALID_UID. */
    const char *  strTitle;            /*!< @brief (required) this event's title */
    unsigned int  iChannelNumber;      /*!< @brief (required) the number of the channel this event occurs on */
    time_t        startTime;           /*!< @brief (required) start time in UTC */
    time_t        endTime;             /*!< @brief (required) end time in UTC */
    const char *  strPlotOutline;      /*!< @brief (optional) plot outline */
    const char *  strPlot;             /*!< @brief (optional) plot */
    const char *  strOriginalTitle;    /*!< @brief (optional) originaltitle */
    const char *  strCast;             /*!< @brief (optional) cast */
    const char *  strDirector;         /*!< @brief (optional) director */
    const char *  strWriter;           /*!< @brief (optional) writer */
    int           iYear;               /*!< @brief (optional) year */
    const char *  strIMDBNumber;       /*!< @brief (optional) IMDBNumber */
    const char *  strIconPath;         /*!< @brief (optional) icon path */
    int           iGenreType;          /*!< @brief (optional) genre type */
    int           iGenreSubType;       /*!< @brief (optional) genre sub type */
    const char *  strGenreDescription; /*!< @brief (optional) genre. Will be used only when iGenreType = EPG_GENRE_USE_STRING */
    time_t        firstAired;          /*!< @brief (optional) first aired in UTC */
    int           iParentalRating;     /*!< @brief (optional) parental rating */
    int           iStarRating;         /*!< @brief (optional) star rating */
    bool          bNotify;             /*!< @brief (optional) notify the user when this event starts */
    int           iSeriesNumber;       /*!< @brief (optional) series number */
    int           iEpisodeNumber;      /*!< @brief (optional) episode number */
    int           iEpisodePartNumber;  /*!< @brief (optional) episode part number */
    const char *  strEpisodeName;      /*!< @brief (optional) episode name */
    unsigned int  iFlags;              /*!< @brief (optional) bit field of independent flags associated with the EPG entry */
  } ATTRIBUTE_PACKED EPG_TAG;

  typedef struct AddonToKodiFuncTable_PVR
  {
    KODI_HANDLE kodi_instance;

    void (*transfer_epg_entry)(void* kodi_instance, const ADDON_HANDLE handle, const EPG_TAG* epgentry);
    void (*transfer_channel_entry)(void* kodi_instance, const ADDON_HANDLE handle, const PVR_CHANNEL* channel);
    void (*transfer_timer_entry)(void* kodi_instance, const ADDON_HANDLE handle, const PVR_TIMER* timer);
    void (*transfer_recording_entry)(void* kodi_instance, const ADDON_HANDLE handle, const PVR_RECORDING* recording);
    void (*add_menu_hook)(void* kodi_instance, const PVR_MENUHOOK* hook);
    void (*recording)(void* kodi_instance, const char* name, const char* filename, bool on);
    void (*trigger_channel_update)(void* kodi_instance);
    void (*trigger_timer_update)(void* kodi_instance);
    void (*trigger_recording_update)(void* kodi_instance);
    void (*trigger_channel_groups_update)(void* kodi_instance);
    void (*trigger_epg_update)(void* kodi_instance, unsigned int channel_uid);

    void (*transfer_channel_group)(void* kodi_instance, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* group);
    void (*transfer_channel_group_member)(void* kodi_instance, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* member);

    void (*free_demux_packet)(void* kodi_instance, DemuxPacket* packet);
    DemuxPacket* (*allocate_demux_packet)(void* kodi_instance, int data_size);
    
    void (*connection_state_change)(void* kodi_instance, const char* connection_string, PVR_CONNECTION_STATE newState, const char* message);
    void (*epg_event_state_change)(void* kodi_instance, EPG_TAG* tag, unsigned int unique_channel_id, EPG_EVENT_STATE new_state);

    xbmc_codec_t (*get_codec_by_name)(const void* kodi_instance, const char* codec_name);
  } AddonToKodiFuncTable_PVR;

  typedef struct AddonProps_PVR
  {
    const char* user_path;
    const char* client_path;
    int epg_max_days;
  } AddonProps_PVR;

  struct AddonInstance_PVR;
  typedef struct KodiToAddonFuncTable_PVR
  {
    kodi::addon::CInstancePVRClient* addon_instance;

    void (__cdecl* get_capabilities)(const AddonInstance_PVR* instance, PVR_ADDON_CAPABILITIES* capabilities);
    const char* (__cdecl* get_backend_name)(const AddonInstance_PVR* instance);
    const char* (__cdecl* get_backend_version)(const AddonInstance_PVR* instance);
    const char* (__cdecl* get_connection_string)(const AddonInstance_PVR* instance);
    PVR_ERROR (__cdecl* get_drive_space)(const AddonInstance_PVR* instance, long long* total, long long* used);
    PVR_ERROR (__cdecl* menu_hook)(const AddonInstance_PVR* instance, const PVR_MENUHOOK* menuhook, const PVR_MENUHOOK_DATA* item);
    PVR_ERROR (__cdecl* get_epg)(const AddonInstance_PVR* instance, ADDON_HANDLE, const PVR_CHANNEL* channel, time_t start, time_t end);
    int (__cdecl* get_channel_groups_amount)(const AddonInstance_PVR* instance);
    PVR_ERROR (__cdecl* get_channel_groups)(const AddonInstance_PVR* instance, ADDON_HANDLE handle, bool radio);
    PVR_ERROR (__cdecl* get_channel_group_members)(const AddonInstance_PVR* instance, ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* group);
    PVR_ERROR (__cdecl* open_dialog_channel_scan)(const AddonInstance_PVR* instance);
    int (__cdecl* get_channels_amount)(const AddonInstance_PVR* instance);
    PVR_ERROR (__cdecl* get_channels)(const AddonInstance_PVR* instance, ADDON_HANDLE handle, bool radio);
    PVR_ERROR (__cdecl* delete_channel)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    PVR_ERROR (__cdecl* rename_channel)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    PVR_ERROR (__cdecl* move_channel)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    PVR_ERROR (__cdecl* open_dialog_channel_settings)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    PVR_ERROR (__cdecl* open_dialog_channel_add)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    int (__cdecl* get_recordings_amount)(const AddonInstance_PVR* instance, bool deleted);
    PVR_ERROR (__cdecl* get_recordings)(const AddonInstance_PVR* instance, ADDON_HANDLE handle, bool deleted);
    PVR_ERROR (__cdecl* delete_recording)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording);
    PVR_ERROR (__cdecl* undelete_recording)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording);
    PVR_ERROR (__cdecl* delete_all_recordings_from_trash)(const AddonInstance_PVR* instance);
    PVR_ERROR (__cdecl* rename_recording)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording);
    PVR_ERROR (__cdecl* set_recording_lifetime)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording);
    PVR_ERROR (__cdecl* set_recording_play_count)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording, int count);
    PVR_ERROR (__cdecl* set_recording_last_played_position)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording, int last_played_position);
    int (__cdecl* get_recording_last_played_position)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording);
    PVR_ERROR (__cdecl* get_recording_edl)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording, PVR_EDL_ENTRY edl[], int* size);
    PVR_ERROR (__cdecl* get_timer_types)(const AddonInstance_PVR* instance, PVR_TIMER_TYPE types[], int* typesCount);
    int (__cdecl* get_timers_amount)(const AddonInstance_PVR* instance);
    PVR_ERROR (__cdecl* get_timers)(const AddonInstance_PVR* instance, ADDON_HANDLE handle);
    PVR_ERROR (__cdecl* add_timer)(const AddonInstance_PVR* instance, const PVR_TIMER* timer);
    PVR_ERROR (__cdecl* delete_timer)(const AddonInstance_PVR* instance, const PVR_TIMER* timer, bool force_delete);
    PVR_ERROR (__cdecl* update_timer)(const AddonInstance_PVR* instance, const PVR_TIMER* timer);
    bool (__cdecl* open_live_stream)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    void (__cdecl* close_live_stream)(const AddonInstance_PVR* instance);
    int (__cdecl* read_live_stream)(const AddonInstance_PVR* instance, unsigned char* buffer, unsigned int buffer_size);
    long long (__cdecl* seek_live_stream)(const AddonInstance_PVR* instance, long long position, int whence);
    long long (__cdecl* position_live_stream)(const AddonInstance_PVR* instance);
    long long (__cdecl* length_live_stream)(const AddonInstance_PVR* instance);
    bool (__cdecl* switch_channel)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    PVR_ERROR (__cdecl* signal_status)(const AddonInstance_PVR* instance, PVR_SIGNAL_STATUS* signal_status);
    PVR_ERROR (__cdecl* get_descramble_info)(const AddonInstance_PVR* instance, PVR_DESCRAMBLE_INFO* descramble_info);
    const char*  (__cdecl* get_live_stream_url)(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel);
    PVR_ERROR (__cdecl* get_stream_properties)(const AddonInstance_PVR* instance, PVR_STREAM_PROPERTIES* properties);
    bool (__cdecl* open_recorded_stream)(const AddonInstance_PVR* instance, const PVR_RECORDING* recording);
    void (__cdecl* close_recorded_stream)(const AddonInstance_PVR* instance);
    int (__cdecl* read_recorded_stream)(const AddonInstance_PVR* instance, unsigned char* buffer, unsigned int buffer_size);
    long long (__cdecl* seek_recorded_stream)(const AddonInstance_PVR* instance, long long position, int whence);
    long long (__cdecl* position_recorded_stream)(const AddonInstance_PVR* instance);
    long long (__cdecl* length_recorded_stream)(const AddonInstance_PVR* instance);
    void (__cdecl* demux_reset)(const AddonInstance_PVR* instance);
    void (__cdecl* demux_abort)(const AddonInstance_PVR* instance);
    void (__cdecl* demux_flush)(const AddonInstance_PVR* instance);
    DemuxPacket* (__cdecl* demux_read)(const AddonInstance_PVR* instance);
    unsigned int (__cdecl* get_channel_switch_delay)(const AddonInstance_PVR* instance);
    bool (__cdecl* can_pause_stream)(const AddonInstance_PVR* instance);
    void (__cdecl* pause_stream)(const AddonInstance_PVR* instance, bool paused);
    bool (__cdecl* can_seek_stream)(const AddonInstance_PVR* instance);
    bool (__cdecl* seek_time)(const AddonInstance_PVR* instance, double time, bool backwards, double* startpts);
    void (__cdecl* set_speed)(const AddonInstance_PVR* instance, int speed);
    time_t (__cdecl* get_playing_time)(const AddonInstance_PVR* instance);
    time_t (__cdecl* get_buffer_time_start)(const AddonInstance_PVR* instance);
    time_t (__cdecl* get_buffer_time_end)(const AddonInstance_PVR* instance);
    const char* (__cdecl* get_backend_hostname)(const AddonInstance_PVR* instance);
    bool (__cdecl* is_timeshifting)(const AddonInstance_PVR* instance);
    bool (__cdecl* is_real_time_stream)(const AddonInstance_PVR* instance);
    PVR_ERROR (__cdecl* set_epg_time_frame)(const AddonInstance_PVR* instance, int days);
    void (__cdecl* on_system_sleep)(const AddonInstance_PVR* instance);
    void (__cdecl* on_system_wake)(const AddonInstance_PVR* instance);
    void (__cdecl* on_power_saving_activated)(const AddonInstance_PVR* instance);
    void (__cdecl* on_power_saving_deactivated)(const AddonInstance_PVR* instance);
  } KodiToAddonFuncTable_PVR;

  typedef struct AddonInstance_PVR
  {
    AddonProps_PVR props;
    AddonToKodiFuncTable_PVR toKodi;
    KodiToAddonFuncTable_PVR toAddon;
  } AddonInstance_PVR;

#ifdef __cplusplus
}
#endif

namespace kodi {
namespace addon {

  class CInstancePVRClient : public IAddonInstance
  {
  public:
    //==========================================================================
    /// @brief Class constructor
    ///
    /// @param[in] instance             The from Kodi given instance given be
    ///                                 add-on CreateInstance call with instance
    ///                                 id ADDON_INSTANCE_PVR.
    ///
    CInstancePVRClient(KODI_HANDLE instance) : IAddonInstance(ADDON_INSTANCE_PVR)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstancePVRClient: Creation of multiple together with single instance way is not allowed!");

      SetAddonStruct(instance);
    }
    //--------------------------------------------------------------------------

    /// @name PVR add-on methods
    //@{
    //==========================================================================
    ///
    /// @brief Get the list of features that this add-on provides.
    ///
    /// Called by Kodi to query the add-on's capabilities.
    ///
    /// Used to check which options should be presented in the UI, which methods
    /// to call, etc.
    ///
    /// All capabilities that the add-on supports should be set to true. As default
    /// them set from Kodi to false.
    ///
    /// @param[out] capabilities    The add-on's capabilities, see PVR_ADDON_CAPABILITIES
    ///                             for detailed informations.
    ///
    /// @note Valid implementation required.
    ///
    virtual void GetCapabilities(PVR_ADDON_CAPABILITIES& capabilities) = 0;
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief PVR add-ons backend name.
    ///
    /// @return               The name reported by the backend that will be
    ///                       displayed in the UI.
    ///
    /// @note Valid implementation required.
    ///
    virtual std::string GetBackendName() = 0;
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief PVR add-ons client backend version.
    ///
    /// @return               The version string reported by the backend that
    ///                       will be displayed in the UI.
    ///
    /// @note Valid implementation required.
    ///
    virtual std::string GetBackendVersion() = 0;
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get the hostname of the pvr backend server
    ///
    /// @return               hostname as ip address or alias.
    ///
    /// @remarks If backend does not utilize a server ignore this function.
    ///
    virtual std::string GetBackendHostname() { return ""; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief PVR add-ons connection string of client.
    ///
    /// @return               The connection string reported by the backend that
    ///                       will be displayed in the UI.
    ///
    /// @note Valid implementation required.
    ///
    virtual std::string GetConnectionString() = 0;
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get the disk space reported by the backend (if supported).
    ///
    /// @param[in] total      The total disk space in bytes.
    /// @param[in] used       The used disk space in bytes.
    /// @return               \ref PVR_ERROR_NO_ERROR if the drive space has been
    ///                       fetched successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Optional.
    ///
    virtual PVR_ERROR GetDriveSpace(long long& total, long long& used) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Call one of the menu hooks (if supported).
    ///
    /// Supported PVR_MENUHOOK instances have to be added in ADDON_Create(), by
    /// calling AddMenuHook() on the callback.
    ///
    /// @param[in] menuhook   The hook to call.
    /// @param[in] item       The selected item for which the hook was called.
    /// @return               \ref PVR_ERROR_NO_ERROR if the hook was called
    ///                       successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Optional.
    ///
    virtual PVR_ERROR MenuHook(const PVR_MENUHOOK& menuhook, const PVR_MENUHOOK_DATA &item) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR channel group methods
    ///
    /// @remarks Only used by Kodi is bSupportsChannelGroups is set to true.\n
    ///          If a group or one of the group members changes after the initial
    ///          import, or if a new one was added, then the add-on
    ///          should call TriggerChannelGroupsUpdate().
    ///
    //@{

    //==========================================================================
    ///
    /// @brief Get the total amount of channel groups on the backend if it
    /// supports channel groups.
    ///
    /// @return               The amount of channels, or -1 on error.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsChannelGroups is
    /// set to true.
    ///
    virtual int GetChannelGroupsAmount() { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request the list of all channel groups from the backend if it
    /// supports channel groups.
    ///
    /// @param[in] radio      True to get the radio channel groups, false to get
    ///                       the TV channel groups.
    /// @param[out] groups    List to store availanle channel groups withe the
    ///
    /// @return               \ref PVR_ERROR_NO_ERROR if the list has been
    ///                       fetched successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsChannelGroups is
    /// set to true.
    ///
    virtual PVR_ERROR GetChannelGroups(bool radio, std::vector<PVR_CHANNEL_GROUP>& groups) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------


    //==========================================================================
    ///
    /// @brief Request the list of all group members of a group from the backend
    /// if it supports channel groups.
    ///
    /// @param[in] group      The group to get the members for.
    /// @param[out] members   list of all group members of group
    /// @return               \ref PVR_ERROR_NO_ERROR if the list has been
    ///                       fetched successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsChannelGroups is
    /// set to true.
    ///
    virtual PVR_ERROR GetChannelGroupMembers(const PVR_CHANNEL_GROUP& group, std::vector<PVR_CHANNEL_GROUP_MEMBER>& members) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR channel methods
    /// @remarks Either bSupportsTV or bSupportsRadio is required to be set to
    ///          true.\n
    ///          If a channel changes after the initial import, or if a new one
    ///          was added, then the add-on should call TriggerChannelUpdate().
    ///
    //@{

    //==========================================================================
    ///
    /// @brief To get total amount of channels on the backend
    ///
    /// @return               The total amount of channels on the backend, or -1
    ///                       on error.
    ///
    /// @note Valid implementation required.
    ///
    virtual int GetChannelsAmount() = 0;
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request the list of all channels from the backend.
    ///
    /// @param[in] radio      True to get the radio channels, false to get the
    ///                       TV channels.
    /// @param[out] channels  list to add available channls defined with the
    ///                       PVR_CHANNEL structure
    ///
    /// @return               \ref PVR_ERROR_NO_ERROR if the list has been
    ///                       fetched successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks If PVR_ADDON_CAPABILITIES::bSupportsTV is set to true, a valid
    /// result set needs to be provided for radio = false.\n
    /// If PVR_ADDON_CAPABILITIES::bSupportsRadio is set to true, a valid result
    /// set needs to be provided for radio = true.\n
    /// At least one of these two must provide a valid result set.
    ///
    virtual PVR_ERROR GetChannels(bool radio, std::vector<PVR_CHANNEL> &channels) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Delete a channel from the backend.
    ///
    /// @param[in] channel    The channel to delete.
    /// @return               \ref PVR_ERROR_NO_ERROR if the channel has been
    ///                       deleted successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsChannelSettings is
    /// set to true.
    ///
    virtual PVR_ERROR DeleteChannel(const PVR_CHANNEL& channel) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Rename a channel on the backend.
    ///
    /// @param[in] channel    The channel to rename, containing the new channel
    ///                       name.
    /// @return               \ref PVR_ERROR_NO_ERROR if the channel has been
    ///                       renamed successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bSupportsChannelSettings
    /// is set to true.
    ///
    virtual PVR_ERROR RenameChannel(const PVR_CHANNEL& channel) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Move a channel to another channel number on the backend.
    ///
    /// @param[in] channel    The channel to move, containing the new channel
    ///                       number.
    /// @return               \ref PVR_ERROR_NO_ERROR if the channel has been
    ///                       moved successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Optional, and only used if bSupportsChannelSettings is set to
    /// true.
    ///
    virtual PVR_ERROR MoveChannel(const PVR_CHANNEL& channel) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Show the channel scan dialog if this backend supports it.
    ///
    /// @return               \ref PVR_ERROR_NO_ERROR if the dialog was displayed
    ///                       successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsChannelScan is set
    /// to true.
    ///
    /// @note see \ref CPP_kodi_gui "kodi::gui" about related parts
    ///
    virtual PVR_ERROR OpenDialogChannelScan() { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Show the channel settings dialog, if supported by the backend.
    ///
    /// @param[in] channel    The channel to show the dialog for.
    /// @return               \ref PVR_ERROR_NO_ERROR if the dialog has been
    ///                       displayed successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsChannelSettings is
    /// set to true.
    ///
    /// @note see \ref CPP_kodi_gui "kodi::gui" about related parts
    ///
    virtual PVR_ERROR OpenDialogChannelSettings(const PVR_CHANNEL& channel) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Show the dialog to add a channel on the backend, if supported by
    /// the backend.
    ///
    /// @param[in] channel    The channel to add.
    /// @return               \ref PVR_ERROR_NO_ERROR if the channel has been
    ///                       added successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsChannelSettings is
    /// set to true.
    ///
    /// @note see \ref CPP_kodi_gui "kodi::gui" about related parts
    ///
    virtual PVR_ERROR OpenDialogChannelAdd(const PVR_CHANNEL& channel) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR EPG methods
    /// @remarks Only used by Kodi if bSupportsEPG is set to true.
    ///
    //@{

    //==========================================================================
    ///
    /// @brief Request the EPG for a channel from the backend.
    ///
    /// @param[in] channel    The channel to get the EPG table for.
    /// @param[in] start      Get events after this time (UTC).
    /// @param[in] end        Get events before this time (UTC).
    /// @param[out] epg       List where the asked epg's becomes stored
    /// @return               \ref PVR_ERROR_NO_ERROR if the table has been
    ///                       fetched successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsEPG is set to true.
    ///
    virtual PVR_ERROR GetEPG(const PVR_CHANNEL& channel, time_t start, time_t end, std::vector<EPG_TAG>& epg) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Tell the client the time frame to use when notifying epg events
    /// back to Kodi.
    ///
    /// The client might push epg events asynchronously to Kodi using the
    /// callback function EpgEventStateChange. To be able to only push events
    /// that are actually of interest for Kodi, client needs to know about the
    /// epg time frame Kodi uses. Kodi supplies the current epg time frame value
    /// in PVR_PROPERTIES.iEpgMaxDays when creating the addon and calls
    /// SetEPGTimeFrame later whenever Kodi's epg time frame value changes.
    ///
    /// @param[in] days       number of days from "now". EPG_TIMEFRAME_UNLIMITED
    ///                       means that Kodi is interested in all epg events,
    ///                       regardless of event times.
    /// @return               \ref PVR_ERROR_NO_ERROR if new value was successfully
    ///                       set. See \ref PVR_ERROR for all possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsEPG is set to true.
    ///
    virtual PVR_ERROR SetEPGTimeFrame(int days) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR recording methods
    ///  @remarks Only used by Kodi is bSupportsRecordings is set to true.
    ///           If a recording changes after the initial import, or if a new one was added,
    ///           then the add-on should call TriggerRecordingUpdate()
    ///
    //@{

    //==========================================================================
    ///
    /// @brief To get the amount of usable or deleted recordings.
    ///
    /// @param[in] deleted    if set return deleted recording (called if
    ///                       PVR_ADDON_CAPABILITIES::bSupportsRecordingsUndelete
    ///                       set to true)
    /// @return               The total amount of recordings on the backend or
    ///                       -1 on error.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual int GetRecordingsAmount(bool deleted) { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request the list of all recordings from the backend, if supported.
    ///
    /// Recording entries are added to Kodi by insert them to vector recording.
    ///
    /// @param[in] deleted    if set return deleted recording (called if
    ///                       PVR_ADDON_CAPABILITIES::bSupportsRecordingsUndelete
    ///                       set to true)
    /// @param[out] recording the vector list where available recordings becomes
    ///                       inserted with the PVR_RECORDING structure.
    /// @return               \ref PVR_ERROR_NO_ERROR if the recordings have been
    ///                       fetched successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual PVR_ERROR GetRecordings(bool deleted, std::vector<PVR_RECORDING>& recording) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Delete a recording on the backend.
    ///
    /// @param[in] recording  The recording to delete.
    /// @return               \ref PVR_ERROR_NO_ERROR if the recording has been
    ///                       deleted successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual PVR_ERROR DeleteRecording(const PVR_RECORDING& recording) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Undelete a recording on the backend.
    ///
    /// @param[in] recording  The recording to undelete.
    /// @return               \ref PVR_ERROR_NO_ERROR if the recording has been
    ///                       undeleted successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual PVR_ERROR UndeleteRecording(const PVR_RECORDING& recording) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Delete all recordings permanent which in the deleted folder on
    /// the backend.
    ///
    /// @return               \ref PVR_ERROR_NO_ERROR if the recordings has been
    ///                       deleted successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordingsUndelete
    /// is set to true.
    ///
    virtual PVR_ERROR DeleteAllRecordingsFromTrash() { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Rename a recording on the backend.
    ///
    /// @param[in] recording  The recording to rename, containing the new name.
    /// @return               \ref PVR_ERROR_NO_ERROR if the recording has been
    ///                       renamed successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual PVR_ERROR RenameRecording(const PVR_RECORDING& recording) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Set the lifetime of a recording on the backend.
    ///
    /// @param[in] recording The recording to change the lifetime for
    ///                      recording.iLifetime contains the new lieftime
    ///                      value.
    /// @return PVR_ERROR_NO_ERROR if the recording's lifetime has been set successfully.
    ///
    /// @remarks Required if bSupportsRecordingsLifetimeChange is set to true.
    /// Return PVR_ERROR_NOT_IMPLEMENTED if this add-on won't provide this function.
    ///
    virtual PVR_ERROR SetRecordingLifetime(const PVR_RECORDING& recording) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Set the play count of a recording on the backend.
    ///
    /// @param[in] recording  The recording to change the play count.
    /// @param[in] count      Play count.
    /// @return               \ref PVR_ERROR_NO_ERROR if the recording's play count
    ///                       has been set successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual PVR_ERROR SetRecordingPlayCount(const PVR_RECORDING& recording, int count) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Set the last watched position of a recording on the backend.
    ///
    /// @param[in] recording  The recording.
    /// @param[in] position   The last watched position in seconds
    /// @return               \ref PVR_ERROR_NO_ERROR if the position has been
    ///                       stored successfully. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual PVR_ERROR SetRecordingLastPlayedPosition(const PVR_RECORDING& recording, int lastplayedposition) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Retrieve the last watched position of a recording on the backend.
    ///
    /// @param[in] recording  The recording.
    /// @return               The last watched position in seconds or -1 on
    ///                       error
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true.
    ///
    virtual int GetRecordingLastPlayedPosition(const PVR_RECORDING& recording) { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Retrieve the edit decision list (EDL) of a recording on the
    /// backend.
    ///
    /// @param[in] recording  The recording.
    /// @param[out] edl       The function has to write the EDL list (defined as
    ///                       struct PVR_EDL_ENTRY) into this array.
    /// @return               \ref PVR_ERROR_NO_ERROR if the EDL was successfully
    ///                       read. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsRecordings is set
    /// to true. Return PVR_ERROR_NOT_IMPLEMENTED if this add-on won't provide
    /// this function.
    ///
    virtual PVR_ERROR GetRecordingEdl(const PVR_RECORDING&, std::vector<PVR_EDL_ENTRY> &edl) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR timer methods
    ///  @remarks Only used by Kodi is bSupportsTimers is set to true.
    ///           If a timer changes after the initial import, or if a new one was added,
    ///           then the add-on should call TriggerTimerUpdate()
    ///
    //@{

    //==========================================================================
    ///
    /// @brief Retrieve the timer types supported by the backend.
    ///
    /// @param types[out]     The function has to write the definition of the
    ///                       supported timer types into this array.
    /// @return               \ref PVR_ERROR_NO_ERROR if the types were successfully
    ///                       written to the array. See \ref PVR_ERROR for all
    ///                       possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsTimers is set to true.
    ///
    virtual PVR_ERROR GetTimerTypes(std::vector<PVR_TIMER_TYPE>& types) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief To get the complete amount of timers present on backend.
    ///
    /// @return                 The total amount of timers on the backend or -1
    ///                         on error.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsTimers is set to true.
    ///
    virtual int GetTimersAmount() { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request the list of all timers from the backend if supported.
    ///
    /// @param timers[out]      Vector list to store available timers defined
    ///                         with PVR_TIMER
    /// @return                 \ref PVR_ERROR_NO_ERROR if the list has been
    ///                         fetched successfully. See \ref PVR_ERROR for all
    ///                         possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsTimers is set to
    /// true.
    ///
    virtual PVR_ERROR GetTimers(std::vector<PVR_TIMER>& timers) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Add a timer on the backend.
    ///
    /// @param[in] timer        The timer to add.
    /// @return                 \ref PVR_ERROR_NO_ERROR if the timer has been
    ///                         added successfully. See \ref PVR_ERROR for all
    ///                         possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsTimers is set to
    /// true.
    ///
    virtual PVR_ERROR AddTimer(const PVR_TIMER& timer) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Delete a timer on the backend.
    ///
    /// @param[in] timer        The timer to delete.
    /// @param[in] forceDelete  Set to true to delete a timer that is currently
    ///                         recording a program.
    /// @return                 \ref PVR_ERROR_NO_ERROR if the timer has been
    ///                         deleted successfully. See \ref PVR_ERROR for all
    ///                         possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsTimers is set to
    /// true.
    ///
    virtual PVR_ERROR DeleteTimer(const PVR_TIMER& timer, bool forceDelete) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Update the timer information on the backend.
    ///
    /// @param[in] timer        The timer to update.
    /// @return                 \ref PVR_ERROR_NO_ERROR if the timer has been
    ///                         updated successfully. See \ref PVR_ERROR for all
    ///                         possible values.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bSupportsTimers is set to
    /// true.
    ///
    virtual PVR_ERROR UpdateTimer(const PVR_TIMER& timer) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR live stream methods, used to open and close a stream to a channel, and optionally perform read operations on the stream
    //@{
    //==========================================================================
    ///
    /// @brief Open a live stream on the backend.
    ///
    /// @param[in] channel      The channel to stream.
    /// @return                 True if the stream has been opened successfully,
    ///                         false otherwise.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesInputStream or
    /// PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to true.
    ///
    virtual bool OpenLiveStream(const PVR_CHANNEL& channel) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Close an open live stream.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesInputStream or
    /// PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to true.
    ///
    virtual void CloseLiveStream() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Read from an open live stream.
    ///
    /// @param[out] buffer      The buffer to store the data in.
    /// @param[in] bufferSize   The amount of bytes to read.
    /// @return                 The amount of bytes that were actually read from
    ///                         the stream.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesInputStream is set
    /// to true.
    ///
    virtual int ReadLiveStream(unsigned char* buffer, unsigned int bufferSize) { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Seek in a live stream on a backend that supports timeshifting.
    ///
    /// @param[in] position   The position to seek to.
    /// @param[in] whence     [optional] offset relative to
    ///                       You can set the value of whence to one of three
    ///                       things:
    ///  |   Value  | int | Description                                        |
    ///  |:--------:|:---:|:---------------------------------------------------|
    ///  | SEEK_SET |  0  | position is relative to the beginning of the file. This is probably what you had in mind anyway, and is the most commonly used value for whence.
    ///  | SEEK_CUR |  1  | position is relative to the current file pointer position. So, in effect, you can say, "Move to my current position plus 30 bytes," or, "move to my current position minus 20 bytes."
    ///  | SEEK_END |  2  | position is relative to the end of the file. Just like SEEK_SET except from the other end of the file. Be sure to use negative values for offset if you want to back up from the end of the file, instead of going past the end into oblivion.
    /// @return                         Returns the resulting offset location as
    ///                                 measured in bytes from the beginning of
    ///                                 the stream. On error, the value -1 is
    ///                                 returned.
    ///

    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bHandlesInputStream
    /// is set to true.
    ///
    virtual long long SeekLiveStream(long long position, int whence = SEEK_SET) { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief To get position in the stream that's currently being read.
    ///
    /// @return                 The position in the stream that's currently
    ///                         being read.
    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bHandlesInputStream
    /// is set to true.
    ///
    virtual long long PositionLiveStream() { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief To get total length of the stream that's currently being read.
    ///
    /// @return                 The total length of the stream that's currently
    ///                         being read.
    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bHandlesInputStream
    /// is set to true.
    ///
    virtual long long LengthLiveStream() { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Switch to another channel. Only to be called when a live stream
    /// has already been opened.
    ///
    /// @param[in] channel      The channel to switch to.
    /// @return                 True if the switch was successful, false
    ///                         otherwise.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesInputStream or
    /// PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to true.
    ///
    virtual bool SwitchChannel(const PVR_CHANNEL& channel) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Delay to use when using switching channels for add-ons not
    /// providing an input stream.
    ///
    /// If the add-on does provide an input stream, then this method will not be
    /// called.
    ///
    /// Those add-ons can do that in OpenLiveStream() if needed.
    ///
    /// @return                 The delay in milliseconds.
    ///
    virtual unsigned int GetChannelSwitchDelay() { return 0; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get the signal status of the stream that's currently open.
    ///
    /// @param[out] signalStatus        The signal status.
    /// @return                         True if the signal status has been read
    ///                                 successfully, false otherwise.
    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bHandlesInputStream
    /// or PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to true.
    ///
    virtual PVR_ERROR SignalStatus(PVR_SIGNAL_STATUS& signalStatus) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// Get the descramble information of the stream that's currently open.
    ///
    /// @param[out] descrambleInfo The descramble information.
    /// @return True if the decramble information has been read successfully,
    /// false otherwise.
    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bSupportsDescrambleInfo
    /// is set to true. Return PVR_ERROR_NOT_IMPLEMENTED if this add-on won't
    /// provide this function.
    ///
    virtual PVR_ERROR GetDescrambleInfo(PVR_DESCRAMBLE_INFO& descrambleInfo) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get the stream URL for a channel from the backend. Used by the
    /// MediaPortal add-on.
    ///
    /// @param[out] channel     The channel to get the stream URL for.
    /// @return                 The requested URL.
    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bHandlesInputStream
    /// is set to true.
    ///
    virtual std::string GetLiveStreamURL(const PVR_CHANNEL& channel) { return ""; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get the stream properties of the stream that's currently being
    /// read.
    ///
    /// @param[out] properties  The properties of the currently playing stream.
    /// @return                 \ref PVR_ERROR_NO_ERROR if the properties have
    ///                         been fetched successfully. See \ref PVR_ERROR
    ///                         for all possible values.
    ///
    /// @remarks Optional, and only used if PVR_ADDON_CAPABILITIES::bHandlesInputStream
    /// or PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to true.
    ///
    virtual PVR_ERROR GetStreamProperties(PVR_STREAM_PROPERTIES& properties) { return PVR_ERROR_NOT_IMPLEMENTED; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR recording stream methods, used to open and close a stream to a
    /// recording, and perform read operations on the stream.
    ///
    /// @remarks This will only be used if the backend doesn't provide a direct
    /// URL in the recording tag.
    ///
    //@{

    //==========================================================================
    ///
    /// @brief Open a stream to a recording on the backend.
    ///
    /// @param[in] recording    The recording to open.
    /// @return                 True if the stream has been opened successfully,
    ///                         false otherwise.
    ///
    /// @remarks Optional, and only used if
    /// PVR_ADDON_CAPABILITIES::bSupportsRecordings is set to true.
    ///
    virtual bool OpenRecordedStream(const PVR_RECORDING& recording) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Close an open stream from a recording.
    ///
    /// @remarks Optional, and only used if
    /// PVR_ADDON_CAPABILITIES::bSupportsRecordings is set to true.
    ///
    virtual void CloseRecordedStream() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Read from a recording.
    ///
    /// @param[out] buffer      The buffer to store the data in.
    /// @param[in] bufferSize   The amount of bytes to read.
    /// @return                 The amount of bytes that were actually read from
    ///                         the stream.
    ///
    /// @remarks Optional, and only used if
    /// PVR_ADDON_CAPABILITIES::bSupportsRecordings is set to true,
    /// but required if OpenRecordedStream() is implemented.
    ///
    virtual int ReadRecordedStream(unsigned char* buffer, unsigned int bufferSize) { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Seek in a recorded stream.
    ///
    /// @param[in] position     The position to seek to.
    /// @param[in] whence       ?
    /// @return                 The new position.
    ///
    /// @remarks Optional, and only used if
    /// PVR_ADDON_CAPABILITIES::bSupportsRecordings is set to true.
    ///
    virtual long long SeekRecordedStream(long long position, int whence = SEEK_SET) { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief To get position in the stream that's currently being read.
    ///
    /// @return                 The position in the stream that's currently
    ///                         being read.
    ///
    /// @remarks Optional, and only used if
    /// PVR_ADDON_CAPABILITIES::bSupportsRecordings is set to true.
    ///
    virtual long long PositionRecordedStream() { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief To get total length of the stream that's currently being read
    ///
    /// @return                 The total length of the stream that's currently
    ///                         being read.
    ///
    /// @remarks Optional, and only used if
    /// PVR_ADDON_CAPABILITIES::bSupportsRecordings is set to true.
    ///
    virtual long long LengthRecordedStream() { return -1; }
    //--------------------------------------------------------------------------
    //@}

    /// @name PVR demultiplexer methods
    ///
    /// @remarks Only used by Kodi is bHandlesDemuxing is set to true.
    ///
    //@{

    //==========================================================================
    ///
    /// @brief Reset the demultiplexer in the add-on.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to
    /// true.
    ///
    virtual void DemuxReset() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Abort the demultiplexer thread in the add-on.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to
    /// true.
    ///
    virtual void DemuxAbort() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Flush all data that's currently in the demultiplexer buffer in
    /// the add-on.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to
    /// true.
    ///
    virtual void DemuxFlush() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Read the next packet from the demultiplexer, if there is one.
    ///
    /// @return The next packet.\n
    ///         If there is no next packet, then the add-on should return the
    ///         packet created by calling AllocateDemuxPacket(0) on the callback.
    ///         If the stream changed and Kodi's player needs to be reinitialised,
    ///         then, the add-on should call AllocateDemuxPacket(0) on the
    ///         callback, and set the streamid to DMX_SPECIALID_STREAMCHANGE and
    ///         return the value.\n
    ///         The add-on should return nullptr if an error occured.
    ///
    /// @remarks Required if PVR_ADDON_CAPABILITIES::bHandlesDemuxing is set to
    /// true.
    ///
    virtual DemuxPacket* DemuxRead() { return nullptr; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Free a packet that was allocated with AllocateDemuxPacket
    ///
    /// @param[in] packet              The packet to free
    ///
    void FreeDemuxPacket(DemuxPacket* packet)
    {
      return m_instanceData->toKodi.free_demux_packet(m_instanceData->toKodi.kodi_instance, packet);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Allocate a demux packet. Free with FreeDemuxPacket
    ///
    /// @param[in] datasize             The size of the data that will go into
    ///                                 the packet
    /// @return                         The allocated packet
    ///
    DemuxPacket* AllocateDemuxPacket(int datasize)
    {
      return m_instanceData->toKodi.allocate_demux_packet(m_instanceData->toKodi.kodi_instance, datasize);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    /// @brief Get the codec ID by the name
    ///
    /// @param[in] codecName A on ffmpeg defined codec name
    /// @return codec identifier
    ///
    inline xbmc_codec_t GetCodecByName(const std::string& codecName)
    {
      return m_instanceData->toKodi.get_codec_by_name(m_instanceData->toKodi.kodi_instance, codecName.c_str());
    }
    //--------------------------------------------------------------------------
    //@}

    //==========================================================================
    ///
    /// @brief Check if the backend support pausing the currently playing stream
    ///
    /// This will enable/disable the pause button in Kodi based on the return
    /// value
    ///
    /// @return               false if the PVR addon/backend does not support
    ///                       pausing, true if possible
    ///
    virtual bool CanPauseStream() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Check if the backend supports seeking for the currently playing
    /// stream
    ///
    /// This will enable/disable the rewind/forward buttons in Kodi based on the
    /// return value
    ///
    /// @return               false if the PVR addon/backend does not support
    ///                       seeking, true if possible
    ///
    virtual bool CanSeekStream() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify the pvr addon that Kodi (un)paused the currently playing
    /// stream
    ///
    /// @param[in] paused     true if stream is paused otherwise false
    ///
    virtual void PauseStream(bool paused) { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify the pvr addon/demuxer that Kodi wishes to seek the stream
    /// by time
    ///
    /// @param[in] time       The absolute time since stream start
    /// @param[in] backwards  True to seek to keyframe BEFORE time, else AFTER
    /// @param[out] startpts  can be updated to point to where display should
    ///                       start
    /// @return               True if the seek operation was possible
    ///
    /// @remarks Optional, and only used if addon has its own demuxer.
    ///
    virtual bool SeekTime(double time, bool backwards, double &startpts) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify the pvr addon/demuxer that Kodi wishes to change playback
    /// speed
    ///
    /// @param[in] speed        The requested playback speed
    ///
    /// @remarks Optional, and only used if addon has its own demuxer.
    ///
    virtual void SetSpeed(int speed) { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get actual playing time from addon.
    ///
    /// With timeshift enabled this is different to live.
    ///
    /// @return time as UTC
    ///
    virtual time_t GetPlayingTime() { return 0; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get time of oldest packet in timeshift buffer
    ///
    /// @return time as UTC
    ///
    virtual time_t GetBufferTimeStart() { return 0; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Get time of latest packet in timeshift buffer
    ///
    /// @return time as UTC
    ///
    virtual time_t GetBufferTimeEnd() { return 0; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Check if timeshift is active
    ///
    /// @return true if timeshift is active
    ///
    virtual bool IsTimeshifting() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Check for real-time streaming
    ///
    /// @return true if current stream is real-time
    ///
    virtual bool IsRealTimeStream() { return true; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify the pvr addon for power management events
    ///
    virtual void OnSystemSleep() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify the pvr addon about a system wake event.
    ///
    virtual void OnSystemWake() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify the pvr addon that power saving becomes activated.
    ///
    virtual void OnPowerSavingActivated() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify the pvr addon about power saving becomes deactivated.
    ///
    virtual void OnPowerSavingDeactivated() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Add or replace a menu hook for the context menu for this add-on
    ///
    /// @param[in] hook                 The hook to add
    ///
    void AddMenuHook(const PVR_MENUHOOK& hook)
    {
      return m_instanceData->toKodi.add_menu_hook(m_instanceData->toKodi.kodi_instance, &hook);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Display a notification in Kodi that a recording started or stopped on the server
    ///
    /// @param[in] recordingname        The name of the recording to display
    /// @param[in] filename             The filename of the recording
    /// @param[in] on                   True when recording started, false when
    ///                                 it stopped
    ///
    void Recording(std::string recordingname, std::string filename, bool on)
    {
      return m_instanceData->toKodi.recording(m_instanceData->toKodi.kodi_instance, recordingname.c_str(), filename.c_str(), on);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request Kodi to update it's list of timers
    ///
    void TriggerTimerUpdate(void)
    {
      return m_instanceData->toKodi.trigger_timer_update(m_instanceData->toKodi.kodi_instance);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request Kodi to update it's list of recordings
    ///
    void TriggerRecordingUpdate(void)
    {
      return m_instanceData->toKodi.trigger_recording_update(m_instanceData->toKodi.kodi_instance);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request Kodi to update it's list of channels
    ///
    void TriggerChannelUpdate(void)
    {
      return m_instanceData->toKodi.trigger_channel_groups_update(m_instanceData->toKodi.kodi_instance);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Schedule an EPG update for the given channel channel
    ///
    /// @param[in] channelUid           The unique id of the channel for this
    ///                                 add-on
    ///
    void TriggerEpgUpdate(unsigned int channelUid)
    {
      return m_instanceData->toKodi.trigger_epg_update(m_instanceData->toKodi.kodi_instance, channelUid);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Request Kodi to update it's list of channel groups
    ///
    void TriggerChannelGroupsUpdate(void)
    {
      return m_instanceData->toKodi.trigger_channel_groups_update(m_instanceData->toKodi.kodi_instance);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify a state change for a PVR backend connection
    ///
    /// @param[in] connectionString     The connection string reported by the
    ///                                 backend that can be displayed in the UI.
    /// @param[in] newState             The new state.
    /// @param[in] message              A localized addon-defined string
    ///                                 representing the new state, that can be
    ///                                 displayed in the UI or NULL if the
    ///                                 Kodi-defined default string for the new
    ///                                 state shall be displayed.
    ///
    void ConnectionStateChange(std::string connectionString, PVR_CONNECTION_STATE newState, std::string message)
    {
      return m_instanceData->toKodi.connection_state_change(m_instanceData->toKodi.kodi_instance, connectionString.c_str(), newState, message.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief Notify a state change for an EPG event
    ///
    /// @param[in] tag                  The EPG event.
    /// @param[in] uniqueChannelId      The unique id of the channel for the EPG
    ///                                 event
    /// @param[in] newState             The new state. For EPG_EVENT_CREATED and
    ///                                 EPG_EVENT_UPDATED, tag must be filled
    ///                                 with all available event data, not just
    ///                                 a delta. For EPG_EVENT_DELETED, it is
    ///                                 sufficient to fill
    ///                                 EPG_TAG.iUniqueBroadcastId
    ///
    void EpgEventStateChange(EPG_TAG *tag, unsigned int uniqueChannelId, EPG_EVENT_STATE newState)
    {
      return m_instanceData->toKodi.epg_event_state_change(m_instanceData->toKodi.kodi_instance, tag, uniqueChannelId, newState);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    /// @brief path to the user profile
    ///
    inline std::string UserPath() { return m_instanceData->props.user_path; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @brief path to this add-on
    ///
    inline std::string ClientPath() { return m_instanceData->props.client_path; }
    //--------------------------------------------------------------------------

    //==========================================================================
    /// @brief Maximal used days for EPG on Kodi
    ///
    /// if > EPG_TIMEFRAME_UNLIMITED, in async epg mode, deliver only events in
    /// the range from 'end time > now' to 'start time < now + iEpgMaxDays.
    /// EPG_TIMEFRAME_UNLIMITED, notify all events.
    ///
    /// @return the amount of used days for EPG
    ///
    inline int EpgMaxDays() { return m_instanceData->props.epg_max_days; }
    //--------------------------------------------------------------------------

  private:
    void SetAddonStruct(KODI_HANDLE instance)
    {
      if (instance == nullptr)
        throw std::logic_error("kodi::addon::CInstancePVRClient: Creation with empty addon structure not allowed, table must be given from Kodi!");

      m_instanceData = static_cast<AddonInstance_PVR*>(instance);
      m_instanceData->toAddon.addon_instance = this;
      m_instanceData->toAddon.get_capabilities = ADDON_GetCapabilities;
      m_instanceData->toAddon.get_stream_properties = ADDON_GetStreamProperties;
      m_instanceData->toAddon.get_backend_name = ADDON_GetBackendName;
      m_instanceData->toAddon.get_backend_version = ADDON_GetBackendVersion;
      m_instanceData->toAddon.get_connection_string = ADDON_GetConnectionString;
      m_instanceData->toAddon.get_drive_space = ADDON_GetDriveSpace;
      m_instanceData->toAddon.menu_hook = ADDON_MenuHook;
      m_instanceData->toAddon.get_epg = ADDON_GetEPG;
      m_instanceData->toAddon.get_channel_groups_amount = ADDON_GetChannelGroupsAmount;
      m_instanceData->toAddon.get_channel_groups = ADDON_GetChannelGroups;
      m_instanceData->toAddon.get_channel_group_members = ADDON_GetChannelGroupMembers;
      m_instanceData->toAddon.open_dialog_channel_scan = ADDON_OpenDialogChannelScan;
      m_instanceData->toAddon.get_channels_amount = ADDON_GetChannelsAmount;
      m_instanceData->toAddon.get_channels = ADDON_GetChannels;
      m_instanceData->toAddon.delete_channel = ADDON_DeleteChannel;
      m_instanceData->toAddon.rename_channel = ADDON_RenameChannel;
      m_instanceData->toAddon.move_channel = ADDON_MoveChannel;
      m_instanceData->toAddon.open_dialog_channel_settings = ADDON_OpenDialogChannelSettings;
      m_instanceData->toAddon.open_dialog_channel_add = ADDON_OpenDialogChannelAdd;
      m_instanceData->toAddon.get_recordings_amount = ADDON_GetRecordingsAmount;
      m_instanceData->toAddon.get_recordings = ADDON_GetRecordings;
      m_instanceData->toAddon.delete_recording = ADDON_DeleteRecording;
      m_instanceData->toAddon.undelete_recording = ADDON_UndeleteRecording;
      m_instanceData->toAddon.delete_all_recordings_from_trash = ADDON_DeleteAllRecordingsFromTrash;
      m_instanceData->toAddon.rename_recording = ADDON_RenameRecording;
      m_instanceData->toAddon.set_recording_lifetime = ADDON_SetRecordingLifetime;
      m_instanceData->toAddon.set_recording_play_count = ADDON_SetRecordingPlayCount;
      m_instanceData->toAddon.set_recording_last_played_position = ADDON_SetRecordingLastPlayedPosition;
      m_instanceData->toAddon.get_recording_last_played_position = ADDON_GetRecordingLastPlayedPosition;
      m_instanceData->toAddon.get_recording_edl = ADDON_GetRecordingEdl;
      m_instanceData->toAddon.get_timer_types = ADDON_GetTimerTypes;
      m_instanceData->toAddon.get_timers_amount = ADDON_GetTimersAmount;
      m_instanceData->toAddon.get_timers = ADDON_GetTimers;
      m_instanceData->toAddon.add_timer = ADDON_AddTimer;
      m_instanceData->toAddon.delete_timer = ADDON_DeleteTimer;
      m_instanceData->toAddon.update_timer = ADDON_UpdateTimer;
      m_instanceData->toAddon.open_live_stream = ADDON_OpenLiveStream;
      m_instanceData->toAddon.close_live_stream = ADDON_CloseLiveStream;
      m_instanceData->toAddon.read_live_stream = ADDON_ReadLiveStream;
      m_instanceData->toAddon.seek_live_stream = ADDON_SeekLiveStream;
      m_instanceData->toAddon.position_live_stream = ADDON_PositionLiveStream;
      m_instanceData->toAddon.length_live_stream = ADDON_LengthLiveStream;
      m_instanceData->toAddon.switch_channel = ADDON_SwitchChannel;
      m_instanceData->toAddon.signal_status = ADDON_SignalStatus;
      m_instanceData->toAddon.get_descramble_info = ADDON_GetDescrambleInfo;
      m_instanceData->toAddon.get_live_stream_url = ADDON_GetLiveStreamURL;
      m_instanceData->toAddon.open_recorded_stream = ADDON_OpenRecordedStream;
      m_instanceData->toAddon.close_recorded_stream = ADDON_CloseRecordedStream;
      m_instanceData->toAddon.read_recorded_stream = ADDON_ReadRecordedStream;
      m_instanceData->toAddon.seek_recorded_stream = ADDON_SeekRecordedStream;
      m_instanceData->toAddon.position_recorded_stream = ADDON_PositionRecordedStream;
      m_instanceData->toAddon.length_recorded_stream = ADDON_LengthRecordedStream;
      m_instanceData->toAddon.demux_reset = ADDON_DemuxReset;
      m_instanceData->toAddon.demux_abort = ADDON_DemuxAbort;
      m_instanceData->toAddon.demux_flush = ADDON_DemuxFlush;
      m_instanceData->toAddon.demux_read = ADDON_DemuxRead;
      m_instanceData->toAddon.get_channel_switch_delay = ADDON_GetChannelSwitchDelay;
      m_instanceData->toAddon.can_pause_stream = ADDON_CanPauseStream;
      m_instanceData->toAddon.pause_stream = ADDON_PauseStream;
      m_instanceData->toAddon.can_seek_stream = ADDON_CanSeekStream;
      m_instanceData->toAddon.seek_time = ADDON_SeekTime;
      m_instanceData->toAddon.set_speed = ADDON_SetSpeed;
      m_instanceData->toAddon.get_playing_time = ADDON_GetPlayingTime;
      m_instanceData->toAddon.get_buffer_time_start = ADDON_GetBufferTimeStart;
      m_instanceData->toAddon.get_buffer_time_end = ADDON_GetBufferTimeEnd;
      m_instanceData->toAddon.get_backend_hostname = ADDON_GetBackendHostname;
      m_instanceData->toAddon.is_timeshifting = ADDON_IsTimeshifting;
      m_instanceData->toAddon.is_real_time_stream = ADDON_IsRealTimeStream;
      m_instanceData->toAddon.set_epg_time_frame = ADDON_SetEPGTimeFrame;
      m_instanceData->toAddon.on_system_sleep = ADDON_OnSystemSleep;
      m_instanceData->toAddon.on_system_wake = ADDON_OnSystemWake;
      m_instanceData->toAddon.on_power_saving_activated = ADDON_OnPowerSavingActivated;
      m_instanceData->toAddon.on_power_saving_deactivated = ADDON_OnPowerSavingDeactivated;
    }

    static inline void ADDON_GetCapabilities(const AddonInstance_PVR* instance, PVR_ADDON_CAPABILITIES *capabilities)
    {
      instance->toAddon.addon_instance->GetCapabilities(*capabilities);
    }

    static inline const char* ADDON_GetBackendName(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->m_backendName = instance->toAddon.addon_instance->GetBackendName();
      return instance->toAddon.addon_instance->m_backendName.c_str();
    }

    static inline const char* ADDON_GetBackendVersion(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->m_backendVersion = instance->toAddon.addon_instance->GetBackendVersion();
      return instance->toAddon.addon_instance->m_backendVersion.c_str();
    }

    static inline const char* ADDON_GetConnectionString(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->m_connectionString = instance->toAddon.addon_instance->GetConnectionString();
      return instance->toAddon.addon_instance->m_connectionString.c_str();
    }

    static inline PVR_ERROR ADDON_GetDriveSpace(const AddonInstance_PVR* instance, long long* total, long long* used)
    {
      return instance->toAddon.addon_instance->GetDriveSpace(*total, *used);
    }

    static inline PVR_ERROR ADDON_MenuHook(const AddonInstance_PVR* instance, const PVR_MENUHOOK* menuhook, const PVR_MENUHOOK_DATA* item)
    {
      return instance->toAddon.addon_instance->MenuHook(*menuhook, *item);
    }

    static inline int ADDON_GetChannelGroupsAmount(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->GetChannelGroupsAmount();
    }

    static inline PVR_ERROR ADDON_GetChannelGroups(const AddonInstance_PVR* instance, ADDON_HANDLE handle, bool radio)
    {
      std::vector<PVR_CHANNEL_GROUP> group;
      PVR_ERROR error = instance->toAddon.addon_instance->GetChannelGroups(radio, group);
      for (auto iter : group)
        instance->toAddon.addon_instance->m_instanceData->toKodi.transfer_channel_group(instance->toKodi.kodi_instance, handle, &iter);
      return error;
    }

    static inline PVR_ERROR ADDON_GetChannelGroupMembers(const AddonInstance_PVR* instance, ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* group)
    {
      std::vector<PVR_CHANNEL_GROUP_MEMBER> members;
      PVR_ERROR error = instance->toAddon.addon_instance->GetChannelGroupMembers(*group, members);
      for (auto iter : members)
        instance->toAddon.addon_instance->m_instanceData->toKodi.transfer_channel_group_member(instance->toKodi.kodi_instance, handle, &iter);
      return error;
    }

    static inline int ADDON_GetChannelsAmount(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->GetChannelsAmount();
    }

    static inline PVR_ERROR ADDON_GetChannels(const AddonInstance_PVR* instance, ADDON_HANDLE handle, bool radio)
    {
      std::vector<PVR_CHANNEL> channels;
      PVR_ERROR error = instance->toAddon.addon_instance->GetChannels(radio, channels);
      for (auto iter : channels)
        instance->toAddon.addon_instance->m_instanceData->toKodi.transfer_channel_entry(instance->toKodi.kodi_instance, handle, &iter);
      return error;
    }

    static inline PVR_ERROR ADDON_DeleteChannel(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      return instance->toAddon.addon_instance->DeleteChannel(*channel);
    }

    static inline PVR_ERROR ADDON_RenameChannel(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      return instance->toAddon.addon_instance->RenameChannel(*channel);
    }

    static inline PVR_ERROR ADDON_MoveChannel(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      return instance->toAddon.addon_instance->MoveChannel(*channel);
    }

    static inline PVR_ERROR ADDON_OpenDialogChannelScan(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->OpenDialogChannelScan();
    }

    static inline PVR_ERROR ADDON_OpenDialogChannelSettings(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      return instance->toAddon.addon_instance->OpenDialogChannelSettings(*channel);
    }

    static inline PVR_ERROR ADDON_OpenDialogChannelAdd(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      return instance->toAddon.addon_instance->OpenDialogChannelAdd(*channel);
    }

    static inline PVR_ERROR ADDON_GetEPG(const AddonInstance_PVR* instance, ADDON_HANDLE handle, const PVR_CHANNEL* channel, time_t start, time_t end)
    {
      std::vector<EPG_TAG> epg;
      PVR_ERROR error = instance->toAddon.addon_instance->GetEPG(*channel, start, end, epg);
      for (auto iter : epg)
        instance->toAddon.addon_instance->m_instanceData->toKodi.transfer_epg_entry(instance->toKodi.kodi_instance, handle, &iter);
      return error;
    }

    static inline PVR_ERROR ADDON_SetEPGTimeFrame(const AddonInstance_PVR* instance, int days)
    {
      return instance->toAddon.addon_instance->SetEPGTimeFrame(days);
    }

    static inline int ADDON_GetRecordingsAmount(const AddonInstance_PVR* instance, bool deleted)
    {
      return instance->toAddon.addon_instance->GetRecordingsAmount(deleted);
    }

    static inline PVR_ERROR ADDON_GetRecordings(const AddonInstance_PVR* instance, ADDON_HANDLE handle, bool deleted)
    {
      std::vector<PVR_RECORDING> recording;
      PVR_ERROR error = instance->toAddon.addon_instance->GetRecordings(deleted, recording);
      for (auto iter : recording)
        instance->toAddon.addon_instance->m_instanceData->toKodi.transfer_recording_entry(instance->toKodi.kodi_instance, handle, &iter);
      return error;
    }

    static inline PVR_ERROR ADDON_DeleteRecording(const AddonInstance_PVR* instance, const PVR_RECORDING* recording)
    {
      return instance->toAddon.addon_instance->DeleteRecording(*recording);
    }

    static inline PVR_ERROR ADDON_UndeleteRecording(const AddonInstance_PVR* instance, const PVR_RECORDING* recording)
    {
      return instance->toAddon.addon_instance->UndeleteRecording(*recording);
    }

    static inline PVR_ERROR ADDON_DeleteAllRecordingsFromTrash(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->DeleteAllRecordingsFromTrash();
    }

    static inline PVR_ERROR ADDON_RenameRecording(const AddonInstance_PVR* instance, const PVR_RECORDING* recording)
    {
      return instance->toAddon.addon_instance->RenameRecording(*recording);
    }

    static inline PVR_ERROR ADDON_SetRecordingLifetime(const AddonInstance_PVR* instance, const PVR_RECORDING* recording)
    {
      return instance->toAddon.addon_instance->SetRecordingLifetime(*recording);
    }

    static inline PVR_ERROR ADDON_SetRecordingPlayCount(const AddonInstance_PVR* instance, const PVR_RECORDING* recording, int count)
    {
      return instance->toAddon.addon_instance->SetRecordingPlayCount(*recording, count);
    }

    static inline PVR_ERROR ADDON_SetRecordingLastPlayedPosition(const AddonInstance_PVR* instance, const PVR_RECORDING* recording, int lastplayedposition)
    {
      return instance->toAddon.addon_instance->SetRecordingLastPlayedPosition(*recording, lastplayedposition);
    }

    static inline int ADDON_GetRecordingLastPlayedPosition(const AddonInstance_PVR* instance, const PVR_RECORDING* recording)
    {
      return instance->toAddon.addon_instance->GetRecordingLastPlayedPosition(*recording);
    }

    static inline PVR_ERROR ADDON_GetRecordingEdl(const AddonInstance_PVR* instance, const PVR_RECORDING* recording, PVR_EDL_ENTRY edl[], int *size)
    {
      instance->toAddon.addon_instance->m_edlList.clear();
      PVR_ERROR error = instance->toAddon.addon_instance->GetRecordingEdl(*recording, instance->toAddon.addon_instance->m_edlList);
      edl = instance->toAddon.addon_instance->m_edlList.data();
      *size = instance->toAddon.addon_instance->m_edlList.size();
      return error;
    }

    static inline PVR_ERROR ADDON_GetTimerTypes(const AddonInstance_PVR* instance, PVR_TIMER_TYPE types[], int *typesCount)
    {
      std::vector<PVR_TIMER_TYPE> timerTypesList;
      PVR_ERROR error = instance->toAddon.addon_instance->GetTimerTypes(timerTypesList);
      *typesCount = 0;
      for (auto type : timerTypesList)
      {
        types[*typesCount] = type;
        ++*typesCount;
      }
      return error;
    }

    static inline int ADDON_GetTimersAmount(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->GetTimersAmount();
    }

    static inline PVR_ERROR ADDON_GetTimers(const AddonInstance_PVR* instance, ADDON_HANDLE handle)
    {
      std::vector<PVR_TIMER> timers;
      PVR_ERROR error = instance->toAddon.addon_instance->GetTimers(timers);
      for (auto iter : timers)
        instance->toAddon.addon_instance->m_instanceData->toKodi.transfer_timer_entry(instance->toKodi.kodi_instance, handle, &iter);
      return error;
    }

    static inline PVR_ERROR ADDON_AddTimer(const AddonInstance_PVR* instance, const PVR_TIMER* timer)
    {
      return instance->toAddon.addon_instance->AddTimer(*timer);
    }

    static inline PVR_ERROR ADDON_DeleteTimer(const AddonInstance_PVR* instance, const PVR_TIMER* timer, bool forceDelete)
    {
      return instance->toAddon.addon_instance->DeleteTimer(*timer, forceDelete);
    }

    static inline PVR_ERROR ADDON_UpdateTimer(const AddonInstance_PVR* instance, const PVR_TIMER* timer)
    {
      return instance->toAddon.addon_instance->UpdateTimer(*timer);
    }

    static inline bool ADDON_OpenLiveStream(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      return instance->toAddon.addon_instance->OpenLiveStream(*channel);
    }

    static inline void ADDON_CloseLiveStream(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->CloseLiveStream();
    }

    static inline int ADDON_ReadLiveStream(const AddonInstance_PVR* instance, unsigned char* buffer, unsigned int bufferSize)
    {
      return instance->toAddon.addon_instance->ReadLiveStream(buffer, bufferSize);
    }

    static inline long long ADDON_SeekLiveStream(const AddonInstance_PVR* instance, long long position, int whence)
    {
      return instance->toAddon.addon_instance->SeekLiveStream(position, whence);
    }

    static inline long long ADDON_PositionLiveStream(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->PositionLiveStream();
    }

    static inline long long ADDON_LengthLiveStream(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->LengthLiveStream();
    }

    static inline bool ADDON_SwitchChannel(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      return instance->toAddon.addon_instance->SwitchChannel(*channel);
    }

    static inline PVR_ERROR ADDON_SignalStatus(const AddonInstance_PVR* instance, PVR_SIGNAL_STATUS* signalStatus)
    {
      return instance->toAddon.addon_instance->SignalStatus(*signalStatus);
    }

    static inline PVR_ERROR ADDON_GetDescrambleInfo(const AddonInstance_PVR* instance, PVR_DESCRAMBLE_INFO* descrambleInfo)
    {
      return instance->toAddon.addon_instance->GetDescrambleInfo(*descrambleInfo);
    }

    static inline const char* ADDON_GetLiveStreamURL(const AddonInstance_PVR* instance, const PVR_CHANNEL* channel)
    {
      instance->toAddon.addon_instance->m_liveStreamURL = instance->toAddon.addon_instance->GetLiveStreamURL(*channel);
      return instance->toAddon.addon_instance->m_liveStreamURL.c_str();
    }

    static inline PVR_ERROR ADDON_GetStreamProperties(const AddonInstance_PVR* instance, PVR_STREAM_PROPERTIES* properties)
    {
      return instance->toAddon.addon_instance->GetStreamProperties(*properties);
    }

    static inline bool ADDON_OpenRecordedStream(const AddonInstance_PVR* instance, const PVR_RECORDING* recording)
    {
      return instance->toAddon.addon_instance->OpenRecordedStream(*recording);
    }

    static inline void ADDON_CloseRecordedStream(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->CloseRecordedStream();
    }

    static inline int ADDON_ReadRecordedStream(const AddonInstance_PVR* instance, unsigned char* buffer, unsigned int bufferSize)
    {
      return instance->toAddon.addon_instance->ReadRecordedStream(buffer, bufferSize);
    }

    static inline long long ADDON_SeekRecordedStream(const AddonInstance_PVR* instance, long long position, int whence)
    {
      return instance->toAddon.addon_instance->SeekRecordedStream(position, whence);
    }

    static inline long long ADDON_PositionRecordedStream(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->PositionRecordedStream();
    }

    static inline long long ADDON_LengthRecordedStream(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->LengthRecordedStream();
    }

    static inline void ADDON_DemuxReset(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->DemuxReset();
    }

    static inline void ADDON_DemuxAbort(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->DemuxAbort();
    }

    static inline void ADDON_DemuxFlush(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->DemuxFlush();
    }

    static inline DemuxPacket* ADDON_DemuxRead(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->DemuxRead();
    }

    static inline unsigned int ADDON_GetChannelSwitchDelay(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->GetChannelSwitchDelay();
    }

    static inline bool ADDON_CanPauseStream(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->CanPauseStream();
    }

    static inline bool ADDON_CanSeekStream(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->CanSeekStream();
    }

    static inline void ADDON_PauseStream(const AddonInstance_PVR* instance, bool paused)
    {
      instance->toAddon.addon_instance->PauseStream(paused);
    }

    static inline bool ADDON_SeekTime(const AddonInstance_PVR* instance, double time, bool backwards, double *startpts)
    {
      return instance->toAddon.addon_instance->SeekTime(time, backwards, *startpts);
    }

    static inline void ADDON_SetSpeed(const AddonInstance_PVR* instance, int speed)
    {
      instance->toAddon.addon_instance->SetSpeed(speed);
    }

    static inline time_t ADDON_GetPlayingTime(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->GetPlayingTime();
    }

    static inline time_t ADDON_GetBufferTimeStart(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->GetBufferTimeStart();
    }

    static inline time_t ADDON_GetBufferTimeEnd(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->GetBufferTimeEnd();
    }

    static inline const char* ADDON_GetBackendHostname(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->m_backendHostname = instance->toAddon.addon_instance->GetBackendHostname();
      return instance->toAddon.addon_instance->m_backendHostname.c_str();
    }

    static inline bool ADDON_IsTimeshifting(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->IsTimeshifting();
    }

    static inline bool ADDON_IsRealTimeStream(const AddonInstance_PVR* instance)
    {
      return instance->toAddon.addon_instance->IsRealTimeStream();
    }

    static inline void ADDON_OnSystemSleep(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->OnSystemSleep();
    }

    static inline void ADDON_OnSystemWake(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->OnSystemWake();
    }

    static inline void ADDON_OnPowerSavingActivated(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->OnPowerSavingActivated();
    }

    static inline void ADDON_OnPowerSavingDeactivated(const AddonInstance_PVR* instance)
    {
      instance->toAddon.addon_instance->OnPowerSavingDeactivated();
    }

    std::string m_backendName;
    std::string m_backendVersion;
    std::string m_backendHostname;
    std::string m_connectionString;
    std::string m_liveStreamURL;
    std::vector<PVR_EDL_ENTRY> m_edlList;
    AddonInstance_PVR* m_instanceData;
  };

} /* namespace addon */
} /* namespace kodi */


