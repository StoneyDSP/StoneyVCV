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

::StoneyDSP::VCVRack::HP1Module::HP1Module()
{
    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::VCVRack::HP1Module::PARAMS_LEN,   // numParams
        ::StoneyDSP::VCVRack::HP1Module::INPUTS_LEN,   // numInputs
        ::StoneyDSP::VCVRack::HP1Module::OUTPUTS_LEN,  // numOutputs
        ::StoneyDSP::VCVRack::HP1Module::LIGHTS_LEN    // numLights
    );
}

::StoneyDSP::VCVRack::HP1Module::~HP1Module()
{}

//==============================================================================

::StoneyDSP::VCVRack::HP1Widget::HP1Widget()
{
    // Widgets
    hp1WidgetFrameBuffer = new ::rack::FramebufferWidget;
    hp1WidgetFrameBuffer->setSize(box.size);
    addChild(hp1WidgetFrameBuffer);

    panelBorder = ::rack::createWidget<::rack::PanelBorder>(::rack::math::Vec(0.0f, 0.0f));
    panelBorder->setSize(box.size);
    hp1WidgetFrameBuffer->addChild(panelBorder);
}

::StoneyDSP::VCVRack::HP1Widget::~HP1Widget()
{}

void ::StoneyDSP::VCVRack::HP1Widget::step()
{
    panelBorder->box.size = box.size;
    ::StoneyDSP::VCVRack::Widget::step();
}

void ::StoneyDSP::VCVRack::HP1Widget::draw(const ::StoneyDSP::VCVRack::Widget::DrawArgs &args)
{

    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg, 0.0, 0.0, box.size.x, box.size.y);
    ::NVGcolor bg = ::rack::settings::preferDarkPanels ? ::nvgRGB(42, 42, 42) : ::nvgRGB(235, 235, 235);
    ::nvgFillColor(args.vg, bg);
    ::nvgFill(args.vg);
    ::StoneyDSP::VCVRack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::VCVRack::HP1ModuleWidget::HP1ModuleWidget(::StoneyDSP::VCVRack::HP1Module* module)
{
    setModule(module);
    setPanel(::rack::createPanel(
        // Light-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::VCVRack::pluginInstance, "res/HP1-light.svg"
        ),
        // Dark-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::VCVRack::pluginInstance, "res/HP1-dark.svg"
        )
    ));
    // Widgets
    hp1ModuleWidgetFrameBuffer = new ::rack::FramebufferWidget;
    hp1ModuleWidgetFrameBuffer->setSize(box.size);
    addChild(hp1ModuleWidgetFrameBuffer);
    //
    hp1Widget = ::rack::createWidget<::StoneyDSP::VCVRack::HP1Widget>(::rack::math::Vec(0.0f, 0.0f));
    hp1Widget->setSize(box.size);
    hp1ModuleWidgetFrameBuffer->addChild(hp1Widget);
}

::StoneyDSP::VCVRack::HP1ModuleWidget::~HP1ModuleWidget()
{}

/**
 *
 */
::rack::plugin::Model* ::StoneyDSP::VCVRack::createHP1()
{

    ::rack::plugin::Model* modelHP1 = ::rack::createModel<
        ::StoneyDSP::VCVRack::HP1Module,
        ::StoneyDSP::VCVRack::HP1ModuleWidget
    >("HP1");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP1 == nullptr, bad_alloc);
    return modelHP1;
}

//==============================================================================

namespace StoneyDSP {

namespace VCVRack {

::rack::plugin::Model* modelHP1 = ::StoneyDSP::VCVRack::createHP1();

}

}

//==============================================================================
