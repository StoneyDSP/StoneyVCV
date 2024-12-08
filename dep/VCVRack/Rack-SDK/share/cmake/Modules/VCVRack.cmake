set(_version 2.5.2)

# add_library(${brand}::${slug}::plugin)
# add_library(${brand}::${slug}::{module})

#[==[Requirements]==]
cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
include(CMakeParseArguments)
include(GNUInstallDirs)
include(CMakeDependentOption)

find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib CONFIG)

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
message(STATUS "Loading VCVRack helper functions...")

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
    set(options EXPORT INSTALL)
    set(args BRAND SLUG VERSION SOVERSION RACK_SDK_VERSION)
    set(list_args SOURCES HEADERS INCLUDE_DIRS)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    # Generate a regex to validate some args with...
    set(namespace_regex "[a-zA-Z_][a-zA-Z0-9_]*")

    # Validate 'SLUG' arg (required)
    if(NOT DEFINED ARG_SLUG)
        message(SEND_ERROR "'vcvrack_add_plugin' requires arg: SLUG")
        return()
    else()
        if(NOT ARG_SLUG MATCHES "${namespace_regex}")
            message(SEND_ERROR "'vcvrack_add_plugin() given invalid arg: SLUG ${ARG_SLUG}'. Please choose a valid C++ identifier.")
            return()
        endif()
        set(slug ${ARG_SLUG})
    endif()

    # Validate 'BRAND' arg (optional)
    if(DEFINED ARG_BRAND)
        if(NOT ARG_BRAND MATCHES "${namespace_regex}")
            message(SEND_ERROR "'vcvrack_add_plugin() given invalid arg: BRAND ${ARG_BRAND}'. Please choose a valid C++ identifier.")
            return()
        endif()
        set(brand ${ARG_BRAND})
    endif()

    # if(NOT DEFINED ARG_EXPORT)
    #     set(ARG_EXPORT TRUE)
    # endif()

    # if(NOT DEFINED ARG_INSTALL)
    #     set(ARG_INSTALL TRUE)
    # endif()

    # Begin target...
    add_library(plugin SHARED) # EXCLUDE_FROM_ALL
    add_library(${slug}::plugin ALIAS plugin)
    if(DEFINED ARG_BRAND)
        add_library(${brand}::${slug}::plugin ALIAS plugin)
    endif()
    target_link_libraries(plugin
        PUBLIC
        unofficial-vcvrack::rack-sdk::lib
    )

    # Minimum C/C++ language requirements
    target_compile_features(plugin PUBLIC cxx_std_11)
    target_compile_features(plugin PUBLIC c_std_11)

    set_target_properties(plugin
        PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_NAME "plugin"
        # Prevent some platforms from putting built lib in 'lib64/' or 'bin/'
        ARCHIVE_OUTPUT_DIRECTORY "lib"
        LIBRARY_OUTPUT_DIRECTORY "lib"
    )

    set_property(
        TARGET plugin
        PROPERTY "plugin_IS_VCVRACK_LIBRARY" TRUE # custom validation
    )

    if(DEFINED ARG_VERSION)
        set_target_properties(plugin
            PROPERTIES
            VERSION "${ARG_VERSION}"
        )
        vcvrack_add_compile_definitions(plugin
            PUBLIC
            "-Dplugin_VERSION=${ARG_VERSION}"
        )
    endif()
    if(DEFINED ARG_SOVERSION)
        set_target_properties(plugin
            PROPERTIES
            SOVERSION "${ARG_SOVERSION}"
        )
        vcvrack_add_compile_definitions(plugin
            PUBLIC
            "-Dplugin_SOVERSION=${ARG_SOVERSION}"
        )
    endif()

    if(DEFINED ARG_INCLUDE_DIRS)
        foreach(include_dir IN LISTS ARG_INCLUDE_DIRS)
            vcvrack_include_directories(plugin ${include_dir})
        endforeach()
    endif()


    if(DEFINED ARG_HEADERS)
        foreach(header IN LISTS ARG_HEADERS)
            vcvrack_add_headers(plugin ${header})
        endforeach()
    endif()

    if(DEFINED ARG_SOURCES)
        foreach(source IN LISTS ARG_SOURCES)
            vcvrack_add_sources(plugin ${source})
        endforeach()
    endif()

    vcvrack_add_sources(plugin ${ARG_UNPARSED_ARGUMENTS})

    vcvrack_add_compile_options(plugin
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

    if(ARG_INSTALL)
        install(TARGETS plugin
            EXPORT PluginExports
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILE_SET plugin_plugin_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

        if(ARG_BRAND)
            set(_ns_prefix ${ARG_BRAND}::)
            set(_dir_prefix ${ARG_BRAND}/)
        endif()

        # install export set
        install(EXPORT PluginExports
            FILE "${slug}-plugin-targets.cmake"
            NAMESPACE ${_ns_prefix}${brand}::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${_dir_prefix}${slug}"
        )
    endif()

    if(ARG_EXPORT)
        # export targets
        if(ARG_BRAND)
            set(_ns_prefix ${ARG_BRAND}::)
            set(_dir_prefix ${ARG_BRAND}/)
        endif()
        export(
            TARGETS plugin
            FILE "share/cmake/${_dir_prefix}${slug}/${slug}-plugin-targets.cmake"
            NAMESPACE ${_ns_prefix}${slug}::
        )
    endif()

endfunction()

#[=============================================================================[
Example usage:

vcvrack_add_module(
    NAME "MyModule"
    SLUG "MySlug"
    BRAND "MyBrand"
    VERSION 2.0.1
    HEADERS "include/MyModule.hpp"
    SOURCES "src/MyModule.cp"
)

Should create a target named 'MyModule', along with some aliases...
]=============================================================================]#
function(vcvrack_add_module name)

    if(NOT TARGET plugin)
        message(SEND_ERROR "'vcvrack_add_module()' called in a project with no corresponding 'vcvrack_add_plugin()'")
        return()
    endif()

    # Parse args...
    set(options EXPORT INSTALL)
    set(args SLUG BRAND VERSION SOVERSION RACK_SDK_VERSION)
    set(list_args SOURCES HEADERS INCLUDE_DIRS)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    # Generate a regex to validate some args with...
    set(namespace_regex "[a-zA-Z_][a-zA-Z0-9_]*")

    # Validate 'SLUG' arg (required)
    if(NOT DEFINED ARG_SLUG)
        message(SEND_ERROR "'vcvrack_add_module' requires arg: SLUG")
        return()
    else()
        if(NOT ARG_SLUG MATCHES "${namespace_regex}")
            message(SEND_ERROR "'vcvrack_add_plugin() given invalid arg: SLUG ${ARG_SLUG}'. Please choose a valid C++ identifier.")
            return()
        endif()
        set(slug ${ARG_SLUG})
    endif()

    # Validate 'BRAND' arg (optional)
    if(DEFINED ARG_BRAND)
        if(NOT ARG_BRAND MATCHES "${namespace_regex}")
            message(SEND_ERROR "'vcvrack_add_plugin() given invalid arg: BRAND ${ARG_BRAND}'. Please choose a valid C++ identifier.")
            return()
        endif()
        set(brand ${ARG_BRAND})
    endif()

    # Validate 'VERSION' arg (optional)

    # if(NOT DEFINED ARG_EXPORT)
    #     set(ARG_EXPORT TRUE)
    # endif()

    # if(NOT DEFINED ARG_INSTALL)
    #     set(ARG_INSTALL TRUE)
    # endif()

    # Begin target...
    add_library(${name} OBJECT)
    add_library(${slug}::${name} ALIAS ${name})
    if(DEFINED ARG_BRAND)
        add_library(${brand}::${slug}::${name} ALIAS ${name})
    #     target_link_libraries(plugin PRIVATE ${brand}::${slug}::${name})
    # else()
    #     target_link_libraries(plugin PRIVATE ${slug}::${name})
    endif()

    vcvrack_add_sources(plugin PRIVATE $<TARGET_OBJECTS:${name}>)
    target_link_libraries(${name}
        PUBLIC
        unofficial-vcvrack::rack-sdk::core
    )
    set_property(
        TARGET ${name}
        PROPERTY "${name}_IS_VCVRACK_LIBRARY" TRUE # custom validation
    )

    if(DEFINED ARG_VERSION)
        set_target_properties(${name}
            PROPERTIES
            VERSION "${ARG_VERSION}"
        )
        vcvrack_add_compile_definitions(${name}
            PUBLIC
            "-D${name}_VERSION=${ARG_VERSION}"
        )
    endif()
    if(DEFINED ARG_SOVERSION)
        set_target_properties(${name}
            PROPERTIES
            SOVERSION "${ARG_SOVERSION}"
        )
        vcvrack_add_compile_definitions(${name}
            PUBLIC
            "-D${name}_SOVERSION=${ARG_SOVERSION}"
        )
    endif()

    vcvrack_add_compile_options(${name}
        PUBLIC
        "-fPIC"
    )

    if(DEFINED ARG_INCLUDE_DIRS)
        foreach(include_dir IN LISTS ARG_INCLUDE_DIRS)
            vcvrack_include_directories(${name} ${include_dir})
        endforeach()
    endif()

    if(DEFINED ARG_HEADERS)
        foreach(header IN LISTS ARG_HEADERS)
            vcvrack_add_headers(${name} ${header})
        endforeach()
    endif()

    if(DEFINED ARG_SOURCES)
        foreach(source IN LISTS ARG_SOURCES)
            vcvrack_add_sources(${name} ${source})
        endforeach()
    endif()

    vcvrack_add_sources(${name} ${ARG_UNPARSED_ARGUMENTS})

    get_target_property(plugin_include_dirs plugin INCLUDE_DIRECTORIES)

    if(DEFINED plugin_include_dirs AND NOT plugin_include_dirs STREQUAL "")
        vcvrack_include_directories(${name} PUBLIC "${plugin_include_dirs}")
    endif()

    if(ARG_INSTALL)
        install(TARGETS ${name}
            EXPORT ${name}Exports
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILE_SET plugin_${name}_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

        if(ARG_BRAND)
            set(_ns_prefix ${ARG_BRAND}::)
            set(_dir_prefix ${ARG_BRAND}/)
        endif()

        # install export set
        install(EXPORT ${name}Exports
            FILE "${slug}-${name}-targets.cmake"
            NAMESPACE ${_ns_prefix}${brand}::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${_dir_prefix}${slug}"
        )
    endif()

    if(ARG_EXPORT)
        # export targets
        if(ARG_BRAND)
            set(_ns_prefix ${ARG_BRAND}::)
        endif()
        export(
            TARGETS ${name}
            FILE "share/cmake/${_ns_prefix}${slug}/${slug}-${name}-targets.cmake"
            NAMESPACE ${_ns_prefix}${slug}::
        )
    endif()

endfunction()

#[=============================================================================[
Include directories in an existing VCVRack library target.

vcvrack_include_directories(<name> [items1...])
vcvrack_include_directories(<name> [BASE_DIRS <dirs>] [items1...])
vcvrack_include_directories(<name> [<INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]])
vcvrack_include_directories(<name> [<INTERFACE|PUBLIC|PRIVATE> [BASE_DIRS [<dirs>...]] [items1...]...)
]=============================================================================]#
function(vcvrack_include_directories name)

    # Check that this is a VCVRack library target
    get_target_property(is_vcvrack_lib ${name} ${name}_IS_VCVRACK_LIBRARY)
    if(NOT TARGET ${name} OR NOT is_vcvrack_lib)
        message(SEND_ERROR "'vcvrack_include_directories()' called on '${name}' which is not an existing VCVRack library")
        return()
    endif()

    set(options)
    set(args)
    set(list_args INTERFACE PRIVATE PUBLIC)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    if(DEFINED ARG_INTERFACE)
        foreach(item IN LISTS ARG_INTERFACE)
            target_include_directories(${name} INTERFACE ${item})
        endforeach()
    endif()

    if(DEFINED ARG_PUBLIC)
        foreach(item IN LISTS ARG_PUBLIC)
            target_include_directories(${name} PUBLIC ${item})
        endforeach()
    endif()

    if(DEFINED ARG_PRIVATE)
        foreach(item IN LISTS ARG_PRIVATE)
            target_include_directories(${name} PRIVATE ${item})
        endforeach()
    endif()

    if(DEFINED ARG_UNPARSED_ARGUMENTS)
        foreach(item IN LISTS ARG_UNPARSED_ARGUMENTS)
            target_include_directories(${name} PUBLIC ${item})
        endforeach()
    endif()

endfunction()

#[=============================================================================[
Add header files to an existing VCVRack library target.

vcvrack_add_headers(<name> [items1...])
vcvrack_add_headers(<name> [BASE_DIRS <dirs>] [items1...])
vcvrack_add_headers(<name> [<INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]])
vcvrack_add_headers(<name> [<INTERFACE|PUBLIC|PRIVATE> [BASE_DIRS [<dirs>...]] [items1...]...)
]=============================================================================]#
function(vcvrack_add_headers name)

    # Check that this is a VCVRack library target
    get_target_property(is_vcvrack_lib ${name} ${name}_IS_VCVRACK_LIBRARY)
    if(NOT TARGET ${name} OR NOT is_vcvrack_lib)
        message(SEND_ERROR "'vcvrack_add_headers()' called on '${name}' which is not an existing VCVRack library")
        return()
    endif()

    set(options)
    set(args BASE_DIR)
    set(list_args INTERFACE PRIVATE PUBLIC)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    if(NOT ARG_BASE_DIR)
        # Default base directory of the passed-in source file(s)
        set(ARG_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
    _vcvrack_normalize_path(ARG_BASE_DIR)
    get_filename_component(ARG_BASE_DIR "${ARG_BASE_DIR}" ABSOLUTE)

    # All remaining unparsed args 'should' be source files for this target, so...
    foreach(input IN LISTS ARG_UNPARSED_ARGUMENTS ARG_INTERFACE ARG_PUBLIC ARG_PRIVATE)

        _vcvrack_normalize_path(input)
        get_filename_component(abs_in "${input}" ABSOLUTE)
        file(RELATIVE_PATH rel_in "${ARG_BASE_DIR}" "${abs_in}")

        if(rel_in MATCHES "^\\.\\.")
            # For now we just error on files that exist outside of the source dir.
            message(SEND_ERROR "Cannot add file '${input}': File must be in a subdirectory of ${ARG_BASE_DIR}")
            return()
        endif()

        get_filename_component(input_filename "${abs_in}" NAME)
        get_filename_component(input_dirname "${abs_in}" DIRECTORY)

        file(RELATIVE_PATH item_relpath "${ARG_BASE_DIR}" "${abs_in}")
        file(RELATIVE_PATH dir_relpath "${ARG_BASE_DIR}" "${input_dirname}")

        configure_file("${item_relpath}" "${item_relpath}")

        # set(rel_file "${ARG_BASE_DIR}/${rel_in}")
        # _vcvrack_normalize_path(rel_file)
        # get_filename_component(source_file "${input}" ABSOLUTE)
        # # If we are here, source file is valid. Add IDE support
        # source_group("${name}" FILES "${source_file}")
    endforeach()

    if(DEFINED ARG_INTERFACE)
        foreach(item IN LISTS ARG_INTERFACE)
            get_filename_component(item_absolute_path "${item}" ABSOLUTE)
            get_filename_component(item_filename "${item}" NAME)
            get_filename_component(item_dirname "${item}" DIRECTORY)
            file(RELATIVE_PATH item_relpath "${ARG_BASE_DIR}" "${item_absolute_path}")
            get_filename_component(dir_relpath "${item_relpath}" DIRECTORY)
            target_sources(${name}
                INTERFACE
                FILE_SET "plugin_${name}_INTERFACE_HEADERS"
                TYPE HEADERS
                BASE_DIRS
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}>
                $<INSTALL_INTERFACE:${dir_relpath}>
                FILES
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}/${item_filename}>
                $<INSTALL_INTERFACE:${dir_relpath}/${item_filename}>
            )
        endforeach()
    endif()

    if(DEFINED ARG_PRIVATE)
        foreach(item IN LISTS ARG_PRIVATE)
            get_filename_component(item_absolute_path "${item}" ABSOLUTE)
            get_filename_component(item_filename "${item}" NAME)
            get_filename_component(item_dirname "${item}" DIRECTORY)
            file(RELATIVE_PATH item_relpath "${ARG_BASE_DIR}" "${item_absolute_path}")
            get_filename_component(dir_relpath "${item_relpath}" DIRECTORY)
            target_sources(${name}
                PRIVATE
                FILE_SET "plugin_${name}_PRIVATE_HEADERS"
                TYPE HEADERS
                BASE_DIRS
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}>
                $<INSTALL_INTERFACE:${dir_relpath}>
                FILES
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}/${item_filename}>
                $<INSTALL_INTERFACE:${dir_relpath}/${item_filename}>
            )
        endforeach()
    endif()

    if(DEFINED ARG_PUBLIC)
        foreach(item IN LISTS ARG_PUBLIC)
            get_filename_component(item_absolute_path "${item}" ABSOLUTE)
            get_filename_component(item_filename "${item}" NAME)
            get_filename_component(item_dirname "${item}" DIRECTORY)
            file(RELATIVE_PATH item_relpath "${ARG_BASE_DIR}" "${item_absolute_path}")
            get_filename_component(dir_relpath "${item_relpath}" DIRECTORY)
            target_sources(${name}
                PUBLIC
                FILE_SET "plugin_${name}_PUBLIC_HEADERS"
                TYPE HEADERS
                BASE_DIRS
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}>
                $<INSTALL_INTERFACE:${dir_relpath}>
                FILES
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}/${item_filename}>
                $<INSTALL_INTERFACE:${dir_relpath}/${item_filename}>
            )
        endforeach()
    endif()

    if(DEFINED ARG_UNPARSED_ARGUMENTS)
        foreach(item IN LISTS ARG_UNPARSED_ARGUMENTS)
            get_filename_component(item_absolute_path "${item}" ABSOLUTE)
            get_filename_component(item_filename "${item}" NAME)
            get_filename_component(item_dirname "${item}" DIRECTORY)
            file(RELATIVE_PATH item_relpath "${ARG_BASE_DIR}" "${item_absolute_path}")
            get_filename_component(dir_relpath "${item_relpath}" DIRECTORY)
            target_sources(${name}
                PUBLIC
                FILE_SET "plugin_${name}_PUBLIC_HEADERS"
                TYPE HEADERS
                BASE_DIRS
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}>
                $<INSTALL_INTERFACE:${dir_relpath}>
                FILES
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${dir_relpath}/${item_filename}>
                $<INSTALL_INTERFACE:${dir_relpath}/${item_filename}>
            )
        endforeach()
    endif()

endfunction()

#[=============================================================================[
Add source files to an existing VCVRack library target.

vcvrack_add_sources(<name> [items1...])
vcvrack_add_sources(<name> [BASE_DIRS <dirs>] [items1...])
vcvrack_add_sources(<name> [<INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]])
vcvrack_add_sources(<name> [<INTERFACE|PUBLIC|PRIVATE> [BASE_DIRS [<dirs>...]] [items1...]...)
]=============================================================================]#
function(vcvrack_add_sources name)

    # Check that this is a VCVRack library target
    get_target_property(is_vcvrack_lib ${name} ${name}_IS_VCVRACK_LIBRARY)
    if(NOT TARGET ${name} OR NOT is_vcvrack_lib)
        message(SEND_ERROR "'vcvrack_add_sources()' called on '${name}' which is not an existing VCVRack library")
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
    _vcvrack_normalize_path(ARG_BASE_DIRS)
    get_filename_component(ARG_BASE_DIRS "${ARG_BASE_DIRS}" ABSOLUTE)

    # All remaining unparsed args 'should' be source files for this target, so...
    foreach(input IN LISTS ARG_UNPARSED_ARGUMENTS ARG_PUBLIC ARG_PRIVATE ARG_INTERFACE)

        _vcvrack_normalize_path(input)
        get_filename_component(abs_in "${input}" ABSOLUTE)
        file(RELATIVE_PATH relpath "${ARG_BASE_DIRS}" "${abs_in}")
        if(relpath MATCHES "^\\.\\.")
            # For now we just error on files that exist outside of the source dir.
            message(SEND_ERROR "Cannot add file '${input}': File must be in a subdirectory of ${ARG_BASE_DIRS}")
            return()
        endif()

        # set(rel_file "${ARG_BASE_DIRS}/${relpath}")
        # _vcvrack_normalize_path(rel_file)
        # get_filename_component(source_file "${input}" ABSOLUTE)
        # # If we are here, source file is valid. Add IDE support
        # source_group("${name}" FILES "${source_file}")

    endforeach()

    if(DEFINED ARG_INTERFACE)
        foreach(item IN LISTS ARG_INTERFACE)
            target_sources(${name} INTERFACE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PRIVATE)
        foreach(item IN LISTS ARG_PRIVATE)
            target_sources(${name} PRIVATE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PUBLIC)
        foreach(item IN LISTS ARG_PUBLIC)
            target_sources(${name} PUBLIC "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_UNPARSED_ARGUMENTS)
        foreach(item IN LISTS ARG_UNPARSED_ARGUMENTS)
            target_sources(${name} PRIVATE "${item}")
        endforeach()
    endif()

endfunction()

#[=============================================================================[
Add pre-processor definitions to an existing VCVRack library target.

vcvrack_add_compile_definitions(<name> [items1...])
vcvrack_add_compile_definitions(<name> <INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
]=============================================================================]#
function(vcvrack_add_compile_definitions name)

    # Check that this is a VCVRack library target
    get_target_property(is_vcvrack_lib ${name} ${name}_IS_VCVRACK_LIBRARY)
    if(NOT TARGET ${name} OR NOT is_vcvrack_lib)
        message(SEND_ERROR "'vcvrack_add_compile_definitions()' called on '${name}' which is not an existing VCVRack library")
        return()
    endif()

    set(options)
    set(args)
    set(list_args INTERFACE PRIVATE PUBLIC)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    if(DEFINED ARG_INTERFACE)
        foreach(item IN LISTS ARG_INTERFACE)
            target_compile_definitions(${name} INTERFACE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PRIVATE)
        foreach(item IN LISTS ARG_PRIVATE)
            target_compile_definitions(${name} PRIVATE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PUBLIC)
        foreach(item IN LISTS ARG_PUBLIC)
            target_compile_definitions(${name} PUBLIC "${item}")
        endforeach()
    endif()

    foreach(input IN LISTS ARG_UNPARSED_ARGUMENTS)
        target_compile_definitions(${name} "${item}")
    endforeach()

endfunction()

#[=============================================================================[
Add compiler options to an existing VCVRack library target.

vcvrack_add_compile_options(<name> [items1...])
vcvrack_add_compile_options(<name> <INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
]=============================================================================]#
function(vcvrack_add_compile_options name)

    # Check that this is a VCVRack library target
    get_target_property(is_vcvrack_lib ${name} ${name}_IS_VCVRACK_LIBRARY)
    if(NOT TARGET ${name} OR NOT is_vcvrack_lib)
        message(SEND_ERROR "'vcvrack_add_compile_options()' called on '${name}' which is not an existing VCVRack library")
        return()
    endif()

    set(options)
    set(args)
    set(list_args INTERFACE PRIVATE PUBLIC)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    if(DEFINED ARG_INTERFACE)
        foreach(item IN LISTS ARG_INTERFACE)
            target_compile_options(${name} INTERFACE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PRIVATE)
        foreach(item IN LISTS ARG_PRIVATE)
            target_compile_options(${name} PRIVATE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PUBLIC)
        foreach(item IN LISTS ARG_PUBLIC)
            target_compile_options(${name} PUBLIC "${item}")
        endforeach()
    endif()

    foreach(input IN LISTS ARG_UNPARSED_ARGUMENTS)
        target_compile_options(${name} "${item}")
    endforeach()

endfunction()

#[=============================================================================[
Add linker options to an existing VCVRack library target.

vcvrack_add_link_options(<name> [items1...])
vcvrack_add_link_options(<name> <INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
]=============================================================================]#
function(vcvrack_add_link_options name)

    # Check that this is a VCVRack library target
    get_target_property(is_vcvrack_lib ${name} ${name}_IS_VCVRACK_LIBRARY)
    if(NOT TARGET ${name} OR NOT is_vcvrack_lib)
        message(SEND_ERROR "'vcvrack_add_link_options()' called on '${name}' which is not an existing VCVRack library")
        return()
    endif()

    set(options)
    set(args)
    set(list_args INTERFACE PRIVATE PUBLIC)
    cmake_parse_arguments(ARG "${options}" "${args}" "${list_args}" "${ARGN}")

    if(DEFINED ARG_INTERFACE)
        foreach(item IN LISTS ARG_INTERFACE)
            target_link_options(${name} INTERFACE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PRIVATE)
        foreach(item IN LISTS ARG_PRIVATE)
            target_link_options(${name} PRIVATE "${item}")
        endforeach()
    endif()

    if(DEFINED ARG_PUBLIC)
        foreach(item IN LISTS ARG_PUBLIC)
            target_link_options(${name} PUBLIC "${item}")
        endforeach()
    endif()

    foreach(input IN LISTS ARG_UNPARSED_ARGUMENTS)
        target_link_options(${name} "${item}")
    endforeach()

endfunction()

#[==[Cleanup]==]

unset(_version)
