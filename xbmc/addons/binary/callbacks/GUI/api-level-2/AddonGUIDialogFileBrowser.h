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

#include "../../../../../../addons/library.kodi.guilib/gui.api2/GUILib.h"

class CMediaSource;

typedef std::vector<CMediaSource> VECSOURCES;

namespace GUILIB
{
namespace V2
{

  struct CB_GUILib;

  struct CAddonGUI_Dialog_FileBrowser
  {
    static void Init(CB_GUILib *callbacks);

    static bool ShowAndGetDirectory(const char   *shares,
                                    const char   *heading,
                                    char         &path,
                                    unsigned int &iMaxStringSize,
                                    bool          bWriteOnly);

    static bool ShowAndGetFile(const char  *shares,
                               const char  *mask,
                               const char  *heading,
                               char        &file,
                               unsigned int &iMaxStringSize,
                               bool         useThumbs,
                               bool         useFileDirectories);

    static bool ShowAndGetFileFromDir(const char   *directory,
                                      const char   *mask,
                                      const char   *heading,
                                      char         &path,
                                      unsigned int &iMaxStringSize,
                                      bool          useThumbs,
                                      bool          useFileDirectories,
                                      bool singleList);

    static bool ShowAndGetSource(char        &path,
                                 unsigned int &iMaxStringSize,
                                 bool         allowNetworkShares,
                                 const char  *additionalShare,
                                 const char  *strType);

    static bool ShowAndGetImage(const char   *shares,
                                const char   *heading,
                                char         &path,
                                unsigned int &iMaxStringSize);

  private:
    static void GetVECShares(VECSOURCES &vecShares, std::string strShares, std::string strPath);
  };

}; /* namespace V2 */
}; /* namespace GUILIB */
