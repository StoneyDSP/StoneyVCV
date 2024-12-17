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

// Declare the Plugin, defined in plugin.cpp
extern ::rack::plugin::Plugin* pluginInstance;

//==============================================================================

#if defined (STONEYVCV_BUILD_MODULES)
// Declare each Model, defined in each module source file

#if defined (STONEYVCV_EXPERIMENTAL)
    // EXPERIMENTAL MODULES HERE...
#if defined (STONEYVCV_BUILD_VCA)
namespace VCA {
extern ::rack::plugin::Model* modelVCA;
}
#endif
#if defined (STONEYVCV_BUILD_LFO)
namespace LFO {
extern ::rack::plugin::Model* modelLFO;
}
#endif
#endif // STONEYVCV_EXPERIMENTAL

#if (STONEYVCV_VERSION_MAJOR >= 0U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH >= 1U)
#if defined (STONEYVCV_BUILD_HP4)
namespace HP4 {
extern ::rack::plugin::Model* modelHP4;
}
#endif
#if defined (STONEYVCV_BUILD_HP2)
namespace HP2 {
extern ::rack::plugin::Model* modelHP2;
}
#endif
#if defined (STONEYVCV_BUILD_HP1)
namespace HP1 {
extern ::rack::plugin::Model* modelHP1;
}
#endif
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
struct Spec {
public:
    ::std::string slug;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS;
    virtual Spec();
private:
    // STONEYDSP_DECLARE_NON_CONSTRUCTABLE(Spec)
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
