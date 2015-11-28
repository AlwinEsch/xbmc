/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
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
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "addons/Addon.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "dialogs/GUIDialogProgress.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"
#include "utils/Variant.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIDialogProgress.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

void CAddonGUI_Dialog_Progress::Init(CB_GUILib *callbacks)
{
  callbacks->Dialogs.Progress.New                = CAddonGUI_Dialog_Progress::New;
  callbacks->Dialogs.Progress.Delete             = CAddonGUI_Dialog_Progress::Delete;
  callbacks->Dialogs.Progress.Open               = CAddonGUI_Dialog_Progress::Open;
  callbacks->Dialogs.Progress.SetHeading         = CAddonGUI_Dialog_Progress::SetHeading;
  callbacks->Dialogs.Progress.SetLine            = CAddonGUI_Dialog_Progress::SetLine;
  callbacks->Dialogs.Progress.SetCanCancel       = CAddonGUI_Dialog_Progress::SetCanCancel;
  callbacks->Dialogs.Progress.IsCanceled         = CAddonGUI_Dialog_Progress::IsCanceled;
  callbacks->Dialogs.Progress.SetPercentage      = CAddonGUI_Dialog_Progress::SetPercentage;
  callbacks->Dialogs.Progress.GetPercentage      = CAddonGUI_Dialog_Progress::GetPercentage;
  callbacks->Dialogs.Progress.ShowProgressBar    = CAddonGUI_Dialog_Progress::ShowProgressBar;
  callbacks->Dialogs.Progress.SetProgressMax     = CAddonGUI_Dialog_Progress::SetProgressMax;
  callbacks->Dialogs.Progress.SetProgressAdvance = CAddonGUI_Dialog_Progress::SetProgressAdvance;
  callbacks->Dialogs.Progress.Abort              = CAddonGUI_Dialog_Progress::Abort;
}

GUIHANDLE CAddonGUI_Dialog_Progress::New(void *addonData)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return nullptr;

  CGUIDialogProgress *dialog = (CGUIDialogProgress*)g_windowManager.GetWindow(WINDOW_DIALOG_PROGRESS);
  return dialog;
}

void CAddonGUI_Dialog_Progress::Delete(void *addonData, GUIHANDLE handle)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->Close();
}

void CAddonGUI_Dialog_Progress::Open(void *addonData, GUIHANDLE handle)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->Open();
}

void CAddonGUI_Dialog_Progress::SetHeading(void *addonData, GUIHANDLE handle, const char *heading)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle || !heading)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog or nullptr heading", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->SetHeading(heading);
}

void CAddonGUI_Dialog_Progress::SetLine(void *addonData, GUIHANDLE handle, unsigned int iLine, const char *line)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle || !line)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog or nullptr line", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->SetLine(iLine, line);
}

void CAddonGUI_Dialog_Progress::SetCanCancel(void *addonData, GUIHANDLE handle, bool bCanCancel)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->SetCanCancel(bCanCancel);
}

bool CAddonGUI_Dialog_Progress::IsCanceled(void *addonData, GUIHANDLE handle)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return false;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return false;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  return dialog->IsCanceled();
}

void CAddonGUI_Dialog_Progress::SetPercentage(void *addonData, GUIHANDLE handle, int iPercentage)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->SetPercentage(iPercentage);
}

int CAddonGUI_Dialog_Progress::GetPercentage(void *addonData, GUIHANDLE handle)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return 0;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return 0;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  return dialog->GetPercentage();
}

void CAddonGUI_Dialog_Progress::ShowProgressBar(void *addonData, GUIHANDLE handle, bool bOnOff)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->ShowProgressBar(bOnOff);
}

void CAddonGUI_Dialog_Progress::SetProgressMax(void *addonData, GUIHANDLE handle, int iMax)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->SetProgressMax(iMax);
}

void CAddonGUI_Dialog_Progress::SetProgressAdvance(void *addonData, GUIHANDLE handle, int nSteps)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  dialog->SetProgressAdvance(nSteps);
}

bool CAddonGUI_Dialog_Progress::Abort(void *addonData, GUIHANDLE handle)
{
  CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
  if (!helper)
    return false;

  if (!handle)
  {
    CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
    CLog::Log(LOGERROR, "%s: %s/%s - No Dialog", __FUNCTION__, TranslateType(guiHelper->GetAddon()->Type()).c_str(), guiHelper->GetAddon()->Name().c_str());
    return false;
  }

  CGUIDialogProgress* dialog = static_cast<CGUIDialogProgress *>(handle);
  return dialog->Abort();
}

}; /* namespace V2 */
}; /* namespace GUILIB */
