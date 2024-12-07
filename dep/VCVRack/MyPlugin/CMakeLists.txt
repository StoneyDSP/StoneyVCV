cmake_minimum_required(VERSION 3.14...3.31 FATAL_ERROR)

# Pick up 'VCVRack.cmake' - helper functions
get_filename_component(VCVRACK_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
list(APPEND CMAKE_MODULE_PATH "${VCVRACK_DIR}/Rack-SDK/share/cmake/Modules")
# Pick up 'rack-sdk-config.cmake', 'rack-sdk-*-targets.cmake.cmake', etc
list(APPEND CMAKE_PREFIX_PATH "${VCVRACK_DIR}/Rack-SDK/share/cmake/rack-sdk")

project(MyPlugin)

# Find rack-sdk package from CMAKE_PREFIX_PATH
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib)

# Include VCVRack helpers from CMAKE_MODULE_PATH
include(VCVRack)

vcvrack_get_plugin_slug()
vcvrack_get_plugin_version()
