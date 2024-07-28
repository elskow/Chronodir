cmake_minimum_required(VERSION 3.22)
project(Chronodir LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    set(CMAKE_C_FLAGS_DEBUG "/Zi /Od /W4")
    set(CMAKE_C_FLAGS_RELEASE "/O2 /W4")
else()
    set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -Wall -Wextra")
endif()

include_directories(include)

add_executable(
        cdir src/main.c
 "include/getopt.h" "include/getopt.c")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# uncomment to install the binary
#install(TARGETS cdir DESTINATION bin)