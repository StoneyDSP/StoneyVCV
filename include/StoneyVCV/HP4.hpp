/*******************************************************************************
 * @file HP4.hpp
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

#define STONEYVCV_HP4_HPP_INCLUDED 1

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
 * @brief The `HP4` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace HP4
 *
 */
namespace HP4
{
/** @addtogroup HP4
 *  @{
 */

//==============================================================================

/**
 * @brief The `HP4Module` struct.
 *
 */
struct HP4Module final :
    ::rack::engine::Module
{
    //==========================================================================

public:

    //==========================================================================

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

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
     * @brief Construct a new `HP4Module` object.
     *
     */
    HP4Module();

    /**
     * @brief Destroys the `HP4Module` object.
     *
     */
    virtual ~HP4Module();

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP4Module)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP4Module)
};

//==============================================================================

/**
 * @brief The `HP2Widget` struct.
 *
 */
struct HP4Widget final :
    ::rack::widget::Widget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::rack::widget::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `HP4Widget` object.
     *
     */
    HP4Widget();

    /**
     * @brief Destroys the `HP4Widget` object.
     *
     */
    virtual ~HP4Widget();

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws the widget to the NanoVG context.
     * When overriding, call the superclass's draw(args) to recurse to
     * children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::HP4::HP4Widget::DrawArgs& args) override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::widget::FramebufferWidget* hp4WidgetFrameBuffer;

    /**
     * @brief
     *
     */
    ::rack::app::PanelBorder* panelBorder;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP4Widget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP4Widget)
};

//==============================================================================

/**
 * @brief The `HP4ModuleWidget` struct.
 *
 */
struct HP4ModuleWidget final :
    ::rack::app::ModuleWidget
{

    //==========================================================================

public:

    //==========================================================================

    /**
     * @brief Construct a new `HP4ModuleWidget` object.
     *
     */
    HP4ModuleWidget(::StoneyDSP::StoneyVCV::HP4::HP4Module* module);

    /**
     * @brief Destroys the `HP4ModuleWidget` object.
     *
     */
    virtual ~HP4ModuleWidget();

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     */
    const ::rack::math::Vec size;

    /**
     * @brief
     */
    ::rack::app::ThemedSvgPanel* panel;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::HP4::HP4Widget* hp4Widget;

    /**
     * @brief
     *
     */
    ::rack::widget::FramebufferWidget* hp4ModuleWidgetFrameBuffer;

    //==========================================================================

    /**
     * @brief
     *
     */
    const ::rack::math::Vec screwsPositions [4];

    /**
     * @brief
     *
     */
    ::rack::componentlibrary::ThemedScrew* screws [4];

    //==========================================================================

    /**
     * @brief
     *
     */
    bool lastPrefersDarkPanels;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP4ModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP4ModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model* createHP4(); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group HP4
} // namespace HP4

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================
