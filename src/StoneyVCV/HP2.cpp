/***************************************************************************//**
 * @file HP2.cpp
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

#include <StoneyVCV/HP2.hpp>

//==============================================================================

#include <rack.hpp>

//==============================================================================

::StoneyDSP::StoneyVCV::HP2::HP2Module::HP2Module()
{
    assert(::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_PARAMS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_INPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_OUTPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_LIGHTS == 0U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_LIGHTS
    );
}

::StoneyDSP::StoneyVCV::HP2::HP2Module::~HP2Module()
{
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP2::HP2Widget::HP2Widget()
:   hp2WidgetFrameBuffer(new ::rack::FramebufferWidget),
    panelBorder(::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0F, 0.0F)))
{
    // Widget
    hp2WidgetFrameBuffer->setSize(box.size);
    addChild(hp2WidgetFrameBuffer);

    // Border
    panelBorder->setSize(box.size);
    hp2WidgetFrameBuffer->addChild(panelBorder);
}

// ::StoneyDSP::StoneyVCV::HP2::HP2Widget::~HP2Widget()
// {
// }

void ::StoneyDSP::StoneyVCV::HP2::HP2Widget::step()
{
    panelBorder->box.size = box.size;
    ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::HP2::HP2Widget::draw(const ::StoneyDSP::StoneyVCV::HP2::HP2Widget::DrawArgs& args)
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

::StoneyDSP::StoneyVCV::HP2::HP2ModuleWidget::HP2ModuleWidget(::StoneyDSP::StoneyVCV::HP2::HP2Module* module)
:   size(::rack::window::mm2px(10.1599999984F), ::rack::window::mm2px(128.693333312F)),
    hp2Widget(::rack::createWidget<::StoneyDSP::StoneyVCV::HP2::HP2Widget>(::rack::math::Vec(0.0F, 0.0F))),
    hp2ModuleWidgetFrameBuffer(new ::rack::FramebufferWidget),
    // Screws
    screwT1Pos(::rack::math::Vec((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F), (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // top-left
    screwT2Pos(::rack::math::Vec((size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)), (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // top-right
    screwB1Pos(::rack::math::Vec((::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F), size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // bottom-left
    screwB2Pos(::rack::math::Vec((size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)), size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))), // bottom-right
    screwT1(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwT1Pos)),
    screwT2(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwT2Pos)),
    screwB1(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwB1Pos)),
    screwB2(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwB2Pos)),
    // Panel
    panel(::rack::createPanel<::rack::app::ThemedSvgPanel>(
        // Light-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP2-light.svg"
        ),
        // Dark-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP2-dark.svg"
        )
    ))
{
    setModule(module);
    setSize(size);
    setPanel(panel);

    hp2Widget->setSize(this->getSize());
    addChild(hp2Widget);

    // // Frame Buffer
    // hp2ModuleWidgetFrameBuffer->setSize(box.size);
    // addChild(hp2ModuleWidgetFrameBuffer);

    // // Widget
    // hp2Widget->setSize(box.size);
    // hp2ModuleWidgetFrameBuffer->addChild(hp2Widget);

    addChild(screwT1);
    addChild(screwT2);
    addChild(screwB1);
    addChild(screwB2);

    assert(this->getSize().x == ::rack::window::mm2px(10.1599999984F));
    assert(this->getSize().y == ::rack::window::mm2px(128.693333312F));
}

// ::StoneyDSP::StoneyVCV::HP2::HP2ModuleWidget::~HP2ModuleWidget()
// {
// }

//==============================================================================

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::HP2::createHP2()
{
    ::rack::plugin::Model* modelHP2 = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::HP2::HP2Module,
        ::StoneyDSP::StoneyVCV::HP2::HP2ModuleWidget
    >("HP2");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP2 == nullptr, bad_alloc);
    return modelHP2;
}

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP2 {

//==============================================================================

::rack::plugin::Model* modelHP2 = ::StoneyDSP::StoneyVCV::HP2::createHP2();

//==============================================================================

}
}
}

//==============================================================================
