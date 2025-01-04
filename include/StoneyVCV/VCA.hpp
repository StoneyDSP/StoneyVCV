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

#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/plugin.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>
#include <StoneyDSP/DSP.hpp>
#include <StoneyDSP/SIMD.hpp>

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

    VCAEngine(T sample);

    ~VCAEngine() noexcept;

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
        BLINK_LIGHT, // ENUMS(BLINK_LIGHT, 2),
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

private:

    //==========================================================================

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

    //==========================================================================

    ::rack::engine::Input &getVcaInput() noexcept;

    ::rack::engine::Input &getCvInput() noexcept;

    ::rack::engine::Param &getGainParam() noexcept;

    ::rack::engine::Output &getVcaOutput() noexcept;

    ::rack::engine::Light &getBlinkLight() noexcept;

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
    ::std::array<::StoneyDSP::StoneyVCV::VCA::VCAEngine<::StoneyDSP::float_t>, 16> engine;

    /**
     * @brief
     *
     */
    ::std::array<::StoneyDSP::float_t, 16> lightGains;

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

    STONEYDSP_DECLARE_NON_COPYABLE(VCAModule)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAModule)
};

//==============================================================================

/**
 * @brief The `VCAWidget` struct.
 *
 */
struct VCAWidget final : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget
{

    //==========================================================================

public:

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `VCAWidget` object.
     *
     */
    VCAWidget();

    /**
     * @brief Destroys the `VCAWidget` object.
     *
     */
    virtual ~VCAWidget();

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
    virtual void draw(const ::StoneyDSP::StoneyVCV::VCA::VCAWidget::DrawArgs &args) override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    const ::std::array<::rack::math::Vec, 4> screwsPositions;

    /**
     * @brief
     *
     */
    const ::std::array<::rack::componentlibrary::ThemedScrew *, 4> screws;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(VCAWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCAWidget)
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
    virtual ~VCAModuleWidget();

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    const ::rack::math::Vec size;

    /**
     * @brief
     *
     */
    ::rack::app::ThemedSvgPanel *panel;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::VCA::VCAWidget *vcaWidget;

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget *vcaModuleWidgetFrameBuffer;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::componentlibrary::RoundBigBlackKnob *gainKnob;

    // ::rack::componentlibrary::VCVLightSlider<::rack::componentlibrary::YellowLight>* gainSlider;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portCvInput;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portVcaInput;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget *portVcaOutput;

    /**
     * @brief 3mm LED showing a smoothed CV value.
     */
    ::rack::componentlibrary::MediumLight<::rack::componentlibrary::RedLight> *lightVca;

    // ::rack::componentlibrary::MediumLight<::rack::componentlibrary::GreenRedLight> *lightVca;

    //==========================================================================

    /**
     * @brief
     *
     */
    bool lastPrefersDarkPanels;

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
