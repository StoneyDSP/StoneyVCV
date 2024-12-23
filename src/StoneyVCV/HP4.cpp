/*******************************************************************************
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

#include <StoneyVCV/HP4.hpp>

//==============================================================================

#include <rack.hpp>

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP4 {

//==============================================================================

::rack::plugin::Model* modelHP4 = ::StoneyDSP::StoneyVCV::HP4::createHP4();

//==============================================================================

static const ::rack::math::Vec HP4Dimensions = (
    ::rack::window::mm2px(20.3199999965F), // 5.079999999F * 4.0F
    ::rack::window::mm2px(128.693333312F)
);

//==============================================================================

} // namespace HP4
} // namespace StoneyVCV
} // namespace StoneyDSP

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4Module::HP4Module()
{
    // Assertions
    DBG("Constructing StoneyVCV::HP4::HP4Module");
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_PARAMS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_INPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_OUTPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_LIGHTS == 0U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    this->config(
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_LIGHTS
    );
}

::StoneyDSP::StoneyVCV::HP4::HP4Module::~HP4Module()
{
    DBG("Destroying StoneyVCV::HP4::HP4Module");
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4Widget::HP4Widget()
:   hp4WidgetFrameBuffer(new ::rack::widget::FramebufferWidget),
    panelBorder(::rack::createWidget<::rack::app::PanelBorder>(::rack::math::Vec(0.0F, 0.0F)))
{
    // Assertions
    DBG("Constructing StoneyVCV::HP4::HP4Widget");
    assert(this->hp4WidgetFrameBuffer != nullptr);
    assert(this->panelBorder != nullptr);

    // Widgets
    this->hp4WidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->hp4WidgetFrameBuffer);

    // Border
    this->panelBorder->setSize(this->getSize());
    this->hp4WidgetFrameBuffer->addChild(this->panelBorder);
}

::StoneyDSP::StoneyVCV::HP4::HP4Widget::~HP4Widget()
{
    // Assertions
    DBG("Destroying StoneyVCV::HP4::HP4Widget");
    assert(!this->parent);

    // Children
    this->panelBorder->clearChildren();
    this->hp4WidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::HP4::HP4Widget::step()
{
    const auto& size = this->getSize();

    this->panelBorder->setSize(size);
    this->hp4WidgetFrameBuffer->setSize(size);

    return ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::HP4::HP4Widget::draw(const ::StoneyDSP::StoneyVCV::HP4::HP4Widget::DrawArgs& args)
{
    const auto& bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    const auto& bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;
    const auto& bgColor = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    const auto& bgGradientS0 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS0;
    const auto& bgGradientS1 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS1;
    const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& minWidth = ::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH;
    const auto& minHeight = ::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT;
    const auto& size = this->getSize();

    // Draw Themed BG
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg,
        /** x */0.0F,
        /** y */0.0F,
        /** w */size.x,
        /** h */size.y
        );
    ::nvgFillColor(args.vg, bgColor);
    ::nvgFill(args.vg);

    // Draw themed BG gradient
    const auto& bgGradient = ::nvgLinearGradient(args.vg,
        size.x * 0.5,
        0.0F,
        size.x * 0.5,
        380.0F,
        bgGradientS0,
        bgGradientS1
    );
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg,
        /** x */0.0F,
        /** y */0.0F,
        /** w */size.x,
        /** h */size.y
        );
    ::nvgFillPaint(args.vg, bgGradient);
    ::nvgFill(args.vg);

    // Draw line L
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */minWidth + (minWidth * 0.5F));           /** 1.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */size.y - (minWidth + (minWidth * 0.5F)));/** 1.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line R
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */size.x - (minWidth * 0.5F),              /** 0.5 screws left  */
        /** y */minWidth + (minWidth * 0.5F));           /** 1.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth * 0.5F),              /** 0.5 screws left  */
        /** y */size.y - (minWidth + (minWidth * 0.5F)));/** 1.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line T
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */minWidth + (minWidth * 0.5F),            /** 1.5 screws right */
        /** y */minWidth * 0.5F);                        /** 0.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth + (minWidth * 0.5F)), /** 1.5 screws left  */
        /** y */minWidth * 0.5F);                        /** 0.5 screws down  */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line B
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */minWidth + (minWidth * 0.5F),            /** 1.5 screws right */
        /** y */size.y - (minWidth * 0.5F));             /** 0.5 screws up    */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth + (minWidth * 0.5F)), /** 1.5 screws left  */
        /** y */size.y - (minWidth * 0.5F));             /** 0.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    ::StoneyDSP::ignoreUnused(minHeight);

    return ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::HP4ModuleWidget(::StoneyDSP::StoneyVCV::HP4::HP4Module* module)
:   size(
        ::rack::window::mm2px(20.3199999965F),
        ::rack::window::mm2px(128.693333312F)
    ),
    // Panel
    panel(::rack::createPanel<::rack::app::ThemedSvgPanel>(
        // Light-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP4-light.svg"
        ),
        // Dark-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::pluginInstance, "res/HP4-dark.svg"
        )
    )),
    hp4Widget(::rack::createWidget<::StoneyDSP::StoneyVCV::HP4::HP4Widget>(::rack::math::Vec(0.0F, 0.0F))),
    hp4ModuleWidgetFrameBuffer(new ::rack::widget::FramebufferWidget),
    screwsPositions{
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // top-right
            (this->size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-right
            (this->size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
    },
    screws{
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[2]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[3])
    },
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels)
{
    // Assertions
    DBG("Constructing StoneyVCV::HP4::HP4ModuleWidget");
    // assert(module != nullptr);
    assert(this->hp4Widget != nullptr);
    assert(this->hp4ModuleWidgetFrameBuffer != nullptr);
    assert(this->screws != nullptr);
    assert(this->screws[0] != nullptr);
    assert(this->screws[1] != nullptr);
    assert(this->screws[2] != nullptr);
    assert(this->screws[3] != nullptr);
    assert(this->panel != nullptr);

    this->setModule(module);
    this->setSize(this->size);
    this->setPanel(this->panel);
    this->getPanel()->setSize(this->getSize());

    // Frame Buffer
    this->hp4ModuleWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->hp4ModuleWidgetFrameBuffer);

    // Widget
    this->hp4Widget->setSize(this->getSize());
    this->hp4ModuleWidgetFrameBuffer->addChild(this->hp4Widget);

    // Screws
    for(auto screw : this->screws) {
        this->addChild(screw);
    }

    assert(this->getSize().x == ::rack::window::mm2px(20.3199999965F));
    assert(this->getSize().y == ::rack::window::mm2px(128.693333312F));
    assert(this->getPanel()->getSize().x == ::rack::window::mm2px(20.3199999965F));
    assert(this->getPanel()->getSize().y == ::rack::window::mm2px(128.693333312F));
}

::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::~HP4ModuleWidget()
{
    // Assertions
    DBG("Destroying StoneyVCV::HP4::HP4ModuleWidget");
    assert(!this->parent);

    // Children
    this->hp4Widget->clearChildren();
    this->hp4ModuleWidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::step()
{
    if(this->lastPrefersDarkPanels != ::rack::settings::preferDarkPanels) {
        this->hp4ModuleWidgetFrameBuffer->setDirty();
        this->lastPrefersDarkPanels = ::rack::settings::preferDarkPanels;
    }

    return ::rack::Widget::step();
}

//==============================================================================

/**
 *
 */
::rack::plugin::Model* ::StoneyDSP::StoneyVCV::HP4::createHP4()
{
    DBG("Creating StoneyVCV::HP4::modelHP4");

    ::rack::plugin::Model* modelHP4 = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::HP4::HP4Module,
        ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget
    >("HP4");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP4 == nullptr, bad_alloc);
    return modelHP4;
}

//==============================================================================
