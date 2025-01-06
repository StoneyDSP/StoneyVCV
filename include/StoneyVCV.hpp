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
        DBG("Creating StoneyDSP::StoneyVCV::Engine");
    };

    virtual ~Engine() noexcept = 0;                                             // pure virtual

    //==========================================================================

    virtual void processSample(T* sample) = 0;                                  // pure virtual

    //==========================================================================

private:

    //==========================================================================

    STONEYDSP_DECLARE_NON_COPYABLE(Engine)
    STONEYDSP_DECLARE_NON_MOVEABLE(Engine)
};

template<class T>
::StoneyDSP::StoneyVCV::Engine<T>::~Engine() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::Engine");
}

template struct ::StoneyDSP::StoneyVCV::Engine<::StoneyDSP::float_t>;
template struct ::StoneyDSP::StoneyVCV::Engine<::StoneyDSP::double_t>;

//==============================================================================

template <class TWidget = ::rack::widget::Widget>
TWidget *createWidgetSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    TWidget* o = ::rack::createWidget<TWidget>(pos);
	o->box.size = size;
	return o;
}

template <class TWidget = ::rack::widget::Widget>
TWidget* createWidgetCenteredSized(::rack::math::Vec pos, ::rack::math::Vec size)
{
    TWidget* o = ::rack::createWidgetCentered<TWidget>(pos);
	o->box.size = size;
	return o;
}

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

// #include <StoneyVCV/version.hpp>
// #include <StoneyVCV/ComponentLibrary.hpp>
// #include <StoneyVCV/plugin.hpp>
// #include <StoneyVCV/HP1.hpp>
// #include <StoneyVCV/HP2.hpp>
// #include <StoneyVCV/HP4.hpp>
// #include <StoneyVCV/VCA.hpp>

//==============================================================================
