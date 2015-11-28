INCLUDES+=-I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.addon \
          -I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.audioengine \
          -I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.guilib \
          -I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.pvr \

SRCS=AddonCallbacks.cpp \

LIB=addon-callbacks.a

include /home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
