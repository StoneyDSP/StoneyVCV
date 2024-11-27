# ###### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
# ###### Any changes to this file will be overwritten by the next CMake run ####
# ###### The input file was rack-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
    set(${_var} "${_file}")

    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# ###################################################################################
include("${CMAKE_CURRENT_LIST_DIR}/rack-config-version.cmake")

set(_rack_supported_components)
list(APPEND _rack_supported_components
    dep;sdk;lib
)

# # Custom 'check_required_components' macro
foreach(_requested_component ${rack_FIND_COMPONENTS})
    if(NOT _requested_component IN_LIST _rack_supported_components)
        message(FATAL_ERROR "Unsupported component: ${_requested_component}")
        set(rack_FOUND False)
        set(rack_NOT_FOUND_MESSAGE "Unsupported component: ${_requested_component}")
    endif()

    include("${CMAKE_CURRENT_LIST_DIR}/rack-${_requested_component}-targets.cmake")
    message(STATUS "Linking with rack::${_requested_component}")
endforeach()

unset(_rack_supported_components)

# ###################################################################################

# Tell the user what to do
message(STATUS "Linking with rack")
