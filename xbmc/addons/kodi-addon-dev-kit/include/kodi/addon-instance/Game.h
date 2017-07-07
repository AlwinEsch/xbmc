#pragma once
/*
 *      Copyright (C) 2014-2017 Team Kodi
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

#include "../AddonBase.h"
#include "../Filesystem.h"

#include <stddef.h>
#include <stdint.h>

#ifdef BUILD_KODI_ADDON
#include "XBMC_vkeys.h"
#else
#include "input/XBMC_vkeys.h"
#endif

namespace kodi { namespace addon { class CInstanceGame; } }

#ifdef __cplusplus
extern "C" {
#endif

/*! Game add-on error codes */
typedef enum GAME_ERROR
{
  GAME_ERROR_NO_ERROR,               // no error occurred
  GAME_ERROR_UNKNOWN,                // an unknown error occurred
  GAME_ERROR_NOT_IMPLEMENTED,        // the method that the frontend called is not implemented
  GAME_ERROR_REJECTED,               // the command was rejected by the game client
  GAME_ERROR_INVALID_PARAMETERS,     // the parameters of the method that was called are invalid for this operation
  GAME_ERROR_FAILED,                 // the command failed
  GAME_ERROR_NOT_LOADED,             // no game is loaded
  GAME_ERROR_RESTRICTED,             // game requires restricted resources
} GAME_ERROR;

typedef enum GAME_STREAM_TYPE
{
  GAME_STREAM_UNKNOWN,
  GAME_STREAM_AUDIO,
  GAME_STREAM_VIDEO,
} GAME_STREAM_TYPE;

typedef enum GAME_PIXEL_FORMAT
{
  GAME_PIXEL_FORMAT_UNKNOWN,
  GAME_PIXEL_FORMAT_YUV420P,
  GAME_PIXEL_FORMAT_0RGB8888,
  GAME_PIXEL_FORMAT_RGB565,
  GAME_PIXEL_FORMAT_0RGB1555,
} GAME_PIXEL_FORMAT;

typedef enum GAME_VIDEO_CODEC
{
  GAME_VIDEO_CODEC_UNKNOWN,
  GAME_VIDEO_CODEC_H264,
  GAME_VIDEO_CODEC_THEORA,
} GAME_VIDEO_CODEC;

typedef enum GAME_VIDEO_ROTATION // Counter-clockwise
{
  GAME_VIDEO_ROTATION_0,
  GAME_VIDEO_ROTATION_90,
  GAME_VIDEO_ROTATION_180,
  GAME_VIDEO_ROTATION_270,
} GAME_VIDEO_ROTATION;

typedef enum GAME_PCM_FORMAT
{
  GAME_PCM_FORMAT_UNKNOWN,
  GAME_PCM_FORMAT_S16NE,
} GAME_PCM_FORMAT;

typedef enum GAME_AUDIO_CODEC
{
  GAME_AUDIO_CODEC_UNKNOWN,
  GAME_AUDIO_CODEC_OPUS,
} GAME_AUDIO_CODEC;

typedef enum GAME_AUDIO_CHANNEL
{
  GAME_CH_NULL, // Channel list terminator
  GAME_CH_FL,
  GAME_CH_FR,
  GAME_CH_FC,
  GAME_CH_LFE,
  GAME_CH_BL,
  GAME_CH_BR,
  GAME_CH_FLOC,
  GAME_CH_FROC,
  GAME_CH_BC,
  GAME_CH_SL,
  GAME_CH_SR,
  GAME_CH_TFL,
  GAME_CH_TFR,
  GAME_CH_TFC,
  GAME_CH_TC,
  GAME_CH_TBL,
  GAME_CH_TBR,
  GAME_CH_TBC,
  GAME_CH_BLOC,
  GAME_CH_BROC,
} GAME_AUDIO_CHANNEL;

// TODO
typedef enum GAME_HW_FRAME_BUFFER
{
  GAME_HW_FRAME_BUFFER_VALID,     // Pass this to game_video_refresh if rendering to hardware
  GAME_HW_FRAME_BUFFER_DUPLICATE, // Passing NULL to game_video_refresh is still a frame dupe as normal
  GAME_HW_FRAME_BUFFER_RENDER,
} GAME_HW_FRAME_BUFFER;

typedef enum GAME_HW_CONTEXT_TYPE
{
  GAME_HW_CONTEXT_NONE,
  GAME_HW_CONTEXT_OPENGL,      // OpenGL 2.x. Latest version available before 3.x+. Driver can choose to use latest compatibility context
  GAME_HW_CONTEXT_OPENGLES2,   // GLES 2.0
  GAME_HW_CONTEXT_OPENGL_CORE, // Modern desktop core GL context. Use major/minor fields to set GL version
  GAME_HW_CONTEXT_OPENGLES3,   // GLES 3.0
} GAME_HW_CONTEXT_TYPE;

typedef enum GAME_INPUT_PORT
{
  GAME_INPUT_PORT_JOYSTICK_START = 0, // Non-negative values are for joystick ports
  GAME_INPUT_PORT_KEYBOARD = -1,
  GAME_INPUT_PORT_MOUSE = -2,
} GAME_INPUT_PORT;

typedef enum GAME_INPUT_EVENT_SOURCE
{
  GAME_INPUT_EVENT_DIGITAL_BUTTON,
  GAME_INPUT_EVENT_ANALOG_BUTTON,
  GAME_INPUT_EVENT_ANALOG_STICK,
  GAME_INPUT_EVENT_ACCELEROMETER,
  GAME_INPUT_EVENT_KEY,
  GAME_INPUT_EVENT_RELATIVE_POINTER,
  GAME_INPUT_EVENT_ABSOLUTE_POINTER,
  GAME_INPUT_EVENT_MOTOR,
} GAME_INPUT_EVENT_SOURCE;

typedef enum GAME_KEY_MOD
{
  GAME_KEY_MOD_NONE = 0x00,

  GAME_KEY_MOD_SHIFT = 0x01,
  GAME_KEY_MOD_CTRL = 0x02,
  GAME_KEY_MOD_ALT = 0x04,
  GAME_KEY_MOD_RALT = 0x08,
  GAME_KEY_MOD_META = 0x10,

  GAME_KEY_MOD_NUMLOCK = 0x20,
  GAME_KEY_MOD_CAPSLOCK = 0x40,
  GAME_KEY_MOD_SCROLLOCK = 0x80,
} GAME_KEY_MOD;

/*! Returned from game_get_region() */
typedef enum GAME_REGION
{
  GAME_REGION_UNKNOWN,
  GAME_REGION_NTSC,
  GAME_REGION_PAL,
} GAME_REGION;

/*!
* Special game types passed into game_load_game_special(). Only used when
* multiple ROMs are required.
*/
typedef enum SPECIAL_GAME_TYPE
{
  SPECIAL_GAME_TYPE_BSX,
  SPECIAL_GAME_TYPE_BSX_SLOTTED,
  SPECIAL_GAME_TYPE_SUFAMI_TURBO,
  SPECIAL_GAME_TYPE_SUPER_GAME_BOY,
} SPECIAL_GAME_TYPE;

typedef enum GAME_MEMORY
{
  /*!
   * Passed to game_get_memory_data/size(). If the memory type doesn't apply
   * to the implementation NULL/0 can be returned.
   */
  GAME_MEMORY_MASK                   = 0xff,

  /*!
   * Regular save ram. This ram is usually found on a game cartridge, backed
   * up by a battery. If save game data is too complex for a single memory
   * buffer, the SYSTEM_DIRECTORY environment callback can be used.
   */
  GAME_MEMORY_SAVE_RAM               = 0,

  /*!
   * Some games have a built-in clock to keep track of time. This memory is
   * usually just a couple of bytes to keep track of time.
   */
  GAME_MEMORY_RTC                    = 1,

  /*! System ram lets a frontend peek into a game systems main RAM */
  GAME_MEMORY_SYSTEM_RAM             = 2,

  /*! Video ram lets a frontend peek into a game systems video RAM (VRAM) */
  GAME_MEMORY_VIDEO_RAM              = 3,

  /*! Special memory types */
  GAME_MEMORY_SNES_BSX_RAM           = ((1 << 8) | GAME_MEMORY_SAVE_RAM),
  GAME_MEMORY_SNES_BSX_PRAM          = ((2 << 8) | GAME_MEMORY_SAVE_RAM),
  GAME_MEMORY_SNES_SUFAMI_TURBO_A_RAM= ((3 << 8) | GAME_MEMORY_SAVE_RAM),
  GAME_MEMORY_SNES_SUFAMI_TURBO_B_RAM= ((4 << 8) | GAME_MEMORY_SAVE_RAM),
  GAME_MEMORY_SNES_GAME_BOY_RAM      = ((5 << 8) | GAME_MEMORY_SAVE_RAM),
  GAME_MEMORY_SNES_GAME_BOY_RTC      = ((6 << 8) | GAME_MEMORY_RTC),
} GAME_MEMORY;

/*! ID values for SIMD CPU features */
typedef enum GAME_SIMD
{
  GAME_SIMD_SSE                      = (1 << 0),
  GAME_SIMD_SSE2                     = (1 << 1),
  GAME_SIMD_VMX                      = (1 << 2),
  GAME_SIMD_VMX128                   = (1 << 3),
  GAME_SIMD_AVX                      = (1 << 4),
  GAME_SIMD_NEON                     = (1 << 5),
  GAME_SIMD_SSE3                     = (1 << 6),
  GAME_SIMD_SSSE3                    = (1 << 7),
  GAME_SIMD_MMX                      = (1 << 8),
  GAME_SIMD_MMXEXT                   = (1 << 9),
  GAME_SIMD_SSE4                     = (1 << 10),
  GAME_SIMD_SSE42                    = (1 << 11),
  GAME_SIMD_AVX2                     = (1 << 12),
  GAME_SIMD_VFPU                     = (1 << 13),
} GAME_SIMD;

typedef enum GAME_ROTATION
{
  GAME_ROTATION_0_CW,
  GAME_ROTATION_90_CW,
  GAME_ROTATION_180_CW,
  GAME_ROTATION_270_CW,
} GAME_ROTATION;

typedef struct game_controller
{
  const char*  controller_id;
  unsigned int digital_button_count;
  unsigned int analog_button_count;
  unsigned int analog_stick_count;
  unsigned int accelerometer_count;
  unsigned int key_count;
  unsigned int rel_pointer_count;
  unsigned int abs_pointer_count;
  unsigned int motor_count;
} ATTRIBUTE_PACKED game_controller;

typedef struct game_digital_button_event
{
  bool         pressed;
} ATTRIBUTE_PACKED game_digital_button_event;

typedef struct game_analog_button_event
{
  float        magnitude;
} ATTRIBUTE_PACKED game_analog_button_event;

typedef struct game_analog_stick_event
{
  float        x;
  float        y;
} ATTRIBUTE_PACKED game_analog_stick_event;

typedef struct game_accelerometer_event
{
  float        x;
  float        y;
  float        z;
} ATTRIBUTE_PACKED game_accelerometer_event;

typedef struct game_key_event
{
  bool         pressed;
  XBMCVKey     character;
  GAME_KEY_MOD modifiers;
} ATTRIBUTE_PACKED game_key_event;

typedef struct game_rel_pointer_event
{
  int          x;
  int          y;
} ATTRIBUTE_PACKED game_rel_pointer_event;

typedef struct game_abs_pointer_event
{
  bool         pressed;
  float        x;
  float        y;
} ATTRIBUTE_PACKED game_abs_pointer_event;

typedef struct game_motor_event
{
  float        magnitude;
} ATTRIBUTE_PACKED game_motor_event;

typedef struct game_input_event
{
  GAME_INPUT_EVENT_SOURCE type;
  int                     port;
  const char*             controller_id;
  const char*             feature_name;
  union
  {
    struct game_digital_button_event digital_button;
    struct game_analog_button_event  analog_button;
    struct game_analog_stick_event   analog_stick;
    struct game_accelerometer_event  accelerometer;
    struct game_key_event            key;
    struct game_rel_pointer_event    rel_pointer;
    struct game_abs_pointer_event    abs_pointer;
    struct game_motor_event          motor;
  };
} ATTRIBUTE_PACKED game_input_event;

struct game_geometry
{
  unsigned base_width;          // Nominal video width of game
  unsigned base_height;         // Nominal video height of game
  unsigned max_width;           // Maximum possible width of game
  unsigned max_height;          // Maximum possible height of game
  float    aspect_ratio;        // Nominal aspect ratio of game. If aspect_ratio is <= 0.0,
                                // an aspect ratio of base_width / base_height is assumed.
                                // A frontend could override this setting if desired.
};

struct game_system_timing
{
  double fps;                   // FPS of video content.
  double sample_rate;           // Sampling rate of audio.
};

struct game_system_av_info
{
  struct game_geometry geometry;
  struct game_system_timing timing;
};

typedef void (*game_proc_address_t)(void);

struct game_hw_info
{
  GAME_HW_CONTEXT_TYPE context_type;        // Which API to use. Set by game client
  bool                 depth;               // Set if render buffers should have depth component attached
  bool                 stencil;             // Set if stencil buffers should be attached
                                            // If depth and stencil are true, a packed 24/8 buffer will be added. Only attaching stencil is invalid and will be ignored
  bool                 bottom_left_origin;  // Use conventional bottom-left origin convention. Is false, standard top-left origin semantics are used
  unsigned             version_major;       // Major version number for core GL context
  unsigned             version_minor;       // Minor version number for core GL context
  bool                 cache_context;       // If this is true, the frontend will go very far to avoid resetting context in scenarios like toggling fullscreen, etc.
                                            // The reset callback might still be called in extreme situations such as if the context is lost beyond recovery
                                            // For optimal stability, set this to false, and allow context to be reset at any time
  bool                 debug_context;       // Creates a debug context
};

/*! Properties passed to the ADDON_Create() method of a game client */
typedef struct AddonProps_Game
{
  /*!
   * The path of the game client being loaded.
   */
  const char* game_client_dll_path;

  /*!
   * Paths to proxy DLLs used to load the game client.
   */
  const char** proxy_dll_paths;

  /*!
   * Number of proxy DLL paths provided.
   */
  unsigned int proxy_dll_count;

  /*!
   * The "system" directories of the frontend. These directories can be used to
   * store system-specific ROMs such as BIOSes, configuration data, etc.
   */
  const char** resource_directories;

  /*!
   * Number of resource directories provided
   */
  unsigned int resource_directory_count;

  /*!
   * The writable directory of the frontend. This directory can be used to store
   * SRAM, memory cards, high scores, etc, if the game client cannot use the
   * regular memory interface, GetMemoryData().
   */
  const char* profile_directory;

  /*!
   * The value of the <supports_vfs> property from addon.xml
   */
  bool supports_vfs;

  /*!
   * The extensions in the <extensions> property from addon.xml
   */
  const char** extensions;

  /*!
   * Number of extensions provided
   */
  unsigned int extension_count;
} AddonProps_Game;
  
/*! Structure to transfer the methods from kodi_game_dll.h to Kodi */

typedef struct AddonToKodiFuncTable_Game
{
  KODI_HANDLE kodiInstance;

  void (*close_game)(void* kodiInstance);
  int (*open_pixel_stream)(void* kodiInstance, GAME_PIXEL_FORMAT format, unsigned int width, unsigned int height, GAME_VIDEO_ROTATION rotation);
  int (*open_video_stream)(void* kodiInstance, GAME_VIDEO_CODEC codec);
  int (*open_pcm_stream)(void* kodiInstance, GAME_PCM_FORMAT format, const GAME_AUDIO_CHANNEL* channel_map);
  int(*open_audio_stream)(void* kodiInstance, GAME_AUDIO_CODEC codec, const GAME_AUDIO_CHANNEL* channel_map);
  void (*add_stream_data)(void* kodiInstance, GAME_STREAM_TYPE stream, const uint8_t* data, unsigned int size);
  void (*close_stream)(void* kodiInstance, GAME_STREAM_TYPE stream);
  void (*enable_hardware_rendering)(void* kodiInstance, const game_hw_info* hw_info);
  uintptr_t (*hw_get_current_framebuffer)(void* kodiInstance);
  game_proc_address_t (*hw_get_proc_address)(void* kodiInstance, const char* symbol);
  void (*render_frame)(void* kodiInstance);
  bool (*open_port)(void* kodiInstance, unsigned int port);
  void (*close_port)(void* kodiInstance, unsigned int port);
  bool (*input_event)(void* kodiInstance, const game_input_event* event);

} AddonToKodiFuncTable_Game;

struct AddonInstance_Game;
typedef struct KodiToAddonFuncTable_Game
{
  kodi::addon::CInstanceGame* addon_instance;

  GAME_ERROR (__cdecl* load_game)(const AddonInstance_Game* instance, const char* url);
  GAME_ERROR (__cdecl* load_game_special)(const AddonInstance_Game* instance, SPECIAL_GAME_TYPE type, const char** urls, size_t url_count);
  GAME_ERROR (__cdecl* load_standalone)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* unload_game)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* get_game_info)(const AddonInstance_Game* instance, game_system_av_info* info);
  GAME_REGION (__cdecl* get_region)(const AddonInstance_Game* instance);
  bool (__cdecl* requires_game_loop)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* run_frame)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* reset)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* hw_context_reset)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* hw_context_destroy)(const AddonInstance_Game* instance);
  void (__cdecl* update_port)(const AddonInstance_Game* instance, int port, bool connected, const game_controller* controller);
  bool (__cdecl* has_feature)(const AddonInstance_Game* instance, const char* controller_id, const char* feature_name);
  bool (__cdecl* input_event)(const AddonInstance_Game* instance, const game_input_event* event);
  size_t (__cdecl* serialize_size)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* serialize)(const AddonInstance_Game* instance, uint8_t* data, size_t size);
  GAME_ERROR (__cdecl* deserialize)(const AddonInstance_Game* instance, const uint8_t* data, size_t size);
  GAME_ERROR (__cdecl* cheat_reset)(const AddonInstance_Game* instance);
  GAME_ERROR (__cdecl* get_memory)(const AddonInstance_Game* instance, GAME_MEMORY type, uint8_t** data, size_t* size);
  GAME_ERROR (__cdecl* set_cheat)(const AddonInstance_Game* instance, unsigned int index, bool enabled, const char* code);
} KodiToAddonFuncTable_Game;

typedef struct AddonInstance_Game
{
  AddonProps_Game props;
  AddonToKodiFuncTable_Game toKodi;
  KodiToAddonFuncTable_Game toAddon;
} AddonInstance_Game;

#ifdef __cplusplus
}
#endif

namespace kodi {
namespace addon {

  class CInstanceGame : public IAddonInstance
  {
  public:
    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Visualization class constructor
    ///
    /// Used on addon who supports only visualization and CAddonBase is also
    /// included as parent.
    ///
    CInstanceGame() : IAddonInstance(ADDON_INSTANCE_GAME)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceGame: Creation of more as one in single instance way is not allowed!");

      SetAddonStruct(CAddonBase::m_interface->firstKodiInstance);
      CAddonBase::m_interface->globalSingleInstance = this;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Visualization class constructor used to support multiple instance
    /// types
    ///
    /// @param[in] instance               The with <b>`kodi::addon::CAddonBase::CreateInstance(...)`</b>
    ///                                   given `instance` value.
    ///
    /// @warning Use always only `instance` value from CreateInstance call
    ///
    CInstanceGame(KODI_HANDLE instance) : IAddonInstance(ADDON_INSTANCE_GAME)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceGame: Creation of multiple together with single instance way is not allowed!");

      SetAddonStruct(instance);
    }
    //--------------------------------------------------------------------------

    // --- Game operations ---------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Load a game
    ///
    /// @param url The URL to load
    ///
    /// return the error, or GAME_ERROR_NO_ERROR if the game was loaded
    ///
    virtual GAME_ERROR LoadGame(const std::string& url) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Load a game that requires multiple files
    ///
    /// @param type The game stype
    /// @param urls An array of urls
    /// @param urlCount The number of urls in the array
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the game was loaded
    ///
    virtual GAME_ERROR LoadGameSpecial(SPECIAL_GAME_TYPE type, const std::vector<std::string>& urls) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Begin playing without a game file
    ///
    /// If the add-on supports standalone mode, it must add the <supports_standalone>
    /// tag to the extension point in addon.xml:
    ///
    ///     <supports_no_game>false</supports_no_game>
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the game add-on was loaded
    ///
    virtual GAME_ERROR LoadStandalone(void) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Unload the current game
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the game was unloaded
    ///
    virtual GAME_ERROR UnloadGame(void) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Get information about the loaded game
    ///
    /// @param info The info structure to fill
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if info was filled
    ///
    virtual GAME_ERROR GetGameInfo(game_system_av_info& info) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Get region of the loaded game
    ///
    /// @return the region, or GAME_REGION_UNKNOWN if unknown or no game is loaded
    ///
    virtual GAME_REGION GetRegion(void) { return GAME_REGION_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Return true if the client requires the frontend to provide a game loop
    ///
    /// The game loop is a thread that calls RunFrame() in a loop at a rate
    /// determined by the playback speed and the client's FPS.
    ///
    /// @return true if the frontend should provide a game loop, false otherwise
    ///
    virtual bool RequiresGameLoop(void) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Run a single frame for add-ons that use a game loop
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if there was no error
    ///
    virtual GAME_ERROR RunFrame(void) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Reset the current game
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the game was reset
    ///
    virtual GAME_ERROR Reset(void) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    // --- Hardware rendering operations -------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Invalidates the current HW context and reinitializes GPU resources
    ///
    /// Any GL state is lost, and must not be deinitialized explicitly.
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the HW context was reset
    ///
    virtual GAME_ERROR HwContextReset(void) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Called before the context is destroyed
    ///
    /// Resources can be deinitialized at this step.
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the HW context was destroyed
    ///
    virtual GAME_ERROR HwContextDestroy(void) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    // --- Input operations --------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Notify the add-on of a status change on an open port
    ///
    /// Ports can be opened using the OpenPort() callback
    ///
    /// @param port Non-negative for a joystick port, or GAME_INPUT_PORT value otherwise
    /// @param collected True if a controller was connected, false if disconnected
    /// @param controller The connected controller
    ///
    virtual void UpdatePort(int port, bool connected, const game_controller* controller) { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Check if input is accepted for a feature on the controller
    ///
    /// If only a subset of the controller profile is used, this can return false
    /// for unsupported features to not absorb their input.
    ///
    /// If the entire controller profile is used, this should always return true.
    ///
    /// @param controllerId The ID of the controller profile
    /// @param featureName The name of a feature in that profile
    /// @return true if input is accepted for the feature, false otherwise
    ///
    virtual bool HasFeature(const std::string& controllerId, const std::string& featureName) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Notify the add-on of an input event
    ///
    /// @param event The input event
    ///
    /// @return true if the event was handled, false otherwise
    ///
    virtual bool InputEvent(const game_input_event* event) { return false; }
    //--------------------------------------------------------------------------

    // --- Serialization operations ------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Get the number of bytes required to serialize the game
    ///
    /// @return the number of bytes, or 0 if serialization is not supported
    ///
    virtual size_t SerializeSize(void) { return 0; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Serialize the state of the game
    ///
    /// @param data The buffer receiving the serialized game data
    /// @param size The size of the buffer
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the game was serialized into the buffer
    ///
    virtual GAME_ERROR Serialize(uint8_t* data, size_t size) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Deserialize the game from the given state
    ///
    /// @param data A buffer containing the game's new state
    /// @param size The size of the buffer
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the game deserialized
    ///
    virtual GAME_ERROR Deserialize(const uint8_t* data, size_t size) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    // --- Cheat operations --------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Reset the cheat system
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the cheat system was reset
    ///
    virtual GAME_ERROR CheatReset(void) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Get a region of memory
    ///
    /// @param type The type of memory to retrieve
    /// @param data Set to the region of memory; must remain valid until UnloadGame() is called
    /// @param size Set to the size of the region of memory
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if data was set to a valid buffer
    ///
    virtual GAME_ERROR GetMemory(GAME_MEMORY type, uint8_t** data, size_t* size) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Set a cheat code
    ///
    /// @param index
    /// @param enabled
    /// @param code
    ///
    /// @return the error, or GAME_ERROR_NO_ERROR if the cheat was set
    ///
    virtual GAME_ERROR SetCheat(unsigned int index, bool enabled, const char* code) { return GAME_ERROR_UNKNOWN; }
    //--------------------------------------------------------------------------


    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// The path of the game client being loaded.
    ///
    std::string GameClientDllPath() const { return m_instanceData->props.game_client_dll_path; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// Paths to proxy DLLs used to load the game client.
    ///
    const std::vector<std::string>& ProxyDllPaths() const { return m_proxyDllPaths; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// The "system" directories of the frontend. These directories can be used to
    /// store system-specific ROMs such as BIOSes, configuration data, etc.
    ///
    const std::vector<std::string>& ResourceDirectories() const { return m_resourceDirectories; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// The writable directory of the frontend. This directory can be used to store
    /// SRAM, memory cards, high scores, etc, if the game client cannot use the
    /// regular memory interface, GetMemoryData().
    ///
    std::string ProfileDirectory() const { return m_instanceData->props.profile_directory; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// The value of the <supports_vfs> property from addon.xml
    ///
    bool SupportsVFS() const { return m_instanceData->props.supports_vfs; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// The extensions in the <extensions> property from addon.xml
    ///
    const std::vector<std::string>& Extensions() const { return m_extensions; }
    //--------------------------------------------------------------------------


    // --- Game callbacks --------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Requests the frontend to stop the current game
    ///
    void CloseGame(void)
    {
      return m_instanceData->toKodi.close_game(m_instanceData->toKodi.kodiInstance);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Create a video stream for pixel data
    ///
    /// @param format The type of pixel data accepted by this stream
    /// @param width The frame width
    /// @param height The frame height
    /// @param rotation The rotation (counter-clockwise) of the video frames
    ///
    /// @return 0 on success or -1 if a video stream is already created
    ///
    bool OpenPixelStream(GAME_PIXEL_FORMAT format, unsigned int width, unsigned int height, GAME_VIDEO_ROTATION rotation)
    {
      return m_instanceData->toKodi.open_pixel_stream(m_instanceData->toKodi.kodiInstance, format, width, height, rotation) == 0;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Create a video stream for encoded video data
    ///
    /// @param codec The video format accepted by this stream
    ///
    /// @return 0 on success or -1 if a video stream is already created
    ///
    bool OpenVideoStream(GAME_VIDEO_CODEC codec)
    {
      return m_instanceData->toKodi.open_video_stream(m_instanceData->toKodi.kodiInstance, codec) == 0;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Create an audio stream for PCM audio data
    ///
    /// @param format The type of audio data accepted by this stream
    /// @param channel_map The channel layout terminated by GAME_CH_NULL
    ///
    /// @return 0 on success or -1 if an audio stream is already created
    ////
    bool OpenPCMStream(GAME_PCM_FORMAT format, const GAME_AUDIO_CHANNEL* channel_map)
    {
      return m_instanceData->toKodi.open_pcm_stream(m_instanceData->toKodi.kodiInstance, format, channel_map) == 0;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Create an audio stream for encoded audio data
    ///
    /// @param codec The audio format accepted by this stream
    /// @param channel_map The channel layout terminated by GAME_CH_NULL
    ///
    /// @return 0 on success or -1 if an audio stream is already created
    ///
    bool OpenAudioStream(GAME_AUDIO_CODEC codec, const GAME_AUDIO_CHANNEL* channel_map)
    {
      return m_instanceData->toKodi.open_audio_stream(m_instanceData->toKodi.kodiInstance, codec, channel_map) == 0;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Add a data packet to an audio or video stream
    ///
    /// @param stream The target stream
    /// @param data The data packet
    /// @param size The size of the data
    ///
    void AddStreamData(GAME_STREAM_TYPE stream, const uint8_t* data, unsigned int size)
    {
      m_instanceData->toKodi.add_stream_data(m_instanceData->toKodi.kodiInstance, stream, data, size);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Free the specified stream
    ///
    /// @param stream The stream to close
    ///
    void CloseStream(GAME_STREAM_TYPE stream)
    {
      m_instanceData->toKodi.close_stream(m_instanceData->toKodi.kodiInstance, stream);
    }
    //--------------------------------------------------------------------------

    // -- Hardware rendering callbacks -------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Enable hardware rendering
    ///
    /// @param hw_info A struct of properties for the hardware rendering system
    ///
    void EnableHardwareRendering(const struct game_hw_info* hw_info)
    {
      return m_instanceData->toKodi.enable_hardware_rendering(m_instanceData->toKodi.kodiInstance, hw_info);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Get the framebuffer for rendering
    ///
    /// @return The framebuffer
    ///
    uintptr_t HwGetCurrentFramebuffer(void)
    {
      return m_instanceData->toKodi.hw_get_current_framebuffer(m_instanceData->toKodi.kodiInstance);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Get a symbol from the hardware context
    ///
    /// @param symbol The symbol's name
    ///
    /// @return A function pointer for the specified symbol
    ///
    game_proc_address_t HwGetProcAddress(const char* sym)
    {
      return m_instanceData->toKodi.hw_get_proc_address(m_instanceData->toKodi.kodiInstance, sym);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Called when a frame is being rendered
    ///
    void RenderFrame()
    {
      return m_instanceData->toKodi.render_frame(m_instanceData->toKodi.kodiInstance);
    }
    //--------------------------------------------------------------------------

    // --- Input callbacks -------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Begin reporting events for the specified joystick port
    ///
    /// @param port The zero-indexed port number
    ///
    /// @return true if the port was opened, false otherwise
    ///
    bool OpenPort(unsigned int port)
    {
      return m_instanceData->toKodi.open_port(m_instanceData->toKodi.kodiInstance, port);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief End reporting events for the specified port
    ///
    /// @param port The port number passed to OpenPort()
    ////
    void ClosePort(unsigned int port)
    {
      return m_instanceData->toKodi.close_port(m_instanceData->toKodi.kodiInstance, port);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_game
    /// @brief Notify the port of an input event
    ///
    /// @param event The input event
    ///
    /// Input events can arrive for the following sources:
    ///   - GAME_INPUT_EVENT_MOTOR
    ///
    /// @return true if the event was handled, false otherwise
    ///
    bool InputEvent(const game_input_event& event)
    {
      return m_instanceData->toKodi.input_event(m_instanceData->toKodi.kodiInstance, &event);
    }
    //--------------------------------------------------------------------------

  private:
    void SetAddonStruct(KODI_HANDLE instance)
    {
      if (instance == nullptr)
        throw std::logic_error("kodi::addon::CInstanceGame: Creation with empty addon structure not allowed, table must be given from Kodi!");

      m_instanceData = static_cast<AddonInstance_Game*>(instance);
      m_instanceData->toAddon.addon_instance = this;
      m_instanceData->toAddon.load_game = ADDON_load_game;
      m_instanceData->toAddon.load_game_special = ADDON_load_game_special;
      m_instanceData->toAddon.load_standalone = ADDON_load_standalone;
      m_instanceData->toAddon.unload_game = ADDON_unload_game;
      m_instanceData->toAddon.get_game_info = ADDON_get_game_info;
      m_instanceData->toAddon.get_region = ADDON_get_region;
      m_instanceData->toAddon.requires_game_loop = ADDON_requires_game_loop;
      m_instanceData->toAddon.run_frame = ADDON_run_frame;
      m_instanceData->toAddon.reset = ADDON_reset;
      m_instanceData->toAddon.hw_context_reset = ADDON_hw_context_reset;
      m_instanceData->toAddon.hw_context_destroy = ADDON_hw_context_destroy;
      m_instanceData->toAddon.update_port = ADDON_update_port;
      m_instanceData->toAddon.has_feature = ADDON_has_feature;
      m_instanceData->toAddon.input_event = ADDON_input_event;
      m_instanceData->toAddon.serialize_size = ADDON_serialize_size;
      m_instanceData->toAddon.serialize = ADDON_serialize;
      m_instanceData->toAddon.deserialize = ADDON_deserialize;
      m_instanceData->toAddon.cheat_reset = ADDON_cheat_reset;
      m_instanceData->toAddon.get_memory = ADDON_get_memory;
      m_instanceData->toAddon.set_cheat = ADDON_set_cheat;

      for (unsigned int i = 0; i < m_instanceData->props.resource_directory_count; ++i)
      {
        if (m_instanceData->props.resource_directories[i] == nullptr)
          break;
        if (strlen(m_instanceData->props.resource_directories[i]) == 0)
          continue;
        std::string path = m_instanceData->props.resource_directories[i];
        kodi::vfs::RemoveSlashAtEnd(path);
        m_resourceDirectories.push_back(path);
      }

      for (unsigned int i = 0; i < m_instanceData->props.proxy_dll_count; ++i)
      {
        if (m_instanceData->props.proxy_dll_paths[i] == nullptr)
          break;
        if (strlen(m_instanceData->props.proxy_dll_paths[i]) == 0)
          continue;
        std::string path = m_instanceData->props.proxy_dll_paths[i];
        m_proxyDllPaths.push_back(m_instanceData->props.proxy_dll_paths[i]);
      }

      for (unsigned int i = 0; i < m_instanceData->props.extension_count; ++i)
      {
        if (m_instanceData->props.extensions[i] == nullptr)
          break;
        if (strlen(m_instanceData->props.extensions[i]) == 0)
          continue;
        m_extensions.push_back(m_instanceData->props.extensions[i]);
      }
    }

    static inline GAME_ERROR ADDON_load_game(const AddonInstance_Game* instance, const char* url)
    {
      return instance->toAddon.addon_instance->LoadGame(url);
    }

    static inline GAME_ERROR ADDON_load_game_special(const AddonInstance_Game* instance, SPECIAL_GAME_TYPE type, const char** urls, size_t url_count)
    {
      if (urls == nullptr || url_count == 0)
        return GAME_ERROR_INVALID_PARAMETERS;

      std::vector<std::string> urlList;
      for (unsigned int i = 0; i < url_count; ++i)
      {
        if (urls[i] == nullptr)
          return GAME_ERROR_INVALID_PARAMETERS;
        urlList.push_back(urls[i]);
      }

      return instance->toAddon.addon_instance->LoadGameSpecial(type, urlList);
    }

    static inline GAME_ERROR ADDON_load_standalone(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->LoadStandalone();
    }

    static inline GAME_ERROR ADDON_unload_game(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->UnloadGame();
    }

    static inline GAME_ERROR ADDON_get_game_info(const AddonInstance_Game* instance, game_system_av_info* info)
    {
      return instance->toAddon.addon_instance->GetGameInfo(*info);
    }

    static inline GAME_REGION ADDON_get_region(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->GetRegion();
    }

    static inline bool ADDON_requires_game_loop(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->RequiresGameLoop();
    }

    static inline GAME_ERROR ADDON_run_frame(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->RunFrame();
    }

    static inline GAME_ERROR ADDON_reset(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->Reset();
    }

    static inline GAME_ERROR ADDON_hw_context_reset(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->HwContextReset();
    }

    static inline GAME_ERROR ADDON_hw_context_destroy(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->HwContextDestroy();
    }

    static inline void ADDON_update_port(const AddonInstance_Game* instance, int port, bool connected, const game_controller* controller)
    {
      return instance->toAddon.addon_instance->UpdatePort(port, connected, controller);
    }

    static inline bool ADDON_has_feature(const AddonInstance_Game* instance, const char* controller_id, const char* feature_name)
    {
      return instance->toAddon.addon_instance->HasFeature(controller_id, feature_name);
    }

    static inline bool ADDON_input_event(const AddonInstance_Game* instance, const game_input_event* event)
    {
      return instance->toAddon.addon_instance->InputEvent(event);
    }

    static inline size_t ADDON_serialize_size(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->SerializeSize();
    }

    static inline GAME_ERROR ADDON_serialize(const AddonInstance_Game* instance, uint8_t* data, size_t size)
    {
      return instance->toAddon.addon_instance->Serialize(data, size);
    }

    static inline GAME_ERROR ADDON_deserialize(const AddonInstance_Game* instance, const uint8_t* data, size_t size)
    {
      return instance->toAddon.addon_instance->Deserialize(data, size);
    }

    static inline GAME_ERROR ADDON_cheat_reset(const AddonInstance_Game* instance)
    {
      return instance->toAddon.addon_instance->CheatReset();
    }

    static inline GAME_ERROR ADDON_get_memory(const AddonInstance_Game* instance, GAME_MEMORY type, uint8_t** data, size_t* size)
    {
      return instance->toAddon.addon_instance->GetMemory(type, data, size);
    }

    static inline GAME_ERROR ADDON_set_cheat(const AddonInstance_Game* instance, unsigned int index, bool enabled, const char* code)
    {
      return instance->toAddon.addon_instance->SetCheat(index, enabled, code);
    }

    AddonInstance_Game* m_instanceData;
    std::vector<std::string> m_proxyDllPaths;
    std::vector<std::string> m_resourceDirectories;
    std::vector<std::string> m_extensions;
  };

} /* namespace addon */
} /* namespace kodi */
