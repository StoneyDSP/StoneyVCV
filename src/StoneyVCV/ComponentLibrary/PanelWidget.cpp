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
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget(),
    borderColor(::StoneyDSP::StoneyVCV::Panels::borderColor)
{
    // Assertions
    DBG("Constructing StoneyVCV::ComponentLibrary::PanelBorderWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget::PanelBorderWidget(::rack::math::Rect newBox)
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget(newBox),
    borderColor(::StoneyDSP::StoneyVCV::Panels::borderColor)
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
    const auto& borderColor = this->getBorderColor();
    const auto& size = this->getSize();

	::nvgBeginPath(args.vg);
    ::nvgLineCap(args.vg, NVG_MITER);
    ::nvgLineJoin(args.vg, NVG_MITER);
	::nvgRect(args.vg,
        0.5F,
        0.5F,
        size.x - 1.0F,
        size.y - 1.0F
    );
	::nvgStrokeColor(args.vg, borderColor);
	::nvgStrokeWidth(args.vg, 1.0F);
	::nvgStroke(args.vg);
}

const ::NVGcolor &::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget::getBorderColor() const noexcept
{
    return this->borderColor;
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::PanelLinesWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget(),
    borderColor(::StoneyDSP::StoneyVCV::Panels::borderColor)
{
    // Assertions
    DBG("Constructing StoneyVCV::ComponentLibrary::PanelLinesWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::PanelLinesWidget(::rack::math::Rect newBox)
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget(newBox),
    borderColor(::StoneyDSP::StoneyVCV::Panels::borderColor)
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
    const auto& borderColor = this->getBorderColor();
    const auto& size = this->getSize();

    // Draw line L
    ::nvgBeginPath(args.vg);
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
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
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
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
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
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
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
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

const ::NVGcolor &::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::getBorderColor() const noexcept
{
    return this->borderColor;
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::ThemedPanelWidget(::rack::math::Rect newBox)
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget(newBox),
    paramPanelWidgets{nullptr},
    portPanelWidgets{nullptr},
    numScrews(0U),
    numParams(0U),
    numPorts(0U),
    numLights(0U),
    fb(nullptr),
    panelBorder(nullptr),
    panelLines(nullptr),
    // Screws
    screwsPositions{::rack::math::Vec()},
    screws{nullptr}
{
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget");

    this->setBox(newBox);

    this->portPanelWidgets.clear();     // because element 0 is a null-ish value from the in-class initializer...
    this->paramPanelWidgets.clear();    // because element 0 is a null-ish value from the in-class initializer...
    this->portPanelWidgets.reserve(this->numPorts);
    this->paramPanelWidgets.reserve(this->numParams);

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
    // Screws
    this->screwsPositions = {
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
    };
    // Screws
    this->screws = {
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0])),
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1])),
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[2])),
        dynamic_cast<::rack::componentlibrary::ThemedScrew *>(::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[3]))
    };
    this->screws.at(0)->setPosition( // Centered
        this->screwsPositions.at(0).minus(this->screws.at(0)->getSize().div(2.0F))
    );
    this->screws.at(1)->setPosition( // Centered
        this->screwsPositions.at(1).minus(this->screws.at(1)->getSize().div(2.0F))
    );
    this->screws.at(2)->setPosition( // Centered
        this->screwsPositions.at(2).minus(this->screws.at(2)->getSize().div(2.0F))
    );
    this->screws.at(3)->setPosition( // Centered
        this->screwsPositions.at(3).minus(this->screws.at(3)->getSize().div(2.0F))
    );

    // Framebuffer
    assert(this->fb != nullptr);
    this->fb->setSize(this->getSize());
    this->addChildBottom(this->fb);

    // Border
    assert(this->panelBorder != nullptr);
    this->panelBorder->setSize(this->getSize());
    this->fb->addChildBottom(this->panelBorder);

    // Lines
    assert(this->panelLines != nullptr);
    this->panelLines->setSize(this->getSize());
    this->fb->addChild(this->panelLines);

    // Screws
    for(const auto& screw : this->screws) {
        assert(screw != nullptr);
        this->fb->addChild(screw);
    }

    // Assertions
    assert(static_cast<unsigned int>(this->getPosition().x) == static_cast<unsigned int>(0.0F) && "box.pos.x should be 0.0F");
    assert(static_cast<unsigned int>(this->getPosition().y) == static_cast<unsigned int>(0.0F) && "box.pos.y should be 0.0F");
    assert(static_cast<unsigned int>(this->getSize().x)     >  static_cast<unsigned int>(0.0F) && "box.size.x should be greater than 0.0F");
    assert(static_cast<unsigned int>(this->getSize().y)     >  static_cast<unsigned int>(0.0F) && "box.size.x should be greater than 0.0F");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::~ThemedPanelWidget() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget");

    // Assertions
    assert(!this->parent);

    // Children
    this->clearChildren();

    this->fb = nullptr;
    this->panelBorder = nullptr;
    this->panelLines = nullptr;
    for(auto &screw : this->screws) {
        screw = nullptr;
    }
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::step()
{
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

const ::std::size_t &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getNumScrews() const noexcept
{
    return this->numScrews;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::setNumScrews(const ::std::size_t &newNumScrews)
{
    // Validate
    if(this->getNumScrews() == newNumScrews)
        return;

    // Update
    this->numScrews = newNumScrews;

    // TODO: Dispatch event? Resize vector?
    // this->screws.reserve(this->getNumScrews());
    if(!this->fb->dirty)
        this->fb->setDirty();
}

const ::std::size_t &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getNumParams() const noexcept
{
    return this->numParams;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::setNumParams(const ::std::size_t &newNumParams)
{
    // Validate
    if(this->getNumParams() == newNumParams)
        return;

    // Update
    this->numParams = newNumParams;

    // TODO: Dispatch event? Resize vector?
    // this->paramPanelWidgets.reserve(this->getNumParams());
    if(!this->fb->dirty)
        this->fb->setDirty();
}

const ::std::size_t &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getNumPorts() const noexcept
{
    return this->numPorts;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::setNumPorts(const ::std::size_t &newNumPorts)
{
    // Validate
    if(this->getNumPorts() == newNumPorts)
        return;

    // Update
    this->numPorts = newNumPorts;

    // TODO: Dispatch event? Resize vector?
    // this->portPanelWidgets.reserve(this->getNumPorts());
    if(!this->fb->dirty)
        this->fb->setDirty();
}

const ::std::size_t &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getNumLights() const noexcept
{
    return this->numLights;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::setNumLights(const ::std::size_t &newNumLights)
{
    if(this->getNumLights() == newNumLights)
        return;

    this->numLights = newNumLights;
    // TODO: Dispatch event? Resize vector?
    // this->lightPanelWidgets.resize(this->getNumLights());
    if(!this->fb->dirty)
        this->fb->setDirty();
}

::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getFrameBufferWidget() noexcept
{
    return *this->fb;
}

::std::vector<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget *> &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getPortPanelWidgets() noexcept
{
    return this->portPanelWidgets;
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getPortPanelWidget(const ::std::size_t &i) noexcept(false)
{
    try {
        return *this->portPanelWidgets.at(i);
    } catch (const std::out_of_range& e) {
        DBG("Index out of range: %s", e.what());
        return *this->portPanelWidgets.at(0);
    }
}

::std::vector<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget *> &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getParamPanelWidgets() noexcept
{
    return this->paramPanelWidgets;
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::getParamPanelWidget(const ::std::size_t &i) noexcept(false)
{
    try {
        return *this->paramPanelWidgets.at(i);
    } catch (const std::out_of_range& e) {
        DBG("Index out of range: %s", e.what());
        return *this->paramPanelWidgets.at(0);
    }
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
