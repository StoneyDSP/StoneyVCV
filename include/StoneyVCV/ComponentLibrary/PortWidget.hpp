/*******************************************************************************
 * @file include/StoneyVCV/ComponentLibrary/PortWidget.hpp
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

#define STONEYVCV_COMPONENTLIBRARY_PORTWIDGET_HPP_INCLUDED 1

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
 * @brief The `ThemedPortWidgetPanel` struct.
 *
 * Provides a panel background to the `ThemedPortWidget` struct.
 *
 */
struct ThemedPortWidgetPanel : virtual ::rack::widget::TransparentWidget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::rack::widget::TransparentWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Constructs a new `ThemedPortWidgetPanel` object.
     *
     */
    ThemedPortWidgetPanel();

    virtual ~ThemedPortWidgetPanel();

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     * Calls `::rack::widget::Widget::step()` internally.
     *
     */
    virtual void step() override;

    /**
     * @brief Renders to the NanoVG context.
     * Calls `::rack::widget::Widget::draw(args)` internally.
     *
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel::DrawArgs &args) override;

    //==========================================================================

    ::std::string labelText;

    /**
     * @brief Set whether the parent is an input or an output port.
     *
     */
    bool isOutput;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedPortWidgetPanel)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedPortWidgetPanel)
};

//==============================================================================

/**
 * @brief The `ThemedPortWidget` struct.
 *
 */
struct ThemedPortWidget : virtual ::rack::app::ThemedSvgPort
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::rack::app::ThemedSvgPort::DrawArgs;

    ThemedPortWidget();

    virtual ~ThemedPortWidget();

    //==========================================================================

    virtual void step() override;

    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidget::DrawArgs &args) override;

    //==========================================================================

    bool isOutput;

    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortWidgetPanel* panel;

    //==========================================================================

private:

    //==========================================================================

    ::rack::FramebufferWidget* fb;

    bool lastPrefersDarkPanels;

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedPortWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedPortWidget)
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
