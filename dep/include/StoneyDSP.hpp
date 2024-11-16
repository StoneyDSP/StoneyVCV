/***************************************************************************//**
 * @file StoneyDSP.hpp
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

#pragma once

#define STONEYDSP_HPP_INCLUDED

//==============================================================================

#ifndef STONEYDSP_STRINGIFY
  # define STONEYDSP_STRINGIFY_HELPER(n) #n
  /**
   * @brief Handy stringify pre-processor macro.
   * @param n The value to stringify.
   */
  # define STONEYDSP_STRINGIFY(n) STONEYDSP_STRINGIFY_HELPER(n)
#endif

#include "StoneyDSP/version.hpp"
#include "StoneyDSP/system.hpp"
#include "StoneyDSP/common.hpp"
// #include "StoneyDSP/exceptions.hpp"

//==============================================================================

/**
 * @brief The `StoneyDSP` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

/**
 * A single 32-bit integer can represent a wide range of values;
 * from `-2,147,483,648`, to `2,147,483,647`.
 *
 * A single 64-bit integer can represent a much larger range of values;
 * from `-9,223,372,036,854,775,808`, to `9,223,372,036,854,775,807`.
 *
 */

//==============================================================================

using __INT_8_T = signed char;
using __UINT_8_T = unsigned char;
using __INT_16_T = signed short;
using __UINT_16_T = unsigned short;
using __INT_32_T = signed int;
using __UINT_32_T = unsigned int;
#ifndef STONEYDSP_USING_INT64_2
 #if STONEYDSP_MSVC
  using  __INT_64_T = __int64;
  using  __UINT_64_T = unsigned __int64;
 #else
  using __INT_64_T = long long;
  using __UINT_64_T = unsigned long long;
 #endif
#else
 using __INT_64_T = __m64;    // simd-optimized integer
 using __UINT_64_T = __m64_u; // simd-optimized integer
#endif
using __FLOAT_T = float;
using __DOUBLE_T = double;

//==============================================================================

using int8_t = ::StoneyDSP::__INT_8_T;
using uint8_t =  ::StoneyDSP::__UINT_8_T;
using int16_t = ::StoneyDSP::__INT_16_T;
using uint16_t = ::StoneyDSP::__UINT_16_T;
using int32_t = ::StoneyDSP::__INT_32_T;
using uint32_t = ::StoneyDSP::__UINT_32_T;
using int64_t = ::StoneyDSP::__INT_64_T;
using uint64_t = ::StoneyDSP::__UINT_64_T;
using float_t = ::StoneyDSP::__FLOAT_T;
using double_t = ::StoneyDSP::__DOUBLE_T;

//==============================================================================

/** @brief A platform-independent 8-bit signed integer type. */
using int8 = ::StoneyDSP::int8_t;
/** @brief A platform-independent 8-bit unsigned integer type. */
using uint8 = ::StoneyDSP::uint8_t;
/** @brief A platform-independent 16-bit signed integer type. */
using int16 = ::StoneyDSP::int16_t;
/** @brief A platform-independent 16-bit unsigned integer type. */
using uint16 = ::StoneyDSP::uint16_t;
/** @brief A platform-independent 32-bit signed integer type. */
using int32 = ::StoneyDSP::int32_t;
/** @brief A platform-independent 32-bit unsigned integer type. */
using uint32 = ::StoneyDSP::uint32_t;
/** @brief A platform-independent 64-bit signed integer type. */
using int64 = ::StoneyDSP::int64_t;
/** @brief A platform-independent 64-bit unsigned integer type. */
using uint64 = ::StoneyDSP::uint64_t;

//==============================================================================

using __BYTE_T = signed char;

using byte_t = ::StoneyDSP::__BYTE_T;

using byte = ::StoneyDSP::byte_t;

//==============================================================================

/** @brief The SystemStats class. */
class SystemStats final {
public:

    /**
     * @brief Returns the current version of `STONEYDSP`.
     * See also the `STONEYDSP_VERSION`, `STONEYDSP_MAJOR_VERSION` and
     * `STONEYDSP_MINOR_VERSION` macros.
     *
     */
    static std::string getStoneyDSPVersion();

    // static std::string_view getStoneyDSPVersion();

private:
    STONEYDSP_DECLARE_NON_CONSTRUCTABLE (SystemStats)
    STONEYDSP_DECLARE_NON_COPYABLE (SystemStats)
};

//==============================================================================

/**
 * @brief Handy function for avoiding unused variables warning.
 *
 * @tparam Types
 */
template <typename... Types>
void ignoreUnused (Types&&...) noexcept {}

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

// StoneyDSP Library

#include "StoneyDSP/simd.hpp"
// #include "StoneyDSP/dsp.hpp"

//==============================================================================
