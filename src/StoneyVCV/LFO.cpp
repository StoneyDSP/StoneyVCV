/***************************************************************************//**
 * @file LFO.cpp
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

//==============================================================================

#include <rack.hpp>

//==============================================================================

#include "StoneyVCV/LFO.hpp"

//==============================================================================

::StoneyDSP::StoneyVCV::LFO::LFOModule::LFOModule()
{
    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::PARAMS_LEN,     // numParams
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::INPUTS_LEN,     // numInputs
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::OUTPUTS_LEN,    // numOutputs
        ::StoneyDSP::StoneyVCV::LFO::LFOModule::LIGHTS_LEN      // numLights
    );
}

::StoneyDSP::StoneyVCV::LFO::LFOModule::~LFOModule()
{

}

void ::StoneyDSP::StoneyVCV::LFO::LFOModule::process(const ::StoneyDSP::StoneyVCV::LFO::LFOModule::ProcessArgs &args)
{
    ::StoneyDSP::ignoreUnused(args);
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
{
    // Widgets
    lfoWidgetFrameBuffer = new ::rack::FramebufferWidget;
    lfoWidgetFrameBuffer->setSize(box.size);
    addChild(lfoWidgetFrameBuffer);
}

::StoneyDSP::StoneyVCV::LFO::LFOWidget::~LFOWidget()
{
    // delete lfoWidgetFrameBuffer;
}

void ::StoneyDSP::StoneyVCV::LFO::LFOWidget::step()
{
    panelBorder->box.size = box.size;
    ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::LFO::LFOWidget::draw(const ::rack::Widget::DrawArgs &args)
{

    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg, 0.0, 0.0, box.size.x, box.size.y);
    ::NVGcolor bg = ::rack::settings::preferDarkPanels ? ::nvgRGB(42, 42, 42) : ::nvgRGB(235, 235, 235);
    ::nvgFillColor(args.vg, bg);
    ::nvgFill(args.vg);
    ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::LFOModuleWidget(::StoneyDSP::StoneyVCV::LFO::LFOModule* module) {
    setModule(module);
    setPanel(::rack::createPanel<::rack::app::SvgPanel>(
        ::rack::asset::plugin(::StoneyDSP::StoneyVCV::pluginInstance, "res/LFO-light.svg"),
        ::rack::asset::plugin(::StoneyDSP::StoneyVCV::pluginInstance, "res/LFO-dark.svg")
    ));
    // Widgets
    lfoModuleWidgetFrameBuffer = new ::rack::FramebufferWidget;
    lfoModuleWidgetFrameBuffer->setSize(box.size);
    addChild(lfoModuleWidgetFrameBuffer);
    //
    lfoWidget = ::rack::createWidget<::StoneyDSP::StoneyVCV::LFO::LFOWidget>(::rack::math::Vec(0.0f, 0.0f));
    lfoWidget->setSize(box.size);
    lfoModuleWidgetFrameBuffer->addChild(lfoWidget);
    // Scews
    addChild(::rack::createWidget<::rack::componentlibrary::ScrewSilver>(::rack::math::Vec(::rack::RACK_GRID_WIDTH, 0.0f)));
    addChild(::rack::createWidget<::rack::componentlibrary::ScrewSilver>(::rack::math::Vec(box.size.x - 2.0f * ::rack::RACK_GRID_WIDTH, 0.0f)));
    addChild(::rack::createWidget<::rack::componentlibrary::ScrewSilver>(::rack::math::Vec(::rack::RACK_GRID_WIDTH, ::rack::RACK_GRID_HEIGHT - ::rack::RACK_GRID_WIDTH)));
    addChild(::rack::createWidget<::rack::componentlibrary::ScrewSilver>(::rack::math::Vec(box.size.x - 2.0f * ::rack::RACK_GRID_WIDTH, ::rack::RACK_GRID_HEIGHT - ::rack::RACK_GRID_WIDTH)));
}

::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget::~LFOModuleWidget()
{
    // delete lfoModuleWidgetFrameBuffer;
}

//==============================================================================

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::LFO::createLFO() // STONEYDSP_NOEXCEPT(false)
{
    ::rack::plugin::Model* modelLFO = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::LFO::LFOModule,
        ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget
    >("LFO");
    // STONEYDSP_THROW_IF_FAILED_VOID(modelVCO == nullptr, bad_alloc);
    return modelLFO;
}

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

namespace LFO {

//==============================================================================

::rack::plugin::Model* modelLFO = ::StoneyDSP::StoneyVCV::LFO::createLFO();

//==============================================================================

} // namespace LFO

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================
