/*
 *  Copyright (C) 2005-2013 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Bookmark.h"

CBookmark::CBookmark()
{
  Reset();
}

void CBookmark::Reset()
{
  episodeNumber = 0;
  seasonNumber = 0;
  timeInSeconds = 0.0f;
  totalTimeInSeconds = 0.0f;
  partNumber = 0;
  type = STANDARD;
}

bool CBookmark::IsSet() const
{
  return totalTimeInSeconds > 0.0f;
}

bool CBookmark::IsPartWay() const
{
  return totalTimeInSeconds > 0.0f && timeInSeconds > 0.0f;
}
