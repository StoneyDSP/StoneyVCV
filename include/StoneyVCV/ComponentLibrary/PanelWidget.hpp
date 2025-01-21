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

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/Widget.hpp>
#include <StoneyVCV/ComponentLibrary/PortWidget.hpp>
#include <StoneyVCV/ComponentLibrary/ParamWidget.hpp>
#include <StoneyVCV/ComponentLibrary/RoundKnobWidget.hpp>

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

namespace ComponentLibrary {
struct ThemedPanelWidget; // forward-declaration
}

/**
 * @brief
 *
 * @tparam
 *
 * @param
 *
 * @returns
 */
template <class TPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget>
inline TPanelWidget *createPanelWidget(::rack::math::Rect box);

//==============================================================================

namespace ComponentLibrary
{
/** @addtogroup ComponentLibrary
 *  @{
 */

//==============================================================================

/**
 * @brief The `PaneBorderWidget` struct.
 * Draws 4 lines around the outer edges of the module.
 * Does not send or respond to events.
 *
 */
struct PanelBorderWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget
{

    //==========================================================================

public:

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Constructs a new `PanelBorderWidget` object.
     *
     */
    PanelBorderWidget();

    /**
     * @brief Construct a new `PanelBorderWidget` object with its' position and
     * size set using a `rack::math::Rect`.
     *
     */
    PanelBorderWidget(::rack::math::Rect newBox);

    /**
     * @brief Destroys the `PanelBorderWidget` object.
     *
     */
    virtual ~PanelBorderWidget() noexcept;

    //==========================================================================

    /**
     * @brief Draws a set of lines for spacing to the widget's NanoVG context.
     *
     * @param args
     *
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget::DrawArgs &args) override;

    //==========================================================================

    const ::NVGcolor &getBorderColor() const noexcept;

    //==========================================================================

private:

    //==========================================================================

    const ::NVGcolor &borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(PanelBorderWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(PanelBorderWidget)
};

//==============================================================================

/**
 * @brief The `PanelLinesWidget` struct.
 * Draws 4 lines around the inner edges of the module.
 * Does not send or respond to events.
 *
 */
struct PanelLinesWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget
{

    //==========================================================================

public:

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Constructs a new `PanelLinesWidget` object.
     *
     */
    PanelLinesWidget();

    /**
     * @brief Construct a new `PanelLinesWidget` object with its' position and
     * size set using a `rack::math::Rect`.
     *
     */
    PanelLinesWidget(::rack::math::Rect newBox);

    /**
     * @brief Destroys the `PanelLinesWidget` object.
     *
     */
    virtual ~PanelLinesWidget() noexcept;

    //==========================================================================

    /**
     * @brief Draws a set of lines for spacing to the widget's NanoVG context.
     *
     * @param args
     *
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget::DrawArgs &args) override;

    //==========================================================================

    const ::NVGcolor &getBorderColor() const noexcept;

    //==========================================================================

private:

    //==========================================================================

    const ::NVGcolor &borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(PanelLinesWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(PanelLinesWidget)
};

//==============================================================================

/**
 * @brief The `ThemedPanelWidget` struct.
 *
 */
struct ThemedPanelWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget
{

    //==========================================================================

public:

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs;

    //==========================================================================

    /**
     * @brief Construct a new `ThemedPanelWidget` object with its' position and
     * size set using a `rack::math::Rect`.
     *
     */
    ThemedPanelWidget(::rack::math::Rect newBox);

    /**
     * @brief Destroys the `ThemedPanelWidget` object.
     *
     */
    virtual ~ThemedPanelWidget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     * Calls the superclass's `step()` to recurse to children.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws a themed background to the widget's NanoVG context.
     * Calls the superclass's `draw(args)` to recurse to children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::DrawArgs &args) override;

    //==========================================================================

    /**
     * Called after the `prefersDarkPanels` setting is changed.
     *
     * @param e
     *
     */
	virtual void onPrefersDarkPanelsChange(const PrefersDarkPanelsChangeEvent& e) override;

    //==========================================================================

    const ::std::size_t &getNumScrews() const noexcept;

    void setNumScrews(const ::std::size_t &newNumScrews);

    //==========================================================================

    const ::std::size_t &getNumPorts() const noexcept;

    void setNumPorts(const ::std::size_t &newNumPorts);

    //==========================================================================

    const ::std::size_t &getNumParams() const noexcept;

    void setNumParams(const ::std::size_t &newNumParams);

    //==========================================================================

    const ::std::size_t &getNumLights() const noexcept;

    void setNumLights(const ::std::size_t &newNumLights);

    //==========================================================================

    ::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget &getFrameBufferWidget() noexcept;

    //==========================================================================

    ::std::vector<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget *> &getPortPanelWidgets() noexcept;

    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget &getPortPanelWidget(const ::std::size_t &i) noexcept(false);

    //==========================================================================

    ::std::vector<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget *> &getParamPanelWidgets() noexcept;

    ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget &getParamPanelWidget(const ::std::size_t &i) noexcept(false);

    //==========================================================================

    template <class TPanelWidget>
    friend TPanelWidget *::StoneyDSP::StoneyVCV::createPanelWidget(::rack::math::Rect box);

    //==========================================================================

protected:

    //==========================================================================

    template <typename TParamPanelWidget>
    inline void addParamPanelWidget(::rack::math::Vec pos);

    template <typename TParamPanelWidget>
    inline void addParamPanelWidgetCentered(::rack::math::Vec pos);

    template <typename TParamPanelWidget>
    inline void addParamPanelWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size);

    template <typename TParamPanelWidget>
    inline void addParamPanelWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size);

    template <typename TPortPanelWidget>
    inline void addPortPanelWidget(::rack::math::Vec pos);

    template <typename TPortPanelWidget>
    inline void addPortPanelWidgetCentered(::rack::math::Vec pos);

    template <typename TPortPanelWidget>
    inline void addPortPanelWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size);

    template <typename TPortPanelWidget>
    inline void addPortPanelWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size);

    //==========================================================================

    ::std::vector<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget *> paramPanelWidgets = { NULL };


    ::std::vector<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget *> portPanelWidgets = { NULL };

    //==========================================================================

    ::std::size_t numScrews = 0U;

    ::std::size_t numParams = 0U;

    ::std::size_t numPorts = 0U;

    ::std::size_t numLights = 0U;

    //==========================================================================

    /**
     * @brief The "head" Framebuffer Widget of the PanelWidget.
     *
     * Ideally, sub-classes of this `ThemedPanelWidget` class will initialize
     * any sub-widgets, such as panels and text labels for ports and parameters,
     * and then place them all into this `FramebufferWidget` instance, where
     * the owner can manage `Dirty` events, and so forth, affecting the whole
     * panel.
     *
     * This prevents the need for tracking lots of different Framebuffer Widgets
     * and event sources/sinks for the representation of one overall Panel.
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget *fb = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelBorderWidget *panelBorder = NULL;

    /**
     * @brief
     *
     */
    ::StoneyDSP::StoneyVCV::ComponentLibrary::PanelLinesWidget *panelLines = NULL;

    //==========================================================================

    /**
     * @brief
     *
     */
    ::std::array<::rack::math::Vec, 4> screwsPositions = { ::rack::math::Vec() };

    /**
     * @brief
     *
     */
    ::std::array<::rack::componentlibrary::ThemedScrew *, 4> screws = { NULL };

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedPanelWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedPanelWidget)
    STONEYDSP_DECLARE_NON_CONSTRUCTABLE(ThemedPanelWidget)
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

template <class TPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget>
inline TPanelWidget *::StoneyDSP::StoneyVCV::createPanelWidget(::rack::math::Rect box)
{
    static_assert(::std::is_base_of<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget, TPanelWidget>::value, "TPanelWidget must be derived from StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget");

    TPanelWidget *o = new TPanelWidget(box);
    return o;
}

// Explicit instantiation to ensure the definition is visible to the linker
template ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget *::StoneyDSP::StoneyVCV::createPanelWidget<::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget>(::rack::math::Rect box);

//==============================================================================

/**
 * @brief Adds a new `ThemedParamPanelWidget` to this `ThemedPanelWidget`,
 * with its' top-left at a position.
 *
 * Accesses the `paramPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidget<TParamPanelWidget>(pos)`.
 *
 * @tparam `ThemedParamPanelWidget` may be substituted for a sub-class of
 * `ThemedParamPanelWidget`.
 *
 * @param pos
 */
template <typename TParamPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addParamPanelWidget(::rack::math::Vec pos)
{
    this->paramPanelWidgets.emplace_back<TParamPanelWidget *>(
        dynamic_cast<TParamPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidget<TParamPanelWidget>(pos)
        )
    );
}

/**
 * @brief Adds a new `ThemedParamPanelWidget` to this `ThemedPanelWidget`,
 * with its' center at a position.
 *
 * Accesses the `paramPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidgetCentered<TParamPanelWidget>(pos)`.
 *
 * @tparam `ThemedParamPanelWidget` may be substituted for a sub-class of
 * `ThemedParamPanelWidget`.
 *
 * @param pos
 */
template <typename TParamPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addParamPanelWidgetCentered(::rack::math::Vec pos)
{
    this->paramPanelWidgets.emplace_back<TParamPanelWidget *>(
        dynamic_cast<TParamPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidgetCentered<TParamPanelWidget>(pos)
        )
    );
}

/**
 * @brief Adds a new `ThemedParamPanelWidget` to this `ThemedPanelWidget`,
 * with its' top-left at a position and its' size set.
 *
 * Accesses the `paramPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidgetSized<TParamPanelWidget>(pos, size)`.
 *
 * @tparam `ThemedParamPanelWidget` may be substituted for a sub-class of
 * `ThemedParamPanelWidget`.
 *
 * @param pos
 * @param size
 */
template <typename TParamPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addParamPanelWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    this->paramPanelWidgets.emplace_back<TParamPanelWidget *>(
        dynamic_cast<TParamPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidgetSized<TParamPanelWidget>(pos, size)
        )
    );
}

/**
 * @brief Adds a new `ThemedParamPanelWidget` to this `ThemedPanelWidget`,
 * with its' center at a position and its' size set.
 *
 * Accesses the `paramPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidgetSized<TParamPanelWidget>(pos, size)`.
 *
 * @tparam `ThemedParamPanelWidget` may be substituted for a sub-class of
 * `ThemedParamPanelWidget`.
 *
 * @param pos
 * @param size
 */
template <typename TParamPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addParamPanelWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    this->paramPanelWidgets.emplace_back<TParamPanelWidget *>(
        dynamic_cast<TParamPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidgetCenteredSized<TParamPanelWidget>(pos, size)
        )
    );
}

/**
 * @brief Adds a new `ThemedPortPanelWidget` to this `ThemedPanelWidget`,
 * with its' top-left at a position.
 *
 * Accesses the `portPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidget<TPortPanelWidget>(pos)`.
 *
 * @tparam `ThemedPortPanelWidget` may be substituted for a sub-class of
 * `ThemedPortPanelWidget`.
 *
 * @param pos
 */
template <typename TPortPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addPortPanelWidget(::rack::math::Vec pos)
{
    this->portPanelWidgets.emplace_back<TPortPanelWidget *>(
        dynamic_cast<TPortPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidget<TPortPanelWidget>(pos)
        )
    );
}

/**
 * @brief Adds a new `ThemedPortPanelWidget` to this `ThemedPanelWidget`,
 * with its' center at a position.
 *
 * Accesses the `portPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidgetCentered<TPortPanelWidget>(pos)`.
 *
 * @tparam `ThemedPortPanelWidget` may be substituted for a sub-class of
 * `ThemedPortPanelWidget`.
 *
 * @param pos
 */
template <typename TPortPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addPortPanelWidgetCentered(::rack::math::Vec pos)
{
    this->portPanelWidgets.emplace_back<TPortPanelWidget *>(
        dynamic_cast<TPortPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidgetCentered<TPortPanelWidget>(pos)
        )
    );
}

/**
 * @brief Adds a new `ThemedPortPanelWidget` to this `ThemedPanelWidget`,
 * with its' top-left at a position and its' size set.
 *
 * Accesses the `portPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidgetSized<TPortPanelWidget>(pos, size)`.
 *
 * @tparam `ThemedPortPanelWidget` may be substituted for a sub-class of
 * `ThemedPortPanelWidget`.
 *
 * @param pos
 * @param size
 */
template <typename TPortPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addPortPanelWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    this->portPanelWidgets.emplace_back<TPortPanelWidget *>(
        dynamic_cast<TPortPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidgetSized<TPortPanelWidget>(pos, size)
        )
    );
}

/**
 * @brief Adds a new `ThemedPortPanelWidget` to this `ThemedPanelWidget`,
 * with its' center at a position and its' size set.
 *
 * Accesses the `portPanelWidgets` vector and calls it's `emplace_back()`
 * method using `::StoneyDSP::StoneyVCV::createWidgetSized<TPortPanelWidget>(pos, size)`.
 *
 * @tparam `ThemedPortPanelWidget` may be substituted for a sub-class of
 * `ThemedPortPanelWidget`.
 *
 * @param pos
 * @param size
 */
template <typename TPortPanelWidget = ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPortPanelWidget>
inline void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedPanelWidget::addPortPanelWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    this->portPanelWidgets.emplace_back<TPortPanelWidget *>(
        dynamic_cast<TPortPanelWidget *>(
            ::StoneyDSP::StoneyVCV::createWidgetCenteredSized<TPortPanelWidget>(pos, size)
        )
    );
}

//==============================================================================

#endif // STONEYVCV_BUILD_COMPONENTLIBRARY

//==============================================================================
