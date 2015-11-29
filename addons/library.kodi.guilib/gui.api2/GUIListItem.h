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

#include "internal/libKODI_guilib_internal.h"
#include "internal/libKODI_guilib_ListItemHead.h"

namespace GUILIB
{
namespace V2
{

  class CAddonGUIListItem
  {
  public:
    CAddonGUIListItem(const std::string&      label,
                      const std::string&      label2,
                      const std::string&      iconImage,
                      const std::string&      thumbnailImage,
                      const std::string&      path);
    virtual ~CAddonGUIListItem();

    virtual std::string GetLabel();
    virtual void SetLabel(const std::string& label);

    virtual std::string GetLabel2();
    virtual void SetLabel2(const std::string& label);

    virtual std::string GetIconImage();
    virtual void SetIconImage(const std::string& image);

    virtual std::string GetOverlayImage();
    virtual void SetOverlayImage(unsigned int image, bool bOnOff = false);
    virtual void SetThumbnailImage(const std::string& image);

    virtual void SetSortLabel(const std::string& label);

    virtual void SetArt(const std::string& type, const std::string& url);
    virtual void SetArtFallback(const std::string& from, const std::string& to);
    virtual bool HasArt(const std::string& type);

    virtual bool HasIcon();
    virtual bool HasOverlay();
    virtual bool IsFileItem();
    virtual bool IsFolder();

    virtual void Select(bool bOnOff);
    virtual bool IsSelected();

    virtual void SetProperty(const std::string& key, const std::string& value);
    virtual std::string GetProperty(const std::string& key);
    virtual void IncrementProperty(const std::string& key, int nVal);
    virtual void ClearProperty(const std::string& key);
    virtual void ClearProperties();
    virtual bool HasProperties();
    virtual bool HasProperty(const std::string& key);

    virtual void SetPath(const std::string& path);

    IMPL_ADDON_GUI_LIST;
  };

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ListItemFunc.h"
