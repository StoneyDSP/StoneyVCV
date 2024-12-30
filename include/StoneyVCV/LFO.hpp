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

    ~LFOEngine() noexcept;

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
    T frequency;

    /**
     * @brief
     *
     */
    T lastFrequency;

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

    enum IdxParams {
        /** Number of Parameters. */
        NUM_PARAMS
    };

    enum IdxInputs {
        /** Number of Input ports. */
        NUM_INPUTS
    };

    enum IdxOutputs {
        /** Number of Output ports. */
        NUM_OUTPUTS
    };

    enum IdxLights {
        /** Number of Lights. */
        ENUMS(BLINK_LIGHT, 2),
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
    ::std::array<::StoneyDSP::StoneyVCV::LFO::LFOEngine<::StoneyDSP::float_t>, 16> engine;

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

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(LFOModule)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOModule)
};

//==============================================================================

/**
 * @brief The `LFOWidget` struct.
 *
 */
struct LFOWidget final : virtual ::rack::Widget
{

    //==========================================================================

public:

    using DrawArgs = ::rack::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `LFOWidget` object.
     *
     */
    LFOWidget();

    /**
     * @brief Destroy the `LFOWidget` object.
     *
     */
    virtual ~LFOWidget();

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
    void draw(const ::StoneyDSP::StoneyVCV::LFO::LFOWidget::DrawArgs& args) override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget* lfoWidgetFrameBuffer;

    /**
     * @brief
     *
     */
    ::rack::app::PanelBorder *panelBorder;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(LFOWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOWidget)
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
    virtual ~LFOModuleWidget();

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
    ::StoneyDSP::StoneyVCV::LFO::LFOWidget *lfoWidget;

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget *lfoModuleWidgetFrameBuffer;

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

    /**
     * @brief
     *
     */
    bool lastPrefersDarkPanels;

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
