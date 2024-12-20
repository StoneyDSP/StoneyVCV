/*******************************************************************************
 * @file HP1.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 0.0.1
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

#include "StoneyVCV/plugin.hpp"

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

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

/**
 * @brief The `HP1` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace HP1
 *
 */
namespace HP1
{
/** @addtogroup HP1
 *  @{
 */

//==============================================================================

/**
 * @brief The `HP1Module` struct.
 *
 */
struct HP1Module final :
    ::rack::engine::Module
{

    //==========================================================================

public:

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

    //==========================================================================

    enum IdxParams {
        /** Number of Parameters. */
        NUM_PARAMS
    };

	enum IdxInputs {
        /** Number of Input ports. */
		NUM_INPUTS
	};

	enum IdxOutputs {
        /** Number of Output ports. */
		NUM_OUTPUTS
	};

	enum IdxLights {
        /** Number of Lights. */
		NUM_LIGHTS
	};

    //==========================================================================

    /**
     * @brief Construct a new `HP1Module` object.
     *
     */
    HP1Module();

    /**
     * @brief Destroys the `HP1Module` object.
     *
     */
    ~HP1Module();

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP1Module)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP1Module)
};

//==============================================================================

/**
 * @brief The `HP1Widget` struct.
 *
 */
struct HP1Widget final :
    ::rack::Widget
{
public:

    using DrawArgs = ::rack::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `HP1Widget` object.
     *
     */
    HP1Widget();

    // /**
    //  * @brief Destroys the `HP1Widget` object.
    //  *
    //  */
    // ~HP1Widget();

    //==========================================================================

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
    void draw(const ::StoneyDSP::StoneyVCV::HP1::HP1Widget::DrawArgs& args) override;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget* hp1WidgetFrameBuffer;

    /**
     * @brief
     *
     */
    ::rack::Widget* panelBorder;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP1Widget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP1Widget)
};

//==============================================================================

/**
 * @brief The `HP1ModuleWidget` struct.
 *
 */
struct HP1ModuleWidget final :
    ::rack::app::ModuleWidget
{

    //==========================================================================

public:

    //==========================================================================

    /**
     * @brief Construct a new `HP1ModuleWidget` object.
     *
     * @param module
     *
     */
    HP1ModuleWidget(::StoneyDSP::StoneyVCV::HP1::HP1Module* module);

    //==========================================================================

    /**
     * @brief
     */
    ::rack::math::Vec size;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::HP1::HP1Widget* hp1Widget;

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget* hp1ModuleWidgetFrameBuffer;

    //==========================================================================

    ::rack::math::Vec screwTPos, screwBPos;

    ::rack::componentlibrary::ThemedScrew* screwT;
    ::rack::componentlibrary::ThemedScrew* screwB;

    ::rack::app::ThemedSvgPanel* panel;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP1ModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP1ModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model* createHP1(); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group HP1
} // namespace HP1

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================
