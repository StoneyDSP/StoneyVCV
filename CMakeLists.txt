cmake_minimum_required(VERSION 3.23...3.31 FATAL_ERROR)

#[=================================[STONEYVCV]=================================]

project(STONEYVCV
    VERSION 2.0.1.0
    DESCRIPTION "StoneyDSP Modules for VCV Rack 2."
    HOMEPAGE_URL "https://github.com/StoneyDSP/StoneyVCV"
)
set(PROJECT_NAME "StoneyVCV" CACHE STRING "" FORCE)

enable_language(C)
enable_language(CXX)

include(CMakeDependentOption)
include(GNUInstallDirs)

set(STONEYVCV_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "" FORCE)
set(STONEYVCV_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE PATH "" FORCE)
set(STONEYVCV_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION_TWEAK "${CMAKE_PROJECT_VERSION_TWEAK}" CACHE STRING "" FORCE)
set(STONEYVCV_VERSION "${CMAKE_PROJECT_VERSION}" CACHE STRING "" FORCE)

option(STONEYVCV_EXPERIMENTAL                       "Use '-DSTONEYVCV_EXPERIMENTAL=ON|OFF' when configuring to toggle this option." OFF)
option(STONEYVCV_BUILD_PLUGIN                       "Use '-DSTONEYVCV_BUILD_PLUGIN=ON|OFF' when configuring to toggle this option." ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULES      "Use '-DSTONEYVCV_BUILD_MODULES=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_PLUGIN" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_HP1   "Use '-DSTONEYVCV_BUILD_MODULE_HP1=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_HP2   "Use '-DSTONEYVCV_BUILD_MODULE_HP2=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_HP4   "Use '-DSTONEYVCV_BUILD_MODULE_HP4=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_BUILD_MODULES" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_VCA   "Use '-DSTONEYVCV_BUILD_MODULE_VCA=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_EXPERIMENTAL" ON)
cmake_dependent_option(STONEYVCV_BUILD_MODULE_LFO   "Use '-DSTONEYVCV_BUILD_MODULE_LFO=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_EXPERIMENTAL" ON)
cmake_dependent_option(STONEYVCV_BUILD_TESTS        "Use '-DSTONEYVCV_BUILD_TESTS=ON|OFF' when configuring to toggle this option." ON "STONEYVCV_IS_TOP_LEVEL" ON)

# Put components in the correct order of their dependencies on eachother to save tears...
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib CONFIG)
find_package(StoneyDSP 0.0.0 REQUIRED COMPONENTS Core SIMD DSP CONFIG)

# Initialize list of targets to build
set(STONEYVCV_TARGETS)

#[==================================[plugin]==================================]#

if(STONEYVCV_BUILD_PLUGIN)

    # create rack-sdk plugin target
    vcvrack_add_plugin(
        SLUG StoneyVCV
        BRAND StoneyDSP
            HEADERS "include/StoneyVCV/plugin.hpp" "include/StoneyVCV/version.hpp"
        SOURCES "src/StoneyVCV/plugin.cpp"
            VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}"
            SOVERSION "${STONEYVCV_VERSION_MAJOR}"
        EXPORT
        INSTALL
    )

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

endif(STONEYVCV_BUILD_PLUGIN)

#[==[test]==]
function(stoneyvcv_add_test MODULE)
    add_library(tests_${MODULE} OBJECT EXCLUDE_FROM_ALL)
    add_library(StoneyVCV::tests_${MODULE} ALIAS tests_${MODULE})
    add_library(StoneyDSP::StoneyVCV::tests_${MODULE} ALIAS tests_${MODULE})
    target_include_directories(tests_${MODULE}
        PUBLIC
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_sources(tests_${MODULE}
        PRIVATE
            "${STONEYVCV_SOURCE_DIR}/test/StoneyVCV/${MODULE}.cpp"
    )
    target_link_libraries(tests_${MODULE}
        PUBLIC
            unofficial-vcvrack::rack-sdk::core
            StoneyDSP::StoneyVCV::${MODULE}
            Catch2::Catch2
    )
    target_compile_features(tests_${MODULE} PUBLIC cxx_std_17)
    target_compile_features(tests_${MODULE} PUBLIC c_std_17)
endfunction()

if(STONEYVCV_IS_TOP_LEVEL AND STONEYVCV_BUILD_TESTS)

    find_package(Catch2 3.5.2 REQUIRED)
    add_executable(tests)
    add_executable(StoneyVCV::tests ALIAS tests)
    add_executable(StoneyDSP::StoneyVCV::tests ALIAS tests)
    target_include_directories(tests
        PUBLIC
        $<BUILD_INTERFACE:${STONEYVCV_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(tests
        PUBLIC
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
endif()

#[==================================[Modules]==================================]

if(STONEYVCV_BUILD_MODULES)

    set(STONEYVCV_MODULES)
    list(APPEND STONEYVCV_MODULES # List of enabled modules
        HP1
        HP2
        HP4
    )

    set(STONEYVCV_EXPERIMENTAL_MODULES)
    list(APPEND STONEYVCV_EXPERIMENTAL_MODULES # List of enabled experimental modules
        VCA
        LFO
    )

    if(STONEYVCV_EXPERIMENTAL)
        list(APPEND STONEYVCV_MODULES ${STONEYVCV_EXPERIMENTAL_MODULES})
    endif()

    foreach(MODULE IN LISTS STONEYVCV_MODULES)

        if(STONEYVCV_BUILD_MODULE_${MODULE}) # Toggle module code with -D

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
            list(APPEND STONEYVCV_TARGETS ${MODULE}) # Collect enabled modules

            target_compile_definitions(${MODULE}
                PUBLIC
                    "-DSTONEYVCV_BUILD_PLUGIN=1"
                    "-DSTONEYVCV_BUILD_MODULES=1"
                    "-DSTONEYVCV_BUILD_${MODULE}=1"
            )

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
        target_link_libraries(tests PUBLIC StoneyDSP::StoneyVCV::tests_${TARGET})
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

#[============================[Write CMake Package]============================]

include(CMakePackageConfigHelpers)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/StoneyVCV.pc.in" [==[
prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=/${exec_prefix}/@CMAKE_INSTALL_LIBDIR@
includedir=/${prefix}/@CMAKE_INSTALL_INCLUDEDIR@

Name: @PROJECT_NAME@
Description: @PROJECT_DESCRIPTION@
Version: @PROJECT_VERSION@
Requires: Rack-SDK = 2.5.2
Libs: -L${libdir} -lRack
Cflags: -I${includedir}
]==])

configure_file (
  "${CMAKE_CURRENT_BINARY_DIR}/StoneyVCV.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/lib/pkgconfig/StoneyVCV.pc"
  @ONLY
)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/lib/pkgconfig/StoneyVCV.pc"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSP-StoneyVCVConfig.cmake.in" [==[
@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/StoneyDSP-StoneyVCVConfigVersion.cmake")

include(CMakeFindDependencyMacro)

find_dependency(rack-sdk 2.5.2)
find_dependency(StoneyDSP 0.0.0)

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
# generate a basic package config file
configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/StoneyDSP-StoneyVCVConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/StoneyDSP/StoneyDSP-StoneyVCVConfig.cmake"
    INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"
    # Use custom 'check_required_components' macro
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/StoneyDSP/StoneyDSP-StoneyVCVConfigVersion.cmake"
    VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}"
    COMPATIBILITY ExactVersion
)

#[===========================[Install CMake Package]===========================]

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/StoneyDSP/StoneyDSP-StoneyVCVConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/StoneyDSP/StoneyDSP-StoneyVCVConfigVersion.cmake"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP"
)
install(DIRECTORY
    "${STONEYVCV_SOURCE_DIR}/res"
    DESTINATION
    # This is not a good location to be using...
    "${CMAKE_INSTALL_PREFIX}"
)
install(DIRECTORY
    "${STONEYVCV_SOURCE_DIR}/presets"
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
    set(CPACK_PACKAGE_NAME "StoneyVCV")
    set(CPACK_PACKAGE_VENDOR "StoneyDSP")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "StoneyDSP modules for VCV Rack 2.")
    set(CPACK_PACKAGE_VERSION "${STONEYVCV_VERSION_MAJOR}.${STONEYVCV_VERSION_MINOR}.${STONEYVCV_VERSION_PATCH}")
    set(CPACK_PACKAGE_VERSION_MAJOR "${STONEYVCV_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${STONEYVCV_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${STONEYVCV_VERSION_PATCH}")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "StoneyDSP")
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
    cpack_add_component(plugin
        DISPLAY_NAME "StoneyVCV v${STONEYVCV_VERSION}"
        DESCRIPTION "StoneyDSP modules for VCV Rack 2."
        GROUP "StoneyVCV"
    )
    foreach(MODULE IN LISTS STONEYVCV_MODULES)
        cpack_add_component(${MODULE}
            DISPLAY_NAME "${MODULE} v${STONEYVCV_VERSION}"
            DESCRIPTION "The ${MODULE} module."
            GROUP "StoneyVCV"
        )
    endforeach()
endif()
