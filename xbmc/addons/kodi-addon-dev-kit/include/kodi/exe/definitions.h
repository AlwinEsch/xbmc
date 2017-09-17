#pragma once
/*
 *      Copyright (C) 2005-2017 Team KODI
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

#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

  static constexpr const int KODI_API_ConnectionTimeout = 3;
  static constexpr const int KODI_API_ConnectionPort    = 34687;

  //============================================================================
  /// \ingroup KodiAddon_CPP_Main
  /// @brief Last error code generated from lib
  ///
  /// Becomes only be set if on  function on  error the  return of them  is  not
  /// possible, e.g. `KodiAPI::Init`.
  ///
  /// Human readable string can be retrived with `KodiAPI_ErrorCodeToString`.
  ///
  extern uint32_t KODI_API_lasterror;
  //----------------------------------------------------------------------------

  //============================================================================
  /// \ingroup KodiAddon_CPP_Defs
  /// @brief Properties about add-on informations
  ///
  /// This special extension point must be provided by all add-ons, and is the
  /// way that your add-on is described to users of the Kodi add-on manager.
  ///
  /// @note This properties becomes only be used on binary executable add-ons,
  /// which are possible to start independent from Kodi (but Kodi is running).
  /// This is required to inform Kodi about him.
  ///
  /// ------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// int main(int argc, char *argv[])
  /// {
  ///   addon_properties props;
  ///   props.id              = "demo_binary_addon";
  ///   props.type            = "xbmc.addon.executable";
  ///   props.version         = "0.0.1";
  ///   props.name            = "Demo binary add-on";
  ///   props.license         = "GNU GENERAL PUBLIC LICENSE. Version 2, June 1991";
  ///   props.summary         = "";
  ///   props.description     = "Hello World add-on provides some basic examples on how to create your first add-on";
  ///                           " and hopefully will increase the number of Kodi users to start creating their own addons.";
  ///   props.path            = "";
  ///   props.libname         = "";
  ///   props.author          = "";
  ///   props.source          = "http://github.com/someone/myaddon"";
  ///   props.icon            = "";
  ///   props.disclaimer      = "Feel free to use this add-on. For information visit the wiki.";
  ///   props.changelog       = "";
  ///   props.fanart          = "";
  ///   props.is_independent  = false;
  ///   props.use_net_only    = true;
  ///
  ///   if (KodiAPI::Init(argc, argv, &props, "127.0.0.1") != API_SUCCESS)
  ///   {
  ///     fprintf(stderr, "Binary AddOn: %i %s\n", KODI_API_lasterror, KodiAPI_ErrorCodeToString(KODI_API_lasterror));
  ///     return 1;
  ///   }
  ///   ...
  /// ~~~~~~~~~~~~~
  typedef struct addon_properties
  {
    /// @brief Identification name for add-on
    const char* id;

    /// @brief The used type of binary add-on
    ///
    /// Possible types are:
    ///
    /// | Identification name   | Description                                               |
    /// |-----------------------|-----------------------------------------------------------|
    /// | xbmc.addon.executable | A normal executable which match from style not the others |
    /// | xbmc.addon.video      | Video add-on for streams and everything to do there       |
    /// | xbmc.addon.audio      | To support audio for the user after start of him          |
    /// | xbmc.addon.image      | Add-on used to handle images in Kodi                      |
    ///
    const char* type;

    /// @brief Version of the add-on
    const char* version;

    /// @brief The own name.
    ///
    /// The human readable name of add-on used from Kodi e.g. in Log entries.
    ///
    const char* name;

    /// @brief Add-on licence
    ///
    /// The license element indicates what license is used for this add-on.
    ///
    /// ------------------------------------------------------------------------
    ///
    /// ~~~~~~~~~~~~~
    /// license="GNU GENERAL PUBLIC LICENSE. Version 2, June 1991";
    /// ~~~~~~~~~~~~~
    const char* license;


    /// @brief Summary add-on description
    ///
    /// The element provide a short summary of what the add-on does. This should
    /// be a single sentence.
    ///
    /// ------------------------------------------------------------------------
    ///
    /// ~~~~~~~~~~~~~
    /// summary="Hello World add-on provides some basic examples on how to create your first add-on.";
    /// ~~~~~~~~~~~~~
    const char* summary;

    /// @brief Detailed add-on description
    ///
    /// The element provide a more detailed summary of what the add-on does.
    ///
    /// ------------------------------------------------------------------------
    ///
    /// ~~~~~~~~~~~~~
    /// description="Hello World add-on provides some basic examples on how to create your first add-on"
    ///             " and hopefully will increase the number of Kodi users to start creating their own addons.";
    /// ~~~~~~~~~~~~~
    const char* description;

    /// @brief Add-on path (optional)
    const char* path;

    /// @brief Add-on executable name (optional)
    const char* libname;

    /// @brief Author of add-on
    ///
    /// Name of the man or company who created the add-on.
    const char* author;

    /// @brief Source URL (optional)
    ///
    /// The source element provides the URL for the source code for this specific
    /// add-on.
    ///
    /// -------------------------------------------------------------------------
    ///
    /// ~~~~~~~~~~~~~
    /// source="http://github.com/someone/myaddon";
    /// ~~~~~~~~~~~~~
    const char* source;

    /// @brief Add-on icon
    ///
    /// A PNG icon for the add-on. It can be 256x256 or  512x512 pixels big.  Try
    /// to make it look nice!
    const char* icon;

    /// @brief Disclaimer of add-on
    ///
    /// The element that indicate what (if any) things the user should know about
    /// the add-on. There is no need to have a disclaimer if you don't want  one,
    /// though if something requires  settings, or only  works  in  a  particular
    /// country then you may want to state this here.
    ///
    /// ------------------------------------------------------------------------
    ///
    /// ~~~~~~~~~~~~~
    /// disclaimer="Feel free to use this add-on. For information visit the wiki.";
    /// ~~~~~~~~~~~~~
    const char* disclaimer;

    /// @brief Change log of add-on (optional)
    ///
    /// Description of changes on add-on versions to allow show on Kodi's GUI for
    /// the user.
    const char* changelog;

    /// @brief Fan art Image
    ///
    /// Fan  art,  also  known  as  Backdrops, are high  quality artwork  that is
    /// displayed in the background as wallpapers on add-on GUI menus.
    const char* fanart;

    /// @brief To inform add-on is independent from Kodi.
    ///
    /// To  inform Kodi  that add-on  is independent and is not  stopped by  Kodi
    /// after calling "KodiAPI_Finalize".
    ///
    bool is_independent;

    /// @brief Option to create interface only over network.
    ///
    /// @note Should be  ignored and set  to false.  Is passicly  used  for  test
    /// purpose only.
    ///
    bool use_net_only;
  } addon_properties;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @{
  /// \ingroup KodiAddon_CPP_Defs
  /// @brief KODI API Error Classes
  ///
  /// The error codes are to describe the caused errors on interface.
  ///
  typedef enum KODI_API_Errortype
  {
    /// @brief Successful return code
    API_SUCCESS                 = 0,

    /// @brief Invalid buffer pointer
    API_ERR_BUFFER              = 1,

    /// @brief Invalid count argument
    API_ERR_COUNT               = 2,

    /// @brief Invalid datatype argument
    API_ERR_TYPE                = 3,

    /// @brief Invalid tag argument
    API_ERR_TAG                 = 4,

    /// @brief Invalid communicator
    API_ERR_COMM                = 5,

    /// @brief Invalid rank
    API_ERR_RANK                = 6,

    /// @brief Invalid root
    API_ERR_ROOT                = 7,

    /// @brief Null group passed to function
    API_ERR_GROUP               = 8,

    /// @brief Invalid operation
    API_ERR_OP                  = 9,

    /// @brief Invalid topology
    API_ERR_TOPOLOGY            = 10,

    /// @brief Illegal dimension argument
    API_ERR_DIMS                = 11,

    /// @brief Invalid argument
    API_ERR_ARG                 = 12,

    /// @brief Unknown error
    API_ERR_UNKNOWN             = 13,

    /// @brief message truncated on receive
    API_ERR_TRUNCATE            = 14,

    /// @brief Other error; use Error_string
    API_ERR_OTHER               = 15,

    /// @brief internal error code
    API_ERR_INTERN              = 16,

    /// @brief Look in status for error value
    API_ERR_IN_STATUS           = 17,

    /// @brief Pending request
    API_ERR_PENDING             = 18,

    /// @brief illegal API_request handle
    API_ERR_REQUEST             = 19,

    /// @brief failed to connect
    API_ERR_CONNECTION          = 20,

    /// @brief failed to connect
    API_ERR_VALUE_NOT_AVAILABLE = 21,

    /// @brief Last error code -- always at end
    API_ERR_LASTCODE            = 22
  } KODI_API_Errortype;
  /// @}
  //----------------------------------------------------------------------------

  namespace kodi
  {

  //============================================================================
  /// \ingroup KodiAddon_CPP_Main
  /// @brief Add-on initialization function
  ///
  /// @warning Function only be needed on binary executable add-ons for Kodi!
  ///
  /// To be used for initialization of main interface  from Add-on to Kodi. This
  /// is  the  master  to be used  on  the  executables  <b><c>main(...)</c></b>
  /// function.
  ///
  /// @warning The  used   handle  is  only  be  used on his thread,  if another
  /// thread    is   created,   should    be   another  handle   returned   from
  /// <b><c>KodiAPI::InitThread(...)</c></b> to be used!\n\n
  /// Further  is  this  call   only   be   allowed   to   call   one   time  on
  /// <b><c>main(...)</c></b>.\n\n
  /// Also  should  never  forget  to call  <b><c>KodiAPI::Finalize(...)</c></b>
  /// before exit  of  addon  to   prevent  problems   about  still  organizated
  /// communication interface between Kodi and Add-on
  ///
  /// @param[in] argc         Amount of command line values present
  /// @param[in] argv[]       String list with given command line values
  /// @param[in] props        From add-on developer requested  properties on his
  ///                         add-on to Kodi.
  /// @param[in] hostname     The  host  name   address   to  use,  default   is
  ///                         127.0.0.1
  /// @return                 Add-on error codes from `KODI_API_Errortype` or if
  ///                         OK with `API_SUCCESS`
  ///
  /// @note If pointer is  returned  NULL is the  related last  error code  with
  /// `uint32_t KODI_API_lasterror` available.
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/api2/AddonLib.hpp>
  ///
  /// int main(int argc, char *argv[])
  /// {
  ///   addon_properties props;
  ///   props.addon_name      = "My Demo binary add-on";
  ///   props.is_independent  = false;
  ///
  ///   int retValue = KodiAPI::Init(argc, argv, &props)
  ///   if (retValue != API_SUCCESS)
  ///   {
  ///     fprintf(stderr, "Binary AddOn: %s\n", KodiAPI::ErrorCodeToString(retValue));
  ///     return 1;
  ///   }
  ///   ...
  ///   return 0;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  int Init(
    int               argc,
    char*             argv[],
    addon_properties* props,
    const std::string &hostname = "127.0.0.1");
  //----------------------------------------------------------------------------

  //============================================================================
  /// \ingroup KodiAddon_CPP_Main
  /// @brief To close Add-on to Kodi control interface
  ///
  /// This function is required after end of processes and on exit of them, e.g.
  /// Add-on itself exits or a thread with handling becomes closed.
  ///
  /// @return                 Add-on error codes from `KODI_API_Errortype` or if
  ///                         OK with `API_SUCCESS`
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example 1 (Executable add-on):**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/api2/AddonLib.hpp>
  ///
  /// int main(int argc, char *argv[])
  /// {
  ///   addon_properties props;
  ///   ...
  ///
  ///   KodiAPI::Init(argc, argv, &props);
  ///   ...
  ///
  ///   KodiAPI::Finalize();
  ///   return 0;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example 2 (Library add-on):**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/api2/AddonLib.hpp>
  ///
  /// ...
  ///
  /// void ADDON_Destroy()
  /// {
  ///   KodiAPI::Finalize();
  ///   m_CurStatus = ADDON_STATUS_UNKNOWN;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example 3: (Add-on Thread)**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/api2/AddonLib.hpp>
  ///
  /// void* CThreadTest::Process(void)
  /// {
  ///   KodiAPI_InitThread();
  ///
  ///   while (!IsStopped())
  ///   {
  ///     ...
  ///   }
  ///
  ///   KodiAPI::Finalize();
  ///   return nullptr;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  int Finalize();
  //----------------------------------------------------------------------------

  //============================================================================
  /// \ingroup KodiAddon_CPP_Main
  /// @brief Get string for error code
  ///
  /// To  translate a from several functions used error code in a human readable
  /// format
  ///
  /// @param[in] code         Error value to translate to string
  /// @return                 String about error
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/api2/AddonLib.hpp>
  ///
  /// ...
  /// int retValue = KodiAPI::Init(argc, argv, &props)
  /// if (retValue != API_SUCCESS)
  /// {
  ///   fprintf(stderr, "Binary AddOn: %s\n", KodiAPI_ErrorCodeToString(retValue));
  ///   return 1;
  /// }
  /// ...
  /// ~~~~~~~~~~~~~
  ///
  const char* ErrorCodeToString(uint32_t code);
  //----------------------------------------------------------------------------
  }

  typedef enum KODI_API_Calls
  {
    KODICall_Noop                     = 0,
    KODICall_LoginVerify              = 1,
    KODICall_Logout                   = 2,
    KODICall_Ping                     = 3,
    KODICall_Log                      = 6,
    KODICall_CreateSubThread          = 7,
    KODICall_DeleteSubThread          = 8,

    KODICall_AddOn_General_GetSettingString                               =  97,
    KODICall_AddOn_General_GetSettingBoolean                              =  98,
    KODICall_AddOn_General_GetSettingInt                                  =  99,
    KODICall_AddOn_General_GetSettingFloat                                = 100,
    KODICall_AddOn_General_OpenSettings                                   = 101,
    KODICall_AddOn_General_GetAddonInfo                                   = 102,
    KODICall_AddOn_General_QueueFormattedNotification                     = 103,
    KODICall_AddOn_General_QueueNotificationFromType                      = 104,
    KODICall_AddOn_General_QueueNotificationWithImage                     = 105,
    KODICall_AddOn_General_GetMD5                                         = 106,
    KODICall_AddOn_General_UnknownToUTF8                                  = 107,
    KODICall_AddOn_General_GetLocalizedString                             = 108,
    KODICall_AddOn_General_GetLanguage                                    = 109,
    KODICall_AddOn_General_GetDVDMenuLanguage                             = 110,
    KODICall_AddOn_General_StartServer                                    = 111,
    KODICall_AddOn_General_AudioSuspend                                   = 112,
    KODICall_AddOn_General_AudioResume                                    = 113,
    KODICall_AddOn_General_GetVolume                                      = 114,
    KODICall_AddOn_General_SetVolume                                      = 115,
    KODICall_AddOn_General_IsMuted                                        = 116,
    KODICall_AddOn_General_ToggleMute                                     = 117,
    KODICall_AddOn_General_SetMute                                        = 118,
    KODICall_AddOn_General_GetOpticalDriveState                           = 119,
    KODICall_AddOn_General_EjectOpticalDrive                              = 120,
    KODICall_AddOn_General_KodiVersion                                    = 121,
    KODICall_AddOn_General_KodiQuit                                       = 122,
    KODICall_AddOn_General_HTPCShutdown                                   = 123,
    KODICall_AddOn_General_HTPCRestart                                    = 124,
    KODICall_AddOn_General_ExecuteScript                                  = 125,
    KODICall_AddOn_General_ExecuteBuiltin                                 = 126,
    KODICall_AddOn_General_ExecuteJSONRPC                                 = 127,
    KODICall_AddOn_General_GetRegion                                      = 128,
    KODICall_AddOn_General_GetFreeMem                                     = 129,
    KODICall_AddOn_General_GetGlobalIdleTime                              = 130,
    KODICall_AddOn_General_TranslatePath                                  = 131,
  } KODI_API_Calls;

  typedef enum KODI_API_Packets
  {
    KODIPacket_RequestedResponse      = 1,
    KODIPacket_Status                 = 2

  } KODI_API_Packets;

  typedef struct KODI_API_ErrorTranslator
  {
    uint32_t    errorCode;
    const char* errorName;
  } KODI_API_ErrorTranslator;

  extern const KODI_API_ErrorTranslator errorTranslator[];

  /// @{
  /// @brief
  typedef enum KODI_API_Datatype
  {
    /// @brief
    API_DATATYPE_NULL           = 0x00000000,

    /// @{
    /// @brief
    API_CHAR                    = 0x00000001,
    /// @brief
    API_SIGNED_CHAR             = 0x00000002,
    /// @brief
    API_UNSIGNED_CHAR           = 0x00000003,
    /// @}

    /// @{
    /// @brief
    API_SHORT                   = 0x00000101,
    /// @brief
    API_SIGNED_SHORT            = 0x00000102,
    /// @brief
    API_UNSIGNED_SHORT          = 0x00000103,
    /// @}

    /// @{
    /// @brief
    API_INT                     = 0x00000201,
    API_CONST_INT               = 0x00000201,
    /// @brief
    API_SIGNED_INT              = 0x00000202,
    /// @brief
    API_UNSIGNED_INT            = 0x00000203,
    /// @}

    /// @{
    /// @brief
    API_LONG                    = 0x00000301,
    /// @brief
    API_SIGNED_LONG             = 0x00000302,
    /// @brief
    API_UNSIGNED_LONG           = 0x00000303,
    /// @}

    /// @{
    /// @brief
    API_FLOAT                   = 0x00000501,
    /// @brief
    API_DOUBLE                  = 0x00000511,
    /// @brief
    API_LONG_DOUBLE             = 0x00000521,
    /// @}

    /// @{
    /// @brief
    API_INT8_T                  = 0x00000701,
    /// @brief
    API_INT16_T                 = 0x00000702,
    /// @brief
    API_INT32_T                 = 0x00000703,
    /// @brief
    API_INT64_T                 = 0x00000704,
    /// @}

    /// @{
    /// @brief
    API_UINT8_T                 = 0x00000801,
    /// @brief
    API_UINT16_T                = 0x00000802,
    /// @brief
    API_UINT32_T                = 0x00000803,
    /// @brief
    API_UINT64_T                = 0x00000804,
    /// @}

    API_VOID_PTR                = 0x00000901,
    API_BOOL                    = 0x00000902,
    API_STRING                  = 0x00000911,
    API_CONST_CHAR_PTR          = 0x00000911,
    API_CHAR_PTR                = 0x00000912,
    API_ADDON_HANDLE            = 0x00000913,
    API_BOOL_PTR                = 0x00000914,
    API_INT_PTR                 = 0x00000915,
    API_LONG_PTR                = 0x00000916,
    API_FLOAT_PTR               = 0x00000917,
    API_CHAR_PTR_PTR            = 0x00000918,

    /// @{
    /// @brief
    API_PACKED                  = 0x00001001,
    /// @brief
    API_LB                      = 0x00001002,
    /// @brief
    API_UB                      = 0x00001003,
    /// @}

    /// @{
    /// @brief The layouts for the types API_DOUBLE_INT etc are simply
    ///
    /// ~~~~~~~~~~~~~
    /// struct
    /// {
    ///   double var;
    ///   int    loc;
    /// }
    ///
    /// This is documented in the man pages on the various datatypes.
    ///

    /// @brief
    API_FLOAT_INT               = 0x00002001,
    /// @brief
    API_DOUBLE_INT              = 0x00002002,
    /// @brief
    API_LONG_INT                = 0x00002003,
    /// @brief
    API_SHORT_INT               = 0x00002004,
    /// @brief
    API_2INT                    = 0x00002005,
    /// @brief
    API_LONG_DOUBLE_INT         = 0x00002006
    /// @}
  } KODI_API_Datatype;
  /// @}

  #define IMPL_STREAM_PROPS                         \
    private:                                        \
      stream_vector              *m_streamVector;   \
      std::map<unsigned int, int> m_streamIndex;    \
      void UpdateIndex();

#ifdef __cplusplus
}; /* extern "C" */
#endif
