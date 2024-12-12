/***************************************************************************//**
 * @file LFO.hpp
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

#pragma once

#define STONEYVCV_LFO_HPP_INCLUDED 1

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>
#include <StoneyDSP/DSP.hpp>
#include <StoneyDSP/SIMD.hpp>

//==============================================================================

#include "plugin.hpp"

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

namespace LFO
{
/** @addtogroup LFO
 *  @{
 */

//==============================================================================

/**
 * @brief The `LFOModule` class.
 *
 */
struct LFOModule final :
    ::rack::engine::Module
{
public:

    using ProcessArgs = ::rack::engine::Module::ProcessArgs;

    enum ParamsId {
        PARAMS_LEN
    };
	enum InputsId {
		INPUTS_LEN
	};
	enum OutputsId {
		OUTPUTS_LEN
	};
	enum LightsId {
		LIGHTS_LEN
	};

    /**
     * @brief Construct a new `LFOModule` object.
     *
     */
    LFOModule();

    /**
     * @brief Destroy the `LFOModule` object.
     *
     */
    ~LFOModule();

    /**
     * @brief Advances the module by one audio sample.
     *
     * @param args
     */
    virtual void process(const ::StoneyDSP::StoneyVCV::LFO::LFOModule::ProcessArgs &args) override;

    ::json_t *dataToJson() override;

    void dataFromJson(::json_t *rootJ) override;

private:
    STONEYDSP_DECLARE_NON_COPYABLE(LFOModule)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOModule)
};

//==============================================================================

/**
 * @brief The `LFOWidget` class.
 *
 */
struct LFOWidget final :
    ::rack::Widget
{
public:
    LFOWidget();
    ~LFOWidget();
    /**
     * @brief Advances the module by one frame.
     *
     */
    void step() override;
    /**
     * @brief Draws the widget to the NanoVG context.
     * When overriding, call the superclass's draw(args) to recurse to
     * children.
     *
     * @param args
     */
    void draw(const ::rack::Widget::DrawArgs &args) override;
    ::rack::FramebufferWidget *lfoWidgetFrameBuffer;
    ::rack::Widget *panelBorder;
private:
    STONEYDSP_DECLARE_NON_COPYABLE(LFOWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOWidget)
};

//==============================================================================

/**
 * @brief The `LFOModuleWidget` struct.
 *
 * @tparam T
 */
struct LFOModuleWidget final :
    ::rack::app::ModuleWidget
{
public:
    LFOModuleWidget(::StoneyDSP::StoneyVCV::LFO::LFOModule* module);
    ~LFOModuleWidget();
private:
    // ::StoneyDSP::StoneyVCV::LFO::LFOWidget *lfoWidget;
    // ::rack::FramebufferWidget *lfoModuleWidgetFrameBuffer;
    STONEYDSP_DECLARE_NON_COPYABLE(LFOModuleWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOModuleWidget)
};

//==============================================================================

/**
 * @brief
 *
 * @return `rack::plugin::Model*`
 */
::rack::plugin::Model *createLFO(); // STONEYDSP_NOEXCEPT(false);

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
