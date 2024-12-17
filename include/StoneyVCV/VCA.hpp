/*******************************************************************************
 * @file VCA.hpp
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

#define STONEYVCV_VCA_HPP_INCLUDED 1

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>
#include <StoneyDSP/DSP.hpp>
#include <StoneyDSP/SIMD.hpp>

//==============================================================================

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

/**
 * @brief The `VCA` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace VCA
 *
 */
namespace VCA
{
/** @addtogroup VCA
 *  @{
 */

//==============================================================================

/**
 * @brief The `VCAModule` struct.
 *
 */
struct VCAModule final :
    ::rack::engine::Module
{

    //==========================================================================

public:

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

    //==========================================================================

    enum IdxParams {
        GAIN_PARAM,
        NUM_PARAMS
    };

	enum IdxInputs {
		VCA_INPUT,
        CV_INPUT,
		NUM_INPUTS
	};

	enum IdxOutputs {
		VCA_OUTPUT,
		NUM_OUTPUTS
	};

	enum IdxLights {
		BLINK_LIGHT,
		NUM_LIGHTS
	};

    //==========================================================================

    /**
     * @brief Construct a new `VCOModule` object.
     *
     */
    VCAModule();

    /**
     * @brief Destroy the `VCOModule` object.
     *
     */
    ~VCAModule();

    //==========================================================================

    /**
     * @brief Advances the module by one audio sample.
     *
     * @param args
     */
    virtual void process(const ::StoneyDSP::StoneyVCV::VCA::VCAModule::ProcessArgs &args) override;

    /**
     * @brief Store extra internal data in the "data" property of the module's JSON object.
     *
     * @return json_t
     */
    ::json_t *dataToJson() override;

    /**
     * @brief Load internal data from the "data" property of the module's JSON object.
     * Not called if "data" property is not present.
     *
     * @param rootJ
     */
    void dataFromJson(::json_t *rootJ) override;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::StoneyDSP::size_t lastChannels = 1;

    /**
     * @brief
     *
     */
    ::StoneyDSP::float_t gain;

    /**
     * @brief
     *
     */
	::StoneyDSP::float_t lastGains[16] = {};

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(VCAModule)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAModule)
};

//==============================================================================

/**
 * @brief The `VCAWidget` struct.
 *
 */
struct VCAWidget final :
    ::rack::Widget
{

    //==========================================================================

public:

    using DrawArgs = ::rack::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `VCOWidget` object.
     *
     */
    VCAWidget();

    // /**
    //  * @brief Destroys the `VCOWidget` object.
    //  *
    //  */
    // ~VCAWidget();

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
    void draw(const ::StoneyDSP::StoneyVCV::VCA::VCAWidget::DrawArgs &args) override;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget *vcaWidgetFrameBuffer;

    /**
     * @brief
     *
     */
    ::rack::Widget *panelBorder;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(VCAWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAWidget)
};

//==============================================================================

/**
 * @brief The `VCAModuleWidget` struct.
 *
 */
struct VCAModuleWidget final :
    ::rack::app::ModuleWidget
{

    //==========================================================================

public:

    //==========================================================================

    /**
     * @brief Construct a new `VCOModuleWidget` object.
     *
     * @param module
     *
     */
    VCAModuleWidget(::StoneyDSP::StoneyVCV::VCA::VCAModule* module);

    // /**
    //  * @brief Destroys the `VCOModuleWidget` object.
    //  *
    //  */
    // ~VCAModuleWidget();

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::math::Vec size;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::VCA::VCAWidget *vcaWidget;

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget *vcaModuleWidgetFrameBuffer;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(VCAModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model *createVCA(); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group VCA
} // namespace VCA

//==============================================================================

  /// @} group VCVRack
} // namespace VCVRack

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================
