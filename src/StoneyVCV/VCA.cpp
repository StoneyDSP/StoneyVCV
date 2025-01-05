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

#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/VCA.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>
#include <StoneyDSP/DSP.hpp>

#include <array>

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace VCA {

//==============================================================================

::rack::plugin::Model* modelVCA = ::StoneyDSP::StoneyVCV::VCA::createModelVCA(
/** name        */"VCA",
/** description */"Voltage-controlled Amplifier. Supports polyphony.",
/** manualUrl   */"https://stoneydsp.github.io/StoneyVCV/md_docs_2VCA.html",
/** hidden      */false
);

//==============================================================================

static const ::rack::math::Vec VCADimensions = ::rack::math::Vec(
/** width       */90.0F, // 15.0F * 6.0F = mm2px(5.079999999F * 3.0F = 30.479999995F)
/** height      */380.0F // mm2px(128.693333312F)
);

//==============================================================================

} // namespace VCA
} // namespace StoneyVCV
} // namespace StoneyDSP

//==============================================================================

template <typename T>
::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::VCAEngine()
:   gain(static_cast<T>(0.0)),
    lastGain(static_cast<T>(0.0))
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAEngine");
}

template <typename T>
::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::VCAEngine(T sample)
:   gain(sample),
    lastGain(sample)
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAEngine");
}

template <typename T>
::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::~VCAEngine() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::VCA::VCAEngine");

    this->gain = static_cast<T>(0.0);
    this->lastGain = static_cast<T>(0.0);
}

template <typename T>
void ::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::processSample(T* sample)
{
    *sample *= this->getGain();
}

template <typename T>
void ::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::processSampleSimd(::StoneyDSP::SIMD::float_4 *v)
{
    ::StoneyDSP::SIMD::float_4& input = *v;
    input *= this->gain;
}

template <typename T>
void ::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::processSampleSimd(::StoneyDSP::SIMD::double_2 *v)
{
    ::StoneyDSP::SIMD::double_2& input = *v;
    input *= this->gain;
}

template <typename T>
void ::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::setGain(const T &newGain)
{
    this->gain = newGain;
}

template <typename T>
T& ::StoneyDSP::StoneyVCV::VCA::VCAEngine<T>::getGain() noexcept
{
    return this->gain;
}

template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<::StoneyDSP::float_t>;
template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<::StoneyDSP::double_t>;
// template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<::rack::simd::float_4>;
// template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<::StoneyDSP::SIMD::double_2>;

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAModule::VCAModule()
:   lightDivider(),
    engine(),
    lightGains{0.0F}
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
        10.0F,                                                                  // maxValue
        10.0F,                                                                  // defaultValue
        "Gain",                                                                 // name
        "%",                                                                    // unit
        0.0F,                                                                   // displayBase
        10.0F                                                                   // displayMultiplier
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT,           // portID
        "Channel"                                                               // name
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT,            // portID
        "Control Voltage"                                                       // name
    );
    this->configOutput(
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT,         // portID
        "Channel"                                                               // name
    );
    this->configBypass(                                                         // Route input to output on bypass
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT,
        ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT
    );
    this->lightDivider.setDivision(16);
    for(auto &e : this->engine) {
        e.setGain(0.0F);
    }
}

::StoneyDSP::StoneyVCV::VCA::VCAModule::~VCAModule() noexcept
{
    DBG("Destroying StoneyVCV::VCA::VCAModule");

    for(auto &e : this->engine) {
        e.setGain(0.0F);
    }

    for(auto &lightGain : this->lightGains) {
        lightGain = (0.0F);
    }
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModule::process(const ::StoneyDSP::StoneyVCV::VCA::VCAModule::ProcessArgs &args)
{
    auto &vca_input = this->getVcaInput();
    auto &cv_input = this->getCvInput();
    auto &gain_param = this->getGainParam();
    auto &vca_output = this->getVcaOutput();
    auto &blink_light = this->lights[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT + 0];
    // auto &blink_light_r = this->lights[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT + 1];

    // if (!vca_input.isConnected() && !vca_output.isConnected() && !cv_input.isConnected()) {
    //     return;
    // }

    // Panel-based params are monophonic by nature,
    // so don't iterate over them
    const auto &gain = gain_param.getValue();

    // Get desired number of channels from a "primary" input.
	// If this input is unpatched, getChannels() returns 0, but we should
    // still generate 1 channel of output.
    ::std::size_t numChannels = ::std::max<::std::size_t>({
        1U,
        static_cast<unsigned>(vca_input.getChannels()),
        static_cast<unsigned>(cv_input.getChannels())
    });

    // Poly process block
    for (::std::size_t channel = 0U; channel < numChannels; channel++ /** channel += 4 */ ) {

        // const auto& cchannel = channel / 4;

        // Get input or 0v
        auto input = vca_input.getNormalPolyVoltage(vFloor, channel);

        // Get cv or 10v as 0..1
        const auto &cv = ::rack::clamp(cv_input.getNormalPolyVoltage(vNominal, channel) * gain * 0.01F, vFloor, vNominal);

        // Apply gain
        this->engine[channel].setGain(cv);

        // Process input
        this->engine[channel].processSample(&input);

        // Set output
        vca_output.setVoltage(input, channel);

        // Set lights
        this->lightGains[channel] = this->engine[channel].getGain();
    }

	vca_output.setChannels(numChannels);

    // Lights
    if (this->lightDivider.process()) {
        auto lightValue = *::std::max_element<StoneyDSP::float_t *>(this->lightGains.begin(), this->lightGains.end());
        // blink_light.setBrightnessSmooth(
        //     1 - (lightValue * lightValue),
        //     this->lightDivider.getDivision() * args.sampleTime
        // );
        // blink_light_r.setBrightnessSmooth(
        //     (lightValue * lightValue),
        //     this->lightDivider.getDivision() * args.sampleTime
        // );
        blink_light.setBrightnessSmooth(
            (lightValue * lightValue),
            this->lightDivider.getDivision() * args.sampleTime
        );
    }
}

::rack::engine::Input &::StoneyDSP::StoneyVCV::VCA::VCAModule::getVcaInput() noexcept
{
    return this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT];
}

::rack::engine::Input &::StoneyDSP::StoneyVCV::VCA::VCAModule::getCvInput() noexcept
{
    return this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT];
}

::rack::engine::Param &::StoneyDSP::StoneyVCV::VCA::VCAModule::getGainParam() noexcept
{
    return this->params[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::GAIN_PARAM];
}

::rack::engine::Output &::StoneyDSP::StoneyVCV::VCA::VCAModule::getVcaOutput() noexcept
{
    return this->outputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT];
}

::rack::engine::Light &::StoneyDSP::StoneyVCV::VCA::VCAModule::getBlinkLight() noexcept
{
    return this->lights[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT];
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
:   // Screws
    screwsPositions{
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // top-right
            (::StoneyDSP::StoneyVCV::VCA::VCADimensions.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::VCA::VCADimensions.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
        ::rack::math::Vec( // bottom-right
            (::StoneyDSP::StoneyVCV::VCA::VCADimensions.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::VCA::VCADimensions.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
    },
    screws{
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[2]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[3])
    }
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAWidget");
    assert(this->screws[0] != nullptr);
    assert(this->screws[1] != nullptr);
    assert(this->screws[2] != nullptr);
    assert(this->screws[3] != nullptr);

    this->setSize(::StoneyDSP::StoneyVCV::VCA::VCADimensions);

    for(const auto& screw : this->screws) {
        this->addChild(screw);
    }

    assert(static_cast<unsigned int>(this->getSize().x) == 6U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::VCA::VCAWidget::~VCAWidget()
{
    // Assertions
    DBG("Destroying StoneyVCV::VCA::VCAWidget");
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::step()
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::step();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::draw(const ::StoneyDSP::StoneyVCV::VCA::VCAWidget::DrawArgs &args)
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::VCAModuleWidget(::StoneyDSP::StoneyVCV::VCA::VCAModule* module)
:   // Panel
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
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
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
        ::rack::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
                238.000984252F
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT
        )
    ),
    portVcaInput(
        ::rack::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
                286.000984252F
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT
        )
    ),
    portVcaOutput(
        ::rack::createOutputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
                // widget is 28.55155 x 39.15691
                // port is 23.7 x 23.7
                // widget.x - port.x = 4.85155 (/ 2 = 2.425775 = edge distance)
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (309.05634F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT
        )
    ),
    // Lights
    // lightVca(
    //     ::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::GreenRedLight>>(
    //         ::rack::math::Vec(
    //             size.x * 0.5F,
    //             0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
    //         ),
    //         module, ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT
    //     )
    // ),
    lightVca(
        ::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight>>(
            ::rack::math::Vec(
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
                0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT
        )
    ),
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels)
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAModuleWidget");
    // assert(module != nullptr);
    assert(this->vcaWidget != nullptr);
    assert(this->vcaModuleWidgetFrameBuffer != nullptr);
    assert(this->panel != nullptr);

    this->portVcaInput->panel->labelText = "IN";
    this->portCvInput->panel->labelText = "CV";
    this->portVcaOutput->panel->labelText = "OUT";

    this->setModule(module);
    this->setSize(::StoneyDSP::StoneyVCV::VCA::VCADimensions);
    this->setPanel(this->panel);
    this->getPanel()->setSize(this->getSize());

    // Frame Buffer
    this->vcaModuleWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->vcaModuleWidgetFrameBuffer);

    // Widget
    this->vcaWidget->setSize(this->getSize());
    this->vcaModuleWidgetFrameBuffer->addChild(this->vcaWidget);

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

    assert(static_cast<unsigned int>(this->getSize().x) == 6U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().x) == 6U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
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
    this->setModule(NULL);
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::step()
{
    if (APP->window->pixelRatio < 2.0F) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->vcaModuleWidgetFrameBuffer->oversample = 2.0F;
	}
	else {
		this->vcaModuleWidgetFrameBuffer->oversample = 1.0F;
	}

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
