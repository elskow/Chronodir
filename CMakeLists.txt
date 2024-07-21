cmake_minimum_required(VERSION 3.22)
project(Chronodir LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-O2 -Wall -Wextra")

add_executable(cdir main.c)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#install(TARGETS cdir DESTINATION bin)