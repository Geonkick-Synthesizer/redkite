cmake_minimum_required (VERSION 3.7)

project(redkite VERSION 0.0.1)

#set(CMAKE_SYSTEM_NAME Windows)

# specify the cross compiler
if (CMAKE_SYSTEM_NAME MATCHES Windows)
  message(STATUS "Build Redkite for Windows")
  add_compile_options(-DRK_OS_WIN)
  set(CMAKE_C_COMPILER   /usr/bin/x86_64-w64-mingw32-gcc)
  set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)
elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
  message(FATAL_ERROR "Redkite not implemented yet for Mac OS X")
#    add_compile_definitions(RK_OS_MAC)
elseif (CMAKE_SYSTEM_NAME MATCHES Linux)
  message(STATUS " Build Redkite for GNU/Linux")
else()
  message(FATAL_ERROR "Redkite not implemented yet for ${CMAKE_SYSTEM_NAME}")
endif()

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
  ${RK_INCLUDE_PATH}/RkEventQueue.h
  ${RK_INCLUDE_PATH}/RkWidget.h
  ${RK_INCLUDE_PATH}/RkLabel.h
  ${RK_INCLUDE_PATH}/RkMain.h)

set(RK_HEADERS_IMPL
  ${RK_INCLUDE_PATH}/impl/RkMainImpl.h
  ${RK_INCLUDE_PATH}/impl/RkEventQueueImpl.h
  ${RK_INCLUDE_PATH}/impl/RkWidgetImpl.h
  ${RK_INCLUDE_PATH}/impl/RkLabelImpl.h)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
set(RK_HEADERS_PLATFORM
  ${RK_INCLUDE_PATH}/impl/platforms/win/RkWindowWin.h
  ${RK_INCLUDE_PATH}/impl/platforms/win/RkEventQueueWin.h)
elseif (CMAKE_SYSTEM_NAME MATCHES Darwin)
set(RK_HEADERS_PLATFORM
  ${RK_INCLUDE_PATH}/impl/platforms/mac/RkWindowMac.h
  ${RK_INCLUDE_PATH}/impl/platforms/mac/RkEventQueueMac.h)
else() # defaut GNU/Linux
set(RK_HEADERS_PLATFORM
  ${RK_INCLUDE_PATH}/impl/platforms/xwin/RkWindowX.h
  ${RK_INCLUDE_PATH}/impl/platforms/xwin/RkEventQueueX.h)
endif()

set(RK_SOURCES
  ${RK_SRC_PATH}/RkWidget.cpp
  ${RK_SRC_PATH}/RkWidgetImpl.cpp
  ${RK_SRC_PATH}/RkMain.cpp
  ${RK_SRC_PATH}/RkEventQueue.cpp
  ${RK_SRC_PATH}/RkEventQueueImpl.cpp
  ${RK_SRC_PATH}/RkMainImpl.cpp
  ${RK_SRC_PATH}/RkLabel.cpp
  ${RK_SRC_PATH}/RkLabelImpl.cpp)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
set(RK_SOURCES_PLATFORM
  ${RK_SRC_PATH}/platforms/win/RkPlatformWin.cpp
  ${RK_SRC_PATH}/platforms/win/RkWindowWin.cpp
  ${RK_SRC_PATH}/platforms/win/RkEventQueueWin.cpp)
elseif (CMAKE_SYSTEM_NAME MATCHES Darwin)
set(RK_SOURCES_PLATFORM
  ${RK_SRC_PATH}/platforms/mac/RkPlatformMac.cpp
  ${RK_SRC_PATH}/platforms/mac/RkWindowMac.cpp
  ${RK_SRC_PATH}/platforms/mac/RkEventQueueMac.cpp)
else() # defaut GNU/Linux
set(RK_SOURCES_PLATFORM
  ${RK_SRC_PATH}/platforms/xwin/RkPlatformX.cpp
  ${RK_SRC_PATH}/platforms/xwin/RkWindowX.cpp
  ${RK_SRC_PATH}/platforms/xwin/RkEventQueueX.cpp)
endif()

add_definitions(-fPIC)
include_directories(${RK_INCLUDE_PATH})
include_directories(${RK_INCLUDE_PATH}/impl)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
  include_directories(${RK_INCLUDE_PATH}/impl/platforms/win)
elseif (CMAKE_SYSTEM_NAME MATCHES Darwin)
  include_directories(${RK_INCLUDE_PATH}/impl/platforms/mac)
# not implemented yet
else() # defualt GNU/Linux
include_directories(${RK_INCLUDE_PATH}/impl/platforms/xwin)
endif()

add_library(redkite STATIC
  ${RK_HEADERS}
  ${RK_HEADERS_IMPL}
  ${RK_HEADERS_PLATFORM}
  ${RK_SOURCES}
  ${RK_SOURCES_PLATFORM})

install(TARGETS redkite DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${RK_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/redkite)

if (ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif (ENABLE_EXAMPLES)
