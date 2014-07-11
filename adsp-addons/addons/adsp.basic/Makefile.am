#
# Makefile for the ADSP basic sound processing add-on for XBMC Audio DSP
#
# See the README for copyright information and
# how to reach the author.
#

ADDONBINNAME    = XBMC_Basic
ADDONNAME       = adsp.basic
LIBNAME         = libadspbasic-addon
lib_LTLIBRARIES = libadspbasic-addon.la

LIBS            = @abs_top_srcdir@/lib/tinyxml/libtinyxml.la -lsamplerate -lfftw3f -lfftw3

include ../Makefile.include.am

libadspbasic_addon_la_SOURCES = src/client.cpp \
                                src/AudioDSPBasic.cpp \
                                src/AudioDSPSettings.cpp \
                                src/AudioDSPSoundTest.cpp \
                                src/DSPProcessMaster.cpp \
                                src/GUIDialogSpeakerDistance.cpp \
                                src/GUIDialogSpeakerGain.cpp \
                                src/Process_Stereo/DSPProcessStereo.cpp \
                                src/filter/complex.cpp \
                                src/filter/delay.cpp \
                                src/filter/filter.cpp \
                                src/filter/high_shelf.cpp \
                                src/filter/mkfilter.cpp

libadspbasic_addon_la_LDFLAGS = @TARGET_LDFLAGS@

