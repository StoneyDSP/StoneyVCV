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

## Locate StoneyDSP...
set(STONEYDSP_DIR "${CMAKE_CURRENT_LIST_DIR}/dep/StoneyDSP")

## Locate CMake Modules...
list(APPEND CMAKE_MODULE_PATH
    "${STONEYDSP_DIR}/share/cmake/Modules"
    "${CMAKE_CURRENT_LIST_DIR}/dep/Catch2/share/cmake/Modules"
    "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules"
)

if(NOT DEFINED STONEYVCV_VERSION_MAJOR)
    set(STONEYDSP_VERSION_MAJOR 0 CACHE STRING "" FORCE)
endif()
if(NOT DEFINED STONEYVCV_VERSION_MINOR)
set(STONEYDSP_VERSION_MINOR 1 CACHE STRING "" FORCE)
endif()

project(STONEYVCV)

#[==[Set StoneyDSP Library ABI version to use]==]
set(STONEYDSP_VERSION_MAJOR 0 CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_MINOR 1 CACHE STRING "" FORCE)
include(StoneyDSP)

if(WIN32 AND NOT DEFINED CMAKE_EXTRA_GENERATOR)
    set(CMAKE_EXTRA_GENERATOR "mingw32-make")
endif()

enable_language(C)
enable_language(CXX)

set(PLUGIN_HPP "plugin.hpp")
set(PLUGIN_CPP "plugin.cpp")
if(WIN32)
    set(PLUGIN_LIB "plugin.dll")
elseif(UNIX AND NOT APPLE)
    set(PLUGIN_LIB "plugin.dylib")
else() # LINUX
    set(PLUGIN_LIB "plugin.so")
endif()

configure_file("include/${PLUGIN_HPP}" "include/${PLUGIN_HPP}")
# configure_file("include/VCA.hpp" "include/VCA.hpp")
# configure_file("include/VCO.hpp" "include/VCO.hpp")

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
    FILE_SET stoneyvcv_PUBLIC_HEADERS
    TYPE HEADERS
    BASE_DIRS
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    FILES
        # include/plugin.hpp
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${PLUGIN_HPP}>
        $<INSTALL_INTERFACE:include/${PLUGIN_HPP}>
)

target_sources(StoneyVCV
    PRIVATE
        "src/${PLUGIN_CPP}"
        # "src/VCA.cpp"
        # "src/VCO.cpp"
)

set_target_properties(StoneyVCV
    PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_NAME "plugin"
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
)

target_link_libraries(StoneyVCV
    PRIVATE
        StoneyDSP::Core
        StoneyDSP::SIMD
        StoneyDSP::DSP
)

# if(NOT DEFINED CMAKE_MAKE_PROGRAM)
#     set(CMAKE_MAKE_PROGRAM "make" CACHE STRING "" FORCE)
    set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "" FORCE)
    set(CMAKE_AUTOGEN_VERBOSE TRUE CACHE BOOL "" FORCE)
#     if(NOT DEFINED ENV{CI})
#         set(CMAKE_COLOR_MAKEFILE TRUE CACHE BOOL "" FORCE)
#     endif()
# endif()

add_custom_target(plugin ALL
    COMMAND "make"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    BYPRODUCTS "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
    SOURCES "${PROJECT_SOURCE_DIR}/src/${PLUGIN_CPP}" "${PROJECT_BINARY_DIR}/include/${PLUGIN_HPP}"
    JOB_SERVER_AWARE TRUE
    # DEPENDS StoneyVCV
    USES_TERMINAL
)

add_custom_target(dist
    COMMAND "make" "dist"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    BYPRODUCTS "${PROJECT_SOURCE_DIR}/dist"
    SOURCES "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
    JOB_SERVER_AWARE TRUE
    DEPENDS plugin
    USES_TERMINAL
)

# add_custom_target(clean
#     COMMAND "make" "clean"
#     WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
#     BYPRODUCTS "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
#     SOURCES "${PROJECT_SOURCE_DIR}/src/${PLUGIN_CPP}" "${PROJECT_BINARY_DIR}/include/${PLUGIN_HPP}"
#     JOB_SERVER_AWARE TRUE
#     USES_TERMINAL
# )

## Only build tests if this project is the top-level project...
if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)

    find_package(Catch2 3 REQUIRED)

    # Include(FetchContent)

    # FetchContent_Declare(
    #   Catch2
    #   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    #   GIT_TAG        v3.4.0 # or a later release
    # )

    # FetchContent_MakeAvailable(Catch2)

    ## These tests can use the Catch2-provided main
    add_executable(Tests_StoneyVCV)
    add_executable(StoneyVCV::Tests_StoneyVCV ALIAS Tests_StoneyVCV)
    add_executable(StoneyDSP::StoneyVCV::Tests_StoneyVCV ALIAS Tests_StoneyVCV)
    target_include_directories(Tests_StoneyVCV
        PUBLIC
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    target_sources(Tests_StoneyVCV
        PRIVATE
            "${PROJECT_SOURCE_DIR}/test/plugin.cpp"
            # "${PROJECT_SOURCE_DIR}/test/VCA.cpp"
            # "${PROJECT_SOURCE_DIR}/test/VCA.cpp"
    )
    target_link_libraries(Tests_StoneyVCV
        PRIVATE
            StoneyDSP::Core
            StoneyDSP::SIMD
            StoneyDSP::DSP
            # StoneyDSP::StoneyVCV
            Catch2::Catch2WithMain
    )
    set_target_properties(Tests_StoneyVCV
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test"
            RUNTIME_OUTPUT_NAME "Tests_StoneyVCV"
    )

    enable_testing()

    include(CTest)
    include(Catch)
    catch_discover_tests(Tests_StoneyVCV)

endif()
