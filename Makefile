GIT := git
CURL := curl
ZIP := zip
UNZIP := unzip
JQ := jq

ifdef CROSS_COMPILE
	MACHINE := $(CROSS_COMPILE)
else
	MACHINE ?= $(shell $(CC) -dumpmachine)
endif

ifneq (,$(findstring x86_64-,$(MACHINE)))
	ARCH_X64 := 1
	ARCH_CPU := x64
else ifneq (,$(findstring arm64-,$(MACHINE)))
	ARCH_ARM64 := 1
	ARCH_CPU := arm64
else ifneq (,$(findstring aarch64-,$(MACHINE)))
	ARCH_ARM64 := 1
	ARCH_CPU := arm64
else
$(error Could not determine CPU architecture of $(MACHINE))
endif

ifneq (,$(findstring -darwin,$(MACHINE)))
	ARCH_MAC := 1
	ARCH_OS := mac
else ifneq (,$(findstring -mingw32,$(MACHINE)))
	ARCH_WIN := 1
	ARCH_OS := win
else ifneq (,$(findstring -linux,$(MACHINE)))
	ARCH_LIN := 1
	ARCH_OS := lin
else
$(error Could not determine operating system of $(MACHINE))
endif

ARCH_NAME := $(ARCH_OS)-$(ARCH_CPU)

# Fetch submodules
submodules:
	$(shell $(GIT) submodule update --init --recursive)

# Fetch vcpkg
./dep/vcpkg: submodules

# Bootstrap vcpkg
./dep/vcpkg/bootstrap-vcpkg.sh: ./dep/vcpkg

# Use vcpkg
vcpkg: ./dep/vcpkg/bootstrap-vcpkg.sh

VCPKG := vcpkg
VCPKG_ROOT ?= ./dep/vcpkg

# Rack-SDK
RACK_SDK_VERSION_MAJOR := 2
RACK_SDK_VERSION_MINOR ?= 5
RACK_SDK_VERSION_BUILD ?= 2
RACK_SDK_VERSION ?= $(RACK_SDK_VERSION_MAJOR).$(RACK_SDK_VERSION_MINOR).$(RACK_SDK_VERSION_BUILD)
RACK_SDK_PLATFORM ?= $(ARCH_OS)-$(ARCH_CPU)
RACK_SDK_FILENAME := Rack-SDK-$(RACK_SDK_VERSION)-$(RACK_SDK_PLATFORM).zip
RACK_SDK_URL := https://vcvrack.com/downloads/$(RACK_SDK_FILENAME)

./dep/$(RACK_SDK_FILENAME):
	$(shell $(CURL) $(RACK_SDK_URL) -o $@)

./dep/Rack-SDK: ./dep/$(RACK_SDK_FILENAME)
	$(UNZIP) ./dep/$(RACK_SDK_FILENAME) -d ./dep

# Target: 'make sdk'
sdk: ./dep/Rack-SDK

# If RACK_DIR is not defined when calling the Makefile, default to two
# directories above, i.e., `Rack-SDK/plugins/<we are here>`
RACK_DIR ?= ./dep/Rack-SDK

# StoneyVCV
STONEYVCV_VERSION_MAJOR ?= 2
STONEYVCV_VERSION_MINOR ?= 0
STONEYVCV_VERSION_PATCH ?= $(strip $(shell $(GIT) rev-list HEAD | wc -l))
STONEYVCV_VERSION_TWEAK ?= $(strip $(shell $(GIT) rev-parse HEAD))
STONEYVCV_VERSION_BUILD ?= $(strip $(shell $(GIT) rev-parse --short HEAD))
STONEYVCV_VERSION ?= $(STONEYVCV_VERSION_MAJOR).$(STONEYVCV_VERSION_MINOR).$(STONEYVCV_VERSION_PATCH).$(STONEYVCV_VERSION_TWEAK)

version-major:
	@echo $(STONEYVCV_VERSION_MAJOR)
version-minor:
	@echo $(STONEYVCV_VERSION_MINOR)
version-patch:
	@echo $(STONEYVCV_VERSION_PATCH)
version-tweak:
	@echo $(STONEYVCV_VERSION_TWEAK)
version-build:
	@echo $(STONEYVCV_VERSION_BUILD)
version:
	@echo $(STONEYVCV_VERSION)

version-package:
	@echo $(STONEYVCV_VERSION_MAJOR).$(STONEYVCV_VERSION_MINOR).$(STONEYVCV_VERSION_PATCH)-r$(STONEYVCV_VERSION_BUILD)

version-all: version-major version-minor version-patch version-tweak
	@echo $(STONEYVCV_VERSION)
	@echo $(STONEYVCV_VERSION_MAJOR).$(STONEYVCV_VERSION_MINOR).$(STONEYVCV_VERSION_PATCH)-r$(STONEYVCV_VERSION_BUILD)

FLAGS += -DSTONEYVCV_VERSION_MAJOR=$(STONEYVCV_VERSION_MAJOR)
FLAGS += -DSTONEYVCV_VERSION_MINOR=$(STONEYVCV_VERSION_MINOR)
FLAGS += -DSTONEYVCV_VERSION_PATCH=$(STONEYVCV_VERSION_PATCH)
FLAGS += -DSTONEYVCV_VERSION_TWEAK=$(STONEYVCV_VERSION_TWEAK)

# Experimental?
STONEYVCV_EXPERIMENTAL ?= 0

# Build plugin?
STONEYVCV_BUILD_PLUGIN ?= 1

# Build modules?
STONEYVCV_BUILD_MODULES ?= $(STONEYVCV_BUILD_PLUGIN)
STONEYVCV_BUILD_HP4 ?= $(STONEYVCV_BUILD_MODULES)
STONEYVCV_BUILD_HP2 ?= $(STONEYVCV_BUILD_MODULES)
STONEYVCV_BUILD_HP1 ?= $(STONEYVCV_BUILD_MODULES)
STONEYVCV_BUILD_VCA ?= $(STONEYVCV_BUILD_MODULES)
STONEYVCV_BUILD_LFO ?= $(STONEYVCV_EXPERIMENTAL)

ifeq ($(STONEYVCV_BUILD_PLUGIN),1)
	FLAGS += -DSTONEYVCV_BUILD_PLUGIN=$(STONEYVCV_BUILD_PLUGIN)
	SOURCES += src/StoneyVCV/plugin.cpp

	ifeq ($(STONEYVCV_BUILD_MODULES),1)
		FLAGS += -DSTONEYVCV_BUILD_MODULES=$(STONEYVCV_BUILD_MODULES)

		ifeq ($(STONEYVCV_BUILD_HP4),1)
			FLAGS += -DSTONEYVCV_BUILD_HP4=$(STONEYVCV_BUILD_HP4)
			SOURCES += src/StoneyVCV/HP4.cpp
		endif

		ifeq ($(STONEYVCV_BUILD_HP2),1)
			FLAGS += -DSTONEYVCV_BUILD_HP2=$(STONEYVCV_BUILD_HP2)
			SOURCES += src/StoneyVCV/HP2.cpp
		endif

		ifeq ($(STONEYVCV_BUILD_HP1),1)
			FLAGS += -DSTONEYVCV_BUILD_HP1=$(STONEYVCV_BUILD_HP1)
			SOURCES += src/StoneyVCV/HP1.cpp
		endif

		ifeq ($(STONEYVCV_BUILD_VCA),1)
			FLAGS += -DSTONEYVCV_BUILD_VCA=$(STONEYVCV_BUILD_VCA)
			SOURCES += src/StoneyVCV/VCA.cpp
		endif

		ifeq ($(STONEYVCV_BUILD_LFO),1)
			FLAGS += -DSTONEYVCV_BUILD_LFO=$(STONEYVCV_BUILD_LFO)
			SOURCES += src/StoneyVCV/LFO.cpp
		endif
	endif
endif

# Build tests?
STONEYVCV_BUILD_TESTS ?= 0

ifeq ($(STONEYVCV_BUILD_TESTS),1)
	FLAGS += -DSTONEYVCV_BUILD_TESTS=$(STONEYVCV_BUILD_TESTS)
endif

ifdef ARCH_X64
	TRIPLET_ARCH := x64
	PRESET_ARCH := x64
endif

ifdef ARCH_ARM64
	TRIPLET_ARCH := arm64
	PRESET_ARCH := arm64
endif

# Include deps
ifdef ARCH_WIN
	TRIPLET_OS := mingw-dynamic
	PRESET_OS := windows
endif

ifdef ARCH_LIN
	TRIPLET_OS := linux
	PRESET_OS := linux
endif

ifdef ARCH_MAC
	TRIPLET_OS := osx
	PRESET_OS := osx
endif

ifdef BUILD_TYPE
	PRESET_CONFIG := $(BUILD_TYPE)
else
	ifdef DEBUG
		PRESET_CONFIG := debug
	else
		PRESET_CONFIG := release
	endif
endif

# The macro NDEBUG controls whether assert() statements are active or not.
ifdef DEBUG
	CFLAGS += -Wall
	CFLAGS += -Wextra
	CFLAGS += -DNDEBUG
	CFLAGS += -D_DEBUG
endif

ifdef VERBOSE
	PRESET_VERBOSE := -verbose
endif

EXTERNAL_DEPS :=
EXTERNAL_DEPS += StoneyDSP
EXTERNAL_DEPS += Rack-SDK
EXTERNAL_DEPS += catch2

PKG_CONFIG_PATH := $(PWD)/build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/pkgconfig:$(PKG_CONFIG_PATH)

FLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(EXTERNAL_DEPS))
LDFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(EXTERNAL_DEPS))

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -I$(PWD)/include
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about
# the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build
# system.
LDFLAGS +=

# Add .cpp files to the build
# SOURCES += $(wildcard src/StoneyVCV/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
# DISTRIBUTABLES += include
DISTRIBUTABLES += res
DISTRIBUTABLES += LICENSE
DISTRIBUTABLES += VERSION
DISTRIBUTABLES += README.md
DISTRIBUTABLES += $(wildcard presets)

PRESET ?= $(PRESET_ARCH)-$(PRESET_OS)-$(PRESET_CONFIG)$(PRESET_VERBOSE)

reconfigure: sdk submodules
	VCPKG_ROOT=$(VCPKG_ROOT) cmake \
	--preset $(PRESET) \
  --fresh

configure: sdk submodules
	VCPKG_ROOT=$(VCPKG_ROOT) cmake \
	--preset $(PRESET)

build: configure
	cmake \
  --build $(PWD)/build \
	--preset $(PRESET)

test: build
	ctest \
  --test-dir $(PWD)/build \
	--preset $(PRESET)

package: test
	cmake \
  --build $(PWD)/build \
	--target $@

package_source: test
	cmake \
  --build $(PWD)/build \
	--target $@

workflow: vcpkg
	VCPKG_ROOT=$(VCPKG_ROOT) cmake \
  --workflow \
	--preset $(PRESET) \
	--fresh

source: configure
	cmake \
  --install $(PWD)/build \
	--prefix $(PWD)/dist \
	--component $@

# package: test
# 	cmake \
#   --install $(PWD)/build \
# 	--prefix $(PWD)/install

# Include the docs target
./build/docs/html: configure
	cd docs
	doxygen ./docs/Doxyfile
	cd $(PWD)

docs: $(PWD)/build/docs/html

# These are "main" Makefile targets which most Rack plugin devs expect
dep: reconfigure

$(RACK_DIR)/plugin.mk: sdk

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

# all: dep
# 	$(MAKE) -f $(RACK_DIR)/plugin.mk $@ -E RACK_DIR=$(RACK_DIR)

# clean:
# 	$(MAKE) -f $(RACK_DIR)/plugin.mk $@ -E RACK_DIR=$(RACK_DIR)
# 	$(MAKE) -f ./dep/Makefile $@
