/*******************************************************************************
 * @file plugin.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.1
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

#define STONEYVCV_PLUGIN_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

//==============================================================================

#include <StoneyVCV/version.hpp>

//==============================================================================

namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

/**
 * @brief The `StoneyVCV` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyVCV
 *
 */
namespace StoneyVCV
{
/** @addtogroup StoneyVCV
 *  @{
 */

//==============================================================================

/**
 * @brief Declare the Plugin instance, defined in `plugin.cpp`
 */
extern ::rack::plugin::Plugin* pluginInstance;

//==============================================================================

#if defined (STONEYVCV_BUILD_MODULES)
// Declare each Model, defined in each module source file

#if defined (STONEYVCV_EXPERIMENTAL)
// EXPERIMENTAL MODULES HERE...

#if defined (STONEYVCV_BUILD_VCA)
    namespace VCA {
    /** @addtogroup VCA
     *  @{
     */

    /**
     * @brief Declaration of the `VCA` Model instance, defined in `VCA.cpp`.
     */
    extern ::rack::plugin::Model* modelVCA;

    /// @} group VCA
    } // namespace VCA
#endif // STONEYVCV_BUILD_VCA

#if defined (STONEYVCV_BUILD_LFO)
    namespace LFO {
    /** @addtogroup LFO
     *  @{
     */

    /**
     * @brief Declaration of the `LFO` Model instance, defined in `LFO.cpp`.
     */
    extern ::rack::plugin::Model* modelLFO;

    /// @} group LFO
    } // namespace LFO
#endif // STONEYVCV_BUILD_LFO

#endif // STONEYVCV_EXPERIMENTAL

#if (STONEYVCV_VERSION_MAJOR >= 0U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH >= 1U)

#if defined (STONEYVCV_BUILD_HP4)
    namespace HP4 {
    /** @addtogroup HP4
     *  @{
     */

    /**
     * @brief Declaration of the `HP4` Model instance, defined in `HP4.cpp`.
     */
    extern ::rack::plugin::Model* modelHP4;


    /// @} group HP4
    } // namespace HP4
#endif // STONEYVCV_BUILD_HP4

#if defined (STONEYVCV_BUILD_HP2)
    namespace HP2 {
    /** @addtogroup HP2
     *  @{
     */

    /**
     * @brief Declaration of the `HP2` Model instance, defined in `HP2.cpp`.
     */
    extern ::rack::plugin::Model* modelHP2;

    /// @} group HP1
    } // namespace HP1
#endif // STONEYVCV_BUILD_HP2

#if defined (STONEYVCV_BUILD_HP1)
    namespace HP1 {
    /** @addtogroup HP1
     *  @{
     */

    /**
     * @brief Declaration of the `HP1` Model instance, defined in `HP1.cpp`.
     */
    extern ::rack::plugin::Model* modelHP1;

    /// @} group HP1
    } // namespace HP1
#endif // STONEYVCV_BUILD_HP1

#elif (STONEYVCV_VERSION_MAJOR >= 0U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH >= 0U)
    #warning "No modules found..."
#endif

namespace Panels {
extern ::NVGcolor bgBlack;
extern ::NVGcolor bgWhite;
extern ::StoneyDSP::float_t MIN_WIDTH;
extern ::StoneyDSP::float_t MIN_HEIGHT;
}

#endif // STONEYVCV_BUILD_MODULES

//==============================================================================

#if defined (STONEYVCV_BUILD_TESTS)
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
#endif

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif // STONEYVCV_BUILD_PLUGIN

//==============================================================================
