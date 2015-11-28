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
#include "internal/libKODI_guilib_DialogFileBrowserHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUIDialogFileBrowser
  {
  public:
    static bool ShowAndGetDirectory(
          const std::string&      shares,
          const std::string&      heading,
          std::string&            path,
          bool                    bWriteOnly = false);

    static bool ShowAndGetFile(
          const std::string&      shares,
          const std::string&      mask,
          const std::string&      heading,
          std::string&            file,
          bool                    useThumbs = false,
          bool                    useFileDirectories = false);

    static bool ShowAndGetFileFromDir(
          const std::string&      directory,
          const std::string&      mask,
          const std::string&      heading,
          std::string&            strPath,
          bool                    useThumbs = false,
          bool                    useFileDirectories = false,
          bool                    singleList = false);

    static bool ShowAndGetSource(
          std::string&            path,
          bool                    allowNetworkShares,
          const std::string&      additionalShare = nullptr,
          const std::string&      strType = "");

    static bool ShowAndGetImage(
          const std::string&      shares,
          const std::string&      heading,
          std::string&            strPath);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogFileBrowserFunc.h"
