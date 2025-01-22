/*******************************************************************************
 * @file include/StoneyVCV/VCA.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief @PROJECT_DESCRIPTION@
 * @version @VCA_VERSION@
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

#define STONEYVCV_VCA_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_VCA)

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
 * @brief The `VCA` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @VCA_VERSION@
 *
 */
namespace VCA
{
/** @addtogroup VCA
 *  @{
 */

//==============================================================================

/**
 * @brief The `VCAEngine` struct.
 *
 */
template<typename T>
struct VCAEngine : virtual ::StoneyDSP::StoneyVCV::Engine<T>
{
    //==========================================================================

public:

    //==========================================================================

    VCAEngine();

    virtual ~VCAEngine() noexcept;

    //==========================================================================

    void processSample(T *sample) override;

    void processSampleSimd(::StoneyDSP::SIMD::float_4 *v);

    void processSampleSimd(::StoneyDSP::SIMD::double_2 *v);

    void setGain(const T &newGain);

    T& getGain() noexcept;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    T gain;

    /**
     * @brief
     *
     */
    T lastGain;

    STONEYDSP_DECLARE_NON_COPYABLE(VCAEngine)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAEngine)
};

//==============================================================================

/**
 * @brief The `VCAModule` struct.
 *
 */
struct VCAModule final : virtual ::rack::engine::Module
{

    //==========================================================================

public:

    //==========================================================================

    enum IdxParams {
        GAIN_PARAM,
        NUM_PARAMS
    };

    enum IdxInputs {
        VCA_INPUT,
        CV_INPUT,
        NUM_INPUTS
    };

    enum IdxOutputs {
        VCA_OUTPUT,
        NUM_OUTPUTS
    };

    enum IdxLights {
        //BLINK_LIGHT,
        ENUMS(BLINK_LIGHT, 2),
        NUM_LIGHTS
    };

    //==========================================================================

    /**
     * @brief Construct a new `VCAModule` object.
     *
     */
    VCAModule();

    /**
     * @brief Destroy the `VCAModule` object.
     *
     */
    virtual ~VCAModule() noexcept;

    //==========================================================================

    /**
     * @brief Advances the module by one audio sample.
     *
     * @param args
     */
    virtual void process(const ::StoneyDSP::StoneyVCV::VCA::VCAModule::ProcessArgs &args) override;

    //==========================================================================

	struct NumChannelsChangedEvent {};
	/** Called after enabling the module.
	*/
	virtual void onNumChannelsChanged(const NumChannelsChangedEvent& e) {}

	struct GainParamChangedEvent {};
	/** Called after changing the Gain parameter (knob) on the panel.
	*/
	virtual void onGainParamChanged(const GainParamChangedEvent& e) {}

    //==========================================================================

    ::std::size_t getVcaInputNumChannels() noexcept;

    ::std::size_t getCvInputNumChannels() noexcept;

    /**
     * Get desired number of channels from `vcaInput` and `cvInput`.
     * If these input are unpatched, getChannels() returns 0, but we should
     * still generate 1 channel of output.
     *
     */
    ::std::size_t getMinNumChannels() noexcept;

    ::rack::engine::Input &getVcaInput() noexcept;

    ::rack::engine::Input &getCvInput() noexcept;

    ::rack::engine::Param &getGainParam() noexcept;

    ::rack::engine::Output &getVcaOutput() noexcept;

    ::rack::engine::Light &getBlinkLight() noexcept;

    //==========================================================================

private:

    //==========================================================================

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

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
    ::std::array<::StoneyDSP::StoneyVCV::VCA::VCAEngine<float>, 16> engine;

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
    const ::StoneyDSP::float_t &vNominal = ::StoneyDSP::StoneyVCV::Tools::vNominal;

    /**
     * @brief
     *
     */
    const ::StoneyDSP::float_t &vFloor = ::StoneyDSP::StoneyVCV::Tools::vFloor;

    //==========================================================================

    ::rack::engine::Input* vcaInputPtr = NULL;

    ::rack::engine::Input* cvInputPtr = NULL;

    ::rack::engine::Param* gainParamPtr = NULL;

    ::rack::engine::Output* vcaOutputPtr = NULL;

    ::rack::engine::Light* blinkLightPtr = NULL;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(VCAModule)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAModule)
};

//==============================================================================

/**
 * @brief The `VCAPanelWidget` struct.
 *
 */
struct VCAPanelWidget final : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget
{

    //==========================================================================

public:

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `VCAPanelWidget` object.
     *
     */
    VCAPanelWidget(::rack::math::Rect newBox);

    /**
     * @brief Destroys the `VCAPanelWidget` object.
     *
     */
    virtual ~VCAPanelWidget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws the widget to the NanoVG context.
     * Calls the superclass's draw(args) to recurse to children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::VCA::VCAPanelWidget::DrawArgs &args) override;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(VCAPanelWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAPanelWidget)
    STONEYDSP_DECLARE_NON_CONSTRUCTABLE(VCAPanelWidget)
};

//==============================================================================

/**
 * @brief The `VCAModuleWidget` struct.
 *
 */
struct VCAModuleWidget final : virtual ::rack::app::ModuleWidget
{

    //==========================================================================

public:

    using DrawArgs = ::rack::app::ModuleWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `VCAModuleWidget` object.
     *
     * @param module
     *
     */
    VCAModuleWidget(::StoneyDSP::StoneyVCV::VCA::VCAModule *module);

    /**
     * @brief Destroys the `VCAModuleWidget` object.
     *
     */
    virtual ~VCAModuleWidget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the `VCAModuleWidget` by one frame.
     * Calls `::rack::ModuleWidget::step()` internally.
     *
     */
    virtual void step() override;

    /**
     * @brief Renders the `VCAModuleWidget` to the NanoVG context.
     * Calls `::rack::ModuleWidget::draw(args)` internally.
     *
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget::DrawArgs &args) override;

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
    ::StoneyDSP::StoneyVCV::VCA::VCAPanelWidget *panelWidget = NULL;

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
    ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundHugeBlackKnob *knobGain = NULL;

    // ::rack::componentlibrary::VCVLightSlider<::rack::componentlibrary::YellowLight>* gainSlider = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portInputCv = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portInputVca = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portOutputVca = NULL;

    /**
     * @brief 3mm LED showing a smoothed CV value.
     *
     */
    ::rack::componentlibrary::MediumLight<::rack::componentlibrary::GreenRedLight> *vcaLight = NULL;

    // ::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight> *lightVca = NULL;


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

    STONEYDSP_DECLARE_NON_COPYABLE(VCAModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAModuleWidget)
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
::rack::plugin::Model *createModelVCA(
    ::std::string name = "",
    ::std::string description = "",
    ::std::string manualUrl = "",
    bool hidden = true
) noexcept(false); // STONEYDSP_NOEXCEPT(false);

//==============================================================================

  /// @} group VCA
} // namespace VCA

//==============================================================================

  /// @} group VCVRack
} // namespace VCVRack

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif // defined (STONEYVCV_BUILD_VCA)

//==============================================================================
