/*******************************************************************************
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

#include <StoneyVCV/HP1.hpp>

//==============================================================================

#include <rack.hpp>

//==============================================================================

::StoneyDSP::StoneyVCV::HP1::HP1Module::HP1Module()
{
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_PARAMS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_INPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_OUTPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_LIGHTS == 0U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_LIGHTS
    );
}

::StoneyDSP::StoneyVCV::HP1::HP1Module::~HP1Module()
{
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP1::HP1Widget::HP1Widget()
:   hp1WidgetFrameBuffer(new ::rack::FramebufferWidget),
    panelBorder(::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0F, 0.0F)))
{
    // Widget
    hp1WidgetFrameBuffer->setSize(box.size);
    addChild(hp1WidgetFrameBuffer);

    // Border
    panelBorder->setSize(box.size);
    hp1WidgetFrameBuffer->addChild(panelBorder);
}

// ::StoneyDSP::StoneyVCV::HP1::HP1Widget::~HP1Widget()
// {
//     delete panelBorder;
//     delete hp1WidgetFrameBuffer;
// }

void ::StoneyDSP::StoneyVCV::HP1::HP1Widget::step()
{
    panelBorder->box.size = box.size;
    ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::HP1::HP1Widget::draw(const ::StoneyDSP::StoneyVCV::HP1::HP1Widget::DrawArgs& args)
{
    ::NVGcolor& bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    ::NVGcolor& bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;

    // draw Themed BG
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg, 0.0F, 0.0F, box.size.x, box.size.y);
    ::nvgFillColor(args.vg, ::rack::settings::preferDarkPanels ? bgBlack : bgWhite);
    ::nvgFill(args.vg);
    ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget::HP1ModuleWidget(::StoneyDSP::StoneyVCV::HP1::HP1Module* module)
:   size(::rack::window::mm2px(5.079999999F), ::rack::window::mm2px(128.693333312F)),
    hp1Widget(::rack::createWidget<::StoneyDSP::StoneyVCV::HP1::HP1Widget>(::rack::math::Vec(0.0F, 0.0F))),
    hp1ModuleWidgetFrameBuffer(new ::rack::FramebufferWidget),
    // Screws
    screwTPos(::rack::math::Vec(size.x * 0.5F, size.x * 0.5F)), // top-middle
    screwBPos(::rack::math::Vec(size.x * 0.5F, ::rack::RACK_GRID_HEIGHT - size.x * 0.5F)), // bottom-middle
    screwT(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwTPos)),
    screwB(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwBPos)),
    // Panel
    panel(
        ::rack::createPanel<::rack::app::ThemedSvgPanel>(
            // Light-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP1-light.svg"
            ),
            // Dark-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP1-dark.svg"
            )
        )
    )
{

    setModule(module);
    setSize(size);
    setPanel(panel);

    hp1Widget->setSize(this->getSize());
    addChild(hp1Widget);

    // // Frame Buffer
    // hp1ModuleWidgetFrameBuffer->setSize(this->getSize());
    // addChild(hp1ModuleWidgetFrameBuffer);

    // // Widget
    // hp1Widget->setSize(this->getSize());
    // hp1ModuleWidgetFrameBuffer->addChild(hp1Widget);

    //
    addChild(screwT);
    addChild(screwB);

    assert(this->getSize().x == ::rack::window::mm2px(5.079999999F));
    assert(this->getSize().y == ::rack::window::mm2px(128.693333312F));
}

// ::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget::~HP1ModuleWidget()
// {
// }

//==============================================================================

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::HP1::createHP1()
{
    ::rack::plugin::Model* modelHP1 = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::HP1::HP1Module,
        ::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget
    >("HP1");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP1 == nullptr, bad_alloc);
    return modelHP1;
}

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP1 {

//==============================================================================

::rack::plugin::Model* modelHP1 = ::StoneyDSP::StoneyVCV::HP1::createHP1();

//==============================================================================

} // namespace HP1
} // namespace StoneyVCV
} // namespace StoneyDSP

//==============================================================================
