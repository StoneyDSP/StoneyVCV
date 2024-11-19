# vcpkg_from_github(
#   OUT_SOURCE_PATH SOURCE_PATH
#   REPO northwindtraders/beison
#   REF a16bd37a342a20357ecfc67e8ce550b7a414bcb0
#   SHA512 2bbefe9d59b9e0f2e7192570eb744ddbb500277be8d51df9be6e9a4449710d3ce6030a6d5a6418871c8050418311be5002d95585432d3b624ff59344740aa6b8
#   HEAD_REF main
# )

function(get_this_dir)
    set(_this_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}" PARENT_SCOPE)
endfunction()

get_this_dir()

get_filename_component(__stoneyvcv_dir "${_this_dir}/../../../../../" ABSOLUTE)

set(SOURCE_PATH "${__stoneyvcv_dir}/dep/VCVRack")

vcpkg_backup_env_variables(
    VARS _RACK_DIR
    RACK_DIR
)


vcpkg_cmake_configure(
  SOURCE_PATH "${SOURCE_PATH}"
  OPTIONS -DRACK_DIR="$ENV{RACK_DIR}"
)
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(
    PACKAGE_NAME VCVRack
    CONFIG_PATH "lib/cmake/VCVRack"
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright)
