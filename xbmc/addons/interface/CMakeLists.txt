# Auto generated CMakeLists.txt.
# See xbmc/addons/kodi-dev-kit/tools/code-generator.py.

set(SOURCES
  Controller.cpp
  GUICrashReporter.cpp
  IMsgHdl.cpp
  InstanceHandler.cpp
  Interface.cpp
  RunningProcess.cpp
  RunningThread.cpp
)

set(HEADERS
  Controller.h
  GUICrashReporter.h
  IMsgHdl.h
  InstanceHandler.h
  Interface.h
  RunningProcess.h
  RunningThread.h
)

if(NOT ENABLE_STATIC_LIBS OR SOURCES)
  core_add_library(addons_interface)
endif()
