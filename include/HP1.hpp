/***************************************************************************//**
 * @file HP1.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 0.0.0
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
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

#define STONEYVCV_HP1_HPP_INCLUDED 1

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

#include "plugin.hpp"

//==============================================================================

namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

namespace VCVRack
{
/** @addtogroup VCVRack
 *  @{
 */

//==============================================================================

using Module = ::rack::engine::Module;

/**
 * @brief The `HP1` struct.
 *
 */
struct HP1 final : Module
{
public:

    using ProcessArgs = ::StoneyDSP::VCVRack::Module::ProcessArgs;

    enum ParamsId {
        PARAMS_LEN
    };
	enum InputsId {
		INPUTS_LEN
	};
	enum OutputsId {
		OUTPUTS_LEN
	};
	enum LightsId {
		LIGHTS_LEN
	};

    HP1();
    ~HP1();
private:
    STONEYDSP_DECLARE_NON_COPYABLE(HP1)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP1)
};

//==============================================================================

using ModuleWidget = ::rack::app::ModuleWidget;

/**
 * @brief The `HP1ModuleWidget` struct.
 *
 */
struct HP1ModuleWidget final : ModuleWidget
{
public:
    HP1ModuleWidget(::StoneyDSP::VCVRack::HP1 *module);
    ~HP1ModuleWidget();
private:
    STONEYDSP_DECLARE_NON_COPYABLE(HP1ModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP1ModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model *createHP1(); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group VCVRack
} // namespace VCVRack

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================
