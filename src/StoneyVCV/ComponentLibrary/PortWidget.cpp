/*******************************************************************************
 * @file src/StoneyVCV/ComponentLibrary/PortWidget.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2025 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV/ComponentLibrary/PortWidget.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/Widget.hpp>

//==============================================================================

#include <string>

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::ThemedPortWidgetPanel()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget(),
    labelText(""),
    isOutput(true),
    prefersDarkPanelsPtr(nullptr)
{
    // Assertions...
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel");

    this->setSize(::rack::math::Vec(28.55155F, 39.15691F));

    this->prefersDarkPanelsPtr = static_cast<const bool *>(&::rack::settings::preferDarkPanels);

    assert(this->prefersDarkPanelsPtr != nullptr);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::~ThemedPortWidgetPanel() noexcept
{
    // Assertions
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel");
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::step()
{
    // this->setSize(::rack::math::Vec(28.55155F, 39.15691F));

    return ::rack::widget::Widget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::draw(const StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::DrawArgs &args)
{
    const bool &prefersDarkPanels = *this->prefersDarkPanelsPtr;
    const auto& size = this->getSize();

    const auto& bgBlack = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortBlack : ::StoneyDSP::StoneyVCV::Panels::bgPortWhite;
    const auto& bgWhite = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortWhite : ::StoneyDSP::StoneyVCV::Panels::bgPortBlack;
    const auto& bgColor = prefersDarkPanels ? bgBlack : bgWhite;
    // const auto& bgGradientS0 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS0;
    // const auto& bgGradientS1 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS1;
    // const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& textWhite = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortBlack : ::StoneyDSP::StoneyVCV::Panels::bgPortWhite;
    const auto& textBlack = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortWhite : ::StoneyDSP::StoneyVCV::Panels::bgPortBlack;
    const auto& textColor = prefersDarkPanels ? textBlack : textWhite;

    // Load font from cache
	::std::shared_ptr<::rack::window::Font> font = APP->window->loadFont(
            ::rack::asset::system("res/fonts/DejaVuSans.ttf"
        )
    );

    if(this->isOutput)
    {
        // Draw themed bg panel box
        ::nvgBeginPath(args.vg);
        ::nvgRoundedRect(args.vg,
            /** x  */0.0F,
            /** y  */0.0F,
            /** w  */size.x,
            /** h  */size.y,
            /** rx */2.83465F
        );
        ::nvgFillColor(args.vg, bgColor);
        ::nvgFill(args.vg);

        // // Draw themed BG gradient
        // const auto& bgGradient = ::nvgLinearGradient(args.vg,
        //     /** x */size.x * 0.5,
        //     /** Y */0.0F,
        //     /** w */size.x * 0.5,
        //     /** h */size.y,
        //     /** s1 */bgGradientS0,
        //     /** s2 */bgGradientS1
        // );
        // ::nvgBeginPath(args.vg);
        // ::nvgRoundedRect(args.vg,
        //     /** x  */0.0F,
        //     /** y  */0.0F,
        //     /** w  */size.x,
        //     /** h  */size.y,
        //     /** rx */2.83465F
        // );
        // ::nvgFillPaint(args.vg, bgGradient);
        // ::nvgFill(args.vg);

        // // Draw border
        // ::nvgBeginPath(args.vg);
        // ::nvgRoundedRect(args.vg,
        //     /** x  */0.0F,
        //     /** y  */0.0F,
        //     /** w  */size.x,
        //     /** h  */size.y,
        //     /** rx */2.83465F
        // );
        // ::nvgStrokeColor(args.vg, borderColor);
        // ::nvgStrokeWidth(args.vg, 1.0F);
        // ::nvgStroke(args.vg);
    }

    // Don't draw text if font failed to load
	if (font) {
        ::nvgBeginPath(args.vg);
		// Select font handle
		::nvgFontFaceId(args.vg, font->handle);

		// Set font size and alignment
		::nvgFontSize(args.vg, 8.0F);
		::nvgTextAlign(args.vg,
            ::NVGalign::NVG_ALIGN_CENTER | ::NVGalign::NVG_ALIGN_BASELINE
        );
        ::nvgFillColor(args.vg, textColor);

		// Draw the text at a position
		::nvgText(args.vg,
            (size.x * 0.5F),
            (8.0F + 2.425775F),
            labelText.c_str(),
            NULL
        );
	}

    return ::rack::widget::Widget::draw(args);
}

const bool &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::getPrefersDarkPanels() const noexcept
{
    return *this->prefersDarkPanelsPtr;
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::ThemedPortWidget()
:   ::rack::app::ThemedSvgPort(),
    isOutput(true),
    panel(nullptr),
    lightSvg(
        ::rack::window::Svg::load(
            ::rack::asset::system("res/ComponentLibrary/PJ301M.svg")
        )
    ),
    darkSvg(
        ::rack::window::Svg::load(
            ::rack::asset::system("res/ComponentLibrary/PJ301M-dark.svg")
        )
    ),
    panelFrameBufferWidget(nullptr),
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels),
    prefersDarkPanelsPtr(nullptr),
    lastPixelRatio(APP->window->pixelRatio),
    pixelRatioPtr(nullptr)
{
    DBG("Constructing StoneyVCV::ComponentLibrary::ThemedPortWidget");

    this->panel = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel *>(
        ::StoneyDSP::StoneyVCV::createWidget<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel>(
            ::rack::math::Vec(
                0.0F,
                0.0F
            )
        )
    );

    this->panelFrameBufferWidget = dynamic_cast<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget *>(
        ::StoneyDSP::StoneyVCV::createWidget<::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget>(
            ::rack::math::Vec(
                0.0F - 2.425775F,
                0.0F - ((39.15691F - 23.7F) - 2.425775F)
            )
        )
    );

    this->prefersDarkPanelsPtr = static_cast<const bool *>(
        &::rack::settings::preferDarkPanels
    );
    this->pixelRatioPtr = static_cast<const float *>(&APP->window->pixelRatio);

    this->isOutput = this->type == ::rack::engine::Port::Type::OUTPUT;
    this->panel->isOutput = this->isOutput;

    ::rack::app::ThemedSvgPort::setSvg(this->lightSvg, this->darkSvg);

    this->panelFrameBufferWidget->setSize(this->panel->getSize());
    this->addChildBottom(this->panelFrameBufferWidget);
    this->panelFrameBufferWidget->addChildBottom(this->panel);

    // Oversample (for panel text)
    if (APP->window->pixelRatio < 2.0F) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->panelFrameBufferWidget->oversample = 2.0F;
	}
	else {
		this->panelFrameBufferWidget->oversample = 1.0F;
	}

    // Assertions
    assert(this->panel != nullptr);
    assert(this->panelFrameBufferWidget != nullptr);
    assert(this->prefersDarkPanelsPtr != nullptr);
    assert(this->pixelRatioPtr != nullptr);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::~ThemedPortWidget()
{
    // Assertions
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget");
    assert(!this->parent);

    // Children
    this->panel->clearChildren();
    this->panelFrameBufferWidget->clearChildren();
    this->clearChildren();

    this->panel = nullptr;
    this->panelFrameBufferWidget = nullptr;
    this->pixelRatioPtr = nullptr;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::step()
{
    const bool &prefersDarkPanels = *this->prefersDarkPanelsPtr;
    const float &currentPixelRatio = *this->pixelRatioPtr;

    if(this->lastPixelRatio != currentPixelRatio) {
        // Dispatch event
        PixelRatioChangeEvent ePixelRatioChanged;
        ePixelRatioChanged.newPixelRatio = currentPixelRatio;
        this->onPixelRatioChange(ePixelRatioChanged);
        // Update
        this->lastPixelRatio = currentPixelRatio;
    }

    if(this->lastPrefersDarkPanels != prefersDarkPanels) {
        this->panelFrameBufferWidget->setDirty();
        this->lastPrefersDarkPanels = prefersDarkPanels;
    }

    ::rack::app::ThemedSvgPort::setSvg(this->lightSvg, this->darkSvg);

    // Update
    this->isOutput = this->type == ::rack::engine::Port::Type::OUTPUT;
    this->panel->isOutput = this->isOutput;
    // this->fb->setSize(this->panel->getSize());

    return ::rack::app::ThemedSvgPort::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::DrawArgs &args)
{
    return ::rack::app::ThemedSvgPort::draw(args);
};

const bool &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::getPrefersDarkPanels() const noexcept
{
    return *this->prefersDarkPanelsPtr;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::onPixelRatioChange(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::PixelRatioChangeEvent & e)
{
    DBG("pixelRatioChanged event");
    DBG(::rack::string::f("%f", lastPixelRatio));
    DBG(::rack::string::f("%f", e.newPixelRatio));
    // Validate
    if(this->lastPixelRatio == e.newPixelRatio)
        return;

    if (APP->window->pixelRatio < 2.0F) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->panelFrameBufferWidget->oversample = 2.0F;
	}
	else {
		this->panelFrameBufferWidget->oversample = 1.0F;
	}

    this->panelFrameBufferWidget->setDirty();
}

const float &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::getPixelRatio() const noexcept
{
    return *this->pixelRatioPtr;
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
