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

#include "GUISettingsLabelControl.h"
#include "GUIWindowManager.h"
#include "GUIDialog.h"
#include "GUIFontManager.h"

using namespace std;

CGUISettingsLabelControl::CGUISettingsLabelControl(int parentID, int controlID, float posX, float posY, float width, float height, const CTextureInfo& texture, const CLabelInfo& labelInfo)
    : CGUIControl(parentID, controlID, posX, posY, width, height)
    , m_image(posX, posY, width, height, texture)
    , m_label(posX, posY, width, height, labelInfo)
    , m_alpha(255)
    , m_fImageHeight(height)
    , m_fNormalHeight(height)
    , m_bHideSeparator(false)
{
  ControlType = GUICONTROL_SETTINGS_LABEL;
}

CGUISettingsLabelControl::~CGUISettingsLabelControl(void)
{
}

void CGUISettingsLabelControl::Process(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  if (m_bInvalidated)
  {
    m_image.SetWidth(m_width);
    m_image.SetHeight(m_fImageHeight);
  }

  m_image.Process(currentTime);

  std::string label(m_info.GetLabel(m_parentID));
  bool changed  = m_label.SetMaxRect(m_posX, m_posY, m_width, m_height);
  changed |= m_label.SetText(label);
  if (!label.empty())
  {
    changed |= m_label.SetColor(GetTextColor());
    changed |= m_label.Process(currentTime);
  }
  if (changed)
    MarkDirtyRegion();

  CGUIControl::Process(currentTime, dirtyregions);
}

void CGUISettingsLabelControl::Render()
{
  m_image.Render();
  m_label.Render();
  CGUIControl::Render();
}

CGUILabel::COLOR CGUISettingsLabelControl::GetTextColor() const
{
  if (IsDisabled())
    return CGUILabel::COLOR_DISABLED;
  return CGUILabel::COLOR_TEXT;
}

bool CGUISettingsLabelControl::OnMessage(CGUIMessage& message)
{
  if (message.GetControlId() == GetID())
  {
    if (message.GetMessage() == GUI_MSG_LABEL_SET)
    {
      SetLabel(message.GetLabel());
      return true;
    }
  }

  return CGUIControl::OnMessage(message);
}

void CGUISettingsLabelControl::AllocResources()
{
  CGUIControl::AllocResources();
  m_image.AllocResources();
  if (!m_width)
    m_width = m_image.GetWidth();
  if (!m_height)
    m_height = m_image.GetHeight();
}

void CGUISettingsLabelControl::FreeResources(bool immediately)
{
  CGUIControl::FreeResources(immediately);
  m_image.FreeResources(immediately);
}

void CGUISettingsLabelControl::DynamicResourceAlloc(bool bOnOff)
{
  CGUIControl::DynamicResourceAlloc(bOnOff);
  m_image.DynamicResourceAlloc(bOnOff);
}

void CGUISettingsLabelControl::SetInvalid()
{
  CGUIControl::SetInvalid();
  m_label.SetInvalid();
  m_image.SetInvalid();
}

void CGUISettingsLabelControl::SetLabel(const string &label)
{
  m_info.SetLabel(label, "", GetParentID());
  m_height = label.empty() ? m_bHideSeparator ? 0 : m_fImageHeight : m_fNormalHeight;
  SetInvalid();
}

void CGUISettingsLabelControl::SetPosition(float posX, float posY)
{
  CGUIControl::SetPosition(posX, posY);
  m_image.SetPosition(posX, posY + (m_info.GetLabel(m_parentID).empty() ? 0 : m_fImagePosY));
}

void CGUISettingsLabelControl::SetAlpha(unsigned char alpha)
{
  if (m_alpha != alpha)
    MarkDirtyRegion();
  m_alpha = alpha;
}

bool CGUISettingsLabelControl::UpdateColors()
{
  bool changed = CGUIControl::UpdateColors();
  changed |= m_label.UpdateColors();
  changed |= m_image.SetDiffuseColor(m_diffuseColor);

  return changed;
}

CRect CGUISettingsLabelControl::CalcRenderRegion() const
{
  CRect rect = CGUIControl::CalcRenderRegion();
  CRect textRect = m_label.GetRenderRect();
  rect.Union(textRect);
  return rect;
}

std::string CGUISettingsLabelControl::GetDescription() const
{
  std::string strLabel(m_info.GetLabel(m_parentID));
  return strLabel;
}

void CGUISettingsLabelControl::SetAspectRatio(const CAspectRatio &aspect)
{
  m_image.SetAspectRatio(aspect);
}

float CGUISettingsLabelControl::GetHeight() const
{
  return m_height;
}

void CGUISettingsLabelControl::SetImage(float fPosY, float fHeight)
{
  if (m_fImageHeight != fHeight || m_fImagePosY != fPosY)
  {
    m_fImagePosY = fPosY;
    m_fImageHeight = fHeight;
    m_image.SetHeight(m_fImageHeight);

    SetInvalid();
  }
}

void CGUISettingsLabelControl::SetHideSeparator(bool bHide)
{
  if (m_bHideSeparator != bHide)
  {
    m_bHideSeparator = bHide;
    m_image.SetVisible(!bHide);

    SetInvalid();
  }
}
