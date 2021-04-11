include(../../../../../cmake/scripts/common/Macros.cmake)

macro(devkit_add_object name)
  add_library(${name} OBJECT ${SOURCES} ${HEADERS})
  set_target_properties(${name} PROPERTIES C_VISIBILITY_PRESET hidden
                                           CXX_VISIBILITY_PRESET hidden
                                           VISIBILITY_INLINES_HIDDEN ON
                                           POSITION_INDEPENDENT_CODE ON)
  set(DEVKIT_OBJECTS $<TARGET_OBJECTS:${name}> ${DEVKIT_OBJECTS} PARENT_SCOPE)
endmacro()
