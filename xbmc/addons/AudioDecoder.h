/*
 *  Copyright (C) 2013 Arne Morten Kvarving
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/paplayer/ICodec.h"
#include "filesystem/MusicFileDirectory.h"
#include "interface/InstanceHandler.h"
#include "music/tags/ImusicInfoTagLoader.h"

namespace MUSIC_INFO
{
class CMusicInfoTag;
class EmbeddedArt;
} // namespace MUSIC_INFO

namespace ADDON
{

class CAudioDecoder : public KODI::ADDONS::INTERFACE::IAddonInstanceHandler,
                      public ICodec,
                      public MUSIC_INFO::IMusicInfoTagLoader,
                      public XFILE::CMusicFileDirectory
{
public:
  explicit CAudioDecoder(const AddonInfoPtr& addonInfo);
  ~CAudioDecoder() override;

  // Things that MUST be supplied by the child classes
  bool CreateDecoder();
  bool Init(const CFileItem& file, unsigned int filecache) override;
  int ReadPCM(uint8_t* buffer, size_t size, size_t* actualsize) override;
  bool Seek(int64_t time) override;
  bool CanInit() override { return true; }
  bool Load(const std::string& strFileName,
            MUSIC_INFO::CMusicInfoTag& tag,
            EmbeddedArt* art = nullptr) override;
  int GetTrackCount(const std::string& strPath) override;

  static inline std::string GetExtensions(const AddonInfoPtr& addonInfo)
  {
    return addonInfo->Type(ADDON_AUDIODECODER)->GetValue("@extension").asString();
  }

  static inline std::string GetMimetypes(const AddonInfoPtr& addonInfo)
  {
    return addonInfo->Type(ADDON_AUDIODECODER)->GetValue("@mimetype").asString();
  }

  static inline bool HasTags(const AddonInfoPtr& addonInfo)
  {
    return addonInfo->Type(ADDON_AUDIODECODER)->GetValue("@tags").asBoolean();
  }

  static inline bool HasTracks(const AddonInfoPtr& addonInfo)
  {
    return addonInfo->Type(ADDON_AUDIODECODER)->GetValue("@tracks").asBoolean();
  }

private:
  KODI_HANDLE m_addonInstance;
  bool m_hasTags;
};

} /*namespace ADDON*/
