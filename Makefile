# If RACK_DIR is not defined when calling the Makefile, default to two
# directories above
RACK_DIR ?= ../..

STONEYVCV_VERSION_MAJOR ?= 2
STONEYVCV_VERSION_MINOR ?= 0
STONEYVCV_VERSION_PATCH ?= 1
STONEYVCV_VERSION_TWEAK ?= 0

FLAGS += -DSTONEYVCV_VERSION_MAJOR=$(STONEYVCV_VERSION_MAJOR)
FLAGS += -DSTONEYVCV_VERSION_MINOR=$(STONEYVCV_VERSION_MINOR)
FLAGS += -DSTONEYVCV_VERSION_PATCH=$(STONEYVCV_VERSION_PATCH)
FLAGS += -DSTONEYVCV_VERSION_TWEAK=$(STONEYVCV_VERSION_TWEAK)

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
