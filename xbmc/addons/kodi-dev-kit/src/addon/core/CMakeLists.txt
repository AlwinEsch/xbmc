# Auto generated CMakeLists.txt.
# See xbmc/addons/kodi-dev-kit/tools/code-generator.py.

set(SOURCES
  addon_control.cpp
  addon_thread_control.cpp
)

set(HEADERS
  IMsgHdl.h
  addon_control.h
  addon_thread_control.h
)

if(SOURCES OR HEADERS)
  devkit_add_object(devkit_core)
endif()
