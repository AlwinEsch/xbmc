/*!
\file GUISettingsLabelControl.h
\brief
*/

#ifndef GUILIB_GUISETTINGSLABELCONTROL_H
#define GUILIB_GUISETTINGSLABELCONTROL_H

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

#include "GUITexture.h"
#include "GUILabel.h"
#include "GUIControl.h"

/*!
 \ingroup controls
 \brief
 */
class CGUISettingsLabelControl : public CGUIControl
{
public:
  CGUISettingsLabelControl(int parentID, int controlID,
                           float posX, float posY, float width, float height,
                           const CTextureInfo& texture, const CLabelInfo &label);

  virtual ~CGUISettingsLabelControl(void);
  virtual CGUISettingsLabelControl *Clone() const { return new CGUISettingsLabelControl(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool CanFocus() const { return false; };
  virtual bool OnMessage(CGUIMessage& message);
  virtual std::string GetLabel() const { return GetDescription(); };
  virtual std::string GetDescription() const;
  virtual float GetHeight() const;
  virtual CRect CalcRenderRegion() const;
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  virtual void SetPosition(float posX, float posY);
  virtual void SetLabel(const std::string & aLabel);
  virtual void SetAspectRatio(const CAspectRatio &aspect);

  const CLabelInfo& GetLabelInfo() const { return m_label.GetLabelInfo(); };

  void SetAlpha(unsigned char alpha);
  void SetImage(float fPosY, float fHeight);
  void SetHideSeparator(bool bHide);

  virtual bool UpdateColors();

protected:
  virtual CGUILabel::COLOR GetTextColor() const;

  CGUITexture    m_image;
  CGUIInfoLabel  m_info;
  CGUILabel      m_label;

  unsigned char m_alpha;
  float m_fImagePosY;
  float m_fImageHeight;
  float m_fNormalHeight;
  bool m_bHideSeparator;
};

#endif // GUILIB_GUISETTINGSLABELCONTROL_H
