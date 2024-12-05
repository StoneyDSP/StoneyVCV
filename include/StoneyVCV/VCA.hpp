/***************************************************************************//**
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

#define VCA_HPP_INCLUDED 1

//==============================================================================

#include <rack.hpp>

#include "plugin.hpp"
#include "StoneyDSP/Core.hpp"
#include "StoneyDSP/DSP.hpp"
#include "StoneyDSP/SIMD.hpp"

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
 * @brief The `VCAModule` class.
 *
 */
struct VCAModule final : ::rack::engine::Module
{
public:

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

    ::StoneyDSP::float_t gain;

    int lastChannels = 1;
	::StoneyDSP::float_t lastGains[16] = {};

    enum ParamsId {
        GAIN_PARAM,
        PARAMS_LEN
    };
	enum InputsId {
		VCA_INPUT,
        CV_INPUT,
		INPUTS_LEN
	};
	enum OutputsId {
		VCA_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightsId {
		BLINK_LIGHT,
		LIGHTS_LEN
	};

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

    /**
     * @brief Advances the module by one audio sample.
     *
     * @param args
     */
    virtual void process(const ::StoneyDSP::StoneyVCV::VCAModule::ProcessArgs &args) override;

    ::json_t *dataToJson() override;

    void dataFromJson(::json_t *rootJ) override;

private:
    STONEYDSP_DECLARE_NON_COPYABLE(VCAModule)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAModule)
};

//==============================================================================

/**
 * @brief The `VCAWidget` class.
 *
 */
struct VCAWidget final : ::rack::Widget
{
public:
    VCAWidget();
    ~VCAWidget();
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
    void draw(const ::rack::Widget::DrawArgs &args) override;
    ::rack::FramebufferWidget *vcaWidgetFrameBuffer;
    ::rack::Widget *panelBorder;
private:
    STONEYDSP_DECLARE_NON_COPYABLE(VCAWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAWidget)
};

//==============================================================================

/**
 * @brief The `VCAModuleWidget` class.
 *
 */
struct VCAModuleWidget final : ::rack::app::ModuleWidget
{
public:
    VCAModuleWidget(::StoneyDSP::StoneyVCV::VCAModule* module);
    ~VCAModuleWidget();
    // ::StoneyDSP::StoneyVCV::VCAWidget *vcaWidget;
    // ::rack::FramebufferWidget *vcaModuleWidgetFrameBuffer;
private:
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

  /// @} group VCVRack
} // namespace VCVRack

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================
