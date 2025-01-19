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

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::ThemedPortPanelWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget(),
    labelText(""),
    isOutput(true),
    prefersDarkPanelsPtr(nullptr)
{
    DBG("Constructing StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget");

    // Taken from the Core svg's
    this->setSize(::rack::math::Vec(28.55155F, 39.15691F));

    // Initial theme
    this->prefersDarkPanelsPtr = static_cast<const bool *>(&::rack::settings::preferDarkPanels);

    // Assertions...
    assert(this->prefersDarkPanelsPtr != nullptr);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::~ThemedPortPanelWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget");
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::step()
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::draw(const StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::DrawArgs &args)
{
    const bool &prefersDarkPanels = this->getPrefersDarkPanels();
    const auto& size = this->getSize();

    const auto& bgDark = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortDark : ::StoneyDSP::StoneyVCV::Panels::bgPortLight;
    const auto& bgLight = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortLight : ::StoneyDSP::StoneyVCV::Panels::bgPortDark;
    const auto& bgColor = prefersDarkPanels ? bgDark : bgLight;
    const auto& bgGradientS0 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS0;
    const auto& bgGradientS1 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS1;
    // const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& textLight = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortDark : ::StoneyDSP::StoneyVCV::Panels::bgPortLight;
    const auto& textDark = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortLight : ::StoneyDSP::StoneyVCV::Panels::bgPortDark;
    const auto& textColor = prefersDarkPanels ? textDark : textLight;

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
        ::nvgRoundedRect(args.vg,
            /** x  */0.0F,
            /** y  */0.0F,
            /** w  */size.x,
            /** h  */size.y,
            /** rx */2.83465F
        );
        ::nvgFillPaint(args.vg, bgGradient);
        ::nvgFill(args.vg);

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

    return ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::draw(args);
}

const bool &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::getPrefersDarkPanels() const noexcept
{
    return *this->prefersDarkPanelsPtr;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::setLabelText(const::std::string & newLabelText) noexcept
{
    this->labelText = newLabelText;
}

const::std::string &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::getLabelText() const noexcept
{
    return this->labelText;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::setIsOutput(const bool &newIsOutput) noexcept
{
    this->isOutput = newIsOutput;
}

const bool &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget::getIsOutput() const noexcept
{
    return this->isOutput;
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::ThemedPortWidget()
:   ::rack::app::ThemedSvgPort(),
    lightSvg(
        ::rack::window::Svg::load(
            ::rack::asset::system("res/ComponentLibrary/PJ301M.svg")
        )
    ),
    darkSvg(
        ::rack::window::Svg::load(
            ::rack::asset::system("res/ComponentLibrary/PJ301M-dark.svg")
        )
    )
{
    DBG("Constructing StoneyVCV::ComponentLibrary::ThemedPortWidget");

    ::rack::app::ThemedSvgPort::setSvg(this->lightSvg, this->darkSvg);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::~ThemedPortWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget");
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::step()
{
    ::rack::app::ThemedSvgPort::setSvg(this->lightSvg, this->darkSvg);

    return ::rack::app::ThemedSvgPort::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::DrawArgs &args)
{
    return ::rack::app::ThemedSvgPort::draw(args);
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
