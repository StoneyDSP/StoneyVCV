/***************************************************************************//**
 * @file SIMD.hpp
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

#pragma once

#define STONEYDSP_SIMD_HPP_INCLUDED 1

#ifndef STONEYDSP_CORE_HPP_INCLUDED
 #include "StoneyDSP/Core.hpp"
#endif

//==============================================================================

/**
 * @brief This namespace describes the data types for using SIMD instructions
 * to "vectorize" some operations. It uses parallel CPU processing to optimize
 * the available operations; a "vector" is a register 128 bits wide, allowing
 * the following data types to be available for parallel processing:
 *
 * - `double_2` - 2x64-bit double-precision
 * - `float_4` - 4x32-bit floating point
 * - `int8_16` - 16x8-bit integer
 * - `int16_8` - 8x16-bit integer
 * - `int32_4` - 4x32-bit integer
 * - `int64_2` - 2x64-bit integer
 *
 * The namespace has the below requirements, which are imported in
 * `common.hpp` as shown using the below pre-processor logic:
 *
 * @example
 * ```cpp
 * #include <stdint.h>
 * #ifdef __SSE2__
 *  #include <emmintrin.h>
 * #else
 *  #warning SSE2 is not available. Code will not compile!
 * #endif
 *
 * #ifdef __SSE4_2__
 *  #include <nmmintrin.h>
 * #else
 *  #define SIMDE_ENABLE_NATIVE_ALIASES
 *  #include "<simde/x86/sse4.2.h>"
 * #endif
 * ```
 *
 * <mmintrin.h>  MMX
 * <xmmintrin.h> SSE
 * <emmintrin.h> SSE2
 * <pmmintrin.h> SSE3
 * <tmmintrin.h> SSSE3
 * <smmintrin.h> SSE4.1
 * <nmmintrin.h> SSE4.2
 * <ammintrin.h> SSE4A
 * <wmmintrin.h> AES
 * <immintrin.h> AVX, AVX2, FMA
 *
 * If building against VCV Rack's SDK, the required file shall be available
 * automatically.
 */

//==============================================================================

namespace StoneyDSP {
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

/**
 * @brief The `SIMD` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
namespace SIMD {
/** @addtogroup SIMD
 *  @{
 */


//==============================================================================

  /// @} group SIMD
} // namespace SIMD

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#include "StoneyDSP/SIMD/Vector.hpp"

// template <>
// struct Vector<float, 4> {

// public:

// 	using type = float;

//     constexpr static int size = 4;

// 	union {
//      /** @brief  */
// 		float_t v;
// 		/** @brief Accessing this array of scalars is slow and defeats the purpose of vectorizing. */
// 		float s[4];
// 	};

// 	/**
// 	 * @brief Constructs an uninitialized `Vector` object.
// 	 *
// 	 */
// 	Vector() = default;

// 	/**
//      * @brief Constructs a `Vector` object from a native `__m128` type.
//      */
// 	Vector(float_t v) : v(v) {}

// 	/**
// 	 * @brief Constructs a `Vector` object with all four elements equal to `x`.
// 	 *
// 	 * @param x
// 	 */
// 	Vector(float x) {
// 		v = _mm_set1_ps(x);
// 	}

//     /**
//      * @brief Constructs a `Vector` object from four scalars.
//      *
//      * @param x1
//      * @param x2
//      * @param x3
//      * @param x4
//      */
// 	Vector(float x1, float x2, float x3, float x4) {
// 		v = _mm_setr_ps(x1, x2, x3, x4);
// 	}

//     /**
//      * @brief Returns a `Vector` with all 0 bits.
//      */
// 	static Vector zero() {
// 		return Vector(_mm_setzero_ps());
// 	}

//     /**
//      * @brief Returns a `Vector` with all 1 bits.
//      */
// 	static Vector mask() {
// 		return Vector(_mm_castsi128_ps(_mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())));
// 	}

//     /**
//      * @brief Reads an array of 4 values.
//      * On little-endian machines (e.g. x86_64), the order is reversed, so `x[0]`
//      * corresponds to `vector.s[3]`.
// 	 */
// 	static Vector load(const float* x) {
// 		return Vector(_mm_loadu_ps(x));
// 	}

// 	/**
//      * Writes an array of 4 values.
//      * On little-endian machines (e.g. x86_64), the order is reversed, so `x[0]`
//      * corresponds to `vector.s[3]`.
// 	 */
// 	void store(float* x) {
// 		_mm_storeu_ps(x, v);
// 	}

// 	/**
//      * @brief Accessing vector elements individually is slow and defeats the
//      * purpose of vectorizing.
//      * However, this operator is convenient when writing simple serial code in a
//      * non-bottlenecked section.
// 	 */
// 	float& operator[](int i) {
// 		return s[i];
// 	}
// 	const float& operator[](int i) const {
// 		return s[i];
// 	}

//     static Vector add(float_t a, float_t b) {
//         return _mm_add_ps(a, b);
//     }

//     static Vector sub(float_t a, float_t b) {
//         return _mm_sub_ps(a, b);
//     }

//     static Vector mul(float_t a, float_t b) {
//         return _mm_mul_ps(a, b);
//     }

//     static Vector div(float_t a, float_t b) {
//         return _mm_div_ps(a, b);
//     }

//     static Vector sqrt(float_t x) {
//         return _mm_sqrt_ps(x);
//     }

//     static Vector min(float_t a, float_t b) {
//         return _mm_min_ps(a, b);
//     }

//     static Vector max(float_t a, float_t b) {
//         return _mm_max_ps(a, b);
//     }

//     static Vector ceil(float_t x) {
//         return _mm_ceil_ps(x);
//     }

//     static Vector floor(float_t x) {
//         return _mm_floor_ps(x);
//     }

//     static Vector round(float_t x) {
//         return _mm_round_ps(x);
//     }

// 	// Conversions
// 	Vector(Vector<int32_t, 4> a);
// 	// Casts
// 	static Vector cast(Vector<int32_t, 4> a);

// private:
//     // STONEYDSP_DECLARE_NON_COPYABLE(Vector)
//     // STONEYDSP_DECLARE_NON_MOVEABLE(Vector)
//     STONEYDSP_PREVENT_HEAP_ALLOCATION
// };
