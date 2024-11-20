# vcpkg_from_github(
#   OUT_SOURCE_PATH SOURCE_PATH
#   REPO northwindtraders/beison
#   REF a16bd37a342a20357ecfc67e8ce550b7a414bcb0
#   SHA512 2bbefe9d59b9e0f2e7192570eb744ddbb500277be8d51df9be6e9a4449710d3ce6030a6d5a6418871c8050418311be5002d95585432d3b624ff59344740aa6b8
#   HEAD_REF main
# )

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

set(VCVRACK_RACK_LIB_FILE_EXTENSION)
if(VCPKG_TARGET_IS_MINGW)
    set(VCVRACK_RACK_LIB_FILE_EXTENSION ".dylib")
elseif(VCPKG_TARGET_IS_LINUX)
    set(VCVRACK_RACK_LIB_FILE_EXTENSION ".so")
elseif(VCPKG_TARGET_IS_OSX)
    set(VCVRACK_RACK_LIB_FILE_EXTENSION ".dll.a")
else()
    message(FATAL_ERROR "VCVRack: unsupported platform")
endif()

# vcpkg_download_distfile(ARCHIVE
#     URLS "@URL@"
#     FILENAME "@FILENAME@"
#     SHA512 @SHA512@
# )

# vcpkg_extract_source_archive_ex(
#     OUT_SOURCE_PATH SOURCE_PATH
#     ARCHIVE "${ARCHIVE}"
#     # (Optional) A friendly name to use instead of the filename of the archive (e.g.: a version number or tag).
#     # REF 1.0.0
#     # (Optional) Read the docs for how to generate patches at:
#     # https://github.com/microsoft/vcpkg-docs/blob/main/vcpkg/examples/patching.md
#     # PATCHES
#     #   001_port_fixes.patch
#     #   002_more_port_fixes.patch
# )


get_this_dir()

get_filename_component(__stoneyvcv_dir "${_this_dir}/../../../../../" ABSOLUTE)

set(SOURCE_PATH "${__stoneyvcv_dir}/dep/VCVRack")

vcpkg_backup_env_variables(
    VARS RACK_DIR
)

if(VCPKG_TARGET_IS_MINGW)
    # _normalize_path("${z_vcpkg_env_backup_RACK_DIR}")
    message(STATUS "normalizing Rack SDK Path: ${z_vcpkg_env_backup_RACK_DIR}")
    vcpkg_execute_in_download_mode(
        COMMAND "cygpath -u ${z_vcpkg_env_backup_RACK_DIR}"
        RESULT_VARIABLE _RACK_DIR #error_code
        # WORKING_DIRECTORY "${arg_WORKING_DIRECTORY}"
    )
    # if("${_RACK_DIR}" NOT STREQUAL "")
    #     message(FATAL_ERROR "${error_variable}")
    # endif()
    set(z_vcpkg_env_backup_RACK_DIR "${_RACK_DIR}" CACHE)
endif()

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS -DRACK_DIR="${z_vcpkg_env_backup_RACK_DIR}"
)
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(
    PACKAGE_NAME VCVRack
    CONFIG_PATH "lib/cmake/VCVRack"
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/lib" "${CURRENT_PACKAGES_DIR}/debug/lib")

file(
    INSTALL "${SOURCE_PATH}/LICENSE"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
    RENAME copyright
)

vcpkg_restore_env_variables(
    VARS RACK_DIR
)
