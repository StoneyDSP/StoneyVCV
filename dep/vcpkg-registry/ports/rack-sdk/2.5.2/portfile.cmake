# VCV Rack's Rack-SDK as a vcpkg package? yep - here's how;
# We have a CMakeLists.txt file in a nearby directory, which tells CMake
# how to scoop up the contents of '${RACK_DIR}', and to parse everything
# into three logical CMake targets: deps, sdk (headers), and lib (dynamic
# library).

# For this to be a vcpkg thing, we just need to use a vcpkg helper function
# to download the SDK from the Rack website, unzip it, and then configure
# the VCVRack CMake project with those contents...

if(NOT VCPKG_TARGET_IS_MINGW AND NOT VCPKG_TARGET_IS_LINUX AND NOT VCPKG_TARGET_IS_OSX)
    message(SEND_ERROR "VCV Rack SDK does not support the current platform...")
    return()
endif()

set(VCVRACK_RACKSDK_VERSION_MAJOR "2")
set(VCVRACK_RACKSDK_VERSION_MINOR "5")
set(VCVRACK_RACKSDK_VERSION_BUILDNUMBER "2")
# 2.5.2
set(VCVRACK_RACKSDK_VERSION "${VCVRACK_RACKSDK_VERSION_MAJOR}.${VCVRACK_RACKSDK_VERSION_MINOR}.${VCVRACK_RACKSDK_VERSION_BUILDNUMBER}")

if(NOT "${VERSION}" STREQUAL "${VCVRACK_RACKSDK_VERSION}")
    message(SEND_ERROR "VCV Rack SDK version mismatch: Requested version: ${VERSION}; found version: ${VCVRACK_RACKSDK_VERSION}...")
    return()
endif()

if(VCPKG_TARGET_IS_MINGW)
    # Rack-SDK uses the old C runtime...
    set(VCPKG_POLICY_ALLOW_OBSOLETE_MSVCRT enabled)
endif()

vcpkg_check_linkage(
    ONLY_DYNAMIC_LIBRARY
)

if(FALSE) # interesting...
    vcpkg_acquire_msys(MSYS_ROOT
        PACKAGES
            git
            wget
            make
            tar
            unzip
            zip
            mingw-w64-x86_64-gcc
            mingw-w64-x86_64-gdb
            mingw-w64-x86_64-cmake
            autoconf
            automake
            libtool
            mingw-w64-x86_64-jq
            python
            zstd
            mingw-w64-x86_64-pkgconf
    )
endif()
# This can be further customized... does the Rack SDK have x86 profiles?
set(VCVRACK_RACKSDK_FILE_URL)
set(VCVRACK_RACKSDK_FILE_HASH)

if(VCPKG_TARGET_IS_MINGW)
    set(VCVRACK_RACKSDK_FILE_URL "win-x64")
    set(VCVRACK_RACKSDK_FILE_HASH "fad593f7c6d7679a105984b3b30d719b7767b846a9f3c0ef29644159e77d73eea99d02869a94f6d47c6a55330419304fab941634d81c92beae501f8141564074")
elseif(VCPKG_TARGET_IS_LINUX)
    set(VCVRACK_RACKSDK_FILE_URL "lin-x64")
    set(VCVRACK_RACKSDK_FILE_HASH "845b174c4071c8be6d061e619d886cf4a309a2b9750327ddb62ad176ae40571d109877239cdc3258bf5c8e76a0b958352c5a31e99293ac6d951c87d204dc3ec9")
elseif(VCPKG_TARGET_IS_OSX)
    set(VCVRACK_RACKSDK_FILE_URL "mac-x64+arm64")
    set(VCVRACK_RACKSDK_FILE_HASH "533eec89a68ae33d47120106f2410836fcdf6c60df1858ca0c03892a8490c7e48d1433df79fc2f182c4318c983f211f6ef66bbea270188761c78c1a262f91d47")
else()
    message(FATAL_ERROR "VCVRack: unsupported platform")
endif()

# This can be further customized... package version == archive version???
vcpkg_download_distfile(ARCHIVE
    URLS "https://vcvrack.com/downloads/Rack-SDK-${VCVRACK_RACKSDK_VERSION}-${VCVRACK_RACKSDK_FILE_URL}.zip"
    FILENAME "Rack-SDK-${VCVRACK_RACKSDK_VERSION}-${VCVRACK_RACKSDK_FILE_URL}"
    SHA512 "${VCVRACK_RACKSDK_FILE_HASH}"
)

vcpkg_extract_source_archive_ex(
    OUT_SOURCE_PATH RACK_DIR
    ARCHIVE "${ARCHIVE}"
)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO StoneyDSP/Rack-SDK
    REF 95c6e2fc9b1589f8a719f9fa6819fe7d50d7ad60
    SHA512 4b5fb5812464a4957bc7a6d63e0da42b706834a6fee7a1892ad7efa0d8f3ab901af0f5559b0e5b8a21d9e5809c1e047503fe8658e54afd23d8921d5ca22af493
    HEAD_REF main
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        dep         RACK_SDK_INSTALL_DEPS
        core        RACK_SDK_INSTALL_CORE
        lib         RACK_SDK_INSTALL_LIB
        runtimes    RACK_SDK_INSTALL_RUNTIME_LIBS
)

# Configure Rack-SDK CMake project using the unzipped Rack SDK
vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
    -DRACK_DIR:PATH="${RACK_DIR}"
    -DRACK_SDK_DISABLE_USAGE_MESSAGE:BOOL="TRUE"
    # Expands to: "-DRACK_SDK_BUILD_DEPS=ON|OFF;-DRACK_SDK_BUILD_CORE=ON|OFF;-DRACK_SDK_BUILD_LIB=ON|OFF;-DRACK_SDK_INSTALL_RUNTIME_LIBS=ON|OFF"
    ${FEATURE_OPTIONS}
)
vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(
    INSTALL "${SOURCE_PATH}/LICENSE"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
    RENAME copyright
)
string(CONFIGURE [==[

rack-sdk provides CMake targets:

project(MyPlugin)

find_package(@PORT@ @VCVRACK_RACKSDK_VERSION@)

vcvrack_add_plugin(
    SLUG MySlug
    HEADERS "include/plugin.hpp"
    SOURCES "src/plugin.cpp"
)

vcvrack_add_module(MyModule
    SLUG MySlug
    SOURCES "src/MyModule.cpp"
)

vcvrack_add_module(MyOtherModule
    SLUG MySlug
    SOURCES "src/MyOtherModule.cpp"
)

You can #include '<rack.hpp>' in 'plugin.cpp' and start building with the VCV Rack API and all its' dependencies.

For more examples:

https://github.com/StoneyDSP/Rack-SDK/share/cmake/Modules/README.md

]==] _VCVRACK_USAGE_FILE @ONLY)
file(WRITE "${CURRENT_PACKAGES_DIR}/include/rack.hpp" [==[
// intellisense helper
#include "Rack-SDK/rack/rack.hpp"
]==])
file(WRITE "${CURRENT_PACKAGES_DIR}/share/${PORT}/usage" "${_VCVRACK_USAGE_FILE}")
unset(_VCVRACK_USAGE_FILE)
vcpkg_cmake_config_fixup(
    PACKAGE_NAME rack-sdk
    CONFIG_PATH "lib/cmake/Rack-SDK"
)

# The rack SDK is now a vcpkg package named "rack" - you can add "rack" to your
# vcpkg.json dependencies and point vcpkg-configuration.json at this registry
# in order to pick it up!
