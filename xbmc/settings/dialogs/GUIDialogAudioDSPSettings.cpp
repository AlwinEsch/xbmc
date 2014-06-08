/*
 *      Copyright (C) 2005-2014 Team XBMC
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

#include "system.h"
#include "GUIDialogAudioDSPSettings.h"
#include "GUIPassword.h"
#include "Application.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "dialogs/GUIDialogYesNo.h"
#include "addons/Skin.h"
#include "profiles/ProfilesManager.h"
#include "settings/AdvancedSettings.h"
#include "settings/MediaSettings.h"
#include "settings/Settings.h"
#include "guilib/GUIImage.h"
#include "guilib/GUIWindowManager.h"
#include "cores/AudioEngine/DSPAddons/ActiveAEDSPDatabase.h"
#include "cores/AudioEngine/DSPAddons/ActiveAEDSPMode.h"
#include "cores/AudioEngine/Utils/AEUtil.h"
#include "cores/IPlayer.h"
#include "utils/StringUtils.h"
#include "utils/MathUtils.h"

#include "guilib/GUISpinControlEx.h"
#include "guilib/GUIRadioButtonControl.h"
#include "guilib/GUISettingsSliderControl.h"
#include "guilib/GUIImage.h"
#include "guilib/GUIControlGroupList.h"
#include "guilib/GUILabelControl.h"
#include "guilib/LocalizeStrings.h"
#include "utils/log.h"
#include "guilib/GUIKeyboardFactory.h"


using namespace std;
using namespace XFILE;
using namespace ActiveAE;

/*! Skin control variables */
#define CONTROL_SETTINGS_LABEL      2
#define CONTROL_NONE_AVAILABLE      3
#define CONTROL_GROUP_LIST          5
#define CONTROL_DEFAULT_BUTTON      7
#define CONTROL_DEFAULT_RADIOBUTTON 8
#define CONTROL_DEFAULT_SPIN        9
#define CONTROL_DEFAULT_SLIDER     10
#define CONTROL_DEFAULT_SEPARATOR  11
#define CONTROL_DEFAULT_LABEL      14
#define CONTROL_START              30
#define CONTROL_PAGE               60

/*! Control id's */
#define AUDIO_MENU_MAIN                         0   /*! Not used as control id only to identfiy main menu place */
#define AUDIO_SETTING_CONTENT_TYPE              1
#define AUDIO_SETTING_CONTENT_LABEL             2
#define AUDIO_SETTING_STREAM_SELECTION          3
#define AUDIO_SETTINGS_DELAY                    4
#define AUDIO_SEPERATOR_1                       5
#define AUDIO_SETTINGS_VOLUME                   6
#define AUDIO_SETTINGS_VOLUME_AMPLIFICATION     7
#define AUDIO_SEPERATOR_2                       8
#define AUDIO_BUTTON_MASTER_MODE_SETUP          9
#define AUDIO_BUTTON_SPEAKER_OUTPUT_SETUP       10
#define AUDIO_BUTTON_RESAMPLER_SETUP            11
#define AUDIO_BUTTON_PRE_PROCESS_SETUP          12
#define AUDIO_BUTTON_MISC_SETUP                 13
#define AUDIO_BUTTON_AUDIO_INFORMATION          14
#define AUDIO_SEPERATOR_3                       15
#define AUDIO_SETTINGS_MAKE_DEFAULT             16
#define AUDIO_SELECT_MASTER_MODE                17
#define AUDIO_STREAM_INFO_TYPE_INPUT            18
#define AUDIO_STREAM_INFO_TYPE_PREPROC          19
#define AUDIO_STREAM_INFO_TYPE_MASTER           20
#define AUDIO_STREAM_INFO_TYPE_POSTPROC         21
#define AUDIO_STREAM_INFO_TYPE_OUTPUT           22
#define AUDIO_STREAM_INFO_INPUT_CHANNELS        23
#define AUDIO_STREAM_INFO_INPUT_CHANNEL_NAMES   24
#define AUDIO_STREAM_INFO_INPUT_SAMPLERATE      25
#define AUDIO_STREAM_INFO_OUTPUT_CHANNELS       26
#define AUDIO_STREAM_INFO_OUTPUT_CHANNEL_NAMES  27
#define AUDIO_STREAM_INFO_OUTPUT_SAMPLERATE     28
#define AUDIO_STREAM_INFO_CPU_USAGE             29

/*! Addon settings control list id's */
#define AUDIO_SETTINGS_MENUS                    31 // to 60
#define AUDIO_SETTINGS_MENUS_END                60

/*! Label list id */
#define INPUT_TYPE_LABEL_START                  15001


CGUIDialogAudioDSPSettings::CGUIDialogAudioDSPSettings(void)
    : CGUIDialog(WINDOW_DIALOG_AUDIO_DSP_OSD_SETTINGS, "DialogAudioDSPSettings.xml")
{
  m_ActiveStreamId          = 0;
  m_CurrentMenu             = AUDIO_MENU_MAIN;
  m_OldMenu                 = AUDIO_MENU_MAIN;
  m_LastMenu                = AUDIO_MENU_MAIN;

  m_pOriginalSpin           = NULL;
  m_pOriginalRadioButton    = NULL;
  m_pOriginalSettingsButton = NULL;
  m_pOriginalSlider         = NULL;
  m_pOriginalSeparator      = NULL;
  m_pOriginalLabel          = NULL;
  m_usePopupSliders         = false;
  m_loadType                = KEEP_IN_MEMORY;
}

CGUIDialogAudioDSPSettings::~CGUIDialogAudioDSPSettings(void)
{
}

bool CGUIDialogAudioDSPSettings::OnMessage(CGUIMessage &message)
{
  switch (message.GetMessage())
  {
  case GUI_MSG_CLICKED:
    {
      unsigned int iControl = message.GetSenderId();
      if (iControl >= CONTROL_START && iControl < CONTROL_PAGE)
      {
        unsigned int settingNum = iControl - CONTROL_START;
        if (settingNum >= m_settings.size()) return false;
        SettingInfo &setting = m_settings.at(settingNum);
        if (setting.type == SettingInfo::SPIN)
        {
          CGUISpinControlEx *pControl = (CGUISpinControlEx *)GetControl(iControl);
          if (setting.data) *(int *)setting.data = pControl->GetValue();
        }
        else if (setting.type == SettingInfo::BUTTON_DIALOG)
        {
          CGUIButtonControl *pControl = (CGUIButtonControl *)GetControl(iControl);
          if (setting.data) *(std::string *)setting.data = pControl->GetLabel2();
        }
        else if (setting.type == SettingInfo::CHECK)
        {
          CGUIRadioButtonControl *pControl = (CGUIRadioButtonControl *)GetControl(iControl);
          if (setting.data) *(bool *)setting.data = pControl->IsSelected();
        }
        else if (setting.type == SettingInfo::SLIDER)
        {
          CGUISettingsSliderControl *pControl = (CGUISettingsSliderControl *)GetControl(iControl);
          if (setting.data) *(float *)setting.data = pControl->GetFloatValue();
          if (setting.formatFunction) pControl->SetTextValue(setting.formatFunction(pControl->GetFloatValue(), setting.interval));
        }
        else if (setting.type == SettingInfo::BUTTON && m_usePopupSliders && setting.data)
        { // we're using popup sliders
          CGUIDialogSlider::ShowAndGetInput(CStdString(setting.name), *(float *)setting.data, setting.min, setting.interval, setting.max, this, &setting);
          if (setting.formatFunction)
            SET_CONTROL_LABEL2(iControl, setting.formatFunction(*(float *)setting.data, setting.interval));
        }
        OnSettingChanged(setting);
      }
      return true;
    }
    break;
  case GUI_MSG_WINDOW_DEINIT:
    {
      m_ActiveStreamProcess = CActiveAEDSPProcessPtr();
      m_CurrentMenu         = m_LastMenu;
      m_LastMenu            = AUDIO_MENU_MAIN;

      CGUIDialog::OnMessage(message);
      FreeControls();
      m_settings.clear();
      return true;
    }
    break;
  }
  return CGUIDialog::OnMessage(message);
}

void CGUIDialogAudioDSPSettings::OnInitWindow()
{
  m_usePopupSliders = g_SkinInfo->HasSkinFile("DialogSlider.xml");

  m_Menus.clear();
  m_audioCaps.clear();
  if (g_application.m_pPlayer->HasPlayer())
    g_application.m_pPlayer->GetAudioCapabilities(m_audioCaps);

  // clear out any old settings
  m_settings.clear();

  m_ActiveStreamId      = CActiveAEDSP::Get().GetActiveStreamId();
  m_ActiveStreamProcess = CActiveAEDSP::Get().GetDSPProcess(m_ActiveStreamId);
  if (m_ActiveStreamId == (unsigned int)-1 || !m_ActiveStreamProcess)
  {
    m_CurrentMenu = AUDIO_MENU_MAIN;
    Close(true);
    return;
  }

  int modeUniqueId;
  m_ActiveStreamProcess->GetMasterModeTypeInformation(m_streamTypeUsed, m_baseTypeUsed, modeUniqueId);

  // create our settings
  if (m_CurrentMenu == AUDIO_MENU_MAIN)
  {
    SET_CONTROL_LABEL(CONTROL_SETTINGS_LABEL, g_localizeStrings.Get(15028));

    int modesAvailable = 0;
    for (int i = 0; i < AE_DSP_ASTREAM_AUTO; i++)
    {
      m_MasterModes[i].clear();
      m_ActiveStreamProcess->GetAvailableMasterModes((AE_DSP_STREAMTYPE)i, m_MasterModes[i]);
      if (!m_MasterModes[i].empty()) modesAvailable++;
    }

    if (modesAvailable > 0)
    {
      /* about size() > 1, it is always the fallback (ignore of master processing) present. */
      vector<pair<int, int> > modeEntries;
      if (m_MasterModes[AE_DSP_ASTREAM_BASIC].size() > 1)
        modeEntries.push_back(pair<int, int>(AE_DSP_ASTREAM_BASIC,   INPUT_TYPE_LABEL_START+AE_DSP_ASTREAM_BASIC));
      if (m_MasterModes[AE_DSP_ASTREAM_MUSIC].size() > 1)
        modeEntries.push_back(pair<int, int>(AE_DSP_ASTREAM_MUSIC,   INPUT_TYPE_LABEL_START+AE_DSP_ASTREAM_MUSIC));
      if (m_MasterModes[AE_DSP_ASTREAM_MOVIE].size() > 1)
        modeEntries.push_back(pair<int, int>(AE_DSP_ASTREAM_MOVIE,   INPUT_TYPE_LABEL_START+AE_DSP_ASTREAM_MOVIE));
      if (m_MasterModes[AE_DSP_ASTREAM_GAME].size() > 1)
        modeEntries.push_back(pair<int, int>(AE_DSP_ASTREAM_GAME,    INPUT_TYPE_LABEL_START+AE_DSP_ASTREAM_GAME));
      if (m_MasterModes[AE_DSP_ASTREAM_APP].size() > 1)
        modeEntries.push_back(pair<int, int>(AE_DSP_ASTREAM_APP,     INPUT_TYPE_LABEL_START+AE_DSP_ASTREAM_APP));
      if (m_MasterModes[AE_DSP_ASTREAM_MESSAGE].size() > 1)
        modeEntries.push_back(pair<int, int>(AE_DSP_ASTREAM_MESSAGE, INPUT_TYPE_LABEL_START+AE_DSP_ASTREAM_MESSAGE));
      if (m_MasterModes[AE_DSP_ASTREAM_PHONE].size() > 1)
        modeEntries.push_back(pair<int, int>(AE_DSP_ASTREAM_PHONE,   INPUT_TYPE_LABEL_START+AE_DSP_ASTREAM_PHONE));
      if (modesAvailable > 1 && m_MasterModes[m_streamTypeUsed].size() > 1)
        modeEntries.insert(modeEntries.begin(), pair<int, int>(AE_DSP_ASTREAM_AUTO, 14061));

      AddSpin(AUDIO_SETTING_CONTENT_TYPE, 15021, (int*)&CMediaSettings::Get().GetCurrentAudioSettings().m_MasterStreamTypeSel, modeEntries);
    }

    CMediaSettings::Get().GetCurrentAudioSettings().m_MasterStreamType = m_streamTypeUsed;

    bool addonMasterModeSetupPresent = false;

    vector<pair<int, std::string> > entries;
    for (unsigned int i = 0; i < m_MasterModes[m_streamTypeUsed].size(); i++)
    {
      if (m_MasterModes[m_streamTypeUsed][i])
      {
        AE_DSP_ADDON addon;
        int modeId = m_MasterModes[m_streamTypeUsed][i]->ModeID();
        if (modeId == AE_DSP_MASTER_MODE_ID_PASSOVER || modeId >= AE_DSP_MASTER_MODE_ID_INTERNAL_TYPES)
        {
          entries.push_back(pair<int, std::string>(modeId, g_localizeStrings.Get(m_MasterModes[m_streamTypeUsed][i]->ModeName())));
        }
        else if (CActiveAEDSP::Get().GetAudioDSPAddon(m_MasterModes[m_streamTypeUsed][i]->AddonID(), addon))
        {
          entries.push_back(pair<int, std::string>(modeId, addon->GetString(m_MasterModes[m_streamTypeUsed][i]->ModeName())));
          if (!addonMasterModeSetupPresent)
            addonMasterModeSetupPresent = m_MasterModes[m_streamTypeUsed][i]->HasSettingsDialog();
        }
      }
    }
    AddSpin(AUDIO_SELECT_MASTER_MODE,
            15022,
            (int*)&CMediaSettings::Get().GetCurrentAudioSettings().m_MasterModes[m_streamTypeUsed][m_baseTypeUsed],
            entries);

    AddSeparator(AUDIO_SEPERATOR_1);

    m_volume = g_application.GetVolume(false);
    AddSlider(AUDIO_SETTINGS_VOLUME, 13376, &m_volume, VOLUME_MINIMUM, VOLUME_MAXIMUM / 100.0f, VOLUME_MAXIMUM, FormatPercentAsDecibel, false);
    if (SupportsAudioFeature(IPC_AUD_AMP))
    {
      AddSlider(AUDIO_SETTINGS_VOLUME_AMPLIFICATION,
                660,
                &CMediaSettings::Get().GetCurrentVideoSettings().m_VolumeAmplification,
                VOLUME_DRC_MINIMUM * 0.01f, (VOLUME_DRC_MAXIMUM - VOLUME_DRC_MINIMUM) / 6000.0f, VOLUME_DRC_MAXIMUM * 0.01f,
                FormatDecibel,
                false);
    }
    AddSeparator(AUDIO_SEPERATOR_2);

    if (addonMasterModeSetupPresent)
      AddButton(AUDIO_BUTTON_MASTER_MODE_SETUP, 15025);
    if (CActiveAEDSP::Get().HaveMenuHooks(AE_DSP_MENUHOOK_POST_PROCESS) || SupportsAudioFeature(IPC_AUD_OFFSET))
      AddButton(AUDIO_BUTTON_SPEAKER_OUTPUT_SETUP, 15026);
    if (CActiveAEDSP::Get().HaveMenuHooks(AE_DSP_MENUHOOK_RESAMPLE))
      AddButton(AUDIO_BUTTON_RESAMPLER_SETUP, 15033);
    if (CActiveAEDSP::Get().HaveMenuHooks(AE_DSP_MENUHOOK_PRE_PROCESS))
      AddButton(AUDIO_BUTTON_PRE_PROCESS_SETUP, 15039);
    if (CActiveAEDSP::Get().HaveMenuHooks(AE_DSP_MENUHOOK_MISCELLANEOUS))
      AddButton(AUDIO_BUTTON_MISC_SETUP, 15034);
    AddButton(AUDIO_BUTTON_AUDIO_INFORMATION, 15027);

    AddSeparator(AUDIO_SEPERATOR_3);
    AddButton(AUDIO_SETTINGS_MAKE_DEFAULT, 15032);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_MASTER_MODE_SETUP)
  {
    SET_CONTROL_LABEL(CONTROL_SETTINGS_LABEL, g_localizeStrings.Get(15029));

    unsigned int menuEntry = 0;
    for (unsigned int i = 0; i < m_MasterModes[m_streamTypeUsed].size(); i++)
    {
      if (m_MasterModes[m_streamTypeUsed][i]->HasSettingsDialog())
      {
        AE_DSP_ADDON addon;
        if (CActiveAEDSP::Get().GetAudioDSPAddon(m_MasterModes[m_streamTypeUsed][i]->AddonID(), addon))
        {
          AE_DSP_MENUHOOKS hooks;
          if (CActiveAEDSP::Get().GetMenuHooks(m_MasterModes[m_streamTypeUsed][i]->AddonID(), AE_DSP_MENUHOOK_MASTER_PROCESS, hooks))
          {
            for (unsigned int j = 0; j < hooks.size(); j++)
            {
              if (hooks[j].iRelevantModeId != m_MasterModes[m_streamTypeUsed][i]->AddonModeNumber())
                continue;

              MenuHookMember menu;
              menu.addonId                  = m_MasterModes[m_streamTypeUsed][i]->AddonID();
              menu.hook.category            = hooks[j].category;
              menu.hook.iHookId             = hooks[j].iHookId;
              menu.hook.iLocalizedStringId  = hooks[j].iLocalizedStringId;
              menu.hook.iRelevantModeId     = hooks[j].iRelevantModeId;
              m_Menus.push_back(menu);
              AddButton(AUDIO_SETTINGS_MENUS+menuEntry++, addon->GetString(m_MasterModes[m_streamTypeUsed][i]->ModeSetupName()));
              break;
            }
          }
        }
      }
    }
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_SPEAKER_OUTPUT_SETUP)
  {
    SET_CONTROL_LABEL(CONTROL_SETTINGS_LABEL, g_localizeStrings.Get(15030));

    if (SupportsAudioFeature(IPC_AUD_OFFSET))
    {
      AddSlider(AUDIO_SETTINGS_DELAY,
                297,
                &CMediaSettings::Get().GetCurrentVideoSettings().m_AudioDelay,
                -g_advancedSettings.m_videoAudioDelayRange,
                .025f,
                g_advancedSettings.m_videoAudioDelayRange,
                FormatDelay);
      AddSeparator(AUDIO_SEPERATOR_1);
    }

    GetAudioDSPMenus(AE_DSP_MENUHOOK_POST_PROCESS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_RESAMPLER_SETUP)
  {
    SET_CONTROL_LABEL(CONTROL_SETTINGS_LABEL, g_localizeStrings.Get(15035));

    GetAudioDSPMenus(AE_DSP_MENUHOOK_RESAMPLE);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_PRE_PROCESS_SETUP)
  {
    SET_CONTROL_LABEL(CONTROL_SETTINGS_LABEL, g_localizeStrings.Get(15037));

    GetAudioDSPMenus(AE_DSP_MENUHOOK_PRE_PROCESS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_MISC_SETUP)
  {
    SET_CONTROL_LABEL(CONTROL_SETTINGS_LABEL, g_localizeStrings.Get(15038));

    GetAudioDSPMenus(AE_DSP_MENUHOOK_MISCELLANEOUS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_AUDIO_INFORMATION)
  {
    m_usePopupSliders = false;

    SET_CONTROL_LABEL(CONTROL_SETTINGS_LABEL, g_localizeStrings.Get(15031));

    m_ActiveModes.clear();
    m_ActiveStreamProcess->GetActiveModes(AE_DSP_MODE_TYPE_UNDEFINED, m_ActiveModes);
    m_ActiveModesCPUUsage.resize(m_ActiveModes.size());

    AddLabel(AUDIO_SETTING_CONTENT_LABEL, 15089);
    m_InputChannels = StringUtils::Format("%i", m_ActiveStreamProcess->GetInputChannels());
    AddString(AUDIO_STREAM_INFO_INPUT_CHANNELS, 15091, &m_InputChannels);
    m_InputChannelNames = m_ActiveStreamProcess->GetInputChannelNames();
    AddString(AUDIO_STREAM_INFO_INPUT_CHANNEL_NAMES, 15093, &m_InputChannelNames);
    m_InputSamplerate = StringUtils::Format("%i Hz", (int)m_ActiveStreamProcess->GetInputSamplerate());
    AddString(AUDIO_STREAM_INFO_INPUT_SAMPLERATE, 15092, &m_InputSamplerate);

    AddSeparator(AUDIO_SEPERATOR_1);

    AddLabel(AUDIO_SETTING_CONTENT_LABEL, 15090);
    m_OutputChannels = StringUtils::Format("%i", m_ActiveStreamProcess->GetOutputChannels());
    AddString(AUDIO_STREAM_INFO_OUTPUT_CHANNELS, 15091, &m_OutputChannels);
    m_OutputChannelNames = m_ActiveStreamProcess->GetOutputChannelNames();
    AddString(AUDIO_STREAM_INFO_OUTPUT_CHANNEL_NAMES, 15093, &m_OutputChannelNames);
    m_OutputSamplerate = StringUtils::Format("%i Hz", (int)m_ActiveStreamProcess->GetOutputSamplerate());
    AddString(AUDIO_STREAM_INFO_OUTPUT_SAMPLERATE, 15092, &m_OutputSamplerate);

    AddSeparator(AUDIO_SEPERATOR_2);

    AddLabel(AUDIO_SETTING_CONTENT_LABEL, 15081);
    m_CPUUsage = StringUtils::Format("%.02f %%", m_ActiveStreamProcess->GetCPUUsage());
    AddString(AUDIO_STREAM_INFO_CPU_USAGE, 15094, &m_CPUUsage);

    bool foundPreProcess = false;
	bool foundPostProcess = false;
    for (unsigned int i = 0; i < m_ActiveModes.size(); i++)
    {
      AE_DSP_ADDON addon;
      if (CActiveAEDSP::Get().GetAudioDSPAddon(m_ActiveModes[i]->AddonID(), addon))
      {
        std::string label;
        switch (m_ActiveModes[i]->ModeType())
        {
          case AE_DSP_MODE_TYPE_INPUT_RESAMPLE:
            AddLabel(AUDIO_STREAM_INFO_TYPE_INPUT, 15087);
            label = StringUtils::Format(g_localizeStrings.Get(15082), m_ActiveStreamProcess->GetProcessSamplerate());
            break;
          case AE_DSP_MODE_TYPE_OUTPUT_RESAMPLE:
            AddLabel(AUDIO_STREAM_INFO_TYPE_OUTPUT, 15088);
            label = StringUtils::Format(g_localizeStrings.Get(15083), m_ActiveStreamProcess->GetOutputSamplerate());
            break;
          case AE_DSP_MODE_TYPE_MASTER_PROCESS:
            AddLabel(AUDIO_STREAM_INFO_TYPE_MASTER, 15084);
            label = addon->GetString(m_ActiveModes[i]->ModeName());
            break;
          case AE_DSP_MODE_TYPE_PRE_PROCESS:
            if (!foundPreProcess)
            {
              foundPreProcess = true;
              AddLabel(AUDIO_STREAM_INFO_TYPE_PREPROC, 15085);
            }
            label = addon->GetString(m_ActiveModes[i]->ModeName());
            break;
          case AE_DSP_MODE_TYPE_POST_PROCESS:
            if (!foundPostProcess)
            {
              foundPostProcess = true;
              AddLabel(AUDIO_STREAM_INFO_TYPE_POSTPROC, 15086);
            }
            label = addon->GetString(m_ActiveModes[i]->ModeName());
            break;
          default:
          {
            label += addon->GetString(m_ActiveModes[i]->ModeName());
            label += " - ";
            label += addon->GetFriendlyName();
          }
        };
        m_ActiveModesCPUUsage[i] = m_ActiveModes[i]->CPUUsage();

        MenuHookMember menu;
        menu.addonId = -1;

        AE_DSP_MENUHOOKS hooks;
        if (CActiveAEDSP::Get().GetMenuHooks(m_ActiveModes[i]->AddonID(), AE_DSP_MENUHOOK_INFORMATION, hooks))
        {
          for (unsigned int j = 0; j < hooks.size(); j++)
          {
            if (hooks[j].iRelevantModeId != m_ActiveModes[i]->AddonModeNumber())
              continue;

            menu.addonId                  = m_ActiveModes[i]->AddonID();
            menu.hook.category            = hooks[j].category;
            menu.hook.iHookId             = hooks[j].iHookId;
            menu.hook.iLocalizedStringId  = hooks[j].iLocalizedStringId;
            menu.hook.iRelevantModeId     = hooks[j].iRelevantModeId;
            label += " ...";
            break;
          }
        }

        AddButton(AUDIO_SETTINGS_MENUS+i, label, &m_ActiveModesCPUUsage[i], 0.0f, 1.0f, 100.0f, FormatPercent);
        m_Menus.push_back(menu);
      }
    }
  }

  SetInitialVisibility();

  // cleanup first, if necessary
  FreeControls();

  m_pOriginalSpin           = (CGUISpinControlEx*)GetControl(CONTROL_DEFAULT_SPIN);
  m_pOriginalRadioButton    = (CGUIRadioButtonControl *)GetControl(CONTROL_DEFAULT_RADIOBUTTON);
  m_pOriginalSettingsButton = (CGUIButtonControl *)GetControl(CONTROL_DEFAULT_BUTTON);
  m_pOriginalSlider         = (CGUISettingsSliderControl *)GetControl(CONTROL_DEFAULT_SLIDER);
  m_pOriginalSeparator      = (CGUIImage *)GetControl(CONTROL_DEFAULT_SEPARATOR);
  m_pOriginalLabel          = (CGUILabelControl *)GetControl(CONTROL_DEFAULT_LABEL);

  if (m_pOriginalSpin)
    m_pOriginalSpin->SetVisible(false);
  if (m_pOriginalRadioButton)
    m_pOriginalRadioButton->SetVisible(false);
  if (m_pOriginalSettingsButton)
    m_pOriginalSettingsButton->SetVisible(false);
  if (m_pOriginalSlider)
    m_pOriginalSlider->SetVisible(false);
  if (m_pOriginalSeparator)
    m_pOriginalSeparator->SetVisible(false);
  if (m_pOriginalLabel)
    m_pOriginalLabel->SetVisible(false);

  CGUIControlGroupList *group = (CGUIControlGroupList *)GetControl(CONTROL_GROUP_LIST);
  if (!group)
    return;

  if (!m_settings.size())
  { // no settings available
    SET_CONTROL_VISIBLE(CONTROL_NONE_AVAILABLE);
    return;
  }
  else
  {
    SET_CONTROL_HIDDEN(CONTROL_NONE_AVAILABLE);
  }

  // create our controls
  for (unsigned int i = 0; i < m_settings.size(); i++)
  {
    SettingInfo &setting = m_settings.at(i);
    AddSetting(setting, group->GetWidth(), CONTROL_START + i);
  }

  // set the default focus control
  m_lastControlID = CONTROL_START;

  for (unsigned int i = 0; i < m_settings.size(); i++)
  {
    if (m_settings.at(i).id == m_OldMenu)
    {
      m_lastControlID = CONTROL_START + i;
      break;
    }
  }
  CGUIDialog::OnInitWindow();
}

void CGUIDialogAudioDSPSettings::UpdateSetting(unsigned int id)
{
  unsigned int settingNum = (unsigned int)-1;
  for (unsigned int i = 0; i < m_settings.size(); i++)
  {
    if (m_settings[i].id == id)
    {
      settingNum = i;
      break;
    }
  }
  if(settingNum == (unsigned int)-1)
    return;

  SettingInfo &setting = m_settings.at(settingNum);
  unsigned int controlID = settingNum + CONTROL_START;
  if (setting.type == SettingInfo::SPIN)
  {
    CGUISpinControlEx *pControl = (CGUISpinControlEx *)GetControl(controlID);
    if (pControl && setting.data) pControl->SetValue(*(int *)setting.data);
  }
  else if (setting.type == SettingInfo::CHECK)
  {
    CGUIRadioButtonControl *pControl = (CGUIRadioButtonControl *)GetControl(controlID);
    if (pControl && setting.data) pControl->SetSelected(*(bool *)setting.data);
  }
  else if (setting.type == SettingInfo::SLIDER)
  {
    CGUISettingsSliderControl *pControl = (CGUISettingsSliderControl *)GetControl(controlID);
    if (pControl && setting.data)
    {
      float value = *(float *)setting.data;
      pControl->SetFloatValue(value);
      if (setting.formatFunction) pControl->SetTextValue(setting.formatFunction(value, setting.interval));
    }
  }
  else if (setting.type == SettingInfo::BUTTON_DIALOG)
  {
    SET_CONTROL_LABEL(controlID,setting.name);
    CGUIButtonControl *pControl = (CGUIButtonControl *)GetControl(controlID);
    if (pControl && setting.data) pControl->SetLabel2(*(std::string *)setting.data);
  }
  else if (setting.type == SettingInfo::BUTTON)
  {
    SET_CONTROL_LABEL(controlID,setting.name);
    CGUIButtonControl *pControl = (CGUIButtonControl *)GetControl(controlID);
    if (pControl && setting.data) pControl->SetLabel2(setting.formatFunction(*(float *)setting.data, setting.interval));
  }
  else if (setting.type == SettingInfo::STRING)
  {
    SET_CONTROL_LABEL(controlID, setting.name);
    string strNewValue = string(*(std::string *)setting.data);
    if (strNewValue.empty())
      strNewValue = "-";
    SET_CONTROL_LABEL2(controlID, strNewValue);
  }
  else if (setting.type == SettingInfo::LABEL)
  {
    SET_CONTROL_LABEL(controlID, setting.name);
  }

  if (setting.enabled)
  {
    CONTROL_ENABLE(controlID);
  }
  else
  {
    CONTROL_DISABLE(controlID);
  }
}

bool CGUIDialogAudioDSPSettings::OnBack(int actionID)
{
  m_OldMenu = m_CurrentMenu;
  switch (m_CurrentMenu)
  {
    case AUDIO_BUTTON_MASTER_MODE_SETUP:
    case AUDIO_BUTTON_SPEAKER_OUTPUT_SETUP:
    case AUDIO_BUTTON_AUDIO_INFORMATION:
    case AUDIO_BUTTON_RESAMPLER_SETUP:
    case AUDIO_BUTTON_PRE_PROCESS_SETUP:
    case AUDIO_BUTTON_MISC_SETUP:
      FreeControls();
      m_CurrentMenu = AUDIO_MENU_MAIN;
      OnInitWindow();
      return true;
  }

  return CGUIDialog::OnBack(actionID);
}

void CGUIDialogAudioDSPSettings::FreeControls()
{
  // just clear our group list
  CGUIControlGroupList *group = (CGUIControlGroupList *)GetControl(CONTROL_GROUP_LIST);
  if (group)
  {
    group->FreeResources();
    group->ClearAll();
  }
}

void CGUIDialogAudioDSPSettings::OnSliderChange(void *data, CGUISliderControl *slider)
{
  if (!data || !slider)
    return;

  SettingInfo *setting = (SettingInfo *)data;
  if (setting->type == SettingInfo::SLIDER || (setting->type == SettingInfo::BUTTON && m_usePopupSliders && !slider->GetRangeSelection()))
  {
    *(float *)setting->data = slider->GetFloatValue();
    OnSettingChanged(*setting);
    if (setting->formatFunction)
      slider->SetTextValue(setting->formatFunction(slider->GetFloatValue(), setting->interval));
  }
}

void CGUIDialogAudioDSPSettings::OnSettingChanged(SettingInfo &setting)
{
  // check and update anything that needs it
  if (setting.id == AUDIO_SETTINGS_MAKE_DEFAULT)
  {
    if (!g_passwordManager.CheckSettingLevelLock(SettingLevelExpert) &&
        CProfilesManager::Get().GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE)
      return;

    // prompt user if they are sure
    if (CGUIDialogYesNo::ShowAndGetInput(12376, 750, 0, 12377))
    { // reset the settings
      CActiveAEDSPDatabase db;
      db.Open();
      db.EraseActiveDSPSettings();
      db.Close();
      CMediaSettings::Get().GetDefaultAudioSettings() = CMediaSettings::Get().GetCurrentAudioSettings();
      CMediaSettings::Get().GetDefaultAudioSettings().m_MasterStreamType = AE_DSP_ASTREAM_AUTO;
      CSettings::Get().Save();
    }
  }

  if (m_CurrentMenu == AUDIO_MENU_MAIN)
  {
    if (setting.id == AUDIO_SETTING_CONTENT_TYPE)
    {
      int type = CMediaSettings::Get().GetCurrentAudioSettings().m_MasterStreamTypeSel;
      if (type == AE_DSP_ASTREAM_AUTO)
        type = m_ActiveStreamProcess->GetDetectedStreamType();

      CMediaSettings::Get().GetCurrentAudioSettings().m_MasterStreamType = type;

      /* Set the input stream type if any modes are available for this type */
      if (type >= AE_DSP_ASTREAM_BASIC && type < AE_DSP_ASTREAM_AUTO && !m_MasterModes[type].empty())
      {
        /* Find the master mode id for the selected stream type if it was not known before */
        if (CMediaSettings::Get().GetCurrentAudioSettings().m_MasterModes[type][m_baseTypeUsed] < 0)
          CMediaSettings::Get().GetCurrentAudioSettings().m_MasterModes[type][m_baseTypeUsed] = m_MasterModes[type][0]->ModeID();

        /* Switch now the master mode and stream type for audio dsp processing */
        m_ActiveStreamProcess->SetMasterMode((AE_DSP_STREAMTYPE)type,
                                             CMediaSettings::Get().GetCurrentAudioSettings().m_MasterModes[type][m_baseTypeUsed],
                                             true);
      }
      else
      {
        CLog::Log(LOGERROR, "ActiveAE DSP Settings - %s - Change of audio stream type failed (type = %i)", __FUNCTION__, type);
      }
    }
    else if (setting.id == AUDIO_SETTING_STREAM_SELECTION)
    {
      FreeControls();
      OnInitWindow();
    }
    else if (setting.id == AUDIO_SELECT_MASTER_MODE)
    {
      m_ActiveStreamProcess->SetMasterMode(m_streamTypeUsed,
                                           CMediaSettings::Get().GetCurrentAudioSettings().m_MasterModes[m_streamTypeUsed][m_baseTypeUsed]);
    }
    else if (setting.id == AUDIO_SETTINGS_VOLUME)
    {
      g_application.SetVolume(m_volume, false); //false - value is not in percent
    }
    else if (setting.id == AUDIO_SETTINGS_VOLUME_AMPLIFICATION)
    {
      g_application.m_pPlayer->SetDynamicRangeCompression((long)(CMediaSettings::Get().GetCurrentVideoSettings().m_VolumeAmplification * 100));
    }
    else if (setting.id >= AUDIO_BUTTON_MASTER_MODE_SETUP && setting.id <= AUDIO_BUTTON_AUDIO_INFORMATION)
    {
      FreeControls();
      m_CurrentMenu = setting.id;
      OnInitWindow();
    }
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_MASTER_MODE_SETUP)
  {
    OpenAudioDSPMenu(setting.id-AUDIO_SETTINGS_MENUS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_SPEAKER_OUTPUT_SETUP)
  {
    if (setting.id == AUDIO_SETTINGS_DELAY)
      g_application.m_pPlayer->SetAVDelay(CMediaSettings::Get().GetCurrentVideoSettings().m_AudioDelay);
    else
      OpenAudioDSPMenu(setting.id-AUDIO_SETTINGS_MENUS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_RESAMPLER_SETUP)
  {
    OpenAudioDSPMenu(setting.id-AUDIO_SETTINGS_MENUS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_PRE_PROCESS_SETUP)
  {
    OpenAudioDSPMenu(setting.id-AUDIO_SETTINGS_MENUS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_MISC_SETUP)
  {
    OpenAudioDSPMenu(setting.id-AUDIO_SETTINGS_MENUS);
  }
  else if (m_CurrentMenu == AUDIO_BUTTON_AUDIO_INFORMATION)
  {
    if (setting.id >= AUDIO_SETTINGS_MENUS && setting.id <= AUDIO_SETTINGS_MENUS_END)
    {
      if (!OpenAudioDSPMenu(setting.id-AUDIO_SETTINGS_MENUS))
        CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Info, g_localizeStrings.Get(15031), g_localizeStrings.Get(15095));
    }
  }
}

void CGUIDialogAudioDSPSettings::FrameMove()
{
  if (CActiveAEDSP::Get().GetProcessingStreamsAmount() == 0)
  {
    Close(true);
    return;
  }

  m_volume = g_application.GetVolume(false);
  UpdateSetting(AUDIO_SETTINGS_VOLUME);

  if (g_application.m_pPlayer->HasPlayer())
  {
    bool forceReload = false;
    unsigned int  streamId = CActiveAEDSP::Get().GetActiveStreamId();
    if (m_ActiveStreamId != streamId)
    {
      m_ActiveStreamId      = streamId;
      m_ActiveStreamProcess = CActiveAEDSP::Get().GetDSPProcess(m_ActiveStreamId);
      if (m_ActiveStreamId == (unsigned int)-1 || !m_ActiveStreamProcess)
      {
        Close(true);
        return;
      }
      forceReload = true;
    }

    int               modeUniqueId;
    AE_DSP_BASETYPE   usedBaseType;
    AE_DSP_STREAMTYPE streamTypeUsed;
    m_ActiveStreamProcess->GetMasterModeTypeInformation(streamTypeUsed, usedBaseType, modeUniqueId);
    if (forceReload || m_baseTypeUsed != usedBaseType || m_streamTypeUsed != streamTypeUsed)
    {
      m_baseTypeUsed   = usedBaseType;
      m_streamTypeUsed = streamTypeUsed;

      /*!
      * Update settings
      */
      int selType = CMediaSettings::Get().GetCurrentAudioSettings().m_MasterStreamTypeSel;
      CMediaSettings::Get().GetCurrentAudioSettings().m_MasterModes[streamTypeUsed][usedBaseType] = modeUniqueId;
      CMediaSettings::Get().GetCurrentAudioSettings().m_MasterModes[selType][usedBaseType]        = modeUniqueId;
      CMediaSettings::Get().GetCurrentAudioSettings().m_MasterStreamBase                          = usedBaseType;
      CMediaSettings::Get().GetCurrentAudioSettings().m_MasterStreamType                          = streamTypeUsed;

      FreeControls();
      OnInitWindow();
    }

    // these settings can change on the fly
    if (m_CurrentMenu == AUDIO_BUTTON_AUDIO_INFORMATION)
    {
      m_CPUUsage = StringUtils::Format("%.02f %%", m_ActiveStreamProcess->GetCPUUsage());
      UpdateSetting(AUDIO_STREAM_INFO_CPU_USAGE);

      for (unsigned int i = 0; i < m_ActiveModes.size(); i++)
      {
        m_ActiveModesCPUUsage[i] = m_ActiveModes[i]->CPUUsage();
        UpdateSetting(AUDIO_SETTINGS_MENUS+i);
      }
    }
    UpdateSetting(AUDIO_SETTINGS_DELAY);
  }

  CGUIDialog::FrameMove();
}

bool CGUIDialogAudioDSPSettings::SupportsAudioFeature(int feature)
{
  for (Features::iterator itr = m_audioCaps.begin(); itr != m_audioCaps.end(); itr++)
  {
    if(*itr == feature || *itr == IPC_AUD_ALL)
      return true;
  }
  return false;
}

void CGUIDialogAudioDSPSettings::GetAudioDSPMenus(AE_DSP_MENUHOOK_CAT category)
{
  AE_DSP_ADDONMAP addonMap;
  if (CActiveAEDSP::Get().GetEnabledAudioDSPAddons(addonMap) > 0)
  {
    for (AE_DSP_ADDONMAP_ITR itr = addonMap.begin(); itr != addonMap.end(); itr++)
    {
      AE_DSP_MENUHOOKS hooks;
      if (CActiveAEDSP::Get().GetMenuHooks(itr->second->GetID(), category, hooks))
      {
        for (unsigned int i = 0; i < hooks.size(); i++)
        {
          if (!m_ActiveStreamProcess->IsMenuHookModeActive(hooks[i].category, itr->second->GetID(), hooks[i].iRelevantModeId))
            continue;

          MenuHookMember menu;
          menu.addonId                  = itr->second->GetID();
          menu.hook.category            = hooks[i].category;
          menu.hook.iHookId             = hooks[i].iHookId;
          menu.hook.iLocalizedStringId  = hooks[i].iLocalizedStringId;
          menu.hook.iRelevantModeId     = hooks[i].iRelevantModeId;
          m_Menus.push_back(menu);
        }
      }
    }
  }

  for (unsigned int i = 0; i < m_Menus.size(); i++)
  {
    AE_DSP_ADDON addon;
    if (CActiveAEDSP::Get().GetAudioDSPAddon(m_Menus[i].addonId, addon))
    {
      std::string modeName = addon->GetString(m_Menus[i].hook.iLocalizedStringId);
      if (modeName.empty())
        modeName = g_localizeStrings.Get(15041);
      AddButton(AUDIO_SETTINGS_MENUS+i, modeName);
    }
  }
}

bool CGUIDialogAudioDSPSettings::OpenAudioDSPMenu(unsigned int setupEntry)
{
  if (setupEntry >= m_Menus.size())
    return false;

  AE_DSP_ADDON addon;
  if (!CActiveAEDSP::Get().GetAudioDSPAddon(m_Menus[setupEntry].addonId, addon))
    return false;

  AE_DSP_MENUHOOK       hook;
  AE_DSP_MENUHOOK_DATA  hookData;

  hook.category           = m_Menus[setupEntry].hook.category;
  hook.iHookId            = m_Menus[setupEntry].hook.iHookId;
  hook.iLocalizedStringId = m_Menus[setupEntry].hook.iLocalizedStringId;
  hook.iRelevantModeId    = m_Menus[setupEntry].hook.iRelevantModeId;
  hookData.category       = m_Menus[setupEntry].hook.category;
  switch (hookData.category)
  {
    case AE_DSP_MENUHOOK_PRE_PROCESS:
    case AE_DSP_MENUHOOK_MASTER_PROCESS:
    case AE_DSP_MENUHOOK_RESAMPLE:
    case AE_DSP_MENUHOOK_POST_PROCESS:
      hookData.data.iStreamId = m_ActiveStreamId;
      break;
    default:
      break;
  }

  m_LastMenu = m_CurrentMenu;
  int iLastSelected = GetFocusedControlID();
  Close();
  addon->CallMenuHook(hook, hookData);

  //Lock graphic context here as it is sometimes called from non rendering threads
  //maybe we should have a critical section per window instead??
  CSingleLock lock(g_graphicsContext);

  if (CActiveAEDSP::Get().GetProcessingStreamsAmount() == 0 || !g_windowManager.Initialized())
  {
    m_CurrentMenu = AUDIO_MENU_MAIN;
    return true; // don't do anything
  }

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

  if (iLastSelected > -1)
    SET_CONTROL_FOCUS(iLastSelected, 0);

  if (!m_windowLoaded)
  {
    m_CurrentMenu = AUDIO_MENU_MAIN;
    Close(true);
  }

  lock.Leave();
  return true;
}

void CGUIDialogAudioDSPSettings::AddSetting(SettingInfo &setting, float width, int iControlID)
{
  CGUIControl *pControl = NULL;
  if (setting.type == SettingInfo::BUTTON_DIALOG && m_pOriginalSettingsButton)
  {
    pControl = new CGUIButtonControl(*m_pOriginalSettingsButton);
    if (!pControl) return ;
    ((CGUIButtonControl *)pControl)->SetLabel(setting.name);
    pControl->SetWidth(width);
    if (setting.data) ((CGUIButtonControl *)pControl)->SetLabel2(*(std::string *)setting.data);
  }
  else if (setting.type == SettingInfo::BUTTON && m_pOriginalSettingsButton)
  {
    pControl = new CGUIButtonControl(*m_pOriginalSettingsButton);
    if (!pControl) return ;
    ((CGUIButtonControl *)pControl)->SetLabel(setting.name);
    if (setting.formatFunction)
      ((CGUIButtonControl *)pControl)->SetLabel2(setting.formatFunction(*(float *)setting.data, setting.interval));
    pControl->SetWidth(width);
  }
  else if (setting.type == SettingInfo::SEPARATOR && m_pOriginalSeparator)
  {
    pControl = new CGUIImage(*m_pOriginalSeparator);
    if (!pControl) return ;
    pControl->SetWidth(width);
  }
  else if (setting.type == SettingInfo::SPIN && setting.entry.size() > 0 && m_pOriginalSpin)
  {
    pControl = new CGUISpinControlEx(*m_pOriginalSpin);
    if (!pControl) return ;
    pControl->SetWidth(width);
    ((CGUISpinControlEx *)pControl)->SetText(setting.name);
    pControl->SetWidth(width);
    for (unsigned int i = 0; i < setting.entry.size(); i++)
      ((CGUISpinControlEx *)pControl)->AddLabel(setting.entry[i].second, setting.entry[i].first);
    if (setting.data) ((CGUISpinControlEx *)pControl)->SetValue(*(int *)setting.data);
  }
  else if (setting.type == SettingInfo::SLIDER)
  {
    if (!m_pOriginalSlider) return;
    pControl = new CGUISettingsSliderControl(*m_pOriginalSlider);
    if (!pControl) return ;
    pControl->SetWidth(width);
    ((CGUISettingsSliderControl *)pControl)->SetText(setting.name);
    if (setting.formatFunction)
      ((CGUISettingsSliderControl *)pControl)->SetTextValue(setting.formatFunction(*(float *)setting.data, setting.interval));
    ((CGUISettingsSliderControl *)pControl)->SetType(SPIN_CONTROL_TYPE_FLOAT);
    ((CGUISettingsSliderControl *)pControl)->SetFloatRange(setting.min, setting.max);
    ((CGUISettingsSliderControl *)pControl)->SetFloatInterval(setting.interval);
    if (setting.data) ((CGUISettingsSliderControl *)pControl)->SetFloatValue(*(float *)setting.data);
  }
  else if (setting.type == SettingInfo::STRING && m_pOriginalSettingsButton)
  {
    pControl = new CGUIButtonControl(*m_pOriginalSettingsButton);
    if (!pControl) return ;
    ((CGUIButtonControl *)pControl)->SetLabel(setting.name);
    string strValue = string(*(std::string *)setting.data);
    if (strValue.empty())
      strValue = "-";
    ((CGUIButtonControl *)pControl)->SetLabel2(strValue);
    pControl->SetWidth(width);
  }
  else if (setting.type == SettingInfo::LABEL && m_pOriginalLabel)
  {
    pControl = new CGUILabelControl(*m_pOriginalLabel);
    if (!pControl) return ;
    ((CGUILabelControl *)pControl)->SetLabel(setting.name);
    pControl->SetWidth(width);
  }
  if (!pControl) return;

  pControl->SetID(iControlID);
  pControl->SetVisible(true);
  pControl->SetEnabled(setting.enabled);
  CGUIControlGroupList *group = (CGUIControlGroupList *)GetControl(CONTROL_GROUP_LIST);
  if (group)
  {
    pControl->AllocResources();
    group->AddControl(pControl);
  }
  else
    delete pControl;
}

void CGUIDialogAudioDSPSettings::AddButton(unsigned int id, int label, float *current, float min, float interval, float max, FORMATFUNCTION function)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = g_localizeStrings.Get(label);
  setting.type = SettingInfo::BUTTON;
  setting.data = current;
  setting.min = min;
  setting.max = max;
  setting.interval = interval;
  setting.formatFunction = function;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddButton(unsigned int id, std::string label, float *current, float min, float interval, float max, FORMATFUNCTION function)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = label;
  setting.type = SettingInfo::BUTTON;
  setting.data = current;
  setting.min = min;
  setting.max = max;
  setting.interval = interval;
  setting.formatFunction = function;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddButton(unsigned int id, int label, std::string *str, bool bOn)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = g_localizeStrings.Get(label);
  setting.type = SettingInfo::BUTTON_DIALOG;
  setting.enabled  = bOn;
  setting.data = str;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddButton(unsigned int id, std::string label, std::string *str, bool bOn)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = label;
  setting.type = SettingInfo::BUTTON_DIALOG;
  setting.enabled  = bOn;
  setting.data = str;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddString(unsigned int id, int label, std::string *current)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = g_localizeStrings.Get(label);
  setting.type = SettingInfo::STRING;
  setting.data = current;
  setting.enabled = true;
  setting.allowPopup = false;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddLabel(unsigned int id, int label)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = g_localizeStrings.Get(label);
  setting.type = SettingInfo::LABEL;
  setting.data = NULL;
  setting.enabled = false;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddBool(unsigned int id, int label, bool *on, bool enabled)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = g_localizeStrings.Get(label);
  setting.type = SettingInfo::CHECK;
  setting.data = on;
  setting.enabled = enabled;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddSpin(unsigned int id, int label, int *current, vector<pair<int, std::string> > &values)
{
  SettingInfo setting;
  setting.id = id;
  setting.name = g_localizeStrings.Get(label);
  setting.type = SettingInfo::SPIN;
  setting.data = current;
  setting.entry = values;
  if (values.size() <= 1)
    setting.enabled = false;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddSpin(unsigned int id, int label, int *current, vector<pair<int, int> > &values)
{
  vector<pair<int, std::string> > entries;
  for(unsigned i = 0; i < values.size(); i++)
    entries.push_back(make_pair(values[i].first, g_localizeStrings.Get(values[i].second)));
  AddSpin(id, label, current, entries);
}

void CGUIDialogAudioDSPSettings::AddSlider(unsigned int id, int label, float *current, float min, float interval, float max, FORMATFUNCTION function, bool allowPopup /* = true*/)
{
  if (m_usePopupSliders && allowPopup)
  {
    AddButton(id, label, current, min, interval, max, function);
    return;
  }
  SettingInfo setting;
  setting.id = id;
  setting.name = g_localizeStrings.Get(label);
  setting.type = SettingInfo::SLIDER;
  setting.min = min;
  setting.interval = interval;
  setting.max = max;
  setting.data = current;
  setting.formatFunction = function;
  m_settings.push_back(setting);
}

void CGUIDialogAudioDSPSettings::AddSeparator(unsigned int id)
{
  SettingInfo setting;
  setting.id = id;
  setting.type = SettingInfo::SEPARATOR;
  setting.data = NULL;
  m_settings.push_back(setting);
}

std::string CGUIDialogAudioDSPSettings::FormatPercent(float value, float minimum)
{
  return StringUtils::Format("%.2f %%", value);
}

std::string CGUIDialogAudioDSPSettings::FormatPercentAsDecibel(float value, float interval)
{
  return StringUtils::Format("%2.1f dB", CAEUtil::PercentToGain(value));
}

std::string CGUIDialogAudioDSPSettings::FormatDecibel(float value, float interval)
{
  return StringUtils::Format("%2.1f dB", value);;
}

std::string CGUIDialogAudioDSPSettings::FormatDelay(float value, float interval)
{
  std::string text;
  if (fabs(value) < 0.5f*interval)
    text = StringUtils::Format(g_localizeStrings.Get(22003).c_str(), 0.0);
  else if (value < 0)
    text = StringUtils::Format(g_localizeStrings.Get(22004).c_str(), fabs(value));
  else
    text = StringUtils::Format(g_localizeStrings.Get(22005).c_str(), value);
  return text;
}

