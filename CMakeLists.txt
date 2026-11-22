# SillyEngine
# Build setup created by Claude (Anthropic AI) for SillyCatDevelopment.
#
# You never need to edit this file to add code. It finds everything itself:
#
#   src/<part>/            every folder directly inside src/ is one part
#     **/*.cppm            module interface units (any subfolder depth)
#     **/*.cpp             sources and module implementation units
#     main.cpp             if a part has this file directly inside it, the part
#                          is a PROGRAM (named after the folder); otherwise
#                          it's a LIBRARY that programs and tests can use
#
# New files and folders are picked up on the next build (CONFIGURE_DEPENDS
# makes the build re-check the folders and re-run CMake when they change).
# A part with no files yet is skipped, so empty folders are fine.

cmake_minimum_required(VERSION 4.5)

project(SillyEngine
    VERSION 0.1.0
    DESCRIPTION "A chess engine written from scratch"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)          # lets every file write `import std;`
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd in VS Code

if(CMAKE_CXX_COMPILER_IMPORT_STD_ERROR_MESSAGE)
    message(FATAL_ERROR
        "`import std;` isn't available (CMake ${CMAKE_VERSION}, ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}):\n"
        "  ${CMAKE_CXX_COMPILER_IMPORT_STD_ERROR_MESSAGE}\n"
        "Needs CMake 4.5+ and Homebrew's LLVM (brew install cmake llvm ninja), then  cmake --preset debug --fresh")
endif()

option(SILLYENGINE_NATIVE "Optimise Release builds for this machine's CPU" ON)

# Release: tuned for this Mac's CPU. Set for every target (yours and the
# std module) so their compiled modules stay compatible.
if(SILLYENGINE_NATIVE AND NOT MSVC)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
        add_compile_options("$<$<CONFIG:Release>:-mcpu=native>")
    else()
        add_compile_options("$<$<CONFIG:Release>:-march=native>")
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(CompilerWarnings)
include(Parts)

sillyengine_add_parts("${PROJECT_SOURCE_DIR}/src")
