#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "xbmc_pvr_types.h"
#include <algorithm>
#include <map>
#include "kodi/addon.api2/General.h"
#include "internal/libKODI_addon_StreamUtilsHead.h"

namespace AddOnLIB
{
namespace V2
{
  /**
   * Represents a single stream. It extends the PODS to provide some operators
   * overloads.
   */
  class CPVRStream : public PVR_STREAM_PROPERTIES::PVR_STREAM
  {
  public:
    CPVRStream();
    CPVRStream(const CPVRStream &other);

    CPVRStream& operator=(const CPVRStream &other);

    /**
     * Compares this stream based on another stream
     * @param other
     * @return
     */
    bool operator==(const CPVRStream &other) const;

    /**
     * Compares this stream with another one so that video streams are sorted
     * before any other streams and the others are sorted by the physical ID
     * @param other
     * @return
     */
    bool operator<(const CPVRStream &other) const;

    /**
     * Clears the stream
     */
     void Clear();

    /**
     * Checks whether the stream has been cleared
     * @return true if cleared
     */
    bool IsCleared() const;
  };

  /*\___________________________________________________________________________
  \*/

  class CStreamProperties
  {
  public:
    typedef std::vector<CPVRStream> stream_vector;

    CStreamProperties(void);
    virtual ~CStreamProperties(void);

    /**
     * Resets the streams
     */
    void Clear(void);

    /**
     * Returns the index of the stream with the specified physical ID, or -1 if
     * there no stream is found. This method is called very often which is why
     * we keep a separate map for this.
     * @param iPhysicalId
     * @return
     */
    int GetStreamId(unsigned int iPhysicalId) const;

    /**
     * Returns the stream with the specified physical ID, or null if no such
     * stream exists
     * @param iPhysicalId
     * @return
     */
    CPVRStream* GetStreamById(unsigned int iPhysicalId) const;

    /**
     * Populates the specified stream with the stream having the specified
     * physical ID. If the stream is not found only target stream's physical ID
     * will be populated.
     * @param iPhysicalId
     * @param stream
     */
    void GetStreamData(unsigned int iPhysicalId, CPVRStream* stream);

    /**
     * Populates props with the current streams and returns whether there are
     * any streams at the moment or not.
     * @param props
     * @return
     */
    bool GetProperties(PVR_STREAM_PROPERTIES* props);

    /**
     * Merges new streams into the current list of streams. Identical streams
     * will retain their respective indexes and new streams will replace unused
     * indexes or be appended.
     * @param newStreams
     */
    void UpdateStreams(stream_vector &newStreams);

    IMPL_STREAM_PROPS;
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_StreamUtils.hpp"
