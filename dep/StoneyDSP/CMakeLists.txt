cmake_minimum_required(VERSION 3.14...3.31 FATAL_ERROR)

if(NOT DEFINED STONEYDSP_VERSION_MAJOR)
    set(STONEYDSP_VERSION_MAJOR 0 CACHE STRING "" FORCE)
endif()

if(NOT DEFINED STONEYDSP_VERSION_MINOR)
    set(STONEYDSP_VERSION_MINOR 0 CACHE STRING "" FORCE)
endif()

if(NOT DEFINED STONEYDSP_VERSION_MINOR)
    set(STONEYDSP_VERSION_MINOR 0 CACHE STRING "" FORCE)
endif()

project(STONEYDSP
    VERSION 0.0.0
    DESCRIPTION "StoneyDSP C++ Library"
    HOMEPAGE_URL "https://github.com/StoneyDSP/StoneyDSP"
)

set(STONEYDSP_DIR "${CMAKE_CURRENT_LIST_DIR}")

enable_language(C)
enable_language(CXX)

include(GNUInstallDirs)

#[==[Files]==]
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

set(STONEYDSP_TARGETS)

#[==[Core]==]
add_library(Core INTERFACE)
add_library(StoneyDSP::Core ALIAS Core)

set_target_properties(Core PROPERTIES VERSION 0.0.0)
set_target_properties(Core PROPERTIES SOVERSION 0)
set_target_properties(Core PROPERTIES INTERFACE_STONEYDSP_CORE_MAJOR_VERSION 0)
set_property(
    TARGET Core
    APPEND
    PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_STONEYDSP_CORE_MAJOR_VERSION
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

# install the target and create export-set
install(TARGETS Core
    EXPORT StoneyDSPCoreTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET stoneydsp_CORE_PUBLIC_HEADERS
)

# generate and install export file
install(EXPORT StoneyDSPCoreTargets
    FILE "StoneyDSPCoreTargets.cmake"
    NAMESPACE StoneyDSP::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"
)
export(
    TARGETS Core
    FILE "share/cmake/StoneyDSPCoreTargets.cmake"
    NAMESPACE StoneyDSP::
)
set_target_properties(Core
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "bin"
    LIBRARY_OUTPUT_DIRECTORY "lib"
    ARCHIVE_OUTPUT_DIRECTORY "lib"
    PDB_OUTPUT_DIRECTORY "bin"
)
list(APPEND STONEYDSP_TARGETS Core)

#[==[SIMD]==]
add_library(SIMD INTERFACE)
add_library(StoneyDSP::SIMD ALIAS SIMD)

set_target_properties(SIMD PROPERTIES VERSION 0.0.0)
set_target_properties(SIMD PROPERTIES SOVERSION 0)
set_target_properties(SIMD PROPERTIES INTERFACE_STONEYDSP_SIMD_MAJOR_VERSION 0)
set_property(
    TARGET SIMD
    APPEND
    PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_STONEYDSP_SIMD_MAJOR_VERSION
)

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

# install the target and create export-set
install(TARGETS SIMD
    EXPORT StoneyDSPSIMDTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET stoneydsp_SIMD_PUBLIC_HEADERS
)

# generate and install export file
install(EXPORT StoneyDSPSIMDTargets
    FILE "StoneyDSPSIMDTargets.cmake"
    NAMESPACE StoneyDSP::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"
)
export(
    TARGETS SIMD
    FILE "share/cmake/StoneyDSPSIMDTargets.cmake"
    NAMESPACE StoneyDSP::
)
set_target_properties(SIMD
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "bin"
    LIBRARY_OUTPUT_DIRECTORY "lib"
    ARCHIVE_OUTPUT_DIRECTORY "lib"
    PDB_OUTPUT_DIRECTORY "bin"
)
target_link_libraries(SIMD
    INTERFACE
    StoneyDSP::Core
)
list(APPEND STONEYDSP_TARGETS SIMD)

#[==[DSP]==]
add_library(DSP INTERFACE)
add_library(StoneyDSP::DSP ALIAS DSP)

set_target_properties(DSP PROPERTIES VERSION 0.0.0)
set_target_properties(DSP PROPERTIES SOVERSION 0)
set_target_properties(DSP PROPERTIES INTERFACE_STONEYDSP_DSP_MAJOR_VERSION 0)
set_property(
    TARGET DSP
    APPEND
    PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_STONEYDSP_DSP_MAJOR_VERSION
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

# install the target and create export-set
install(TARGETS DSP
    EXPORT StoneyDSPDSPTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET stoneydsp_DSP_PUBLIC_HEADERS
)

# generate and install export file
install(EXPORT StoneyDSPDSPTargets
    FILE "StoneyDSPDSPTargets.cmake"
    NAMESPACE StoneyDSP::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"
)

export(
    TARGETS DSP
    FILE "share/cmake/StoneyDSPDSPTargets.cmake"
    NAMESPACE StoneyDSP::
)

set_target_properties(DSP
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "bin"
    LIBRARY_OUTPUT_DIRECTORY "lib"
    ARCHIVE_OUTPUT_DIRECTORY "lib"
    PDB_OUTPUT_DIRECTORY "bin"
)

target_link_libraries(DSP
    INTERFACE
    StoneyDSP::Core
    StoneyDSP::SIMD
)

list(APPEND STONEYDSP_TARGETS DSP)

#[==[StoneyDSPConfig.cmake]==]
include(CMakePackageConfigHelpers)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSPConfig.cmake.in" [==[
@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/StoneyDSPConfigVersion.cmake")

set(_StoneyDSP_supported_components)
list(APPEND _StoneyDSP_supported_components
    @STONEYDSP_TARGETS@
)

## Custom 'check_required_components' macro
foreach(_requested_component ${StoneyDSP_FIND_COMPONENTS})
  if (NOT _requested_component IN_LIST _StoneyDSP_supported_components)
    set(StoneyDSP_FOUND False)
    set(StoneyDSP_NOT_FOUND_MESSAGE "Unsupported component: ${_requested_component}")
  endif()
  include("${CMAKE_CURRENT_LIST_DIR}/StoneyDSP${_requested_component}Targets.cmake")
  message(STATUS "Linking with StoneyDSP::${_requested_component}")
endforeach()

unset(_StoneyDSP_supported_components)

# Tell the user what to do
message(STATUS "Linking with StoneyDSP")

]==])

# Create pkgconfig file
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSP.pc.in" [==[
prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=/${exec_prefix}/@CMAKE_INSTALL_LIBDIR@
includedir=/${prefix}/@CMAKE_INSTALL_INCLUDEDIR@

Name: @PROJECT_NAME@
Description: @PROJECT_DESCRIPTION@
Version: @PROJECT_VERSION@
Libs: -L${libdir}
Cflags: -I${includedir}
]==])

# Configure pkgconfig file
configure_file (
  "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSP.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/share/pkgconfig/StoneyDSP.pc"
  @ONLY
)

# Install pkgconfig file
install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/share/pkgconfig/StoneyDSP.pc"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSPConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSPConfig.cmake"
    INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"

    # # Use custom 'check_required_components' macro
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSPConfigVersion.cmake"
    VERSION "${STONEYDSP_VERSION_MAJOR}.${STONEYDSP_VERSION_MINOR}.${STONEYDSP_VERSION_PATCH}"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSPConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSPConfigVersion.cmake"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"
)

#[==[Test]==]
# # Only build tests if this project is the top-level project...
if(STONEYDSP_IS_TOP_LEVEL AND STONEYDSP_BUILD_TESTS)
    find_package(Catch2 3 REQUIRED)

    # # These tests can use the Catch2-provided main
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
