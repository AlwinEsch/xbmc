#pragma once

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

class CEdl;
typedef std::shared_ptr<CEdl> CEdlPtr;

class CEdl
{
public:
  CEdl();
  virtual ~CEdl(void);

  typedef enum
  {
    CUT = 0,
    MUTE = 1,
    // SCENE = 2,
    COMM_BREAK = 3
  } Action;

  struct Cut
  {
    int start; // ms
    int end;   // ms
    Action action;
    std::string comment;
  };

  bool ReadEditDecisionLists(const std::string& strMovie, const float fFramesPerSecond, const int iHeight);
  void Clear();

  std::string GetInfo() const;
  int GetTotalCutTime() const;
  int RemoveCutTime(int iSeek) const;
  int RestoreCutTime(int iClock) const;

  bool HasSceneMarker() const;
  bool OnSceneMarker(const int iClock);
  bool GetNextSceneMarker(bool bPlus, const int iClock, int *iSceneMarker) const;
  bool AddSceneMarker(const int sceneMarker);
  bool RemoveSceneMarker(int sceneMarker);
  bool MoveSceneMarker(int sceneMarker, int newPos);

  bool HasCut() const;
  bool InCut(int iSeek, Cut *pCut = NULL) const;
  bool AddCut(Cut& NewCut);
  bool RemoveCut(Cut& Cut);
  bool GenerateCutMarks();
  bool GetCutMarks(std::vector<Cut> &list);

  static std::string MillisecondsToTimeString(const int iMilliseconds);

protected:
private:
  int m_iTotalCutTime; // ms
  std::vector<Cut> m_vecCuts;
  std::vector<int> m_vecSceneMarkers;

  bool ReadEdl(const std::string& strMovie, const float fFramesPerSecond);
  bool ReadComskip(const std::string& strMovie, const float fFramesPerSecond);
  bool ReadVideoReDo(const std::string& strMovie);
  bool ReadBeyondTV(const std::string& strMovie);
  bool ReadPvr(const std::string& strMovie);

  void MergeShortCommBreaks();
  bool CheckValidCut(Cut& Cut);
};
