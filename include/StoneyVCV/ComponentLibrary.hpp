/*******************************************************************************
 * @file include/StoneyVCV/ComponentLibrary.hpp
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

#define STONEYVCV_COMPONENTLIBRARY_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================

#include <StoneyVCV/version.hpp>

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

/**
 * @brief The `Panels` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 * @version @STONEYVCV_VERSION@
 *
 */
namespace Panels
{
/** @addtogroup Panels
 *  @{
 */

//==============================================================================
const extern ::NVGcolor bgBlack;
const extern ::NVGcolor bgWhite;
const extern ::NVGcolor borderColor;
const extern ::NVGcolor bgPortWhite;
const extern ::NVGcolor bgPortBlack;
const extern ::NVGcolor bgGradientBlackS0;
const extern ::NVGcolor bgGradientBlackS1;
const extern ::NVGcolor bgGradientWhiteS0;
const extern ::NVGcolor bgGradientWhiteS1;
const extern ::StoneyDSP::float_t MIN_WIDTH;
const extern ::StoneyDSP::float_t MIN_HEIGHT;
extern void addScrewsToWidget(::rack::widget::Widget* widget);

//==============================================================================

  /// @} group Panels
} // namespace Panels

/**
 * @brief The `ComponentLibrary` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 * @version @STONEYVCV_VERSION@
 *
 */
namespace ComponentLibrary
{
/** @addtogroup ComponentLibrary
 *  @{
 */

//==============================================================================

/**
 * @brief The `ThemedPortWidget` struct.
 *
 * Provides a panel background to the `ThemedPortWidget` struct.
 *
 */
struct ThemedPortWidgetPanel : virtual ::rack::widget::Widget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::rack::widget::Widget::DrawArgs;

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

/**
 * @brief The `ThemedWidget` struct.
 *
 */
struct ThemedWidget : virtual ::rack::widget::Widget
{

    //==========================================================================

public:

    using DrawArgs = ::rack::widget::Widget::DrawArgs;

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
     *
     * @param args
     */
    void drawThemedBg(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args);

    /**
     * @brief Draws a set of lines for spacing to the widget's NanoVG context.
     *
     * @param args
     */
    void drawDividerLines(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args);

    /**
     * @brief Draws the widget to the NanoVG context.
     * Calls the superclass's draw(args) to recurse to children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args) override;

    //==========================================================================

private:

    //==========================================================================

    /**
     * @brief
     *
     */
    ::rack::FramebufferWidget *fb;

    /**
     * @brief
     *
     */
    ::rack::app::PanelBorder *panelBorder;

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

#endif // STONEYVCV_BUILD_PLUGIN

//==============================================================================
