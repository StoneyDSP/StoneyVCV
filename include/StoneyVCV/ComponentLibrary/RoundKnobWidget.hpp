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
    :   ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget(),
        minAngle(0.0F),
        maxAngle(0.0F),
        leading(0.0F)
    {
        DBG("Constructing StoneyVCV::ComponentLibrary::ThemedRoundKnobPanelWidget");

        this->minAngle = (0.0F - (5.0F / 6.0F)) * M_PI;
        this->maxAngle = (5.0F / 6.0F) * M_PI;
        this->leading = (4.0F);
    }

    virtual ~ThemedRoundKnobPanelWidget() noexcept
    {
        DBG("Destroying StoneyVCV::ComponentLibrary::ThemedRoundKnobPanelWidget");
        assert(!this->parent);

        this->clearChildren();
    }

    //==========================================================================

    virtual void step() override
    {
        return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::step();
    }

    float radiansToDegrees(const float &radians)
    {
        return radians * (180.0F / M_PI);
    }

    ::rack::math::Vec radiusToXY(const float &radius, float angle, float rotation = 0.0F)
    {
        const float theta = (angle + rotation) * (M_PI / 180.0F);

        return ::rack::math::Vec(
             radius * ::std::cos(theta),
            -radius * ::std::sin(theta)
        );
    }

    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedRoundKnobPanelWidget::DrawArgs &args) override
    {
        const bool &prefersDarkPanels = this->getPrefersDarkPanels();
        const auto &size = this->getSize();

        const auto &minAngle = this->getMinAngle();
        const auto &maxAngle = this->getMaxAngle();
        const auto &leading = this->getLeading();

        // For debugging the bounding box of the widget
        const auto &bgColor = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgLight: ::StoneyDSP::StoneyVCV::Panels::bgDark;
        // const auto &borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
        const auto &textColor = prefersDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgPortDark : ::StoneyDSP::StoneyVCV::Panels::bgPortLight;
        const auto &fontSize = this->getFontSize();

        // Load font from cache
        ::std::shared_ptr<::rack::window::Font> font = APP->window->loadFont(
                ::rack::asset::system("res/fonts/DejaVuSans.ttf"
            )
        );

        // Don't draw text if font failed to load
        if (font) {
            // ::nvgBeginPath(args.vg);
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

        ::nvgBeginPath(args.vg);
        ::nvgLineCap(args.vg, NVG_ROUND);               // set rounded lines
        ::nvgLineJoin(args.vg, NVG_ROUND);              // set the line join to round corners

        float radius = (size.x * 0.5F) + leading;
        float rotationOffset = -M_PI / 2.0F;            // Knob Widgets are actually rotated -90 degress in rads

        ::nvgArc(args.vg,                               // Draw knob ring
            (size.x * 0.5F),                            // knob ring centre x
            (size.y * 0.5F),                            // knob ring center y
            radius,                                     // knob ring diameter
            (minAngle + rotationOffset),                // knob ring start position
            (maxAngle + rotationOffset),                // knob ring end position
            NVG_CW                                      // knob ring direction
        );

        // reset cursor
        ::nvgMoveTo(args.vg,
            size.x * 0.5F,
            size.y * 0.5F
        );

        /// Use the 'ranges' iterable to draw a list of lines on the knob panel,
        /// indicating useful positions such as the knob's minimum and maximum
        /// positions, the default position when double-clicked, the mid-point
        /// for bi-polar knobs, and snap points, if any.

        /// TODO:
        /// This widget should read the values - specified in radians - carried
        /// by the 'ranges' vector member. It purposely makes no attempts at
        /// creating equidistant spaces between given 'ranges', allowing for
        /// any arbitrary position(s) to be marked out on the knob panel.
        /// If some spacing scheme is required, calculate that on the outside
        /// after instanstating this class, and pass the results as an iterable
        /// to a `setRanges()` method - be aware that the method re-allocates
        /// if your number of ranges is greater than the default, or previously
        /// - specified, number of ranges, since the container type is dynamic.

        ::rack::math::Vec ranges [] = {
            // rangeStart, rangeEnd
            this->radiusToXY(radius, this->radiansToDegrees(this->minAngle - rotationOffset)),
            // this->radiusToXY(radius, 0.0F),
            // this->radiusToXY(radius, 45.0F),
            // this->radiusToXY(radius, 90.0F),
            // this->radiusToXY(radius, 180.0F),
            // this->radiusToXY(radius, 270.0F),
            this->radiusToXY(radius, this->radiansToDegrees(this->maxAngle - rotationOffset))
        };

        // Draw ranges as lines from the knob centre-point to the outer radius (includes leading)
        for(const auto &range : ranges) {
            ::nvgLineTo(args.vg,
                (size.x * 0.5F) + range.x,
                (size.y * 0.5F) + range.y
            );
            ::nvgMoveTo(args.vg,
                size.x * 0.5F,
                size.y * 0.5F
            );
        }

        // Draw ranges as lines
        ::nvgStrokeWidth(args.vg, (5.0F / 6.0F));
        ::nvgStrokeColor(args.vg, bgColor);
        ::nvgStroke(args.vg);
        ::nvgClosePath(args.vg);

        return ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::draw(args);
    }

    //==========================================================================

    virtual void setMinAngle(const float &newMinAngle)
    {
        this->minAngle = newMinAngle;
    }

    virtual const float &getMinAngle() const noexcept
    {
        return this->minAngle;
    }

    //==========================================================================

    virtual void setMaxAngle(const float &newMaxAngle)
    {
        this->maxAngle = newMaxAngle;
    }

    virtual const float &getMaxAngle() const noexcept
    {
        return this->maxAngle;
    }

    //==========================================================================

    virtual void setLeading(const float &newLeading)
    {
        this->leading = newLeading;
    }

    virtual const float &getLeading() const noexcept
    {
        return this->leading;
    }

    //==========================================================================

protected:

    //==========================================================================

    float minAngle = (0.0F - (5.0F / 6.0F)) * M_PI;     // -0.8333... * pi
    float maxAngle = (5.0F / 6.0F) * M_PI;              // +0.8333... * pi
    float leading = (4.0F);

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
		this->minAngle = (0.0F - (5.0F / 6.0F)) * M_PI; // -0.83 * pi
		this->maxAngle = (5.0F / 6.0F) * M_PI;          //  0.83 * pi

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
