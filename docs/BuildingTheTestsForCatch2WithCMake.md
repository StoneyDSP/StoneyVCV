## Building the tests for Catch2 with CMake

StoneyVCV uses [Catch2](https://github.com/catch-org/Catch2) for unit testing.

Since Catch2 is so well-integrated with CMake, some CMake files exist in the StoneyVCV project tree - these are used for building the StoneyDSP library (for static linkage and distribution along with the plugin bundle), and for building the tests.

Catch2 creates an executable named 'tests' out of the unit test source files, which themselves are located under `test/`. Once built, the exectuable is run as a native command-line application.

Here is an example of how to build, and then run, the tests executable:

### 1. Configure tests with CMake

```shell
cmake -S . -B ./build -G Ninja -DSTONEYVCV_BUILD_TESTS=TRUE
```

### 2. Build tests with Ninja

```shell
$ cmake --build ./build
```

### 3. Run the tests executable

Linux/macOS:

```shell
$ ./build/tests

# output...

Randomness seeded to: 3545744703
===============================================================================
All tests passed (2 assertions in 1 test case)
```

Windows:

```powershell
> .\build\tests.exe

# output...

Randomness seeded to: 3545744703
===============================================================================
All tests passed (2 assertions in 1 test case)
```

### 4. Do more with the tests executable

```shell
$ ./build/tests --help

Catch2 v3.5.2
usage:
  tests [<test name|pattern|tags> ... ] options

where options are:
  -?, -h, --help                            display usage information
  -s, --success                             include successful tests in
                                            output
  -b, --break                               break into debugger on failure
  -e, --nothrow                             skip exception tests
  -i, --invisibles                          show invisibles (tabs, newlines)
  -o, --out <filename>                      default output filename
  -r, --reporter <name[::key=value]*>       reporter to use (defaults to
                                            console)
  -n, --name <name>                         suite name
  -a, --abort                               abort at first failure
  -x, --abortx <no. failures>               abort after x failures
  -w, --warn <warning name>                 enable warnings
  -d, --durations <yes|no>                  show test durations
  -D, --min-duration <seconds>              show test durations for tests
                                            taking at least the given number
                                            of seconds
  -f, --input-file <filename>               load test names to run from a
                                            file
  -#, --filenames-as-tags                   adds a tag for the filename
  -c, --section <section name>              specify section to run
  -v, --verbosity <quiet|normal|high>       set output verbosity
  --list-tests                              list all/matching test cases
  --list-tags                               list all/matching tags
  --list-reporters                          list all available reporters
  --list-listeners                          list all listeners
  --order <decl|lex|rand>                   test case order (defaults to
                                            decl)
  --rng-seed <'time'|'random-device'        set a specific seed for random
  |number>                                  numbers
  --colour-mode <ansi|win32|none            what color mode should be used as
  |default>                                 default
  --libidentify                             report name and version according
                                            to libidentify standard
  --wait-for-keypress <never|start|exit     waits for a keypress before
  |both>                                    exiting
  --skip-benchmarks                         disable running benchmarks
  --benchmark-samples <samples>             number of samples to collect
                                            (default: 100)
  --benchmark-resamples <resamples>         number of resamples for the
                                            bootstrap (default: 100000)
  --benchmark-confidence-interval           confidence interval for the
  <confidence interval>                     bootstrap (between 0 and 1,
                                            default: 0.95)
  --benchmark-no-analysis                   perform only measurements; do not
                                            perform any analysis
  --benchmark-warmup-time                   amount of time in milliseconds
  <benchmarkWarmupTime>                     spent on warming up each test
                                            (default: 100)
  --shard-count <shard count>               split the tests to execute into
                                            this many groups
  --shard-index <shard index>               index of the group of tests to
                                            execute (see --shard-count)
  --allow-running-no-tests                  Treat 'No tests run' as a success

For more detailed usage please see the project docs
```

---

## Further Reading:

- [Catch2 Documentation](https://github.com/catchorg/Catch2/blob/devel/docs/Readme.md)

---
