# include ./dep.mk

# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -Iinclude -Idep/include -DSTONEYDSP_VERSION_MAJOR=0 -DSTONEYDSP_VERSION_MINOR=1
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += LICENSE
DISTRIBUTABLES += VERSION
DISTRIBUTABLES += $(wildcard presets)

## For building libstoneydsp & unit tests

VCPKG_JSON_FILES += vcpkg.json
VCPKG_JSON_FILES += vcpkg-configuration.json

vcpkg: $(VCPKG_JSON_FILES)
	vcpkg install

.PHONY: vcpkg

TEST_SOURCES += test/StoneyDSP/simd.cpp

## For running unit tests

test: $(TEST_SOURCES)
	cmake -S . -B build -DVCPKG_ROOT="${VCPKG_ROOT}" -G Ninja && \
	cmake --build build && \
	cd build && \
	./tests && \
	cd ..

.PHONY: test

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk
