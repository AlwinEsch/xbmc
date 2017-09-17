project(kodi-addon-executable)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(C CXX)

find_package(Kodi)
find_package(kodiplatform REQUIRED)
find_package(p8-platform REQUIRED)

add_definitions(-DUSE_DEMUX)

list(APPEND LIB_SOURCES AddonToKodi.cpp
                        ErrorCodeNames.cpp
                        InterProcess.cpp
                        RequestPacket.cpp
                        ResponsePacket.cpp
                        SharedMemory.cpp
                        SharedMemoryPosix.cpp
                        SharedMemoryWindows.cpp
                        tools.cpp
                        main.cpp)

if(WIN32)
  list(APPEND DEPLIBS ${p8-platform_LIBRARIES} ws2_32)
else()
  list(APPEND DEPLIBS ${p8-platform_LIBRARIES})
endif()

include_directories(${INCLUDES}
                    ../../../include
                    ../../../include/kodi
                    ../../../../../../xbmc/cores/AudioEngine/Utils/
                    ../../../../../../xbmc/cores/VideoPlayer/DVDDemuxers/
                    ../../../../../../xbmc/filesystem/
                    ../../../../../../xbmc/input/
                    ${kodiplatform_INCLUDE_DIRS}
                    ${p8-platform_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR})

add_executable(kodi.addon.executable ${LIB_SOURCES})
target_link_libraries(kodi.addon.executable ${DEPLIBS})
set_target_properties(kodi.addon.executable PROPERTIES OUTPUT_NAME kodi.addon.executable.api${ADDON_API_LEVEL})
