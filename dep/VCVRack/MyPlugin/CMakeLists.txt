cmake_minimum_required(VERSION 3.14...3.31 FATAL_ERROR)

project(MyPlugin)

# Find rack-sdk package from CMAKE_TOOLCHAIN_FILE
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib)

# Let's try to make a plugin!

vcvrack_add_plugin(
    SLUG MySlug
    HEADERS "include/plugin.hpp"
    SOURCES "src/plugin.cpp"
    VERSION 2.0.0
    SOVERSION 2
    EXPORT
    INSTALL
)

vcvrack_add_module(MyModule
    SLUG MySlug
    SOURCES "src/MyModule.cpp"
    VERSION 0.0.1
    SOVERSION 0
    # INCLUDE_DIRS
    # $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    # $<INSTALL_INTERFACE:include>
    EXPORT
    INSTALL
)

#[==[Some fun with the helper functions...]==]

# vcvrack_get_plugin_slug()
# vcvrack_get_plugin_version()

# # Let's not *really* do this... but it's a useful test, for now
# message(STATUS "plugin.json: {")
# message(STATUS "  \"slug\": \"${VCVRACK_PLUGIN_SLUG}\"")
# message(STATUS "  \"version\": \"${VCVRACK_PLUGIN_VERSION}\"")
# message(STATUS "}")

# I don't like that design pattern above; and parsing the plugin.json in this
# way leads to too many "cool ideas" which end up as dead ends. Let's focus on
# the real tasks: the helper functions which create plugin and module targets.

# Golden rule of CMake: *don't* tie your user's hands. It gets too brittle
# when you enforce requirements! Keep it flexible.

# Remember, we want this to "just work" for most users, but on the other hand,
# we do *not* want to dictate things like project and target names, and so
# forth; that stuff is often done with all the best intentions, but ironically
# ends up being the source of most problems, especially for inexperienced users.
