# StoneyVCV

StoneyDSP modules for [VCV Rack 2](https://vcvrack.com/).

---
[![windows](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/windows-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/windows-latest.yml)
[![macos](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/macos-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/macos-latest.yml)
[![ubuntu](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/ubuntu-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyVCV/actions/workflows/ubuntu-latest.yml)

---

## Contents

- [StoneyVCV](#stoneyvcv)
  - [Building StoneyVCV for VCV Rack 2](#build-and-install-stoneyvcv-for-vcv-rack-2-with-make)
  - [Further Reading](#further-reading)

## Build and Install StoneyVCV for VCV Rack 2 with Make

Complete the [Setting up your development environment](https://vcvrack.com/manual/Building#Setting-up-your-development-environment) section of the [VCV Rack Plugin Development guide](https://vcvrack.com/manual/Building).

StoneyVCV can be built in three ways:

- Download [VCV Rack](https://vcvrack.com/Rack) and the Rack SDK ([Windows x64](https://vcvrack.com/downloads/Rack-SDK-latest-win-x64.zip) / [Mac x64+ARM64](https://vcvrack.com/downloads/Rack-SDK-latest-mac-x64+arm64.zip) / [Linux x64](https://vcvrack.com/downloads/Rack-SDK-latest-lin-x64.zip)), and build StoneyVCV from any location. (Easiest/fastest.)

- [Build Rack from source](https://vcvrack.com/manual/Building#Building-Rack) and build StoneyVCV in the `plugins/` folder. (Recommended for advanced developers.)

- Build for all architectures with one command using the [VCV Rack Plugin Toolchain](https://github.com/VCVRack/rack-plugin-toolchain). Native (Linux) or Docker (Linux, Mac, Windows). *Recommended 15 GB disk space, 8 GB RAM.*

Download or clone the StoneyVCV source code, e.g.

```shell
git clone https://github.com/StoneyDSP/StoneyVCV.git
```

If using the Rack SDK, unzip it and set the `RACK_DIR` environment variable by running `export RACK_DIR=<Rack SDK dir>`.

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

Note: you may need [vcpkg](https://github.com/microsoft/vcpkg) to acquire some headers and libraries for developing, testing, and debugging StoneyVCV for VCV Rack2. StoneyVCV is built and tested using the (Rack 2.5.2 SDK for all platforms)[]. We recommend setting the `VCPKG_ROOT` and `RACK_DIR` environment variables in your shell, and launching your IDE from that shell, to ensure the IDE runs in the correct envvironment.

To configure the [StoneyDSP Library](https://github.com/StoneyDSP/StoneyDSP) with CMake and vcpkg:

```shell
cmake \
  -S . \
  -B build \
  -DVCPKG_ROOT=${VCPKG_ROOT}
  -DRACK_DIR=${RACK_DIR}
  -DSTONEYDSP_BUILD_TESTS=TRUE
```

To build the tests executable:

```shell
cmake \
  --build
  --target Tests_StoneyDSP
```

To run unit tests with [Catch2](https://github.com/catch-org/catch2) and CTest:

```shell
cd build
```

```shell
ctest \
  --rerun-failed \
  --output-on-failure \
  --verbose
```

[See the documentation](https://github.com/StoneyDSP/StoneyVCV/blob/production/docs/BuildingTheTestsForCatch2WithCMake.md) for more detailed information.

---

## Further Reading:

- [VCV Rack - Installing and Running](https://vcvrack.com/manual/Installing)
- [VCV Rack - Getting Started](https://vcvrack.com/manual/GettingStarted)
- [VCV Rack - Plugin Development Tutorial](https://vcvrack.com/manual/PluginDevelopmentTutorial)
- [VCV Rack - Plugin Guide](https://vcvrack.com/manual/PluginGuide)

---
