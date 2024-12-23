/*******************************************************************************
 * @file HP2.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief @PROJECT_DESCRIPTION@
 * @version @STONEYVCV_VERSION@
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

#define STONEYVCV_HP2_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_HP2)

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
 * @brief The `HP2` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace HP2
 *
 */
namespace HP2
{
/** @addtogroup HP2
 *  @{
 */

//==============================================================================

/**
 * @brief The `HP2Module` struct.
 *
 */
struct HP2Module final :
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
     * @brief Construct a new `HP2Module` object.
     *
     */
    HP2Module();

    /**
     * @brief Destroys the `HP2Module` object.
     *
     */
    virtual ~HP2Module();

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP2Module)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP2Module)
};

//==============================================================================

/**
 * @brief The `HP2Widget` struct.
 *
 */
struct HP2Widget final :
    ::rack::widget::Widget
{
    //==========================================================================

public:

    using DrawArgs = ::rack::widget::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `HP2Widget` object.
     *
     */
    HP2Widget();

    /**
     * @brief Destroys the `HP2Widget` object.
     *
     */
    virtual ~HP2Widget();

    //==========================================================================

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
    virtual void draw(const ::StoneyDSP::StoneyVCV::HP2::HP2Widget::DrawArgs& args) override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::widget::FramebufferWidget* hp2WidgetFrameBuffer;

    /**
     * @brief
     *
     */
    ::rack::widget::Widget* panelBorder;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(HP2Widget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP2Widget)
};

//==============================================================================

/**
 * @brief The `HP2ModuleWidget` struct.
 *
 */
struct HP2ModuleWidget final :
    ::rack::app::ModuleWidget
{
    //==========================================================================

public:

    //==========================================================================

    /**
     * @brief Construct a new `HP2ModuleWidget` object.
     *
     * @param module
     *
     */
    HP2ModuleWidget(::StoneyDSP::StoneyVCV::HP2::HP2Module* module);

    /**
     * @brief Destroys the `HP2ModuleWidget` object.
     *
     */
    virtual ~HP2ModuleWidget();

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
    ::rack::math::Vec size;

    /**
     * @brief
     */
    ::rack::app::ThemedSvgPanel* panel;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::HP2::HP2Widget* hp2Widget;

    /**
     * @brief
     *
     */
    ::rack::widget::FramebufferWidget* hp2ModuleWidgetFrameBuffer;

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

    STONEYDSP_DECLARE_NON_COPYABLE(HP2ModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP2ModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model* createHP2(); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group HP2
} // namespace HP2

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif // defined (STONEYVCV_BUILD_HP2)

//==============================================================================
