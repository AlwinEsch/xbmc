INCLUDES+=-I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.audioengine \
          -I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.addon

SRCS=AddonCallbacksAudioEngine.cpp \
     AudioEngineCB_Stream.cpp \

LIB=addon-callbacks-audioengine.a

include /home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
