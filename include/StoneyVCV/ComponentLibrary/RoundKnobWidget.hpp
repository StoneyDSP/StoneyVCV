/*******************************************************************************
 * @file include/StoneyVCV/ComponentLibrary/RoundKnob.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief @PROJECT_DESCRIPTION@
 * @version @plugin_VERSION@
 *
 * @copyright MIT License
 *
 * Copyright (c) 2024 Nathan J. Hood <nathanjhood@googlemail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#define STONEYVCV_COMPONENTLIBRARY_ROUNDKNOB_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/Widget.hpp>
#include <StoneyVCV/ComponentLibrary/ParamWidget.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

//==============================================================================

#include <string>

//==============================================================================

namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

namespace StoneyVCV
{
/** @addtogroup StoneyVCV
 *  @{
 */

//==============================================================================

namespace ComponentLibrary
{
/** @addtogroup ComponentLibrary
 *  @{
 */

//==============================================================================

/**
 *
 *
 */
struct ThemedRoundKnobPanelWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::DrawArgs;

    //==========================================================================

    ThemedRoundKnobPanelWidget()
    :   ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget()
    {

    }

    virtual ~ThemedRoundKnobPanelWidget() noexcept
    {
        assert(!this->parent);
    }

    //==========================================================================

    virtual void step() override
    {
        return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::step();
    }

    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedRoundKnobPanelWidget::DrawArgs &args) override
    {
        const bool &prefersDarkPanels = this->getPrefersDarkPanels();
        const auto &size = this->getSize();

        // For debugging the bounding box of the widget
        const auto &bgColor = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgLight: ::StoneyDSP::StoneyVCV::Panels::bgDark;
        // const auto &bgGradientS0 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS0;
        // const auto &bgGradientS1 = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS1;
        // const auto &borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
        const auto &textColor = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgPortDark : ::StoneyDSP::StoneyVCV::Panels::bgPortLight;
        const auto &fontSize = this->getFontSize();

        // Load font from cache
        ::std::shared_ptr<::rack::window::Font> font = APP->window->loadFont(
                ::rack::asset::system("res/fonts/DejaVuSans.ttf"
            )
        );

        // Clip the bottom of the ring
        ::nvgScissor(args.vg,
            0.0F - (size.x * 0.5F),
            0.0F - (fontSize * 2.0F),
            size.x * 2.0F,
            size.y + (fontSize * 2.0F)
        );

        // Draw the ring as the colour-filled diff between two circles
        ::nvgBeginPath(args.vg);
        ::nvgCircle(args.vg,
            size.x * 0.5F,
            size.y * 0.5F,
            (size.x * 0.5F) + 4.0F
        );
        ::nvgCircle(args.vg,
            size.x * 0.5F,
            size.y * 0.5F,
            (size.x * 0.5F) + 3.0F
        );
        ::nvgPathWinding(args.vg, NVG_HOLE);
        ::nvgFillColor(args.vg, bgColor);
        ::nvgFill(args.vg);

        // // Draw themed bg panel box
        // ::nvgBeginPath(args.vg);
        // ::nvgRoundedRect(args.vg,
        //     /** x  */0.0F,
        //     /** y  */0.0F,
        //     /** w  */size.x,
        //     /** h  */size.y,
        //     /** rx */2.83465F
        // );
        // ::nvgFillColor(args.vg, bgColor);
        // ::nvgFill(args.vg);

        // ::nvgBeginPath(args.vg);
        // ::nvgStrokeWidth(args.vg, 2.0F);
        // ::nvgStrokeColor(args.vg, ::nvgRGBAf(1.0F, 1.0F, 0.0F, 0.5F));
        // ::nvgStroke(args.vg);
        // // Draw themed BG gradient
        // const auto& bgGradient = ::nvgLinearGradient(args.vg,
        //     /** x */size.x * 0.5,
        //     /** Y */0.0F,
        //     /** w */size.x * 0.5,
        //     /** h */size.y,
        //     /** s1 */bgGradientS0,
        //     /** s2 */bgGradientS1
        // );
        // ::nvgRoundedRect(args.vg,
        //     /** x  */0.0F,
        //     /** y  */0.0F,
        //     /** w  */size.x,
        //     /** h  */size.y,
        //     /** rx */2.83465F
        // );
        // ::nvgFillPaint(args.vg, bgGradient);
        // ::nvgFill(args.vg);

        // Don't draw text if font failed to load
        if (font) {
            ::nvgBeginPath(args.vg);
            // Select font handle
            ::nvgFontFaceId(args.vg, font->handle);

            // Set font size and alignment
            ::nvgFontSize(args.vg, fontSize);
            ::nvgTextAlign(args.vg,
                ::NVGalign::NVG_ALIGN_CENTER | ::NVGalign::NVG_ALIGN_BASELINE
            );
            ::nvgFillColor(args.vg, textColor);

            // Draw the text at a position
            ::nvgText(args.vg,
                (size.x * 0.5F),
                0.0F - (fontSize), // font size / 2
                this->getLabelText().c_str(),
                NULL
            );
        }

        return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::draw(args);
    }

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedRoundKnobPanelWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedRoundKnobPanelWidget)
};

//==============================================================================

struct RoundKnob : virtual ::rack::app::SvgKnob
{
    RoundKnob()
    :   ::rack::app::SvgKnob(),
        bg(nullptr)
    {
		this->minAngle = -0.83 * M_PI;
		this->maxAngle = 0.83 * M_PI;

		this->bg = new ::rack::widget::SvgWidget;
		this->fb->addChildBelow(this->bg, this->tw);
	}

    virtual ~RoundKnob() noexcept
    {
        assert(!this->parent);

        this->clearChildren();
    }

    /** */
	::rack::widget::SvgWidget* bg = NULL;

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundKnob)
};

//==============================================================================

struct RoundBlackKnob : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob
{
public:

	RoundBlackKnob()
    : ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob()
    {
		this->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundBlackKnob.svg"
                )
            )
        );
		this->bg->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundBlackKnob_bg.svg"
                )
            )
        );
	}

    ~RoundBlackKnob()
    {
        assert(!this->parent);

        this->clearChildren();
    }

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundBlackKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundBlackKnob)
};


struct RoundSmallBlackKnob : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob
{

public:

    RoundSmallBlackKnob()
    :   ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob()
    {
		this->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundSmallBlackKnob.svg"
                )
            )
        );

		this->bg->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundSmallBlackKnob_bg.svg"
                )
            )
        );
	}

    ~RoundSmallBlackKnob()
    {
        assert(!this->parent);

        this->clearChildren();
    }

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundSmallBlackKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundSmallBlackKnob)
};

struct RoundLargeBlackKnob : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob
{

public:

    RoundLargeBlackKnob()
    :   ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob()
    {
		this->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundLargeBlackKnob.svg"
                )
            )
        );

		this->bg->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundLargeBlackKnob_bg.svg"
                )
            )
        );
	}

    ~RoundLargeBlackKnob()
    {
        assert(!this->parent);

        this->clearChildren();
    }

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundLargeBlackKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundLargeBlackKnob)
};

struct RoundBigBlackKnob : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob
{

public:

	RoundBigBlackKnob()
    :   ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob()
    {
		this->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundBigBlackKnob.svg"
                )
            )
        );

		this->bg->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundBigBlackKnob_bg.svg"
                )
            )
        );
	}

    ~RoundBigBlackKnob()
    {
        assert(!this->parent);

        this->clearChildren();
    }

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundBigBlackKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundBigBlackKnob)
};

struct RoundHugeBlackKnob : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob
{

public:

    RoundHugeBlackKnob()
    :   ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob()
    {
		this->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundHugeBlackKnob.svg"
                )
            )
        );

		this->bg->setSvg(
            ::rack::window::Svg::load(
                ::rack::asset::system(
                    "res/ComponentLibrary/RoundHugeBlackKnob_bg.svg"
                )
            )
        );
	}

    ~RoundHugeBlackKnob()
    {
        assert(!this->parent);

        this->clearChildren();
    }

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundHugeBlackKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundHugeBlackKnob)
};

struct RoundBlackSnapKnob : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob
{

public:

	RoundBlackSnapKnob()
    :   ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob()
    {
		snap = true;
	}

    ~RoundBlackSnapKnob()
    {
        assert(!this->parent);

        this->clearChildren();
    }

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundBlackSnapKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundBlackSnapKnob)
};

//==============================================================================

  /// @} group ComponentLibrary
} // namespace ComponentLibrary

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif // STONEYVCV_BUILD_COMPONENTLIBRARY

//==============================================================================
