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

#include "FileItem.h"
#include "addons/Addon.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "guilib/GUIListItem.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"
#include "utils/StringUtils.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIListItem.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_ListItem::Init(CB_GUILib *callbacks)
{
  callbacks->ListItem.Create                = CAddonGUI_ListItem::Create;
  callbacks->ListItem.Destroy               = CAddonGUI_ListItem::Destroy;
  callbacks->ListItem.GetLabel              = CAddonGUI_ListItem::GetLabel;
  callbacks->ListItem.SetLabel              = CAddonGUI_ListItem::SetLabel;
  callbacks->ListItem.GetLabel2             = CAddonGUI_ListItem::GetLabel2;
  callbacks->ListItem.SetLabel2             = CAddonGUI_ListItem::SetLabel2;
  callbacks->ListItem.GetIconImage          = CAddonGUI_ListItem::GetIconImage;
  callbacks->ListItem.SetIconImage          = CAddonGUI_ListItem::SetIconImage;
  callbacks->ListItem.GetOverlayImage       = CAddonGUI_ListItem::GetOverlayImage;
  callbacks->ListItem.SetOverlayImage       = CAddonGUI_ListItem::SetOverlayImage;
  callbacks->ListItem.SetThumbnailImage     = CAddonGUI_ListItem::SetThumbnailImage;
  callbacks->ListItem.SetArt                = CAddonGUI_ListItem::SetArt;
  callbacks->ListItem.SetArtFallback        = CAddonGUI_ListItem::SetArtFallback;
  callbacks->ListItem.HasArt                = CAddonGUI_ListItem::HasArt;
  callbacks->ListItem.SetSortLabel          = CAddonGUI_ListItem::SetSortLabel;
  callbacks->ListItem.Select                = CAddonGUI_ListItem::Select;
  callbacks->ListItem.IsSelected            = CAddonGUI_ListItem::IsSelected;
  callbacks->ListItem.HasIcon               = CAddonGUI_ListItem::HasIcon;
  callbacks->ListItem.HasOverlay            = CAddonGUI_ListItem::HasOverlay;
  callbacks->ListItem.IsFileItem            = CAddonGUI_ListItem::IsFileItem;
  callbacks->ListItem.IsFolder              = CAddonGUI_ListItem::IsFolder;
  callbacks->ListItem.SetProperty           = CAddonGUI_ListItem::SetProperty;
  callbacks->ListItem.GetProperty           = CAddonGUI_ListItem::GetProperty;
  callbacks->ListItem.IncrementProperty     = CAddonGUI_ListItem::IncrementProperty;
  callbacks->ListItem.ClearProperty         = CAddonGUI_ListItem::ClearProperty;
  callbacks->ListItem.ClearProperties       = CAddonGUI_ListItem::ClearProperties;
  callbacks->ListItem.HasProperties         = CAddonGUI_ListItem::HasProperties;
  callbacks->ListItem.HasProperty           = CAddonGUI_ListItem::HasProperty;
  callbacks->ListItem.SetPath               = CAddonGUI_ListItem::SetPath;
}

GUIHANDLE CAddonGUI_ListItem::Create(void *addonData, const char *label, const char *label2, const char *iconImage, const char *thumbnailImage, const char *path)
{
  // create CFileItem
  CFileItem *pItem = new CFileItem();
  if (!pItem)
    return nullptr;

  if (label)
    pItem->SetLabel(label);
  if (label2)
    pItem->SetLabel2(label2);
  if (iconImage)
    pItem->SetIconImage(iconImage);
  if (thumbnailImage)
    pItem->SetArt("thumb", thumbnailImage);
  if (path)
    pItem->SetPath(path);

  return pItem;
}

void CAddonGUI_ListItem::Destroy(void *addonData, GUIHANDLE handle)
{
  // @note: Delete of CFileItem brings crash, need to check about the in related
  // window and no memleak present to confirm.
  // In old version was the same way, only the Destroy passed here to allow
  // changes and fixes without API level changes.
}

void CAddonGUI_ListItem::GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonGUI_General::Lock();
  strncpy(&label, static_cast<CFileItem *>(handle)->GetLabel().c_str(), iMaxStringSize);
  CAddonGUI_General::Unlock();
  iMaxStringSize = static_cast<CFileItem *>(handle)->GetLabel().length();
}

void CAddonGUI_ListItem::SetLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetLabel(label);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::GetLabel2(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonGUI_General::Lock();
  strncpy(&label, static_cast<CFileItem *>(handle)->GetLabel2().c_str(), iMaxStringSize);
  CAddonGUI_General::Unlock();
  iMaxStringSize = static_cast<CFileItem *>(handle)->GetLabel2().length();
}

void CAddonGUI_ListItem::SetLabel2(void *addonData, GUIHANDLE handle, const char *label)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetLabel2(label);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::GetIconImage(void *addonData, GUIHANDLE handle, char &image, unsigned int &iMaxStringSize)
{
  CAddonGUI_General::Lock();
  strncpy(&image, static_cast<CFileItem *>(handle)->GetIconImage().c_str(), iMaxStringSize);
  CAddonGUI_General::Unlock();
  iMaxStringSize = static_cast<CFileItem *>(handle)->GetIconImage().length();
}

void CAddonGUI_ListItem::SetIconImage(void *addonData, GUIHANDLE handle, const char *image)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetIconImage(image);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::GetOverlayImage(void *addonData, GUIHANDLE handle, char &image, unsigned int &iMaxStringSize)
{
  CAddonGUI_General::Lock();
  strncpy(&image, static_cast<CFileItem *>(handle)->GetOverlayImage().c_str(), iMaxStringSize);
  CAddonGUI_General::Unlock();
  iMaxStringSize = static_cast<CFileItem *>(handle)->GetOverlayImage().length();
}

void CAddonGUI_ListItem::SetOverlayImage(void *addonData, GUIHANDLE handle, unsigned int image, bool bOnOff /* = false*/)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetOverlayImage((CGUIListItem::GUIIconOverlay)image, bOnOff);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::SetThumbnailImage(void *addonData, GUIHANDLE handle, const char *image)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetArt("thumb", image);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::SetArt(void *addonData, GUIHANDLE handle, const char *type, const char *url)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetArt(type, url);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::SetArtFallback(void *addonData, GUIHANDLE handle, const char *from, const char *to)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetArtFallback(from, to);
  CAddonGUI_General::Unlock();
}

bool CAddonGUI_ListItem::HasArt(void *addonData, GUIHANDLE handle, const char *type)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->HasArt(type);
  CAddonGUI_General::Unlock();
  return ret;
}

void CAddonGUI_ListItem::SetSortLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetSortLabel(label);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::Select(void *addonData, GUIHANDLE handle, bool bOnOff)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->Select(bOnOff);
  CAddonGUI_General::Unlock();
}

bool CAddonGUI_ListItem::IsSelected(void *addonData, GUIHANDLE handle)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->IsSelected();
  CAddonGUI_General::Unlock();
}

bool CAddonGUI_ListItem::HasIcon(void *addonData, GUIHANDLE handle)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->HasIcon();
  CAddonGUI_General::Unlock();
}

bool CAddonGUI_ListItem::HasOverlay(void *addonData, GUIHANDLE handle)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->HasOverlay();
  CAddonGUI_General::Unlock();
}

bool CAddonGUI_ListItem::IsFileItem(void *addonData, GUIHANDLE handle)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->IsFileItem();
  CAddonGUI_General::Unlock();
}

bool CAddonGUI_ListItem::IsFolder(void *addonData, GUIHANDLE handle)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->m_bIsFolder;
  CAddonGUI_General::Unlock();
  return ret;
}

void CAddonGUI_ListItem::SetProperty(void *addonData, GUIHANDLE handle, const char *key, const char *value)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetProperty(key, value);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::GetProperty(void *addonData, GUIHANDLE handle, const char *key, char &property, unsigned int &iMaxStringSize)
{
  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  CAddonGUI_General::Lock();
  std::string value = static_cast<CFileItem *>(handle)->GetProperty(lowerKey).asString();
  CAddonGUI_General::Unlock();

  strncpy(&property, value.c_str(), iMaxStringSize);
  iMaxStringSize = value.length();
}

void CAddonGUI_ListItem::IncrementProperty(void *addonData, GUIHANDLE handle, const char *key, int nVal)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->IncrementProperty(key, nVal);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::ClearProperty(void *addonData, GUIHANDLE handle, const char *key)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->ClearProperty(key);
  CAddonGUI_General::Unlock();
}

void CAddonGUI_ListItem::ClearProperties(void *addonData, GUIHANDLE handle)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->ClearProperties();
  CAddonGUI_General::Unlock();
}

bool CAddonGUI_ListItem::HasProperties(void *addonData, GUIHANDLE handle)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->HasProperties();
  CAddonGUI_General::Unlock();
  return ret;
}

bool CAddonGUI_ListItem::HasProperty(void *addonData, GUIHANDLE handle, const char *key)
{
  CAddonGUI_General::Lock();
  bool ret = static_cast<CFileItem *>(handle)->HasProperty(key);
  CAddonGUI_General::Unlock();
  return ret;
}

void CAddonGUI_ListItem::SetPath(void *addonData, GUIHANDLE handle, const char *path)
{
  CAddonGUI_General::Lock();
  static_cast<CFileItem *>(handle)->SetPath(path);
  CAddonGUI_General::Unlock();
}

}; /* namespace V2 */
}; /* namespace GUILIB */
