/*******************************************************************************
 * @file VCA.cpp
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

//==============================================================================

#include <StoneyVCV/VCA.hpp>

//==============================================================================

#include <rack.hpp>

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAModule::VCAModule()
 : gain(0.0F)
{
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_PARAMS == 1U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_INPUTS == 2U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_OUTPUTS == 1U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_LIGHTS == 1U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_LIGHTS
    );
    configParam(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::GAIN_PARAM,     // paramId
        0.0F,                                                   // minValue
        1.0F,                                                   // maxValue
        1.0F,                                                   // defaultValue
        "Gain",                                                 // name
        "%",                                                    // unit
        0.0F,                                                   // displayBase
        100.0F                                                  // displayMultiplier
    );
    configInput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_INPUT,      // portID
        "IN"                                                    // name
    );
    configInput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT,       // portID
        "CV"                                                    // name
    );
    configOutput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_OUTPUT,     // portID
        "OUT"                                                   // name
    );
}

::StoneyDSP::StoneyVCV::VCA::VCAModule::~VCAModule()
{

}

void ::StoneyDSP::StoneyVCV::VCA::VCAModule::process(const ::StoneyDSP::StoneyVCV::VCA::VCAModule::ProcessArgs &args)
{
    auto vca_input = inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_INPUT];
    auto cv_input = inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT];

    // Get desired number of channels from a "primary" input.
	// If this input is unpatched, getChannels() returns 0, but we should
    // still generate 1 channel of output.
    ::StoneyDSP::uint32_t numChannels = std::max({
        1,
        vca_input.getChannels(),
        cv_input.getChannels()
    });

    // Panel-based params are monophonic by nature
    float level = params[::StoneyDSP::StoneyVCV::VCA::VCAModule::GAIN_PARAM].getValue();

    for (::StoneyDSP::uint32_t c = 0; c < numChannels; c++) {
			// Get input
			float in = inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_INPUT].getPolyVoltage(c);

			// Get gain
			auto gainApply = level;
			if (inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT].isConnected()) {
				auto cv = ::rack::clamp(inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT].getPolyVoltage(c) / 10.0f, 0.0f, 1.0f);
				// if (int(params[EXP_PARAM].getValue()) == 0)
				// 	cv = std::pow(cv, 4.f);
				gainApply *= cv;
			}

			// Apply gain
			in *= gainApply;
			lastGains[c] = gainApply;

			// Set output
			outputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_OUTPUT].setVoltage(in, c);
		}

	outputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_OUTPUT].setChannels(numChannels);
	lastChannels = numChannels;
}

::json_t *::StoneyDSP::StoneyVCV::VCA::VCAModule::dataToJson()
{
    ::json_t *rootJ = ::json_object();
    ::json_object_set_new(rootJ, "gain", ::json_real(gain));
    return rootJ;
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModule::dataFromJson(::json_t *rootJ)
{
    ::json_t *gainJ = ::json_object_get(rootJ, "gain");
    if (gainJ)
        gain = json_number_value(gainJ);
}

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAWidget::VCAWidget()
{
    // Widgets
    vcaWidgetFrameBuffer = new ::rack::FramebufferWidget;
    vcaWidgetFrameBuffer->setSize(box.size);
    addChild(vcaWidgetFrameBuffer);

    panelBorder = ::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0F, 0.0F));
    panelBorder->setSize(box.size);
    vcaWidgetFrameBuffer->addChild(panelBorder);
}

// ::StoneyDSP::StoneyVCV::VCA::VCAWidget::~VCAWidget()
// {
// }

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::step()
{
    panelBorder->box.size = box.size;
    ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::draw(const ::StoneyDSP::StoneyVCV::VCA::VCAWidget::DrawArgs &args)
{
    ::NVGcolor& bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    ::NVGcolor& bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;

    // draw Themed BG
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg, 0.0F, 0.0F, box.size.x, box.size.y);
    ::NVGcolor bg = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    ::nvgFillColor(args.vg, bg);
    ::nvgFill(args.vg);
    ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::VCAModuleWidget(::StoneyDSP::StoneyVCV::VCA::VCAModule* module)
:   size(::rack::window::mm2px(30.479999995F), ::rack::window::mm2px(128.693333312F)),
    vcaWidget(::rack::createWidget<::StoneyDSP::StoneyVCV::VCA::VCAWidget>(::rack::math::Vec(0.0F, 0.0F))),
    vcaModuleWidgetFrameBuffer(new ::rack::FramebufferWidget),
    // Screws
    screwT1Pos(::rack::math::Vec((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F), (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // top-left
    screwT2Pos(::rack::math::Vec((size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)), (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // top-right
    screwB1Pos(::rack::math::Vec((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F), size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // bottom-left
    screwB2Pos(::rack::math::Vec((size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)), size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // bottom-right
    screwT1(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwT1Pos)),
    screwT2(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwT2Pos)),
    screwB1(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwB1Pos)),
    screwB2(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwB2Pos)),
    // Panel
    panel(
        ::rack::createPanel<::rack::app::ThemedSvgPanel>(
            // Light-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::pluginInstance, "res/VCA-light.svg"
            ),
            // Dark-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::pluginInstance, "res/VCA-dark.svg"
            )
        )
    )
{
    setModule(module);
    setSize(size);
    setPanel(panel);

    vcaWidget->setSize(this->getSize());
    addChild(vcaWidget);

    // // Frame Buffer
    // vcaModuleWidgetFrameBuffer->setSize(box.size);
    // addChild(vcaModuleWidgetFrameBuffer);

    // // Widget
    // vcaWidget->setSize(box.size);
    // vcaModuleWidgetFrameBuffer->addChild(vcaWidget);

    addChild(screwT1);
    addChild(screwT2);
    addChild(screwB1);
    addChild(screwB2);

    // Params
    addParam(::rack::createParamCentered<::rack::componentlibrary::RoundBigBlackKnob>(::rack::window::mm2px(::rack::math::Vec(box.size.x * 0.5F, 34.068F)), module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::GAIN_PARAM));
    // Inputs
    addInput(::rack::createInputCentered<::rack::componentlibrary::PJ301MPort>(::rack::window::mm2px(::rack::math::Vec(box.size.x * 0.5F, 58.4275F)), module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT));
    addInput(::rack::createInputCentered<::rack::componentlibrary::PJ301MPort>(::rack::window::mm2px(::rack::math::Vec(box.size.x * 0.5F, 82.7865F)), module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_INPUT));
    // Outputs
    addOutput(::rack::createOutputCentered<::rack::componentlibrary::PJ301MPort>(::rack::window::mm2px(::rack::math::Vec(box.size.x * 0.5F, 107.1455F)), module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_OUTPUT));
    // Lights
    addChild(::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight>>(::rack::window::mm2px(::rack::math::Vec(box.size.x * 0.5F, 21.889F)), module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::BLINK_LIGHT));

    assert(this->getSize().x == ::rack::window::mm2px(30.479999995F));
    assert(this->getSize().y == ::rack::window::mm2px(128.693333312F));
}

// ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::~VCAModuleWidget()
// {
//     delete vcaModuleWidgetFrameBuffer;
// }

//==============================================================================

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::VCA::createVCA() // STONEYDSP_NOEXCEPT(false)
{
    ::rack::plugin::Model* modelVCA = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::VCA::VCAModule,
        ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget
    >("VCA");
    // STONEYDSP_THROW_IF_FAILED_VOID(modelVCO == nullptr, bad_alloc);
    return modelVCA;
}

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

namespace VCA {

//==============================================================================

::rack::plugin::Model* modelVCA = ::StoneyDSP::StoneyVCV::VCA::createVCA();

//==============================================================================

} // namespace VCA

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================
