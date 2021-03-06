cmake_minimum_required(VERSION 2.8)
project(CMON CXX)
set(CMAKE_VERBOSE_MAKEFILE OFF)

message(STATUS "Using ${CMAKE_CXX_COMPILER_ID} compiler")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") 
  # using GCC
  set(CMAKE_CXX_FLAGS "-pthread -Wall -Wextra -Wno-unused-local-typedefs -Wno-unused-parameter")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # using Clang or AppleClang
  set(CMAKE_CXX_FLAGS "-pthread -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
else()
    message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} is not a supported compiler")
    # exit due to fatal error
endif()

# Check for c++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    # exit due to fatal error
endif()

# searching for boost 1.53 or newer (1.53 is the default version on SL7 and CentOS)
find_package(Boost 1.53 REQUIRED COMPONENTS system regex thread)

include_directories(
  ${CMON_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
)

add_library(
  webserver
  webserver.cpp
)

target_link_libraries(
  webserver
  ${Boost_LIBRARIES}
)

add_executable(
  cmon
  main.cpp
)

target_link_libraries(
  cmon
  webserver
  ${Boost_LIBRARIES}
)

add_subdirectory(udp)
add_subdirectory(shared_queue)
