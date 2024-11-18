/***************************************************************************//**
 * @file Vector.hpp
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

#define STONEYDSP_SIMD_VECTOR_HPP_INCLUDED 1

//==============================================================================

#ifndef STONEYDSP_CORE_HPP_INCLUDED
 #include "StoneyDSP/Core.hpp"
#endif

//==============================================================================

/**
 * @brief This file describes the data types for using SIMD instructions to
 * "vectorize" some operations. It uses parallel CPU processing to optimize
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
 * The file has the below requirements, which are imported in `common.hpp` as
 * shown using the below pre-processor logic:
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

using __DOUBLE_T = __m128d;
using __FLOAT_T = __m128;
using __INT_T = __m128i;

// using __UDOUBLE_T = __m128d_u;   // not supported on ARM....
// using __UFLOAT_T = __m128_u;     // not supported on ARM....
// using __UINT_T = __m128i_u;      // not supported on ARM....

//==============================================================================

/**
 * @brief A 128-bit register of two double-precision floating point numbers
 * `(2x64 = 128 bits)`.
 *
 */
using double_t = ::StoneyDSP::SIMD::__DOUBLE_T;

/**
 * @brief A 128-bit register of four single-precision floating point numbers
 * `(4x32 = 128 bits)`.
 *
 */
using float_t = ::StoneyDSP::SIMD::__FLOAT_T;

/**
 * @brief A 128-bit register of integer numbers
 * `(16x8, 8x16, 4x32, or 2x64 = 128 bits)`.
 */
using int_t = ::StoneyDSP::SIMD::__INT_T;

// not supported on ARM....

// /**
//  * @brief An unaligned 128-bit register of four single-precision floating
//  * point numbers `(4x32 = 128 bits)`.
//  */
// using ufloat_t = ::StoneyDSP::SIMD::__UFLOAT_T;

// /**
//  * @brief An unaligned 128-bit register of two double-precision floating
//  * point numbers `(2x64 = 128 bits)`.
//  */
// using udouble_t = ::StoneyDSP::SIMD::__UDOUBLE_T;

// /**
//  * @brief An unaligned 128-bit register of integer numbers
//  * `(16x8, 8x16, 4x32, or 2x64 = 128 bits)`.
//  */
// using uint_t = ::StoneyDSP::SIMD::__UINT_T;

//==============================================================================

/**
 * @brief The `Vector` template, for using SIMD instructions on intrinsic
 * data operations.
 *
 * @tparam TYPE
 * @tparam SIZE
 */
template <typename TYPE, ::StoneyDSP::size_t SIZE>
struct Vector;

//==============================================================================

/**
 * @brief A `Vector` of two double-precision floating point numbers
 * `(2x64 = 128 bits)`.
 *
 * @tparam
 */
template <>
struct Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>;

/**
 * @brief A `Vector` of four single-precision floating point numbers
 * `(4x32 = 128 bits)`.
 *
 * @tparam
 */
template <>
struct Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>;

/**
 * @brief A `Vector` of sixteen 8-bit integer numbers
 * `(2x64 = 128 bits)`.
 *
 * @tparam
 */
template <>
struct Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>;

/**
 * @brief A `Vector` of eight 16-bit integer numbers
 * `(2x64 = 128 bits)`.
 *
 * @tparam
 */
template <>
struct Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>;

/**
 * @brief A `Vector` of four 32-bit integer numbers
 * `(2x64 = 128 bits)`.
 *
 * @tparam
 */
template <>
struct Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>;

#if STONEYDSP_USING_INT64_2

/**
 * @brief A `Vector` of two 64-bit integer numbers
 * `(2x64 = 128 bits)`.
 *
 * @tparam
 */
template <>
struct Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>;

#endif

//==============================================================================

/**
 * @brief An array of two 64-bit double precision values.
 *
 */
using double_2 = Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>;

/**
 * @brief An array of four 32-bit floating point values.
 *
 */
using float_4 = Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>;

/**
 * @brief An array of sixteen 8-bit integer values.
 *
 */
using int8_16 = Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>;

/**
 * @brief An array of eight 16-bit integer values.
 *
 */
using int16_8 = Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>;

/**
 * @brief An array of four 32-bit integer values.
 *
 */
using int32_4 = Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>;

#if STONEYDSP_USING_INT64_2
/**
 * @brief An array of two 64-bit integer values.
 *
 */
using int64_2 = Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>;
#endif

//==============================================================================

template <>
struct Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> {
public:

	using type = ::StoneyDSP::double_t;

    /**
     * @brief The number of scalars contained by this `Vector`.
     */
    constexpr static ::StoneyDSP::size_t size = 2U;

    union {
        /**
         * @brief
         */
		::StoneyDSP::SIMD::double_t v;

        /**
         * @warning Accessing this array of scalars is slow and defeats the
         * purpose of vectorizing.
		 */
		::StoneyDSP::double_t s[2];
	};

    //==========================================================================

    /**
     * @brief @brief Constructs an uninitialized `Vector<double, 2>`.
     *
     */
	Vector() = default;

    /**
     * @brief Constructs a `Vector<double, 2>` from a `Vector<double, 2>`.
     *
     * @param v
     */
	Vector(::StoneyDSP::SIMD::double_t v) : v(v) {}

    /**
     * @brief Constructs a `Vector<double, 2>` with all elements set to `x`.
     *
     * @param x
     */
	Vector(::StoneyDSP::double_t x) {
		v = _mm_set1_pd(x);
	}

	/**
	 * @brief Constructs a `Vector<double, 2>` from two scalars.
	 *
	 * @param x1
	 * @param x2
	 */
	Vector(::StoneyDSP::double_t x1, ::StoneyDSP::double_t x2) {
		v = _mm_setr_pd(x1, x2);
	}

    //==========================================================================

    /**
     * @brief Reads from a `double_2` (an array of two double-precision
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[1]`.
     *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
     * @param x
     * @return `Vector<double, 2>`
     */
	static Vector load(const ::StoneyDSP::double_t* x) {
		return Vector(_mm_loadu_pd(x));
	}

	/**
	 * @brief Writes to a `double_2` (an array of two 64-bit double-precision
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[1]`.
	 *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
	 * @param x
	 */
	void store(::StoneyDSP::double_t* x) {
		_mm_storeu_pd(x, v);
	}

    //==========================================================================

    /**
     * @brief Returns a `double_2` with all bits set to `0`.
     *
     * @return `Vector<double, 2>`
     */
	static Vector zero() {
		return Vector(_mm_setzero_pd());
	}

    /**
     * @brief Returns a `double_2` with all bits set to `1`.
     *
     * @return `Vector<double, 2>`
     */
	static Vector mask() {
		return Vector(
            _mm_castsi128_pd(
                _mm_cmpeq_epi64(
                    _mm_setzero_si128(),
                    _mm_setzero_si128()
                )
            )
        );
	}

    //==========================================================================

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return double&
     */
	::StoneyDSP::double_t& operator[](::StoneyDSP::size_t i) {
		return s[i];
	}

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return const double&
     */
	const ::StoneyDSP::double_t& operator[](::StoneyDSP::size_t i) const {
		return s[i];
	}

    // Conversions =============================================================

    Vector(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    Vector(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
    Vector(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
	Vector(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    Vector(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

	// Casts ===================================================================

    static Vector cast(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    static Vector cast(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
    static Vector cast(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
	static Vector cast(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    static Vector cast(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

    //==========================================================================

private:

    STONEYDSP_PREVENT_HEAP_ALLOCATION

};

//==============================================================================

template <>
struct Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> {
public:

	using type = ::StoneyDSP::float_t;

    /**
     * @brief The number of scalars contained by this `Vector`.
     */
    constexpr static ::StoneyDSP::size_t size = 4U;

    union {
        /**
         * @brief
         */
		::StoneyDSP::SIMD::float_t v;

        /**
         * @warning Accessing this array of scalars is slow and defeats the
         * purpose of vectorizing.
		 */
		::StoneyDSP::float_t s[4];
	};

    //==========================================================================

    /**
     * @brief Constructs an uninitialized `Vector<float_t, 4>`.
     *
     */
	Vector() = default;

	/**
	 * @brief Constructs a `Vector<float_t, 4>` from a `Vector<float_t, 4>`.
	 *
	 * @param v
	 */
	Vector(::StoneyDSP::SIMD::float_t v) : v(v) {}

    /**
     * @brief Constructs a `Vector<float, 4>` with all elements set to `x`.
     *
     * @param x
     */
	Vector(::StoneyDSP::float_t x) {
		v = _mm_set1_ps(x);
	}

	/**
	 * @brief Constructs a `Vector<float, 4>` from four scalars.
	 *
	 * @param x1
	 * @param x2
	 * @param x3
	 * @param x4
	 */
	Vector(
        ::StoneyDSP::float_t x1,
        ::StoneyDSP::float_t x2,
        ::StoneyDSP::float_t x3,
        ::StoneyDSP::float_t x4
    ) {
		v = _mm_setr_ps(x1, x2, x3, x4);
	}

    //==========================================================================

    /**
     * @brief Reads from a `float_4` (an array of four 32-bit floating-point
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[3]`.
     *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
     * @param x
     * @return `Vector<float, 4>`
     */
	static Vector load(const ::StoneyDSP::float_t *x) {
		return Vector(_mm_loadu_ps(x));
	}

	/**
	 * @brief Writes to a `float_4` (an array of four 32-bit floating-point
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[3]`.
	 *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
	 * @param x
	 */
	void store(::StoneyDSP::float_t *x) {
		_mm_storeu_ps(x, v);
	}

    //==========================================================================

    /**
     * @brief Returns a `float_4` with all bits set to `0`.
     *
     * @return `Vector<float, 4>`
     */
	static Vector zero() {
		return Vector(_mm_setzero_ps());
	}

    /**
     * @brief Returns a `float_4` with all bits set to `1`.
     *
     * @return `Vector<float, 4>`
     */
	static Vector mask() {
		return Vector(
            _mm_castsi128_ps(
                _mm_cmpeq_epi32(
                    _mm_setzero_si128(),
                    _mm_setzero_si128()
                )
            )
        );
	}

    //==========================================================================

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return float&
     */
	::StoneyDSP::float_t& operator[](::StoneyDSP::size_t i) {
		return s[i];
	}

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return const float&
     */
	const ::StoneyDSP::float_t& operator[](::StoneyDSP::size_t i) const {
		return s[i];
	}

    // Conversions =============================================================

    Vector(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    Vector(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
    Vector(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
	Vector(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    Vector(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

	// Casts ===================================================================

    static Vector cast(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    static Vector cast(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
    static Vector cast(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
	static Vector cast(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    static Vector cast(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

    //==========================================================================

private:

    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

//==============================================================================

template <>
struct Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>
{
public:

	using type = ::StoneyDSP::int8_t;

    /**
     * @brief The number of scalars contained by this `Vector`.
     */
    constexpr static ::StoneyDSP::size_t size = 16U;

    union {
        /**
         * @brief
         */
		::StoneyDSP::SIMD::int_t v;

        /**
         * @warning Accessing this array of scalars is slow and defeats the
         * purpose of vectorizing.
		 */
		::StoneyDSP::int8_t s[16];
	};

    //==========================================================================

    /**
     * @brief Constructs an uninitialized `Vector<int8_t, 16>`.
     *
     */
	Vector() = default;

	/**
	 * @brief Constructs a `Vector<int8_t, 16>` from a `Vector<int8_t, 16>`.
	 *
	 * @param v
	 */
	Vector(::StoneyDSP::SIMD::int_t v) : v(v) {}

    /**
     * @brief Constructs a `Vector<int8_t, 16>` with all elements set to `x`.
     *
     * @param x
     */
	Vector(::StoneyDSP::int8_t x) {
		v = _mm_set1_epi8(x);
	}

	/**
	 * @brief Constructs a `Vector<int8_t, 16>` from sixteen scalars.
	 *
	 * @param x1
	 * @param x2
	 * @param x3
	 * @param x4
	 * @param x5
	 * @param x6
	 * @param x7
	 * @param x8
	 * @param x9
	 * @param x10
	 * @param x11
	 * @param x12
	 * @param x13
	 * @param x14
	 * @param x15
	 * @param x16
	 */
	Vector(
        ::StoneyDSP::int8_t x1,
        ::StoneyDSP::int8_t x2,
        ::StoneyDSP::int8_t x3,
        ::StoneyDSP::int8_t x4,
        ::StoneyDSP::int8_t x5,
        ::StoneyDSP::int8_t x6,
        ::StoneyDSP::int8_t x7,
        ::StoneyDSP::int8_t x8,
        ::StoneyDSP::int8_t x9,
        ::StoneyDSP::int8_t x10,
        ::StoneyDSP::int8_t x11,
        ::StoneyDSP::int8_t x12,
        ::StoneyDSP::int8_t x13,
        ::StoneyDSP::int8_t x14,
        ::StoneyDSP::int8_t x15,
        ::StoneyDSP::int8_t x16
    ) {
		v = _mm_setr_epi8(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16);
	}

    //==========================================================================

    /**
     * @brief Reads from an `int8_16` (an array of sixteen 8-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[15]`.
     *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
     * @param x
     * @return `Vector<int8_t, 16>`
     */
    static Vector load(const ::StoneyDSP::int8_t* x) {
#if defined (STONEYDSP_GCC) || defined (STONEYDSP_MAC)  // TODO: Check Apple platforms other than Clang
		// HACK
		// Use _mm_loadu_si128() because GCC doesn't support _mm_loadu_si8()
		return Vector(_mm_loadu_si128((const __m128i*) x));
#else
        return Vector(_mm_loadu_si8(x));
#endif
	}

    /**
	 * @brief Writes to an `int8_16` (an array of sixteen 8-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[15]`.
     *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
	 *
	 * @param x
	 */
	void store(::StoneyDSP::int8_t* x) {
#if defined (STONEYDSP_GCC) || defined (STONEYDSP_MAC) // TODO: Check Apple platforms other than Clang
		// HACK
		// Use `_mm_storeu_si128()` because GCC doesn't support
        // `_mm_storeu_si8()`
		_mm_storeu_si128((__m128i*) x, v);
#else
        _mm_storeu_si8(x, v);
#endif
	}

    //==========================================================================

    /**
     * @brief Returns an `int8_16` with all bits set to `0`.
     *
     * @return `Vector<int8_t, 16>`
     */
	static Vector zero() {
		return Vector(_mm_setzero_si128());
	}

    /**
     * @brief Returns a `int8_16` with all bits set to `1`.
     *
     * @return `Vector<int8_t, 16>`
     */
	static Vector mask() {
		return Vector(_mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128()));
	}

    //==========================================================================

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return int8_t&
     */
	::StoneyDSP::int8_t& operator[](::StoneyDSP::size_t i) {
		return s[i];
	}

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return const int8_t&
     */
	const ::StoneyDSP::int8_t& operator[](::StoneyDSP::size_t i) const {
		return s[i];
	}

    // Conversions =============================================================

    Vector(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    Vector(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    Vector(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
	Vector(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    Vector(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

	// Casts ===================================================================

    static Vector cast(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    static Vector cast(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    static Vector cast(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
	static Vector cast(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    static Vector cast(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

    //==========================================================================

private:

    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

//==============================================================================

template <>
struct Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> {
public:

	using type = ::StoneyDSP::int16_t;

    /**
     * @brief The number of scalars contained by this `Vector`.
     */
    constexpr static ::StoneyDSP::size_t size = 8U;

    union {
        /**
         * @brief
         */
		::StoneyDSP::SIMD::int_t v;

        /**
         * @warning Accessing this array of scalars is slow and defeats the
         * purpose of vectorizing.
		 */
		::StoneyDSP::int16_t s[8];
	};

    //==========================================================================

    /**
     * @brief Constructs an uninitialized `Vector<int16_t, 8>`.
     *
     */
	Vector() = default;

	/**
	 * @brief Constructs a `Vector<int16_t, 8>` from a `Vector<int16_t, 8>`.
	 *
	 * @param v
	 */
	Vector(::StoneyDSP::SIMD::int_t v) : v(v) {}

    /**
     * @brief Constructs a `Vector<int16_t, 8>` with all elements set to `x`.
     *
     * @param x
     */
	Vector(::StoneyDSP::int16_t x) {
		v = _mm_set1_epi16(x);
	}

	/**
	 * @brief Constructs a `Vector<int16_t, 8>` from eight scalars.
	 *
	 * @param x1
	 * @param x2
	 * @param x3
	 * @param x4
	 * @param x5
	 * @param x6
	 * @param x7
	 * @param x8
	 */
	Vector(
        ::StoneyDSP::int16_t x1,
        ::StoneyDSP::int16_t x2,
        ::StoneyDSP::int16_t x3,
        ::StoneyDSP::int16_t x4,
        ::StoneyDSP::int16_t x5,
        ::StoneyDSP::int16_t x6,
        ::StoneyDSP::int16_t x7,
        ::StoneyDSP::int16_t x8
    ) {
		v = _mm_setr_epi16(x1, x2, x3, x4, x5, x6, x7, x8);
	}

    //==========================================================================

    /**
     * @brief Reads from an `int16_8` (an array of eight 16-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[7]`.
     *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
     * @param x
     * @return `Vector<int16_t, 8>`
     */
    static Vector load(const ::StoneyDSP::int16_t* x) {
#if STONEYDSP_GCC && defined (__GNUC__)
		// HACK
		// Use `_mm_loadu_si128()` because GCC doesn't support
        // `_mm_loadu_si16()`
		return Vector(_mm_loadu_si128((const __m128i*) x));
#else
        return Vector(_mm_loadu_si16(x));
#endif
	}

    /**
	 * @brief Writes to an `int16_8` (an array of eight 16-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[7]`.
	 *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
	 * @param x
	 */
	void store(::StoneyDSP::int16_t* x) {
#if STONEYDSP_GCC && defined (__GNUC__)
		// HACK
		// Use `_mm_storeu_si128()` because GCC doesn't (??) support
        // `_mm_storeu_si16()`
		_mm_storeu_si128((__m128i*) x, v);
#else
        _mm_storeu_si16(x, v);
#endif
	}

    //==========================================================================

    /**
     * @brief Returns an `int16_8` with all bits set to `0`.
     *
     * @return `Vector<int16_t, 8>`
     */
	static Vector zero() {
		return Vector(_mm_setzero_si128());
	}

    /**
     * @brief Returns a `int16_8` with all bits set to `1`.
     *
     * @return `Vector<int16_t, 8>`
     */
	static Vector mask() {
		return Vector(
            _mm_cmpeq_epi32(
                _mm_setzero_si128(),
                _mm_setzero_si128()
            )
        );
	}

    //==========================================================================

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return int16_t&
     */
	::StoneyDSP::int16_t& operator[](::StoneyDSP::size_t i) {
		return s[i];
	}

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return const int16_t&
     */
	const ::StoneyDSP::int16_t& operator[](::StoneyDSP::size_t i) const {
		return s[i];
	}

    // Conversions =============================================================

    Vector(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    Vector(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    Vector(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
	Vector(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    Vector(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

	// Casts ===================================================================

    static Vector cast(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    static Vector cast(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    static Vector cast(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
	static Vector cast(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);
#if STONEYDSP_USING_INT64_2
    static Vector cast(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

    //==========================================================================

private:

    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

//==============================================================================

template <>
struct Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>
{
public:

	using type = ::StoneyDSP::int32_t;

    /**
     * @brief The number of scalars contained by this `Vector`.
     */
    constexpr static ::StoneyDSP::size_t size = 4U;

        union {
        /**
         * @brief
         */
		::StoneyDSP::SIMD::int_t v;

        /**
         * @warning Accessing this array of scalars is slow and defeats the
         * purpose of vectorizing.
		 */
		::StoneyDSP::int32_t s[4];
	};

    //==========================================================================

    /**
     * @brief Constructs an uninitialized `Vector<int32_t, 4>`.
     *
     */
	Vector() = default;

	/**
	 * @brief Constructs a `Vector<int32_t, 4>` from a `Vector<int32_t, 4>`.
	 *
	 * @param v
	 */
	Vector(::StoneyDSP::SIMD::int_t v) : v(v) {}

    /**
     * @brief Constructs a `Vector<int32_t, 4>` with all elements set to `x`.
     *
     * @param x
     */
	Vector(::StoneyDSP::int32_t x) {
		v = _mm_set1_epi32(x);
	}

	/**
	 * @brief Constructs a `Vector<int32_t, 4>` from four scalars.
	 *
	 * @param x1
	 * @param x2
	 * @param x3
	 * @param x4
	 */
	Vector(
        ::StoneyDSP::int32_t x1,
        ::StoneyDSP::int32_t x2,
        ::StoneyDSP::int32_t x3,
        ::StoneyDSP::int32_t x4)
    {
		v = _mm_setr_epi32(x1, x2, x3, x4);
	}

    //==========================================================================

    /**
     * @brief Reads from an `int32_4` (an array of four 32-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[3]`.
     *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
     * @param x
     * @return `Vector<int32_t, 4>`
     */
    static Vector load(const ::StoneyDSP::int32_t* x) {
#if STONEYDSP_GCC && defined (__GNUC__)
		// HACK
		// Use `_mm_loadu_si128()` because GCC doesn't (??) support
        // `_mm_loadu_si32()`
		return Vector(_mm_loadu_si128((const __m128i*) x));
#else
		return Vector(_mm_loadu_si32(x));
#endif
	}

    /**
	 * @brief Writes to an `int32_4` (an array of four 32-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[3]`.
	 *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
	 * @param x
	 */
	void store(::StoneyDSP::int32_t* x) {
#if STONEYDSP_GCC && defined (__GNUC__)
		// HACK
		// Use `_mm_storeu_si128()` because GCC doesn't (??) support
        // `_mm_storeu_si32()`
        _mm_storeu_si128((__m128i*) x, v);
#else
		_mm_storeu_si32(x, v);
#endif
	}

    //==========================================================================

    /**
     * @brief Returns an `int32_4` with all bits set to `0`.
     *
     * @return `Vector<int32_t, 4>`
     */
	static Vector zero() {
		return Vector(_mm_setzero_si128());
	}

    /**
     * @brief Returns a `int32_4` with all bits set to `1`.
     *
     * @return `Vector<int32_t, 4>`
     */
	static Vector mask() {
		return Vector(
            _mm_cmpeq_epi32(
                _mm_setzero_si128(),
                _mm_setzero_si128()
            )
        );
	}

    //==========================================================================

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return int32_t&
     */
	::StoneyDSP::int32_t& operator[](::StoneyDSP::size_t i) {
		return s[i];
	}

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return const int32_t&
     */
	const ::StoneyDSP::int32_t& operator[](::StoneyDSP::size_t i) const {
		return s[i];
	}

    // Conversions =============================================================

    Vector(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    Vector(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    Vector(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
	Vector(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
#if STONEYDSP_USING_INT64_2
    Vector(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

	// Casts ===================================================================

    static Vector cast(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    static Vector cast(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    static Vector cast(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
	static Vector cast(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
#if STONEYDSP_USING_INT64_2
    static Vector cast(Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a);
#endif

    //==========================================================================

private:

    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

//==============================================================================

#if STONEYDSP_USING_INT64_2

template <>
struct Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>
{
public:

	using type = ::StoneyDSP::int64_t;

    /** @brief The number of scalars contained by this `Vector`. */
    constexpr static ::StoneyDSP::size_t size = 2;

    /**
     * @brief Constructs an uninitialized `Vector<int64_t, 2>`.
     */
	Vector() = default;

	/**
     * @brief Constructs a `Vector<int64_t, 2>` from a `Vector<int64_t, 2>`.
     *
     */
	Vector(::StoneyDSP::SIMD::int_t v) : v(v) {}

    /**
     * @brief Constructs a `Vector<int64_t, 2>` with all elements set to `x`.
     *
     * @param x
     */
	Vector(::StoneyDSP::int64_t x) {
		v = _mm_set1_epi64(x);
	}

	/**
	 * @brief Constructs a `Vector<int64_t, 2>` from two scalars.
	 *
	 * @param x1
	 * @param x2
	 */
	Vector(::StoneyDSP::int64_t x1, ::StoneyDSP::int64_t x2) {
		v = _mm_setr_epi64(x1, x2);
	}

    union {
        /**
         * @brief
         */
		::StoneyDSP::SIMD::int_t v;

        /**
         * @warning Accessing this array of scalars is slow and defeats the
         * purpose of vectorizing.
		 */
		::StoneyDSP::int64_t s[2];
	};

    //==========================================================================

    /**
     * @brief Reads from an `int64_2` (an array of two 64-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[1]`.
     *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
     * @param x
     * @return `Vector<int64_t, 2>`
     */
    static Vector load(const ::StoneyDSP::int32_t* x) {
#if STONEYDSP_GCC && defined (__GNUC__)
		// HACK
		// Use `_mm_loadu_si128()` because GCC doesn't (??) support
        // `_mm_loadu_si64()`
        return Vector(_mm_loadu_si128((const __m128i*) x));
#else
		return Vector(_mm_loadu_si64(x));
#endif
	}

    /**
	 * @brief Writes to an `int64_2` (an array of two 64-bit integer
     * values).
     *
     * @note On little-endian machines (e.g. x86_64), the order is reversed,
     * so `x[0]` corresponds to `vector.s[1]`.
	 *
     * Your code may check the helper macros `STONEYDSP_LITTLE_ENDIAN` and/or
     * `STONEYDSP_BIG_ENDIAN` to determine the endian-ness of the current
     * machine.
     *
	 * @param x
	 */
	void store(::StoneyDSP::int64_t* x) {
#if STONEYDSP_GCC && defined (__GNUC__)
		// HACK
		// Use `_mm_storeu_si128()` because GCC doesn't (??) support
        // `_mm_storeu_si64()`
        _mm_storeu_si64((__m128i*) x, v);
#else
		_mm_storeu_si128(x, v);
#endif
	}

    //==========================================================================

    /**
     * @brief Returns an `int64_2` with all bits set to `0`.
     *
     * @return `Vector<int64_t, 2>`
     */
	static Vector zero() {
		return Vector(_mm_setzero_si128());
	}

    /**
     * @brief Returns a `int64_2` with all bits set to `1`.
     *
     * @return `Vector<int64_t, 2>`
     */
	static Vector mask() {
		return Vector(
            _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())
        );
	}

    //==========================================================================

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return int64_t&
     */
	::StoneyDSP::int64_t& operator[](::StoneyDSP::size_t i) {
		return s[i];
	}

    /**
     * @warning Accessing vector elements individually is slow and defeats the
     * purpose of vectorizing.
     * However, this operator is convenient when writing simple serial code in
     * a non-bottlenecked section.
     *
     * @param i
     * @return const int64_t&
     */
	const ::StoneyDSP::int64_t& operator[](::StoneyDSP::size_t i) const {
		return s[i];
	}

    // Conversions =============================================================

    Vector(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    Vector(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    Vector(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
	Vector(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
    Vector(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);

	// Casts ===================================================================

    static Vector cast(Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a);
    static Vector cast(Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a);
    static Vector cast(Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a);
	static Vector cast(Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a);
    static Vector cast(Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a);

    //==========================================================================

private:

    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

#endif

// Conversions - double_2 ======================================================

inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	v = _mm_cvtps_pd(a.v);
}
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	v = _mm_cvtepi32_pd(a.v);
}
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	v = _mm_cvtepi32_pd(a.v);
}
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	v = _mm_cvtepi32_pd(a.v);
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	v = _mm_cvtepi32_pd(a.v);
}
#endif

// Conversions - float_4 =======================================================

inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	v = _mm_cvtpd_ps(a.v);
}
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	v = _mm_cvtepi32_ps(a.v);
}
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	v = _mm_cvtepi32_ps(a.v);
}
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	v = _mm_cvtepi32_ps(a.v);
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	v = _mm_cvtepi32_ps(a.v);
}
#endif

// Conversions - int8_16 =======================================================

inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::Vector(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	v = _mm_cvttpd_epi32(a.v);
}
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::Vector(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	v = _mm_cvttps_epi32(a.v);
}
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::Vector(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	v = a.v;
}
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16>::Vector(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	v = a.v;
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::Vector(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	v = a.v;
}
#endif

// Conversions - int16_8 =======================================================

inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::Vector(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	v = _mm_cvttpd_epi32(a.v);
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::Vector(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	v = _mm_cvttps_epi32(a.v);
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::Vector(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	v = a.v;
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::Vector(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	v = a.v;
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::Vector(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	v = a.v;
}
#endif

// Conversions - int32_4 =======================================================

inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	v = _mm_cvttpd_epi32(a.v);
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	v = _mm_cvttps_epi32(a.v);
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	v = a.v;
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	v = a.v;
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::Vector(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	v = a.v;
}
#endif

// Conversions - int64_2 =======================================================

#if STONEYDSP_USING_INT64_2

inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	v = _mm_cvttpd_epi32(a.v);
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	v = _mm_cvttps_epi32(a.v);
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	v = a.v;
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	v = a.v;
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::Vector(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	v = a.v;
}

#endif

// Casts - double_2 ============================================================

inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(_mm_castps_pd(a.v));
}
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	return Vector(_mm_castsi128_pd(a.v));
}
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	return Vector(_mm_castsi128_pd(a.v));
}
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(_mm_castsi128_pd(a.v));
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(_mm_castsi128_pd(a.v));
}
#endif

// Casts - float_4 =============================================================

inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(_mm_castpd_ps(a.v));
}
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	return Vector(_mm_castsi128_ps(a.v));
}
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	return Vector(_mm_castsi128_ps(a.v));
}
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(_mm_castsi128_ps(a.v));
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(_mm_castsi128_ps(a.v));
}
#endif

// Casts - int8_16 =============================================================

inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::cast(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(_mm_castpd_si128(a.v));
}
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::cast(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(_mm_castps_si128(a.v));
}
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::cast(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	return Vector(a.v);
}
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::cast(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(a.v);
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::cast(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(a.v);
}
#endif

// Casts - int16_8 =============================================================

inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::cast(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(_mm_castpd_si128(a.v));
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::cast(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(_mm_castps_si128(a.v));
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::cast(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	return Vector(a.v);
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::cast(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(a.v);
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::cast(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(a.v);
}
#endif

// Casts - int32_4 =============================================================

inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(_mm_castpd_si128(a.v));
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(_mm_castps_si128(a.v));
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	return Vector(a.v);
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	return Vector(a.v);
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::cast(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(a.v);
}
#endif

// Casts - int64_2 =============================================================

#if STONEYDSP_USING_INT64_2

inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> a)
{
	return Vector(_mm_castpd_si128(a.v));
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> a)
{
	return Vector(_mm_castps_si128(a.v));
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> a)
{
	return Vector(a.v);
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> a)
{
	return Vector(a.v);
}
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::cast(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> a) {
	return Vector(a.v);
}

#endif

// Operator overloads ==========================================================

/**
 * @brief `a @ b`
 *
*/
#define DECLARE_VECTOR_OPERATOR_INFIX(t, s, operator, func) \
	inline Vector<t, s> operator(const Vector<t, s>& a, const Vector<t, s>& b) { \
		return Vector<t, s>(func(a.v, b.v)); \
	}

/**
 * @brief `a @= b`
 *
*/
#define DECLARE_VECTOR_OPERATOR_INCREMENT(t, s, operator, opfunc) \
	inline Vector<t, s>& operator(Vector<t, s>& a, const Vector<t, s>& b) { \
		return a = opfunc(a, b); \
	}

//==============================================================================

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<double, 2>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator+, _mm_add_pd)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<double, 2>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator-, _mm_sub_pd)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<double, 2>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator*, _mm_mul_pd)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<double, 2>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator/, _mm_div_pd)

//==============================================================================

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<float, 4>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator+, _mm_add_ps)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<float, 4>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator-, _mm_sub_ps)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<float, 4>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator*, _mm_mul_ps)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<float, 4>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator/, _mm_div_ps)

//==============================================================================

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int8_t, 16>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator+, _mm_add_epi8)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int8_t, 16>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator-, _mm_sub_epi8)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator*, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator/, NOT AVAILABLE IN SSE3)

//==============================================================================

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int16_t, 8>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator+, _mm_add_epi16)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int16_t, 8>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator-, _mm_sub_epi16)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator*, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator/, NOT AVAILABLE IN SSE3)

//==============================================================================

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int32_t, 4>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator+, _mm_add_epi32)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int32_t, 4>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator-, _mm_sub_epi32)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator*, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator/, NOT AVAILABLE IN SSE3)

//==============================================================================

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int64_t, 2>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator+, _mm_add_epi64)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int64_t, 2>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator-, _mm_sub_epi64)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator*, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator/, NOT AVAILABLE IN SSE3)

#endif

//==============================================================================

/* Use these to apply logic, bit masks, and conditions to elements.
Boolean operators on vectors give 0x00000000 for false and 0xffffffff for true, for each vector element.

Examples:

Subtract 1 from value if greater than or equal to 1.

	x -= (x >= 1.f) & 1.f;
*/

//==============================================================================

// ^

DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator^, _mm_xor_pd)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator^, _mm_xor_ps)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator^, _mm_xor_si128)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator^, _mm_xor_si128)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator^, _mm_xor_si128)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator^, _mm_xor_si128)
#endif

//==============================================================================

// &

DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator&, _mm_and_pd)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator&, _mm_and_ps)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator&, _mm_and_si128)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator&, _mm_and_si128)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator&, _mm_and_si128)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator&, _mm_and_si128)
#endif

//==============================================================================

// |

DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator|, _mm_or_pd)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator|, _mm_or_ps)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator|, _mm_or_si128)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator|, _mm_or_si128)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator|, _mm_or_si128)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator|, _mm_or_si128)
#endif

//==============================================================================

// +=

DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator+=, operator+)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator+=, operator+)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator+=, operator+)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator+=, operator+)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator+=, operator+)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator+=, operator+)
#endif

//==============================================================================

// -=

DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator-=, operator-)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator-=, operator-)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator-=, operator-)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator-=, operator-)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator-=, operator-)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator-=, operator-)
#endif

//==============================================================================

// *=

DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator*=, operator*)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator*=, operator*)
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator*=, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator*=, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator*=, NOT AVAILABLE IN SSE3)
#if STONEYDSP_USING_INT64_2
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator*=, NOT AVAILABLE IN SSE3)
#endif

//==============================================================================

// /=

DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator/=, operator/)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator/=, operator/)
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator/=, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator/=, NOT AVAILABLE IN SSE3)
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator/=, NOT AVAILABLE IN SSE3)
#if STONEYDSP_USING_INT64_2
// DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator/=, NOT AVAILABLE IN SSE3)
#endif

//==============================================================================

// ^⁼

DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator^=, operator^)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator^=, operator^)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator^=, operator^)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator^=, operator^)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator^=, operator^)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator^=, operator^)
#endif

//==============================================================================

// &=

DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator&=, operator&)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator&=, operator&)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator&=, operator&)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator&=, operator&)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator&=, operator&)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator&=, operator&)
#endif

//==============================================================================

// |=

DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator|=, operator|)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator|=, operator|)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator|=, operator|)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator|=, operator|)
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator|=, operator|)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INCREMENT(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator|=, operator|)
#endif

//==============================================================================

// >=

DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator>=, _mm_cmpge_pd)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator>=, _mm_cmpge_ps)
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator>=(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a,
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& b)
{
	return Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>(_mm_cmpgt_epi8(a.v, b.v)) ^ Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::mask();
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator>=(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a,
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& b)
{
	return Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>(_mm_cmpgt_epi16(a.v, b.v)) ^ Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::mask();
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator>=(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a,
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& b)
{
	return Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>(_mm_cmpgt_epi32(a.v, b.v)) ^ Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::mask();
}
#if STONEYDSP_USING_INT64_2
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator>=(
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a,
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& b)
{
	return Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>(_mm_cmpgt_epi64(a.v, b.v)) ^ Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::mask();
}
#endif

//==============================================================================

// >

DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator>, _mm_cmpgt_pd)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator>, _mm_cmpgt_ps)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator>, _mm_cmpgt_epi8)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator>, _mm_cmpgt_epi16)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator>, _mm_cmpgt_epi32)
#if STONEYDSP_USING_INT64_2
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator>, _mm_cmpgt_epi64)
#endif

//==============================================================================

// <=

DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator<=, _mm_cmple_pd)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator<=, _mm_cmple_ps)
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator<=(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a,
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& b)
{
	return Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>(_mm_cmplt_epi8(a.v, b.v)) ^ Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::mask();
}
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator<=(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a,
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& b)
{
	return Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>(_mm_cmplt_epi16(a.v, b.v)) ^ Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::mask();
}
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator<=(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a,
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& b)
{
	return Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>(_mm_cmplt_epi32(a.v, b.v)) ^ Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::mask();
}
#if STONEYDSP_USING_INT64_2
// inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator<=(const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a, const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& b) {
// 	return Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>(_mm_cmplt_epi64(a.v, b.v)) ^ Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::mask();
// }
#endif

//==============================================================================

// <

DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator<, _mm_cmplt_pd)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator<, _mm_cmplt_ps)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U, operator<, _mm_cmplt_epi8)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U, operator<, _mm_cmplt_epi16)
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U, operator<, _mm_cmplt_epi32)
#if STONEYDSP_USING_INT64_2
// DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U, operator<, _mm_cmplt_epi64)
#endif

//==============================================================================

// !=

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<double, 2>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::double_t, (::StoneyDSP::size_t)2U, operator!=, _mm_cmpneq_pd)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<float, 4>
 */
DECLARE_VECTOR_OPERATOR_INFIX(::StoneyDSP::float_t, (::StoneyDSP::size_t)4U, operator!=, _mm_cmpneq_ps)

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator!=(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a,
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& b)
{
	return Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>(_mm_cmpeq_epi8(a.v, b.v)) ^ Vector<::StoneyDSP::int8_t, 16U>::mask();
}

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator!=(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a,
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& b)
{
	return Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>(_mm_cmpeq_epi16(a.v, b.v)) ^ Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::mask();
}

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator!=(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a,
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& b)
{
	return Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>(_mm_cmpeq_epi32(a.v, b.v)) ^ Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::mask();
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator!=(
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a,
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& b)
{
	return Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>(_mm_cmpeq_epi64(a.v, b.v)) ^ Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::mask();
}

#endif

//==============================================================================

// +a

/**
 * @brief
 *
 * @param a
 * @return Vector<double, 2>
 */
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> operator+(
    const Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& a)
{
	return a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<float, 4>
 */
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> operator+(
    const Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& a)
{
	return a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator+(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a)
{
	return a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator+(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a)
{
	return a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator+(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a)
{
	return a;
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator+(
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a)
{
	return a;
}

#endif

//==============================================================================

// -a

/**
 * @brief
 *
 * @param a
 * @return Vector<double, 2>
 */
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> operator-(
    const Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& a)
{
	return (::StoneyDSP::double_t)0.0 - a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<float, 4>
 */
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> operator-(
    const Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& a)
{
	return (::StoneyDSP::float_t)0.0f - a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator-(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a)
{
	return (::StoneyDSP::int8_t)0 - a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator-(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a)
{
	return (::StoneyDSP::int16_t)0 - a;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator-(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a)
{
	return (::StoneyDSP::int32_t)0 - a;
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator-(
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a)
{
	return _mm_castpd_si128(_mm_setzero_pd()) - a;
}

#endif

//==============================================================================

// ++a

/**
 * @brief
 *
 * @param a
 * @return Vector<double, 2>&
 */
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& operator++(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& a)
{
	return a += (::StoneyDSP::double_t)1.0;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<float, 4>&
 */
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& operator++(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& a)
{
	return a += (::StoneyDSP::float_t)1.0f;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int8_t, 16>&
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& operator++(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a)
{
	return a += (::StoneyDSP::int8_t)1;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int16_t, 8>&
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& operator++(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a)
{
	return a += (::StoneyDSP::int16_t)1;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int32_t, 4>&
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& operator++(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a)
{
	return a += (::StoneyDSP::int32_t)1;
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @return Vector<int64_t, 2>&
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& operator++(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a)
{
	return a += _mm_castpd_si128(_mm_set1_pd(1.0));
}

#endif

//==============================================================================

// --a

/**
 * @brief
 *
 * @param a
 * @return Vector<double, 2>&
 */
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& operator--(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& a)
{
	return a -= (::StoneyDSP::double_t)1.0;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<float, 4>&
 */
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& operator--(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& a)
{
	return a -= (::StoneyDSP::float_t)1.0f;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int8_t, 16>&
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& operator--(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a)
{
	return a -= (::StoneyDSP::int8_t)1;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int16_t, 8>&
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& operator--(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a)
{
	return a -= (::StoneyDSP::int16_t)1;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int32_t, 4>&
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& operator--(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a)
{
	return a -= (::StoneyDSP::int32_t)1;
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @return Vector<int64_t, 2>&
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& operator--(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a)
{
	return a -= _mm_castpd_si128(_mm_set1_pd(1.0));
}

#endif

//==============================================================================

// a++

/**
 * @brief
 *
 * @param a
 * @return Vector<double, 2>
 */
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> operator++(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& a, int)
{
	Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> b = a;
	++a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<float, 4>
 */
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> operator++(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& a, int)
{
	Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> b = a;
	++a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator++(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a, int)
{
	Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> b = a;
	++a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator++(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a, int)
{
	Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> b = a;
	++a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator++(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a, int)
{
	Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> b = a;
	++a;
	return b;
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator++(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a, int)
{
	Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> b = a;
	++a;
	return b;
}

#endif

//==============================================================================

// a--

/**
 * @brief
 *
 * @param a
 * @return Vector<double, 2>
 */
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> operator--(
    Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& a, int)
{
	Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> b = a;
	--a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<float, 4>
 */
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> operator--(
    Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& a, int)
{
	Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> b = a;
	--a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator--(
    Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a, int)
{
	Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> b = a;
	--a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator--(
    Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a, int)
{
	Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> b = a;
	--a;
	return b;
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator--(
    Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a, int)
{
	Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> b = a;
	--a;
	return b;
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator--(
    Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a, int)
{
	Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> b = a;
	--a;
	return b;
}

#endif

//==============================================================================

// ~a

/**
 * @brief
 *
 * @param a
 * @return Vector<double, 2>
 */
inline Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U> operator~(
    const Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>& a)
{
	return a ^ Vector<::StoneyDSP::double_t, (::StoneyDSP::size_t)2U>::mask();
}

/**
 * @brief
 *
 * @param a
 * @return Vector<float, 4>
 */
inline Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U> operator~(
    const Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>& a)
{
	return a ^ Vector<::StoneyDSP::float_t, (::StoneyDSP::size_t)4U>::mask();
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator~(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a)
{
	return a ^ Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>::mask();
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator~(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a)
{
	return a ^ Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>::mask();
}

/**
 * @brief
 *
 * @param a
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator~(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a)
{
	return a ^ Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>::mask();
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator~(
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a)
{
	return a ^ Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>::mask();
}

#endif

//==============================================================================

// a << b

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator<<(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>(
        _mm_sll_epi32(a.v, _mm_cvtsi32_si128(b))
    );
}

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator<<(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>(
        _mm_sll_epi32(a.v, _mm_cvtsi32_si128(b))
    );
}

/**
 *
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator<<(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>(
        _mm_sll_epi32(a.v, _mm_cvtsi32_si128(b))
    );
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator<<(
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>(
        _mm_sll_epi64(a.v, _mm_cvtsi64_si128(b))
    );
}

#endif

//==============================================================================

// a >> b

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int8_t, 16>
 */
inline Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U> operator>>(
    const Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int8_t, (::StoneyDSP::size_t)16U>(
        _mm_srl_epi32(a.v, _mm_cvtsi32_si128(b))
    );
}

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int16_t, 8>
 */
inline Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U> operator>>(
    const Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int16_t, (::StoneyDSP::size_t)8U>(
        _mm_srl_epi32(a.v, _mm_cvtsi32_si128(b))
    );
}

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int32_t, 4>
 */
inline Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U> operator>>(
    const Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int32_t, (::StoneyDSP::size_t)4U>(
        _mm_srl_epi32(a.v, _mm_cvtsi32_si128(b))
    );
}

#if STONEYDSP_USING_INT64_2

/**
 * @brief
 *
 * @param a
 * @param b
 * @return Vector<int64_t, 2>
 */
inline Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U> operator>>(
    const Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>& a,
    const int& b
) {
	return Vector<::StoneyDSP::int64_t, (::StoneyDSP::size_t)2U>(
        _mm_srl_epi64(a.v, _mm_cvtsi64_si128(b))
    );
}

#endif

//==============================================================================

  /// @} group SIMD
} // namespace SIMD

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

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
