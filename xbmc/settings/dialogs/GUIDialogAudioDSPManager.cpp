/*
 *      Copyright (C) 2012-2014 Team XBMC
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

#include "GUIDialogAudioDSPManager.h"

#include "FileItem.h"
#include "cores/AudioEngine/DSPAddons/ActiveAEDSP.h"
#include "dialogs/GUIDialogTextViewer.h"
#include "dialogs/GUIDialogOK.h"
#include "dialogs/GUIDialogBusy.h"
#include "dialogs/GUIDialogYesNo.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/Key.h"
#include "guilib/LocalizeStrings.h"
#include "utils/StringUtils.h"

#define BUTTON_OK                 4
#define BUTTON_APPLY              5
#define BUTTON_CANCEL             6
#define IMAGE_CHANNEL_LOGO        10
#define SPIN_DSP_TYPE_SELECTION   13
#define CONTROL_LIST_AVAILABLE    20
#define CONTROL_LIST_ACTIVE       21
#define HELP_LABEL                22

#define LIST_AVAILABLE            0
#define LIST_ACTIVE               1

using namespace std;
using namespace ActiveAE;

CGUIDialogAudioDSPManager::CGUIDialogAudioDSPManager(void) :
    CGUIDialog(WINDOW_DIALOG_AUDIO_DSP_MANAGER, "DialogAudioDSPManager.xml")
{
  m_bMovingMode               = false;
  m_bContainsChanges          = false;
  m_bContinousSaving          = true;
  m_iSelected[LIST_AVAILABLE] = 0;
  m_iSelected[LIST_ACTIVE]    = 0;

  for (int ii = 0; ii < AE_DSP_MODE_TYPE_MAX; ii++)
  {
    m_activeItems[ii] = new CFileItemList;
    m_availableItems[ii] = new CFileItemList;
  }

  m_iCurrentType = AE_DSP_MODE_TYPE_MASTER_PROCESS;//AE_DSP_MODE_TYPE_UNDEFINED;
  //m_iLastType                 = AE_DSP_MODE_TYPE_UNDEFINED;
}

CGUIDialogAudioDSPManager::~CGUIDialogAudioDSPManager(void)
{
  for (int ii = 0; ii < AE_DSP_MODE_TYPE_MAX; ii++)
  {
    delete m_activeItems[ii];
    delete m_availableItems[ii];
  }
}

bool CGUIDialogAudioDSPManager::OnActionMove(const CAction &action)
{
  bool bReturn(false);
  int iActionId = action.GetID();

  if (GetFocusedControlID() == CONTROL_LIST_ACTIVE)
  {
    if (iActionId == ACTION_MOUSE_MOVE)
    {
      int iSelected = m_activeViewControl.GetSelectedItem();
      if (m_iSelected[LIST_ACTIVE] < iSelected)
      {
        iActionId = ACTION_MOVE_DOWN;
      }
      else if (m_iSelected[LIST_ACTIVE] > iSelected)
      {
        iActionId = ACTION_MOVE_UP;
      }
      else
      {
        return bReturn;
      }
    }

    if (iActionId == ACTION_MOVE_DOWN || iActionId == ACTION_MOVE_UP ||
        iActionId == ACTION_PAGE_DOWN || iActionId == ACTION_PAGE_UP)
    {
      bReturn = true;
      CGUIDialog::OnAction(action);

      int iSelected = m_activeViewControl.GetSelectedItem();
      if (!m_bMovingMode)
      {
        if (iSelected != m_iSelected[LIST_ACTIVE])
        {
          m_iSelected[LIST_ACTIVE] = iSelected;
        }
      }
      else
      {
        bool bMoveUp        = iActionId == ACTION_PAGE_UP || iActionId == ACTION_MOVE_UP;
        unsigned int iLines = bMoveUp ? abs(m_iSelected[LIST_ACTIVE] - iSelected) : 1;
        bool bOutOfBounds   = bMoveUp ? m_iSelected[LIST_ACTIVE] <= 0  : m_iSelected[LIST_ACTIVE] >= m_activeItems[m_iCurrentType]->Size() - 1;
        if (bOutOfBounds)
        {
          bMoveUp = !bMoveUp;
          iLines  = m_activeItems[m_iCurrentType]->Size() - 1;
        }

        string strNumber;
        for (unsigned int iLine = 0; iLine < iLines; iLine++)
        {
          unsigned int iNewSelect = bMoveUp ? m_iSelected[LIST_ACTIVE] - 1 : m_iSelected[LIST_ACTIVE] + 1;
          if (m_activeItems[m_iCurrentType]->Get(iNewSelect)->GetProperty("Number").asString() != "-")
          {
            strNumber = StringUtils::Format("%i", m_iSelected[LIST_ACTIVE]+1);
            m_activeItems[m_iCurrentType]->Get(iNewSelect)->SetProperty("Number", strNumber);
            strNumber = StringUtils::Format("%i", iNewSelect+1);
            m_activeItems[m_iCurrentType]->Get(m_iSelected[LIST_ACTIVE])->SetProperty("Number", strNumber);
          }
          m_activeItems[m_iCurrentType]->Swap(iNewSelect, m_iSelected[LIST_ACTIVE]);
          m_iSelected[LIST_ACTIVE] = iNewSelect;
        }

        SET_CONTROL_FOCUS(CONTROL_LIST_ACTIVE, 0);

        m_activeViewControl.SetItems(*m_activeItems[m_iCurrentType]);
        m_activeViewControl.SetSelectedItem(m_iSelected[LIST_ACTIVE]);
      }
    }
  }

  return bReturn;
}

bool CGUIDialogAudioDSPManager::OnAction(const CAction& action)
{
  return OnActionMove(action) ||
         CGUIDialog::OnAction(action);
}

void CGUIDialogAudioDSPManager::OnInitWindow()
{
  CGUIDialog::OnInitWindow();

  m_iSelected[LIST_AVAILABLE] = 0;
  m_iSelected[LIST_ACTIVE]    = 0;
  m_bMovingMode               = false;
  m_bContainsChanges          = false;

  CGUIRadioButtonControl *radioButton = dynamic_cast<CGUIRadioButtonControl*>(GetControl(CONTROL_RADIO_BUTTON_CONTINOUS_SAVING));
  CGUIButtonControl *applyButton = dynamic_cast<CGUIButtonControl*>(GetControl(CONTROL_BUTTON_APPLY_CHANGES));
  if (!radioButton || !applyButton)
  {
    // ToDo: some error message
    return;
  }

  SET_CONTROL_SELECTED(GetID(), CONTROL_RADIO_BUTTON_CONTINOUS_SAVING, m_bContinousSaving);
  applyButton->SetEnabled(!m_bContinousSaving);

  Update();
}

void CGUIDialogAudioDSPManager::OnDeinitWindow(int nextWindowID)
{
  if (m_bContainsChanges)
  {
    if (m_bContinousSaving)
    {
      SaveList();
    }
    else
    {
      if (CGUIDialogYesNo::ShowAndGetInput(19098, 15078, -1, 15079))
      {
        SaveList();
      }
      else
      {
        m_bContinousSaving = false;
      }
    }
  }

  Clear();

  CGUIDialog::OnDeinitWindow(nextWindowID);
}

bool CGUIDialogAudioDSPManager::OnClickListAvailable(CGUIMessage &message)
{
  int iAction = message.GetParam1();
  int iItem = m_availableViewControl.GetSelectedItem();

  /* Check file item is in list range and get his pointer */
  if (iItem < 0 || iItem >= (int)m_availableItems[m_iCurrentType]->Size()) return true;

  /* Process actions */
  if (iAction == ACTION_SELECT_ITEM || iAction == ACTION_CONTEXT_MENU || iAction == ACTION_MOUSE_LEFT_CLICK || iAction == ACTION_MOUSE_RIGHT_CLICK)
  {
    /* Show Contextmenu */
    OnPopupMenu(iItem, LIST_AVAILABLE);

    return true;
  }

  return false;
}

bool CGUIDialogAudioDSPManager::OnClickListActive(CGUIMessage &message)
{
  if (!m_bMovingMode)
  {
    int iAction = message.GetParam1();
    int iItem = m_activeViewControl.GetSelectedItem();

    /* Check file item is in list range and get his pointer */
    if (iItem < 0 || iItem >= (int)m_activeItems[m_iCurrentType]->Size()) return true;

    /* Process actions */
    if (iAction == ACTION_SELECT_ITEM || iAction == ACTION_CONTEXT_MENU || iAction == ACTION_MOUSE_LEFT_CLICK || iAction == ACTION_MOUSE_RIGHT_CLICK)
    {
      /* Show Contextmenu */
      OnPopupMenu(iItem, LIST_ACTIVE);

      return true;
    }
  }
  else
  {
    CFileItemPtr pItem = m_activeItems[m_iCurrentType]->Get(m_iSelected[LIST_ACTIVE]);
    if (pItem)
    {
      pItem->Select(false);
      pItem->SetProperty("Changed", true);
      m_bMovingMode = false;
      m_bContainsChanges = true;

      if (m_bContinousSaving)
      {
        SaveList();
      }
      return true;
    }
  }

  return false;
}

bool CGUIDialogAudioDSPManager::OnClickButtonOK(CGUIMessage &message)
{
  SaveList();
  Close();
  return true;
}

bool CGUIDialogAudioDSPManager::OnClickButtonApply(CGUIMessage &message)
{
  SaveList();
  return true;
}

bool CGUIDialogAudioDSPManager::OnClickButtonCancel(CGUIMessage &message)
{
  Close();
  return true;
}

bool CGUIDialogAudioDSPManager::OnClickProcessTypeSpin(CGUIMessage &message)
{
  if (m_bContainsChanges)
  {
    if (CGUIDialogYesNo::ShowAndGetInput(19098, 15078, -1, 15079))
      SaveList();

    m_bContainsChanges = false;
  }

  m_iSelected[LIST_AVAILABLE] = 0;
  m_iSelected[LIST_ACTIVE]    = 0;
  m_bMovingMode               = false;
    m_bContainsChanges = true;
    if (m_bContinousSaving)
    {
      SaveList();
    }
  }

  Update();
  return true;
}

bool CGUIDialogAudioDSPManager::OnMessageClick(CGUIMessage &message)
{
  int iControl = message.GetSenderId();
  switch(iControl)
  {
  case CONTROL_LIST_AVAILABLE:
    return OnClickListAvailable(message);
  case CONTROL_LIST_ACTIVE:
    return OnClickListActive(message);
  case BUTTON_OK:
    return OnClickButtonOK(message);
  case BUTTON_APPLY:
    return OnClickButtonApply(message);
  case BUTTON_CANCEL:
    return OnClickButtonCancel(message);
  case SPIN_DSP_TYPE_SELECTION:
    return OnClickProcessTypeSpin(message);
  default:
    return false;
  }
}

bool CGUIDialogAudioDSPManager::OnMessage(CGUIMessage& message)
{
  unsigned int iMessage = message.GetMessage();

  switch (iMessage)
  {
    case GUI_MSG_CLICKED:
      return OnMessageClick(message);
    case GUI_MSG_ITEM_SELECT:
      {
        bool ret = CGUIDialog::OnMessage(message);
        if (ret)
        {
          int iItem = -1;
          int focusedControl = GetFocusedControlID();
          if (focusedControl == CONTROL_LIST_AVAILABLE)
          {
            m_iCurrentList = LIST_AVAILABLE;
            iItem = m_availableViewControl.GetSelectedItem();
          }
          else if (focusedControl == CONTROL_LIST_ACTIVE)
          {
            m_iCurrentList = LIST_ACTIVE;
            iItem = m_activeViewControl.GetSelectedItem();
          }

          /* Check file item is in list range and get his pointer */
          if (iItem >= 0 || iItem < (int)m_Items[m_iCurrentList]->Size())
          {
            CFileItemPtr pItem = m_Items[m_iCurrentList]->Get(iItem);
            if (pItem)
              SET_CONTROL_LABEL(HELP_LABEL, pItem->GetProperty("Description").c_str());
          }
        }
        return ret;
      }
  }

  return CGUIDialog::OnMessage(message);
}

void CGUIDialogAudioDSPManager::OnWindowLoaded(void)
{
  g_graphicsContext.Lock();

  m_availableViewControl.Reset();
  m_availableViewControl.SetParentWindow(GetID());
  m_availableViewControl.AddView(GetControl(CONTROL_LIST_AVAILABLE));

  m_activeViewControl.Reset();
  m_activeViewControl.SetParentWindow(GetID());
  m_activeViewControl.AddView(GetControl(CONTROL_LIST_ACTIVE));

  CActiveAEDSPDatabase *database = CActiveAEDSP::Get().GetADSPDatabase();
  if (database)
  {
    int firstLabel = AE_DSP_MODE_TYPE_UNDEFINED;
    vector< pair<string, int> > labels;
    if (database->ContainsModes(AE_DSP_MODE_TYPE_MASTER_PROCESS))
    {
      labels.push_back(make_pair(g_localizeStrings.Get(15059), AE_DSP_MODE_TYPE_MASTER_PROCESS));
      firstLabel = AE_DSP_MODE_TYPE_MASTER_PROCESS;
    }
    if (database->ContainsModes(AE_DSP_MODE_TYPE_POST_PROCESS))
    {
      labels.push_back(make_pair(g_localizeStrings.Get(15060), AE_DSP_MODE_TYPE_POST_PROCESS));
      if (firstLabel == AE_DSP_MODE_TYPE_UNDEFINED)
        firstLabel = AE_DSP_MODE_TYPE_POST_PROCESS;
    }
    if (database->ContainsModes(AE_DSP_MODE_TYPE_OUTPUT_RESAMPLE))
      labels.push_back(make_pair(g_localizeStrings.Get(15061), AE_DSP_MODE_TYPE_OUTPUT_RESAMPLE));
    if (database->ContainsModes(AE_DSP_MODE_TYPE_INPUT_RESAMPLE))
      labels.push_back(make_pair(g_localizeStrings.Get(15057), AE_DSP_MODE_TYPE_INPUT_RESAMPLE));
    if (database->ContainsModes(AE_DSP_MODE_TYPE_PRE_PROCESS))
    {
      labels.push_back(make_pair(g_localizeStrings.Get(15058), AE_DSP_MODE_TYPE_PRE_PROCESS));
      if (firstLabel == AE_DSP_MODE_TYPE_UNDEFINED)
        firstLabel = AE_DSP_MODE_TYPE_PRE_PROCESS;
    }

    SET_CONTROL_LABELS(SPIN_DSP_TYPE_SELECTION, firstLabel, &labels);
  }

  g_graphicsContext.Unlock();

  CGUIDialog::OnWindowLoaded();
}

void CGUIDialogAudioDSPManager::OnWindowUnload(void)
{
  CGUIDialog::OnWindowUnload();

  m_availableViewControl.Reset();
  m_activeViewControl.Reset();
}

bool CGUIDialogAudioDSPManager::OnPopupMenu(int iItem, int listType)
{
  // popup the context menu
  // grab our context menu
  CContextButtons buttons;
  int listSize = 0;
  CFileItemPtr pItem;

  if (listType == LIST_ACTIVE)
  {
    listSize = m_activeItems[m_iCurrentType]->Size();
    pItem = m_activeItems[m_iCurrentType]->Get(iItem);
  }
  else if (listType == LIST_AVAILABLE)
  {
    listSize = m_availableItems[m_iCurrentType]->Size();
    pItem = m_availableItems[m_iCurrentType]->Get(iItem);
  }

  if (!pItem)
  {
    return false;
  }

  // mark the item
  if (iItem >= 0 && iItem < listSize)
  {
    pItem->Select(true);
  }
  else
  {
    return false;
  }

  if (listType == LIST_ACTIVE)
  {
    if (listSize > 1)
    {
      buttons.Add(CONTEXT_BUTTON_MOVE, 116);              /* Move mode up or down */
    }
    buttons.Add(CONTEXT_BUTTON_ACTIVATE, 24021);          /* Used to deactivate addon process type */
  }
  else if (listType == LIST_AVAILABLE)
  {
    if (m_activeItems[m_iCurrentType]->Size() > 0 && (m_iCurrentType == AE_DSP_MODE_TYPE_INPUT_RESAMPLE || m_iCurrentType == AE_DSP_MODE_TYPE_OUTPUT_RESAMPLE))
    {
      buttons.Add(CONTEXT_BUTTON_ACTIVATE, 15080);        /* Used to swap addon resampling process type */
    }
    else
    {
      buttons.Add(CONTEXT_BUTTON_ACTIVATE, 24022);        /* Used to activate addon process type */
    }
  }

  if (pItem->GetProperty("SettingsDialog").asInteger() != 0)
  {
    buttons.Add(CONTEXT_BUTTON_SETTINGS, 15077);          /* Used to activate addon process type help description*/
  }

  if (pItem->GetProperty("Help").asInteger() > 0)
  {
    buttons.Add(CONTEXT_BUTTON_HELP, 15062);              /* Used to activate addon process type help description*/
  }

  int choice = CGUIDialogContextMenu::ShowAndGetChoice(buttons);

  // deselect our item
  if (iItem >= 0 && iItem < listSize)
  {
    pItem->Select(false);
  }

  if (choice < 0)
  {
    return false;
  }

  return OnContextButton(iItem, (CONTEXT_BUTTON)choice, listType);
}

bool CGUIDialogAudioDSPManager::OnContextButton(int itemNumber, CONTEXT_BUTTON button, int listType)
{
  CFileItemPtr pItem;
  int listSize = 0;
  if (listType == LIST_ACTIVE)
  {
    pItem = m_activeItems[m_iCurrentType]->Get(itemNumber);
    listSize = m_activeItems[m_iCurrentType]->Size();
  }
  else if (listType == LIST_AVAILABLE)
  {
    pItem = m_availableItems[m_iCurrentType]->Get(itemNumber);
    listSize = m_availableItems[m_iCurrentType]->Size();
  }

  /* Check file item is in list range and get his pointer */
  if (!pItem || itemNumber < 0 || itemNumber >= listSize)
  {
    return false;
  }

  if (button == CONTEXT_BUTTON_HELP)
  {
    /*!
    * Open audio dsp addon mode help text dialog
    */
    AE_DSP_ADDON addon;
    if (CActiveAEDSP::Get().GetAudioDSPAddon((int)pItem->GetProperty("AddonId").asInteger(), addon))
    {
      CGUIDialogTextViewer* pDlgInfo = (CGUIDialogTextViewer*)g_windowManager.GetWindow(WINDOW_DIALOG_TEXT_VIEWER);
      pDlgInfo->SetHeading(g_localizeStrings.Get(15062) + " - " + pItem->GetProperty("Name").asString());
      pDlgInfo->SetText(addon->GetString((uint32_t)pItem->GetProperty("Help").asInteger()));
      pDlgInfo->DoModal();
    }
  }
  else if (button == CONTEXT_BUTTON_ACTIVATE)
  {
    /*!
    * Deactivate selected processing mode
    */
    if (pItem->GetProperty("ActiveMode").asBoolean())
    {
      // remove mode from active mode list and add it to available mode list
      CFileItemPtr newItem(dynamic_cast<CFileItem*>(pItem->Clone()));
      newItem->SetProperty("ActiveMode", false);
      newItem->SetProperty("Changed", true);
      m_activeItems[m_iCurrentType]->Remove(itemNumber);
      m_availableItems[m_iCurrentType]->Add(newItem);
    }
    else
    {
      /*!
      * Activate selected processing mode
      */
      if ((m_iCurrentType == AE_DSP_MODE_TYPE_INPUT_RESAMPLE || m_iCurrentType == AE_DSP_MODE_TYPE_OUTPUT_RESAMPLE) && m_activeItems[m_iCurrentType]->Size() > 0)
      { // if there is already an active resampler, now we remove it
        CFileItemPtr activeResampler = m_activeItems[m_iCurrentType]->Get(0);
        if (activeResampler)
        {
          CFileItemPtr newItem(dynamic_cast<CFileItem*>(activeResampler->Clone()));
          newItem->SetProperty("ActiveMode", false);
          newItem->SetProperty("Changed", true);

          m_availableItems[m_iCurrentType]->Add(newItem);
          // clear active list, because only one active resampling mode is supported by ActiveAEDSP
          m_activeItems[m_iCurrentType]->Clear();
        }
      }

      // remove mode from available mode list and add it to active mode list
      CFileItemPtr newItem(dynamic_cast<CFileItem*>(pItem->Clone()));

      newItem->SetProperty("Number", (int)m_activeItems[m_iCurrentType]->Size() +1);
      newItem->SetProperty("Changed", true);
      newItem->SetProperty("ActiveMode", true);

      m_availableItems[m_iCurrentType]->Remove(itemNumber);
      m_activeItems[m_iCurrentType]->Add(newItem);
    }

    m_bContainsChanges = true;
    if (m_bContinousSaving)
    {
      SaveList();
    }

    // reorder available mode list, so that the mode order is always consistent
    m_availableItems[m_iCurrentType]->ClearSortState();
    m_availableItems[m_iCurrentType]->Sort(SortByLabel, SortOrderAscending);

    // update active and available mode list
    Renumber();
    m_availableViewControl.SetItems(*m_availableItems[m_iCurrentType]);
    m_activeViewControl.SetItems(*m_activeItems[m_iCurrentType]);
  }
  else if (button == CONTEXT_BUTTON_MOVE)
  {
    m_bMovingMode = true;
    pItem->Select(true);

    CGUIListContainer *modeList = dynamic_cast<CGUIListContainer*>(GetControl(CONTROL_LIST_MODE_SELECTION));
    CGUIButtonControl *applyButton = dynamic_cast<CGUIButtonControl*>(GetControl(CONTROL_BUTTON_APPLY_CHANGES));
    CGUIButtonControl *clearActiveModesButton = dynamic_cast<CGUIButtonControl*>(GetControl(CONTROL_BUTTON_CLEAR_ACTIVE_MODES));
    if (!modeList || !applyButton || !clearActiveModesButton)
    {
      // Todo: show some error message!
      return false;
    }
    
    // if we are in MovingMode all buttons and mode selection list will be disabled!
    modeList->SetEnabled(false);
    clearActiveModesButton->SetEnabled(false);
    if (!m_bContinousSaving)
    {
      applyButton->SetEnabled(false);
    }
  }
  else if (button == CONTEXT_BUTTON_SETTINGS)
  {
    int hookId = (int)pItem->GetProperty("SettingsDialog").asInteger();
    if (hookId > 0)
    {
      AE_DSP_ADDON addon;
      if (CActiveAEDSP::Get().GetAudioDSPAddon((int)pItem->GetProperty("AddonId").asInteger(), addon))
      {
        AE_DSP_MENUHOOK       hook;
        AE_DSP_MENUHOOK_DATA  hookData;

        hook.category           = AE_DSP_MENUHOOK_ALL;
        hook.iHookId            = hookId;
        hook.iRelevantModeId    = (unsigned int)pItem->GetProperty("AddonModeNumber").asInteger();
        hookData.category       = AE_DSP_MENUHOOK_ALL;
        hookData.data.iStreamId = -1;

        if (m_bContainsChanges)
        {
          if (m_bContinousSaving)
          {
            SaveList();
          }
          else
          {
            if (CGUIDialogYesNo::ShowAndGetInput(19098, 15078, -1, 15079))
            {
              SaveList();
            }
            else
            {
              m_bContainsChanges = false;
            }
          }
        }

        m_iLastSelected[LIST_AVAILABLE] = m_availableViewControl.GetSelectedItem();
        m_iLastSelected[LIST_ACTIVE]    = m_activeViewControl.GetSelectedItem();

        // save control states and currently selected item of group
        SaveControlStates();

        Close();
        addon->CallMenuHook(hook, hookData);

        if (!g_windowManager.Initialized())
          return false; // don't do anything

        m_closing = false;
        m_bModal = true;
        // set running before it's added to the window manager, else the auto-show code
        // could show it as well if we are in a different thread from
        // the main rendering thread (this should really be handled via
        // a thread message though IMO)
        m_active = true;
        g_windowManager.RouteToWindow(this);

        // active this window...
        CGUIMessage msg(GUI_MSG_WINDOW_INIT, 0, 0);
        OnMessage(msg);

        if (!m_windowLoaded)
          Close(true);
      }
    }
    else
    {
      CGUIDialogOK::ShowAndGetInput(19033, 0, 15040, 0);
    }
  }

  return true;
}

void CGUIDialogAudioDSPManager::Update()
{
  CGUIDialogBusy* pDlgBusy = (CGUIDialogBusy*)g_windowManager.GetWindow(WINDOW_DIALOG_BUSY);
  if (!pDlgBusy)
  {
    //ToDo: add some error message to logfile
    return;
  }
  pDlgBusy->Show();

  Clear();

  AE_DSP_MODELIST modes;
  CActiveAEDSPDatabase db;
  if (!db.Open())
  {
    pDlgBusy->Close();
    CLog::Log(LOGERROR, "%s - Could not open CActiveAEDSPDatabase!", __FUNCTION__);
    return;
  }

  for (int iModeType = 0; iModeType < AE_DSP_MODE_TYPE_MAX; iModeType++)
  {
    modes.clear();
    db.GetModes(modes, iModeType);

    // No modes available, nothing to do.
    if (!modes.empty())
    {
      AE_DSP_MENUHOOK_CAT menuHook = helper_getMenuHookCategory(iModeType);
      int continuesNo = 1;
      for (unsigned int iModePtr = 0; iModePtr < modes.size(); iModePtr++)
      {
        CFileItem *listItem = helper_createModeListItem(modes[iModePtr].first, menuHook, &continuesNo);
        if (listItem)
        {
          CFileItemPtr pItem(listItem);

          if (pItem->GetProperty("ActiveMode").asBoolean())
          {
            m_activeItems[iModeType]->Add(pItem);
          }
          else
          {
            m_availableItems[iModeType]->Add(pItem);
          }
        }
        g_windowManager.ProcessRenderLoop(false);
      }

      m_availableItems[iModeType]->Sort(SortByLabel, SortOrderAscending);
      if (iModeType == AE_DSP_MODE_TYPE_MASTER_PROCESS)
      {
        m_activeItems[iModeType]->Sort(SortByLabel, SortOrderAscending);
      }

    }
  }

  db.Close();

  pDlgBusy->Close();
}
void CGUIDialogAudioDSPManager::SetSelectedModeType(void)
{
  /* lock our display, as this window is rendered from the player thread */
  g_graphicsContext.Lock();
  if (m_iCurrentType > AE_DSP_MODE_TYPE_UNDEFINED && m_iCurrentType < AE_DSP_MODE_TYPE_MAX && !m_bMovingMode)
  {
    m_availableViewControl.SetCurrentView(CONTROL_LIST_AVAILABLE);
    m_activeViewControl.SetCurrentView(CONTROL_LIST_ACTIVE);

    m_availableViewControl.SetItems(*m_availableItems[m_iCurrentType]);
    m_activeViewControl.SetItems(*m_activeItems[m_iCurrentType]);
  }

  g_graphicsContext.Unlock();
}

void CGUIDialogAudioDSPManager::Clear(void)
{
  m_availableViewControl.Clear();
  m_activeViewControl.Clear();

  for (int ii = 0; ii < AE_DSP_MODE_TYPE_MAX; ii++)
  {
    m_activeItems[ii]->Clear();
    m_availableItems[ii]->Clear();
  }
}

void CGUIDialogAudioDSPManager::SaveList(void)
{
  if (!m_bContainsChanges)
   return;

  /* display the progress dialog */
  CGUIDialogBusy* pDlgBusy = (CGUIDialogBusy*)g_windowManager.GetWindow(WINDOW_DIALOG_BUSY);
  if (!pDlgBusy)
  {
    //ToDo: add some error message to logfile
    return;
  }
  pDlgBusy->Show();

  /* persist all modes */
  if (UpdateDatabase(pDlgBusy))
  {
    CActiveAEDSP::Get().TriggerModeUpdate();

    m_bContainsChanges = false;
    SetItemsUnchanged();
  }

  pDlgBusy->Close();
}

bool CGUIDialogAudioDSPManager::UpdateDatabase(CGUIDialogBusy* pDlgBusy)
{
  CActiveAEDSPDatabase db;
  if (!db.Open())
  {
    CLog::Log(LOGERROR, "%s - Could not open CActiveAEDSPDatabase!", __FUNCTION__);
    return false;
  }

  // calculate available items
  int maxItems = 0;
  for (int i = 0; i < AE_DSP_MODE_TYPE_MAX; i++)
  {
    maxItems += m_activeItems[i]->Size() + m_availableItems[i]->Size();
  }

  int processedItems = 0;
  for (int i = 0; i < AE_DSP_MODE_TYPE_MAX; i++)
  {
    for (int iListPtr = 0; iListPtr < m_activeItems[i]->Size(); iListPtr++)
    {
      CFileItemPtr pItem = m_activeItems[i]->Get(iListPtr);
      if (pItem->GetProperty("Changed").asBoolean())
      {
        bool success = db.UpdateMode( i,
                                      pItem->GetProperty("ActiveMode").asBoolean(),
                                      (int)pItem->GetProperty("AddonId").asInteger(),
                                      (int)pItem->GetProperty("AddonModeNumber").asInteger(),
                                      (int)pItem->GetProperty("Number").asInteger());

        if (!success)
        {
          //ToDo some error message
        }
      }

      processedItems++;
      if (pDlgBusy)
      {
        pDlgBusy->SetProgress((float)(processedItems * 100 / maxItems));

        if (pDlgBusy->IsCanceled())
        {
          return false;
        }
      }

      g_windowManager.ProcessRenderLoop(false);
    }

    for (int iListPtr = 0; iListPtr < m_availableItems[i]->Size(); iListPtr++)
    {
      CFileItemPtr pItem = m_availableItems[i]->Get(iListPtr);
      if (pItem && pItem->GetProperty("Changed").asBoolean())
      {
        bool success = db.UpdateMode( i,
                                      pItem->GetProperty("ActiveMode").asBoolean(),
                                      (int)pItem->GetProperty("AddonId").asInteger(),
                                      (int)pItem->GetProperty("AddonModeNumber").asInteger(),
                                      (int)pItem->GetProperty("Number").asInteger());

        if (!success)
        {
          //ToDo some error message
        }
      }

      processedItems++;
      if (pDlgBusy)
      {
        pDlgBusy->SetProgress((float)(processedItems * 100 / maxItems));

        if (pDlgBusy->IsCanceled())
        {
          return false;
        }
      }

      g_windowManager.ProcessRenderLoop(false);
    }
  }
  db.Close();
  return true;
}

void CGUIDialogAudioDSPManager::SetItemsUnchanged()
{
  for (int i = 0; i < AE_DSP_MODE_TYPE_MAX; i++)
  {
    for (int iItemPtr = 0; iItemPtr < m_activeItems[i]->Size(); iItemPtr++)
    {
      CFileItemPtr pItem = m_activeItems[i]->Get(iItemPtr);
      if (pItem)
        pItem->SetProperty("Changed", false);
    }

    for (int iItemPtr = 0; iItemPtr < m_availableItems[i]->Size(); iItemPtr++)
    {
      CFileItemPtr pItem = m_availableItems[i]->Get(iItemPtr);
      if (pItem)
        pItem->SetProperty("Changed", false);
    }
  }
}

void CGUIDialogAudioDSPManager::Renumber(void)
{
  int iNextModeNumber(0);
  string strNumber;
  CFileItemPtr pItem;

  for (int iModePtr = 0; iModePtr < m_activeItems[m_iCurrentType]->Size(); iModePtr++)
  {
    pItem = m_activeItems[m_iCurrentType]->Get(iModePtr);
    strNumber = StringUtils::Format("%i", ++iNextModeNumber);
    pItem->SetProperty("Number", strNumber);
  }
}
    {
      strNumber = StringUtils::Format("%i", ++iNextModeNumber);
      pItem->SetProperty("Number", strNumber);
    }
    else
      pItem->SetProperty("Number", "-");
  }
}
