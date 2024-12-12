ifndef VCPKG_ROOT
$(error VCPKG_ROOT is not defined)
endif

GIT := git
VCPKG := vcpkg
CMAKE := cmake
CTEST := ctest
CPACK := cpack

# ifdef ARCH_LIN
# 	XDG_DATA_HOME ?= $(HOME)/.local/share
# 	RACK_USER_DIR ?= $(XDG_DATA_HOME)/Rack2
# endif

# ifdef ARCH_MAC
# 	RACK_USER_DIR ?= $(HOME)/Library/Application Support/Rack2
# 	CODESIGN ?= codesign -f -s -
# endif

# ifdef ARCH_WIN
# 	RACK_USER_DIR ?= $(LOCALAPPDATA)/Rack2
# endif

# PLUGINS_DIR := $(RACK_USER_DIR)/plugins-$(ARCH_OS)-$(ARCH_CPU)

# GENERATOR ?= "Ninja"

# BUILD_TYPE ?= Release

# SOURCE_DIR ?= $(PWD)
# BUILD_DIR ?= $(PWD)/build
