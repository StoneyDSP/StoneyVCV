
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was StoneyVCVConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/StoneyVCVConfigVersion.cmake")

set(_StoneyVCV_supported_components)
list(APPEND _StoneyVCV_supported_components
    plugin;HP1;HP2;HP4
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

