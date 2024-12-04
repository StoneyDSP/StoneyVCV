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

# Build modules?
STONEYVCV_BUILD_MODULES ?= 1
STONEYVCV_BUILD_HP4 ?= $(STONEYVCV_BUILD_MODULES)
STONEYVCV_BUILD_HP2 ?= $(STONEYVCV_BUILD_MODULES)
STONEYVCV_BUILD_HP1 ?= $(STONEYVCV_BUILD_MODULES)

FLAGS += -DSTONEYVCV_BUILD_MODULES=$(STONEYVCV_BUILD_MODULES)
FLAGS += -DSTONEYVCV_BUILD_HP4=$(STONEYVCV_BUILD_HP4)
FLAGS += -DSTONEYVCV_BUILD_HP2=$(STONEYVCV_BUILD_HP2)
FLAGS += -DSTONEYVCV_BUILD_HP1=$(STONEYVCV_BUILD_HP1)

# Build tests?
STONEYVCV_BUILD_TESTS ?= 0

FLAGS += -DSTONEYVCV_BUILD_TESTS=$(STONEYVCV_BUILD_TESTS)

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -Iinclude -Idep/StoneyDSP/include
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about
# the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build
# system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/StoneyVCV/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
# DISTRIBUTABLES += include
DISTRIBUTABLES += res
DISTRIBUTABLES += LICENSE
DISTRIBUTABLES += VERSION
DISTRIBUTABLES += $(wildcard presets)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

# Include dep
include $(PWD)/dep.mk
