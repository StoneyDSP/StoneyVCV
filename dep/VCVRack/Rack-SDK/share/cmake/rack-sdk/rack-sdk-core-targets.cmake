# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "3.0.0")
   message(FATAL_ERROR "CMake >= 3.0.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 3.0.0...3.28)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS unofficial-vcvrack::rack-sdk::core)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()

# Create imported target unofficial-vcvrack::rack-sdk::core
add_library(unofficial-vcvrack::rack-sdk::core INTERFACE IMPORTED)

set_target_properties(unofficial-vcvrack::rack-sdk::core PROPERTIES
  COMPATIBLE_INTERFACE_STRING "INTERFACE_core_MAJOR_VERSION;INTERFACE_core_MINOR_VERSION;INTERFACE_core_PATCH_VERSION"
  INTERFACE_COMPILE_FEATURES "cxx_std_11;c_std_11"
  INTERFACE_COMPILE_OPTIONS "-fPIC"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "unofficial-vcvrack::rack-sdk::dep"
)

if(NOT CMAKE_VERSION VERSION_LESS "3.23.0")
  target_sources(unofficial-vcvrack::rack-sdk::core
    INTERFACE
      FILE_SET "rack_sdk_CORE_INTERFACE_HEADERS"
      TYPE "HEADERS"
      BASE_DIRS "${_IMPORT_PREFIX}/include/rack"
      FILES "${_IMPORT_PREFIX}/include/rack/Quantity.hpp" "${_IMPORT_PREFIX}/include/rack/arch.hpp" "${_IMPORT_PREFIX}/include/rack/asset.hpp" "${_IMPORT_PREFIX}/include/rack/audio.hpp" "${_IMPORT_PREFIX}/include/rack/color.hpp" "${_IMPORT_PREFIX}/include/rack/common.hpp" "${_IMPORT_PREFIX}/include/rack/componentlibrary.hpp" "${_IMPORT_PREFIX}/include/rack/context.hpp" "${_IMPORT_PREFIX}/include/rack/gamepad.hpp" "${_IMPORT_PREFIX}/include/rack/helpers.hpp" "${_IMPORT_PREFIX}/include/rack/history.hpp" "${_IMPORT_PREFIX}/include/rack/keyboard.hpp" "${_IMPORT_PREFIX}/include/rack/library.hpp" "${_IMPORT_PREFIX}/include/rack/logger.hpp" "${_IMPORT_PREFIX}/include/rack/math.hpp" "${_IMPORT_PREFIX}/include/rack/midi.hpp" "${_IMPORT_PREFIX}/include/rack/midiloopback.hpp" "${_IMPORT_PREFIX}/include/rack/mutex.hpp" "${_IMPORT_PREFIX}/include/rack/network.hpp" "${_IMPORT_PREFIX}/include/rack/patch.hpp" "${_IMPORT_PREFIX}/include/rack/plugin.hpp" "${_IMPORT_PREFIX}/include/rack/rack.hpp" "${_IMPORT_PREFIX}/include/rack/rack0.hpp" "${_IMPORT_PREFIX}/include/rack/random.hpp" "${_IMPORT_PREFIX}/include/rack/rtaudio.hpp" "${_IMPORT_PREFIX}/include/rack/rtmidi.hpp" "${_IMPORT_PREFIX}/include/rack/settings.hpp" "${_IMPORT_PREFIX}/include/rack/string.hpp" "${_IMPORT_PREFIX}/include/rack/system.hpp" "${_IMPORT_PREFIX}/include/rack/tag.hpp" "${_IMPORT_PREFIX}/include/rack/weakptr.hpp" "${_IMPORT_PREFIX}/include/rack/app/AudioDisplay.hpp" "${_IMPORT_PREFIX}/include/rack/app/Browser.hpp" "${_IMPORT_PREFIX}/include/rack/app/CableWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/CircularShadow.hpp" "${_IMPORT_PREFIX}/include/rack/app/Knob.hpp" "${_IMPORT_PREFIX}/include/rack/app/LedDisplay.hpp" "${_IMPORT_PREFIX}/include/rack/app/LightWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/MenuBar.hpp" "${_IMPORT_PREFIX}/include/rack/app/MidiDisplay.hpp" "${_IMPORT_PREFIX}/include/rack/app/ModuleLightWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/ModuleWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/MultiLightWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/ParamWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/PortWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/RackScrollWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/RackWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/RailWidget.hpp" "${_IMPORT_PREFIX}/include/rack/app/Scene.hpp" "${_IMPORT_PREFIX}/include/rack/app/SliderKnob.hpp" "${_IMPORT_PREFIX}/include/rack/app/SvgButton.hpp" "${_IMPORT_PREFIX}/include/rack/app/SvgKnob.hpp" "${_IMPORT_PREFIX}/include/rack/app/SvgPanel.hpp" "${_IMPORT_PREFIX}/include/rack/app/SvgPort.hpp" "${_IMPORT_PREFIX}/include/rack/app/SvgScrew.hpp" "${_IMPORT_PREFIX}/include/rack/app/SvgSlider.hpp" "${_IMPORT_PREFIX}/include/rack/app/SvgSwitch.hpp" "${_IMPORT_PREFIX}/include/rack/app/Switch.hpp" "${_IMPORT_PREFIX}/include/rack/app/TipWindow.hpp" "${_IMPORT_PREFIX}/include/rack/app/common.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/approx.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/common.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/convert.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/digital.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/fft.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/filter.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/fir.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/midi.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/minblep.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/ode.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/resampler.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/ringbuffer.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/vumeter.hpp" "${_IMPORT_PREFIX}/include/rack/dsp/window.hpp" "${_IMPORT_PREFIX}/include/rack/engine/Cable.hpp" "${_IMPORT_PREFIX}/include/rack/engine/Engine.hpp" "${_IMPORT_PREFIX}/include/rack/engine/Light.hpp" "${_IMPORT_PREFIX}/include/rack/engine/LightInfo.hpp" "${_IMPORT_PREFIX}/include/rack/engine/Module.hpp" "${_IMPORT_PREFIX}/include/rack/engine/Param.hpp" "${_IMPORT_PREFIX}/include/rack/engine/ParamHandle.hpp" "${_IMPORT_PREFIX}/include/rack/engine/ParamQuantity.hpp" "${_IMPORT_PREFIX}/include/rack/engine/Port.hpp" "${_IMPORT_PREFIX}/include/rack/engine/PortInfo.hpp" "${_IMPORT_PREFIX}/include/rack/plugin/Model.hpp" "${_IMPORT_PREFIX}/include/rack/plugin/Plugin.hpp" "${_IMPORT_PREFIX}/include/rack/plugin/callbacks.hpp" "${_IMPORT_PREFIX}/include/rack/simd/Vector.hpp" "${_IMPORT_PREFIX}/include/rack/simd/common.hpp" "${_IMPORT_PREFIX}/include/rack/simd/functions.hpp" "${_IMPORT_PREFIX}/include/rack/simd/sse_mathfun.h" "${_IMPORT_PREFIX}/include/rack/simd/sse_mathfun_extension.h" "${_IMPORT_PREFIX}/include/rack/ui/Button.hpp" "${_IMPORT_PREFIX}/include/rack/ui/ChoiceButton.hpp" "${_IMPORT_PREFIX}/include/rack/ui/Label.hpp" "${_IMPORT_PREFIX}/include/rack/ui/List.hpp" "${_IMPORT_PREFIX}/include/rack/ui/Menu.hpp" "${_IMPORT_PREFIX}/include/rack/ui/MenuEntry.hpp" "${_IMPORT_PREFIX}/include/rack/ui/MenuItem.hpp" "${_IMPORT_PREFIX}/include/rack/ui/MenuLabel.hpp" "${_IMPORT_PREFIX}/include/rack/ui/MenuOverlay.hpp" "${_IMPORT_PREFIX}/include/rack/ui/MenuSeparator.hpp" "${_IMPORT_PREFIX}/include/rack/ui/OptionButton.hpp" "${_IMPORT_PREFIX}/include/rack/ui/ProgressBar.hpp" "${_IMPORT_PREFIX}/include/rack/ui/RadioButton.hpp" "${_IMPORT_PREFIX}/include/rack/ui/ScrollWidget.hpp" "${_IMPORT_PREFIX}/include/rack/ui/Scrollbar.hpp" "${_IMPORT_PREFIX}/include/rack/ui/SequentialLayout.hpp" "${_IMPORT_PREFIX}/include/rack/ui/Slider.hpp" "${_IMPORT_PREFIX}/include/rack/ui/TextField.hpp" "${_IMPORT_PREFIX}/include/rack/ui/Tooltip.hpp" "${_IMPORT_PREFIX}/include/rack/ui/TooltipOverlay.hpp" "${_IMPORT_PREFIX}/include/rack/ui/common.hpp" "${_IMPORT_PREFIX}/include/rack/widget/FramebufferWidget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/OpaqueWidget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/OpenGlWidget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/SvgWidget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/TransformWidget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/TransparentWidget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/Widget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/ZoomWidget.hpp" "${_IMPORT_PREFIX}/include/rack/widget/event.hpp" "${_IMPORT_PREFIX}/include/rack/window/Svg.hpp" "${_IMPORT_PREFIX}/include/rack/window/Window.hpp"
  )
else()
  set_property(TARGET unofficial-vcvrack::rack-sdk::core
    APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
      "${_IMPORT_PREFIX}/include/rack"
  )
endif()

# Load information for each installed configuration.
file(GLOB _cmake_config_files "${CMAKE_CURRENT_LIST_DIR}/rack-sdk-core-targets-*.cmake")
foreach(_cmake_config_file IN LISTS _cmake_config_files)
  include("${_cmake_config_file}")
endforeach()
unset(_cmake_config_file)
unset(_cmake_config_files)

# Cleanup temporary variables.
set(_IMPORT_PREFIX)

# Loop over all imported files and verify that they actually exist
foreach(_cmake_target IN LISTS _cmake_import_check_targets)
  if(CMAKE_VERSION VERSION_LESS "3.28"
      OR NOT DEFINED _cmake_import_check_xcframework_for_${_cmake_target}
      OR NOT IS_DIRECTORY "${_cmake_import_check_xcframework_for_${_cmake_target}}")
    foreach(_cmake_file IN LISTS "_cmake_import_check_files_for_${_cmake_target}")
      if(NOT EXISTS "${_cmake_file}")
        message(FATAL_ERROR "The imported target \"${_cmake_target}\" references the file
   \"${_cmake_file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
      endif()
    endforeach()
  endif()
  unset(_cmake_file)
  unset("_cmake_import_check_files_for_${_cmake_target}")
endforeach()
unset(_cmake_target)
unset(_cmake_import_check_targets)

# Make sure the targets which have been exported in some other
# export set exist.
unset(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)
foreach(_target "unofficial-vcvrack::rack-sdk::dep" )
  if(NOT TARGET "${_target}" )
    set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets "${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets} ${_target}")
  endif()
endforeach()

if(DEFINED ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)
  if(CMAKE_FIND_PACKAGE_NAME)
    set( ${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
    set( ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE "The following imported targets are referenced, but are missing: ${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets}")
  else()
    message(FATAL_ERROR "The following imported targets are referenced, but are missing: ${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets}")
  endif()
endif()
unset(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
