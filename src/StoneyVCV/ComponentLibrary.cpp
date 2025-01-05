/*******************************************************************************
 * @file src/StoneyVCV/ComponentLibrary.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_PLUGIN)

#include <StoneyVCV/plugin.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <string>

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

namespace Panels {

//==============================================================================

const ::NVGcolor bgWhite = ::nvgRGBA(235, 235, 235, 255);
const ::NVGcolor bgPortWhite = ::nvgRGBA(31, 31, 31, 255); // is dark
const ::NVGcolor bgGradientWhiteS0 = ::nvgRGBA(235, 235, 235, 0);
const ::NVGcolor bgGradientWhiteS1 = ::nvgRGBA(225, 225, 225, 255);

const ::NVGcolor bgBlack = ::nvgRGBA(43, 43, 43, 255);
const ::NVGcolor bgPortBlack = ::nvgRGBA(237, 237, 237, 255); // is light
const ::NVGcolor bgGradientBlackS0 = ::nvgRGBA(42, 42, 43, 0);
const ::NVGcolor bgGradientBlackS1 = ::nvgRGBA(23, 23, 23, 255);

const ::NVGcolor borderColor = nvgRGBAf(0.5F, 0.5F, 0.5F, 0.5F);

const ::StoneyDSP::float_t MIN_WIDTH = 15.0F; //::rack::window::mm2px(5.079999999F);
const ::StoneyDSP::float_t MIN_HEIGHT = 380.0F; // ::rack::window::mm2px(128.693333312F);

//==============================================================================

void addScrewsToWidget(::rack::widget::Widget* widget)
{
    const auto& size = widget->getSize();

    const ::rack::math::Vec screwsPositions [4] = {
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
        ::rack::math::Vec( // top-right
            (size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))),
        ::rack::math::Vec(// bottom-right
            (size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)))
    };
    ::rack::ThemedScrew* screws [4] = {
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[0]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[1]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[2]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[3])
    };
    for(auto screw : screws) {
        widget->addChild(screw);
    }
}

//==============================================================================

} // namespace Panels

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::ThemedPortWidgetPanel()
:   labelText(""),
    isOutput(true)
{
    // TODO: Assertions...
    this->setSize(::rack::math::Vec(28.55155F, 39.15691F));
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::~ThemedPortWidgetPanel()
{
    // Assertions
    // DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel");
    assert(!this->parent);

    // Children
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::step()
{
    this->setSize(::rack::math::Vec(28.55155F, 39.15691F));
    return ::rack::widget::Widget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::draw(const StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::DrawArgs &args)
{
    const auto& bgBlack = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortBlack : ::StoneyDSP::StoneyVCV::Panels::bgPortWhite;
    const auto& bgWhite = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortWhite : ::StoneyDSP::StoneyVCV::Panels::bgPortBlack;
    const auto& bgColor = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    // const auto& bgGradientS0 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS0;
    // const auto& bgGradientS1 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS1;
    // const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& textWhite = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortBlack : ::StoneyDSP::StoneyVCV::Panels::bgPortWhite;
    const auto& textBlack = this->isOutput ? ::StoneyDSP::StoneyVCV::Panels::bgPortWhite : ::StoneyDSP::StoneyVCV::Panels::bgPortBlack;
    const auto& textColor = ::rack::settings::preferDarkPanels ? textBlack : textWhite;
    const auto& size = this->getSize();

    // Load font from cache
	::std::shared_ptr<::rack::window::Font> font = APP->window->loadFont(
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/fonts/DejaVuSans.ttf"
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
            (this->getSize().x * 0.5F),
            (8.0F + 2.425775F),
            labelText.c_str(),
            NULL
        );
	}

    return ::rack::widget::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::ThemedPortWidget()
:   isOutput(true),
    panel(::rack::createWidget<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel>(
        ::rack::math::Vec(
            0.0F - 2.425775F,
            0.0F - ((39.15691F - 23.7F) - 2.425775F)
        )
    )),
    fb(new ::rack::FramebufferWidget),
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels)
{
    // // TODO: Assertions
    // DBG("Constructing StoneyVCV::ComponentLibrary::ThemedPortWidget");
    this->isOutput = this->type == ::rack::engine::Port::Type::OUTPUT;
    this->panel->isOutput = this->isOutput;

    this->setSize(this->panel->getSize());
    this->fb->setSize(this->panel->getSize());
    this->addChildBottom(this->fb);
    this->fb->addChild(this->panel);

    this->setSvg(
        ::rack::window::Svg::load(
            ::rack::asset::system("res/ComponentLibrary/PJ301M.svg")
        ),
        ::rack::window::Svg::load(
            ::rack::asset::system("res/ComponentLibrary/PJ301M-dark.svg")
        )
    );
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::~ThemedPortWidget()
{
    // Assertions
    // DBG("Destroying StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget");
    assert(!this->parent);

    // Children
    this->panel->clearChildren();
    this->fb->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::step()
{
    if (APP->window->pixelRatio < 2.0F) {
		// Small details draw poorly at low DPI,
        // so oversample when drawing to the framebuffer
		this->fb->oversample = 2.0F;
	}
	else {
		this->fb->oversample = 1.0F;
	}

    if(this->lastPrefersDarkPanels != ::rack::settings::preferDarkPanels) {
        this->fb->setDirty();
        this->lastPrefersDarkPanels = ::rack::settings::preferDarkPanels;
    }

    // Update
    this->isOutput = this->type == ::rack::engine::Port::Type::OUTPUT;
    this->panel->isOutput = this->isOutput;
    this->fb->setSize(this->panel->getSize());

    return ::rack::app::ThemedSvgPort::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::DrawArgs &args)
{
    return ::rack::app::ThemedSvgPort::draw(args);
};

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::ThemedWidget()
:   fb(new ::rack::widget::FramebufferWidget),
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

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::drawDividerLines(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args)
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

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args)
{
    // draw Themed BG
    this->drawThemedBg(args);

    // Draw lines
    this->drawDividerLines(args);

    return ::rack::widget::Widget::draw(args);
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================
