#
# Makefile for the ADSP template sound processing add-on for XBMC Audio DSP
#
# See the README for copyright information and
# how to reach the author.
#

ADDONBINNAME    = XBMC_Template
ADDONNAME       = adsp.template
LIBNAME         = libadsptemplate-addon
lib_LTLIBRARIES = libadsptemplate-addon.la

LIBS            = @abs_top_srcdir@/lib/tinyxml/libtinyxml.la

include ../Makefile.include.am

INCLUDES+=-Isrc -Isrc/template/include

libadsptemplate_addon_la_SOURCES = src/ADDONOptional.cpp \
                                   src/channelUpmixer.cpp \
                                   src/DSPProcessor.cpp \
                                   src/Dialogs/GUIDialogMasterProcess.cpp \
                                   src/Dialogs/GUIDialogOutputResample.cpp \
                                   src/Dialogs/GUIDialogPostProcess.cpp \
                                   src/Dialogs/GUIDialogPreProcess.cpp \
                                   src/template/ADSPAddonHandler.cpp \
                                   src/template/ADSPProcessorHandle.cpp \
                                   src/template/client.cpp \
                                   src/template/GUIDialogBase.cpp \
                                   src/template/IADDONOptional.cpp \
                                   src/template/IADSPProcessor.cpp \
                                   src/template/configuration/templateConfiguration.cpp

libadsptemplate_addon_la_LDFLAGS = @TARGET_LDFLAGS@

