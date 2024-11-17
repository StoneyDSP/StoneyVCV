#!/usr/bin/env cmake
cmake_minimum_required(VERSION 3.14...3.29 FATAL_ERROR)

if(DEFINED VCPKG_ROOT AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(StoneyDSP)

set(STONEYDSP_VERSION_MAJOR 0 CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_MINOR 1 CACHE STRING "" FORCE)

enable_language(C)
enable_language(CXX)

set(STONEYDSP_SIMD_HPP "include/StoneyDSP/simd.hpp")
set(STONEYDSP_COMMON_HPP "include/StoneyDSP/common.hpp")
set(STONEYDSP_SYSTEM_HPP "include/StoneyDSP/system.hpp")
set(STONEYDSP_VERSION_HPP "include/StoneyDSP/version.hpp")
set(STONEYDSP_HPP "include/StoneyDSP.hpp")

if (NOT "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    configure_file("${STONEYDSP_DIR}/${STONEYDSP_SIMD_HPP}" "${STONEYDSP_SIMD_HPP}")
    configure_file("${STONEYDSP_DIR}/${STONEYDSP_COMMON_HPP}" "${STONEYDSP_COMMON_HPP}")
    configure_file("${STONEYDSP_DIR}/${STONEYDSP_SYSTEM_HPP}" "${STONEYDSP_SYSTEM_HPP}")
    configure_file("${STONEYDSP_DIR}/${STONEYDSP_VERSION_HPP}" "${STONEYDSP_VERSION_HPP}")
    configure_file("${STONEYDSP_DIR}/${STONEYDSP_HPP}" "${STONEYDSP_HPP}")

    # configure_file("${STONEYDSP_DIR}/include/StoneyDSP/DSP/Oscillator.hpp" "include/StoneyDSP/DSP/Oscillator.hpp")
    # configure_file("${STONEYDSP_DIR}/include/StoneyDSP/dsp.hpp" "include/StoneyDSP/dsp.hpp")
endif()

add_library(Core INTERFACE)
add_library(StoneyDSP::Core ALIAS Core)

target_include_directories (Core

    INTERFACE

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources (Core

    PUBLIC

        FILE_SET core_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            # include/StoneyDSP/simd.hpp
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${STONEYDSP_SIMD_HPP}>
            $<INSTALL_INTERFACE:${STONEYDSP_SIMD_HPP}>
            # include/StoneyDSP/common.hpp
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${STONEYDSP_COMMON_HPP}>
            $<INSTALL_INTERFACE:${STONEYDSP_COMMON_HPP}>
            # include/StoneyDSP/system.hpp
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${STONEYDSP_SYSTEM_HPP}>
            $<INSTALL_INTERFACE:${STONEYDSP_SYSTEM_HPP}>
            # include/StoneyDSP/version.hpp
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${STONEYDSP_VERSION_HPP}>
            $<INSTALL_INTERFACE:${STONEYDSP_VERSION_HPP}>
            # include/StoneyDSP.hpp
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${STONEYDSP_HPP}>
            $<INSTALL_INTERFACE:${STONEYDSP_HPP}>

            # # These belong in the 'DSP' library, eventually...
            # # //
            # $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/StoneyDSP/DSP/Oscillator.hpp>
            # $<INSTALL_INTERFACE:include/StoneyDSP/DSP/Oscillator.hpp>
            # # //
            # $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/StoneyDSP/dsp.hpp>
            # $<INSTALL_INTERFACE:include/StoneyDSP/dsp.hpp>
)

set_target_properties (Core

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin
)
