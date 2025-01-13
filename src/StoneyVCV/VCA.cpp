/*******************************************************************************
 * @file src/StoneyVCV/VCA.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_VCA)

//==============================================================================

#include <StoneyVCV/VCA.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary/PortWidget.hpp>
#include <StoneyVCV/ComponentLibrary/PanelWidget.hpp>
#include <StoneyVCV/ComponentLibrary/RoundKnob.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>

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
:   ::StoneyDSP::StoneyVCV::Engine<T>(),
    gain(static_cast<T>(0.0)),
    lastGain(static_cast<T>(0.0))
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
    *sample *= this->gain;
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

template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<double>;
template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<float>;

// template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<::rack::simd::float_4>;
// template struct ::StoneyDSP::StoneyVCV::VCA::VCAEngine<::StoneyDSP::SIMD::double_2>;

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAModule::VCAModule()
:   ::rack::engine::Module::Module(),
    lightDivider(),
    engine(),
    lightGains{0.0F},
    vcaInputPtr(nullptr),
    cvInputPtr(nullptr),
    gainParamPtr(nullptr),
    vcaOutputPtr(nullptr),
    blinkLightPtr(nullptr)
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

    this->vcaInputPtr = dynamic_cast<::rack::engine::Input*>(&this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT]);
    this->cvInputPtr = dynamic_cast<::rack::engine::Input*>(&this->inputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT]);
    this->gainParamPtr = dynamic_cast<::rack::engine::Param*>(&this->params[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::GAIN_PARAM]);
    this->vcaOutputPtr = dynamic_cast<::rack::engine::Output*>(&this->outputs[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::VCA_OUTPUT]);
    this->blinkLightPtr = dynamic_cast<::rack::engine::Light*>(&this->lights[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT]);

    assert(this->vcaInputPtr != nullptr);
    assert(this->cvInputPtr != nullptr);
    assert(this->gainParamPtr != nullptr);
    assert(this->vcaOutputPtr != nullptr);
    assert(this->blinkLightPtr != nullptr);
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

    this->vcaInputPtr = nullptr;
    this->cvInputPtr = nullptr;
    this->gainParamPtr = nullptr;
    this->vcaOutputPtr = nullptr;
    this->blinkLightPtr = nullptr;
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModule::process(const ::StoneyDSP::StoneyVCV::VCA::VCAModule::ProcessArgs &args)
{
    auto &vca_input = *this->vcaInputPtr;
    auto &cv_input = *this->cvInputPtr;
    auto &gain_param = *this->gainParamPtr;
    auto &vca_output = *this->vcaOutputPtr;
    auto &blink_light = *this->blinkLightPtr;
    // auto &blink_light = this->lights[::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT + 0];
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
    // (allocation)
    ::std::size_t numChannels = ::std::max<::std::size_t>({
        1U,
        static_cast<unsigned int>(vca_input.getChannels()),
        static_cast<unsigned int>(cv_input.getChannels())
    });

    // Poly process block
    for (::std::size_t channel = 0U; channel < numChannels; channel++ /** channel += 4 */ ) {

        // const auto& cchannel = channel / 4;

        // Get input or 0v (allocation)
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

::std::size_t StoneyDSP::StoneyVCV::VCA::VCAModule::getVcaInputNumChannels() noexcept
{
    return static_cast<unsigned>(this->vcaInputPtr->getChannels());
}

::std::size_t StoneyDSP::StoneyVCV::VCA::VCAModule::getCvInputNumChannels() noexcept
{
    return static_cast<unsigned>(this->cvInputPtr->getChannels());
}

::std::size_t StoneyDSP::StoneyVCV::VCA::VCAModule::getMinNumChannels() noexcept
{
    ::std::size_t minNumChannels = ::std::max<::std::size_t>({
        1U,
        this->getVcaInputNumChannels(),
        this->getCvInputNumChannels()
    });

    return minNumChannels;
}

::rack::engine::Input &::StoneyDSP::StoneyVCV::VCA::VCAModule::getVcaInput() noexcept
{
    return *this->vcaInputPtr;
}

::rack::engine::Input &::StoneyDSP::StoneyVCV::VCA::VCAModule::getCvInput() noexcept
{
    return *this->cvInputPtr;
}

::rack::engine::Param &::StoneyDSP::StoneyVCV::VCA::VCAModule::getGainParam() noexcept
{
    return *this->gainParamPtr;
}

::rack::engine::Output &::StoneyDSP::StoneyVCV::VCA::VCAModule::getVcaOutput() noexcept
{
    return *this->vcaOutputPtr;
}

::rack::engine::Light &::StoneyDSP::StoneyVCV::VCA::VCAModule::getBlinkLight() noexcept
{
    return *this->blinkLightPtr;
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
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget()
{
    DBG("Constructing StoneyVCV::VCA::VCAWidget");

    this->setSize(::StoneyDSP::StoneyVCV::VCA::VCADimensions);

    this->fb->setSize(this->getSize());

    this->screwsPositions = {
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
    };
    this->screws[0]->setPosition( // Centered
        this->screwsPositions[0].minus(this->screws[0]->getSize().div(2.0F))
    );
    this->screws[1]->setPosition( // Centered
        this->screwsPositions[1].minus(this->screws[1]->getSize().div(2.0F))
    );
    this->screws[2]->setPosition( // Centered
        this->screwsPositions[2].minus(this->screws[2]->getSize().div(2.0F))
    );
    this->screws[3]->setPosition( // Centered
        this->screwsPositions[3].minus(this->screws[3]->getSize().div(2.0F))
    );
    this->fb->setDirty();

    // Assertions
    assert(static_cast<unsigned int>(this->getSize().x) == 6U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->fb->getSize().x) == 6U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->fb->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::VCA::VCAWidget::~VCAWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::VCA::VCAWidget");
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::step()
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::step();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAWidget::draw(const ::StoneyDSP::StoneyVCV::VCA::VCAWidget::DrawArgs &args)
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::VCAModuleWidget(::StoneyDSP::StoneyVCV::VCA::VCAModule* module)
:   ::rack::app::ModuleWidget(),
    // Panel
    panel(nullptr),
    vcaWidget(nullptr),
    vcaModuleWidgetFrameBuffer(nullptr),
    // Params
    gainKnob(nullptr),
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
    portCvInput(nullptr),
    portVcaInput(nullptr),
    portVcaOutput(nullptr),
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
    lightVca(nullptr),
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels),
    prefersDarkPanelsPtr(nullptr),
    lastPixelRatio(APP->window->pixelRatio),
    pixelRatioPtr(nullptr)
{
    // Assertions
    DBG("Constructing StoneyVCV::VCA::VCAModuleWidget");

    this->panel = dynamic_cast<::rack::app::ThemedSvgPanel *>(
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
    );
    this->vcaWidget = dynamic_cast<::StoneyDSP::StoneyVCV::VCA::VCAWidget *>(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::VCA::VCAWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            ::StoneyDSP::StoneyVCV::VCA::VCADimensions
        )
    );
    this->vcaModuleWidgetFrameBuffer = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget *>(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            ::StoneyDSP::StoneyVCV::VCA::VCADimensions
        )
    );
    this->gainKnob = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::RoundBlackKnob *>(
        ::rack::createParamCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::RoundBlackKnob>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F),
                (0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 15.0F))
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::GAIN_PARAM
        )
    );
    this->portCvInput = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
                238.000984252F
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::CV_INPUT
        )
    );
    this->portVcaInput = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
                286.000984252F
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::VCA_INPUT
        )
    );
    this->portVcaOutput = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createOutputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
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
    );
    this->lightVca = dynamic_cast<::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight> *>(
        ::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight>>(
            ::rack::math::Vec(
                ::StoneyDSP::StoneyVCV::VCA::VCADimensions.x * 0.5F,
                0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::BLINK_LIGHT
        )
    );

    this->prefersDarkPanelsPtr = static_cast<const bool *>(&::rack::settings::preferDarkPanels);
    this->pixelRatioPtr = static_cast<const float *>(&APP->window->pixelRatio);

    this->portVcaInput->panel->labelText = "IN";
    this->portCvInput->panel->labelText = "CV";
    this->portVcaOutput->panel->labelText = "OUT";

    this->setModule(module);
    this->setSize(::StoneyDSP::StoneyVCV::VCA::VCADimensions);

    // Panel (calls addChildBottom)
    this->setPanel(this->panel);
    this->getPanel()->setSize(this->getSize());

    // Frame Buffer
    this->addChild(this->vcaModuleWidgetFrameBuffer);

    // Widget
    this->vcaModuleWidgetFrameBuffer->addChildBottom(this->vcaWidget);

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

    // Oversample
    if (static_cast<unsigned int>(APP->window->pixelRatio) < static_cast<unsigned int>(2.0F)) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->vcaModuleWidgetFrameBuffer->oversample = 2.0F;
	}
	else {
		this->vcaModuleWidgetFrameBuffer->oversample = 1.0F;
	}

    // assert(module != nullptr);
    assert(this->panel != nullptr);
    assert(this->vcaWidget != nullptr);
    assert(this->vcaModuleWidgetFrameBuffer != nullptr);
    assert(this->gainKnob != nullptr);
    assert(this->portCvInput != nullptr);
    assert(this->portVcaInput != nullptr);
    assert(this->portVcaOutput != nullptr);
    assert(this->lightVca != nullptr);
    assert(this->prefersDarkPanelsPtr != nullptr);
    assert(this->pixelRatioPtr != nullptr);

    assert(static_cast<unsigned int>(this->getSize().x) == 6U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().x) == 6U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::~VCAModuleWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::VCA::VCAModuleWidget");
    assert(!this->parent);

    // Children
    // this->vcaWidget->clearChildren();
    this->vcaModuleWidgetFrameBuffer->clearChildren();
    this->clearChildren();
    this->setModule(NULL);

    this->panel = nullptr;
    this->vcaWidget = nullptr;
    this->vcaModuleWidgetFrameBuffer = nullptr;
    this->gainKnob = nullptr;
    this->portCvInput = nullptr;
    this->portVcaInput = nullptr;
    this->portVcaOutput = nullptr;
    this->lightVca = nullptr;
    this->prefersDarkPanelsPtr = nullptr;
    this->pixelRatioPtr = nullptr;
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::step()
{
    const bool &currentPrefersDarkPanels = *this->prefersDarkPanelsPtr;
    const float &currentPixelRatio = *this->pixelRatioPtr;

    if(this->lastPrefersDarkPanels != currentPrefersDarkPanels) {
        // Dispatch event
        PrefersDarkPanelsChangeEvent ePrefersDarkPanelsChanged;
        ePrefersDarkPanelsChanged.newPrefersDarkPanels = currentPrefersDarkPanels;
        this->onPrefersDarkPanelsChange(ePrefersDarkPanelsChanged);
        // Update
        this->lastPrefersDarkPanels = currentPrefersDarkPanels;
    }

    if(this->lastPixelRatio != currentPixelRatio) {
        // Dispatch event
        PixelRatioChangeEvent ePixelRatioChanged;
        ePixelRatioChanged.newPixelRatio = currentPixelRatio;
        this->onPixelRatioChange(ePixelRatioChanged);
        // Update
        this->lastPixelRatio = currentPixelRatio;
    }

    return ::rack::app::ModuleWidget::step();
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::draw(const ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::DrawArgs &args)
{
    return ::rack::app::ModuleWidget::draw(args);
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::onPrefersDarkPanelsChange(const PrefersDarkPanelsChangeEvent & e)
{
    // Validate
    if(this->lastPrefersDarkPanels == e.newPrefersDarkPanels)
        return;

    this->vcaModuleWidgetFrameBuffer->setDirty();
}

const bool &::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::getPrefersDarkPanels() const noexcept
{
    return *this->prefersDarkPanelsPtr;
}

void ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::onPixelRatioChange(const PixelRatioChangeEvent & e)
{
    // Validate
    if(this->lastPixelRatio == e.newPixelRatio)
        return;

    // Oversample
    if (static_cast<unsigned int>(APP->window->pixelRatio) < static_cast<unsigned int>(2.0F)) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->vcaModuleWidgetFrameBuffer->oversample = 2.0F;
	}
	else {
		this->vcaModuleWidgetFrameBuffer->oversample = 1.0F;
	}

    this->vcaModuleWidgetFrameBuffer->setDirty();
}

const float &StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::getPixelRatio() const noexcept
{
    return *this->pixelRatioPtr;
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
