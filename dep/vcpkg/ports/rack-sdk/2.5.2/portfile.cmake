# VCV Rack's Rack-SDK as a vcpkg package? yep - here's how;
# We have a CMakeLists.txt file in a nearby directory, which tells CMake
# how to scoop up the contents of '${RACK_DIR}', and to parse everything
# into three logical CMake targets: deps, sdk (headers), and lib (dynamic
# library).

# For this to be a vcpkg thing, we just need to use a vcpkg helper function
# to download the SDK from the Rack website, unzip it, and then configure
# the VCVRack CMake project with those contents...

function(_normalize_path var)
    message(STATUS "normalizing path: ${var}")
    set(path "${${var}}")
    file(TO_CMAKE_PATH "${path}" path)

    while(path MATCHES "//")
        string(REPLACE "//" "/" path "${path}")
    endwhile()

    string(REGEX REPLACE "/+$" "" path "${path}")
    set("${var}" "${path}" PARENT_SCOPE)
    message(STATUS "normalized path: ${var}")
endfunction()

function(get_this_dir)
    set(_this_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}" PARENT_SCOPE)
endfunction()

if(NOT VCPKG_TARGET_IS_MINGW AND NOT VCPKG_TARGET_IS_LINUX AND NOT VCPKG_TARGET_IS_OSX)
    message(FATAL_ERROR "VCV Rack SDK does not support the current platform...")
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
    URLS "https://vcvrack.com/downloads/Rack-SDK-2.5.2-${VCVRACK_RACKSDK_FILE_URL}.zip"
    FILENAME "Rack-SDK-2.5.2-${VCVRACK_RACKSDK_FILE_URL}"
    SHA512 "${VCVRACK_RACKSDK_FILE_HASH}"
)

vcpkg_extract_source_archive_ex(
    OUT_SOURCE_PATH RACK_DIR
    ARCHIVE "${ARCHIVE}"
)

# Dirty hack to use the local 'CMakeLists.txt' file under 'dep/VCVRack'...
get_this_dir()
get_filename_component(__stoneyvcv_dir "${_this_dir}/../../../../../" ABSOLUTE)
set(SOURCE_PATH "${__stoneyvcv_dir}/dep/VCVRack/Rack-SDK")

# Configure 'dep/VCVRack/CMakeLists.txt' using the unzipped Rack SDK
vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS -DRACK_DIR="${RACK_DIR}"
)
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(
    PACKAGE_NAME rack-sdk
    CONFIG_PATH "lib/cmake/rack-sdk"
)
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(
    INSTALL "${SOURCE_PATH}/LICENSE"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
    RENAME copyright
)

# The rack SDK is now a vcpkg package named "rack" - you can add "rack" to your
# vcpkg.json dependencies and point vcpkg-configuration.json at this registry
# in order to pick it up!
