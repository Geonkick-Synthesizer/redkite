cmake_minimum_required (VERSION 3.7)

project(redkite VERSION 0.0.1)

set(RK_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RK_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RK_EXAMPLES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "no build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type Debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set (CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "default install path" FORCE)
endif()

option(ENABLE_EXAMPLES    "Build examples" ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "enable logging")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRK_LOG_DEBUG_LEVEL")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRK_LOG_DEBUG_LEVEL")
endif()

set(RK_HEADERS
  ${RK_INCLUDE_PATH}/Rk.h
  ${RK_INCLUDE_PATH}/RkLog.h
  ${RK_INCLUDE_PATH}/RkPlatform.h
  ${RK_INCLUDE_PATH}/RkEvent.h
  ${RK_INCLUDE_PATH}/RkWidget.h
  ${RK_INCLUDE_PATH}/RkLabel.h
  ${RK_INCLUDE_PATH}/RkMain.h)

set(RK_HEADERS_IMPL
  ${RK_INCLUDE_PATH}/impl/RkMainImpl.h
  ${RK_INCLUDE_PATH}/impl/RkWidgetImpl.h
  ${RK_INCLUDE_PATH}/impl/RkLabelImpl.h)
#  ${RK_INCLUDE_PATH}/impl/platforms/xwin/RkWidgetXWin.h
#  ${RK_INCLUDE_PATH}/impl/platforms/xwin/RkMainXWin.h)

set(RK_SOURCES
  ${RK_SRC_PATH}/RkWidget.cpp
  ${RK_SRC_PATH}/RkWidgetImpl.cpp
  ${RK_SRC_PATH}/RkMain.cpp
  ${RK_SRC_PATH}/RkMainImpl.cpp
  ${RK_SRC_PATH}/RkLabel.cpp
  ${RK_SRC_PATH}/RkLabelImpl.cpp
  ${RK_SRC_PATH}/platforms/xwin/RkPlatform.cpp)
#  ${RK_SRC_PATH}/platforms/xwin/RkWidgetXWin.cpp
#  ${RK_SRC_PATH}/platforms/xwin/RkMainXWin.cpp)

add_definitions(-fPIC)
include_directories(${RK_INCLUDE_PATH})
include_directories(${RK_INCLUDE_PATH}/impl)
include_directories(${RK_INCLUDE_PATH}/impl/platforms/xwin)
add_library(redkite STATIC
  ${RK_HEADERS}
  ${RK_HEADERS_IMPL}
  ${RK_SOURCES})

install(TARGETS redkite DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${RK_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/redkite)

if (ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif (ENABLE_EXAMPLES)
