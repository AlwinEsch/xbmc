set(SOURCES AddonChangeObserver.cpp
            AddonChangeProcessor.cpp
            AddonDatabase.cpp
            AddonInfo.cpp
            AddonManager.cpp
            AddonVersion.cpp)

set(HEADERS AddonChangeObserver.h
            AddonChangeProcessor.h
            AddonDatabase.h
            AddonInfo.h
            AddonManager.h
            AddonVersion.h)

core_add_library(addons-new)
