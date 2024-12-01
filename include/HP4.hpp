/***************************************************************************//**
 * @file HP4.hpp
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

#define STONEYVCV_HP4_HPP_INCLUDED 1

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

namespace StoneyVCV
{
/** @addtogroup StoneyVCV
 *  @{
 */

//==============================================================================

using Module = ::rack::engine::Module;

/**
 * @brief The `HP4Module` struct.
 *
 */
struct HP4Module final : Module
{
public:

    using ProcessArgs = ::StoneyDSP::StoneyVCV::Module::ProcessArgs;

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

    HP4Module();
    // ~HP4Module();
private:
    STONEYDSP_DECLARE_NON_COPYABLE(HP4Module)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP4Module)
};

//==============================================================================

using Widget = ::rack::Widget;

struct HP4Widget final : Widget
{
public:
    HP4Widget();
    // ~HP4Widget();
    /**
     * @brief Advances the module by one frame.
     *
     */
    void step() override;
    /**
     * @brief Draws the widget to the NanoVG context.
     * When overriding, call the superclass's draw(args) to recurse to
     * children.
     *
     * @param args
     */
    void draw(const ::StoneyDSP::StoneyVCV::Widget::DrawArgs &args) override;
    // ::rack::FramebufferWidget *hp4WidgetFrameBuffer;
    // Widget *panelBorder;
private:
    STONEYDSP_DECLARE_NON_COPYABLE(HP4Widget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP4Widget)
};

//==============================================================================

using ModuleWidget = ::rack::app::ModuleWidget;

/**
 * @brief The `HP4ModuleWidget` struct.
 *
 */
struct HP4ModuleWidget final : ModuleWidget
{
public:
    HP4ModuleWidget(::StoneyDSP::StoneyVCV::HP4Module *module);
    // ~HP4ModuleWidget();
    // ::StoneyDSP::StoneyVCV::HP4Widget *hp4Widget;
    // ::rack::FramebufferWidget *hp4ModuleWidgetFrameBuffer;
private:
    STONEYDSP_DECLARE_NON_COPYABLE(HP4ModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP4ModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model *createHP4(); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================
