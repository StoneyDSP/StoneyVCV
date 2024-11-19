
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was VCVRackConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/VCVRackConfigVersion.cmake")

set(_VCVRack_supported_components)
list(APPEND _VCVRack_supported_components
    RackSDK
    Rack
)
## Custom 'check_required_components' macro
foreach(_requested_component ${VCVRack_FIND_COMPONENTS})
    if (NOT _requested_component IN_LIST _VCVRack_supported_components)
      set(VCVRack_FOUND False)
      set(VCVRack_NOT_FOUND_MESSAGE "Unsupported component: ${_requested_component}")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/VCVRack${_requested_component}Targets.cmake")
    message(STATUS "Linking with VCVRack::${_requested_component}")
  endforeach()

unset(_VCVRack_supported_components)

####################################################################################

# include ("${CMAKE_CURRENT_LIST_DIR}/VCVRackTargets.cmake")

## Required...
if(NOT DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
    message(FATAL_ERROR "You need to set $RACK_DIR")
endif()

## Take RACK_DIR from env, if not passed as -DRACK_DIR=...
if(DEFINED ENV{RACK_DIR} AND NOT DEFINED RACK_DIR)
    set(RACK_DIR "$ENV{RACK_DIR}" CACHE STRING "" FORCE)
endif()

# Tell the user what to do
message(STATUS "Linking with VCVRack")
