/*******************************************************************************
 * @file include/StoneyVCV/ComponentLibrary/Widget.hpp
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

#define STONEYVCV_COMPONENTLIBRARY_PANELWIDGET_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

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
 * The `Widget` struct.
 *
 * A node in the 2D [scene graph](https://en.wikipedia.org/wiki/Scene_graph).
 * The bounding box of a Widget is a rectangle specified by `box` relative to
 * their parent.
 *
 * The appearance is defined by overriding `draw()`, and the behavior is defined
 * by overriding `step()` and `on*()` event handlers.
 *
 */
struct Widget : virtual ::rack::widget::Widget
{
    //==========================================================================

public:

    using DrawArgs = ::rack::widget::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `Widget` object.
     *
     */
    Widget();

    /**
     * @brief Destroys the `Widget` object.
     *
     */
    virtual ~Widget();

    //==========================================================================

    /**
     * @brief Advances the widget by one frame.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws the widget to the NanoVG context.
     * Calls the superclass's draw(args) to recurse to children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::DrawArgs &args) override;

    //==========================================================================

    template <class TWidget>
    friend TWidget* ::rack::createWidget(::rack::math::Vec pos);

    template <class TWidget>
    friend TWidget* ::rack::createWidgetCentered(::rack::math::Vec pos);

    template <class TWidget>
    friend TWidget *::StoneyDSP::StoneyVCV::createWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size);

    template <class TWidget>
    friend TWidget* ::StoneyDSP::StoneyVCV::createWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size);

private:

    //==========================================================================

    /**
     * @brief Position relative to parent and size of widget.
     *
     */
    ::rack::math::Rect box;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(Widget)
    STONEYDSP_DECLARE_NON_MOVEABLE(Widget)
};

//==============================================================================

/**
 * @brief The `ThemedWidget` struct.
 *
 */
struct ThemedWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget
{

    //==========================================================================

public:

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `ThemedWidget` object.
     *
     */
    ThemedWidget();

    /**
     * @brief Destroys the `ThemedWidget` object.
     *
     */
    virtual ~ThemedWidget();

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws a themed background color to the widget's NanoVG context.
     * Calls the superclass's draw(args) to recurse to children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args) override;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedWidget)
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
