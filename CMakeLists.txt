# # CMake Support...
cmake_minimum_required(VERSION 3.14...3.29 FATAL_ERROR)

# # # Required...
# if(NOT DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
# message(FATAL_ERROR "You need to set $RACK_DIR")
# endif()

# # Recommended...
if(NOT DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED VCPKG_ROOT)
    message(WARNING "You may need to set $VCPKG_ROOT to acquire Catch2...")
endif()

# # # Take RACK_DIR from env, if not passed as -DRACK_DIR=...
# if(DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
# set(RACK_DIR "$ENV{RACK_DIR}" CACHE STRING "" FORCE)
# endif()

# # Take VCPKG_ROOT from env, if not passed as -DVCPKG_ROOT=...
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT "$ENV{VCPKG_ROOT}" CACHE STRING "" FORCE)
endif()

# # Set CMAKE_TOOLCHAIN_FILE to vcpkg, if not passed as -DCMAKE_TOOLCHAIN_FILE=...
if(DEFINED VCPKG_ROOT AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

# # Locate StoneyDSP...
set(STONEYDSP_DIR "${CMAKE_CURRENT_LIST_DIR}/dep/StoneyDSP")

# # Locate CMake Modules...
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules"
)

#[==[STONEYVCV]==]
project(STONEYVCV VERSION 2.1.0.0)

#[==[Set StoneyDSP Library ABI version to use]==]
set(STONEYDSP_VERSION_MAJOR 0 CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_MINOR 1 CACHE STRING "" FORCE)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-municode" _cxx_supports_municode)

# # Put these in the correct order of their dependencies on eachother internally
# # to save tears
find_package(StoneyDSP 0.0 REQUIRED COMPONENTS Core SIMD DSP CONFIG)

# # Put these in the correct order of their dependencies on eachother internally
# # to save tears
find_package(rack 2.5.2 REQUIRED COMPONENTS dep sdk lib CONFIG)

enable_language(C)
enable_language(CXX)

set(PLUGIN_HPP "plugin.hpp")
set(PLUGIN_CPP "plugin.cpp")

if(WIN32)
    set(PLUGIN_LIB_FILE_EXTENSION ".dll")
elseif(UNIX AND NOT APPLE)
    set(PLUGIN_LIB_FILE_EXTENSION ".dylib")
else() # LINUX
    set(PLUGIN_LIB_FILE_EXTENSION ".so")
endif()

set(PLUGIN_LIB "plugin${PLUGIN_LIB_FILE_EXTENSION}")

configure_file("include/${PLUGIN_HPP}" "include/${PLUGIN_HPP}")

# configure_file("include/VCA.hpp" "include/VCA.hpp")
# configure_file("include/VCO.hpp" "include/VCO.hpp")
set(STONEYVCV_TARGETS)

#[==[StoneyVCV]==]
add_library(StoneyVCV SHARED EXCLUDE_FROM_ALL)
add_library(StoneyDSP::StoneyVCV ALIAS StoneyVCV)

set_target_properties(StoneyVCV PROPERTIES VERSION 2.1.0)
set_target_properties(StoneyVCV PROPERTIES SOVERSION 2.1.0)

target_include_directories(StoneyVCV
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_sources(StoneyVCV
    PUBLIC
    FILE_SET stoneyvcv_PUBLIC_HEADERS
    TYPE HEADERS
    BASE_DIRS
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    FILES
    #[==[include/plugin.hpp]==]
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
    PUBLIC
    rack::dep
    rack::sdk
    rack::lib
    StoneyDSP::Core
    StoneyDSP::SIMD
    StoneyDSP::DSP
)

if(UNIX)
    if(APPLE)
        target_link_options(StoneyVCV
            PUBLIC
            "-undefined dynamic_lookup"
        )
    else() # If we're Linux... (assumes GCC, as per Rack)
        target_compile_options(StoneyVCV
            PUBLIC

            # # This prevents static variables in the DSO (dynamic shared
            # # object) from being preserved after dlclose().
            "-fno-gnu-unique"
        )
        target_link_options(StoneyVCV
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
    endif() # APPLE / LINUX
endif()

if(WIN32)
    target_link_options(StoneyVCV
        PUBLIC
        "-static-libstdc++"
    )
endif()

set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "" FORCE)
set(CMAKE_AUTOGEN_VERBOSE TRUE CACHE BOOL "" FORCE)

#[==[plugin]==]
add_custom_target(plugin ALL
    COMMAND "make"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    BYPRODUCTS
    "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
    SOURCES
    "${PROJECT_SOURCE_DIR}/src/${PLUGIN_CPP}"
    "${PROJECT_BINARY_DIR}/include/${PLUGIN_HPP}"
    JOB_SERVER_AWARE TRUE
    DEPENDS StoneyVCV
    USES_TERMINAL
)

#[==[dist]==]
add_custom_target(dist
    COMMAND "make" "dist"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    BYPRODUCTS
    "${PROJECT_SOURCE_DIR}/dist"
    SOURCES
    "${PROJECT_SOURCE_DIR}/${PLUGIN_LIB}"
    JOB_SERVER_AWARE TRUE
    DEPENDS plugin
    USES_TERMINAL
)

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

# # Only build tests if this project is the top-level project...
#[==[Tests_StoneyVCV]==]
if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)
    find_package(Catch2 3 REQUIRED)

    # # These tests can use the Catch2-provided main
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

        rack::dep
        rack::sdk
        rack::lib

        StoneyDSP::Core
        StoneyDSP::SIMD
        StoneyDSP::DSP
        StoneyDSP::StoneyVCV
        Catch2::Catch2WithMain
    )
    set_target_properties(Tests_StoneyVCV
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test"
        RUNTIME_OUTPUT_NAME "Tests_StoneyVCV"
    )
    target_compile_features(Tests_StoneyVCV PUBLIC cxx_std_17)
    target_compile_features(Tests_StoneyVCV PUBLIC c_std_17)

    # if(MINGW)
    # # target_compile_options(Tests_StoneyVCV
    # # PUBLIC

    # # "-municode"
    # # "-DCATCH_PLATFORM_WINDOWS=1"
    # # "-DCATCH_CONFIG_WCHAR=1"
    # # "-DDO_NOT_USE_WMAIN=1"
    # # )
    # # target_link_options(Tests_StoneyVCV
    # # PUBLIC
    # # "-lmingw32"
    # # "-municode"
    # # "-DCATCH_PLATFORM_WINDOWS=1"
    # # "-DCATCH_CONFIG_WCHAR=1"
    # # "-D_UNICODE"

    # # "-DDO_NOT_USE_WMAIN=1"
    # # )
    # endif()
    enable_testing()

    include(CTest)
    include(Catch)
    catch_discover_tests(Tests_StoneyVCV)

    list(APPEND STONEYVCV_TARGETS Tests_StoneyVCV)
endif()
