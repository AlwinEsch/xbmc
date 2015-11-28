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

#include "PlatformDefs.h" // for __stat64, ssize_t
#include "addon.api2/AddonLib.h"

extern "C"
{
namespace AddOnLIB
{
namespace V2
{

class CAddonCB_Directory
{
public:
  CAddonCB_Directory();

  void Init(CB_AddOn_Directory *callbacks);

  static bool can_open_directory(
        void*                     hdl,
        const char*               strURL);

  static bool create_directory(
        void*                     hdl,
        const char*               strPath);

  static bool directory_exists(
        void*                     hdl,
        const char*               strPath);

  static bool remove_directory(
        void*                     hdl,
        const char*               strPath);

};

}; /* namespace V2 */
}; /* namespace AddOnLIB */
}; /* extern "C" */
