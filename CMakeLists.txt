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
cmake_dependent_option(STONEYVCV_BUILD_MODULE_VCA "" ON "STONEYVCV_BUILD_MODULES" ON)

# Put components in the correct order of their dependencies on eachother
# to save tears...
find_package(StoneyDSP 0.0.0 REQUIRED COMPONENTS Core SIMD DSP CONFIG)
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib CONFIG)
# The package cmakerc provides additional cmake functions:
find_package(CMakeRC CONFIG REQUIRED)
# cmrc_add_resource_library(foo-resources ALIAS foo::rc NAMESPACE foo  ...)
# target_link_libraries(main PRIVATE foo::rc)

# These props are helpful to have around...
get_target_property(rack_inc_dir unofficial-vcvrack::rack-sdk::lib INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(rack_link_dir unofficial-vcvrack::rack-sdk::lib INTERFACE_LINK_DIRECTORIES)
get_target_property(rack_implib unofficial-vcvrack::rack-sdk::lib IMPORTED_IMPLIB)
get_target_property(rack_implib_location unofficial-vcvrack::rack-sdk::lib IMPORTED_LOCATION)

set(STONEYVCV_TARGETS)

#[==[StoneyVCV]==]
vcvrack_add_plugin(
    SLUG StoneyVCV
    BRAND StoneyDSP
    HEADERS "include/StoneyVCV/plugin.hpp"
    SOURCES "src/StoneyVCV/plugin.cpp"
    VERSION 2.0.1
    SOVERSION 2
    EXPORT
    INSTALL
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
    StoneyDSP::Core
    StoneyDSP::SIMD
    StoneyDSP::DSP
)
list(APPEND STONEYVCV_TARGETS plugin)

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
        "${STONEYVCV_SOURCE_DIR}/test/StoneyVCV/plugin.cpp"
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
endif()

if(STONEYVCV_BUILD_MODULES)
    set(STONEYVCV_MODULES)
    list(APPEND STONEYVCV_MODULES
        HP1
        HP2
        HP4
        VCA
    )
    foreach(MODULE IN LISTS STONEYVCV_MODULES)
        if(STONEYVCV_BUILD_MODULE_${MODULE})
            vcvrack_add_module(${MODULE}
                SLUG StoneyVCV
                BRAND StoneyDSP
                HEADERS "include/StoneyVCV/${MODULE}.hpp"
                SOURCES "src/StoneyVCV/${MODULE}.cpp"
                VERSION 0.0.1
                SOVERSION 0
                EXPORT
                INSTALL
            )
            target_compile_definitions(${MODULE}
                PUBLIC
                "STONEYVCV_VERSION_MAJOR=${STONEYVCV_VERSION_MAJOR}"
                "STONEYVCV_VERSION_MINOR=${STONEYVCV_VERSION_MINOR}"
                "STONEYVCV_VERSION_PATCH=${STONEYVCV_VERSION_PATCH}"
                "STONEYVCV_VERSION_TWEAK=${STONEYVCV_VERSION_TWEAK}"
                "STONEYVCV_VERSION=${STONEYVCV_VERSION}"
            )
            target_compile_definitions(plugin PUBLIC "-DSTONEYVCV_BUILD_${MODULE}=1")
            if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)
                target_sources(tests
                    PRIVATE
                    "${STONEYVCV_SOURCE_DIR}/test/StoneyVCV/${MODULE}.cpp"
                )
            endif()
            list(APPEND STONEYVCV_TARGETS ${MODULE})
        endif()
    endforeach()

endif(STONEYVCV_BUILD_MODULES)

if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)
    enable_testing()
    include(CTest)
    include(Catch)
    set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
    catch_discover_tests(tests)
endif()

#[==[StoneyVCVConfig.cmake]==]
include(CMakePackageConfigHelpers)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSP-StoneyVCVConfig.cmake.in" [==[
@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/StoneyDSP-StoneyVCVConfigVersion.cmake")

include(CMakeFindDependencyMacro)
find_dependency(rack-sdk 2.5.2)

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
    "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSP-StoneyVCVConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSP-StoneyVCVConfig.cmake"
    INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"

    # # Use custom 'check_required_components' macro
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSP-StoneyVCVConfigVersion.cmake"
    VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSP-StoneyVCVConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/share/cmake/StoneyDSP-StoneyVCVConfigVersion.cmake"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"
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
