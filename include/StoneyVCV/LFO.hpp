/*******************************************************************************
 * @file include/StoneyVCV/LFO.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief @PROJECT_DESCRIPTION@
 * @version @LFO_VERSION@
 *
 * @copyright MIT License
 *
 * Copyright (c) 2024 Nathan J. Hood <nathanjhood@googlemail.com>
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

#define STONEYVCV_LFO_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_LFO)

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/PortWidget.hpp>
#include <StoneyVCV/ComponentLibrary/PanelWidget.hpp>
#include <StoneyVCV/ComponentLibrary/RoundKnobWidget.hpp>
#include <StoneyVCV/plugin.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>
#include <StoneyDSP/DSP.hpp>
#include <StoneyDSP/SIMD.hpp>

//==============================================================================

#include <array>

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
 * @brief The `LFO` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @LFO_VERSION@
 *
 */
namespace LFO
{
/** @addtogroup LFO
 *  @{
 */

//==============================================================================

/**
 * @brief The `LFOEngine` struct.
 *
 */
template<typename T>
struct LFOEngine : virtual ::StoneyDSP::StoneyVCV::Engine<T>
{
    //==========================================================================

public:

    //==========================================================================

    LFOEngine();

    LFOEngine(T sample);

    virtual ~LFOEngine() noexcept;

    //==========================================================================

    void processSample(T *sample) override;

    void setFrequency(const T &newFrequency);

    T& getFrequency() noexcept;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    T frequency = 2.0F;

    /**
     * @brief
     *
     */
    T lastFrequency = 2.0F;

    /**
     * @brief
     *
     */
    T phase = 0.0F;

    STONEYDSP_DECLARE_NON_COPYABLE(LFOEngine)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOEngine)
};

//==============================================================================

/**
 * @brief The `LFOModule` struct.
 *
 */
struct LFOModule final : virtual ::rack::engine::Module
{

    //==========================================================================

public:

    //==========================================================================

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

    //==========================================================================

    enum IdxParams {
        FREQ_PARAM,
        PWM_PARAM,
        TRIMPOT_FM_PARAM,
        TRIMPOT_PWM_PARAM,
        /** Number of Parameters. */
        NUM_PARAMS
    };

    enum IdxInputs {
        FM_INPUT,
        CLK_INPUT,
        RST_INPUT,
        PWM_INPUT,
        /** Number of Input ports. */
        NUM_INPUTS
    };

    enum IdxOutputs {
        SIN_OUTPUT,
        TRI_OUTPUT,
        SAW_OUTPUT,
        SQR_OUTPUT,
        /** Number of Output ports. */
        NUM_OUTPUTS
    };

    enum IdxLights {
        ENUMS(BLINK_LIGHT, 2),
        /** Number of Lights. */
        NUM_LIGHTS
    };

    //==========================================================================

    /**
     * @brief Construct a new `LFOModule` object.
     *
     */
    LFOModule();

    /**
     * @brief Destroy the `LFOModule` object.
     *
     */
    virtual ~LFOModule() noexcept;

    //==========================================================================

    /**
     * @brief Advances the module by one audio sample.
     *
     * @param args
     */
    virtual void process(const ::StoneyDSP::StoneyVCV::LFO::LFOModule::ProcessArgs& args) override;

    /**
     * @brief Store extra internal data in the "data" property of the module's JSON object.
     *
     * @return json_t
     */
    ::json_t* dataToJson() override;

    /**
     * @brief Load internal data from the "data" property of the module's JSON object.
     * Not called if "data" property is not present.
     *
     * @param rootJ
     */
    void dataFromJson(::json_t* rootJ) override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::dsp::ClockDivider lightDivider;

    /**
     * @brief
     *
     */
    ::std::array<::StoneyDSP::StoneyVCV::LFO::LFOEngine<float>, 16> engine;

    /**
     * @brief
     *
     */
    ::std::array<float, 16> lightGains;

    //==========================================================================

    /**
     * @brief
     *
     */
    const float &vNominal = ::StoneyDSP::StoneyVCV::Tools::vNominal;

    /**
     * @brief
     *
     */
    const float &vFloor = ::StoneyDSP::StoneyVCV::Tools::vFloor;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(LFOModule)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOModule)
};

//==============================================================================

/**
 * @brief The `LFOPanelWidget` struct.
 *
 */
struct LFOPanelWidget final : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `LFOWidget` object.
     *
     */
    LFOPanelWidget(::rack::math::Rect newBox);

    /**
     * @brief Destroy the `LFOWidget` object.
     *
     */
    virtual ~LFOPanelWidget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws the widget to the NanoVG context.
     * When overriding, call the superclass's draw(args) to recurse to
     * children.
     *
     * @param args
     */
    void draw(const ::StoneyDSP::StoneyVCV::LFO::LFOPanelWidget::DrawArgs& args) override;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(LFOPanelWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOPanelWidget)
    STONEYDSP_DECLARE_NON_CONSTRUCTABLE(LFOPanelWidget)
};

//==============================================================================

/**
 * @brief The `LFOModuleWidget` struct.
 *
 * @tparam T
 */
struct LFOModuleWidget final : virtual ::rack::app::ModuleWidget
{

    //==========================================================================

public:

    //==========================================================================

    /**
     * @brief Construct a new `LFOModuleWidget` object.
     *
     * @param module
     *
     */
    LFOModuleWidget(::StoneyDSP::StoneyVCV::LFO::LFOModule* module);


    /**
     * @brief Destroys the `LFOModuleWidget` object.
     *
     */
    virtual ~LFOModuleWidget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    //==========================================================================

    /**
     * Occurs after the `prefersDarkPanels` setting is changed.
     * The concept of a "dark" or "light" panel is defined by the type of Widget.
	 *
     */
	struct PrefersDarkPanelsChangeEvent : ::rack::widget::Widget::BaseEvent {
        bool newPrefersDarkPanels;
    };

    /**
     * Called after the `prefersDarkPanels` setting is changed.
     * Sub-classes can override this to receive callbacks when the event is
     * dispatched (from the `ThemedWidget::step()` method).
     *
     * @param e
     *
     */
	virtual void onPrefersDarkPanelsChange(const PrefersDarkPanelsChangeEvent& e);

    /**
     *
     */
    const bool &getPrefersDarkPanels() const noexcept;

    //==========================================================================

    struct PixelRatioChangeEvent : ::rack::widget::Widget::BaseEvent {
        float newPixelRatio = APP->window->pixelRatio;
    };

    /**
     * Called after the `App->window->pixelRatio` setting is changed.
     * Sub-classes can override this to receive callbacks when the event is
     * dispatched (from the `Widget::step()` method).
     *
     * @param e
     *
     */
    virtual void onPixelRatioChange(const PixelRatioChangeEvent& e);

    /**
     * @brief
     *
     */
    const float &getPixelRatio() const noexcept;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::app::ThemedSvgPanel *svgPanelWidget = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::LFO::LFOPanelWidget *panelWidget = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget *fb = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundHugeBlackKnob *knobFreq = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundLargeBlackKnob *knobPwm = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::Trimpot *trimpotFm = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::Trimpot *trimpotPwm = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portInputFm = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portInputClk = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portInputRst = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portInputPwm = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portOutputSin = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portOutputTri = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portOutputSaw = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portOutputSqr = NULL;

    //==========================================================================

    /**
     * @brief 3mm LED showing a smoothed CV value.
     */
    ::rack::componentlibrary::MediumLight<::rack::componentlibrary::GreenRedLight> *lightLfo = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    bool lastPrefersDarkPanels = {::rack::settings::preferDarkPanels};

    /**
     * `{&::rack::settings::preferDarkPanels}`
     *
     */
    const bool *prefersDarkPanelsPtr = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    float lastPixelRatio = {APP->window->pixelRatio};

    /**
     * @brief
     *
     */
    const float *pixelRatioPtr = NULL;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(LFOModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @param name
 * @param description
 * @param manualUrl
 * @param hidden
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model *createModelLFO(
    ::std::string name = "",
    ::std::string description = "",
    ::std::string manualUrl = "",
    bool hidden = true
) noexcept(false); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group LFO
} // namespace LFO

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif // defined (STONEYVCV_BUILD_LFO)

//==============================================================================
