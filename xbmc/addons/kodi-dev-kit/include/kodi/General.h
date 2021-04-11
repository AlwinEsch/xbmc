/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "AddonBase.h"
#include "c-api/general.h"
#include "tools/StringUtils.h"

#include <string>

namespace kodi
{

inline void QueueFormattedNotification(QueueMsg type, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  const std::string str = kodi::tools::StringUtils::FormatV(format, args);
  va_end(args);
  kodi::dl::api.kodi_queue_notification(type, "", str.c_str(), "", 5000, false, 1000);
}

inline void QueueNotification(QueueMsg type,
                              const std::string& header,
                              const std::string& message,
                              const std::string& imageFile = "",
                              unsigned int displayTime = 5000,
                              bool withSound = true,
                              unsigned int messageTime = 1000)
{
  kodi::dl::api.kodi_queue_notification(type, header.c_str(), message.c_str(), imageFile.c_str(), displayTime,
                          withSound, messageTime);
}

inline std::string GetLocalizedString(uint32_t labelId, const std::string& defaultStr = "")
{
  std::string retString = defaultStr;
  char* strMsg = kodi::dl::api.kodi_get_localized_string(labelId);
  if (strMsg != nullptr)
  {
    if (std::strlen(strMsg))
      retString = strMsg;
    free(strMsg);
  }
  return retString;
}

inline void ATTR_DLL_LOCAL PlaySFX(const std::string& filename, bool use_cached)
{
  kodi::dl::api.kodi_play_sfx(filename.c_str(), use_cached);
}

inline void ATTR_DLL_LOCAL StopSFX()
{
  kodi::dl::api.kodi_stop_sfx();
}

} /* namespace kodi */
