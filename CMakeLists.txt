cmake_minimum_required(VERSION 3.14...3.31 FATAL_ERROR)

#[==[STONEYVCV]==]
project(STONEYVCV VERSION 2.0.1.0)

set(STONEYVCV_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(STONEYVCV_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

enable_language(C)
enable_language(CXX)

include(CMakeDependentOption)
include(GNUInstallDirs)

set(STONEYVCV_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_TWEAK "${CMAKE_PROJECT_VERSION_TWEAK}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION "${CMAKE_PROJECT_VERSION}" CACHE STRING "" FORCE)

option(STONEYVCV_BUILD_MODULES "" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_HP1 "" ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_HP2 "" ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_HP4 "" ON "STONEYVCV_BUILD_MODULES" ON)

# Put components in the correct order of their dependencies on eachother
# to save tears...
find_package(StoneyDSP 0.0.0 REQUIRED COMPONENTS Core SIMD DSP CONFIG)
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib CONFIG)

# These props are helpful to have around...
get_target_property(rack_inc_dir unofficial-vcvrack::rack-sdk::lib INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(rack_link_dir unofficial-vcvrack::rack-sdk::lib INTERFACE_LINK_DIRECTORIES)
get_target_property(rack_implib unofficial-vcvrack::rack-sdk::lib IMPORTED_IMPLIB)
get_target_property(rack_implib_unofficial-vcvrack::location rack-sdk::lib IMPORTED_LOCATION)

set(STONEYVCV_TARGETS)

#[==[StoneyVCV]==]
add_library(plugin SHARED EXCLUDE_FROM_ALL)
add_library(StoneyVCV::plugin ALIAS plugin)
add_library(StoneyDSP::StoneyVCV::plugin ALIAS plugin)
# add_library(StoneyVCV SHARED EXCLUDE_FROM_ALL)
# add_library(StoneyDSP::StoneyVCV ALIAS StoneyVCV)

set_target_properties(plugin PROPERTIES VERSION 2.1.0)
set_target_properties(plugin PROPERTIES SOVERSION 2.1.0)

# Gather project files...
set(PLUGIN_HPP "plugin.hpp")
set(PLUGIN_CPP "plugin.cpp")

if(WIN32)
    set(PLUGIN_LIB_FILE_EXTENSION ".dll")
elseif(UNIX AND NOT APPLE)
    set(PLUGIN_LIB_FILE_EXTENSION ".dylib")
else() # LINUX
    set(PLUGIN_LIB_FILE_EXTENSION ".so")
endif(WIN32)
set(PLUGIN_LIB "plugin${PLUGIN_LIB_FILE_EXTENSION}")
configure_file("include/StoneyVCV/${PLUGIN_HPP}" "include/StoneyVCV/${PLUGIN_HPP}")
target_sources(plugin
    PUBLIC
    FILE_SET stoneyvcv_PLUGIN_PUBLIC_HEADERS
    TYPE HEADERS
    BASE_DIRS
    $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    FILES
    #[==[include/plugin.hpp]==]
    $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include/StoneyVCV/${PLUGIN_HPP}>
    $<INSTALL_INTERFACE:include/StoneyVCV/${PLUGIN_HPP}>
)

target_sources(plugin
    PRIVATE
    "src/StoneyVCV/${PLUGIN_CPP}"
)

set_target_properties(plugin
    PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_NAME "plugin"
    ARCHIVE_OUTPUT_DIRECTORY "${STONEYVCV_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${STONEYVCV_BINARY_DIR}/lib"
    # Compatible Interface
    INTERFACE_plugin_MAJOR_VERSION "${STONEYVCV_VERSION_MAJOR}"
    INTERFACE_plugin_MINOR_VERSION "${STONEYVCV_VERSION_MINOR}"
    INTERFACE_plugin_PATCH_VERSION "${STONEYVCV_VERSION_PATCH}"
)
set_property(TARGET plugin APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_plugin_MAJOR_VERSION
)
set_property(TARGET plugin APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_plugin_MINOR_VERSION
)
set_property(TARGET plugin APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_plugin_PATCH_VERSION
)
target_compile_definitions(plugin
    PUBLIC
    "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
    "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
    "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
    "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
    "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
)
if(DEFINED STONEYVCV_EXPERIMENTAL)
    target_compile_definitions(plugin
        PUBLIC
        "STONEYVCV_EXPERIMENTAL=${STONEYVCV_EXPERIMENTAL}"
    )
endif(DEFINED STONEYVCV_EXPERIMENTAL)
target_link_libraries(plugin
    PUBLIC
    unofficial-vcvrack::rack-sdk::lib
    StoneyDSP::Core
    StoneyDSP::SIMD
    StoneyDSP::DSP
)
target_compile_options(plugin
    PUBLIC
    "-fPIC"
)

if(UNIX)
    if(APPLE)
        target_link_options(plugin
            PUBLIC
            "-undefined dynamic_lookup"
        )
    else() # If we're Linux... (assumes GCC, as per Rack)
        target_compile_options(plugin
            PUBLIC

            # # This prevents static variables in the DSO (dynamic shared
            # # object) from being preserved after dlclose().
            "-fno-gnu-unique"
        )
        target_link_options(plugin
            PUBLIC

            # # This prevents static variables in the DSO (dynamic shared
            # # object) from being preserved after dlclose().
            "-fno-gnu-unique"

            # # When Rack loads a plugin, it symlinks /tmp/Rack2 to its
            # # system dir, so the plugin can link to libRack.
            "-Wl,-rpath=/tmp/Rack2"

            # # Since the plugin's compiler could be a different version
            # # than Rack's compiler, link libstdc++ and libgcc statically
            # # to avoid ABI issues.
            "-static-libstdc++"
            "-static-libgcc"
        )
    endif(APPLE)
endif(UNIX)

if(WIN32)
    target_link_options(plugin
        PUBLIC
        "-static-libstdc++"
    )
endif(WIN32)
list(APPEND STONEYVCV_TARGETS plugin)

# install the target and create export-set
install(TARGETS plugin
    EXPORT StoneyVCVPluginTargets
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET stoneyvcv_PLUGIN_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# generate and install export file
install(EXPORT StoneyVCVPluginTargets
    FILE "StoneyVCVPluginTargets.cmake"
    NAMESPACE StoneyDSP::StoneyVCV::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyVCV"
)

export(
    TARGETS plugin
    FILE "share/cmake/StoneyVCVPluginTargets.cmake"
    NAMESPACE StoneyDSP::StoneyVCV::
)

#[==[test]==]
if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)

    target_compile_definitions(plugin PUBLIC "-DSTONEYVCV_BUILD_TESTS=1")

    find_package(Catch2 3.5.2 REQUIRED)

    # # These tests can use the Catch2-provided main
    add_executable(tests)
    add_executable(StoneyVCV::test ALIAS tests)
    add_executable(StoneyDSP::StoneyVCV::test ALIAS tests)
    target_include_directories(tests
        PUBLIC
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_sources(tests
        PRIVATE
        "${PROJECT_SOURCE_DIR}/test/StoneyVCV/plugin.cpp"
    )
    target_link_libraries(tests
        PRIVATE
        unofficial-vcvrack::rack-sdk::lib
        StoneyDSP::StoneyVCV::plugin
        Catch2::Catch2WithMain
    )
    set_target_properties(tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${STONEYVCV_BINARY_DIR}/test"
        RUNTIME_OUTPUT_NAME "tests"
    )
    target_compile_features(tests PUBLIC cxx_std_17)
    target_compile_features(tests PUBLIC c_std_17)
    # list(APPEND STONEYVCV_TARGETS tests)
endif()

if(STONEYVCV_BUILD_MODULES)

# TODO: This module creation stuff can clearly be functionised...
# Would be nice to perhaps define some helper functions in the VCVRack CMake
# files to make this process much more DRY... I have ideas.

#[==[HP1]==]
if(STONEYVCV_BUILD_MODULE_HP1)
    add_library(HP1 OBJECT)
    add_library(StoneyVCV::HP1 ALIAS HP1)
    add_library(StoneyDSP::StoneyVCV::HP1 ALIAS HP1)
    set(STONEYVCV_HP1_HPP "HP1.hpp")
    configure_file("include/StoneyVCV/${STONEYVCV_HP1_HPP}" "include/StoneyVCV/${STONEYVCV_HP1_HPP}")
    set_target_properties(HP1 PROPERTIES VERSION 0.0.1)
    set_target_properties(HP1 PROPERTIES SOVERSION 0.0.1)
    target_sources(HP1 PRIVATE "src/StoneyVCV/HP1.cpp")
    target_sources(HP1
        PUBLIC
        FILE_SET stoneyvcv_HP1_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        FILES
        #[==[include/plugin.hpp]==]
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include/StoneyVCV/${STONEYVCV_HP1_HPP}>
        $<INSTALL_INTERFACE:include/StoneyVCV/${STONEYVCV_HP1_HPP}>
    )
    target_compile_options(HP1
        PUBLIC
        "-fPIC"
    )
    target_compile_definitions(HP1
        PUBLIC
        "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
        "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
        "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
        "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
        "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
    )
    target_link_libraries(HP1
        PUBLIC
        unofficial-vcvrack::rack-sdk::core
        StoneyDSP::Core
    )
    target_link_libraries(plugin PUBLIC StoneyDSP::StoneyVCV::HP1)
    target_compile_definitions(plugin PUBLIC "-DSTONEYVCV_BUILD_HP1=1")
    # install the target and create export-set
    install(TARGETS HP1
        EXPORT StoneyVCVHP1Targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILE_SET stoneyvcv_HP1_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
    # generate and install export file
    install(EXPORT StoneyVCVHP1Targets
        FILE "StoneyVCVHP1Targets.cmake"
        NAMESPACE StoneyDSP::StoneyVCV::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyVCV"
    )
    export(
        TARGETS HP1
        FILE "share/cmake/StoneyVCVHP1Targets.cmake"
        NAMESPACE StoneyDSP::StoneyVCV::
    )
    list(APPEND STONEYVCV_TARGETS HP1)
endif(STONEYVCV_BUILD_MODULE_HP1)

#[==[HP2]==]
if(STONEYVCV_BUILD_MODULE_HP2)
    add_library(HP2 OBJECT)
    add_library(StoneyVCV::HP2 ALIAS HP2)
    add_library(StoneyDSP::StoneyVCV::HP2 ALIAS HP2)
    set_target_properties(HP2 PROPERTIES VERSION 0.0.1)
    set_target_properties(HP2 PROPERTIES SOVERSION 0.0.1)
    set(STONEYVCV_HP2_HPP "HP2.hpp")
    configure_file("include/StoneyVCV/${STONEYVCV_HP2_HPP}" "include/StoneyVCV/${STONEYVCV_HP2_HPP}")
    target_sources(HP2 PRIVATE "src/StoneyVCV/HP2.cpp")
    target_sources(HP2
        PUBLIC
        FILE_SET stoneyvcv_HP2_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        FILES
        #[==[include/plugin.hpp]==]
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include/StoneyVCV/${STONEYVCV_HP2_HPP}>
        $<INSTALL_INTERFACE:include/StoneyVCV/${STONEYVCV_HP2_HPP}>
    )
    target_compile_options(HP2
        PUBLIC
        "-fPIC"
    )
    target_compile_definitions(HP2
        PUBLIC
        "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
        "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
        "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
        "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
        "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
    )
    target_link_libraries(HP2
        PUBLIC
        unofficial-vcvrack::rack-sdk::core
        StoneyDSP::Core
    )
    target_link_libraries(plugin PUBLIC StoneyDSP::StoneyVCV::HP2)
    target_compile_definitions(plugin PUBLIC "-DSTONEYVCV_BUILD_HP2=1")
    # install the target and create export-set
    install(TARGETS HP2
        EXPORT StoneyVCVHP2Targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILE_SET stoneyvcv_HP2_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
    # generate and install export file
    install(EXPORT StoneyVCVHP2Targets
        FILE "StoneyVCVHP2Targets.cmake"
        NAMESPACE StoneyDSP::StoneyVCV::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyVCV"
    )
    export(
        TARGETS HP2
        FILE "share/cmake/StoneyVCVHP2Targets.cmake.cmake"
        NAMESPACE StoneyDSP::StoneyVCV::
    )
    list(APPEND STONEYVCV_TARGETS HP2)
endif(STONEYVCV_BUILD_MODULE_HP2)

#[==[HP4]==]
if(STONEYVCV_BUILD_MODULE_HP4)
    add_library(HP4 OBJECT)
    add_library(StoneyVCV::HP4 ALIAS HP4)
    add_library(StoneyDSP::StoneyVCV::HP4 ALIAS HP4)
    set(STONEYVCV_HP4_HPP "HP4.hpp")
    configure_file("include/StoneyVCV/${STONEYVCV_HP4_HPP}" "include/StoneyVCV/${STONEYVCV_HP4_HPP}")
    set_target_properties(HP2 PROPERTIES VERSION 0.0.1)
    set_target_properties(HP2 PROPERTIES SOVERSION 0.0.1)
    target_sources(HP4 PRIVATE "src/StoneyVCV/HP4.cpp")
    target_sources(HP4
        PUBLIC
        FILE_SET stoneyvcv_HP4_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        FILES
        #[==[include/plugin.hpp]==]
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include/StoneyVCV/${STONEYVCV_HP4_HPP}>
        $<INSTALL_INTERFACE:include/StoneyVCV/${STONEYVCV_HP4_HPP}>
    )
    target_compile_options(HP4
        PUBLIC
        "-fPIC"
    )
    target_compile_definitions(HP4
        PUBLIC
        "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
        "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
        "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
        "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
        "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
    )
    target_link_libraries(HP4
        PUBLIC
        unofficial-vcvrack::rack-sdk::core
        StoneyDSP::Core
    )
    target_link_libraries(plugin PUBLIC StoneyDSP::StoneyVCV::HP4)
    target_compile_definitions(plugin PUBLIC "-DSTONEYVCV_BUILD_HP4=1")
    # install the target and create export-set
    install(TARGETS HP4
        EXPORT StoneyVCVHP4Targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILE_SET stoneyvcv_HP4_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
    # generate and install export file
    install(EXPORT StoneyVCVHP4Targets
        FILE "StoneyVCVHP4Targets.cmake"
        NAMESPACE StoneyDSP::StoneyVCV::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyVCV"
    )
    export(
        TARGETS HP4
        FILE "share/cmake/StoneyVCVHP4Targets.cmake.cmake"
        NAMESPACE StoneyDSP::StoneyVCV::
    )
    list(APPEND STONEYVCV_TARGETS HP4)
endif(STONEYVCV_BUILD_MODULE_HP4)

if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)
    if(STONEYVCV_BUILD_MODULE_HP4)
        target_sources(tests
        PRIVATE
        "${PROJECT_SOURCE_DIR}/test/StoneyVCV/HP4.cpp"
    )
    endif(STONEYVCV_BUILD_MODULE_HP4)
    if(STONEYVCV_BUILD_MODULE_HP2)
        target_sources(tests
        PRIVATE
        "${PROJECT_SOURCE_DIR}/test/StoneyVCV/HP2.cpp"
    )
    endif(STONEYVCV_BUILD_MODULE_HP2)
    if(STONEYVCV_BUILD_MODULE_HP1)
        target_sources(tests
        PRIVATE
        "${PROJECT_SOURCE_DIR}/test/StoneyVCV/HP1.cpp"
    )
    endif(STONEYVCV_BUILD_MODULE_HP1)
endif()

endif(STONEYVCV_BUILD_MODULES)

# set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "" FORCE)
# set(CMAKE_AUTOGEN_VERBOSE TRUE CACHE BOOL "" FORCE)

# #[==[plugin]==]
# add_custom_target(plugin ALL
# COMMAND "make"
# WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
# BYPRODUCTS
# "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
# SOURCES
# "${PROJECT_SOURCE_DIR}/src/${PLUGIN_CPP}"
# "${PROJECT_BINARY_DIR}/include/${PLUGIN_HPP}"
# JOB_SERVER_AWARE TRUE
# DEPENDS StoneyVCV
# USES_TERMINAL
# )

# #[==[dist]==]
# add_custom_target(dist
# COMMAND "make" "dist"
# WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
# BYPRODUCTS
# "${PROJECT_SOURCE_DIR}/dist"
# SOURCES
# "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
# JOB_SERVER_AWARE TRUE
# DEPENDS plugin
# USES_TERMINAL
# )

#[==[clean]==] # Not supported...
# add_custom_target(clean
# COMMAND "make" "clean"
# WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
# BYPRODUCTS "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
# SOURCES
# "${PROJECT_SOURCE_DIR}/src/${PLUGIN_CPP}"
# "${PROJECT_BINARY_DIR}/include/${PLUGIN_HPP}"
# JOB_SERVER_AWARE TRUE
# USES_TERMINAL
# )

if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)
    enable_testing()

    include(CTest)
    include(Catch)

    set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

    set(dl_paths)
    list(APPEND dl_paths "${rack_link_dir}")

    catch_discover_tests(tests)
endif()

# # install the target and create export-set
# install(TARGETS ${STONEYVCV_TARGETS}
#     EXPORT StoneyVCVTargets
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#     FILE_SET stoneyvcv_PLUGIN_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StoneyVCV"
#     FILE_SET stoneyvcv_HP1_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StoneyVCV"
#     FILE_SET stoneyvcv_HP2_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StoneyVCV"
#     FILE_SET stoneyvcv_HP4_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StoneyVCV"
# )

# # generate and install export file
# install(EXPORT StoneyVCVTargets
#     FILE "StoneyVCVTargets.cmake"
#     NAMESPACE StoneyDSP::StoneyVCV::
#     DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyVCV"
# )
# export(
#     TARGETS ${STONEYVCV_TARGETS}
#     FILE "share/cmake/StoneyVCVTargets.cmake"
#     NAMESPACE StoneyDSP::StoneyVCV::
# )

#[==[StoneyVCVConfig.cmake]==]
include(CMakePackageConfigHelpers)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/StoneyVCVConfig.cmake.in" [==[
@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/StoneyVCVConfigVersion.cmake")

set(_StoneyVCV_supported_components)
list(APPEND _StoneyVCV_supported_components
    @STONEYVCV_TARGETS@
)

## Custom 'check_required_components' macro
foreach(_requested_component ${StoneyVCV_FIND_COMPONENTS})
  if (NOT _requested_component IN_LIST _StoneyVCV_supported_components)
    set(StoneyVCV_FOUND False)
    set(StoneyVCV_NOT_FOUND_MESSAGE "Unsupported component: ${_requested_component}")
  endif()
  include("${CMAKE_CURRENT_LIST_DIR}/StoneyVCV${_requested_component}Targets.cmake")
  message(STATUS "Linking with StoneyVCV::${_requested_component}")
endforeach()

unset(_StoneyVCV_supported_components)

# Tell the user what to do
message(STATUS "Linking with StoneyVCV")

]==])

configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/StoneyVCVConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyVCVConfig.cmake"
    INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyVCV"

    # # Use custom 'check_required_components' macro
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyVCVConfigVersion.cmake"
    VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyVCVConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyVCVConfigVersion.cmake"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyVCV"
)
install(DIRECTORY
    "${STONEYVCV_SOURCE_DIR}/res"
    DESTINATION
    # This is not a good location to be using...
    "${CMAKE_INSTALL_PREFIX}"
)
install(
    FILES
    "${STONEYVCV_SOURCE_DIR}/LICENSE"
    "${STONEYVCV_SOURCE_DIR}/VERSION"
    "${STONEYVCV_SOURCE_DIR}/plugin.json"
    DESTINATION
    # This is not a good location to be using...
    "${CMAKE_INSTALL_PREFIX}"
)
