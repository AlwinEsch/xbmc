INCLUDES+=-I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.guilib \
          -I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.addon

SRCS=AddonCallbacksGUI.cpp \
     AddonGUIControlButton.cpp \
     AddonGUIControlCheckMark.cpp \
     AddonGUIControlEdit.cpp \
     AddonGUIControlLabel.cpp \
     AddonGUIControlProgress.cpp \
     AddonGUIControlRadioButton.cpp \
     AddonGUIControlRendering.cpp \
     AddonGUIControlSettingsSlider.cpp \
     AddonGUIControlSlider.cpp \
     AddonGUIControlSpin.cpp \
     AddonGUIDialogExtendedProgressBar.cpp \
     AddonGUIDialogFileBrowser.cpp \
     AddonGUIDialogKeyboard.cpp \
     AddonGUIDialogNumeric.cpp \
     AddonGUIDialogOK.cpp \
     AddonGUIDialogProgress.cpp \
     AddonGUIDialogSelect.cpp \
     AddonGUIDialogTextViewer.cpp \
     AddonGUIDialogYesNo.cpp \
     AddonGUIGeneral.cpp \
     AddonGUIListItem.cpp \
     AddonGUIWindow.cpp \

LIB=addon-callbacks-gui.a

include /home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))

