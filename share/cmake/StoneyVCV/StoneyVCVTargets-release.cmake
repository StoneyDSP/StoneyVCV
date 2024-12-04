#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "StoneyDSP::StoneyVCV::plugin" for configuration "Release"
set_property(TARGET StoneyDSP::StoneyVCV::plugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(StoneyDSP::StoneyVCV::plugin PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/plugin.so.2.1.0"
  IMPORTED_SONAME_RELEASE "plugin.so.2.1.0"
  )

list(APPEND _cmake_import_check_targets StoneyDSP::StoneyVCV::plugin )
list(APPEND _cmake_import_check_files_for_StoneyDSP::StoneyVCV::plugin "${_IMPORT_PREFIX}/lib/plugin.so.2.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
