/*******************************************************************************
 * @file src/StoneyVCV/ComponentLibrary/Widget.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2025 MIT License
 *
 ******************************************************************************/

#include <StoneyVCV/ComponentLibrary/Widget.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <string>

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::ThemedWidget()
:   fb(
        ::rack::createWidget<::rack::widget::FramebufferWidget>(
            ::rack::math::Vec(0.0F, 0.0F)
        )
    ),
    panelBorder(
        ::rack::createWidget<::rack::app::PanelBorder>(
            ::rack::math::Vec(0.0F, 0.0F)
        )
    )
{
    // Assertions
    // DBG("StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget");
    assert(this->fb != nullptr);
    assert(this->panelBorder != nullptr);

    // Widgets
    this->fb->setSize(this->getSize());
    this->addChild(this->fb);

    // Border
    this->panelBorder->setSize(this->getSize());
    this->fb->addChild(this->panelBorder);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::~ThemedWidget()
{
    // Assertions
    // DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget");
    assert(!this->parent);

    // Children
    this->panelBorder->clearChildren();
    this->fb->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::step()
{
    const auto& size = this->getSize();

    this->panelBorder->setSize(size);
    this->fb->setSize(size);

    return ::rack::widget::Widget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::drawThemedBg(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args)
{
    const auto& bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    const auto& bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;
    const auto& bgColor = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    const auto& bgGradientS0 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS0;
    const auto& bgGradientS1 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS1;
    const auto& size = this->getSize();

    // draw Themed BG
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
        /** x */size.x * 0.5,
        /** Y */0.0F,
        /** w */size.x * 0.5,
        /** h */size.y,
        /** s1 */bgGradientS0,
        /** s2 */bgGradientS1
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
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args)
{
    // draw Themed BG
    this->drawThemedBg(args);

    return ::rack::widget::Widget::draw(args);
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
