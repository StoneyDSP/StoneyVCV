# MyPlugin

A test project which aims to build a VCV Rack - compatible plugin and modules, by consuming the CMake Module `VCVRack` (final name tbc) and the CMake Package `rack-sdk`.

Ideally, a user will have a copy of the Rack SDK locally on their filesystem, and will either set the environment variable `RACK_DIR="/path/to/unzipped/Rack-SDK"`, and/or will pass the same location to CMake as `-DRACK_DIR="/path/to/unzipped/Rack-SDK"` as one of the arguments when cofiguring CMake.

Optionally, it is also possible to fetch the Rack SDK using vcpkg, negating the need to set any `RACK_DIR` - you can read more about this elsewhere...

To try building the test project, cd into this directory, and run:

```shell
cmake                                       \
  -S .                                      \
  -B ./build                                \
  -DRACK_DIR="/path/to/unzipped/Rack-SDK"

# example of successful output (linux)...

-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Linking with unofficial-vcvrack::rack-sdk::dep
-- Linking with unofficial-vcvrack::rack-sdk::core
-- Linking with unofficial-vcvrack::rack-sdk::lib
-- Linking with unofficial-vcvrack::rack-sdk
-- VCVRack.cmake v2.5.2
-- found jq: /usr/bin/jq
-- plguin.json: {
--   "slug": "MyPlugin"
--   "version": "2.0.1"
-- }
-- Configuring done (4.6s)
-- Generating done (0.0s)
-- Build files have been written to...
```

```shell
cmake --build ./build
```
