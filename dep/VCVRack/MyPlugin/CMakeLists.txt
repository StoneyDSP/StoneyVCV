cmake_minimum_required(VERSION 3.14...3.31 FATAL_ERROR)

# Pick up 'VCVRack.cmake' - helper functions
get_filename_component(VCVRACK_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
list(APPEND CMAKE_MODULE_PATH "${VCVRACK_DIR}/Rack-SDK/share/cmake/Modules")

# If NOT using CMAKE_TOOLCHAIN_FILE (i.e., vcpkg), then try uncommenting this to
# Ppick up 'rack-sdk-config.cmake', 'rack-sdk-*-targets.cmake.cmake', etc...
# list(APPEND CMAKE_PREFIX_PATH "${VCVRACK_DIR}/Rack-SDK/share/cmake/rack-sdk")

project(MyPlugin)

# Find rack-sdk package from CMAKE_PREFIX_PATH
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib)

# Include VCVRack helpers from CMAKE_MODULE_PATH
include(VCVRack)

vcvrack_get_plugin_slug()
vcvrack_get_plugin_version()

# Let's not *really* do this... but it's a useful test, for now
message(STATUS "plugin.json: {")
message(STATUS "  \"slug\": \"${VCVRACK_PLUGIN_SLUG}\"")
message(STATUS "  \"version\": \"${VCVRACK_PLUGIN_VERSION}\"")
message(STATUS "}")

include(GNUInstallDirs)
# I don't like that design pattern above; and parsing the plugin.json in this
# way leads to too many "cool ideas" which end up as dead ends. Let's focus on
# the real tasks: the helper functions which create plugin and module targets.

# Golden rule of CMake: *don't* tie your user's hands. It gets too brittle
# when you enforce requirements! Keep it flexible.

# Remember, we want this to "just work" for most users, but on the other hand,
# we do *not* want to dictate things like project and target names, and so
# forth; that stuff is often done with all the best intentions, but ironically
# ends up being the source of most problems, especially for inexperienced users.

# Let's try to make a plugin!

vcvrack_add_plugin(
    SLUG MySlug
    # HEADERS "include/plugin.hpp"
    SOURCES "src/plugin.cpp" "src/plugin.hpp"
    VERSION 2.0.0
    SOVERSION 2
)

vcvrack_add_module(MyModule
    SLUG MySlug
    SOURCES "src/MyModule.cpp"
    VERSION 0.0.1
    SOVERSION 0
)

# install targets and generate an export set
install(TARGETS plugin;MyModule
    EXPORT MyPluginExports
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET plugin_plugin_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET plugin_MyModule_PUBLIC_HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# install export set
install(EXPORT MyPluginExports
    FILE "MyPluginTargets.cmake"
    NAMESPACE MyBrand::MyPlugin::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MyBrand"
)

# export targets
export(
    TARGETS plugin;MyModule
    FILE "share/cmake/MyPluginTargets.cmake"
    NAMESPACE MyBrand::MyPlugin::
)
