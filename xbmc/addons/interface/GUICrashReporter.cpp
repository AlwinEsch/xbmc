/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GUICrashReporter.h"

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

CGUICrashReporter::CGUICrashReporter()
  : CGUIDialog(WINDOW_DIALOG_ADDON_CRASH_REPORTER, "DialogAddonCrashReporter.xml")
{

}

CGUICrashReporter::~CGUICrashReporter()
{

}

void CGUICrashReporter::OnInitWindow()
{
  CGUIDialog::OnInitWindow();
}

bool CGUICrashReporter::OnAction(const CAction& action)
{

  return CGUIDialog::OnAction(action);
}

bool CGUICrashReporter::OnMessage(CGUIMessage& message)
{
  return CGUIDialog::OnMessage(message);
}

void CGUICrashReporter::ReportCrash(const std::shared_ptr<ADDON::IAddon>& addon)
{

}

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
