/*******************************************************************************
 * @file src/StoneyVCV/LFO.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_LFO)

//==============================================================================

#include <StoneyVCV/LFO.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/PortWidget.hpp>
#include <StoneyVCV/ComponentLibrary/ParamWidget.hpp>
#include <StoneyVCV/ComponentLibrary/PanelWidget.hpp>
#include <StoneyVCV/ComponentLibrary/RoundKnobWidget.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>
#include <StoneyDSP/DSP.hpp>

//==============================================================================

#include <array>

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace LFO {

//==============================================================================

::rack::plugin::Model* modelLFO = ::StoneyDSP::StoneyVCV::LFO::createModelLFO(
/** name        */"LFO",
/** description */"Low-frequency Oscillator. Supports polyphony.",
/** manualUrl   */"https://stoneydsp.github.io/StoneyVCV/md_docs_2LFO.html",
/** hidden      */false
);

//==============================================================================

static const ::rack::math::Vec LFODimensions = ::rack::math::Vec(
    135.0F,
    380.0F
    // ::rack::window::mm2px(30.479999995F), // 5.079999999F * 3.0F
    // ::rack::window::mm2px(128.693333312F)
);

//==============================================================================

} // namespace LFO
} // namespace StoneyVCV
} // namespace StoneyDSP

//==============================================================================

template <typename T>
::StoneyDSP::StoneyVCV::LFO::LFOEngine<T>::LFOEngine()
:   frequency(static_cast<T>(2.0)),
    lastFrequency(static_cast<T>(2.0))
{
    // Assertions
    DBG("Constructing StoneyVCV::LFO::LFOEngine");
}

template <typename T>
::StoneyDSP::StoneyVCV::LFO::LFOEngine<T>::LFOEngine(T newFrequency)
:   frequency(newFrequency),
    lastFrequency(newFrequency)
{
    // Assertions
    DBG("Constructing StoneyVCV::LFO::LFOEngine");
}

template <typename T>
::StoneyDSP::StoneyVCV::LFO::LFOEngine<T>::~LFOEngine() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::LFO::LFOEngine");

    this->frequency = static_cast<T>(2.0);
}

template <typename T>
void ::StoneyDSP::StoneyVCV::LFO::LFOEngine<T>::processSample(T* sample)
{
    // We can pass in an owned pointer-to-float, and write the phase to it
    ::StoneyDSP::ignoreUnused(sample);
}

template <typename T>
void ::StoneyDSP::StoneyVCV::LFO::LFOEngine<T>::setFrequency(const T &newFrequency)
{
    this->frequency = newFrequency;
}

template <typename T>
T& ::StoneyDSP::StoneyVCV::LFO::LFOEngine<T>::getFrequency() noexcept
{
    return this->frequency;
}

template struct ::StoneyDSP::StoneyVCV::LFO::LFOEngine<::StoneyDSP::float_t>;
template struct ::StoneyDSP::StoneyVCV::LFO::LFOEngine<::StoneyDSP::double_t>;
// template struct ::StoneyDSP::StoneyVCV::LFO::LFOEngine<::rack::simd::float_4>;
// template struct ::StoneyDSP::StoneyVCV::LFO::LFOEngine<::StoneyDSP::SIMD::double_2>;

//==============================================================================

::StoneyDSP::StoneyVCV::LFO::LFOModule::LFOModule()
:   lightDivider(),
    engine(),
    lightGains{0.0F}
{
    // Assertions
    DBG("Constructing StoneyVCV::LFO::LFOModule");
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::NUM_PARAMS == 4U);
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::NUM_INPUTS == 4U);
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::NUM_OUTPUTS == 4U);
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxLights::NUM_LIGHTS == 2U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    this->config(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxLights::NUM_LIGHTS
    );
    this->configParam(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::FREQ_PARAM,          // paramId
        -8.0F,                                                                  // minValue
        10.0F,                                                                  // maxValue
        1.0F,                                                                   // defaultValue
        "Frequency",                                                            // name
        " hz",                                                                  // unit
        2.0F,                                                                   // displayBase
        1.0F                                                                    // displayMultiplier
    );
    this->configParam(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::PWM_PARAM,           // paramId
        0.0F,                                                                   // minValue
        10.0F,                                                                  // maxValue
        5.0F,                                                                   // defaultValue
        "Pulse Width",                                                          // name
        "%",                                                                    // unit
        0.0F,                                                                   // displayBase
        10.0F                                                                   // displayMultiplier
    );
    this->configParam(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::TRIMPOT_FM_PARAM,    // paramId
        0.0F,                                                                   // minValue
        10.0F,                                                                  // maxValue
        5.0F,                                                                   // defaultValue
        "Frequency moduleation gain",                                           // name
        "%",                                                                    // unit
        0.0F,                                                                   // displayBase
        10.0F                                                                   // displayMultiplier
    );
    this->configParam(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::TRIMPOT_PWM_PARAM,   // paramId
        0.0F,                                                                   // minValue
        10.0F,                                                                  // maxValue
        5.0F,                                                                   // defaultValue
        "Pulse-width modulation gain",                                          // name
        "%",                                                                    // unit
        0.0F,                                                                   // displayBase
        10.0F                                                                   // displayMultiplier
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::FM_INPUT,            // portID
        "Frequency modulation"                                                  // name
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::CLK_INPUT,           // portID
        "Clock"                                                                 // name
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::RST_INPUT,           // portID
        "Reset"                                                                 // name
    );
    this->configInput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::PWM_INPUT,           // portID
        "Pulse-width modulation"                                                // name
    );
    this->configOutput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::SIN_OUTPUT,         // portID
        "Sine"                                                                  // name
    );
    this->configOutput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::TRI_OUTPUT,         // portID
        "Triangle"                                                              // name
    );
    this->configOutput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::SAW_OUTPUT,         // portID
        "Sawtooth"                                                              // name
    );
    this->configOutput(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::SQR_OUTPUT,         // portID
        "Square"                                                                // name
    );
    this->lightDivider.setDivision(16);
    for(auto &e : this->engine) {
        e.setFrequency(2.0F);
    }
}

::StoneyDSP::StoneyVCV::LFO::LFOModule::~LFOModule() noexcept
{
    DBG("Destroying StoneyVCV::LFO::LFOModule");

    for(auto &e : this->engine) {
        e.setFrequency(0.0F);
    }

    for(auto &lightGain : this->lightGains) {
        lightGain = (0.0F);
    }
}

void ::StoneyDSP::StoneyVCV::LFO::LFOModule::process(const ::StoneyDSP::StoneyVCV::LFO::LFOModule::ProcessArgs &args)
{
    auto &blink_light0 = this->lights[::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxLights::BLINK_LIGHT + 0];
    auto &blink_light1 = this->lights[::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxLights::BLINK_LIGHT + 1];

    // Lights
    if (this->lightDivider.process()) {
        auto lightValue = *::std::max_element<StoneyDSP::float_t *>(this->lightGains.begin(), this->lightGains.end());
        blink_light0.setBrightnessSmooth(
            1 - (lightValue * lightValue),
            this->lightDivider.getDivision() * args.sampleTime
        );
        blink_light1.setBrightnessSmooth(
            (lightValue * lightValue),
            this->lightDivider.getDivision() * args.sampleTime
        );
    }
}

::json_t *::StoneyDSP::StoneyVCV::LFO::LFOModule::dataToJson()
{
    ::json_t *rootJ = ::json_object();
    return rootJ;
}

void ::StoneyDSP::StoneyVCV::LFO::LFOModule::dataFromJson(::json_t *rootJ)
{
    ::StoneyDSP::ignoreUnused(rootJ);
}

//==============================================================================

::StoneyDSP::StoneyVCV::LFO::LFOWidget::LFOWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget()
{
    DBG("Constructing StoneyVCV::LFO::LFOWidget");

    this->setSize(::StoneyDSP::StoneyVCV::LFO::LFODimensions);

    this->fb->setSize(this->getSize());

    // Screws
    this->screwsPositions = {
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // top-right
            (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::LFO::LFODimensions.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
        ::rack::math::Vec( // bottom-right
            (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::LFO::LFODimensions.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
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
    // Params
    this->setNumParams(4U);
    this->paramPanelWidgets.clear(); // because element 0 is a null-ish value from the in-class initializer...
    this->paramPanelWidgets.reserve(this->getNumParams());
    for(::std::size_t i = 0U; i < this->getNumParams(); ++i) {
        this->paramPanelWidgets.emplace_back<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedRoundKnobPanelWidget *>(
            dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedRoundKnobPanelWidget *>(
                ::StoneyDSP::StoneyVCV::createWidgetCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedRoundKnobPanelWidget>(
                    ::rack::math::Vec()
                )
            )
        );
        this->fb->addChild(this->paramPanelWidgets.at(i));
    }
    // Ports
    this->setNumPorts(8U);
    this->portPanelWidgets.clear(); // because element 0 is a null-ish value from the in-class initializer...
    this->portPanelWidgets.reserve(this->getNumPorts());
    for(::std::size_t i = 0U; i < this->getNumPorts(); ++i) {
        this->portPanelWidgets.emplace_back<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget *>(
            dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget *>(
                ::StoneyDSP::StoneyVCV::createWidgetCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget>(
                    ::rack::math::Vec()
                )
            )
        );
        this->fb->addChild(this->portPanelWidgets.at(i));
    }
    // Update
    this->fb->setDirty();
    // Assertions
    assert(static_cast<unsigned int>(this->getSize().x) == 9U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->fb->getSize().x) == 9U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->fb->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::LFO::LFOWidget::~LFOWidget() noexcept
{
    DBG("Destroying StoneyVCV::LFO::LFOWidget");
    // Assertions
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::LFO::LFOWidget::step()
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::step();
}

void ::StoneyDSP::StoneyVCV::LFO::LFOWidget::draw(const ::StoneyDSP::StoneyVCV::LFO::LFOWidget::DrawArgs &args)
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::LFOModuleWidget(::StoneyDSP::StoneyVCV::LFO::LFOModule* module)
:   ::rack::app::ModuleWidget(),
    // Panel
    panel(nullptr),
    lfoWidget(nullptr),
    lfoModuleWidgetFrameBuffer(nullptr),
    // Params
    knobFreq(nullptr),
    knobPwm(nullptr),
    trimpotFm(nullptr),
    trimpotPwm(nullptr),
    // Inputs
    portInputFm(nullptr),
    portInputClk(nullptr),
    portInputRst(nullptr),
    portInputPwm(nullptr),
    // Outputs
    portOutputSin(nullptr),
    portOutputTri(nullptr),
    portOutputSaw(nullptr),
    portOutputSqr(nullptr),
    // Lights
    lightLfo(nullptr),
    // State
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels),
    prefersDarkPanelsPtr(nullptr),
    lastPixelRatio(APP->window->pixelRatio),
    pixelRatioPtr(nullptr)
{
    // Assertions
    DBG("Constructing StoneyVCV::LFO::LFOModuleWidget");

    this->panel = dynamic_cast<::rack::app::ThemedSvgPanel *>(
        ::rack::createPanel<::rack::app::ThemedSvgPanel>(
            // Light-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/LFO-light.svg"
            ),
            // Dark-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/LFO-dark.svg"
            )
        )
    );
    this->lfoWidget = dynamic_cast<::StoneyDSP::StoneyVCV::LFO::LFOWidget *>(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::LFO::LFOWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            ::StoneyDSP::StoneyVCV::LFO::LFODimensions
        )
    );
    this->lfoModuleWidgetFrameBuffer = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget *>(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            ::StoneyDSP::StoneyVCV::LFO::LFODimensions
        )
    );
    // Params
    this->knobFreq = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::RoundHugeBlackKnob *>(
        ::rack::createParamCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::RoundHugeBlackKnob>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x * 0.5F),
                (0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 12.0F))
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::FREQ_PARAM
        )
    );
    this->knobPwm = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::RoundLargeBlackKnob *>(
        ::rack::createParamCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::RoundLargeBlackKnob>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x * 0.5F),
                (0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 22.0F))
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::PWM_PARAM
        )
    );
    this->trimpotFm = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::Trimpot *>(
        ::rack::createParamCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::Trimpot>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * 1.0F,
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (230.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::TRIMPOT_FM_PARAM
        )
    );
    this->trimpotPwm = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::Trimpot *>(
        ::rack::createParamCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::Trimpot>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * 5.0F,
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (230.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::TRIMPOT_PWM_PARAM
        )
    );
    // Input Ports
    this->portInputFm = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * 1.0F,
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (265.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::FM_INPUT
        )
    ),
    this->portInputClk = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * (2.0F + (1.0F / 3.0F)),
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (265.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::CLK_INPUT
        )
    ),
    this->portInputRst = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * (3.0F + ((1.0F / 3.0F) * 2.0F)),
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (265.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::RST_INPUT
        )
    ),
    this->portInputPwm = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createInputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * 5.0F,
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (265.0F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::PWM_INPUT
        )
    ),
    // Output Ports
    this->portOutputSin = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createOutputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * 1.0F,
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (309.05634F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::SIN_OUTPUT
        )
    );
    this->portOutputTri = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createOutputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * (2.0F + (1.0F / 3.0F)),
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (309.05634F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::TRI_OUTPUT
        )
    );
    this->portOutputSaw = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createOutputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * (3.0F + ((1.0F / 3.0F) * 2.0F)),
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (309.05634F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::SAW_OUTPUT
        )
    );
    this->portOutputSqr = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *>(
        ::StoneyDSP::StoneyVCV::createOutputCentered<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget>(
            ::rack::math::Vec(
                (::StoneyDSP::StoneyVCV::LFO::LFODimensions.x / 6.0F) * 5.0F,
                ((39.15691F - (23.7F * 0.5F)) - 2.425775F) + (309.05634F)
            ),
            module,
            ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::SQR_OUTPUT
        )
    );

    this->lfoWidget->getPortPanelWidget(0).setPosition(
        ::rack::math::Vec(
            this->portInputFm->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portInputFm->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(1).setPosition(
        ::rack::math::Vec(
            this->portInputClk->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portInputClk->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(2).setPosition(
        ::rack::math::Vec(
            this->portInputRst->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portInputRst->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(3).setPosition(
        ::rack::math::Vec(
            this->portInputPwm->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portInputPwm->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(4).setPosition(
        ::rack::math::Vec(
            this->portOutputSin->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portOutputSin->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(5).setPosition(
        ::rack::math::Vec(
            this->portOutputTri->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portOutputTri->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(6).setPosition(
        ::rack::math::Vec(
            this->portOutputSaw->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portOutputSaw->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(7).setPosition(
        ::rack::math::Vec(
            this->portOutputSqr->getPosition().x - 2.425775F, // margin = portPanel.x - port.x / 2
            this->portOutputSqr->getPosition().y - ((39.15691F - 23.7F) - 2.425775F) // portPanel.y - port.y - margin
        )
    );
    this->lfoWidget->getPortPanelWidget(0).setIsOutput(false);
    this->lfoWidget->getPortPanelWidget(1).setIsOutput(false);
    this->lfoWidget->getPortPanelWidget(2).setIsOutput(false);
    this->lfoWidget->getPortPanelWidget(3).setIsOutput(false);
    this->lfoWidget->getPortPanelWidget(4).setIsOutput(true);
    this->lfoWidget->getPortPanelWidget(5).setIsOutput(true);
    this->lfoWidget->getPortPanelWidget(6).setIsOutput(true);
    this->lfoWidget->getPortPanelWidget(7).setIsOutput(true);

    this->lfoWidget->getPortPanelWidget(0).setLabelText("FM");
    this->lfoWidget->getPortPanelWidget(1).setLabelText("CLK");
    this->lfoWidget->getPortPanelWidget(2).setLabelText("RST");
    this->lfoWidget->getPortPanelWidget(3).setLabelText("PWM");
    this->lfoWidget->getPortPanelWidget(4).setLabelText("SIN");
    this->lfoWidget->getPortPanelWidget(5).setLabelText("TRI");
    this->lfoWidget->getPortPanelWidget(6).setLabelText("SAW");
    this->lfoWidget->getPortPanelWidget(7).setLabelText("SQR");

    this->lfoWidget->getParamPanelWidget(0).setBox(this->knobFreq->getBox());
    this->lfoWidget->getParamPanelWidget(0).setFontSize(12.0F);
    this->lfoWidget->getParamPanelWidget(0).setLabelText("FREQ");

    this->lfoWidget->getParamPanelWidget(1).setBox(this->knobPwm->getBox());
    this->lfoWidget->getParamPanelWidget(1).setFontSize(12.0F);
    this->lfoWidget->getParamPanelWidget(1).setLabelText("PWM");
    this->lfoWidget->getParamPanelWidget(1).setIsBipolar(true);

    this->lfoWidget->getParamPanelWidget(2).setBox(this->trimpotFm->getBox());
    this->lfoWidget->getParamPanelWidget(2).setFontSize(8.0F);
    this->lfoWidget->getParamPanelWidget(2).setLeading(3.0F);
    this->lfoWidget->getParamPanelWidget(2).setLabelText("CV");
    this->lfoWidget->getParamPanelWidget(2).setIsBipolar(true);
    //TODO: this->lfoWidget->paramPanelWidgets.at(2)->minAngle = -0.75F * M_PI;
	//TODO: this->lfoWidget->paramPanelWidgets.at(2)->maxAngle = 0.75F * M_PI;

    this->lfoWidget->getParamPanelWidget(3).setBox(this->trimpotPwm->getBox());
    this->lfoWidget->getParamPanelWidget(3).setFontSize(8.0F);
    this->lfoWidget->getParamPanelWidget(3).setLeading(3.0F);
    this->lfoWidget->getParamPanelWidget(3).setLabelText("CV");
    this->lfoWidget->getParamPanelWidget(3).setIsBipolar(true);

    this->prefersDarkPanelsPtr = static_cast<const bool *>(&::rack::settings::preferDarkPanels);
    this->pixelRatioPtr = static_cast<const float *>(&APP->window->pixelRatio);

    this->setModule(module);
    this->setSize(::StoneyDSP::StoneyVCV::LFO::LFODimensions);

    // Panel (calls addChildBottom)
    this->setPanel(this->panel);
    this->getPanel()->setSize(this->getSize());

    // Frame Buffer
    this->addChild(this->lfoModuleWidgetFrameBuffer);

    // Widget
    this->lfoModuleWidgetFrameBuffer->addChildBottom(this->lfoWidget);

    // Params
    this->addParam(this->knobFreq);
    this->addParam(this->knobPwm);
    this->addParam(this->trimpotFm);
    this->addParam(this->trimpotPwm);
    // Inputs
    this->addInput(this->portInputFm);
    this->addInput(this->portInputClk);
    this->addInput(this->portInputRst);
    this->addInput(this->portInputPwm);
    // Outputs
    this->addOutput(this->portOutputSin);
    this->addOutput(this->portOutputTri);
    this->addOutput(this->portOutputSaw);
    this->addOutput(this->portOutputSqr);
    // Lights
    // this->addChild(this->lightLfo);

    // Oversample
    if (static_cast<unsigned int>(APP->window->pixelRatio) < static_cast<unsigned int>(2.0F)) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->lfoModuleWidgetFrameBuffer->oversample = 2.0F;
	}
	else {
		this->lfoModuleWidgetFrameBuffer->oversample = 1.0F;
	}

    assert(this->panel != nullptr);
    assert(this->lfoWidget != nullptr);
    assert(this->lfoModuleWidgetFrameBuffer != nullptr);
    assert(this->knobFreq != nullptr);
    assert(this->knobPwm != nullptr);
    assert(this->trimpotFm != nullptr);
    assert(this->trimpotPwm != nullptr);
    assert(this->portInputFm != nullptr);
    assert(this->portInputClk != nullptr);
    assert(this->portInputRst != nullptr);
    assert(this->portInputPwm != nullptr);
    assert(this->portOutputSin != nullptr);
    assert(this->portOutputTri != nullptr);
    assert(this->portOutputSaw != nullptr);
    assert(this->portOutputSqr != nullptr);
    assert(this->prefersDarkPanelsPtr != nullptr);
    assert(this->pixelRatioPtr != nullptr);

    assert(static_cast<unsigned int>(this->getSize().x) == 9U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().x) == 9U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::~LFOModuleWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::LFO::LFOModuleWidget");
    assert(!this->parent);

    // Children
    // this->lfoWidget->clearChildren();
    this->lfoModuleWidgetFrameBuffer->clearChildren();
    this->clearChildren();
    this->setModule(NULL);

    this->panel = nullptr;
    this->lfoWidget = nullptr;
    this->lfoModuleWidgetFrameBuffer = nullptr;
    this->knobFreq = nullptr;
    this->knobPwm = nullptr;
    this->trimpotFm = nullptr;
    this->trimpotPwm = nullptr;
    this->portInputFm = nullptr;
    this->portInputClk = nullptr;
    this->portInputRst = nullptr;
    this->portInputPwm = nullptr;
    this->portOutputSin = nullptr;
    this->portOutputTri = nullptr;
    this->portOutputSaw = nullptr;
    this->portOutputSqr = nullptr;
    this->prefersDarkPanelsPtr = nullptr;
    this->pixelRatioPtr = nullptr;
}

void ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::step()
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

    return ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::onPrefersDarkPanelsChange(const PrefersDarkPanelsChangeEvent & e)
{
    // Validate
    if(this->lastPrefersDarkPanels == e.newPrefersDarkPanels)
        return;

    this->lfoModuleWidgetFrameBuffer->setDirty();
}

const bool &::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::getPrefersDarkPanels() const noexcept
{
    return *this->prefersDarkPanelsPtr;
}

void ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::onPixelRatioChange(const PixelRatioChangeEvent & e)
{
    // Validate
    if(this->lastPixelRatio == e.newPixelRatio)
        return;

    // Oversample
    if (static_cast<unsigned int>(APP->window->pixelRatio) < static_cast<unsigned int>(2.0F)) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->lfoModuleWidgetFrameBuffer->oversample = 2.0F;
	}
	else {
		this->lfoModuleWidgetFrameBuffer->oversample = 1.0F;
	}

    this->lfoModuleWidgetFrameBuffer->setDirty();
}

const float &StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::getPixelRatio() const noexcept
{
    return *this->pixelRatioPtr;
}

//==============================================================================

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::LFO::createModelLFO(
    ::std::string name,
    ::std::string description,
    ::std::string manualUrl,
    bool hidden
) noexcept(false) // STONEYDSP_NOEXCEPT(false)
{
    DBG("Creating StoneyVCV::LFO::modelLFO");

    ::rack::plugin::Model* modelLFO = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::LFO::LFOModule,
        ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget
    >("LFO"); // slug must never change!

    if(modelLFO == nullptr)
        throw ::rack::Exception("createModelLFO generated a nullptr");

    if(!description.empty())
        modelLFO->description = description;
    if(!manualUrl.empty())
        modelLFO->manualUrl = manualUrl;
    if(!name.empty())
        modelLFO->name = name;
    if(!hidden)
        modelLFO->hidden = hidden;

    return modelLFO;
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_LFO)

//==============================================================================
