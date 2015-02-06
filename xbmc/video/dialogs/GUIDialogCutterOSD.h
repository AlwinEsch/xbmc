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

#include "guilib/GUIDialog.h"
#include "view/GUIViewControl.h"
#include "utils/Observer.h"

class CGUIDialogCutterOSD :
      public CGUIDialog
{
public:
  CGUIDialogCutterOSD(void);
  virtual ~CGUIDialogCutterOSD(void);

  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void FrameMove();
  virtual void OnWindowLoaded();
  virtual void OnWindowUnload();
  virtual void Notify(const Observable &obs, const ObservableMessage msg);

protected:
  virtual void OnInitWindow();
  virtual void OnDeinitWindow(int nextWindowID);
  virtual void RestoreControlStates();
  virtual void SaveControlStates();

private:
  enum SEEK_TYPE { SEEK_ABSOLUTE, SEEK_RELATIVE };
  enum SEEK_DIRECTION { SEEK_FORWARD, SEEK_BACKWARD };

  void ChangetheTimeCode(int remote);
  void SeekToTimeCodeStamp(SEEK_TYPE type, SEEK_DIRECTION direction = SEEK_FORWARD);
  double GetTimeCodeStamp();
  bool UpdateStreamPosition(bool Initial = false);

  bool SetHelperLabel(int controlID);

  bool m_timeCodeShow;
  unsigned int m_timeCodeTimeout;
  int m_timeCodeStamp[6];
  int m_timeCodePosition;
  int64_t m_lastCurrent, m_lastTotal;
  bool m_FirstFrame;
};
