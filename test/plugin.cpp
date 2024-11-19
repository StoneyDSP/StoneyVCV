#include "plugin.hpp"

#ifndef PLUGIN_HPP_INCLUDED
 #error "Couldn't find 'plugin.hpp'?"
#endif

#undef WARN

#if __has_include(<catch2/catch_test_macros.hpp>)
 #include <catch2/catch_test_macros.hpp>
 #define STONEYDSP_HAS_CATCH2 1
#elif __has_include("catch_amalgamated.hpp")
 // portable copy
 #include "catch_amalgamated.hpp"
 #include "../dep/Catch2/src/catch_amalgamated.cpp"
 #define STONEYDSP_HAS_CATCH2 1
#else
 #warning "Can't find Catch2 headers for unit tests!"
#endif

#if STONEYDSP_HAS_CATCH2

// Tests go here...

TEST_CASE( "placeholder", "[plugin]" ) {

    REQUIRE(true == true);
}

#endif // STONEYDSP_HAS_CATCH2
