/*******************************************************************************
 * @file src/StoneyVCV/ComponentLibrary/PortWidget.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2025 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV/ComponentLibrary/PanelWidget.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/Widget.hpp>

//==============================================================================

#include <string>
#include <array>

//==============================================================================

void ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::DrawArgs &args)
{
    const auto& minWidth = ::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH;
    const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& size = this->getSize();

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
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::ThemedPanelWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget(),
    fb(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::rack::widget::FramebufferWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            this->getSize()
        )
    ),
    // screwsPositions{
    //     ::rack::math::Vec( // top-left
    //         (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
    //         (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
    //     ),
    //     ::rack::math::Vec( // top-right
    //         (this->getSize().x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
    //         (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
    //     ),
    //     ::rack::math::Vec( // bottom-left
    //         (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
    //         (this->getSize().y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
    //     ),
    //     ::rack::math::Vec( // bottom-right
    //         (this->getSize().x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
    //         (this->getSize().y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
    //     ),
    // },
    // screws{
    //     ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0]),
    //     ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1]),
    //     ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[2]),
    //     ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[3])
    // },
    panelLines(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            this->getSize()
        )
    ),
    panelBorder(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::rack::app::PanelBorder>(
            ::rack::math::Vec(0.0F, 0.0F),
            this->getSize()
        )
    )
{
    // Assertions
    DBG("StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget");
    assert(this->fb != nullptr);
    // assert(this->screws[0] != nullptr);
    // assert(this->screws[1] != nullptr);
    // assert(this->screws[2] != nullptr);
    // assert(this->screws[3] != nullptr);
    assert(this->panelLines != nullptr);
    assert(this->panelBorder != nullptr);

    // Widgets
    this->fb->setSize(this->getSize());
    this->addChild(this->fb);

    // Screws
    // for(const auto& screw : this->screws) {
    //     this->fb->addChild(screw);
    // }

    // Border
    this->panelLines->setSize(this->getSize());
    this->fb->addChild(this->panelLines);
    this->panelBorder->setSize(this->getSize());
    this->fb->addChild(this->panelBorder);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::~ThemedPanelWidget()
{
    // Assertions
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget");
    assert(!this->parent);

    // Children
    this->panelBorder->clearChildren();
    // for(const auto& screw : this->screws) {
    //     screw->clearChildren();
    // }
    this->fb->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::step()
{
    const auto& size = this->getSize();

    this->panelLines->setSize(size);
    this->panelBorder->setSize(size);
    this->fb->setSize(size);

    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::DrawArgs &args)
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::draw(args);
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
