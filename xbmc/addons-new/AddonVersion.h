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
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <string>

namespace ADDON_NEW
{
  /* \brief Addon versioning using the debian versioning scheme

    AddonVersion uses debian versioning, which means in the each section of the period
    separated version string, numbers are compared numerically rather than lexicographically,
    thus any preceding zeros are ignored.

    i.e. 1.00 is considered the same as 1.0, and 1.01 is considered the same as 1.1.

    Further, 1.0 < 1.0.0

    See here for more info: http://www.debian.org/doc/debian-policy/ch-controlfields.html#s-f-Version
    */
  class AddonVersion
  {
  public:
    AddonVersion(const AddonVersion& other) { *this = other; }
    explicit AddonVersion(const std::string& version);
    virtual ~AddonVersion() = default;

    int Epoch() const { return m_epoch; }
    const std::string &Upstream() const { return m_upstream; }
    const std::string &Revision() const { return m_revision; }

    AddonVersion& operator=(const AddonVersion& other);
    bool operator< (const AddonVersion& other) const;
    bool operator> (const AddonVersion& other) const;
    bool operator<=(const AddonVersion& other) const;
    bool operator>=(const AddonVersion& other) const;
    bool operator==(const AddonVersion& other) const;
    bool operator!=(const AddonVersion& other) const;
    std::string asString() const;
    bool empty() const;

    static bool SplitFileName(std::string& ID, std::string& version,
                              const std::string& filename);

  protected:
    int m_epoch;
    std::string m_upstream;
    std::string m_revision;

    static int CompareComponent(const char *a, const char *b);
  };

  inline AddonVersion& AddonVersion::operator=(const AddonVersion& other)
  {
    m_epoch = other.m_epoch;
    m_upstream = other.m_upstream;
    m_revision = other.m_revision;
    return *this;
  }
}
