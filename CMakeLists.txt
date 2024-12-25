cmake_minimum_required(VERSION 3.23...3.31 FATAL_ERROR)

#[==============================[Version control]==============================]

set(STONEYVCV_BRAND "StoneyDSP" CACHE STRING "" FORCE)
set(STONEYVCV_SLUG "StoneyVCV" CACHE STRING "" FORCE)
set(STONEYVCV_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "" FORCE)
set(STONEYVCV_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE PATH "" FORCE)

# https://softwareengineering.stackexchange.com/questions/141973/how-do-you-achieve-a-numeric-versioning-scheme-with-git
# 'git rev-list HEAD | wc -l'
find_package(Git REQUIRED)
execute_process(
    COMMAND "${GIT_EXECUTABLE}" "rev-list" "HEAD"
    COMMAND "wc" "-l"
    WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
    OUTPUT_VARIABLE _STONEYVCV_GIT_COMMIT_COUNT
    ERROR_VARIABLE _STONEYVCV_GIT_COMMIT_COUNT_ERROR
)
if(_STONEYVCV_GIT_COMMIT_COUNT_ERROR)
    message(SEND_ERROR "${_STONEYVCV_GIT_COMMIT_COUNT_ERROR}")
endif()
execute_process(
    COMMAND "${GIT_EXECUTABLE}" "rev-parse" "HEAD"
    WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
    OUTPUT_VARIABLE _STONEYVCV_GIT_REF_HEAD
    ERROR_VARIABLE _STONEYVCV_GIT_REF_HEAD_ERROR
)
if(_STONEYVCV_GIT_REF_HEAD_ERROR)
    message(SEND_ERROR "${_STONEYVCV_GIT_REF_HEAD_ERROR}")
endif()
execute_process(
    COMMAND "${GIT_EXECUTABLE}" "rev-parse" "--short" "HEAD"
    WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
    OUTPUT_VARIABLE _STONEYVCV_GIT_REF_HEAD_SHORT
    ERROR_VARIABLE _STONEYVCV_GIT_REF_HEAD_SHORT_ERROR
)
if(_STONEYVCV_GIT_REF_HEAD_SHORT_ERROR)
    message(SEND_ERROR "${_STONEYVCV_GIT_REF_HEAD_SHORT_ERROR}")
endif()
execute_process(
    COMMAND "${GIT_EXECUTABLE}" rev-parse --abbrev-ref --symbolic-full-name HEAD
    WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
    OUTPUT_VARIABLE _STONEYVCV_GIT_BRANCH
    ERROR_VARIABLE _STONEYVCV_GIT_BRANCH_ERROR
)
if(_STONEYVCV_GIT_BRANCH_ERROR)
    message(SEND_ERROR "${_STONEYVCV_GIT_BRANCH_ERROR}")
endif()
string(STRIP "${_STONEYVCV_GIT_COMMIT_COUNT}" STONEYVCV_GIT_COMMIT_COUNT)
string(STRIP "${_STONEYVCV_GIT_REF_HEAD}" _STONEYVCV_GIT_REF_HEAD)
string(STRIP "${_STONEYVCV_GIT_REF_HEAD_SHORT}" _STONEYVCV_GIT_REF_HEAD_SHORT)
string(STRIP "${_STONEYVCV_GIT_BRANCH}" STONEYVCV_GIT_BRANCH)

string(HEX "${_STONEYVCV_GIT_REF_HEAD}" STONEYVCV_GIT_REF_HEAD)
string(HEX "${_STONEYVCV_GIT_REF_HEAD_SHORT}" STONEYVCV_GIT_REF_HEAD_SHORT)

file(READ "${CMAKE_CURRENT_LIST_DIR}/plugin.json" STONEYVCV_PLUGIN_JSON)
string(CONFIGURE "2.0.@STONEYVCV_GIT_COMMIT_COUNT@" _STONEYVCV_PLUGIN_JSON_VERSION @ONLY)
string(JSON _STONEYVCV_PLUGIN_JSON ERROR_VARIABLE _STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR SET "${STONEYVCV_PLUGIN_JSON}" "version" "\"${_STONEYVCV_PLUGIN_JSON_VERSION}\"")

if(_STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR)
    message(FATAL_ERROR "${_STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR}")
endif(_STONEYVCV_PLUGIN_JSON_SET_ROOT_ERROR)

file(WRITE "${CMAKE_CURRENT_LIST_DIR}/plugin.json.tmp" "${_STONEYVCV_PLUGIN_JSON}")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_LIST_DIR}/plugin.json.tmp" "${CMAKE_CURRENT_LIST_DIR}/plugin.json")
file(REMOVE "${CMAKE_CURRENT_LIST_DIR}/plugin.json.tmp")

unset(_STONEYVCV_PLUGIN_JSON)
unset(_STONEYVCV_PLUGIN_JSON_VERSION)

#[==================================[project]==================================]
project(STONEYVCV
    VERSION "2.0.${STONEYVCV_GIT_COMMIT_COUNT}.${STONEYVCV_GIT_REF_HEAD_SHORT}"
    DESCRIPTION "${STONEYVCV_BRAND} Modules for VCV Rack 2."
    HOMEPAGE_URL "https://github.com/${STONEYVCV_BRAND}/${STONEYVCV_SLUG}"
)

set(PROJECT_NAME "StoneyVCV" CACHE STRING "" FORCE)

enable_language(C)
enable_language(CXX)

include(CMakeDependentOption)
include(GNUInstallDirs)

option(STONEYVCV_EXPERIMENTAL                       "Use '-DSTONEYVCV_EXPERIMENTAL=ON|OFF' when configuring to toggle this option." OFF)
option(STONEYVCV_BUILD_DOCS "" OFF)
option(STONEYVCV_BUILD_PLUGIN                       "Use '-DSTONEYVCV_BUILD_PLUGIN=ON|OFF' when configuring to toggle this option." ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULES      "Use '-DSTONEYVCV_BUILD_MODULES=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_PLUGIN" ON)
cmake_dependent_option(STONEYVCV_BUILD_HP1          "Use '-DSTONEYVCV_BUILD_HP1=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_HP2          "Use '-DSTONEYVCV_BUILD_HP2=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_HP4          "Use '-DSTONEYVCV_BUILD_HP4=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_VCA          "Use '-DSTONEYVCV_BUILD_VCA=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_LFO          "Use '-DSTONEYVCV_BUILD_LFO=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_EXPERIMENTAL" ON)
cmake_dependent_option(STONEYVCV_BUILD_TESTS        "Use '-DSTONEYVCV_BUILD_TESTS=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_IS_TOP_LEVEL" ON)

# Put components in the correct order of their dependencies on eachother to save tears...
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib CONFIG)
find_package(StoneyDSP 0.0.0 REQUIRED COMPONENTS Core SIMD DSP CONFIG)

set(STONEYVCV_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_TWEAK "${CMAKE_PROJECT_VERSION_TWEAK}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION "${CMAKE_PROJECT_VERSION}" CACHE STRING "" FORCE)

# Validate plugin.json
vcvrack_get_plugin_version()

if(NOT "${VCVRACK_PLUGIN_VERSION}" STREQUAL "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}")
    set(_STONEYVCV_ERROR_STRING [==[

There is a mismatch between plugin versions in 'plugin.json' and 'CMakeLists.txt':
plugin.json#version: @VCVRACK_PLUGIN_VERSION@
project(VERSION @STONEYVCV_VERSION_MAJOR@.@STONEYVCV_VERSION_MINOR@.@STONEYVCV_VERSION_PATCH@
Please update the version number in the following files in order to silence this error:
@STONEYVCV_SOURCE_DIR@/plugin.json
@STONEYVCV_SOURCE_DIR@/CMakeLists.txt
    ]==])
    string(CONFIGURE "${_STONEYVCV_ERROR_STRING}" STONEYVCV_ERROR_STRING @ONLY)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        message(SEND_ERROR "${STONEYVCV_ERROR_STRING}")
        return()
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        message(WARNING "${STONEYVCV_ERROR_STRING}")
    endif()
endif()

set(STONEYVCV_VERSION_FILE "${STONEYVCV_SOURCE_DIR}/VERSION")
file(WRITE "${STONEYVCV_VERSION_FILE}.tmp" "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}.${STONEYVCV_VERSION_TWEAK}\n")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${STONEYVCV_VERSION_FILE}.tmp" "${STONEYVCV_VERSION_FILE}")
file(REMOVE "${STONEYVCV_VERSION_FILE}.tmp")
set(STONEYVCV_VERSION_FILE "${STONEYVCV_VERSION_FILE}" CACHE INTERNAL "StoneyVCV current version file." FORCE)


# Initialize list of targets to build
set(STONEYVCV_TARGETS)

#[=================================[StoneyVCV]=================================]
# Core interface library - base dependency carrier for other developers
add_library("${STONEYVCV_SLUG}" INTERFACE)
add_library("${STONEYVCV_BRAND}::${STONEYVCV_SLUG}" ALIAS "${STONEYVCV_SLUG}")
configure_file("include/StoneyVCV.hpp" "include/StoneyVCV.hpp")
target_sources("${STONEYVCV_SLUG}"
    INTERFACE
    FILE_SET stoneyvcv_INTERFACE_HEADERS
    TYPE HEADERS
    BASE_DIRS
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    FILES
    $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include/${STONEYVCV_SLUG}.hpp>
    $<INSTALL_INTERFACE:include/${STONEYVCV_SLUG}.hpp>
)
# Add project version number
set_target_properties("${STONEYVCV_SLUG}"
    PROPERTIES
    VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}"
    SOVERSION "${STONEYVCV_VERSION_MAJOR}"
)
target_compile_definitions("${STONEYVCV_SLUG}"
    INTERFACE
    "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
    "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
    "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
    "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
    "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
)
# bump C++ version up from Rack-SDK
target_compile_features("${STONEYVCV_SLUG}" INTERFACE cxx_std_17)
target_compile_features("${STONEYVCV_SLUG}" INTERFACE c_std_17)
target_link_libraries("${STONEYVCV_SLUG}"
    INTERFACE
        unofficial-vcvrack::rack-sdk::core
        StoneyDSP::Core
)
install(TARGETS ${STONEYVCV_SLUG}
    EXPORT ${STONEYVCV_SLUG}Exports
    COMPONENT ${STONEYVCV_SLUG}
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET stoneyvcv_INTERFACE_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
install(EXPORT ${STONEYVCV_SLUG}Exports
    FILE "${STONEYVCV_BRAND}-${STONEYVCV_SLUG}-targets.cmake"
    NAMESPACE ${STONEYVCV_BRAND}::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYVCV_BRAND}"
)
export(SETUP ${STONEYVCV_SLUG}Exports)
export(
    EXPORT ${STONEYVCV_SLUG}Exports
    FILE "lib/cmake/${STONEYVCV_BRAND}/$${STONEYVCV_BRAND}-${STONEYVCV_SLUG}-targets.cmake"
    NAMESPACE ${STONEYVCV_BRAND}::
)
message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG} v${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}")

#[==================================[plugin]==================================]#

if(STONEYVCV_BUILD_PLUGIN)

    set(plugin_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(plugin_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    set(plugin_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}")
    set(plugin_VERSION "${plugin_VERSION_MAJOR}.${plugin_VERSION_MINOR}.${plugin_VERSION_PATCH}")

    # create rack-sdk plugin target
    vcvrack_add_plugin(
        SLUG "${STONEYVCV_SLUG}"
        BRAND "${STONEYVCV_BRAND}"
        HEADERS "include/${STONEYVCV_SLUG}/plugin.hpp" "include/${STONEYVCV_SLUG}/version.hpp"
        SOURCES "src/${STONEYVCV_SLUG}/plugin.cpp"
        VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}"
        SOVERSION "${STONEYVCV_VERSION_MAJOR}"
        EXPORT
        INSTALL
    )

    target_link_libraries(plugin PUBLIC "${STONEYVCV_BRAND}::${STONEYVCV_SLUG}")

    target_compile_definitions(plugin
        PUBLIC
            "-DSTONEYVCV_BUILD_PLUGIN=1"
    )

    if(STONEYVCV_BUILD_MODULES)
        target_compile_definitions(plugin
            PUBLIC
                "-DSTONEYVCV_BUILD_MODULES=1"
        )
    endif()

    # plugin custom dependencies
    target_link_libraries(plugin
        PUBLIC
            StoneyDSP::Core
    )

    list(APPEND STONEYVCV_TARGETS plugin) # Collect list of targets to build...
    message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::plugin v${plugin_VERSION}")

endif(STONEYVCV_BUILD_PLUGIN)

#[==[test]==]
function(stoneyvcv_add_test MODULE)

    set(tests_${MODULE}_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(tests_${MODULE}_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    set(tests_${MODULE}_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}")
    set(tests_${MODULE}_VERSION "${tests_${MODULE}_VERSION_MAJOR}.${tests_${MODULE}_VERSION_MINOR}.${tests_${MODULE}_VERSION_PATCH}")

    add_library(tests_${MODULE} OBJECT EXCLUDE_FROM_ALL)
    add_library(${STONEYVCV_SLUG}::tests_${MODULE} ALIAS tests_${MODULE})
    add_library(${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests_${MODULE} ALIAS tests_${MODULE})
    set_target_properties(tests_${MODULE}
        PROPERTIES
            VERSION "${tests_${MODULE}_VERSION}"
            SOVERSION "${tests_${MODULE}_VERSION_MAJOR}"
        )
    target_include_directories(tests_${MODULE}
        PUBLIC
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_sources(tests_${MODULE}
        PRIVATE
            "${STONEYVCV_SOURCE_DIR}/test/${STONEYVCV_SLUG}/${MODULE}.cpp"
    )
    target_link_libraries(tests_${MODULE}
        PUBLIC
            unofficial-vcvrack::rack-sdk::core
            ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::${MODULE}
            Catch2::Catch2
    )
    target_compile_definitions(tests_${MODULE}
        PUBLIC
            "-Dtests_${MODULE}_VERSION_MAJOR=${tests_${MODULE}_VERSION_MAJOR}"
            "-Dtests_${MODULE}_VERSION_MINOR=${tests_${MODULE}_VERSION_MINOR}"
            "-Dtests_${MODULE}_VERSION_PATCH=${tests_${MODULE}_VERSION_PATCH}"
            "-Dtests_${MODULE}_VERSION=${tests_${MODULE}_VERSION}"
    )
    target_compile_features(tests_${MODULE} PUBLIC cxx_std_17)
    target_compile_features(tests_${MODULE} PUBLIC c_std_17)
    message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests_${MODULE} v${tests_${MODULE}_VERSION}")
endfunction()

if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)

    find_package(Catch2 3.5.2 REQUIRED)

    set(tests_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(tests_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    set(tests_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}")
    set(tests_VERSION "${tests_VERSION_MAJOR}.${tests_VERSION_MINOR}.${tests_VERSION_PATCH}")

    add_executable(tests)
    add_executable(StoneyVCV::tests ALIAS tests)
    add_executable(${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests ALIAS tests)
    target_include_directories(tests
        PUBLIC
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(tests
        PUBLIC
        unofficial-vcvrack::rack-sdk::lib
        ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::plugin
        Catch2::Catch2WithMain
    )
    set_target_properties(tests
        PROPERTIES
        VERSION "${tests_VERSION}"
        SOVERSION "${tests_VERSION_MAJOR}"
        RUNTIME_OUTPUT_DIRECTORY "${STONEYVCV_BINARY_DIR}/test"
        RUNTIME_OUTPUT_NAME "tests"
    )
    target_compile_features(tests PUBLIC cxx_std_17)
    target_compile_features(tests PUBLIC c_std_17)
    target_compile_definitions(tests
        PUBLIC
        "-Dtests_VERSION_MAJOR=${tests_VERSION_MAJOR}"
        "-Dtests_VERSION_MINOR=${tests_VERSION_MINOR}"
        "-Dtests_VERSION_PATCH=${tests_VERSION_PATCH}"
        "-Dtests_VERSION=${tests_VERSION}"
    )
    if(STONEYVCV_BUILD_PLUGIN)
        target_compile_definitions(tests
            PUBLIC
                "-DSTONEYVCV_BUILD_PLUGIN=1"
        )
    endif()
    if(STONEYVCV_BUILD_MODULES)
        target_compile_definitions(tests
            PUBLIC
                "-DSTONEYVCV_BUILD_MODULES=1"
        )
    endif()
    message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests v${tests_VERSION}")
endif()

#[==================================[Modules]==================================]

if(STONEYVCV_BUILD_MODULES)

    set(STONEYVCV_MODULES)
    list(APPEND STONEYVCV_MODULES # List of enabled modules
        HP4
        HP2
        HP1
        VCA
    )

    set(STONEYVCV_EXPERIMENTAL_MODULES)
    list(APPEND STONEYVCV_EXPERIMENTAL_MODULES # List of enabled experimental modules
        LFO
    )

    if(STONEYVCV_EXPERIMENTAL)
        list(APPEND STONEYVCV_MODULES ${STONEYVCV_EXPERIMENTAL_MODULES})
    endif()

    foreach(MODULE IN LISTS STONEYVCV_MODULES)

        if(STONEYVCV_BUILD_${MODULE}) # Toggle module code with -D

            set(${MODULE}_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
            set(${MODULE}_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
            execute_process(
                COMMAND "${GIT_EXECUTABLE}" rev-list module/${MODULE}
                COMMAND wc -l
                OUTPUT_VARIABLE ${MODULE}_VERSION_PATCH
                ERROR_VARIABLE _${MODULE}_VERSION_PATCH
            )
            if(${_${MODULE}_VERSION_PATCH})
                message(WARNING "git: could not find a corresponding module/${MODULE} branch for module ${MODULE}")
            endif()
            string(STRIP "${${MODULE}_VERSION_PATCH}" ${MODULE}_VERSION_PATCH)
            set(${MODULE}_VERSION "${${MODULE}_VERSION_MAJOR}.${${MODULE}_VERSION_MINOR}.${${MODULE}_VERSION_PATCH}")

            vcvrack_add_module(${MODULE}
                SLUG "${STONEYVCV_SLUG}"
                BRAND "${STONEYVCV_BRAND}"
                HEADERS "include/${STONEYVCV_SLUG}/${MODULE}.hpp"
                SOURCES "src/${STONEYVCV_SLUG}/${MODULE}.cpp"
                VERSION "${${MODULE}_VERSION}"
                SOVERSION "${STONEYVCV_VERSION_MAJOR}"
                EXPORT
                INSTALL
            )
            target_compile_definitions(${MODULE}
                PUBLIC
                    "-DSTONEYVCV_BUILD_PLUGIN=1"
                    "-DSTONEYVCV_BUILD_MODULES=1"
                    "-DSTONEYVCV_BUILD_${MODULE}=1"
                    "-D${MODULE}_VERSION=${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${${MODULE}_VERSION_PATCH}"
            )

            list(APPEND STONEYVCV_TARGETS ${MODULE}) # Collect enabled modules
            message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::${MODULE} v${${MODULE}_VERSION}")

        endif()

    endforeach()

    # add dep: StoneyDSP::Core
    foreach(CORE_MODULE IN LISTS HP1;HP2;HP4;VCA;LFO)
        if(STONEYVCV_BUILD_${CORE_MODULE}) #if enabled with -D...
            target_link_libraries(${CORE_MODULE} PRIVATE StoneyDSP::Core)
        endif()
    endforeach()

    # add dep: StoneyDSP::DSP
    foreach(DSP_MODULE IN LISTS VCA;LFO)
        if(STONEYVCV_BUILD_${DSP_MODULE}) #if enabled with -D...
            target_link_libraries(${DSP_MODULE} PRIVATE StoneyDSP::DSP)
        endif()
    endforeach()

    # add dep: StoneyDSP::SIMD
    foreach(SIMD_MODULE IN LISTS VCA;LFO)
        if(STONEYVCV_BUILD_${SIMD_MODULE}) #if enabled with -D...
            target_link_libraries(${SIMD_MODULE} PRIVATE StoneyDSP::SIMD)
        endif()
    endforeach()

endif(STONEYVCV_BUILD_MODULES)

#[==[All Enabled Targets]==]
foreach(TARGET IN LISTS STONEYVCV_TARGETS)

    # Add project version number
    target_compile_definitions(${TARGET}
        PUBLIC
        "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
        "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
        "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
        "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
        "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
    )

    # Toggle plugin module code
    target_compile_definitions(plugin
        PUBLIC
            "-DSTONEYVCV_BUILD_${TARGET}=1"
    )

    # Toggle experimental code
    if(STONEYVCV_EXPERIMENTAL)
        target_compile_definitions(${TARGET}
            PUBLIC
                "STONEYVCV_EXPERIMENTAL=${STONEYVCV_EXPERIMENTAL}"
        )
    endif(STONEYVCV_EXPERIMENTAL)

    # Toggle unit test code
    if(STONEYVCV_BUILD_TESTS)
        stoneyvcv_add_test(${TARGET})
        target_link_libraries(tests PUBLIC ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::tests_${TARGET})
        target_compile_definitions(${TARGET}
            PUBLIC
                "-DSTONEYVCV_BUILD_TESTS=1"
        )
        target_compile_definitions(tests
            PUBLIC
                "-DSTONEYVCV_BUILD_${TARGET}=1"
        )
    endif(STONEYVCV_BUILD_TESTS)

endforeach()

#[===================================[docs]===================================]#

if(STONEYVCV_BUILD_DOCS)
    find_package(Doxygen)
    doxygen_add_docs(docs
        CONFIG_FILE "${STONEYVCV_SOURCE_DIR}/docs/Doxyfile"
        WORKING_DIRECTORY "${STONEYVCV_SOURCE_DIR}"
    )
    # add_library(${STONEYVCV_SLUG}::docs ALIAS docs)
    # add_library(${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::docs ALIAS docs)
    set_target_properties(docs PROPERTIES
        VERSION "${STONEYVCV_VERSION}"
        SOVERSION "${STONEYVCV_VERSION_MAJOR}"
    )
    message(STATUS "Added target: ${STONEYVCV_BRAND}::${STONEYVCV_SLUG}::docs v${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}")
endif()

#[============================[Write CMake Package]============================]

include(CMakePackageConfigHelpers)

get_target_property(__plugin_interface_linker_opts plugin
    INTERFACE_LINK_OPTIONS
)
set(plugin_interface_linker_opts)
foreach(plugin_linker_opt IN LISTS __plugin_interface_linker_opts)
    set(plugin_interface_linker_opts "${plugin_linker_opt} ${plugin_interface_linker_opts}")
endforeach()

get_target_property(__plugin_interface_compiler_opts plugin
    INTERFACE_COMPILE_OPTIONS
)
set(plugin_interface_compiler_opts)
foreach(plugin_compiler_opt IN LISTS __plugin_interface_compiler_opts)
    set(plugin_interface_compiler_opts "${plugin_compiler_opt} ${plugin_interface_compiler_opts}")
endforeach()

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/StoneyVCV.pc.in" [==[
prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/@CMAKE_INSTALL_LIBDIR@
includedir=${prefix}/@CMAKE_INSTALL_INCLUDEDIR@

Name: StoneyVCV
Description: @PROJECT_DESCRIPTION@
Version: @PROJECT_VERSION@
Requires: Rack-SDK = 2.5.2
Libs: -L${libdir} -lRack @plugin_interface_linker_opts@
Cflags: -I${includedir} @plugin_interface_compiler_opts@
]==])

configure_file (
  "${CMAKE_CURRENT_BINARY_DIR}/StoneyVCV.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/lib/pkgconfig/StoneyVCV.pc"
  @ONLY
)

unset(plugin_interface_linker_opts)
unset(__plugin_interface_linker_opts)

unset(plugin_interface_compiler_opts)
unset(__plugin_interface_compiler_opts)



install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/lib/pkgconfig/${STONEYVCV_SLUG}.pc"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${STONEYVCV_BRAND}-${STONEYVCV_SLUG}Config.cmake.in" [==[
@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/@STONEYVCV_BRAND@-@STONEYVCV_SLUG@ConfigVersion.cmake")

include(CMakeFindDependencyMacro)

find_dependency(rack-sdk 2.5.2)
find_dependency(StoneyDSP 0.0.0)

set(_@STONEYVCV_SLUG@_supported_components)
list(APPEND _@STONEYVCV_SLUG@_supported_components
    @STONEYVCV_TARGETS@
)

## Custom 'check_required_components' macro
foreach(_requested_component ${@STONEYVCV_SLUG@_FIND_COMPONENTS})
  if (NOT _requested_component IN_LIST _@STONEYVCV_SLUG@_supported_components)
    set(@STONEYVCV_SLUG@_FOUND False)
    set(@STONEYVCV_SLUG@_NOT_FOUND_MESSAGE "Unsupported component: ${_requested_component}")
  endif()
  include("${CMAKE_CURRENT_LIST_DIR}/@STONEYVCV_SLUG@${_requested_component}Targets.cmake")
  message(STATUS "Linking with @STONEYVCV_SLUG@::${_requested_component}")
endforeach()

unset(_@STONEYVCV_SLUG@_supported_components)

# Tell the user what to do
message(STATUS "Linking with @STONEYVCV_SLUG@")

]==])
# generate a basic package config file
configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${STONEYVCV_BRAND}-${STONEYVCV_SLUG}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYVCV_BRAND}/${STONEYVCV_BRAND}-${STONEYVCV_SLUG}Config.cmake"
    INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYVCV_BRAND}"
    # Use custom 'check_required_components' macro
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYVCV_BRAND}/${STONEYVCV_BRAND}-${STONEYVCV_SLUG}ConfigVersion.cmake"
    VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}"
    COMPATIBILITY ExactVersion
)

#[===========================[Install CMake Package]===========================]

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYVCV_BRAND}/${STONEYVCV_BRAND}-${STONEYVCV_SLUG}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYVCV_BRAND}/${STONEYVCV_BRAND}-${STONEYVCV_SLUG}ConfigVersion.cmake"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYVCV_BRAND}"
)
install(DIRECTORY
    "${STONEYVCV_SOURCE_DIR}/res"
    DESTINATION
    # This is not a good location to be using...
    "${CMAKE_INSTALL_DATADIR}"
)
install(DIRECTORY
    "${STONEYVCV_SOURCE_DIR}/presets"
    DESTINATION
    # This is not a good location to be using...
    "${CMAKE_INSTALL_DATADIR}"
)
install(
    FILES
    "${STONEYVCV_SOURCE_DIR}/LICENSE"
    "${STONEYVCV_SOURCE_DIR}/VERSION"
    "${STONEYVCV_SOURCE_DIR}/plugin.json"
    DESTINATION
    # This is not a good location to be using...
    "${CMAKE_INSTALL_DATADIR}"
)

#[=============================[Enable Unit Tests]=============================]

if(STONEYVCV_BUILD_TESTS)
    enable_testing()
    include(CTest)
    include(Catch)
    set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
    catch_discover_tests(tests)
endif()

if(STONEYVCV_IS_TOP_LEVEL)
    # add CPack to project
    set(CPACK_PACKAGE_NAME "${STONEYVCV_SLUG}")
    set(CPACK_PACKAGE_VENDOR "${STONEYVCV_BRAND}")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "StoneyDSP modules for VCV Rack 2.")
    set(CPACK_PACKAGE_VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}")
    set(CPACK_PACKAGE_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${STONEYVCV_BRAND}")
    # set(CPACK_GENERATOR)
    # list(APPEND CPACK_GENERATOR "ZIP")
    set(CPACK_SOURCE_IGNORE_FILES)
    list(APPEND CPACK_SOURCE_IGNORE_FILES
        "/_CPack_Packages/"
        "/install/"
        "/build/"
        "/dist/"
        "/out/"
        "/.git/"
        "/.github/"
        "/.vscode/"
        "/*.zip"
        "/*.tar"
        "/*.tar.gz"
        "/*.tar.xz"
        "/*.tar.bz2"
        "/*.tar.Z"
        "/*.sh"
        "/*.vcvplugin"
    )
    # This must always be after all CPACK\_\* variables are defined
    include(CPack)
    # cpack_add_component_group("${STONEYVCV_SLUG}"
    #     DISPLAY_NAME "${STONEYVCV_SLUG}"
    #     DESCRIPTION "${STONEYVCV_BRAND} modules for VCV Rack 2."
    #     EXPANDED
    # )
    # cpack_add_component_group(plugin
    #     DISPLAY_NAME "plugin"
    #     PARENT_GROUP "${STONEYVCV_SLUG}"
    # )
    # cpack_add_component_group(development
    #     DISPLAY_NAME "development"
    #     PARENT_GROUP "${STONEYVCV_SLUG}"
    # )
    # cpack_add_component("${STONEYVCV_SLUG}"
    #     DISPLAY_NAME "${STONEYVCV_SLUG} v${STONEYVCV_VERSION}"
    #     DESCRIPTION "${STONEYVCV_BRAND} plugin for VCV Rack 2."
    #     GROUP "${STONEYVCV_SLUG}"
    # )
    cpack_add_component(${STONEYVCV_SLUG}
        DISPLAY_NAME "${STONEYVCV_SLUG}"
        DESCRIPTION "${STONEYVCV_SLUG} v${STONEYVCV_VERSION}."
        # GROUP "plugin"
        # GROUP "${STONEYVCV_SLUG}"
    )
    cpack_add_component(plugin
        DISPLAY_NAME "${STONEYVCV_SLUG} v${STONEYVCV_VERSION}"
        DESCRIPTION "${STONEYVCV_BRAND} plugin for VCV Rack 2."
        # GROUP "plugin"
        # GROUP "${STONEYVCV_SLUG}"
    )
    foreach(MODULE IN LISTS STONEYVCV_MODULES)
        cpack_add_component(${MODULE}
            DISPLAY_NAME "${MODULE} v${STONEYVCV_VERSION}"
            DESCRIPTION "The ${MODULE} module developer files."
            # GROUP "development"
            # GROUP "${STONEYVCV_SLUG}"
        )
    endforeach()
endif()

# Tell the user about the plugin (sanity check)
# vcvrack_get_plugin_json()
# message(STATUS "${VCVRACK_PLUGIN_JSON}")

vcvrack_use_jq(
    COMMAND ".modules | length" "plugin.json"
    OUTPUT_VARIABLE STONEYVCV_MODULES_COUNT
)
string(STRIP "${STONEYVCV_MODULES_COUNT}" STONEYVCV_MODULES_COUNT)
message(DEBUG "number of modules: ${STONEYVCV_MODULES_COUNT}")
