/*!
\file GUICutterProgressControl.h
\brief
*/

#ifndef GUILIB_GUICUTTERPROGRESSCONTROL_H
#define GUILIB_GUICUTTERPROGRESSCONTROL_H

#pragma once

/*
 *      Copyright (C) 2005-2015 Team XBMC
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

#include <vector>
#include "GUITexture.h"
#include "GUIControl.h"

class CCutMarks;

/*!
 \ingroup controls
 \brief
 */
class CGUICutterProgressControl :
      public CGUIControl
{
public:
  CGUICutterProgressControl(int parentID, int controlID, float posX, float posY,
                            float width, float height, const CTextureInfo& backGroundTexture,
                            const CTextureInfo& leftTexture, const CTextureInfo& midTexture,
                            const CTextureInfo& rightTexture, const CTextureInfo& overlayTexture,
                            const CTextureInfo& cuttedTexture, const CTextureInfo& markTextureFront,
                            const CTextureInfo& markTextureBack, bool reveal=false);
  virtual ~CGUICutterProgressControl();
  virtual CGUICutterProgressControl *Clone() const { return new CGUICutterProgressControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool CanFocus() const;
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  virtual bool OnMessage(CGUIMessage& message);
  virtual void SetPosition(float posX, float posY);
  void SetPercentage(float fPercent);
  void SetInfo(int iInfo);
  int GetInfo() const {return m_iInfoCode;};

  void SetStreamSize(int64_t streamsize);
  void SetStreamPosition(int64_t position);
  bool AddSceneMark(int64_t markPoint, bool Start, bool Current);
  bool RemoveSceneMark(int64_t markPoint);
  bool MoveSceneMark(int64_t markPoint, int64_t newPoint);
  void ClearSceneMarks();
  bool AddCutMarks(std::vector< std::pair<int64_t, int64_t> > &list);
  void SetMarks(const CCutMarks *Marks);

  float GetPercentage() const;
  std::string GetDescription() const;
  virtual void UpdateInfo(const CGUIListItem *item = NULL);
  bool UpdateLayout(void);

protected:
  virtual bool UpdateColors();
  int Pos(int p) { return p * m_width / m_StreamSize; }

  CGUITexture m_guiBackground;
  CGUITexture m_guiLeft;
  CGUITexture m_guiMid;
  CGUITexture m_guiRight;
  CGUITexture m_guiOverlay;

  typedef std::vector<std::pair<int64_t, CGUITexture> >::iterator listIterator;
  std::vector<std::pair<int64_t, CGUITexture> > m_guiCuttedMap;
  std::vector<std::pair<int64_t, CGUITexture> > m_guiMarkMap;

  const CTextureInfo m_CuttedTexture;
  const CTextureInfo m_MarkTextureFront;
  const CTextureInfo m_MarkTextureBack;

  CRect   m_guiMidClipRect;
  int     m_PosX;
  int     m_PosY;
  int64_t m_StreamSize;
  int64_t m_StreamPosition;
  float   m_fPercent;
  bool    m_bReveal;
  bool    m_bChanged;
  int     m_iInfoCode;
};

#endif // GUILIB_GUICUTTERPROGRESSCONTROL_H
