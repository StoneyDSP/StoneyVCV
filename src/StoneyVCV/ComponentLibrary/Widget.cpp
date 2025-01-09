/*******************************************************************************
 * @file src/StoneyVCV/ComponentLibrary/Widget.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2025 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV/ComponentLibrary/Widget.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <string>

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::Widget()
:   ::rack::widget::Widget(),
    box(::rack::math::Vec(), ::rack::math::Vec(INFINITY, INFINITY))
{
    // Assertions
    // DBG("StoneyDSP::StoneyVCV::ComponentLibrary::Widget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::~Widget()
{
    // DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::Widget");
    assert(!this->parent);

    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::step()
{
    return ::rack::widget::Widget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::DrawArgs &args)
{
    return ::rack::widget::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::ThemedWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget()
{
    // Assertions
    // DBG("StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::~ThemedWidget()
{
    // Assertions
    // DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget");
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::step()
{
    return ::rack::widget::Widget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args)
{
    // draw Themed BG
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

    return ::rack::widget::Widget::draw(args);
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
