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

#include "GUICutterProgressControl.h"
#include "GUIInfoManager.h"
#include "GUIListItem.h"
#include "GUIWindowManager.h"
#include "FileItem.h"
#include "utils/StringUtils.h"

CGUICutterProgressControl::CGUICutterProgressControl(int parentID, int controlID,
                                                     float posX, float posY, float width,
                                                     float height, const CTextureInfo& backGroundTexture,
                                                     const CTextureInfo& leftTexture,
                                                     const CTextureInfo& midTexture,
                                                     const CTextureInfo& rightTexture,
                                                     const CTextureInfo& overlayTexture,
                                                     const CTextureInfo& cuttedTexture,
                                                     const CTextureInfo& markTextureFront,
                                                     const CTextureInfo& markTextureBack,
                                                     bool reveal /* = false */)
  : CGUIControl(parentID, controlID, posX, posY, width, height)
  , m_guiBackground(posX, posY, width, height, backGroundTexture)
  , m_guiLeft(posX, posY, width, height, leftTexture)
  , m_guiMid(posX, posY, width, height, midTexture)
  , m_guiRight(posX, posY, width, height, rightTexture)
  , m_guiOverlay(posX, posY, width, height, overlayTexture)
  , m_CuttedTexture(cuttedTexture)
  , m_MarkTextureFront(markTextureFront)
  , m_MarkTextureBack(markTextureBack)
  , m_PosX(posX)
  , m_PosY(posY)
  , m_StreamSize(-1)
  , m_StreamPosition(-1)
  , m_fPercent(0)
  , m_bReveal(reveal)
  , m_bChanged(false)
  , m_iInfoCode(0)
{
  ControlType = GUICONTROL_CUTTER_PROGRESS;
}

CGUICutterProgressControl::~CGUICutterProgressControl()
{


}

void CGUICutterProgressControl::Process(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{


}

void CGUICutterProgressControl::Render()
{


}

bool CGUICutterProgressControl::CanFocus() const
{


}

void CGUICutterProgressControl::AllocResources()
{


}

void CGUICutterProgressControl::FreeResources(bool immediately)
{


}

void CGUICutterProgressControl::DynamicResourceAlloc(bool bOnOff)
{


}

void CGUICutterProgressControl::SetInvalid()
{


}

bool CGUICutterProgressControl::OnMessage(CGUIMessage& message)
{

  return false;
}

void CGUICutterProgressControl::SetPosition(float posX, float posY)
{


}

void CGUICutterProgressControl::UpdateInfo(const CGUIListItem *item /* = NULL */)
{


}

std::string CGUICutterProgressControl::GetDescription() const
{
//  fprintf(stderr, "<<<<<<<<<<< %s\n", __PRETTY_FUNCTION__);
//  CStdString percent;
//  percent.Format("%2.f", m_fPercent);
  return "";
}

bool CGUICutterProgressControl::UpdateLayout(void)
{

  return false;
}

void CGUICutterProgressControl::SetStreamSize(int64_t streamsize)
{
  m_StreamSize = streamsize;
}

void CGUICutterProgressControl::SetStreamPosition(int64_t position)
{
  m_StreamPosition = position;
}


bool CGUICutterProgressControl::RemoveSceneMark(int64_t markPoint)
{
  return false;
}

bool CGUICutterProgressControl::MoveSceneMark(int64_t markPoint, int64_t newPoint)
{
  return false;
}

bool CGUICutterProgressControl::AddCutMarks(std::vector< std::pair<int64_t, int64_t> > &list)
{

  return true;
}

void CGUICutterProgressControl::ClearSceneMarks()
{
}

bool CGUICutterProgressControl::AddSceneMark(int64_t markPoint, bool Start, bool Current)
{

}

void CGUICutterProgressControl::SetMarks(const CCutMarks *Marks)
{

}

float CGUICutterProgressControl::GetPercentage() const
{
  return 0.0f;
}

void CGUICutterProgressControl::SetPercentage(float fPercent)
{

}

bool CGUICutterProgressControl::UpdateColors()
{
  return true;
}

void CGUICutterProgressControl::SetInfo(int iInfo)
{

}
