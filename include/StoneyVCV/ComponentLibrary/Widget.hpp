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
     * @brief Construct a new `Widget` object with its' position and size set
     * using a `rack::math::Rect`.
     *
     */
    Widget(::rack::math::Rect newBox);

    /**
     * @brief Destroys the `Widget` object.
     *
     */
    virtual ~Widget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the `Widget` by one frame.
     * Calls the superclass's `step()` to recurse to children.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws the `Widget` to the NanoVG context.
     * Calls the superclass's `draw(args)` to recurse to children.
     *
     * @param args
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::DrawArgs &args) override;

    //==========================================================================

    struct PixelRatioChangeEvent : ::rack::widget::Widget::BaseEvent {
        float newPixelRatio = APP->window->pixelRatio;
    };

    /**
     * Called after the `App->window->pixelRatio` setting is changed.
     * Sub-classes can override this to receive callbacks when the event is
     * dispatched (from the `Widget::step()` method).
     *
     * @param e
     *
     */
    virtual void onPixelRatioChange(const PixelRatioChangeEvent& e) {
        ::StoneyDSP::ignoreUnused(e);
    };

    /**
     * @brief
     *
     */
    const float &getPixelRatio() const noexcept;

    //==========================================================================

    template <class TWidget>
    friend TWidget *::rack::createWidget(::rack::math::Vec pos);

    template <class TWidget>
    friend TWidget *::rack::createWidgetCentered(::rack::math::Vec pos);

    template <class TWidget>
    friend TWidget *::StoneyDSP::StoneyVCV::createWidget(::rack::math::Vec pos);

    template <class TWidget>
    friend TWidget *::StoneyDSP::StoneyVCV::createWidgetCentered(::rack::math::Vec pos);

    template <class TWidget>
    friend TWidget *::StoneyDSP::StoneyVCV::createWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size);

    template <class TWidget>
    friend TWidget *::StoneyDSP::StoneyVCV::createWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size);

protected:

    //==========================================================================

    /**
     * @brief Position relative to parent and size of `Widget`.
     *
     */
    ::rack::math::Rect box = ::rack::math::Rect(::rack::math::Vec(), ::rack::math::Vec(INFINITY, INFINITY));

    /**
     * Automatically set when `Widget` is added as a child to another `Widget`.
     *
     */
	::rack::Widget *parent = NULL;

	::std::list<::rack::Widget *> children;

	/**
     * Disables rendering but allow stepping.
     * Use `isVisible()`, `setVisible()`, `show()`, or `hide()` instead of using
     * this variable directly.
	 *
     */
	bool visible = true;

    /**
     * If set to true, parent will delete Widget in the next `step()`.
     * Use `requestDelete()` instead of using this variable directly.
     *
	 */
	bool requestedDelete = false;

    //==========================================================================

    /**
     * @brief
     *
     */
    float lastPixelRatio = {APP->window->pixelRatio};

    /**
     * @brief
     *
     */
    const float *pixelRatioPtr = NULL;

    //==========================================================================

private:

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
     * @brief Construct a new `ThemedWidget` object with its' position and size
     * set using a `rack::math::Rect`.
     *
     */
    ThemedWidget(::rack::math::Rect newBox);

    /**
     * @brief Destroys the `ThemedWidget` object.
     *
     */
    virtual ~ThemedWidget() noexcept;

    //==========================================================================

    /**
     * @brief Advances the module by one frame.
     * Calls the superclass's `step()` to recurse the children.
     *
     */
    virtual void step() override;

    /**
     * @brief Draws a themed background color to the widget's NanoVG context.
     * Calls the superclass's `draw(args)` to recurse to children.
     *
     * @param args
     *
     */
    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedWidget::DrawArgs &args) override;

    const bool &getPrefersDarkPanels() const noexcept;

    //==========================================================================

    /**
     * Occurs after the `prefersDarkPanels` setting is changed.
     * The concept of a "dark" or "light" panel is defined by the type of Widget.
	 *
     */
	struct PrefersDarkPanelsChangeEvent : ::rack::widget::Widget::BaseEvent {
        bool newPrefersDarkPanels = {::rack::settings::preferDarkPanels};
    };

    /**
     * Called after the `prefersDarkPanels` setting is changed.
     * Sub-classes can override this to receive callbacks when the event is
     * dispatched (from the `ThemedWidget::step()` method).
     *
     * @param e
     *
     */
	virtual void onPrefersDarkPanelsChange(const PrefersDarkPanelsChangeEvent& e)
    {
        if(this->lastPrefersDarkPanels != e.newPrefersDarkPanels)
            this->lastPrefersDarkPanels = e.newPrefersDarkPanels;
    }

    //==========================================================================

    STONEYVCV_DECLARE_WIDGET_FACTORY_FUNCTIONS(ThemedWidget)

    //==========================================================================

protected:

    //==========================================================================

    bool lastPrefersDarkPanels = {::rack::settings::preferDarkPanels};

    //==========================================================================

private:

    //==========================================================================

    /**
     * `{&::rack::settings::preferDarkPanels};`
     *
     */
    const bool *prefersDarkPanelsPtr = NULL;

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(ThemedWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(ThemedWidget)
};

//==============================================================================

struct FramebufferWidget : virtual ::rack::widget::FramebufferWidget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::rack::widget::FramebufferWidget::DrawArgs;

    //==========================================================================

    FramebufferWidget();

    FramebufferWidget(::rack::math::Rect newBox);

    virtual ~FramebufferWidget() noexcept;

    //==========================================================================

    virtual void step() override;

    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::FramebufferWidget::DrawArgs &args) override;

    //==========================================================================

    STONEYVCV_DECLARE_WIDGET_FACTORY_FUNCTIONS(FramebufferWidget)

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(FramebufferWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(FramebufferWidget)
};

//==============================================================================

struct TransparentWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::DrawArgs;

    //==========================================================================

    TransparentWidget();

    TransparentWidget(::rack::math::Rect newBox);

    virtual ~TransparentWidget() noexcept;

    //==========================================================================

    STONEYVCV_DECLARE_WIDGET_FACTORY_FUNCTIONS(TransparentWidget)

    //==========================================================================

private:

    //==========================================================================

	// Override behavior to do nothing instead

    virtual void onHover(const HoverEvent& e) override {}
	virtual void onButton(const ButtonEvent& e) override {}
	virtual void onHoverKey(const HoverKeyEvent& e) override {}
	virtual void onHoverText(const HoverTextEvent& e) override {}
	virtual void onHoverScroll(const HoverScrollEvent& e) override {}
	virtual void onDragHover(const DragHoverEvent& e) override {}
	virtual void onPathDrop(const PathDropEvent& e) override {}

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(TransparentWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(TransparentWidget)
};

//==============================================================================

struct OpaqueWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget
{

    //==========================================================================

public:

    //==========================================================================

    OpaqueWidget();

    OpaqueWidget(::rack::math::Rect newBox);

    virtual ~OpaqueWidget() noexcept;

    //==========================================================================

    virtual void onHover(const HoverEvent& e) override
    {
		::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::onHover(e);
		e.stopPropagating();
		// Consume if not consumed by child
		if (!e.isConsumed())
			e.consume(this);
	}

	virtual void onButton(const ButtonEvent& e) override
    {
		::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::onButton(e);
		e.stopPropagating();
		if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
			// Consume if not consumed by child
			if (!e.isConsumed())
				e.consume(this);
		}
	}

	virtual void onHoverKey(const HoverKeyEvent& e) override
    {
		::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::onHoverKey(e);
		e.stopPropagating();
	}

	virtual void onHoverText(const HoverTextEvent& e) override
    {
		::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::onHoverText(e);
		e.stopPropagating();
	}

	virtual void onHoverScroll(const HoverScrollEvent& e) override
    {
		::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::onHoverScroll(e);
		e.stopPropagating();
	}

	virtual void onDragHover(const DragHoverEvent& e) override
    {
		::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::onDragHover(e);
		e.stopPropagating();
		// Consume if not consumed by child
		if (!e.isConsumed())
            e.consume(this);
	}

	virtual void onPathDrop(const PathDropEvent& e) override
    {
		::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::onPathDrop(e);
		e.stopPropagating();
	}

    //==========================================================================

    STONEYVCV_DECLARE_WIDGET_FACTORY_FUNCTIONS(OpaqueWidget)

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(OpaqueWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(OpaqueWidget)
};

//==============================================================================

struct SvgWidget : virtual ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget
{

    //==========================================================================

public:

    //==========================================================================

    using DrawArgs = ::StoneyDSP::StoneyVCV::ComponentLibrary::Widget::DrawArgs;

    //==========================================================================

    SvgWidget();

    SvgWidget(::rack::math::Rect newBox);

    virtual ~SvgWidget() noexcept;

    //==========================================================================

    void wrap() noexcept;

    void setSvg(::std::shared_ptr<::rack::window::Svg> newSvg);

    virtual void draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::SvgWidget::DrawArgs &args) override;

    //==========================================================================

    STONEYVCV_DECLARE_WIDGET_FACTORY_FUNCTIONS(SvgWidget)

    //==========================================================================

protected:

    //==========================================================================

    ::std::shared_ptr<::rack::window::Svg> svg;

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(SvgWidget)
    STONEYDSP_DECLARE_NON_MOVEABLE(SvgWidget)
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
