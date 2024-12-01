/***************************************************************************//**
 * @file HP1.cpp
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

#include "HP1.hpp"

//==============================================================================

::StoneyDSP::StoneyVCV::HP1Module::HP1Module()
{
    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::StoneyVCV::HP1Module::PARAMS_LEN,   // numParams
        ::StoneyDSP::StoneyVCV::HP1Module::INPUTS_LEN,   // numInputs
        ::StoneyDSP::StoneyVCV::HP1Module::OUTPUTS_LEN,  // numOutputs
        ::StoneyDSP::StoneyVCV::HP1Module::LIGHTS_LEN    // numLights
    );
}

// ::StoneyDSP::StoneyVCV::HP1Module::~HP1Module()
// {}

//==============================================================================

::StoneyDSP::StoneyVCV::HP1Widget::HP1Widget()
// :   hp1WidgetFrameBuffer(new ::rack::FramebufferWidget),
//     panelBorder(::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0f, 0.0f)))
{
    // // Widgets
    // hp1WidgetFrameBuffer = new ::rack::FramebufferWidget;
    // hp1WidgetFrameBuffer->setSize(box.size);
    // addChild(hp1WidgetFrameBuffer);
    // //
    // panelBorder = ::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0f, 0.0f));
    // panelBorder->setSize(box.size);
    // hp1WidgetFrameBuffer->addChild(panelBorder);
}

// ::StoneyDSP::StoneyVCV::HP1Widget::~HP1Widget()
// {}

void ::StoneyDSP::StoneyVCV::HP1Widget::step()
{
    // panelBorder->box.size = box.size;
    ::StoneyDSP::StoneyVCV::Widget::step();
}

void ::StoneyDSP::StoneyVCV::HP1Widget::draw(const ::StoneyDSP::StoneyVCV::Widget::DrawArgs &args)
{
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg, 0.0, 0.0, box.size.x, box.size.y);
    ::NVGcolor bg = ::rack::settings::preferDarkPanels ? ::nvgRGB(42, 42, 42) : ::nvgRGB(235, 235, 235);
    ::nvgFillColor(args.vg, bg);
    ::nvgFill(args.vg);
    ::StoneyDSP::StoneyVCV::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP1ModuleWidget::HP1ModuleWidget(::StoneyDSP::StoneyVCV::HP1Module* module)
// :   hp1Widget(::rack::createWidget<::StoneyDSP::StoneyVCV::HP1Widget>(::rack::math::Vec(0.0F, 0.0F))),
//     hp1ModuleWidgetFrameBuffer(new ::rack::FramebufferWidget)
{
    setModule(module);
    setPanel(::rack::createPanel(
        // Light-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP1-light.svg"
        ),
        // Dark-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP1-dark.svg"
        )
    ));
    // // Widgets
    // hp1ModuleWidgetFrameBuffer = new ::rack::FramebufferWidget;
    // hp1ModuleWidgetFrameBuffer->setSize(box.size);
    // addChild(hp1ModuleWidgetFrameBuffer);
    // //
    // hp1Widget = ::rack::createWidget<::StoneyDSP::StoneyVCV::HP1Widget>(::rack::math::Vec(0.0F, 0.0F));
    // hp1Widget->setSize(box.size);
    // hp1ModuleWidgetFrameBuffer->addChild(hp1Widget);
    // // Screws
    // ::rack::math::Vec screwT1Pos = ::rack::math::Vec(::rack::RACK_GRID_WIDTH, 0.0F); // top-middle
    // ::rack::math::Vec screwB1Pos = ::rack::math::Vec(::rack::RACK_GRID_WIDTH, ::rack::RACK_GRID_HEIGHT - ::rack::RACK_GRID_WIDTH); // bottom-middle
    // //
    // ::rack::componentlibrary::ThemedScrew *screwT1 = ::rack::createWidget<::rack::componentlibrary::ThemedScrew>(screwT1Pos);
    // ::rack::componentlibrary::ThemedScrew *screwB1 = ::rack::createWidget<::rack::componentlibrary::ThemedScrew>(screwB1Pos);
    // //
    // addChild(screwT1);
    // addChild(screwB1);
}

// ::StoneyDSP::StoneyVCV::HP1ModuleWidget::~HP1ModuleWidget()
// {}

/**
 *
 */
::rack::plugin::Model* ::StoneyDSP::StoneyVCV::createHP1()
{

    ::rack::plugin::Model* modelHP1 = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::HP1Module,
        ::StoneyDSP::StoneyVCV::HP1ModuleWidget
    >("HP1");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP1 == nullptr, bad_alloc);
    return modelHP1;
}

//==============================================================================

namespace StoneyDSP {

namespace StoneyVCV {

::rack::plugin::Model* modelHP1 = ::StoneyDSP::StoneyVCV::createHP1();

}

}

//==============================================================================
