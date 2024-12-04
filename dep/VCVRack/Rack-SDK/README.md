# VCVRack (unofficial CMake targets)

Unofficial CMake targets for [VCV Rack 2 SDK](https://vcvrack.com/manual/PluginDevelopmentTutorial).

Created by [StoneyDSP](https://github.com/StoneyDSP) (no affiliation with VCV Rack or its' creators).

- [What is this?](#what-is-this)
- [How does this work?](#how-does-this-work)
- [How can I use it?](#how-can-i-use-it)
- [Why?](#why)

## What is this?

This is an empty project containing primarily a `CMakeLists.txt` file and some license information.

The `CMakeLists.txt` file is designed to find a local copy of the Rack SDK using the variable named `RACK_DIR`; once found, the `CMakeLists.txt` file instructs CMake how to arrange the SDK files into logical CMake-style "targets".

Developers who are building plugins (suites of "modules") for VCV Rack 2 may use these "targets" in their own CMake projects, by using `find_package(rack-sdk)`, followed by `target_link_libraries(yourTarget PRIVATE unofficial-vcvrack::rack-sdk::lib)`, and such forth, in their project's `CMakeLists.txt` file.

This provides a way of setting up the C++ toolchain - the compiler, linker, and other tools - in a CMake project to create library files (and test executables) which are compatible with the VCV Rack 2 runtime (the Rack executable).

## How does this work?

This CMake project expects that you have an unmodified copy of the correct Rack 2 SDK on your filesystem, for the correct platform. The location of this Rack SDK copy is passed in to CMake when configuring the VCVRack project (`-DRACK_DIR="path/to/unzipped/Rack-SDK"`), and in return, CMake will generate three targets for linkage:

- `unofficial-vcvrack::rack-sdk::dep` - the header file contents of `<RACK_SDK>/dep/include`
- `unofficial-vcvrack::rack-sdk::core` - the header file contents of `<RACK_SDK>/include`
- `unofficial-vcvrack::rack-sdk::lib` - the `libRack.{so,dylib,dll,dll.a}` library file

All three targets are passed to CMake's "install" routine, which makes them relocatable within the context of the CMake buildsystem. This allows CMake to relocate and/or make copies of the SDK files, and do whatever it likes to do with them, without causing any breakages.

## How can I use it?

Download [VCV Rack](https://vcvrack.com/Rack) and the Rack SDK ([Windows x64](https://vcvrack.com/downloads/Rack-SDK-latest-win-x64.zip) / [Mac x64+ARM64](https://vcvrack.com/downloads/Rack-SDK-latest-mac-x64+arm64.zip) / [Linux x64](https://vcvrack.com/downloads/Rack-SDK-latest-lin-x64.zip)). Install VCV Rack, and unzip the SDK to any location on your local filesystem.

Clone this project and move into the VCVRack SDK directory:

```shell
git clone git@github.com:StoneyDSP/StoneyVCV.git && cd StoneyVCV/dep/VCVRack/Rack-SDK
```

Configure CMake with a source directory (`-S`), a build directory (`-B`), and the `RACK_DIR` variable (`-DRACK_DIR=`). Optionally, set a `CMAKE_INSTALL_PREFIX` if you want to examine the CMake `install` routine's output.

```shell
cmake                                     \
  -S .                                    \
  -B ./build                              \
  -DCMAKE_INSTALL_PREFIX="./install"      \
  -DRACK_DIR="path/to/unzipped/Rack-SDK"
```

Once configuration is complete, use the `--build` command on the build output directory:

```shell
cmake --build ./build
```

Optionally, to examine the CMake `install` routine's output, build the `ìnstall` target (it will populate `<current directory>/install` with the SDK headers, libraries, and relocatable CMake files):

```shell
cmake --build ./build --target install
```

## Why?

The above allows us to "acquire" the VCVRack SDK files as if it were a "package" dependency in another project (i.e., in a VCV Rack plugin project) via [vcpkg package manager for C and C++](https://github.com/microsoft/vcpkg).

To facilitate the above, [a vcpkg portfile can simply download the SDK zip file, unzip it, and pass along the unzipped output directory as `RACK_DIR`](https://github.com/StoneyDSP/StoneyVCV/blob/production/dep/vcpkg/ports/rack/2.5.2/portfile.cmake) when configuring this as a CMake package dependency...

### *NOTE*

The files under `share/` and `include/` are not actually in use; those are just reference material, and a helper to silence some warnings from vcpkg, respectively. Everything of interest is in either the `CMakeLists.txt`, `vcpkg.json`, or elsewhere...

## Further Reading

- [CMake Importing and Exporting Guide](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html)
