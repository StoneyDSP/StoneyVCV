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

#define STONEYVCV_COMPONENTLIBRARY_PARAMWIDGET_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/Widget.hpp>

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
 * @brief The `ThemedParamPanelWidget` struct.
 *
 * Provides a themed panel background which can fit around instances of the
 * `ThemedParamWidget` struct on a Module's panel.
 *
 * Carries a `labelText` member for writing a text label corresponding to the
 * port's purpose.
 *
 */
struct ThemedParamPanelWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Constructs a new `ThemedParamPanelWidget` object.
     *
     */
    ThemedParamPanelWidget();

    /**
     * @brief Destroys the `ThemedParamPanelWidget` object.
     *
     */
    virtual ~ThemedParamPanelWidget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the `ThemedParamPanelWidget` by one frame.
     * Calls the superclass's `step()` method internally to recurse the
     * children.
     *
     */
    virtual void step() override;

    /**
     * @brief Renders the `ThemedParamPanelWidget` to the NanoVG context.
     * Calls the superclass's `draw(args)` method internally to recurse the
     * children.
     *
     * @param args
     *
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::DrawArgs &args) override;

    //==========================================================================

    virtual const bool &getPrefersDarkPanels() const noexcept;

    //==========================================================================

    virtual void setFontSize(const float &newFontSize) noexcept;

    virtual const float &getFontSize() const noexcept;

    //==========================================================================

    virtual void setLabelText(const ::std::string &newLabelText) noexcept;

    virtual const ::std::string &getLabelText() const noexcept;

    //==========================================================================

    enum Type {
		KNOB,
		SLIDER,
        BUTTON,
        SWITCH
	};

    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::Type type = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::Type::KNOB;

protected:

    //==========================================================================

    float fontSize = 8.0F;

    ::std::string labelText = "";

    //==========================================================================

private:

    //==========================================================================

    /**
     * `{&::rack::settings::preferDarkPanels}`
     */
    const bool *prefersDarkPanelsPtr = NULL;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedParamPanelWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedParamPanelWidget)
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
