/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/IAddon.h"
#include "guilib/GUIDialog.h"

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

class CGUICrashReporter : public CGUIDialog
{
public:
  CGUICrashReporter(void);
  ~CGUICrashReporter(void) override;

  bool OnMessage(CGUIMessage& message) override;
  bool OnAction(const CAction& action) override;

  static void ReportCrash(const std::shared_ptr<ADDON::IAddon>& addon);

private:
  void OnInitWindow() override;

};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
