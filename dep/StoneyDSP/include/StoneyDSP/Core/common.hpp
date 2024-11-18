/***************************************************************************//**
 * @file common.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
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

#define STONEYDSP_COMMON_HPP_INCLUDED 1

//==============================================================================

// Standard includes

// #if __has_include(<stdint.h>)
//  #include <stdint.h>
// #endif

#if __has_include(<string>)
 #include <string>
#endif

// #if __has_include(<string_view>)
//   #include <string_view> // Not supported by Rack!! :(
// #endif

#if defined (__SSE2__)
 #include <emmintrin.h>
#else
 #define SIMDE_ENABLE_NATIVE_ALIASES
 #include <simde/x86/sse2.h>
#endif

#if defined (__SSE4_2__)
 #include <nmmintrin.h>
#else
 #define SIMDE_ENABLE_NATIVE_ALIASES
 #include <simde/x86/sse4.2.h>
#endif

//==============================================================================

// Platform defs...

/**
 * @brief This is a shorthand macro for deleting a class's constructor.
 *
 */
#define STONEYDSP_DECLARE_NON_CONSTRUCTABLE(className) \
    className () = delete;

/**
 * @brief This is a shorthand macro for deleting a class's copy constructor
 * and copy assignment operator.
 *
 */
#define STONEYDSP_DECLARE_NON_COPYABLE(className) \
    className (const className&) = delete;\
    className& operator= (const className&) = delete;

/**
 * @brief This is a shorthand macro for deleting a class's move constructor
 * and move assignment operator.
 *
 */
#define STONEYDSP_DECLARE_NON_MOVEABLE(className) \
    className (className&&) = delete;\
    className& operator= (className&&) = delete;

/**
 * @brief This macro can be added to class definitions to disable the use of
 * new/delete to allocate the object on the heap, forcing it to only be used
 * as a stack or member variable.
 *
 */
#define STONEYDSP_PREVENT_HEAP_ALLOCATION \
private: \
    static void* operator new (size_t) = delete; \
    static void operator delete (void*) = delete;

//==============================================================================
