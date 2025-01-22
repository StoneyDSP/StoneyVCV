/*******************************************************************************
 * @file include/StoneyVCV.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief @PROJECT_DESCRIPTION@
 * @version @STONEYVCV_VERSION@
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

#define STONEYVCV_HPP_INCLUDED 1

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

//==============================================================================

#ifdef STONEYDSP_DEBUG
 #include <iostream>
 #define DBG(msg, ...) do { ::std::cerr << std::string(msg, ##__VA_ARGS__) << std::endl; } while (0)
#else
 #define DBG(msg, ...) ::StoneyDSP::ignoreUnused(msg, ##__VA_ARGS__)
#endif

#ifdef STONEYDSP_DEBUG
 #define assert_message(condition, message) assert((condition) && (message))
#else
 #define assert_message(condition, message) ::StoneyDSP::ignoreUnused(condition, message)
#endif

// #if defined (STONEYDSP_DEBUG)
//  #include <iostream>
//  #define DBG(x, ...) do { x } while (false)
// #else
//  #define DBG(msg, ...) ::StoneyDSP::ignoreUnused(msg, ##__VA_ARGS__)
// #endif

// #if defined (STONEYDSP_DEBUG)
//  #include <iostream>
//  #define DBG(x, ...) DEBUG(x, ##__VA_ARGS__)
// #else
//  #define DBG(msg, ...) ::StoneyDSP::ignoreUnused(msg, ##__VA_ARGS__)
// #endif

//==============================================================================

/**
 * @brief The `StoneyDSP` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @PROJECT_VERSION@
 *
 */
namespace StoneyDSP {
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

/**
 * @brief The `StoneyVCV` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @STONEYVCV_VERSION@
 *
 */
namespace StoneyVCV
{
/** @addtogroup StoneyVCV
 *  @{
 */

//==============================================================================

namespace Tools {
/** @addtogroup Tools
 *  @{
 */

//==============================================================================

const extern ::StoneyDSP::float_t vMin;
const extern ::StoneyDSP::float_t vMax;
const extern ::StoneyDSP::float_t vNominal;
const extern ::StoneyDSP::float_t vBias;
const extern ::StoneyDSP::float_t vGround;
const extern ::StoneyDSP::float_t vFloor;

//==============================================================================

  /// @} group Tools
} // namespace Tools

//==============================================================================

// Declare an abstract base class with a pure virtual destructor.
// It's the simplest possible abstract class.
template <typename T>
struct Engine
{

    //==========================================================================

public:

    //==========================================================================

    Engine()
    {
        DBG("Constructing StoneyDSP::StoneyVCV::Engine");
    };

    virtual ~Engine() noexcept = 0;                                             // pure virtual

    //==========================================================================

    virtual void processSample(T* sample) = 0;                                  // pure virtual

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(Engine)
    STONEYDSP_DECLARE_NON_MOVEABLE(Engine)
    // STONEYDSP_PREVENT_HEAP_ALLOCATION
};

template <class T>
::StoneyDSP::StoneyVCV::Engine<T>::~Engine() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::Engine");
}

// Explicit instantiations to ensure the definition is visible to the linker...
template struct ::StoneyDSP::StoneyVCV::Engine<double>;
template struct ::StoneyDSP::StoneyVCV::Engine<float>;

//==============================================================================

/**
 * @brief Creates a `Widget` subclass with its top-left at a position.
 *
 * @param pos
 * @returns A `Widget` with its top-left at a position.
 *
 */
template <class TWidget = ::rack::widget::Widget>
inline TWidget *createWidget(::rack::math::Vec pos)
{
    static_assert(::std::is_base_of<::rack::widget::Widget, TWidget>::value, "TWidget must be derived from rack::widget::Widget");

	TWidget *o = new TWidget;
	o->box.pos = pos;
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::widget::Widget *::StoneyDSP::StoneyVCV::createWidget<::rack::widget::Widget>(::rack::math::Vec pos);

//==============================================================================

/**
 * @brief Creates a `Widget` subclass with its center at a position.
 *
 * @param pos
 * @returns A `Widget` with its center at a position.
 *
 */
template <class TWidget = ::rack::widget::Widget>
inline TWidget *createWidgetCentered(::rack::math::Vec pos)
{
	TWidget *o = ::StoneyDSP::StoneyVCV::createWidget<TWidget>(pos);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::widget::Widget *::StoneyDSP::StoneyVCV::createWidgetCentered<::rack::widget::Widget>(::rack::math::Vec pos);

//==============================================================================

/**
 * @brief Creates a `Widget` subclass with its top-left at a position and its
 * size set.
 *
 * @param pos
 * @param size
 * @returns A `Widget` with its top-left at a position and its size set.
 *
 */
template <class TWidget = ::rack::widget::Widget>
inline TWidget *createWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    TWidget* o = ::StoneyDSP::StoneyVCV::createWidget<TWidget>(pos);
	o->box.size = size;
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::widget::Widget *::StoneyDSP::StoneyVCV::createWidgetSized<::rack::widget::Widget>(::rack::math::Vec pos, ::rack::math::Vec size);

//==============================================================================

/**
 * @brief Creates a `Widget` subclass with its top-left at a position.
 *
 * @param pos
 * @param size
 * @returns A `Widget` with its center at a position and its size set.
 *
 */
template <class TWidget = ::rack::widget::Widget>
inline TWidget *createWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    TWidget *o = ::StoneyDSP::StoneyVCV::createWidgetCentered<TWidget>(pos);
	o->box.size = size;
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::widget::Widget *::StoneyDSP::StoneyVCV::createWidgetCenteredSized<::rack::widget::Widget>(::rack::math::Vec pos, ::rack::math::Vec size);

//==============================================================================

/**
 * @brief
 *
 * @tparam
 *
 * @param pos
 * @param module
 * @param inputId
 *
 * @return
 */
template <class TParamWidget = ::rack::app::ParamWidget>
inline TParamWidget *createParamWidget(::rack::math::Vec pos, ::rack::engine::Module* module, int paramId)
{
    using namespace rack;

    static_assert(::std::is_base_of<::rack::app::ParamWidget, TParamWidget>::value, "TParamWidget must be derived from rack::app::ParamWidget");

	TParamWidget* o = new TParamWidget;
	o->box.pos = pos;
	o->app::ParamWidget::module = module;
	o->app::ParamWidget::paramId = paramId;
	o->initParamQuantity();
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::app::ParamWidget *::StoneyDSP::StoneyVCV::createParamWidget<::rack::app::ParamWidget>(::rack::math::Vec pos, ::rack::engine::Module* module, int paramId);

//==============================================================================

/**
 * @brief
 *
 * @tparam
 *
 * @param pos
 * @param module
 * @param inputId
 *
 * @return
 */
template <class TParamWidget = ::rack::app::ParamWidget>
inline TParamWidget *createParamWidgetCentered(::rack::math::Vec pos, ::rack::engine::Module* module, int paramId)
{
	TParamWidget* o = ::StoneyDSP::StoneyVCV::createParamWidget<TParamWidget>(pos, module, paramId);
    o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::app::ParamWidget *::StoneyDSP::StoneyVCV::createParamWidgetCentered<::rack::app::ParamWidget>(::rack::math::Vec pos, ::rack::engine::Module* module, int paramId);

//==============================================================================

/**
 * @brief
 *
 * @tparam
 *
 * @param pos
 * @param module
 * @param inputId
 *
 * @return
 */
template <class TPortWidget = ::rack::app::PortWidget>
inline TPortWidget *createInput(::rack::math::Vec pos, ::rack::engine::Module *module, int inputId)
{
    // Import some namespaces for convenience
    using namespace ::rack;

    static_assert(::std::is_base_of<::rack::app::PortWidget, TPortWidget>::value, "TPortWidget must be derived from rack::app::PortWidget");

	TPortWidget *o = new TPortWidget;
	o->box.pos = pos;
	o->app::PortWidget::module = module;
	o->app::PortWidget::type = ::rack::engine::Port::INPUT;
	o->app::PortWidget::portId = inputId;
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::app::PortWidget *::StoneyDSP::StoneyVCV::createInput<::rack::app::PortWidget>(::rack::math::Vec pos, ::rack::engine::Module *module, int inputId);

//==============================================================================

/**
 * @brief
 *
 * @tparam
 *
 * @param pos
 * @param module
 * @param inputId
 *
 * @return
 */
template <class TPortWidget = ::rack::app::PortWidget>
inline TPortWidget *createInputCentered(::rack::math::Vec pos, ::rack::engine::Module* module, int inputId)
{
	TPortWidget *o = ::StoneyDSP::StoneyVCV::createInput<TPortWidget>(pos, module, inputId);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::app::PortWidget *::StoneyDSP::StoneyVCV::createInputCentered<::rack::app::PortWidget>(::rack::math::Vec pos, ::rack::engine::Module *module, int inputId);

//==============================================================================

/**
 * @brief
 *
 * @tparam
 *
 * @param pos
 * @param module
 * @param outputId
 *
 * @return
 */
template <class TPortWidget = ::rack::app::PortWidget>
inline TPortWidget* createOutput(::rack::math::Vec pos, ::rack::engine::Module *module, int outputId)
{
    // Import some namespaces for convenience
    using namespace ::rack;

    static_assert(::std::is_base_of<::rack::app::PortWidget, TPortWidget>::value, "TPortWidget must be derived from rack::app::PortWidget");

	TPortWidget *o = new TPortWidget;
	o->box.pos = pos;
	o->app::PortWidget::module = module;
	o->app::PortWidget::type = ::rack::engine::Port::OUTPUT;
	o->app::PortWidget::portId = outputId;
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::app::PortWidget *::StoneyDSP::StoneyVCV::createOutput<::rack::app::PortWidget>(::rack::math::Vec pos, ::rack::engine::Module *module, int inputId);

//==============================================================================

/**
 * @brief
 *
 * @tparam
 *
 * @param pos
 * @param module
 * @param outputId
 *
 * @return
 */
template <class TPortWidget = ::rack::app::PortWidget>
inline TPortWidget *createOutputCentered(::rack::math::Vec pos, ::rack::engine::Module *module, int outputId)
{
	TPortWidget *o = ::StoneyDSP::StoneyVCV::createOutput<TPortWidget>(pos, module, outputId);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}
// Explicit instantiations to ensure the definition is visible to the linker...
template ::rack::app::PortWidget *::StoneyDSP::StoneyVCV::createOutputCentered<::rack::app::PortWidget>(::rack::math::Vec pos, ::rack::engine::Module *module, int inputId);

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================


//==============================================================================

/**
 * Add this definition to a class or struct's declaration body to make it
 * compatible with the StoneyVCV `createWidget` factory methods.
 */
#define STONEYVCV_DECLARE_WIDGET_FACTORY_FUNCTIONS(ClassName) \
public: \
    template <class TWidget> \
    friend TWidget *::rack::createWidget(::rack::math::Vec pos); \
 \
    template <class TWidget> \
    friend TWidget *::rack::createWidgetCentered(::rack::math::Vec pos); \
 \
    template <class TWidget> \
    friend TWidget *::StoneyDSP::StoneyVCV::createWidget(::rack::math::Vec pos); \
 \
    template <class TWidget> \
    friend TWidget *::StoneyDSP::StoneyVCV::createWidgetCentered(::rack::math::Vec pos); \
 \
    template <class TWidget> \
    friend TWidget *::StoneyDSP::StoneyVCV::createWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size); \
 \
    template <class TWidget> \
    friend TWidget *::StoneyDSP::StoneyVCV::createWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size);
