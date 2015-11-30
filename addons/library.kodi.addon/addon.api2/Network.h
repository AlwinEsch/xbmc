#pragma once
/*
 *      Copyright (C) 2015 Team KODI
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

#include <string>

#include "definations.h"
#include "internal/libKODI_addon_NetworkHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{

  class CAddOnLib_Network
  {
  public:
    /*!
     * @brief Send WakeOnLan magic packet.
     * @param mac Network address of the host to wake.
     * @return True if the magic packet was successfully sent, false otherwise.
     */
    static bool WakeOnLan(const char* mac);

    /*!
     * @brief Returns the current ip address as a string.
     * @return The ip.
     */
    static std::string GetIPAddress();

    /*!
     * @brief Encode an URL
     * @param dwCode The code of the message to get.
     * @return Encoded URL string
     */
    static std::string URLEncode(const std::string& url);

    /*!
     * @brief Lookup URL in DNS cache
     * @param strHostName The code of the message to get.
     * @param strIpAddress Returned address
     * @return true if successfull
     */
    static bool DNSLookup(const std::string& strHostName, std::string& strIpAddress);
  }; /* class CAddOnLib_Network */

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_NetworkFunc.h"
