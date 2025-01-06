/*******************************************************************************
 * @file include/StoneyVCV/ComponentLibrary/PanelWidget.hpp
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

#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

//==============================================================================

#include <string>
#include <array>

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
 * @brief The `PanelLinesWidget` struct.
 * Draws 4 lines around the inner edges of the module.
 * Does not ssend or respond to events.
 *
 */
struct PanelLinesWidget : virtual ::rack::widget::TransparentWidget
{

    //==========================================================================

public:

    using DrawArgs = ::rack::widget::TransparentWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `PanelLinesWidget` object.
     *
     */
    PanelLinesWidget() = default;

    /**
     * @brief Draws a set of lines for spacing to the widget's NanoVG context.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::DrawArgs &args) override;

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(PanelLinesWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(PanelLinesWidget)
};

//==============================================================================

/**
 * @brief The `ThemedPanelWidget` struct.
 *
 */
struct ThemedPanelWidget : virtual ::rack::widget::Widget
{

    //==========================================================================

public:

    using DrawArgs = ::rack::widget::Widget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `ThemedPanelWidget` object.
     *
     */
    ThemedPanelWidget();

    /**
     * @brief Destroys the `ThemedPanelWidget` object.
     *
     */
    virtual ~ThemedPanelWidget();

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws a themed background to the widget's NanoVG context.
     * Calls the superclass's draw(args) to recurse to children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::DrawArgs &args) override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget *fb;

    // /**
    //  * @brief
    //  *
    //  */
    // const ::std::array<::rack::math::Vec, 4> screwsPositions;

    // /**
    //  * @brief
    //  *
    //  */
    // const ::std::array<::rack::componentlibrary::ThemedScrew *, 4> screws;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget *panelLines;

    /**
     * @brief
     *
     */
    ::rack::app::PanelBorder *panelBorder;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedPanelWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedPanelWidget)
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
