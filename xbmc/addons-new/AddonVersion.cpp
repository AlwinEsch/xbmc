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

#include "AddonVersion.h"

#include "utils/StringUtils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

namespace ADDON_NEW
{
  AddonVersion::AddonVersion(const std::string& version)
  : m_epoch(0), m_upstream(version.empty() ? "0.0.0" : version)
  {
    size_t pos = m_upstream.find(':');
    if (pos != std::string::npos)
    {
      m_epoch = strtol(m_upstream.c_str(), nullptr, 10);
      m_upstream.erase(0, pos+1);
    }

    pos = m_upstream.find('-');
    if (pos != std::string::npos)
    {
      m_revision = m_upstream.substr(pos+1);
      m_upstream.erase(pos);
    }
  }

  /**Compare two components of a Debian-style version.  Return -1, 0, or 1
   * if a is less than, equal to, or greater than b, respectively.
   */
  int AddonVersion::CompareComponent(const char *a, const char *b)
  {
    while (*a && *b)
    {
      while (*a && *b && !isdigit(*a) && !isdigit(*b))
      {
        if (*a != *b)
        {
          if (*a == '~')
            return -1;
          if (*b == '~')
            return 1;
          return *a < *b ? -1 : 1;
        }
        a++;
        b++;
      }
      if (*a && *b && (!isdigit(*a) || !isdigit(*b)))
      {
        if (*a == '~')
          return -1;
        if (*b == '~')
          return 1;
        return isdigit(*a) ? -1 : 1;
      }

      char *next_a, *next_b;
      long int num_a = strtol(a, &next_a, 10);
      long int num_b = strtol(b, &next_b, 10);
      if (num_a != num_b)
        return num_a < num_b ? -1 : 1;

      a = next_a;
      b = next_b;
    }
    if (!*a && !*b)
      return 0;
    if (*a)
      return *a == '~' ? -1 : 1;
    else
      return *b == '~' ? 1 : -1;
  }

  bool AddonVersion::operator<(const AddonVersion& other) const
  {
    if (m_epoch != other.m_epoch)
      return m_epoch < other.m_epoch;

    int result = CompareComponent(m_upstream.c_str(), other.m_upstream.c_str());
    if (result)
      return (result < 0);

    return (CompareComponent(m_revision.c_str(), other.m_revision.c_str()) < 0);
  }

  bool AddonVersion::operator>(const AddonVersion & other) const
  {
    return !(*this <= other);
  }

  bool AddonVersion::operator==(const AddonVersion& other) const
  {
    return m_epoch == other.m_epoch
      && CompareComponent(m_upstream.c_str(), other.m_upstream.c_str()) == 0
      && CompareComponent(m_revision.c_str(), other.m_revision.c_str()) == 0;
  }

  bool AddonVersion::operator!=(const AddonVersion & other) const
  {
    return !(*this == other);
  }

  bool AddonVersion::operator<=(const AddonVersion& other) const
  {
    return *this < other || *this == other;
  }

  bool AddonVersion::operator>=(const AddonVersion & other) const
  {
    return !(*this < other);
  }

  bool AddonVersion::empty() const
  {
    return m_epoch == 0 && m_upstream == "0.0.0" && m_revision.empty();
  }

  std::string AddonVersion::asString() const
  {
    std::string out;
    if (m_epoch)
      out = StringUtils::Format("%i:", m_epoch);
    out += m_upstream;
    if (!m_revision.empty())
      out += "-" + m_revision;
    return out;
  }

  bool AddonVersion::SplitFileName(std::string& ID, std::string& version,
                                   const std::string& filename)
  {
    size_t dpos = filename.rfind("-");
    if (dpos == std::string::npos)
      return false;
    ID = filename.substr(0, dpos);
    version = filename.substr(dpos + 1);
    version = version.substr(0, version.size() - 4);

    return true;
  }
}
