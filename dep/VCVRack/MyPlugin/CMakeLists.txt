cmake_minimum_required(VERSION 3.14...3.31 FATAL_ERROR)

project(MyPlugin)

# Find rack-sdk package from CMAKE_TOOLCHAIN_FILE
find_package(rack-sdk 2.5.2 REQUIRED COMPONENTS dep core lib)

# Let's make a plugin!
vcvrack_add_plugin(
    SLUG MySlug
    HEADERS "include/plugin.hpp"
    SOURCES "src/plugin.cpp"
    VERSION 2.0.0
    SOVERSION 2
    EXPORT
    INSTALL
)

# Let's add a module to our plugin!
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
