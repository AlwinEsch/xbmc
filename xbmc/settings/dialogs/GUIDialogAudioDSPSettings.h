#pragma once
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

#include "cores/AudioEngine/DSPAddons/ActiveAEDSPProcess.h"
#include "guilib/GUIDialog.h"
#include "dialogs/GUIDialogSlider.h"

typedef std::vector<int> Features;

class CGUISpinControlEx;
class CGUIButtonControl;
class CGUIRadioButtonControl;
class CGUISettingsSliderControl;
class CGUIImage;
class CGUILabelControl;

typedef std::string (*FORMATFUNCTION) (float value, float min);

class SettingInfo
{
public:
  enum SETTING_TYPE { NONE=0, BUTTON, BUTTON_DIALOG, CHECK, SPIN, SLIDER, SEPARATOR, STRING, LABEL };
  SettingInfo()
  {
    id = 0;
    data = NULL;
    type = NONE;
    enabled = true;
    allowPopup = true;
    min = 0;
    max = 0;
    interval = 0;
    formatFunction = NULL;
  };
  SETTING_TYPE type;
  std::string name;
  unsigned int id;
  void *data;
  float min;
  float max;
  float interval;
  FORMATFUNCTION formatFunction;
  std::vector<std::pair<int, std::string> > entry;
  bool enabled;
  bool allowPopup;
};

class CGUIDialogAudioDSPSettings : public CGUIDialog, public ISliderCallback
{
public:
  CGUIDialogAudioDSPSettings(void);
  virtual ~CGUIDialogAudioDSPSettings(void);

  virtual void OnSliderChange(void *data, CGUISliderControl *slider);

  virtual bool OnMessage(CGUIMessage &message);
  virtual bool OnBack(int actionID);
  virtual void FrameMove();

protected:
  virtual void OnInitWindow();

private:
  typedef struct
  {
    int              addonId;
    AE_DSP_MENUHOOK  hook;
  } MenuHookMember;

  void OnSettingChanged(SettingInfo &setting);
  bool SupportsAudioFeature(int feature);
  bool HaveActiveMenuHooks(AE_DSP_MENUHOOK_CAT category);
  void GetAudioDSPMenus(AE_DSP_MENUHOOK_CAT category, std::vector<MenuHookMember> &menus);
  bool OpenAudioDSPMenu(unsigned int setupEntry);

  void UpdateSetting(unsigned int setting);
  void FreeControls();

  void AddSetting(SettingInfo &setting, float width, int iControlID);

  void AddButton(unsigned int id, int label, float *current = NULL, float min = 0, float interval = 0, float max = 0, FORMATFUNCTION function = NULL);
  void AddButton(unsigned int id, int label, std::string *str, bool bOn=true);
  void AddButton(unsigned int id, std::string label, float *current = NULL, float min = 0, float interval = 0, float max = 0, FORMATFUNCTION function = NULL);
  void AddButton(unsigned int it, std::string label, std::string *str, bool bOn=true);
  void AddBool(unsigned int id, int label, bool *on, bool enabled = true);
  void AddString(unsigned int id, int label, std::string *current);
  void AddLabel(unsigned int id, int label);
  void AddSpin(unsigned int id, int label, int *current, std::vector<std::pair<int, std::string> > &values);
  void AddSpin(unsigned int id, int label, int *current, std::vector<std::pair<int, int> > &values);
  void AddSlider(unsigned int id, int label, float *current, float min, float interval, float max, FORMATFUNCTION formatFunction, bool allowPopup = true);
  void AddSeparator(unsigned int id);

  static std::string FormatPercent(float value, float minimum);
  static std::string FormatPercentAsDecibel(float value, float minimum);
  static std::string FormatDelay(float value, float minimum);
  static std::string FormatDecibel(float value, float minimum);

  AE_DSP_STREAM_ID                            m_ActiveStreamId;                         /*!< The on dialog selectable stream identifier */
  ActiveAE::CActiveAEDSPProcessPtr            m_ActiveStreamProcess;                    /*!< On dialog adjustable dsp processing class */
  AE_DSP_STREAMTYPE                           m_streamTypeUsed;                         /*!< The currently selected and used stream type */
  AE_DSP_BASETYPE                             m_baseTypeUsed;                           /*!< The currently detected and used base type */
  std::vector<ActiveAE::CActiveAEDSPModePtr>  m_ActiveModes;                            /*!< The process modes currently active on dsp processing stream */
  std::vector<float>                          m_ActiveModesCPUUsage;                    /*!< CPU usauge of the modes in previous vector, used seperate vector to have CActiveAEDSP::GetActiveModes call with a constant vector table value */
  std::vector<ActiveAE::CActiveAEDSPModePtr>  m_MasterModes[AE_DSP_ASTREAM_MAX];        /*!< table about selectable and usable master processing modes */
  unsigned int                                m_CurrentMenu;                            /*!< identfier of the currently displayed dsp menu */
  unsigned int                                m_OldMenu;                                /*!< identfier of the old displayed dsp menu */
  unsigned int                                m_LastMenu;                               /*!< previous menu identifier, used to have fallback if dsp addon dialog is opened */
  std::vector<MenuHookMember>                 m_Menus;                                  /*!< storage about present addon menus on currently selected submenu */
  Features                                    m_audioCaps;                              /*!< the on current playback on XBMC supported audio features */

  /*! Settings control selection and information data */
  std::string                                 m_InputChannels;
  std::string                                 m_InputChannelNames;
  std::string                                 m_InputSamplerate;
  std::string                                 m_OutputChannels;
  std::string                                 m_OutputChannelNames;
  std::string                                 m_OutputSamplerate;
  std::string                                 m_CPUUsage;
  float                                       m_volume;

  CGUISpinControlEx                          *m_pOriginalSpin;
  CGUIRadioButtonControl                     *m_pOriginalRadioButton;
  CGUIButtonControl                          *m_pOriginalSettingsButton;
  CGUISettingsSliderControl                  *m_pOriginalSlider;
  CGUIImage                                  *m_pOriginalSeparator;
  CGUILabelControl                           *m_pOriginalLabel;

  std::vector<SettingInfo>                    m_settings;

  bool                                        m_usePopupSliders;
};
