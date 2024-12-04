ifndef VCPKG_ROOT
$(error VCPKG_ROOT is not defined)
endif

include $(RACK_DIR)/arch.mk

ifdef ARCH_LIN
	HOST_TRIPLET ?= x64-linux
	TARGET_TRIPLET ?= x64-linux
	XDG_DATA_HOME ?= $(HOME)/.local/share
	RACK_USER_DIR ?= $(XDG_DATA_HOME)/Rack2
endif

ifdef ARCH_MAC
	HOST_TRIPLET ?= x64-osx
	TARGET_TRIPLET ?= x64-osx
	RACK_USER_DIR ?= $(HOME)/Library/Application Support/Rack2
	CODESIGN ?= codesign -f -s -
endif

ifdef ARCH_WIN
	HOST_TRIPLET ?= x64-mingw-dynamic
	TARGET_TRIPLET ?= x64-mingw-dynamic
	RACK_USER_DIR ?= $(LOCALAPPDATA)/Rack2
endif

PLUGINS_DIR := $(RACK_USER_DIR)/plugins-$(ARCH_OS)-$(ARCH_CPU)

VCPKG ?= vcpkg

CMAKE := cmake
CTEST := ctest
CPACK := cpack

GENERATOR ?= "Ninja"

BUILD_TYPE ?= Release

SOURCE_DIR ?= $(PWD)
BUILD_DIR ?= $(PWD)/build

configure:
	$(CMAKE) \
	-S "$(PWD)" \
	-B "$(BUILD_DIR)" \
	-DSTONEYVCV_BUILD_TESTS:BOOL=TRUE \
	-DSTONEYVCV_BUILD_MODULES:BOOL=TRUE \
	-DSTONEYVCV_BUILD_HP1:BOOL=TRUE \
	-DSTONEYVCV_BUILD_HP2:BOOL=TRUE \
	-DSTONEYVCV_BUILD_HP4:BOOL=TRUE \
	-DCMAKE_TOOLCHAIN_FILE:FILEPATH="$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake" \
	-DCMAKE_INSTALL_PREFIX:PATH=$(PLUGINS_DIR) \
	-DCMAKE_CONFIGURATION_TYPES_STRING="Debug;Release" \
	-DCMAKE_BUILD_TYPE:STRING=$(BUILD_TYPE) \
	-DVCPKG_HOST_TRIPLET:STRING=$(HOST_TRIPLET) \
	-DVCPKG_TARGET_TRIPLET:STRING=$(TARGET_TRIPLET) \
	-DVCPKG_OVERLAY_PORTS:FILEPATH=$(PWD)/dep/vcpkg/ports \
	-G $(GENERATOR) \
	--compile-no-warning-as-error \
	--no-warn-unused-cli \
	--fresh

tests: configure
	$(CMAKE) \
	--build $(BUILD_DIR) \
	--target tests


test: tests
	cd $(BUILD_DIR)
	$(CTEST) \
	--output-on-failure \
	--rerun-failed \
	--verbose
	cd $(SOURCE_DIR)
