# VCV Rack API (CMake)

Build modules and plugins (suites of modules) for VCV Rack using the Rack SDK with CMake (and, optionally, vcpkg).

## `vcvrack_add_plugin()`

Should create a target named 'plugin', along with some aliases...

May only be used once per project (unless we can do better somehow)

```cmake
vcvrack_add_plugin(
    SLUG <slug>
    [BRAND] <brand>
    [VERSION] <major.minor.patch>
    [SOVERSION] <major>
    [HEADERS] [<files>...]
    [SOURCES] [<files>...]
    [INCLUDE_DIRS] [<dirs>...]
    [EXPORT]
    [INSTALL]
)
```

Example usage:

```cmake
vcvrack_add_plugin(
    NAME "MyPlugin"
    SLUG "MySlug"
    BRAND "MyBrand"
    VERSION 2.0.1
    HEADERS "include/plugin.hpp" "include/componentLibrary.hpp"
    SOURCES "src/plugin.cp"
)
```

## `vcvrack_add_module()`

```cmake
vcvrack_add_module(<name>
    SLUG <slug>
    [BRAND] <brand>
    [VERSION] <major.minor.patch>
    [SOVERSION] <major>
    [HEADERS] [<files>...]
    [SOURCES] [<files>...]
    [INCLUDE_DIRS] [<dirs>...]
    [EXPORT]
    [INSTALL]
)
```

## `vcvrack_add_sources()`

Add source files to an existing VCV Rack API target.

```cmake
vcvrack_add_sources( <name> [items1...] )
```

```cmake
vcvrack_add_sources( <name> [BASE_DIRS <dirs>] [items1...] )
```

```cmake
vcvrack_add_sources( <name> [<INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]] )
```

```cmake
vcvrack_add_sources( <name> [<INTERFACE|PUBLIC|PRIVATE> [BASE_DIRS [<dirs>...]] [items1...]...] )
```

##  `vcvrack_include_directories()`

## `vcvrack_add_compile_definitions()`

## `vcvrack_add_compile_options()`

## `vcvrack_add_linker_options()`
