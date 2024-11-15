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
 #define STONEYDSP_HAS_CATCH2 1
#else
 #warning "Can't find Catch2 headers for unit tests!"
#endif

#include "StoneyDSP.hpp"
#include "StoneyDSP/simd.hpp"

#ifndef STONEYDSP_SIMD_HPP_INCLUDED
 #error "Couldn't find 'StoneyDSP/simd.hpp'?"
#endif

#if STONEYDSP_HAS_CATCH2

// Tests go here...

TEST_CASE( "Vector<double, 2>", "[double_2]" ) {

    ::StoneyDSP::SIMD::double_2 dbl;

    REQUIRE(dbl.size == 2);
}

TEST_CASE( "Vector<float, 4>", "[float_4]" ) {

    ::StoneyDSP::SIMD::float_4 flt;

    REQUIRE(flt.size == 4);
}

TEST_CASE( "Vector<int8_t, 16>", "[int_8]" ) {

    StoneyDSP::SIMD::int8_16 integer;

    REQUIRE(integer.size == 16);
}

TEST_CASE( "Vector<int16_t, 8>", "[int_16]" ) {

    ::StoneyDSP::SIMD::int16_8 integer;

    REQUIRE(integer.size == 8);
}

TEST_CASE( "Vector<int32_t, 4>", "[int_32]" ) {

    ::StoneyDSP::SIMD::int32_4 integer;

    REQUIRE(integer.size == 4);
}

#if STONEYDSP_USING_INT64_2
TEST_CASE( "Vector<int64_t, 2>", "[int_64]" ) {

    ::StoneyDSP::SIMD::int64_2 integer;

    REQUIRE(integer.size == 2);
}
#endif

#endif
