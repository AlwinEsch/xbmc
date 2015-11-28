INCLUDES+=-I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.addon

CXXFLAGS+=-fPIC

SRCS=AddonCallbacksAddon.cpp \
     AddonCB_Audio.cpp \
     AddonCB_Codec.cpp \
     AddonCB_Directory.cpp \
     AddonCB_File.cpp \
     AddonCB_General.cpp \
     AddonCB_Network.cpp \

LIB=addon-callbacks-addon.a

include /home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
