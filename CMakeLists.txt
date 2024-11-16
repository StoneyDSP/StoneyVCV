#!/usr/bin/env cmake

## CMake Support...
cmake_minimum_required(VERSION 3.14...3.29 FATAL_ERROR)

## Required...
if(NOT DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
    message(FATAL_ERROR "You need to set $RACK_DIR")
endif()

## Recommended...
if(NOT DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED VCPKG_ROOT)
    message(WARNING "You may need to set $VCPKG_ROOT to acquire Catch2...")
endif()

## Take RACK_DIR from env, if not passed as -DRACK_DIR=...
if(DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
    set(RACK_DIR "$ENV{RACK_DIR}" CACHE STRING "" FORCE)
endif()

## Take VCPKG_ROOT from env, if not passed as -DVCPKG_ROOT=...
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT "$ENV{VCPKG_ROOT}" CACHE STRING "" FORCE)
endif()

## Set CMAKE_TOOLCHAIN_FILE to vcpkg, if not passed as -DCMAKE_TOOLCHAIN_FILE=...
if(DEFINED VCPKG_ROOT AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

## Locate helpers...
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules")

project(StoneyVCV)

enable_language(C)
enable_language(CXX)

## Locate StoneyDSP...
set(STONEYDSP_DIR "${CMAKE_CURRENT_LIST_DIR}/dep")

include(StoneyDSP)

set(PLUGIN_HPP "plugin.hpp")
set(PLUGIN_CPP "plugin.cpp")

configure_file("include/${PLUGIN_HPP}" "include/${PLUGIN_HPP}")

add_library(StoneyVCV SHARED EXCLUDE_FROM_ALL)
add_library(StoneyDSP::StoneyVCV ALIAS StoneyVCV)

target_include_directories(StoneyVCV
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(StoneyVCV
    PUBLIC
    "${RACK_DIR}/include"
    "${RACK_DIR}/dep/include"
)

target_sources(StoneyVCV
    PUBLIC
    FILE_SET stoneydsp_STONEYVCV_PUBLIC_HEADERS
    TYPE HEADERS
    BASE_DIRS
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    FILES
        # include/plugin.hpp
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${PLUGIN_HPP}>
        $<INSTALL_INTERFACE:include/${PLUGIN_HPP}>
)

target_sources(StoneyVCV PRIVATE "src/plugin.cpp")

set_target_properties(StoneyVCV
    PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_NAME "plugin"
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

target_link_libraries(StoneyVCV PRIVATE
    StoneyDSP::Core
)

## Only build tests if this project is the top-level project...
if(StoneyVCV_IS_TOP_LEVEL)

    find_package(Catch2 3 REQUIRED)

    # Include(FetchContent)

    # FetchContent_Declare(
    #   Catch2
    #   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    #   GIT_TAG        v3.4.0 # or a later release
    # )

    # FetchContent_MakeAvailable(Catch2)

    ## These tests can use the Catch2-provided main
    add_executable(tests test/StoneyDSP/simd.cpp test/StoneyDSP.cpp)
    target_link_libraries(tests PRIVATE StoneyDSP::Core Catch2::Catch2WithMain)

    enable_testing()

    include(CTest)
    include(Catch)
    catch_discover_tests(tests)

endif()
