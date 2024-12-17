# If RACK_DIR is not defined when calling the Makefile, default to two
# directories above, i.e., `Rack-SDK/plugins/<we are here>`
RACK_DIR ?= ../..

# Build version?
STONEYVCV_VERSION_MAJOR ?= 2
STONEYVCV_VERSION_MINOR ?= 0
STONEYVCV_VERSION_PATCH ?= 1
STONEYVCV_VERSION_TWEAK ?= 0

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
STONEYVCV_BUILD_VCA ?= $(STONEYVCV_EXPERIMENTAL)
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

include $(RACK_DIR)/arch.mk

ifdef ARCH_X64
	TRIPLET_ARCH := x64
endif

ifdef ARCH_ARM64
	TRIPLET_ARCH := arm64
endif

# Include deps
ifdef ARCH_WIN
	TRIPLET_OS := mingw-dynamic
endif

ifdef ARCH_LIN
	TRIPLET_OS := linux
endif

ifdef ARCH_MAC
	TRIPLET_OS := osx
endif

FLAGS += -I$(PWD)/build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include
LDFLAGS += -L$(PWD)/build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib

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
DISTRIBUTABLES += $(wildcard presets)

ifdef ARCH_X64
	PRESET_ARCH := x64
endif

ifdef ARCH_ARM64
	PRESET_ARCH := arm64
endif

ifdef ARCH_WIN
	PRESET_OS := windows
endif

ifdef ARCH_LIN
	PRESET_OS := linux
endif

ifdef ARCH_MAC
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

ifdef VERBOSE
	PRESET_VERBOSE := -verbose
endif

PRESET ?= $(PRESET_ARCH)-$(PRESET_OS)-$(PRESET_CONFIG)$(PRESET_VERBOSE)

reconfigure:
	cmake \
	--preset $(PRESET) \
  --fresh

configure:
	cmake \
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
  --install $(PWD)/build \
	--prefix $(PWD)/install

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

dep: reconfigure
