/***************************************************************************//**
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

#include "StoneyVCV/VCA.hpp"

//==============================================================================

namespace StoneyDSP {

namespace StoneyVCV {

::rack::plugin::Model* modelVCA = NULL;

}

}

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace VCVRack {

//==============================================================================

::StoneyDSP::VCVRack::VCA::VCA()
 : gain(0.0F)
{
    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::VCVRack::VCA::PARAMS_LEN,   // numParams
        ::StoneyDSP::VCVRack::VCA::INPUTS_LEN,   // numInputs
        ::StoneyDSP::VCVRack::VCA::OUTPUTS_LEN,  // numOutputs
        ::StoneyDSP::VCVRack::VCA::LIGHTS_LEN    // numLights
    );
    configParam(
        ::StoneyDSP::VCVRack::VCA::GAIN_PARAM,   // paramId
        0.0f,                                    // minValue
        1.0f,                                    // maxValue
        1.0f,                                    // defaultValue
        "Gain",                                  // name
        "%",                                     // unit
        0.0f,                                    // displayBase
        100.0f                                   // displayMultiplier
    );
    configInput(
        ::StoneyDSP::VCVRack::VCA::VCA_INPUT,    // portID
        "IN"                                     // name
    );
    configInput(
        ::StoneyDSP::VCVRack::VCA::CV_INPUT,     // portID
        "CV"                                     // name
    );
    configOutput(
        ::StoneyDSP::VCVRack::VCA::VCA_OUTPUT,   // portID
        "OUT"                                    // name
    );
}

::StoneyDSP::VCVRack::VCA::~VCA()
{

}

void ::StoneyDSP::VCVRack::VCA::process(const ::StoneyDSP::VCVRack::VCA::ProcessArgs &args)
{
    auto vca_input = inputs[::StoneyDSP::VCVRack::VCA::VCA_INPUT];
    auto cv_input = inputs[::StoneyDSP::VCVRack::VCA::CV_INPUT];

    // Get desired number of channels from a "primary" input.
	// If this input is unpatched, getChannels() returns 0, but we should
    // still generate 1 channel of output.
    ::StoneyDSP::uint32_t numChannels = std::max({
        1,
        vca_input.getChannels(),
        cv_input.getChannels()
    });

    // Panel-based params are monophonic by nature
    float level = params[::StoneyDSP::VCVRack::VCA::GAIN_PARAM].getValue();

    for (::StoneyDSP::uint32_t c = 0; c < numChannels; c++) {
			// Get input
			float in = inputs[::StoneyDSP::VCVRack::VCA::VCA_INPUT].getPolyVoltage(c);

			// Get gain
			auto gainApply = level;
			if (inputs[::StoneyDSP::VCVRack::VCA::CV_INPUT].isConnected()) {
				auto cv = ::rack::clamp(inputs[::StoneyDSP::VCVRack::VCA::CV_INPUT].getPolyVoltage(c) / 10.0f, 0.0f, 1.0f);
				// if (int(params[EXP_PARAM].getValue()) == 0)
				// 	cv = std::pow(cv, 4.f);
				gainApply *= cv;
			}

			// Apply gain
			in *= gainApply;
			lastGains[c] = gainApply;

			// Set output
			outputs[::StoneyDSP::VCVRack::VCA::VCA_OUTPUT].setVoltage(in, c);
		}

	outputs[::StoneyDSP::VCVRack::VCA::VCA_OUTPUT].setChannels(numChannels);
	lastChannels = numChannels;
}

::json_t *::StoneyDSP::VCVRack::VCA::dataToJson()
{
    ::json_t *rootJ = ::json_object();
    ::json_object_set_new(rootJ, "gain", ::json_real(gain));
    return rootJ;
}

void ::StoneyDSP::VCVRack::VCA::dataFromJson(::json_t *rootJ)
{
    ::json_t *gainJ = ::json_object_get(rootJ, "gain");
    if (gainJ)
        gain = json_number_value(gainJ);
}

//==============================================================================

::StoneyDSP::VCVRack::VCAWidget::VCAWidget()
{
    // Widgets
    vcaWidgetFrameBuffer = new ::rack::FramebufferWidget;
    vcaWidgetFrameBuffer->setSize(box.size);
    addChild(vcaWidgetFrameBuffer);

    panelBorder = ::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0f, 0.0f));
    panelBorder->setSize(box.size);
    vcaWidgetFrameBuffer->addChild(panelBorder);
}

::StoneyDSP::VCVRack::VCAWidget::~VCAWidget()
{

}

void ::StoneyDSP::VCVRack::VCAWidget::step()
{
    panelBorder->box.size = box.size;
    ::StoneyDSP::VCVRack::Widget::step();
}

void ::StoneyDSP::VCVRack::VCAWidget::draw(const ::StoneyDSP::VCVRack::Widget::DrawArgs &args)
{

    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg, 0.0, 0.0, box.size.x, box.size.y);
    ::NVGcolor bg = ::rack::settings::preferDarkPanels ? ::nvgRGB(42, 42, 42) : ::nvgRGB(235, 235, 235);
    ::nvgFillColor(args.vg, bg);
    ::nvgFill(args.vg);
    ::StoneyDSP::VCVRack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::VCVRack::VCAModuleWidget::VCAModuleWidget(::StoneyDSP::VCVRack::VCA* module)
{
    setModule(module);
    setPanel(::rack::createPanel(
        ::rack::asset::plugin(::StoneyDSP::VCVRack::pluginInstance, "res/VCA-light.svg"),
        ::rack::asset::plugin(::StoneyDSP::VCVRack::pluginInstance, "res/VCA-dark.svg")
    ));
    // // Widgets
    // vcaModuleWidgetFrameBuffer = new ::rack::FramebufferWidget;
    // vcaModuleWidgetFrameBuffer->setSize(box.size);
    // addChild(vcaModuleWidgetFrameBuffer);
    // //
    // vcaWidget = ::rack::createWidget<::StoneyDSP::VCVRack::VCAWidget>(::rack::math::Vec(0.0f, 0.0f));
    // vcaWidget->setSize(box.size);
    // vcaModuleWidgetFrameBuffer->addChild(vcaWidget);
    // Screws
    ::rack::math::Vec screwAPos = ::rack::math::Vec(::rack::RACK_GRID_WIDTH, 0.0f); // top-left
    ::rack::math::Vec screwBPos = ::rack::math::Vec(box.size.x - 2.0f * ::rack::RACK_GRID_WIDTH, 0.0f); // top-right
    ::rack::math::Vec screwCPos = ::rack::math::Vec(::rack::RACK_GRID_WIDTH, ::rack::RACK_GRID_HEIGHT - ::rack::RACK_GRID_WIDTH); // bottom-left
    ::rack::math::Vec screwDPos = ::rack::math::Vec(box.size.x - 2.0f * ::rack::RACK_GRID_WIDTH, ::rack::RACK_GRID_HEIGHT - ::rack::RACK_GRID_WIDTH); // bottom-right
    //
    ::rack::componentlibrary::ThemedScrew *screwA = ::rack::createWidget<::rack::componentlibrary::ThemedScrew>(screwAPos);
    ::rack::componentlibrary::ThemedScrew *screwB = ::rack::createWidget<::rack::componentlibrary::ThemedScrew>(screwBPos);
    ::rack::componentlibrary::ThemedScrew *screwC = ::rack::createWidget<::rack::componentlibrary::ThemedScrew>(screwCPos);
    ::rack::componentlibrary::ThemedScrew *screwD = ::rack::createWidget<::rack::componentlibrary::ThemedScrew>(screwDPos);
    //
    addChild(screwA);
    addChild(screwB);
    addChild(screwC);
    addChild(screwD);
    // Params
    addParam(::rack::createParamCentered<::rack::componentlibrary::RoundBigBlackKnob>(::rack::window::mm2px(::rack::math::Vec(15.24f, 34.068f)), module, ::StoneyDSP::VCVRack::VCA<T>::GAIN_PARAM));
    // Inputs
    addInput(::rack::createInputCentered<::rack::componentlibrary::PJ301MPort>(::rack::window::mm2px(::rack::math::Vec(15.24f, 58.4275f)), module, ::StoneyDSP::VCVRack::VCA<T>::CV_INPUT));
    addInput(::rack::createInputCentered<::rack::componentlibrary::PJ301MPort>(::rack::window::mm2px(::rack::math::Vec(15.24f, 82.7865f)), module, ::StoneyDSP::VCVRack::VCA<T>::VCA_INPUT));
    // Outputs
    addOutput(::rack::createOutputCentered<::rack::componentlibrary::PJ301MPort>(::rack::window::mm2px(::rack::math::Vec(15.24f, 107.1455f)), module, ::StoneyDSP::VCVRack::VCA<T>::VCA_OUTPUT));
    // Lights
    addChild(::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight>>(::rack::window::mm2px(::rack::math::Vec(15.24f, 21.889f)), module, ::StoneyDSP::VCVRack::VCA<T>::BLINK_LIGHT));
}

::StoneyDSP::VCVRack::VCAModuleWidget::~VCAModuleWidget()
{
    // delete vcaModuleWidgetFrameBuffer;
}

//==============================================================================

::rack::plugin::Model* createVCA() // STONEYDSP_NOEXCEPT(false)
{
    ::rack::plugin::Model* modelVCA = ::rack::createModel<::StoneyDSP::VCVRack::VCA, ::StoneyDSP::VCVRack::VCAModuleWidget>("VCA");
    // STONEYDSP_THROW_IF_FAILED_VOID(modelVCO == nullptr, bad_alloc);
    return modelVCA;
}

//==============================================================================

::rack::plugin::Model* modelVCA = ::StoneyDSP::VCVRack::createVCA();

//==============================================================================

} // namespace VCVRack

//==============================================================================

} // namespace StoneyDSP

//==============================================================================
