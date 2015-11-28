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
#include "internal/libKODI_guilib_DialogKeyboardHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUIDialogKeyboard
  {
  public:
    static bool ShowAndGetInput(
          std::string&            strText,
          const std::string&      strHeading,
          bool                    allowEmptyResult,
          bool                    hiddenInput,
          unsigned int            autoCloseMs = 0);

    static bool ShowAndGetInput(
          std::string&            strText,
          bool                    allowEmptyResult,
          unsigned int            autoCloseMs = 0);

    static bool ShowAndGetNewPassword(
          std::string&            strNewPassword,
          const std::string&      strHeading,
          bool                    allowEmptyResult,
          unsigned int            autoCloseMs = 0);

    static bool ShowAndGetNewPassword(
          std::string&            strNewPassword,
          unsigned int            autoCloseMs = 0);

    static bool ShowAndVerifyNewPassword(
          std::string&            strNewPassword,
          const std::string&      strHeading,
          bool                    allowEmptyResult,
          unsigned int            autoCloseMs = 0);

    static bool ShowAndVerifyNewPassword(
          std::string&            strNewPassword,
          unsigned int            autoCloseMs = 0);

    static int ShowAndVerifyPassword(
          std::string&            strPassword,
          const std::string&      strHeading,
          int                     iRetries,
          unsigned int            autoCloseMs = 0);

    static bool ShowAndGetFilter(
          std::string&            strText,
          bool                    searching,
          unsigned int            autoCloseMs = 0);

    static bool SendTextToActiveKeyboard(
          const std::string&      aTextString,
          bool                    closeKeyboard = false);

    static bool isKeyboardActivated(CHelper_libKODI_guilib* lib);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogKeyboardFunc.h"
