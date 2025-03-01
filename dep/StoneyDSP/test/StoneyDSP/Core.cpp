/***************************************************************************//**
 * @file Core.cpp
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @brief Catch2 unit tests for "StoneyDSP/Core.cpp"
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
 // portable copy
 #include "catch_amalgamated.hpp"
 #include "../dep/Catch2/src/catch_amalgamated.cpp"
 #define STONEYDSP_HAS_CATCH2 1
#else
 #warning "Can't find Catch2 headers for unit tests!"
#endif

#include "StoneyDSP/Core.hpp"

#ifndef STONEYDSP_CORE_HPP_INCLUDED
 #error "Couldn't find 'StoneyDSP/Core.hpp'?"
#endif

#if STONEYDSP_HAS_CATCH2

// Tests go here...

TEST_CASE( "double_t", "[double_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(::StoneyDSP::double_t) == 8);
    }
}

TEST_CASE( "float_t", "[float_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(::StoneyDSP::float_t) == 4);
    }
}

TEST_CASE( "int8_t", "[int8_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(::StoneyDSP::int8_t) == 1);
    }
}

TEST_CASE( "uint8_t", "[uint8_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(::StoneyDSP::uint8_t) == 1);
    }
}

TEST_CASE( "int16_t", "[int16_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(::StoneyDSP::int16_t) == 2);
    }
}

TEST_CASE( "uint16_t", "[uint16_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(::StoneyDSP::uint16_t) == 2);
    }
}

TEST_CASE( "int32_t", "[int32_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(StoneyDSP::int32_t) == 4);
    }
}

TEST_CASE( "uint32_t", "[uint32_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(StoneyDSP::uint32_t) == 4);
    }
}

#if STONEYDSP_USING_INT64_2

TEST_CASE( "int64_t", "[int64_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(StoneyDSP::int64_t) == 8);
    }
}

TEST_CASE( "uint64_t", "[uint64_t]" ) {

    SECTION( "size tests" ) {
        REQUIRE(sizeof(StoneyDSP::uint64_t) == 8);
    }
}

#endif // STONEYDSP_USING_INT64_2

#endif // STONEYDSP_HAS_CATCH2
