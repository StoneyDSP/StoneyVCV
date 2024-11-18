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

TEST_CASE( "Vector<double_t, 2>", "[double_2]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(::StoneyDSP::SIMD::double_2) == 16);

        SECTION( "sizeof constructed instances" ) {

            // Call the default constructor
            ::StoneyDSP::SIMD::double_2 constructor_default;

            // Call the value constructor
            ::StoneyDSP::SIMD::double_2 constructor_value {
                (::StoneyDSP::double_t)0.0
            };

            // Call the scalar constructor
            ::StoneyDSP::SIMD::double_2 constructor_scalar {
                (::StoneyDSP::double_t)0.0,
                (::StoneyDSP::double_t)0.0
            };

            REQUIRE(sizeof(constructor_value) == sizeof(constructor_default));
            REQUIRE(sizeof(constructor_scalar) == sizeof(constructor_default));
        }

        ::StoneyDSP::SIMD::double_2 vector_of_two_doubles;

        SECTION( "sizeof class members" ) {
            // sizeof class members
            REQUIRE(vector_of_two_doubles.size == 2);
            REQUIRE(sizeof(vector_of_two_doubles.v) == 16);
        }
    }
}

TEST_CASE( "Vector<float_t, 4>", "[float_4]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::float_4) == 16);

        SECTION( "sizeof constructed instances" ) {

            // Call the default constructor
            ::StoneyDSP::SIMD::float_4 constructor_default;

            // Call the value constructor
            ::StoneyDSP::SIMD::float_4 constructor_value {
                (::StoneyDSP::float_t)0.0f
            };

            // Call the scalar constructor
            ::StoneyDSP::SIMD::float_4 constructor_scalar {
                (::StoneyDSP::float_t)0.0f,
                (::StoneyDSP::float_t)0.0f,
                (::StoneyDSP::float_t)0.0f,
                (::StoneyDSP::float_t)0.0f
            };

            REQUIRE(sizeof(constructor_value) == sizeof(constructor_default));
            REQUIRE(sizeof(constructor_scalar) == sizeof(constructor_default));
        }

        ::StoneyDSP::SIMD::float_4 vector_of_four_floats {
            (::StoneyDSP::float_t)0.0f
        };

        // sizeof class members
        REQUIRE(vector_of_four_floats.size == 4);
        REQUIRE(sizeof(vector_of_four_floats.v) == 16);
    }
}

TEST_CASE( "Vector<int8_t, 16>", "[int_8]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::int8_16) == 16);

        SECTION( "sizeof constructed instances" ) {

            // Call the default constructor
            ::StoneyDSP::SIMD::int8_16 constructor_default;

            // Call the value constructor
            ::StoneyDSP::SIMD::int8_16 constructor_value {
                (::StoneyDSP::int8_t)0
            };

            // Call the scalar constructor
            ::StoneyDSP::SIMD::int8_16 constructor_scalar {
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0,
                (::StoneyDSP::int8_t)0
            };

            REQUIRE(sizeof(constructor_value) == sizeof(constructor_default));
            REQUIRE(sizeof(constructor_scalar) == sizeof(constructor_default));
        }

        StoneyDSP::SIMD::int8_16 vector_of_sixteen_8bit_integers;

        // sizeof class members
        REQUIRE(vector_of_sixteen_8bit_integers.size == 16);
        REQUIRE(sizeof(vector_of_sixteen_8bit_integers.v) == 16);
    }
}

TEST_CASE( "Vector<int16_t, 8>", "[int_16]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::int16_8) == 16);

        SECTION( "sizeof constructed instances" ) {

            // Call the default constructor
            ::StoneyDSP::SIMD::int16_8 constructor_default;

            // Call the value constructor
            ::StoneyDSP::SIMD::int16_8 constructor_value {
                (::StoneyDSP::int16_t)0
            };

            // Call the scalar constructor
            ::StoneyDSP::SIMD::int16_8 constructor_scalar {
                (::StoneyDSP::int16_t)0,
                (::StoneyDSP::int16_t)0,
                (::StoneyDSP::int16_t)0,
                (::StoneyDSP::int16_t)0,
                (::StoneyDSP::int16_t)0,
                (::StoneyDSP::int16_t)0,
                (::StoneyDSP::int16_t)0,
                (::StoneyDSP::int16_t)0
            };

            REQUIRE(sizeof(constructor_value) == sizeof(constructor_default));
            REQUIRE(sizeof(constructor_scalar) == sizeof(constructor_default));
        }

        ::StoneyDSP::SIMD::int16_8 vector_of_eight_16bit_integers;

        // sizeof class members
        REQUIRE(vector_of_eight_16bit_integers.size == 8);
        REQUIRE(sizeof(vector_of_eight_16bit_integers.v) == 16);
    }
}

TEST_CASE( "Vector<int32_t, 4>", "[int_32]" ) {

    SECTION( "size tests" ) {

        // sizeof class
        REQUIRE(sizeof(StoneyDSP::SIMD::int32_4) == 16);

        SECTION( "sizeof constructed instances" ) {

            // Call the default constructor
            ::StoneyDSP::SIMD::int32_4 constructor_default;

            // Call the value constructor
            ::StoneyDSP::SIMD::int32_4 constructor_value {
                (::StoneyDSP::int32_t)0
            };

            // Call the scalar constructor
            ::StoneyDSP::SIMD::int32_4 constructor_scalar {
                (::StoneyDSP::int32_t)0,
                (::StoneyDSP::int32_t)0,
                (::StoneyDSP::int32_t)0,
                (::StoneyDSP::int32_t)0
            };
        }

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
        REQUIRE(sizeof(StoneyDSP::SIMD::int64_2) == 16);

        SECTION( "sizeof constructed instances" ) {

            // Call the default constructor
            ::StoneyDSP::SIMD::int64_2 constructor_default;

            // Call the value constructor
            ::StoneyDSP::SIMD::int64_2 constructor_value {
                (::StoneyDSP::int64_t)0
            };

            // Call the scalar constructor
            ::StoneyDSP::SIMD::int64_2 constructor_scalar {
                (::StoneyDSP::int64_t)0,
                (::StoneyDSP::int64_t)0
            };
        }

        ::StoneyDSP::SIMD::int64_2 vector_of_two_64bit_integers;

        // sizeof class members
        REQUIRE(vector_of_two_64bit_integers.size == 2);
        REQUIRE(sizeof(vector_of_two_64bit_integers.v) == 16);
    }
}
#endif

#endif
