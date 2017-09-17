set(SOURCES BinaryAddon.cpp
            BinaryAddonManager.cpp
            BinaryAddonStatus.cpp
            SharedMemory.cpp
            SharedMemoryPosix.cpp
            SharedMemoryWindows.cpp
            requestpacket.cpp
            responsepacket.cpp
            tools.cpp)

set(HEADERS BinaryAddon.h
            BinaryAddonManager.h
            BinaryAddonStatus.h
            SharedMemory.h
            SharedMemoryPosix.h
            SharedMemoryWindows.h
            requestpacket.h
            responsepacket.h
            tools.h)

core_add_library(addons_binary-addons_exe)
target_include_directories(${CORE_LIBRARY} PRIVATE ${CMAKE_SOURCE_DIR}/xbmc/addons/kodi-addon-dev-kit/include/kodi)
