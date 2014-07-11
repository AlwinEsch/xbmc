#
# Makefile for the ADSP FreeSurround add-on for XBMC Audio DSP
#
# See the README for copyright information and
# how to reach the author.
#

ADDONBINNAME    = XBMC_FreeSurround
ADDONNAME       = adsp.freesurround
LIBNAME         = libadsp-freesurround-addon
lib_LTLIBRARIES = libadsp-freesurround-addon.la

LIBS            = @abs_top_srcdir@/lib/tinyxml/libtinyxml.la

include ../Makefile.include.am

libadsp_freesurround_addon_la_SOURCES = src/ChannelMaps.cpp \
                                        src/client.cpp \
                                        src/DSPProcessFreeSurround.cpp \
                                        src/FreeSurroundDecoder.cpp \
                                        src/FreeSurroundSettings.cpp \
                                        src/GUIDialogFreeSurround.cpp \
                                        src/kissfft/kiss_fft.cpp \
                                        src/kissfft/kiss_fftr.cpp

libadsp_freesurround_addon_la_LDFLAGS = @TARGET_LDFLAGS@

