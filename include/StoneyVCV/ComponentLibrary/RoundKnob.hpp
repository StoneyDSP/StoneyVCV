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

        this->clearChildren();
    }

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
