# StoneyVCV

StoneyDSP modules for [VCV Rack 2](https://vcvrack.com/).

---
[![windows](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/windows-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/windows-latest.yml)
[![macos](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/macos-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/macos-latest.yml)
[![ubuntu](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/ubuntu-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/ubuntu-latest.yml)

---

## Quickstart

```shell
git clone https://github.com/StoneyDSP/StoneyVCV.git
```

```shell
make dep
```

```shell
make
```

```shell
make install
```

## Contents

- [StoneyVCV](#stoneyvcv)
  - [Quickstart](#quickstart)
  - [Requirements](#requirements)
  - [Build and Install StoneyVCV for VCV Rack 2 with Make](#build-and-install-stoneyvcv-for-vcv-rack-2-with-make)
  - [Develop, Test and Debug StoneyVCV for VCV Rack 2 with CMake and Catch2](#develop-test-and-deploy-stoneyvcv-for-vcv-rack-2-with-cmake-and-catch2)
  - [Additional Functionality](#additional-functionality)
    - [CMake Presets](#cmake-presets)
    - [Makefile Commands](#makefile-commands)
  - [Further Reading](#further-reading)

---

## Requirements

Complete the [Setting up your development environment](https://vcvrack.com/manual/Building#Setting-up-your-development-environment) section of the [VCV Rack Plugin Development guide](https://vcvrack.com/manual/Building). Briefly, you will need the following installations at minimum:

- VCV Rack 2 Free
- CMake
- Ninja
- GNU Make
- A Bash-like command line

StoneyVCV can be built in three ways:

1. Download [VCV Rack](https://vcvrack.com/Rack) and the Rack SDK ([Windows x64](https://vcvrack.com/downloads/Rack-SDK-latest-win-x64.zip) / [Mac x64+ARM64](https://vcvrack.com/downloads/Rack-SDK-latest-mac-x64+arm64.zip) / [Linux x64](https://vcvrack.com/downloads/Rack-SDK-latest-lin-x64.zip)), and build StoneyVCV from any location. (Easiest/fastest.)

2. [Build Rack from source](https://vcvrack.com/manual/Building#Building-Rack) and build StoneyVCV in the `plugins/` folder. (Recommended for advanced developers.)

3. Build for all architectures with one command using the [VCV Rack Plugin Toolchain](https://github.com/VCVRack/rack-plugin-toolchain). Native (Linux) or Docker (Linux, Mac, Windows). *Recommended 15 GB disk space, 8 GB RAM.*

---

## Build and Install StoneyVCV for VCV Rack 2 with Make

Download or clone the StoneyVCV source code, e.g.

```shell
git clone https://github.com/StoneyDSP/StoneyVCV.git
```

```shell
cd StoneyVCV
```

If using the Rack SDK workflow, unzip it and set the `RACK_DIR` environment variable by running `export RACK_DIR="path/to/unzipped/Rack-SDK"` in the terminal, before running the next commands.

*(NOTE: for Windows, use MSYS's 'mingw64' shell for these commands, and use unix-style transformed paths, such as '/c/Users/...')*

Build StoneyVCV.

```shell
make
```

Create the distributable plugin package.

```shell
make dist
```

The StoneyVCV package is created at `dist/<slug>-<version>-<os>-<cpu>.vcvplugin`.

Or you may build, package, and install StoneyVCV to your Rack user folder in one step.

```shell
make install
```

---

## Develop, Test, and Debug StoneyVCV for VCV Rack 2 with CMake and Catch2

Note: We recommend using [vcpkg](https://github.com/microsoft/vcpkg) to acquire some headers and libraries for developing, testing, and debugging StoneyVCV for VCV Rack2.

StoneyVCV is built and tested using the Rack SDK v2.5.2 for all platforms. We use vcpkg to fetch a fresh copy of the correct SDK files when the below commands are run as shown; the fetched SDK files are parsed into CMake targets, which interface with our testing targets.

We recommend setting the `VCPKG_ROOT` environment variable in your shell, and launching your IDE from that shell, to ensure the IDE runs in the correct environment. *(NOTE: for Windows, use MSYS's 'mingw64' shell for these commands, and use unix-style transformed paths, such as '/c/Users/...')*

We recommend *not* setting the `RACK_DIR` environment variable when running the below commands, as it may interfere with vcpkg.

Download or clone the StoneyVCV source code, e.g.

```shell
git clone https://github.com/StoneyDSP/StoneyVCV.git
```

```shell
cd StoneyVCV
```

Configure the StoneyDSP C++ library, Rack SDK, and Catch2 unit tests, along with StoneyVCV, with CMake and vcpkg:

```shell
cmake                                                                        \
  -S .                                                                       \
  -B ./build                                                                 \
  -DCMAKE_TOOLCHAIN_FILE="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"    \
  -DVCPKG_HOST_TRIPLET="x64-linux"                                           \
  -DVCPKG_TARGET_TRIPLET="x64-linux"                                         \
  -DSTONEYVCV_BUILD_TESTS=TRUE
```

*(NOTE: vckpg triplets should be one of: `"x64-linux"` for Linux, or `"x64-osx"` for MacOS, or `"x64-mingw-dynamic"` for Windows)*

To build the tests executable:

```shell
cmake                                                                        \
  --build ./build                                                            \
  --target Tests_StoneyVCV
```

To run unit tests with [Catch2](https://github.com/catch-org/catch2) and CTest:

```shell
cd build
```

```shell
ctest                                                                        \
  --rerun-failed                                                             \
  --output-on-failure                                                        \
  --verbose
```

```shell
cd ..
```

The unit tests executable should run in the terminal, and eventually indicate the success rate of all the tests combined.

## Additional Functionality

StoneyVCV packs some interesting features into its' design, including some well - thought-out and thoroughly tested build system features.

All Modules, tests, and even the plugin itself are all optionable, by applying different configurations to the C++ compiler pre-processor (i.e., what CMake's 'configure' stage means). Module versioning, dependency injection, downstream deployment integration, and much more has been considered throughout the development cycle of StoneyVCV.

To streamline much of these many options and configurations, we have provided some additional functionality which will brings a lot more control over the build (and deloyment, and debugging, and tests...) under smaller "macro"-like code signatures, with the use of tools such as CMake Presets and Makefile commands.

These additional functions provide a wide coverage of the full feature set of StoneyVCV, usually in just a single command line argument each.

### CMake Presets

The following CMake Presets are available for easy access to various configurations:

```txt
x64-windows-debug
x64-windows-release
x64-windows-debug-verbose
x64-windows-release-verbose
```
```txt
x64-linux-debug
x64-linux-release
x64-linux-debug-verbose
x64-linux-release-verbose
```
```txt
x64-osx-debug
x64-osx-release
x64-osx-debug-verbose
x64-osx-release-verbose
```

To use a CMake Preset, you can just pass the `--preset=` arg to CMake (no other args required):

```shell
cmake --preset x64-windows-release
```

*The above command will configure the plugin for Windows 64-bit in Release mode using the same settings that the Rack-SDK itself implements, respectively*

### Makefile commands

As a further helper, we have also organized our `Makefile` to *automatically detect* a relevant CMake Preset - if not manually chosen - and run CMake for us, using an *even simpler* command, which works on *all* platforms:

```shell
make configure
```

*The above command will configure the plugin for the host machine's platform; the CPU and OS are detected by the Rack-SDK itself, while the common environment variables `VERBOSE` and `DEBUG` may also be set or unset, to further adapt the behaviour of `make configure` according to your current environment.*

Further CMake actions and workflows can be triggered via `make` in a similarly environment-sensitive manner:

```shell
make reconfigure
```

*Clears the current CMake cache file (not dir!) and runs the configure step again*

```shell
make build
```

*Builds all currently-enabled CMake targets*


```shell
make test
```

*Runs CTest on the build output directory, executing any tests it finds (i.e., Catch2 unit tests)*


```shell
make package
```

*Creates a local directory (`./install`) containing a distributable package, unarchived*

The GitHub Workflows in our repository may be a useful reference, if any doubts.

---

Please feel welcome to submit pull requests of any changes you feel are useful, interesting, or appropriate, along with any technical notes and/or subjective reasoning; you may use [one of our PR templates](https://github.com/StoneyDSP/StoneyVCV/issues/new/choose) to help you get started - [all community contributions are gratefully recieved](https://github.com/StoneyDSP/StoneyVCV/blob/production/.github/CONTRIBUTING.md).

---

## Further Reading:

- [VCV Rack - Installing and Running](https://vcvrack.com/manual/Installing)
- [VCV Rack - Getting Started](https://vcvrack.com/manual/GettingStarted)
- [VCV Rack - Plugin Development Tutorial](https://vcvrack.com/manual/PluginDevelopmentTutorial)
- [VCV Rack - Plugin Guide](https://vcvrack.com/manual/PluginGuide)

---
