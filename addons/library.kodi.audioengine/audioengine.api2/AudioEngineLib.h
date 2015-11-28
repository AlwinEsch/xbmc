#pragma once
/*
 *      Copyright (C) 2005-2014 Team KODI
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

#include "internal/libKODI_audioengine_Internal.h"

namespace AudioEngineLIB
{
namespace V2
{

  class CAudioEngineLib : protected CAudioEngineLib_Internal
  {
  public:
    /*!
     * @brief Resolve all callback methods
     * @param handle Pointer to the add-on
     * @return True when all methods were resolved, false otherwise.
     */
    static bool RegisterMe(void *handle);

    /*!
     * @brief Release all callback methods and close handling with them
     */
    static void UnRegisterMe();
    /*\_________________________________________________________________________
    \*/

    /*!
     * @brief Add or replace a menu hook for the context menu for a DSP add-on
     * @param hook The hook to add
     */
    static void AddDSPMenuHook(AE_DSP_MENUHOOK* hook);

    /*!
     * @brief Remove a menu hook for the context menu for this add-on
     * @param hook The hook to remove
     */
    static void RemoveDSPMenuHook(AE_DSP_MENUHOOK* hook);
    /*\_________________________________________________________________________
    \*/

    /*!
     * @brief Add or replace mode information inside audio dsp database.
     * Becomes identifier written inside mode to iModeID if it was 0 (undefined)
     * @param mode The master mode to add or update inside database
     */
    static void RegisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);

    /*!
     * @brief Remove a mode from audio dsp database
     * @param mode The Mode to remove
     */
    static void UnregisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);
    /*\_________________________________________________________________________
    \*/

    /**
     * @brief Get the current sink data format
     *
     * @param Current sink data format. For more details see AudioEngineFormat.
     * @return Returns true on success, else false.
     */
    static bool GetCurrentSinkFormat(AudioEngineFormat &SinkFormat);

    KODI_AUDIOENGINE_LIBRARY;
  };

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
#include "internal/libKODI_audioengine_LibFunc.h"
