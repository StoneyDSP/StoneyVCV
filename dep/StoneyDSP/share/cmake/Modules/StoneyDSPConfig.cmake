
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was StoneyDSPConfig.cmake.in                    ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/StoneyDSPConfigVersion.cmake")

set(_StoneyDSP_supported_components)
list(APPEND _StoneyDSP_supported_components
    Core;SIMD;DSP
)

## Custom 'check_required_components' macro
foreach(_requested_component ${StoneyDSP_FIND_COMPONENTS})
  if (NOT _requested_component IN_LIST _StoneyDSP_supported_components)
    set(StoneyDSP_FOUND False)
    set(StoneyDSP_NOT_FOUND_MESSAGE "Unsupported component: ${_requested_component}")
  endif()
  include("${CMAKE_CURRENT_LIST_DIR}/StoneyDSP${_requested_component}Targets.cmake")
  message(STATUS "Linking with StoneyDSP::${_requested_component}")
endforeach()

unset(_StoneyDSP_supported_components)

# Tell the user what to do
message(STATUS "Linking with StoneyDSP")
