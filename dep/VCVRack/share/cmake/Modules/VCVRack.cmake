cmake_minimum_required(VERSION 3.14...3.29 FATAL_ERROR)

set(_version 2.5.2)

## Required...
if(NOT DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
    message(FATAL_ERROR "You need to set $RACK_DIR")
endif()

## Take RACK_DIR from env, if not passed as -DRACK_DIR=...
if(DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
    set(RACK_DIR "$ENV{RACK_DIR}" CACHE STRING "" FORCE)
endif()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]#
function(_vcv_rack_normalize_path var)
    set(path "${${var}}")
    file(TO_CMAKE_PATH "${path}" path)
    while(path MATCHES "//")
        string(REPLACE "//" "/" path "${path}")
    endwhile()
    string(REGEX REPLACE "/+$" "" path "${path}")
    set("${var}" "${path}" PARENT_SCOPE)
endfunction()

function(vcv_rack_get_plugin_json_slug)
    execute_process(
      COMMAND "jq" "-r" ".slug" "plugin.json"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE _VCV_RACK_PLUGIN_JSON_SLUG
    )
    string(REGEX REPLACE "[\r\n\"]" "" _VCV_RACK_PLUGIN_JSON_SLUG "${_VCV_RACK_PLUGIN_JSON_SLUG}")
    set(_VCV_RACK_PLUGIN_JSON_SLUG ${_VCV_RACK_PLUGIN_JSON_SLUG} PARENT_SCOPE)
endfunction()

function(vcv_rack_get_plugin_json_version)
    execute_process(
      COMMAND "jq" "-r" ".version" "plugin.json"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE _VCV_RACK_PLUGIN_JSON_VERSION
    )
    string(REGEX REPLACE "[\r\n\"]" "" _VCV_RACK_PLUGIN_JSON_VERSION "${_VCV_RACK_PLUGIN_JSON_VERSION}")
    set(_VCV_RACK_PLUGIN_JSON_VERSION ${_VCV_RACK_PLUGIN_JSON_VERSION} PARENT_SCOPE)
endfunction()

if(_VCV_RACK_PLUGIN_JSON_SLUG STREQUAL "")
    message(FATAL_ERROR "plugin.json#slug is not defined")
endif()

if(_VCV_RACK_PLUGIN_JSON_VERSION STREQUAL "")
    message(FATAL_ERROR "plugin.json#version is not defined")
endif()

#[=============================================================================[
Exposes a user-side helper function for creating a VCV Rack Plugin library,
linked to the Rack SDK library.

vcv_rack_create_plugin(<name> [<sources>])
vcv_rack_create_plugin(<name> [ALIAS <alias>] [NAMESPACE <namespace>] [VCV_RACK_SDK_VERSION <version>] [<sources>])

(This should wrap the CMakeLists.txt-side requirements for building a VCV Rack Plugin)
]=============================================================================]#

function(vcv_rack_create_plugin name)
        # Avoid duplicate target names
        if(TARGET ${name})
            message(SEND_ERROR "'vcv_rack_create_plugin()' given target '${name}' which already exists. Please choose a unique name for this target.")
        return()
    endif()

    set(options)
    set(args ALIAS NAMESPACE VCV_RACK_SDK_VERSION)
    set(list_args)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    # Generate the identifier for the resource library's namespace
    set(ns_re "[a-zA-Z_][a-zA-Z0-9_]*")

    if(NOT DEFINED ARG_NAMESPACE)
        # Check that the library name is also a valid namespace
        if(NOT name MATCHES "${ns_re}")
            message(SEND_ERROR "Library name is not a valid namespace. Specify the NAMESPACE argument")
            return()
        endif()
        set(ARG_NAMESPACE "${name}")
    else()
        if(NOT ARG_NAMESPACE MATCHES "${ns_re}")
            message(SEND_ERROR "NAMESPACE for ${name} is not a valid C++ namespace identifier (${ARG_NAMESPACE})")
            return()
        endif()
    endif()

    # TODO: This needs more/better validation...
    if(DEFINED ARG_VCV_RACK_SDK_VERSION AND (ARG_VCV_RACK_SDK_VERSION LESS_EQUAL 0))
        message(SEND_ERROR "VCV_RACK_SDK_VERSION for ${name} is not a valid Integer number (${VCV_RACK_SDK_VERSION})")
        return()
    endif()

    if(NOT DEFINED ARG_VCV_RACK_SDK_VERSION)
        if(NOT DEFINED VCV_RACK_SDK_VERSION)
            # default NAPI version to use if none specified
            set(VCV_RACK_SDK_VERSION 8)
        endif()
        set(ARG_VCV_RACK_SDK_VERSION ${VCV_RACK_SDK_VERSION})
    endif()

    if(ARG_ALIAS)
        set(name_alt "${ARG_ALIAS}")
    else()
        set(name_alt "${ARG_NAMESPACE}")
    endif()

    if(VERBOSE)
        message(STATUS "Configuring VCV Rack Plugin: ${name}")
    endif()

    # Begin a new VCV Rack Plugin target

    add_library(${name} SHARED)
    add_library(${name_alt}::${name} ALIAS ${name})

    # target_link_libraries(${name} PRIVATE vcv-rack::rack-sdk)

    set_property(
        TARGET ${name}
        PROPERTY "${name}_IS_VCV_RACK_PLUGIN_LIBRARY" TRUE # Custom property
    )

    set_target_properties(${name}
        PROPERTIES

        LIBRARY_OUTPUT_NAME "${name}"
        # PREFIX ""
        # SUFFIX ".so"

        ARCHIVE_OUTPUT_DIRECTORY "${CMAKEJS_BINARY_DIR}/lib" # Actually we might not need to enforce an opinion here!
        LIBRARY_OUTPUT_DIRECTORY "${CMAKEJS_BINARY_DIR}/lib" # Instead, we call 'cmakejs_create_addon_bindings()'
        RUNTIME_OUTPUT_DIRECTORY "${CMAKEJS_BINARY_DIR}/bin" # on this target, and the user can just 'require()' that file!

        # # Conventional C++-style debug settings might be useful to have...
        # LIBRARY_OUTPUT_NAME_DEBUG "d${name}"
        # ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKEJS_BINARY_DIR}/lib/Debug"
        # LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKEJS_BINARY_DIR}/lib/Debug"
        # RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKEJS_BINARY_DIR}/bin/Debug"
    )

    vcv_rack_plugin_add_sources(${name} ${ARG_UNPARSED_ARGUMENTS})

endfunction()

#[=============================================================================[
Add source files to an existing Napi Addon target.

vcv_rack_plugin_add_sources(<name> [items1...])
vcv_rack_plugin_add_sources(<name> [BASE_DIRS <dirs>] [items1...])
vcv_rack_plugin_add_sources(<name> [<INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]])
vcv_rack_plugin_add_sources(<name> [<INTERFACE|PUBLIC|PRIVATE> [BASE_DIRS [<dirs>...]] [items1...]...)
]=============================================================================]#
function(vcv_rack_plugin_add_sources name)
    # Check that this is a VCV Rack Plugin target
    get_target_property(is_plugin_lib ${name} ${name}_IS_VCV_RACK_PLUGIN_LIBRARY)
    if(NOT TARGET ${name} OR NOT is_plugin_lib)
        message(SEND_ERROR "'vcv_rack_plugin_add_sources()' called on '${name}' which is not an existing napi addon library")
        return()
    endif()

    set(options)
    set(args BASE_DIRS)
    set(list_args INTERFACE PRIVATE PUBLIC)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    if(NOT ARG_BASE_DIRS)
        # Default base directory of the passed-in source file(s)
        set(ARG_BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
    _vcv_rack_normalize_path(ARG_BASE_DIRS)
    get_filename_component(ARG_BASE_DIRS "${ARG_BASE_DIRS}" ABSOLUTE)

    # All remaining unparsed args 'should' be source files for this target, so...
    foreach(input IN LISTS ARG_UNPARSED_ARGUMENTS)

        _vcv_rack_normalize_path(input)
        get_filename_component(abs_in "${input}" ABSOLUTE)
        file(RELATIVE_PATH relpath "${ARG_BASE_DIRS}" "${abs_in}")
        if(relpath MATCHES "^\\.\\.")
            # For now we just error on files that exist outside of the source dir.
            message(SEND_ERROR "Cannot add file '${input}': File must be in a subdirectory of ${ARG_BASE_DIRS}")
            return()
        endif()

        set(rel_file "${ARG_BASE_DIRS}/${relpath}")
        _vcv_rack_normalize_path(rel_file)
        get_filename_component(source_file "${input}" ABSOLUTE)
        # If we are here, source file is valid. Add IDE support
        source_group("${name}" FILES "${source_file}")

        if(DEFINED ARG_INTERFACE)
            foreach(item IN LISTS ARG_INTERFACE)
                target_sources(${name} INTERFACE "${source_file}")
            endforeach()
        endif()

        if(DEFINED ARG_PRIVATE)
            foreach(item IN LISTS ARG_PRIVATE)
                target_sources(${name} PRIVATE "${source_file}")
            endforeach()
        endif()

        if(DEFINED ARG_PUBLIC)
            foreach(item IN LISTS ARG_PUBLIC)
                target_sources(${name} PUBLIC "${source_file}")
            endforeach()
        endif()

        foreach(input IN LISTS ARG_UNPARSED_ARGUMENTS)
            target_sources(${name} PRIVATE "${source_file}")
        endforeach()

    endforeach()

endfunction()

##

set(_VCVRACK_SCRIPT "${CMAKE_CURRENT_LIST_FILE}" CACHE INTERNAL "Path to current 'VCVRack.cmake' script")

set(VCVRACK_TARGETS)

#[==[Rack SDK]==]
add_library(RackSDK SHARED IMPORTED GLOBAL)
add_library(VCVRack::RackSDK ALIAS RackSDK)

set_target_properties(RackSDK PROPERTIES VERSION 2.5.2)
set_target_properties(RackSDK PROPERTIES SOVERSION 2.5.2)
set_target_properties(RackSDK PROPERTIES INTERFACE_VCVRACK_RACKSDK_MAJOR_VERSION 2)
set(VCVRACK_RACK_LIB_FILE_EXTENSION)
if(APPLE)
    set(VCVRACK_RACK_LIB_FILE_EXTENSION ".dylib")
elseif(UNIX AND NOT APPLE) # Linux
    set(VCVRACK_RACK_LIB_FILE_EXTENSION ".so")
endif()
if(WIN_32)
    set(VCVRACK_RACK_LIB_FILE_EXTENSION ".dll.a")
endif()
set_property(
    TARGET RackSDK
    PROPERTY
    IMPORTED_LOCATION "${RACK_DIR}/libRack${VCVRACK_RACK_LIB_FILE_EXTENSION}"
)

target_include_directories(RackSDK
    INTERFACE
        "${RACK_DIR}/include"
        "${RACK_DIR}/dep/include"
)

## Require C++11.
target_compile_features(RackSDK INTERFACE cxx_std_11)
target_compile_features(RackSDK INTERFACE c_std_11)

if(APPLE)
    target_link_options(RackSDK
        INTERFACE
            "-undefined dynamic_lookup"
    )
endif()
if(UNIX AND NOT APPLE)
    target_link_options(RackSDK
        INTERFACE
            ## This prevents static variables in the DSO (dynamic shared
            ## object) from being preserved after dlclose().
            "-fno-gnu-unique"
            "-static-libstdc++" "-static-libgcc"
    )
endif()
if(WIN32)
    target_link_options(RackSDK
        INTERFACE
            "-municode"
    )
endif()
set_target_properties(RackSDK
    PROPERTIES
    LINKER_LANGUAGE CXX
)

list(APPEND VCVRACK_TARGETS RackSDK)

#[==[Rack]==]
add_executable(Rack IMPORTED GLOBAL)
add_executable(VCVRack::Rack ALIAS Rack)

set_target_properties(Rack PROPERTIES VERSION 2.5.2)
set_target_properties(Rack PROPERTIES SOVERSION 2.5.2)
set_target_properties(Rack PROPERTIES INTERFACE_VCVRACK_RACK_MAJOR_VERSION 2)
set_property(
    TARGET Rack
    PROPERTY
    IMPORTED_LOCATION "${RACK_DIR}/Rack"
)
set_property(
    TARGET Rack
    PROPERTY
    ENABLE_EXPORTS TRUE
)
set_target_properties(Rack
    PROPERTIES
        PREFIX ""
        SUFFIX ""
        LIBRARY_OUTPUT_NAME "Rack"
        RUNTIME_OUTPUT_DIRECTORY "${RACK_DIR}"
)
target_link_libraries(Rack
    INTERFACE
        VCVRack::RackSDK
)
set_target_properties(Rack
    PROPERTIES
    LINKER_LANGUAGE CXX
)

list(APPEND VCVRACK_TARGETS Rack)

##

# export (
#   TARGETS ${VCVRACK_TARGETS}
#   FILE "share/cmake/VCVRackTargets.cmake"
#   NAMESPACE VCVRack::
# )

include (CMakePackageConfigHelpers)
file (WRITE "${CMAKE_CURRENT_BINARY_DIR}/VCVRackConfig.cmake.in" [==[
@PACKAGE_INIT@

include (${CMAKE_CURRENT_LIST_DIR}/VCVRackTargets.cmake)

check_required_components (VCVRack)

# Tell the user what to do
message(STATUS "Linking with VCV Rack SDK")
]==])

# create cmake config file
configure_package_config_file (
    "${CMAKE_CURRENT_BINARY_DIR}/VCVRackConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/VCVRackConfig.cmake"
  INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/VCVRack"
)
# generate the version file for the cmake config file
write_basic_package_version_file (
	"${CMAKE_CURRENT_BINARY_DIR}/share/cmake/VCVRackConfigVersion.cmake"
	VERSION ${VCVRACK_VERSION_MAJOR}.${VCVRACK_VERSION_MINOR}.${VCVRACK_VERSION_TWEAK}
	COMPATIBILITY AnyNewerVersion
)
## pass our module along
file(COPY "${_VCVRACK_SCRIPT}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/share/cmake")

# install config files
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/VCVRackConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/VCVRackConfigVersion.cmake"
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/VCVRack"
)

unset(_version)
