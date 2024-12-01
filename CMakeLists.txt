cmake_minimum_required(VERSION 3.14...3.31 FATAL_ERROR)

#[==[STONEYVCV]==]
project(STONEYVCV VERSION 2.0.1.0)

enable_language(C)
enable_language(CXX)

include(CMakeDependentOption)

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
find_package(rack 2.5.2 REQUIRED COMPONENTS dep sdk lib CONFIG)

# These props are helpful to have around...
get_target_property(rack_inc_dir rack::lib INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(rack_link_dir rack::lib INTERFACE_LINK_DIRECTORIES)
get_target_property(rack_implib rack::lib IMPORTED_IMPLIB)
get_target_property(rack_implib_location rack::lib IMPORTED_LOCATION)

set(STONEYVCV_TARGETS)

#[==[StoneyVCV]==]
add_library(StoneyVCV SHARED EXCLUDE_FROM_ALL)
add_library(StoneyDSP::StoneyVCV ALIAS StoneyVCV)

set_target_properties(StoneyVCV PROPERTIES VERSION 2.1.0)
set_target_properties(StoneyVCV PROPERTIES SOVERSION 2.1.0)

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

configure_file("include/${PLUGIN_HPP}" "include/${PLUGIN_HPP}")

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
)

set_target_properties(StoneyVCV
    PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_NAME "plugin"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
    # Compatible Interface
    INTERFACE_StoneyVCV_MAJOR_VERSION ${STONEYVCV_VERSION_MAJOR}
    INTERFACE_StoneyVCV_MINOR_VERSION ${STONEYVCV_VERSION_MINOR}
    INTERFACE_StoneyVCV_PATCH_VERSION ${STONEYVCV_VERSION_PATCH}
)
set_property(TARGET StoneyVCV APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_StoneyVCV_MAJOR_VERSION
)
set_property(TARGET StoneyVCV APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_StoneyVCV_MINOR_VERSION
)
set_property(TARGET StoneyVCV APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING INTERFACE_StoneyVCV_PATCH_VERSION
)
target_compile_definitions(StoneyVCV
    PUBLIC
    "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
    "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
    "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
    "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
    "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
)
if(DEFINED STONEYVCV_EXPERIMENTAL)
    target_compile_definitions(StoneyVCV
        PUBLIC
        "STONEYVCV_EXPERIMENTAL=${STONEYVCV_EXPERIMENTAL}"
    )
endif(DEFINED STONEYVCV_EXPERIMENTAL)
target_link_libraries(StoneyVCV
    PUBLIC
    rack::lib
    StoneyDSP::Core
    StoneyDSP::SIMD
    StoneyDSP::DSP
)

# target_link_options(StoneyVCV
# PRIVATE
# "-fPIC"
# "-shared"
# )
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
    endif(APPLE)
endif(UNIX)

if(WIN32)
    target_link_options(StoneyVCV
        PUBLIC
        "-static-libstdc++"
    )
endif(WIN32)

if(STONEYVCV_BUILD_MODULES)

#[==[HP1]==]
if(STONEYVCV_BUILD_MODULE_HP1)
set(STONEYVCV_HP1_HPP "HP1.hpp")
configure_file("include/${STONEYVCV_HP1_HPP}" "include/${STONEYVCV_HP1_HPP}")
target_sources(StoneyVCV
    PUBLIC
    FILE_SET stoneyvcv_PUBLIC_HEADERS
    TYPE HEADERS
    BASE_DIRS
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    FILES
    #[==[include/plugin.hpp]==]
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${STONEYVCV_HP1_HPP}>
    $<INSTALL_INTERFACE:include/${STONEYVCV_HP1_HPP}>
)
target_sources(StoneyVCV PRIVATE "src/HP1.cpp")
endif(STONEYVCV_BUILD_MODULE_HP1)

#[==[HP2]==]
if(STONEYVCV_BUILD_MODULE_HP2)
set(STONEYVCV_HP2_HPP "HP2.hpp")
configure_file("include/${STONEYVCV_HP2_HPP}" "include/${STONEYVCV_HP2_HPP}")
target_sources(StoneyVCV
    PUBLIC
    FILE_SET stoneyvcv_PUBLIC_HEADERS
    TYPE HEADERS
    BASE_DIRS
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    FILES
    #[==[include/plugin.hpp]==]
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${STONEYVCV_HP2_HPP}>
    $<INSTALL_INTERFACE:include/${STONEYVCV_HP2_HPP}>
)
target_sources(StoneyVCV PRIVATE "src/HP2.cpp")
endif(STONEYVCV_BUILD_MODULE_HP2)

#[==[HP4]==]
if(STONEYVCV_BUILD_MODULE_HP4)
    set(STONEYVCV_HP2_HPP "HP4.hpp")
    configure_file("include/${STONEYVCV_HP4_HPP}" "include/${STONEYVCV_HP4_HPP}")
    target_sources(StoneyVCV
        PUBLIC
        FILE_SET stoneyvcv_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        FILES
        #[==[include/plugin.hpp]==]
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${STONEYVCV_HP4_HPP}>
        $<INSTALL_INTERFACE:include/${STONEYVCV_HP4_HPP}>
    )
    target_sources(StoneyVCV PRIVATE "src/HP4.cpp")
endif(STONEYVCV_BUILD_MODULE_HP4)

endif(STONEYVCV_BUILD_MODULES)


# # Only build tests if this project is the top-level project...
#[==[Tests_StoneyVCV]==]
if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)
    find_package(Catch2 3.5.2 REQUIRED)

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
        "${PROJECT_SOURCE_DIR}/test/HP1.cpp"
    )

    target_link_libraries(Tests_StoneyVCV
        PRIVATE
        rack::lib
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

    enable_testing()

    include(CTest)
    include(Catch)

    set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

    set(dl_paths)
    list(APPEND dl_paths "${rack_link_dir}")

    catch_discover_tests(Tests_StoneyVCV)

    list(APPEND STONEYVCV_TARGETS Tests_StoneyVCV)
endif()
