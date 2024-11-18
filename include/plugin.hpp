/***************************************************************************//**
 * @file plugin.hpp
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

#define PLUGIN_HPP_INCLUDED 1

//==============================================================================

#if !__has_include(<rack.hpp>)
 #error "Cannot find required header 'rack.hpp' - did you set $RACK_DIR?"
#else

#include <rack.hpp>

#include "StoneyDSP/Core.hpp"
#include "StoneyDSP/SIMD.hpp"
#include "StoneyDSP/DSP.hpp"

//==============================================================================

namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

/**
 * @brief The `VCVRack` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 *
 */
namespace VCVRack
{
/** @addtogroup VCVRack
 *  @{
 */

//==============================================================================

// Declare the Plugin, defined in plugin.cpp
extern rack::plugin::Plugin* pluginInstance;

//==============================================================================

// Declare each Model, defined in each module source file
#if (STONEYVCV_VERSION_MAJOR >= 0) && (STONEYVCV_VERSION_MINOR >= 1)
 // EXPERIMENTAL MODULES HERE...
#elif (STONEYVCV_VERSION_MAJOR) >= 0 && (STONEYVCV_VERSION_MINOR >= 0)
 #warning "No modules found..."
#endif

//==============================================================================

  /// @} group VCVRack
} // namespace VCVRack

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif

//==============================================================================
