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

/*
 * Parts with a comment named "internal" are only used inside header and not
 * used or accessed direct during add-on development!
 */

#include "../AddonBase.h"

namespace kodi { namespace addon { class CInstanceVisualization; }}

extern "C"
{

struct AddonInstance_Visualization;

typedef enum VIS_ACTION : unsigned int /* internal */
{ 
  VIS_ACTION_NONE = 0,
  VIS_ACTION_NEXT_PRESET,
  VIS_ACTION_PREV_PRESET,
  VIS_ACTION_LOAD_PRESET,
  VIS_ACTION_RANDOM_PRESET,
  VIS_ACTION_LOCK_PRESET,
  VIS_ACTION_RATE_PRESET_PLUS,
  VIS_ACTION_RATE_PRESET_MINUS,
  VIS_ACTION_UPDATE_ALBUMART,
  VIS_ACTION_UPDATE_TRACK
} VIS_ACTION;

struct VIS_INFO /* internal */
{
  bool bWantsFreq;
  int iSyncDelay;
};

typedef struct AddonProps_Visualization /* internal */
{
  void *device;
  int x;
  int y;
  int width;
  int height;
  float pixelRatio;
  const char *name;
  const char *presets;
  const char *profile;
} AddonProps_Visualization;

typedef struct AddonToKodiFuncTable_Visualization /* internal */
{
  KODI_HANDLE kodiInstance;
  void (__cdecl* transfer_preset) (void* kodiInstance, const char* preset);
} AddonToKodiFuncTable_Visualization;

typedef struct KodiToAddonFuncTable_Visualization /* internal */
{
  kodi::addon::CInstanceVisualization* addonInstance;
  bool (__cdecl* start)(const AddonInstance_Visualization* instance, int channels, int samples_per_sec, int bits_per_sample, const char* song_name);
  void (__cdecl* stop)(const AddonInstance_Visualization* instance);
  void (__cdecl* audio_data)(const AddonInstance_Visualization* instance, const float* audio_data, int audio_data_length, float *freq_data, int freq_data_length);
  bool (__cdecl* is_dirty)(const AddonInstance_Visualization* instance);
  void (__cdecl* render)(const AddonInstance_Visualization* instance);
  void (__cdecl* get_info)(const AddonInstance_Visualization* instance, VIS_INFO *info);
  bool (__cdecl* on_action)(const AddonInstance_Visualization* instance, VIS_ACTION action, const void *param);
  unsigned int (__cdecl *get_presets)(const AddonInstance_Visualization* instance);
  int (__cdecl *get_active_preset)(const AddonInstance_Visualization* instance);
  bool (__cdecl* is_locked)(const AddonInstance_Visualization* instance);
} KodiToAddonFuncTable_Visualization;

typedef struct AddonInstance_Visualization /* internal */
{
  AddonProps_Visualization props;
  AddonToKodiFuncTable_Visualization toKodi;
  KodiToAddonFuncTable_Visualization toAddon;
} AddonInstance_Visualization;

//============================================================================
/// \defgroup cpp_kodi_addon_visualization_VisTrack class VisTrack
/// \ingroup cpp_kodi_addon_visualization
/// @brief **Visualization track information structure**
///
/// Becomes given on kodi::addon::CInstanceVisualization::UpdateTrack() call to have on
/// information of currently played song.
///
//@{
struct VisTrack
{
  /// @brief Title of the currently playing song
  const char *title;

  /// @brief Get artist names from the artist decription string (if it exists)
  /// as a single string
  const char *artist;

  /// @brief Album from which the current song is from
  const char *album;

  /// @brief Album artist names from the artist decription string (if it
  /// exists) as a single string.
  const char *albumArtist;

  /// @brief Shows the genre of the currently playing artist
  const char *genre;

  /// @brief Comment of current song stored in ID tag info
  const char *comment;

  /// @brief Lyrics of the currently played song if available
  const char *lyrics;

  const char *reserved1;
  const char *reserved2;

  /// @brief Track number of current song
  int trackNumber;

  /// @brief Disc Number of current song stored in ID tag info
  int discNumber;

  /// @brief Duration of song in seconds
  int duration;

  /// @brief Year of release of current song
  int year;

  /// @brief The from user defined rating of song
  int rating;

  int reserved3;
  int reserved4;
};
//@}
//----------------------------------------------------------------------------

} /* extern "C" */

namespace kodi
{
namespace addon
{

  //============================================================================
  ///
  /// \addtogroup cpp_kodi_addon_visualization
  /// @brief \cpp_class{ kodi::addon::CInstanceVisualization }
  /// **Visualization add-on instance**
  ///
  /// [Music visualization](https://en.wikipedia.org/wiki/Music_visualization)
  /// or music visualisation, a feature in Kodi, generates animated imagery
  /// based on a piece of music. The imagery is usually generated and rendered
  /// in real time and in a way synchronized with the music as it is played.
  ///
  /// Visualization techniques range from simple ones (e.g., a simulation of an
  /// oscilloscope display) to elaborate ones, which often include a plurality
  /// of composited effects. The changes in the music's loudness and frequency
  /// spectrum are among the properties used as input to the visualization.
  ///
  /// It has the header \ref Visualization.h "#include <kodi/visualization/Visualization.h>"
  /// be included to enjoy it.
  ///
  /// This interface allow the creating of a visualizations for Kodi, based upon
  /// **DirectX** or/and **OpenGL** rendering with `C++` code.
  ///
  /// The interface have big possibility. By transferring the many different
  /// data, almost everything can be possible to use items of the respective
  /// title.
  ///
  /// Further are several \ref cpp_kodi_addon_visualization_CB "other functions"
  /// available where the child class can ask about used device, display and
  /// few other parts.
  ///
  /// --------------------------------------------------------------------------
  ///
  ///
  /// **Here as example what is minimum required to start on a visualization:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/visualization/Visualization.h>
  ///
  /// class CMyVisualization : public kodi::addon::CAddonBase,
  ///                          public kodi::addon::CInstanceVisualization
  /// {
  /// public:
  ///   CMyVisualization();
  ///
  ///   bool Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName) override;
  ///   void AudioData(const float* audioData, int audioDataLength, float* freqData, int freqDataLength) override;
  ///   void Render() override;
  /// };
  ///
  /// CMyVisualization::CMyVisualization()
  /// {
  ///   ...
  /// }
  ///
  /// bool CMyVisualization::Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName)
  /// {
  ///   ...
  ///   return true;
  /// }
  ///
  /// void CMyVisualization::AudioData(const float* audioData, int audioDataLength, float* freqData, int freqDataLength)
  /// {
  ///   ...
  /// }
  ///
  /// void CMyVisualization::Render()
  /// {
  ///   ...
  /// }
  ///
  /// ADDONCREATOR(CMyVisualization)
  /// ~~~~~~~~~~~~~
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  ///
  /// **Here another example where visualization becomes used together with other instance types:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/visualization/Visualization.h>
  ///
  /// class CMyVisualization : public ::kodi::addon::CInstanceVisualization
  /// {
  /// public:
  ///   CMyVisualization(void* instance);
  ///
  ///   bool Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName) override;
  ///   void AudioData(const float* audioData, int audioDataLength, float* freqData, int freqDataLength) override;
  ///   void Render() override;
  /// };
  ///
  /// CMyVisualization::CMyVisualization(void* instance)
  ///   : CInstanceVisualization(instance)
  /// {
  ///   ...
  /// }
  ///
  /// bool CMyVisualization::Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName)
  /// {
  ///   ...
  ///   return true;
  /// }
  ///
  /// void CMyVisualization::AudioData(const float* audioData, int audioDataLength, float* freqData, int freqDataLength)
  /// {
  ///   ...
  /// }
  ///
  /// void CMyVisualization::Render()
  /// {
  ///   ...
  /// }
  ///
  ///
  /// /*----------------------------------------------------------------------*/
  ///
  /// class CMyAddon : public ::kodi::addon::CAddonBase
  /// {
  /// public:
  ///   CMyAddon() { }
  ///   ADDON_STATUS CreateInstance(int instanceType,
  ///                               std::string instanceID,
  ///                               KODI_HANDLE instance,
  ///                               KODI_HANDLE& addonInstance) override;
  /// };
  ///
  /// /* If you use only one instance in your add-on, can be instanceType and
  ///  * instanceID ignored */
  /// ADDON_STATUS CMyAddon::CreateInstance(int instanceType,
  ///                                       std::string instanceID,
  ///                                       KODI_HANDLE instance,
  ///                                       KODI_HANDLE& addonInstance)
  /// {
  ///   if (instanceType == ADDON_INSTANCE_VISUALIZATION)
  ///   {
  ///     kodi::Log(ADDON_LOG_NOTICE, "Creating my Visualization");
  ///     addonInstance = new CMyVisualization(instance);
  ///     return ADDON_STATUS_OK;
  ///   }
  ///   else if (...)
  ///   {
  ///     ...
  ///   }
  ///   return ADDON_STATUS_UNKNOWN;
  /// }
  ///
  /// ADDONCREATOR(CMyAddon)
  /// ~~~~~~~~~~~~~
  ///
  /// The **desctruction** of the here created example class `CMyVisualization`
  /// becomes done from Kodi's header and never for add-on instances a delete on
  /// add-on itself necessary.
  ///
  //----------------------------------------------------------------------------
  class CInstanceVisualization : public IAddonInstance
  {
  public:
    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Visualization class constructor
    ///
    /// Used on addon who supports only visualization and CAddonBase is also
    /// included as parent.
    ///
    CInstanceVisualization()
      : IAddonInstance(ADDON_INSTANCE_VISUALIZATION),
        m_presetLockedByUser(false)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceVisualization: Cannot create multiple instances of add-on.");

      SetAddonStruct(CAddonBase::m_interface->firstKodiInstance);
      CAddonBase::m_interface->globalSingleInstance = this;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Visualization class constructor used to support multiple instance
    /// types
    ///
    /// @param[in] instance               The with <b>`kodi::addon::CAddonBase::CreateInstance(...)`</b>
    ///                                   given `instance` value.
    ///
    /// @warning Use always only `instance` value from CreateInstance call
    ///
    CInstanceVisualization(KODI_HANDLE instance)
      : IAddonInstance(ADDON_INSTANCE_VISUALIZATION),
        m_presetLockedByUser(false)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceVisualization: Creation of multiple together with single instance way is not allowed!");

      SetAddonStruct(instance);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Destructor
    ///
    ~CInstanceVisualization() override = default;
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief To notify visualization. that new song has been started
    ///
    /// It pass the number of audio channels, sample rate, bits/sample and
    /// offcourse the songname.
    ///
    /// @param[in] channels             Amount of channels on stream
    /// @param[in] samplesPerSec        Samples per second on stream
    /// @param[in] bitsPerSample        Amount of bits on one sample
    /// @param[in] songName             The name of the currently played song
    ///
    virtual bool Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName) { return true; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief To inform about stop of rendering control
    ///
    virtual void Stop() {}
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Pass audio data to visualization
    ///
    /// @param[in] audioData            is short audiodata [channel][audioDataLength]
    ///                                 containing the raw audio data
    /// @param[in] audioDataLength      length of audiodata array
    /// @param[in] freqData             fft-ed audio data
    /// @param[in] freqDataLength       length of frequeny data array
    ///
    /// Values **freqData** and **freqDataLength** becomes used if on GetInfo()
    /// the `wantsFreq` is set to true, otherwise is **freqData** = `nullptr`
    /// and **freqDataLength** = `0`.
    ///
    virtual void AudioData(const float* audioData, int audioDataLength, float* freqData, int freqDataLength) {}
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief To inform Kodi rendered region is dirty and need update
    ///
    /// @return true if dirty
    ///
    virtual bool IsDirty() { return true; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief To handle rendering time on add-on
    ///
    virtual void Render() {}
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief To get the number of buffers from the current visualization
    ///
    /// @param[out] wantsFreq           Fourier transform the data if the wants it.
    ///                                 If set to true are the values
    ///                                 **freqData** and **freqDataLength** on
    ///                                 AudioData() used.
    /// @param[out] syncDelay           Number of buffers from the current
    ///
    /// @note If function becomes not used is as defaults from parent the
    /// `wantsFreq` = false and the `syncDelay` = 0.
    ///
    virtual void GetInfo(bool& wantsFreq, int& syncDelay) { wantsFreq = false; syncDelay = 0; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief To get a list of selectable visualization presets on add-on
    ///
    /// @param[out] presets             Vector list with selectable names of
    ///                                 presets
    /// @return                         Return true if successfull done
    ///
    virtual bool GetPresets(std::vector<std::string>& presets) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Get the index of currently used preset on visualization add-on
    ///
    /// @return                         Index number
    ///
    virtual int GetActivePreset() { return -1; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief To ask add-on is locked on current preset
    ///
    /// @return                         True if locked there
    ///
    virtual bool IsLocked() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Load previous visualization preset
    ///
    /// @return                 Return true if it becomes used from you
    virtual bool PrevPreset() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Load next visualization preset
    ///
    /// @return                 Return true if it becomes used from you
    virtual bool NextPreset() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Load visualization preset
    ///
    /// Becomes send after new select is requested.
    ///
    /// @param[in] select       Preset index to use
    /// @return                 Return true if the load becomes used from you
    virtual bool LoadPreset(int select) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Switch to a new random preset
    ///
    /// @return                 Return true if the random becomes used from you
    virtual bool RandomPreset() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Lock the current visualization preset on add-on if selected from
    /// user
    ///
    /// @param[in] lockUnlock   If set to true is the preset is needed to lock
    ///                         there
    /// @return                 Return true if the lock becomes used from you
    virtual bool LockPreset(bool lockUnlock) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Used to increase/decrease track rating in full screen playback
    ///
    /// Press info on track and use pageplus or pageminus on keyboard/remote.
    ///
    /// @param[in] plusMinus    If set to true is the rate increased, otherwise
    ///                         decreased
    /// @return                 Return true if the rate becomes used from you
    virtual bool RatePreset(bool plusMinus) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Inform the visualization of the current album art image
    ///
    /// @param[in] albumart     Path to the current album art image
    /// @return                 Return true if the image becomes used from you
    virtual bool UpdateAlbumart(std::string albumart) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization
    /// @brief Inform the visualization of the current track's tag information
    ///
    /// @param[in] track        Visualization track information structure
    /// @return                 Return true if it becomes used from you
    virtual bool UpdateTrack(const VisTrack &track) { return false; }

    //==========================================================================
    ///
    /// \defgroup cpp_kodi_addon_visualization_CB Information functions
    /// \ingroup cpp_kodi_addon_visualization
    /// @brief **To get info about device, display and few other parts**
    ///
    //@{

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief Device that represents the display adapter
    ///
    /// @return Used device pointer
    ///
    /// @note only be available on **DirectX** and unused (`nullptr`) on
    /// **OpenGL**
    ///
    inline void* Device() { return m_instanceData->props.device; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief Returns the X position of the rendering window
    ///
    /// @return Position X in pixels
    ///
    inline int X() { return m_instanceData->props.x; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief Returns the Y position of the rendering window
    ///
    /// @return Position Y in pixels
    ///
    inline int Y() { return m_instanceData->props.y; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief Returns the width of the rendering window
    ///
    /// @return Width in pixels
    ///
    inline int Width() { return m_instanceData->props.width; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief Returns the height of the rendering window
    ///
    /// @return Height in pixels
    ///
    inline int Height() { return m_instanceData->props.height; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief Pixel aspect ratio (often abbreviated PAR) is a mathematical
    /// ratio that describes how the width of a pixel in a digital image
    /// compares to the height of that pixel.
    ///
    /// @return used Pixel aspect ratio
    ///
    inline float PixelRatio() { return m_instanceData->props.pixelRatio; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief To get the in `addon.xml` defined name of the add-on
    ///
    /// @return Add-on name
    ///
    inline std::string Name() { return m_instanceData->props.name; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief To get the full path where add-on is be installed
    ///
    /// @return Add-on installation path
    ///
    inline std::string Presets() { return m_instanceData->props.presets; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_addon_visualization_CB
    /// @brief To get the full user related path name for the add-on
    ///
    /// @note The folder with his add-on name on end is not created by default,
    /// if it is needed must be one time a kodi::vfs::CreateDirectory()
    /// call performed.
    ///
    /// @return User path name
    ///
    inline std::string Profile() { return m_instanceData->props.profile; }
    //--------------------------------------------------------------------------
    //@}

  private:
    void SetAddonStruct(KODI_HANDLE instance)
    {
      if (instance == nullptr)
        throw std::logic_error("kodi::addon::CInstanceVisualization: Null pointer instance passed.");

      m_instanceData = static_cast<AddonInstance_Visualization*>(instance);
      m_instanceData->toAddon.addonInstance = this;
      m_instanceData->toAddon.start = ADDON_Start;
      m_instanceData->toAddon.stop = ADDON_Stop;
      m_instanceData->toAddon.audio_data = ADDON_AudioData;
      m_instanceData->toAddon.render = ADDON_Render;
      m_instanceData->toAddon.get_info = ADDON_GetInfo;
      m_instanceData->toAddon.on_action = ADDON_OnAction;
      m_instanceData->toAddon.get_presets = ADDON_GetPresets;
      m_instanceData->toAddon.get_active_preset = ADDON_GetActivePreset;
      m_instanceData->toAddon.is_locked = ADDON_IsLocked;
    }

    inline static bool ADDON_Start(const AddonInstance_Visualization* addon, int channels, int samplesPerSec, int bitsPerSample, const char* songName)
    {
      return addon->toAddon.addonInstance->Start(channels, samplesPerSec, bitsPerSample, songName);
    }

    inline static void ADDON_Stop(const AddonInstance_Visualization* addon)
    {
      addon->toAddon.addonInstance->Stop();
    }

    inline static void ADDON_AudioData(const AddonInstance_Visualization* addon, const float* audioData, int audioDataLength, float *freqData, int freqDataLength)
    {
      addon->toAddon.addonInstance->AudioData(audioData, audioDataLength, freqData, freqDataLength);
    }
    
    inline static bool ADDON_IsDirty(const AddonInstance_Visualization* addon)
    {
      return addon->toAddon.addonInstance->IsDirty();
    }

    inline static void ADDON_Render(const AddonInstance_Visualization* addon)
    {
      addon->toAddon.addonInstance->Render();
    }

    inline static void ADDON_GetInfo(const AddonInstance_Visualization* addon, VIS_INFO *info)
    {
      addon->toAddon.addonInstance->GetInfo(info->bWantsFreq, info->iSyncDelay);
    }

    inline static bool ADDON_OnAction(const AddonInstance_Visualization* addon, VIS_ACTION action, const void *param)
    {
      switch (action)
      {
        case VIS_ACTION_NEXT_PRESET:
          return addon->toAddon.addonInstance->NextPreset();
        case VIS_ACTION_PREV_PRESET:
          return addon->toAddon.addonInstance->PrevPreset();
        case VIS_ACTION_LOAD_PRESET:
          return addon->toAddon.addonInstance->LoadPreset(*static_cast<const int*>(param));
        case VIS_ACTION_RANDOM_PRESET:
          return addon->toAddon.addonInstance->RandomPreset();
        case VIS_ACTION_LOCK_PRESET:
          addon->toAddon.addonInstance->m_presetLockedByUser = !addon->toAddon.addonInstance->m_presetLockedByUser;
          return addon->toAddon.addonInstance->LockPreset(addon->toAddon.addonInstance->m_presetLockedByUser);
        case VIS_ACTION_RATE_PRESET_PLUS:
          return addon->toAddon.addonInstance->RatePreset(true);
        case VIS_ACTION_RATE_PRESET_MINUS:
          return addon->toAddon.addonInstance->RatePreset(false);
        case VIS_ACTION_UPDATE_ALBUMART:
          return addon->toAddon.addonInstance->UpdateAlbumart(static_cast<const char*>(param));
        case VIS_ACTION_UPDATE_TRACK:
          return addon->toAddon.addonInstance->UpdateTrack(*static_cast<const VisTrack*>(param));
        case VIS_ACTION_NONE:
        default:
          break;
      }
      return false;
    }

    inline static unsigned int ADDON_GetPresets(const AddonInstance_Visualization* addon)
    {
      std::vector<std::string> presets;
      if (addon->toAddon.addonInstance->GetPresets(presets))
      {
        for (auto it : presets)
          addon->toAddon.addonInstance->m_instanceData->toKodi.transfer_preset(addon->toKodi.kodiInstance, it.c_str());
      }

      return presets.size();
    }

    inline static int ADDON_GetActivePreset(const AddonInstance_Visualization* addon)
    {
      return addon->toAddon.addonInstance->GetActivePreset();
    }

    inline static bool ADDON_IsLocked(const AddonInstance_Visualization* addon)
    {
      return addon->toAddon.addonInstance->IsLocked();
    }

    bool m_presetLockedByUser;
    AddonInstance_Visualization* m_instanceData;
  };

} /* namespace addon */
} /* namespace kodi */
