/***************************************************************************//**
 * @file simd.hpp
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
// #include "StoneyDSP/simd.hpp"

#ifndef STONEYDSP_SIMD_HPP_INCLUDED
 #error "Couldn't find 'StoneyDSP/simd.hpp'?"
#endif

#if STONEYDSP_HAS_CATCH2

// Tests go here...

TEST_CASE( "Vector<double, 2>", "[double_2]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::double_2) == 16);

        StoneyDSP::SIMD::double_2 vector_of_two_doubles;

        // sizeof class members
        REQUIRE(vector_of_two_doubles.size == 2);
        REQUIRE(sizeof(vector_of_two_doubles.v) == 16);
    }
}

TEST_CASE( "Vector<float, 4>", "[float_4]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::float_4) == 16);

        ::StoneyDSP::SIMD::float_4 vector_of_four_floats;

        // sizeof class members
        REQUIRE(vector_of_four_floats.size == 4);
        REQUIRE(sizeof(vector_of_four_floats.v) == 16);
    }
}

TEST_CASE( "Vector<int8_t, 16>", "[int_8]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::int8_16) == 16);

        StoneyDSP::SIMD::int8_16 vector_of_sixteen_8bit_integers;

        // sizeof class members
        REQUIRE(vector_of_sixteen_8bit_integers.size == 16);
        REQUIRE(sizeof(vector_of_sixteen_8bit_integers.v) == 16);
    }
}

TEST_CASE( "Vector<int16_t, 8>", "[int_16]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::float_4) == 16);

        ::StoneyDSP::SIMD::int16_8 vector_of_eight_16bit_integers;

        // sizeof class members
        REQUIRE(vector_of_eight_16bit_integers.size == 8);
        REQUIRE(sizeof(vector_of_eight_16bit_integers.v) == 16);
    }
}

TEST_CASE( "Vector<int32_t, 4>", "[int_32]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::float_4) == 16);

        ::StoneyDSP::SIMD::int32_4 vector_of_four_32bit_integers;

        // sizeof class members
        REQUIRE(vector_of_four_32bit_integers.size == 4);
        REQUIRE(sizeof(vector_of_four_32bit_integers.v) == 16);
    }
}

#if STONEYDSP_USING_INT64_2
TEST_CASE( "Vector<int64_t, 2>", "[int_64]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::float_4) == 16);

        ::StoneyDSP::SIMD::int64_2 vector_of_two_64bit_integers;

        // sizeof class members
        REQUIRE(vector_of_two_64bit_integers.size == 2);
        REQUIRE(sizeof(vector_of_two_64bit_integers.v) == 16);
    }
}
#endif

#endif
