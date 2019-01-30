cmake_minimum_required (VERSION 3.7)

project(redkite VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O0 -g -Wall")

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "no build type selected, default to Release")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type Release" FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")

option(ENABLE_LOGGING    "Enable logging" ON)
option(ENABLE_EXAMPLES    "Build examples" ON)

if (EXAMPLES_ENABLED)
  add_subdirectory(examples)
endif (EXAMPLES_ENABLED)
