cmake_minimum_required(VERSION 3.22)

# Project information
project(Chronodir VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler flags
if (MSVC)
    add_compile_options(
        /W4
    )
    set(CMAKE_C_FLAGS_DEBUG "/Zi /Od /DDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "/O2 /DNDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/O2 /Zi /DNDEBUG")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Os /DNDEBUG")
else()
    add_compile_options(
        -Wall -Wextra -Wpedantic
    )
    set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.c
    include/getopt.c
)

# Add executable
add_executable(cdir ${SOURCES})

# Set build type if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Installation settings
include(GNUInstallDirs)

if (WIN32)
    set(INSTALL_DIR "$ENV{USERPROFILE}/Chronodir/bin")
else()
    set(INSTALL_DIR "${CMAKE_INSTALL_BINDIR}")
endif()

# Install target
install(TARGETS cdir DESTINATION ${INSTALL_DIR})

# Add version information
set_target_properties(cdir PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Add include directories
target_include_directories(cdir PRIVATE include)

# Print installation directory
message(STATUS "Installation directory: ${INSTALL_DIR}")

# Custom script to add the installation directory to the PATH environment variable on Windows
if (WIN32)
    install(CODE "
        execute_process(COMMAND setx PATH \"%PATH%;${INSTALL_DIR}\")
        message(STATUS \"Added ${INSTALL_DIR} to PATH environment variable.\")
    ")
endif()

