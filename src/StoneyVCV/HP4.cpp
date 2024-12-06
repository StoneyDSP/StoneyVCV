/***************************************************************************//**
 * @file HP4.cpp
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

#include "StoneyVCV/HP4.hpp"

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4Module::HP4Module()
{
    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::PARAMS_LEN,   // numParams
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::INPUTS_LEN,   // numInputs
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::OUTPUTS_LEN,  // numOutputs
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::LIGHTS_LEN    // numLights
    );
}

// ::StoneyDSP::StoneyVCV::HP4::HP4Module::~HP4Module()
// {}

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4Widget::HP4Widget()
// :   hp4WidgetFrameBuffer(new ::rack::FramebufferWidget),
//     panelBorder(::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0f, 0.0f)))
{
    // // Widgets
    // hp4WidgetFrameBuffer = new ::rack::FramebufferWidget;
    // hp4WidgetFrameBuffer->setSize(box.size);
    // addChild(hp4WidgetFrameBuffer);
    // //
    // panelBorder = ::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0f, 0.0f));
    // panelBorder->setSize(box.size);
    // hp4WidgetFrameBuffer->addChild(panelBorder);
}

// ::StoneyDSP::StoneyVCV::HP4::HP4Widget::~HP4Widget()
// {}

void ::StoneyDSP::StoneyVCV::HP4::HP4Widget::step()
{
    // panelBorder->box.size = box.size;
    ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::HP4::HP4Widget::draw(const ::rack::Widget::DrawArgs &args)
{
    NVGcolor bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    NVGcolor bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;

    //
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg, 0.0, 0.0, box.size.x, box.size.y);
    ::NVGcolor bg = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    ::nvgFillColor(args.vg, bg);
    ::nvgFill(args.vg);
    ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::HP4ModuleWidget(::StoneyDSP::StoneyVCV::HP4::HP4Module* module)
// :   hp4Widget(::rack::createWidget<::StoneyDSP::StoneyVCV::HP4::HP4Widget>(::rack::math::Vec(0.0F, 0.0F))),
//     hp4ModuleWidgetFrameBuffer(new ::rack::FramebufferWidget)
{
    setModule(module);
    setPanel(::rack::createPanel(
        // Light-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP4-light.svg"
        ),
        // Dark-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP4-dark.svg"
        )
    ));
    // // Widgets
    // hp4ModuleWidgetFrameBuffer = new ::rack::FramebufferWidget;
    // hp4ModuleWidgetFrameBuffer->setSize(box.size);
    // addChild(hp4ModuleWidgetFrameBuffer);
    // //
    // hp4Widget = ::rack::createWidget<::StoneyDSP::StoneyVCV::HP4::HP4Widget>(::rack::math::Vec(0.0F, 0.0F));
    // hp4Widget->setSize(box.size);
    // hp4ModuleWidgetFrameBuffer->addChild(hp4Widget);
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

// ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::~HP4ModuleWidget()
// {}

/**
 *
 */
::rack::plugin::Model* ::StoneyDSP::StoneyVCV::HP4::createHP4()
{

    ::rack::plugin::Model* modelHP4 = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::HP4::HP4Module,
        ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget
    >("HP4");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP4 == nullptr, bad_alloc);
    return modelHP4;
}

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP4 {

::rack::plugin::Model* modelHP4 = ::StoneyDSP::StoneyVCV::HP4::createHP4();

}
}
}

//==============================================================================
