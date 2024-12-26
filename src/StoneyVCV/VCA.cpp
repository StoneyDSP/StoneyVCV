/*******************************************************************************
 * @file src/StoneyVCV/VCA.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
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

::rack::plugin::Model* modelVCA = ::StoneyDSP::StoneyVCV::VCA::createModelVCA(
/** name        */"VCA",
/** description */"Voltage-controlled Oscillator. Supports polyphony.",
/** manualUrl   */"https://stoneydsp.github.io/StoneyVCV/md_docs_2VCA.html",
/** hidden      */false
);

//==============================================================================

static const ::rack::math::Vec VCADimensions = (
    ::rack::window::mm2px(30.479999995F), // 5.079999999F * 3.0F
    ::rack::window::mm2px(128.693333312F)
);

//==============================================================================

} // namespace VCA
} // namespace StoneyVCV
} // namespace StoneyDSP

::StoneyDSP::StoneyVCV::VCA::VCAModule::VCAModule()
// :   lastNumChannels(std::max<::StoneyDSP::size_t>({
//         1,
//         (::StoneyDSP::size_t)this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT].getChannels(),
//         (::StoneyDSP::size_t)this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT].getChannels()
//     }))
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAModule");
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::NUM_PARAMS == 1U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::NUM_INPUTS == 2U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::NUM_OUTPUTS == 1U);
    assert(::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::NUM_LIGHTS == 1U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    this->config(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::NUM_LIGHTS
    );
    this->configParam(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::GAIN_PARAM,          // paramId
        0.0F,                                                                   // minValue
        1.0F,                                                                   // maxValue
        1.0F,                                                                   // defaultValue
        "Gain",                                                                 // name
        "%",                                                                    // unit
        0.0F,                                                                   // displayBase
        100.0F                                                                  // displayMultiplier
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT,           // portID
        "IN"                                                                    // name
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT,            // portID
        "CV"                                                                    // name
    );
    this->configOutput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT,         // portID
        "OUT"                                                                   // name
    );
    this->configBypass(                                                         // Route input to output on bypass
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT
    );
    this->lightDivider.setDivision(128);
}

::StoneyDSP::StoneyVCV::VCA::VCAModule::~VCAModule()
{
    DBG("Destroying StoneyVCV::VCA::VCAModule");
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModule::process(const ::StoneyDSP::StoneyVCV::VCA::VCAModule::ProcessArgs &args)
{
    auto& vca_input = this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT];
    auto& cv_input = this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT];
    auto& gain_param = this->params[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::GAIN_PARAM];
    auto& vca_output = this->outputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT];
    auto& blink_light = this->lights[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT];

    // Panel-based params are monophonic by nature,
    // so don't iterate over them
    const auto& gain = gain_param.getValue();

    // Mono process block
    // {
    //     // Get input
    //     auto in = vca_input.getVoltage();

    //     // Get gain
    //     auto gainApply = gain;

    //     // Get CV
    //     if (cv_input.isConnected()) {
    //         // scale
    //         const auto& scaled_cv = (0.1F * cv_input.getVoltage()); // 0-100%
    //         // clamp
    //         gainApply *= ::rack::math::clamp(scaled_cv, 0.0F, 1.0F); // 0-1
    //     }

    //     // Apply gain
    //     in *= gainApply;

    //     // Set output
    //     vca_output.setVoltage(in);
    // }

    // Get desired number of channels from a "primary" input.
	// If this input is unpatched, getChannels() returns 0, but we should
    // still generate 1 channel of output.
    ::StoneyDSP::size_t numChannels = std::max<::StoneyDSP::size_t>({
        1,
        (::StoneyDSP::size_t)vca_input.getChannels(),
        (::StoneyDSP::size_t)cv_input.getChannels()
    });

    // Poly process block
    for (::StoneyDSP::size_t c = 0; c < numChannels; c++) {

        // Get input
        auto in = vca_input.getPolyVoltage(c);

        // Get gain
        auto gainApply = gain;

        // Get CV
        if (cv_input.isConnected()) {
            const auto& scaled_cv = 0.1F * cv_input.getPolyVoltage(c); // 0-100%
            gainApply *= ::rack::math::clamp(scaled_cv, 0.0F, 1.0F);
        }

        // Apply gain
        in *= gainApply;
        // lastGains[c] = gainApply;

        // Set output
        vca_output.setVoltage(in, c);
    }

	vca_output.setChannels(numChannels);
	// lastNumChannels = numChannels;

    // Lights
    ::StoneyDSP::ignoreUnused(blink_light);
    // if (lightDivider.process()) {
    // }
}

// ::json_t *::StoneyDSP::StoneyVCV::VCA::VCAModule::dataToJson()
// {
//     ::json_t *rootJ = ::json_object();
//     ::json_object_set_new(rootJ, "gain", ::json_real(gain));

//     return rootJ;
// }

// void ::StoneyDSP::StoneyVCV::VCA::VCAModule::dataFromJson(::json_t *rootJ)
// {
//     ::json_t *gainJ = ::json_object_get(rootJ, "gain");
//     if (gainJ)
//         gain = json_number_value(gainJ);
// }

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
    const auto& minWidth = ::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH;
    const auto& minHeight = ::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT;
    const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    const auto& bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;
    const auto& bgColor = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    const auto& bgGradientS0 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS0;
    const auto& bgGradientS1 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS1;

    const auto& size = this->getSize();

    // draw Themed BG
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg,
        /** x */0.0F,
        /** y */0.0F,
        /** w */size.x,
        /** h */size.y
    );
    ::nvgFillColor(args.vg, bgColor);
    ::nvgFill(args.vg);

    // Draw themed BG gradient
    const auto& bgGradient = ::nvgLinearGradient(args.vg,
        /** x */size.x * 0.5,
        /** Y */0.0F,
        /** w */size.x * 0.5,
        /** h */380.0F,
        /** s1 */bgGradientS0,
        /** s2 */bgGradientS1
    );
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg,
        /** x */0.0F,
        /** y */0.0F,
        /** w */size.x,
        /** h */size.y
    );
    ::nvgFillPaint(args.vg, bgGradient);
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
                ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/VCA-light.svg"
            ),
            // Dark-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/VCA-dark.svg"
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
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::GAIN_PARAM
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
        ::rack::createInputCentered<::rack::componentlibrary::ThemedPJ301MPort>(
            ::rack::math::Vec(
                size.x * 0.5F,
                size.y - ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 20.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT
        )
    ),
    portVcaInput(
        ::rack::createInputCentered<::rack::componentlibrary::ThemedPJ301MPort>(
            ::rack::math::Vec(
                size.x * 0.5F,
                size.y - ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT
        )
    ),
    portVcaOutput(
        ::rack::createOutputCentered<::rack::componentlibrary::ThemedPJ301MPort>(
            ::rack::math::Vec(
                size.x * 0.5F,
                size.y - ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 5.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT
        )
    ),
    // Lights
    lightVca(
        ::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight>>(
            ::rack::math::Vec(
                size.x * 0.5F,
                0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
            ),
            module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT
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
            (this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
        ::rack::math::Vec( // bottom-right
            (this->size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
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
    for(const auto& screw : this->screws) {
        assert(screw != nullptr);
    }

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
    for(const auto& screw : this->screws) {
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

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::VCA::createModelVCA(
    ::std::string name,
    ::std::string description,
    ::std::string manualUrl,
    bool hidden
) noexcept(false) // STONEYDSP_NOEXCEPT(false)
{
    DBG("Creating StoneyVCV::VCA::modelVCA");

    ::rack::plugin::Model* modelVCA = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::VCA::VCAModule,
        ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget
    >("VCA"); // slug must never change!

    if(modelVCA == nullptr)
        throw ::rack::Exception("createModelVCA generated a nullptr");

    if(!description.empty())
        modelVCA->description = description;
    if(!manualUrl.empty())
        modelVCA->manualUrl = manualUrl;
    if(!name.empty())
        modelVCA->name = name;
    if(!hidden)
        modelVCA->hidden = hidden;

    return modelVCA;
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_VCA)

//==============================================================================
