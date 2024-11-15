#!/usr/bin/env cmake
cmake_minimum_required(VERSION 3.14...3.29 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules" "${CMAKE_MODULE_PATH}")

if(DEFINED VCPKG_ROOT AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

# if(NOT DEFINED ENV{RACK_DIR})
#     message(FATAL_ERROR "You need to set $RACK_DIR")
# endif()

project(StoneyVCV)

enable_language(C)
enable_language(CXX)

set(STONEYDSP_DIR "${CMAKE_CURRENT_LIST_DIR}/dep")

include(StoneyDSP)

find_package(Catch2 3 REQUIRED)

# Include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v3.4.0 # or a later release
# )

# FetchContent_MakeAvailable(Catch2)

# These tests can use the Catch2-provided main
add_executable(tests test/StoneyDSP/simd.cpp test/StoneyDSP.cpp)
target_link_libraries(tests PRIVATE StoneyDSP::Core Catch2::Catch2WithMain)

enable_testing()

include(CTest)
include(Catch)
catch_discover_tests(tests)
