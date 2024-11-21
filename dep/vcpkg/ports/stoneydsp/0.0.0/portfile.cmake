function(get_this_dir)
    set(_this_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}" PARENT_SCOPE)
endfunction()

get_this_dir()

get_filename_component(__stoneyvcv_dir "${_this_dir}/../../../../../" ABSOLUTE)

set(SOURCE_PATH "${__stoneyvcv_dir}/dep/StoneyDSP")

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(
    PACKAGE_NAME StoneyDSP
    CONFIG_PATH "lib/cmake/StoneyDSP"
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug")

file(
    INSTALL "${SOURCE_PATH}/LICENSE"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
    RENAME copyright
)
