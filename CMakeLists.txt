cmake_minimum_required (VERSION 3.7)

project(redkite VERSION 0.0.1)

set(RK_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RK_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RK_EXAMPLES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "no build type selected, default to Release")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type Release" FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")

option(ENABLE_EXAMPLES    "Build examples" ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRK_LOG_DEBUG_LEVEL")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRK_LOG_DEBUG_LEVEL")
endif()

set(RK_HEADERS
  ${RK_INCLUDE_PATH}/RkLog.h
  ${RK_INCLUDE_PATH}/RkWidget.h
  ${RK_INCLUDE_PATH}/RkMain.h
  ${RK_INCLUDE_PATH}/private/platforms/xwin/RkWidgetXWin.h)


set(RK_SOURCES
  ${RK_SRC_PATH}/RkWidget.cpp
  ${RK_SRC_PATH}/RkMain.cpp
  ${RK_SRC_PATH}/platforms/xwin/RkWidgetXWin.cpp)

include_directories(${RK_INCLUDE_PATH})
include_directories(${RK_INCLUDE_PATH}/private/platforms/xwin)
add_library(redkite STATIC
  ${RK_HEADERS}
  ${RK_SOURCES})

if (ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif (ENABLE_EXAMPLES)
