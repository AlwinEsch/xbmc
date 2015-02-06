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

#include "GUIDialogCutterOSD.h"
#include "Application.h"
#include "ApplicationMessenger.h"
#include "FileItem.h"
#include "GUIInfoManager.h"
#include "Util.h"
#include "dialogs/GUIDialogNumeric.h"
#include "guilib/GUICutterProgressControl.h"
#include "guilib/GUIButtonControl.h"
#include "guilib/GUILabelControl.h"
#include "guilib/Key.h"
#include "guilib/LocalizeStrings.h"
#include "guilib/GUIWindowManager.h"
#include "input/ButtonTranslator.h"
#include "settings/AdvancedSettings.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "utils/TimeUtils.h"

using namespace std;

#define CONTROL_SELECT_LABEL         2

#define CONTROL_PROGRESS            10

#define BUTTON_GENERATE_CUTMARKS    18
#define BUTTON_JUMP_TO_TIMECODE     19

#define BUTTON_JUMP_BIG_BACK        20
#define BUTTON_JUMP_SMALL_BACK      21
#define BUTTON_SETSPEED_BACK        22
#define BUTTON_PAUSE_PLAY           23
#define BUTTON_SETSPEED_FWD         25
#define BUTTON_JUMP_SMALL_FWD       26
#define BUTTON_JUMP_BIG_FWD         27

#define BUTTON_MARK_BEFORESEC_BACK  30
#define BUTTON_ONE_MARK_BACK        31
#define BUTTON_ONE_FRAME_BACK       32
#define BUTTON_ADD_REMOVE_MARK      33
#define BUTTON_ONE_FRAME_FWD        35
#define BUTTON_ONE_MARK_FWD         36
#define BUTTON_MARK_BEFORESEC_FWD   37

#define BUTTON_RETURN_CUTTER        40
#define BUTTON_START_CUT            41
#define BUTTON_CANCEL_CUT           42

CGUIDialogCutterOSD::CGUIDialogCutterOSD()
    : CGUIDialog(WINDOW_DIALOG_OSD_CUTTER, "DialogCutterOSD.xml")
{
  m_timeCodeStamp[0]  = 0;
  m_timeCodePosition  = 0;
  m_timeCodeShow      = false;
  m_timeCodeTimeout   = 0;
}

CGUIDialogCutterOSD::~CGUIDialogCutterOSD()
{
}

bool CGUIDialogCutterOSD::OnMessage(CGUIMessage& message)
{
  switch (message.GetMessage())
  {
  case GUI_MSG_CLICKED:
    {
      int iControl = message.GetSenderId();

      if (iControl == BUTTON_JUMP_TO_TIMECODE)
      {
      }
      else if (iControl == BUTTON_JUMP_SMALL_BACK)
      {
      }
      else if (iControl == BUTTON_JUMP_SMALL_FWD)
      {
      }
      else if (iControl == BUTTON_JUMP_BIG_BACK)
      {
      }
      else if (iControl == BUTTON_JUMP_BIG_FWD)
      {
      }
      else if (iControl == BUTTON_ONE_FRAME_BACK || iControl == BUTTON_ONE_FRAME_FWD)
      {
      }
      else if (iControl == BUTTON_ONE_MARK_BACK || iControl == BUTTON_ONE_MARK_FWD)
      {
      }
      else if (iControl == BUTTON_MARK_BEFORESEC_BACK || iControl == BUTTON_MARK_BEFORESEC_FWD)
      {
      }
      else if (iControl == BUTTON_ADD_REMOVE_MARK)
      {
      }
      else if (iControl == BUTTON_START_CUT)
      {
      }
      else if (iControl == BUTTON_CANCEL_CUT)
      {
      }
      else if (iControl == BUTTON_RETURN_CUTTER)
      {
      }
    }
    break;
  case GUI_MSG_FOCUSED:
    {
    }
    break;
  case GUI_MSG_LOSTFOCUS:
    {
    }
    break;
  }

  return CGUIDialog::OnMessage(message);
}

void CGUIDialogCutterOSD::OnInitWindow()
{

  CGUIDialog::OnInitWindow();
}

void CGUIDialogCutterOSD::OnDeinitWindow(int nextWindowID)
{

  CGUIDialog::OnDeinitWindow(nextWindowID);
}

bool CGUIDialogCutterOSD::OnAction(const CAction &action)
{

  return CGUIDialog::OnAction(action);
}

void CGUIDialogCutterOSD::FrameMove()
{

}

void CGUIDialogCutterOSD::OnWindowLoaded()
{
  fprintf(stderr, "<<<<<<<<<<< %s\n", __PRETTY_FUNCTION__);
  CGUIDialog::OnWindowLoaded();
}

void CGUIDialogCutterOSD::OnWindowUnload()
{
  fprintf(stderr, "<<<<<<<<<<< %s\n", __PRETTY_FUNCTION__);
  CGUIDialog::OnWindowUnload();
}

void CGUIDialogCutterOSD::Notify(const Observable &obs, const ObservableMessage msg)
{
  fprintf(stderr, "<<<<<<<<<<< %s\n", __PRETTY_FUNCTION__);

}

void CGUIDialogCutterOSD::SaveControlStates()
{
  fprintf(stderr, "<<<<<<<<<<< %s\n", __PRETTY_FUNCTION__);

}

void CGUIDialogCutterOSD::RestoreControlStates()
{
  fprintf(stderr, "<<<<<<<<<<< %s\n", __PRETTY_FUNCTION__);

}

void CGUIDialogCutterOSD::ChangetheTimeCode(int remote)
{
  fprintf(stderr, "<<<<<<<<<<< %s\n", __PRETTY_FUNCTION__);

}

void CGUIDialogCutterOSD::SeekToTimeCodeStamp(SEEK_TYPE type, SEEK_DIRECTION direction)
{
}

double CGUIDialogCutterOSD::GetTimeCodeStamp()
{
}

bool CGUIDialogCutterOSD::SetHelperLabel(int controlID)
{
}

bool CGUIDialogCutterOSD::UpdateStreamPosition(bool Initial)
{
}
