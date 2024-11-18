#!/usr/bin/env cmake
cmake_minimum_required(VERSION 3.14...3.29 FATAL_ERROR)

if(NOT DEFINED STONEYDSP_VERSION_MAJOR)
    set(STONEYDSP_VERSION_MAJOR 0 CACHE STRING "" FORCE)
endif()
if(NOT DEFINED STONEYDSP_VERSION_MINOR)
    set(STONEYDSP_VERSION_MINOR 1 CACHE STRING "" FORCE)
endif()

project(STONEYDSP)

enable_language(C)
enable_language(CXX)

set(STONEYDSP_BUILD_TARGETS)

#[==[Core]==]
add_library(Core INTERFACE)
add_library(StoneyDSP::Core ALIAS Core)
set(STONEYDSP_CORE_HEADERS)
set(STONEYDSP_CORE_COMMON_HPP "include/StoneyDSP/Core/common.hpp")
set(STONEYDSP_CORE_SYSTEM_HPP "include/StoneyDSP/Core/system.hpp")
set(STONEYDSP_CORE_VERSION_HPP "include/StoneyDSP/Core/version.hpp")
set(STONEYDSP_CORE_HPP "include/StoneyDSP/Core.hpp")
list(APPEND STONEYDSP_CORE_HEADERS
    "${STONEYDSP_CORE_COMMON_HPP}"
    "${STONEYDSP_CORE_SYSTEM_HPP}"
    "${STONEYDSP_CORE_VERSION_HPP}"
    "${STONEYDSP_CORE_HPP}"
)
target_include_directories(Core
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

foreach(__header IN LISTS STONEYDSP_CORE_HEADERS)
    configure_file("${STONEYDSP_DIR}/${__header}" "${__header}")
    target_sources(Core
        INTERFACE
        FILE_SET stoneydsp_CORE_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            #[==[include/StoneyDSP/__header]==]
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${__header}>
            $<INSTALL_INTERFACE:${__header}>
    )
endforeach()
set_target_properties(Core
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "bin"
        LIBRARY_OUTPUT_DIRECTORY "lib"
        ARCHIVE_OUTPUT_DIRECTORY "lib"
        PDB_OUTPUT_DIRECTORY     "bin"
)
list(APPEND STONEYDSP_BUILD_TARGETS Core)

#[==[SIMD]==]
add_library(SIMD INTERFACE)
add_library(StoneyDSP::SIMD ALIAS SIMD)
target_include_directories(SIMD
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
set(STONEYDSP_SIMD_HEADERS)
set(STONEYDSP_SIMD_VECTOR_HPP "include/StoneyDSP/SIMD/Vector.hpp")
set(STONEYDSP_SIMD_HPP "include/StoneyDSP/SIMD.hpp")
list(APPEND STONEYDSP_SIMD_HEADERS
    "${STONEYDSP_SIMD_VECTOR_HPP}"
    "${STONEYDSP_SIMD_HPP}"
)
foreach(__header IN LISTS STONEYDSP_SIMD_HEADERS)
    configure_file("${STONEYDSP_DIR}/${__header}" "${__header}")
    target_sources(SIMD
        INTERFACE
        FILE_SET stoneydsp_SIMD_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            #[==[include/StoneyDSP/__header]==]
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${__header}>
            $<INSTALL_INTERFACE:${__header}>
    )
endforeach()
set_target_properties(SIMD
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "bin"
        LIBRARY_OUTPUT_DIRECTORY "lib"
        ARCHIVE_OUTPUT_DIRECTORY "lib"
        PDB_OUTPUT_DIRECTORY     "bin"
)
target_link_libraries(SIMD
    INTERFACE
        StoneyDSP::Core
)
list(APPEND STONEYDSP_BUILD_TARGETS SIMD)

#[==[DSP]==]
add_library(DSP INTERFACE)
add_library(StoneyDSP::DSP ALIAS DSP)
target_include_directories(DSP
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
set(STONEYDSP_DSP_HEADERS)
set(STONEYDSP_DSP_GAIN_HPP "include/StoneyDSP/DSP/Gain.hpp")
set(STONEYDSP_DSP_OSCILLATOR_HPP "include/StoneyDSP/DSP/Oscillator.hpp")
set(STONEYDSP_DSP_HPP "include/StoneyDSP/DSP.hpp")
list(APPEND STONEYDSP_DSP_HEADERS
    "${STONEYDSP_DSP_GAIN_HPP}"
    "${STONEYDSP_DSP_OSCILLATOR_HPP}"
    "${STONEYDSP_DSP_HPP}"
)
foreach(__header IN LISTS STONEYDSP_DSP_HEADERS)
    configure_file("${STONEYDSP_DIR}/${__header}" "${__header}")
    target_sources(DSP
        INTERFACE
        FILE_SET stoneydsp_DSP_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            #[==[include/StoneyDSP/__header]==]
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${__header}>
            $<INSTALL_INTERFACE:${__header}>
    )
endforeach()
set_target_properties(DSP
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "bin"
        LIBRARY_OUTPUT_DIRECTORY "lib"
        ARCHIVE_OUTPUT_DIRECTORY "lib"
        PDB_OUTPUT_DIRECTORY     "bin"
)
target_link_libraries(DSP
    INTERFACE
        StoneyDSP::Core
        StoneyDSP::SIMD
)
list(APPEND STONEYDSP_BUILD_TARGETS DSP)
#[==[Test]==]
## Only build tests if this project is the top-level project...
if(STONEYDSP_IS_TOP_LEVEL AND STONEYDSP_BUILD_TESTS)

    find_package(Catch2 3 REQUIRED)

    # Include(FetchContent)

    # FetchContent_Declare(
    #   Catch2
    #   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    #   GIT_TAG        v3.4.0 # or a later release
    # )

    # FetchContent_MakeAvailable(Catch2)

    ## These tests can use the Catch2-provided main
    add_executable(Tests_StoneyDSP)
    add_executable(StoneyDSP::Tests_StoneyDSP ALIAS Tests_StoneyDSP)
    target_sources(Tests_StoneyDSP
        PRIVATE
            "${STONEYDSP_DIR}/test/StoneyDSP/SIMD.cpp"
            "${STONEYDSP_DIR}/test/StoneyDSP/Core.cpp"
    )
    target_link_libraries(Tests_StoneyDSP
        PRIVATE
            StoneyDSP::Core
            StoneyDSP::SIMD
            # StoneyDSP::DSP
            Catch2::Catch2WithMain
    )
    set_target_properties(Tests_StoneyDSP
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test/StoneyDSP"
            RUNTIME_OUTPUT_NAME "Tests_StoneyDSP"
    )

    enable_testing()

    include(CTest)
    include(Catch)
    catch_discover_tests(Tests_StoneyDSP)

endif()
