INCLUDES+=-I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.pvr \
          -I/home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/addons/library.kodi.addon

CXXFLAGS+=-fPIC

SRCS=AddonCallbacksPVR.cpp \

LIB=addon-callbacks-pvr.a

include /home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
