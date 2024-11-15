/***************************************************************************//**
 * @file StoneyDSP.cpp
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @brief
 * @version 0.0.0
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * therights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/orsell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************************/

//==============================================================================

#if __has_include(<catch2/catch_test_macros.hpp>)
 #include <catch2/catch_test_macros.hpp>
 #define STONEYDSP_HAS_CATCH2 1
#elif __has_include("catch_amalgamated.hpp")
 #include "catch_amalgamated.hpp"
 #include "../dep/src/catch_amalgamated.cpp"
 #define STONEYDSP_HAS_CATCH2 1
#else
 #warning "Can't find Catch2 headers for unit tests!"
#endif

#include "StoneyDSP.hpp"

#ifndef STONEYDSP_HPP_INCLUDED
 #error "Couldn't find 'StoneyDSP.hpp'?"
#endif

#if STONEYDSP_HAS_CATCH2

// Tests go here...

TEST_CASE( "double_t", "[double_t]" ) {

    StoneyDSP::double_t typeof_double;

    SECTION( "size tests" ) {
        REQUIRE(sizeof(typeof_double) == 8);
    }
}

TEST_CASE( "float_t", "[float_t]" ) {

    StoneyDSP::float_t typeof_float;

    SECTION( "size tests" ) {
        REQUIRE(sizeof(typeof_float) == 4);
    }
}

TEST_CASE( "int8_t", "[int8_t]" ) {

    StoneyDSP::int8_t typeof_int8;

    SECTION( "size tests" ) {
        REQUIRE(sizeof(typeof_int8) == 1);
    }
}

TEST_CASE( "int16_t", "[int16_t]" ) {

    StoneyDSP::int16_t typeof_int16;

    SECTION( "size tests" ) {
        REQUIRE(sizeof(typeof_int16) == 2);
    }
}

TEST_CASE( "int32_t", "[int32_t]" ) {

    StoneyDSP::int32_t typeof_int32;

    SECTION( "size tests" ) {
        REQUIRE(sizeof(typeof_int32) == 4);
    }
}

#if STONEYDSP_USING_INT64_2
TEST_CASE( "int64_t", "[int64_t]" ) {

    StoneyDSP::int64_t typeof_int64;

    SECTION( "size tests" ) {
        REQUIRE(sizeof(typeof_int64) == 8);
    }
}
#endif

#endif
