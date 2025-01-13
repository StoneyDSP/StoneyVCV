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

::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget::PanelBorderWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget()
{
    // Assertions
    DBG("Constructing StoneyVCV::ComponentLibrary::PanelBorderWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget::~PanelBorderWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::ComponentLibrary::PanelBorderWidget");
    assert(!this->parent);

    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget::DrawArgs &args)
{
    const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& size = this->getSize();

	::nvgBeginPath(args.vg);
	::nvgRect(args.vg, 0.5, 0.5, size.x - 1.0, size.y - 1.0);
	::nvgStrokeColor(args.vg, borderColor);
	::nvgStrokeWidth(args.vg, 1.0);
	::nvgStroke(args.vg);
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::PanelLinesWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget()
{
    // Assertions
    DBG("Constructing StoneyVCV::ComponentLibrary::PanelLinesWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::~PanelLinesWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::ComponentLibrary::PanelLinesWidget");
    assert(!this->parent);

    this->clearChildren();
}

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
    fb(nullptr),
    panelBorder(nullptr),
    panelLines(nullptr),
    // Screws
    screwsPositions{
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // top-right
            (this->getSize().x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (this->getSize().y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
        ::rack::math::Vec( // bottom-right
            (this->getSize().x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (this->getSize().y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
    },
    screws{nullptr}
{
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget");

    this->fb = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget *>(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            this->getSize()
        )
    );
    this->panelBorder = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget *>(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            this->getSize()
        )
    );
    this->panelLines = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget *>(
        ::StoneyDSP::StoneyVCV::createWidgetSized<::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget>(
            ::rack::math::Vec(0.0F, 0.0F),
            this->getSize()
        )
    );
    this->screws = {
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0])),
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1])),
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[2])),
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[3]))
    };

    // Framebuffer
    this->fb->setSize(this->getSize());
    this->addChildBottom(this->fb);

    // Border
    this->panelBorder->setSize(this->getSize());
    this->fb->addChildBottom(this->panelBorder);

    // Lines
    this->panelLines->setSize(this->getSize());
    this->fb->addChild(this->panelLines);

    // Screws
    for(const auto& screw : this->screws) {
        this->fb->addChild(screw);
    }

    // Assertions
    assert(this->fb != nullptr);
    assert(this->panelBorder != nullptr);
    assert(this->panelLines != nullptr);
    assert(this->screws[0] != nullptr);
    assert(this->screws[1] != nullptr);
    assert(this->screws[2] != nullptr);
    assert(this->screws[3] != nullptr);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::~ThemedPanelWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget");
    assert(!this->parent);

    // Children
    // for(const auto& screw : this->screws) {
    //     screw->clearChildren();
    // }
    this->clearChildren();

    this->fb = nullptr;
    this->panelBorder = nullptr;
    this->panelLines = nullptr;
    this->screws[0] = nullptr;
    this->screws[1] = nullptr;
    this->screws[2] = nullptr;
    this->screws[3] = nullptr;
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

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::onPrefersDarkPanelsChange(const PrefersDarkPanelsChangeEvent & e)
{
    // Validate
    if(this->lastPrefersDarkPanels == e.newPrefersDarkPanels)
        return;

    // Update
    this->fb->setDirty();

    // Opaque behaviour p.1
    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::onPrefersDarkPanelsChange(e);

    // Opaque behaviour p.2
    return e.stopPropagating();
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
