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

#include "definations.h"
#include "internal/libKODI_guilib_DialogNumericHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUIDialogNumeric
  {
  public:
    static bool ShowAndVerifyNewPassword(
          std::string&            strNewPassword);

    static int ShowAndVerifyPassword(
          std::string&            strPassword,
          const std::string&      strHeading,
          int                     iRetries);

    static bool ShowAndVerifyInput(
          std::string&            strPassword,
          const std::string&      strHeading,
          bool                    bGetUserInput);

    static bool ShowAndGetTime(
          tm&                     time,
          const std::string&      strHeading);

    static bool ShowAndGetDate(
          tm&                     date,
          const std::string&      strHeading);

    static bool ShowAndGetIPAddress(
          std::string&            strIPAddress,
          const std::string&      strHeading);

    static bool ShowAndGetNumber(
          std::string&            strInput,
          const std::string&      strHeading,
          unsigned int            iAutoCloseTimeoutMs = 0);

    static bool ShowAndGetSeconds(
          std::string&            strTime,
          const std::string&      strHeading);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogNumericFunc.h"
