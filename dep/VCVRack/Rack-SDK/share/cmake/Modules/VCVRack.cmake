set(_version 2.5.2)

# add_library(${brand}::${slug}::plugin)
# add_library(${brand}::${slug}::{module})

#[==[Requirements]==]
cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
include(CMakeParseArguments)
include(GNUInstallDirs)
include(CMakeDependentOption)

#[==[Include Guard]==]

if(COMMAND vcvrack_add_sources)
    if(NOT DEFINED _VCVRACK_API_VERSION OR NOT (_version STREQUAL _VCVRACK_API_VERSION))
        message(WARNING "More than one 'VCVRack.cmake' version has been included in this project.")
    endif()
    # 'VCVRack.cmake' has already been included! Don't do anything
    return()
endif()

set(_VCVRACK_API_VERSION "${_version}" CACHE INTERNAL "Current 'VCVRack.cmake' version. Used for checking for conflicts")

set(_VCVRACK_API_SCRIPT "${CMAKE_CURRENT_LIST_FILE}" CACHE INTERNAL "Path to current 'VCVRack.cmake' script")

#[==[Begin Script]==]

message (STATUS "VCVRack.cmake v${_VCVRACK_API_VERSION}")

function(_vcvrack_function_template)
    # Parse args...
    set(options)
    set(args)
    set(list_args)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")
endfunction()

#[=============================================================================[
Internal helper
]=============================================================================]#
function(_vcvrack_trim_newlines input)
    string(REGEX REPLACE "[\r\n\"]" "" input "${input}")
    set(input "${input}" PARENT_SCOPE)
endfunction()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]#
function(_vcvrack_normalize_path var)
    set(path "${${var}}")
    file(TO_CMAKE_PATH "${path}" path)
    while(path MATCHES "//")
        string(REPLACE "//" "/" path "${path}")
    endwhile()
    string(REGEX REPLACE "/+$" "" path "${path}")
    set("${var}" "${path}" PARENT_SCOPE)
endfunction()

#[=============================================================================[
Provides JQ_EXECUTABLE
]=============================================================================]#
function(vcvrack_find_jq)
    find_program(JQ_EXECUTABLE
        NAMES "jq" "jq.exe"
        PATHS "$ENV{PATH}" "$ENV{ProgramFiles}/cmake-js"
        DOC "jq command line tool for JSON"
        REQUIRED
    )
    if (NOT JQ_EXECUTABLE)
        message(FATAL_ERROR "jq not found! Please install jq and try again.")
        return()
    endif(NOT JQ_EXECUTABLE)
    _vcvrack_normalize_path(JQ_EXECUTABLE)
    _vcvrack_trim_newlines(JQ_EXECUTABLE)
    set(JQ_EXECUTABLE "${JQ_EXECUTABLE}" PARENT_SCOPE)
    message(STATUS "found jq: ${JQ_EXECUTABLE}")
endfunction()

function(vcvrack_use_jq)
    if(NOT DEFINED JQ_EXECUTABLE)
        vcvrack_find_jq()
    endif()
    # Parse args...
    set(options)
    set(args WORKING_DIRECTORY OUTPUT_VARIABLE)
    set(list_args COMMAND)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")
    if(NOT DEFINED ARG_COMMAND)
        message(SEND_ERROR "jq expects some arguments... try 'jq --help'")
    endif()
    if(NOT DEFINED ARG_OUTPUT_VARIABLE)
        message(SEND_ERROR "You need to pass in an OUTPUT_VARIABLE argument to use this function")
    endif()
    if(NOT DEFINED ARG_WORKING_DIRECTORY)
        set(ARG_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    endif()
    execute_process(
        COMMAND ${JQ_EXECUTABLE} ${ARG_COMMAND}
        WORKING_DIRECTORY ${ARG_WORKING_DIRECTORY}
        OUTPUT_VARIABLE JQ_OUTPUT
    )
    string(REGEX REPLACE "[\r\n\"]" "" JQ_OUTPUT "${JQ_OUTPUT}")
    message(DEBUG "JQ_OUTPUT: ${JQ_OUTPUT}")
    set(${ARG_OUTPUT_VARIABLE} "${JQ_OUTPUT}" PARENT_SCOPE)
endfunction()

function(vcvrack_get_plugin_json)
    vcvrack_use_jq(
        COMMAND -r . plugin.json
        OUTPUT_VARIABLE VCVRACK_PLUGIN_JSON
    )
    set(VCVRACK_PLUGIN_JSON "${VCVRACK_PLUGIN_JSON}" PARENT_SCOPE)
endfunction()

function(vcvrack_get_plugin_slug)
    vcvrack_use_jq(
        COMMAND -r .slug plugin.json
        OUTPUT_VARIABLE VCVRACK_PLUGIN_SLUG
    )
    set(VCVRACK_PLUGIN_SLUG "${VCVRACK_PLUGIN_SLUG}" PARENT_SCOPE)
endfunction()

function(vcvrack_get_plugin_version)
    vcvrack_use_jq(
        COMMAND -r .version plugin.json
        OUTPUT_VARIABLE VCVRACK_PLUGIN_VERSION
    )
    set(VCVRACK_PLUGIN_VERSION "${VCVRACK_PLUGIN_VERSION}" PARENT_SCOPE)
endfunction()

function(vcvrack_get_plugin_modules)
    vcvrack_use_jq(
        COMMAND -r .modules plugin.json
        OUTPUT_VARIABLE VCVRACK_PLUGIN_MODULES
    )
    set(VCVRACK_PLUGIN_MODULES "${VCVRACK_PLUGIN_MODULES}" PARENT_SCOPE)
endfunction()

#[==[
SKETCHES

Basically, we want to set up the following pattern;

add_library(${brand}::${slug}::plugin SHARED)
add_library(${brand}::${slug}::{module} OBJECT)
target_link_library(plugin PRIVATE ${brand}::${slug}::{module})

NOTE: we don't actually need to be opinionated about the name of the 'plugin'
target itself (the user can name it as they wish), since
we will set_target_properties(LIBRARY_OUTPUT_NAME "plugin")

This opens up the interesting idea about building more than one plugin
under one project call... but we should set 'plugin' as the default name
incase the user doesn't specify a custom one.

Nonetheless, we *might* hard-code the name for the time being, to avoid
unneccessary bugs...

NOTE: the actual call will be 'add_library(<name> <TYPE>)', followed by
'add_library(<brand::name> ALIAS <name>)', then
'add_library(<brand::slug::name> ALIAS <name>)'.

NOTE: 'plugin.json' doesn't require 'brand', so if the user doesn't pass in a
`BRAND` argument to this function, we can option out
the final 'add_library(<brand::slug::name> ALIAS <name>)' alias library.

NOTE: we should set a custom property on these targets to identify them as
consumers of the VCV Rack API. Then, we use some aliased CMake commands like
`vcvrack_add_sources`.... the custom property will allow us to do some helpful
input validation (and provide helpful error messages) for passed-in files...
]==]
message(STATUS "")

#[=============================================================================[
Example usage:

vcvrack_add_plugin(
    NAME "MyPlugin"
    SLUG "MySlug"
    BRAND "MyBrand"
    VERSION 2.0.1
    HEADERS "include/plugin.hpp" "include/componentLibrary.hpp"
    SOURCES "src/plugin.cp"
)

Should create a target named 'plugin', along with some aliases...

May only be used once per project (unless we can do better somehow)
]=============================================================================]#
function(vcvrack_add_plugin)

    # Parse args...
    set(options)
    set(args BRAND SLUG VERSION)
    set(list_args)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    #
    if(NOT DEFINED ARG_SLUG)
        message(SEND_ERROR "'vcvrack_add_plugin' requires argument: SLUG")
    endif()
    set(slug "${ARG_SLUG}")

    #
    if(DEFINED ARG_BRAND)
        set(brand "${ARG_BRAND}")
    endif()

    # Begin target...
    add_library(plugin SHARED)
    add_library(${slug}::plugin ALIAS plugin)
    if(DEFINED ARG_BRAND)
        add_library(${brand}::${slug}::plugin ALIAS plugin)
    endif()
    #
endfunction()

function(vcvrack_add_module name)
    # Parse args...
    set(options)
    set(args SLUG BRAND VERSION)
    set(list_args)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")
    # Validate 'SLUG' arg (required)
    # Validate 'BRAND' arg (optional)
    # Validate 'VERSION' arg (optional)
    # Begin target...
    add_library(${name} OBJECT)
endfunction()

#[==[Cleanup]==]

unset(_version)
