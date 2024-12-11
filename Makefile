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
	endif
endif

# Build tests?
STONEYVCV_BUILD_TESTS ?= 0

ifeq ($(STONEYVCV_BUILD_TESTS),1)
	FLAGS += -DSTONEYVCV_BUILD_TESTS=$(STONEYVCV_BUILD_TESTS)
endif

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
# SOURCES += $(wildcard src/StoneyVCV/*.cpp)
# SOURCES += src/HP4.cpp
# SOURCES += src/HP2.cpp
# SOURCES += src/HP1.cpp
# SOURCES += src/VCA.cpp
# SOURCES += src/LFO.cpp
# SOURCES += src/plugin.cpp

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
