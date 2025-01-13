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
    }

// // Knob

//     /** Drag horizontally instead of vertically. */
// 	bool horizontal = false;
// 	/** Enables per-sample value smoothing while dragging.
// 	Alternatively, use ParamQuantity::smoothEnabled.
// 	*/
// 	bool smooth = true;
// 	/** Enables value snapping to the nearest integer.
// 	Alternatively, use ParamQuantity::snapEnabled.
// 	*/
// 	bool snap = false;
// 	/** Multiplier for mouse movement to adjust knob value */
// 	float speed = 1.f;
// 	/** Force dragging to linear, e.g. for sliders. */
// 	bool forceLinear = false;
// 	/** Angles in radians.
// 	For drawing and handling the global radial knob setting.
// 	*/
// 	float minAngle = -M_PI;
// 	float maxAngle = M_PI;

// // SVGKnob

//     /** */
//     ::rack::widget::FramebufferWidget* fb = NULL;
//     /** */
// 	::rack::CircularShadow* shadow = NULL;
//     /** */
// 	::rack::widget::TransformWidget* tw = NULL;
//     /** */
// 	::rack::widget::SvgWidget* sw = NULL;

// // RoundKnob

    /** */
	::rack::widget::SvgWidget* bg = NULL;

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundKnob)
};

struct RoundBlackKnob : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::RoundKnob
{
public:

	RoundBlackKnob()
    {
		this->setSvg(
            ::rack::Svg::load(
                ::rack::asset::system("res/ComponentLibrary/RoundBlackKnob.svg")
            )
        );
		this->bg->setSvg(
            ::rack::Svg::load(
                ::rack::asset::system("res/ComponentLibrary/RoundBlackKnob_bg.svg")
            )
        );
	}

    ~RoundBlackKnob() {
        assert(!this->parent);
    }

private:

    STONEYDSP_DECLARE_NON_COPYABLE(RoundBlackKnob)
    STONEYDSP_DECLARE_NON_MOVEABLE(RoundBlackKnob)
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
