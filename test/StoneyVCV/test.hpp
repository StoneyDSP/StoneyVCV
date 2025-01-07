/*******************************************************************************
 * @file include/StoneyVCV/test.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief @PROJECT_DESCRIPTION@
 * @version @test_VERSION@
 *
 * @copyright MIT License
 *
 * Copyright (c) 2024 Nathan J. Hood <nathanjhood@googlemail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#define STONEYVCV_TEST_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/version.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

//==============================================================================

namespace StoneyDSP {
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

namespace StoneyVCV {
/** @addtogroup StoneyVCV
 *  @{
 */

//==============================================================================


/**
 * @brief The `Spec` struct.
 *
 * A base class for deriving specs for unit-testing with.
 *
 */
struct Spec {
public:
    ::std::string slug, name, description;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 0U;
    ::rack::math::Vec size;
    Spec()
    :   slug("Spec"),
        name(""),
        description("Unit test spec base class (internal)"),
        size(
            ::rack::window::mm2px(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH),
            ::rack::window::mm2px(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT)
        )
    {};
    ~Spec() = default;
private:
    STONEYDSP_DECLARE_NON_COPYABLE(Spec)
    STONEYDSP_DECLARE_NON_MOVEABLE(Spec)
};

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif

//==============================================================================
