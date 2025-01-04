/*******************************************************************************
 * @file src/StoneyVCV/LFO.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_LFO)

//==============================================================================

#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/LFO.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>
#include <StoneyDSP/DSP.hpp>

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

static const ::rack::math::Vec LFODimensions = (
    ::rack::window::mm2px(30.479999995F), // 5.079999999F * 3.0F
    ::rack::window::mm2px(128.693333312F)
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
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::NUM_PARAMS == 0U);
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::NUM_INPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::NUM_OUTPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxLights::NUM_LIGHTS == 2U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    this->config(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxParams::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxInputs::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxOutputs::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxLights::NUM_LIGHTS
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
:   lfoWidgetFrameBuffer(new ::rack::FramebufferWidget),
    panelBorder(
        ::rack::createWidget<::rack::app::PanelBorder>(
            ::rack::math::Vec(0.0F, 0.0F)
        )
    )
{
    // Assertions
    DBG("Constructing StoneyVCV::LFO::LFOWidget");
    assert(this->lfoWidgetFrameBuffer != nullptr);
    assert(this->panelBorder != nullptr);

    // Widgets
    this->lfoWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->lfoWidgetFrameBuffer);

    // Border
    this->panelBorder->setSize(this->getSize());
    this->lfoWidgetFrameBuffer->addChild(this->panelBorder);
}

::StoneyDSP::StoneyVCV::LFO::LFOWidget::~LFOWidget()
{
    // Assertions
    DBG("Destroying StoneyVCV::LFO::LFOWidget");
    assert(!this->parent);

    // Children
    this->panelBorder->clearChildren();
    this->lfoWidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::LFO::LFOWidget::step()
{
    const auto& size = this->getSize();

    this->panelBorder->setSize(size);
    this->lfoWidgetFrameBuffer->setSize(size);

    return ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::LFO::LFOWidget::draw(const ::StoneyDSP::StoneyVCV::LFO::LFOWidget::DrawArgs &args)
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
        /** h */size.y,
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

::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::LFOModuleWidget(::StoneyDSP::StoneyVCV::LFO::LFOModule* module)
:   size(
        15.0F * 9.0F,
        380.0F
    ),
    // Panel
    panel(
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
    ),
    lfoWidget(::rack::createWidget<::StoneyDSP::StoneyVCV::LFO::LFOWidget>(::rack::math::Vec(0.0F, 0.0F))),
    lfoModuleWidgetFrameBuffer(new ::rack::FramebufferWidget),
    // Params
    // Inputs
    // Outputs
    // Lights
    lightLfo(
        ::rack::createLightCentered<::rack::componentlibrary::MediumLight<::rack::componentlibrary::GreenRedLight>>(
            ::rack::math::Vec(
                size.x * 0.5F,
                0.0F + ((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F) * 10.0F)
            ),
            module, ::StoneyDSP::StoneyVCV::LFO::LFOModule::IdxLights::BLINK_LIGHT
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
    DBG("Constructing StoneyVCV::LFO::LFOModuleWidget");
    // assert(module != nullptr);
    assert(this->lfoWidget != nullptr);
    assert(this->lfoModuleWidgetFrameBuffer != nullptr);
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
    this->lfoModuleWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->lfoModuleWidgetFrameBuffer);

    // Widget
    this->lfoWidget->setSize(this->getSize());
    this->lfoModuleWidgetFrameBuffer->addChild(this->lfoWidget);

    // Screws
    for(const auto& screw : this->screws) {
        this->addChild(screw);
    }

    // Params
    // Inputs
    // Outputs
    // Lights
    this->addChild(this->lightLfo);

    assert(static_cast<unsigned int>(this->getSize().x) == 9U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().x) == 9U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::~LFOModuleWidget()
{
    // Assertions
    DBG("Destroying StoneyVCV::LFO::LFOModuleWidget");
    assert(!this->parent);

    // Children
    this->lfoWidget->clearChildren();
    this->lfoModuleWidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::step()
{
    if(this->lastPrefersDarkPanels != ::rack::settings::preferDarkPanels) {
        this->lfoModuleWidgetFrameBuffer->setDirty();
        this->lastPrefersDarkPanels = ::rack::settings::preferDarkPanels;
    }

    return ::rack::Widget::step();
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
