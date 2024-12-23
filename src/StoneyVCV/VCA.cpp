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

#if defined (STONEYVCV_BUILD_VCA)

//==============================================================================

#include <StoneyVCV/VCA.hpp>

//==============================================================================

#include <rack.hpp>

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace VCA {

//==============================================================================

::rack::plugin::Model* modelVCA = ::StoneyDSP::StoneyVCV::VCA::createVCA();

//==============================================================================

static const ::rack::math::Vec HP4Dimensions = (
    ::rack::window::mm2px(30.479999995F), // 5.079999999F * 3.0F
    ::rack::window::mm2px(128.693333312F)
);

//==============================================================================

} // namespace VCA
} // namespace StoneyVCV
} // namespace StoneyDSP

::StoneyDSP::StoneyVCV::VCA::VCAModule::VCAModule()
:   gain(0.0F)
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAModule");
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_PARAMS == 1U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_INPUTS == 2U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_OUTPUTS == 1U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_LIGHTS == 1U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    this->config(
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
    lightDivider.setDivision(128);
}

::StoneyDSP::StoneyVCV::VCA::VCAModule::~VCAModule()
{
    DBG("Destroying StoneyVCV::VCA::VCAModule");
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModule::process(const ::StoneyDSP::StoneyVCV::VCA::VCAModule::ProcessArgs &args)
{
    auto vca_input = inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_INPUT];
    auto cv_input = inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT];

    // Get desired number of channels from a "primary" input.
	// If this input is unpatched, getChannels() returns 0, but we should
    // still generate 1 channel of output.
    ::StoneyDSP::size_t numChannels = std::max<::StoneyDSP::size_t>({
        1,
        (::StoneyDSP::size_t)vca_input.getChannels(),
        (::StoneyDSP::size_t)cv_input.getChannels()
    });

    // Panel-based params are monophonic by nature
    float level = params[::StoneyDSP::StoneyVCV::VCA::VCAModule::GAIN_PARAM].getValue();

    for (::StoneyDSP::size_t c = 0; c < numChannels; c++) {
        // Get input
        float in = inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_INPUT].getPolyVoltage(c);

        // Get gain
        auto gainApply = level;
        if (inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT].isConnected()) {
            auto cv = ::rack::math::clamp(inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT].getPolyVoltage(c) / 10.0F, 0.0F, 1.0F);
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

    // Lights
    if (lightDivider.process()) {
        for (::StoneyDSP::size_t c = 0; c < numChannels; c++) {
            // Get output
            float out = outputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_OUTPUT].getPolyVoltage(c);

            // Get gain
            auto gainApply = level;
            if (inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT].isConnected()) {
                auto cv = ::rack::math::clamp(inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT].getPolyVoltage(c) / 10.0F, 0.0F, 1.0F);
                gainApply *= cv;
            }

            // Apply gain
            auto lightsGain = out * gainApply;

            lights[::StoneyDSP::StoneyVCV::VCA::VCAModule::BLINK_LIGHT].setBrightnessSmooth(
                ::std::abs(lightsGain),
                args.sampleTime
            );
        }
    }
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
:   vcaWidgetFrameBuffer(new ::rack::widget::FramebufferWidget),
    panelBorder(::rack::createWidget<::rack::app::PanelBorder>(::rack::math::Vec(0.0F, 0.0F)))
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAWidget");
    assert(this->vcaWidgetFrameBuffer != nullptr);
    assert(this->panelBorder != nullptr);

    // Widgets
    this->vcaWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->vcaWidgetFrameBuffer);

    // Border
    this->panelBorder->setSize(this->getSize());
    this->vcaWidgetFrameBuffer->addChild(this->panelBorder);
}

::StoneyDSP::StoneyVCV::VCA::VCAWidget::~VCAWidget()
{
    // Assertions
    DBG("Destroying StoneyVCV::VCA::VCAWidget");
    assert(!this->parent);

    // Children
    this->panelBorder->clearChildren();
    this->vcaWidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::step()
{
    const auto& size = this->getSize();

    this->panelBorder->setSize(size);
    this->vcaWidgetFrameBuffer->setSize(size);

    return ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::draw(const ::StoneyDSP::StoneyVCV::VCA::VCAWidget::DrawArgs &args)
{
    const auto& bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    const auto& bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;
    const auto& bgColor = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& minWidth = ::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH;
    const auto& minHeight = ::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT;
    const auto& size = this->getSize();

    // draw Themed BG
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg,
        0.0F,
        0.0F,
        size.x,
        size.y
    );
    ::nvgFillColor(args.vg, bgColor);
    ::nvgFill(args.vg);

    // Draw line L
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */minWidth + (minWidth * 0.5F));           /** 1.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */size.y - (minWidth + (minWidth * 0.5F)));/** 1.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line R
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */size.x - (minWidth * 0.5F),              /** 0.5 screws left  */
        /** y */minWidth + (minWidth * 0.5F));           /** 1.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth * 0.5F),              /** 0.5 screws left  */
        /** y */size.y - (minWidth + (minWidth * 0.5F)));/** 1.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line T
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */minWidth + (minWidth * 0.5F),            /** 1.5 screws right */
        /** y */minWidth * 0.5F);                        /** 0.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth + (minWidth * 0.5F)), /** 1.5 screws left  */
        /** y */minWidth * 0.5F);                        /** 0.5 screws down  */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line B
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */minWidth + (minWidth * 0.5F),            /** 1.5 screws right */
        /** y */size.y - (minWidth * 0.5F));             /** 0.5 screws up    */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth + (minWidth * 0.5F)), /** 1.5 screws left  */
        /** y */size.y - (minWidth * 0.5F));             /** 0.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    ::StoneyDSP::ignoreUnused(minHeight);

    return ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::VCAModuleWidget(::StoneyDSP::StoneyVCV::VCA::VCAModule* module)
:   size(
        ::rack::window::mm2px(30.479999995F),
        ::rack::window::mm2px(128.693333312F)
    ),
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
    ),
    vcaWidget(::rack::createWidget<::StoneyDSP::StoneyVCV::VCA::VCAWidget>(::rack::math::Vec(0.0F, 0.0F))),
    vcaModuleWidgetFrameBuffer(new ::rack::FramebufferWidget),
    // Params
    gainKnob(
        ::rack::createParamCentered<::rack::componentlibrary::RoundBigBlackKnob>(
            ::rack::math::Vec(
                size.x * 0.5F,
                0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 15.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::GAIN_PARAM
        )
    ),
    // gainSlider(
    //     ::rack::createLightParamCentered<::rack::componentlibrary::VCVLightSlider<::rack::componentlibrary::YellowLight>>(
    //         ::rack::math::Vec(
    //             size.x * 0.5F,
    //             0.0F - (this->gainSlider->getSize().y - ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F))
    //         ),
    //         module,
    //         ::StoneyDSP::StoneyVCV::VCA::VCAModule::GAIN_PARAM,
    //         ::StoneyDSP::StoneyVCV::VCA::VCAModule::BLINK_LIGHT
    //     )
    // ),
    // Ports
    portCvInput(
        ::rack::createInputCentered<::rack::componentlibrary::PJ301MPort>(
            ::rack::math::Vec(
                size.x * 0.5F,
                size.y - ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 20.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::CV_INPUT
        )
    ),
    portVcaInput(
        ::rack::createInputCentered<::rack::componentlibrary::PJ301MPort>(
            ::rack::math::Vec(
                size.x * 0.5F,
                size.y - ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_INPUT
        )
    ),
    portVcaOutput(
        ::rack::createOutputCentered<::rack::componentlibrary::PJ301MPort>(
            ::rack::math::Vec(
                size.x * 0.5F,
                size.y - ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 5.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::VCA_OUTPUT
        )
    ),
    // Lights
    lightVca(
        ::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight>>(
            ::rack::math::Vec(
                size.x * 0.5F,
                0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
            ),
            module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::BLINK_LIGHT
        )
    ),
    // Screws
    screwsPositions{
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // top-right
            (this->size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-right
            (this->size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
    },
    screws{
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[2]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[3])
    },
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels)
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAModuleWidget");
    // assert(module != nullptr);
    assert(this->vcaWidget != nullptr);
    assert(this->vcaModuleWidgetFrameBuffer != nullptr);
    assert(this->screws != nullptr);
    assert(this->screws[0] != nullptr);
    assert(this->screws[1] != nullptr);
    assert(this->screws[2] != nullptr);
    assert(this->screws[3] != nullptr);
    assert(this->panel != nullptr);

    this->setModule(module);
    this->setSize(this->size);
    this->setPanel(this->panel);
    this->getPanel()->setSize(this->getSize());

    // Frame Buffer
    this->vcaModuleWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->vcaModuleWidgetFrameBuffer);

    // Widget
    this->vcaWidget->setSize(this->getSize());
    this->vcaModuleWidgetFrameBuffer->addChild(this->vcaWidget);

    // Screws
    for(auto screw : this->screws) {
        this->addChild(screw);
    }

    // Params
    this->addParam(this->gainKnob);
    // this->addParam(this->gainSlider);
    // Inputs
    this->addInput(this->portCvInput);
    this->addInput(this->portVcaInput);
    // Outputs
    this->addOutput(this->portVcaOutput);
    // Lights
    this->addChild(this->lightVca);

    assert(this->getSize().x == ::rack::window::mm2px(30.479999995F));
    assert(this->getSize().y == ::rack::window::mm2px(128.693333312F));
    assert(this->getPanel()->getSize().x == ::rack::window::mm2px(30.479999995F));
    assert(this->getPanel()->getSize().y == ::rack::window::mm2px(128.693333312F));

}

::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::~VCAModuleWidget()
{
    // Assertions
    DBG("Destroying StoneyVCV::VCA::VCAModuleWidget");
    assert(!this->parent);

    // Children
    this->vcaWidget->clearChildren();
    this->vcaModuleWidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::step()
{
    if(this->lastPrefersDarkPanels != ::rack::settings::preferDarkPanels) {
        this->vcaModuleWidgetFrameBuffer->setDirty();
        this->lastPrefersDarkPanels = ::rack::settings::preferDarkPanels;
    }

    return ::rack::Widget::step();
}

//==============================================================================

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::VCA::createVCA() // STONEYDSP_NOEXCEPT(false)
{
    DBG("Creating StoneyVCV::VCA::modelVCA");

    ::rack::plugin::Model* modelVCA = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::VCA::VCAModule,
        ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget
    >("VCA");
    // STONEYDSP_THROW_IF_FAILED_VOID(modelVCO == nullptr, bad_alloc);
    return modelVCA;
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_VCA)

//==============================================================================
