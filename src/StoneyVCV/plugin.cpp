/*******************************************************************************
 * @file plugin.cpp
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

//==============================================================================

#include <rack.hpp>

//==============================================================================

#include "StoneyVCV/plugin.hpp"

//==============================================================================

#ifdef STONEYVCV_BUILD_PLUGIN

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

/**
 * @brief The `StoneyDSP` VCV Rack Plugin instance.
 */
::rack::plugin::Plugin* pluginInstance;

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================

#ifdef STONEYVCV_BUILD_MODULES

/**
 * @brief The `StoneyDSP` VCV Rack Plugin Initialiser.
 *
 * @param p
 */
void init(::rack::plugin::Plugin* p) {

    ::StoneyDSP::StoneyVCV::pluginInstance = p;

#ifdef STONEYVCV_EXPERIMENTAL
    // EXPERIMENTAL MODULES HERE...
#ifdef STONEYVCV_BUILD_VCA
    p->addModel(::StoneyDSP::StoneyVCV::VCA::modelVCA);
#endif
#ifdef STONEYVCV_BUILD_LFO
    p->addModel(::StoneyDSP::StoneyVCV::LFO::modelLFO);
#endif
#endif // STONEYVCV_EXPERIMENTAL

#if (STONEYVCV_VERSION_MAJOR >= 0) && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 1)
#ifdef STONEYVCV_BUILD_HP4
    p->addModel(::StoneyDSP::StoneyVCV::HP4::modelHP4);
#endif
#ifdef STONEYVCV_BUILD_HP2
    p->addModel(::StoneyDSP::StoneyVCV::HP2::modelHP2);
#endif
#ifdef STONEYVCV_BUILD_HP1
    p->addModel(::StoneyDSP::StoneyVCV::HP1::modelHP1);
#endif
#elif (STONEYVCV_VERSION_MAJOR) >= 0 && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 0)
    #warning "No modules found..."
#endif

    // Any other plugin initialization may go here.
    // As an alternative, consider lazy-loading assets and lookup tables when
    // your module is created to reduce startup times of Rack.
}

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

namespace Panels {

//==============================================================================

::NVGcolor bgBlack = ::nvgRGBA(0, 0, 0, 255);
::NVGcolor bgWhite = ::nvgRGBA(255, 255, 255, 255);
::StoneyDSP::float_t MIN_WIDTH = ::rack::window::mm2px(5.079999999F);
::StoneyDSP::float_t MIN_HEIGHT = ::rack::window::mm2px(128.693333312F);

//==============================================================================

} // namespace Panels

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================

#endif // STONEYVCV_BUILD_MODULES

//==============================================================================

#endif // STONEYVCV_BUILD_PLUGIN

//==============================================================================
