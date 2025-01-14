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
    box(::rack::math::Rect(::rack::math::Vec(), ::rack::math::Vec(INFINITY, INFINITY))),
    parent(NULL),
    children(),
    visible(true),
    requestedDelete(false),
    pixelRatioPtr(nullptr)
{
    // Assertions
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::Widget");

    this->pixelRatioPtr = static_cast<const float *>(&APP->window->pixelRatio);

    assert(this->pixelRatioPtr != nullptr);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::~Widget() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::Widget");
    assert(!this->parent);

    this->clearChildren();

    this->pixelRatioPtr = nullptr;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::step()
{
    return ::rack::widget::Widget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::DrawArgs &args)
{
    return ::rack::widget::Widget::draw(args);
}

const float &::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::getPixelRatio() const noexcept
{
    return *this->pixelRatioPtr;
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::ThemedWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget(),
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels),
    prefersDarkPanelsPtr(nullptr)
{
    // Assertions
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget");

    this->prefersDarkPanelsPtr = static_cast<const bool *>(&::rack::settings::preferDarkPanels);

    assert(this->prefersDarkPanelsPtr != nullptr);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::~ThemedWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget");
    assert(!this->parent);

    // Children
    this->clearChildren();

    this->prefersDarkPanelsPtr = nullptr;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::step()
{
    const bool &currentPrefersDarkPanels = *this->prefersDarkPanelsPtr;

    if(this->lastPrefersDarkPanels != currentPrefersDarkPanels) {
        // Dispatch event
        PrefersDarkPanelsChangeEvent ePrefersDarkPanelsChanged;
        ePrefersDarkPanelsChanged.newPrefersDarkPanels = currentPrefersDarkPanels;
        this->onPrefersDarkPanelsChange(ePrefersDarkPanelsChanged);
        // Update
        this->lastPrefersDarkPanels = currentPrefersDarkPanels;
    }

    return ::rack::widget::Widget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args)
{
    const bool &prefersDarkPanels = *this->prefersDarkPanelsPtr;

    // draw Themed BG
    const auto& bgDark = ::StoneyDSP::StoneyVCV::Panels::bgDark;
    const auto& bgLight = ::StoneyDSP::StoneyVCV::Panels::bgLight;
    const auto& bgColor = prefersDarkPanels ? bgDark : bgLight;
    const auto& bgGradientS0 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS0;
    const auto& bgGradientS1 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS1;
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

const bool &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::getPrefersDarkPanels() const noexcept
{
    return *this->prefersDarkPanelsPtr;
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget::FramebufferWidget()
:   ::rack::widget::FramebufferWidget()
{
    // Assertions
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget::~FramebufferWidget() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::FramebufferWidget::FramebufferWidget");
    assert(!this->parent);

    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget::step()
{
    return ::rack::widget::FramebufferWidget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget::DrawArgs &args)
{
    // // For debugging the bounding box of the framebuffer
	// ::nvgStrokeWidth(args.vg, 2.0F);
	// ::nvgStrokeColor(args.vg, ::nvgRGBAf(1.0F, 1.0F, 0.0F, 0.5F));
	// ::nvgStroke(args.vg);

    return ::rack::widget::FramebufferWidget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::TransparentWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget()
{
    // Assertions
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::~TransparentWidget() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::TransparentWidget::TransparentWidget");
    assert(!this->parent);

    this->clearChildren();
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::OpaqueWidget::OpaqueWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget()
{
    // Assertions
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::OpaqueWidget");
}

::StoneyDSP::StoneyVCV::ComponentLibrary::OpaqueWidget::~OpaqueWidget() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::OpaqueWidget::OpaqueWidget");
    assert(!this->parent);

    this->clearChildren();
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget::SvgWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget()
{
    // Assertions
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget");

    this->box.size = ::rack::math::Vec();
}

::StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget::~SvgWidget() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::SvgWidget::SvgWidget");
    assert(!this->parent);

    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget::wrap() noexcept
{
    if (this->svg) {
		this->box.size = this->svg->getSize();
	}
	else {
		this->box.size = ::rack::math::Vec();
	}
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget::setSvg(::std::shared_ptr<::rack::window::Svg> newSvg)
{
    this->svg = newSvg;

    this->wrap();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget::draw(const DrawArgs &args)
{
    if (!this->svg)
		return;

	return ::rack::window::svgDraw(args.vg, this->svg->handle);
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
