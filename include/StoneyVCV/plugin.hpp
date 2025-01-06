/*******************************************************************************
 * @file include/StoneyVCV/plugin.hpp
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

#define STONEYVCV_PLUGIN_HPP_INCLUDED 1

#if defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================

#include <StoneyVCV/version.hpp>

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
 * @brief The `Plugin` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @plugin_VERSION@
 *
 */
namespace Plugin
{
/** @addtogroup Plugin
 *  @{
 */

//==============================================================================

/**
 * @brief Declare the Plugin instance, defined in `plugin.cpp`
 */
extern ::rack::plugin::Plugin* pluginInstance;

//==============================================================================

  /// @} group Plugin
} // namespace Plugin

//==============================================================================

#if defined (STONEYVCV_BUILD_MODULES)

// Declare each Model, defined in each module source file

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH >= 2U)

    #if defined (STONEYVCV_BUILD_VCA)
        namespace VCA {
        /** @addtogroup VCA
         *  @{
         */

        /**
         * @brief Declaration of the `VCA` Model instance, defined in `VCA.cpp`.
         */
        extern ::rack::plugin::Model* modelVCA;

        /// @} group VCA
        } // namespace VCA
    #endif // STONEYVCV_BUILD_VCA

#endif // STONEYVCV_VERSION_PATCH >= 2

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH >= 1U)

    #if defined (STONEYVCV_BUILD_HP4)
        namespace HP4 {
        /** @addtogroup HP4
         *  @{
         */

        /**
         * @brief Declaration of the `HP4` Model instance, defined in `HP4.cpp`.
         */
        extern ::rack::plugin::Model* modelHP4;


        /// @} group HP4
        } // namespace HP4
    #endif // STONEYVCV_BUILD_HP4

    #if defined (STONEYVCV_BUILD_HP2)
        namespace HP2 {
        /** @addtogroup HP2
         *  @{
         */

        /**
         * @brief Declaration of the `HP2` Model instance, defined in `HP2.cpp`.
         */
        extern ::rack::plugin::Model* modelHP2;

        /// @} group HP1
        } // namespace HP1
    #endif // STONEYVCV_BUILD_HP2

    #if defined (STONEYVCV_BUILD_HP1)
        namespace HP1 {
        /** @addtogroup HP1
         *  @{
         */

        /**
         * @brief Declaration of the `HP1` Model instance, defined in `HP1.cpp`.
         */
        extern ::rack::plugin::Model* modelHP1;

        /// @} group HP1
        } // namespace HP1
    #endif // STONEYVCV_BUILD_HP1

#endif

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH < 1U)
    #warning "No modules found..."
#endif

#if defined (STONEYVCV_EXPERIMENTAL)

    // EXPERIMENTAL MODULES HERE...

    #if defined (STONEYVCV_BUILD_LFO)
        namespace LFO {
        /** @addtogroup LFO
         *  @{
         */

        /**
         * @brief Declaration of the `LFO` Model instance, defined in `LFO.cpp`.
         */
        extern ::rack::plugin::Model* modelLFO;

        /// @} group LFO
        } // namespace LFO
    #endif // STONEYVCV_BUILD_LFO

#endif // STONEYVCV_EXPERIMENTAL

#endif // STONEYVCV_BUILD_MODULES

//==============================================================================

  /// @} group StoneyVCV
} // namespace StoneyVCV

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

#endif // STONEYVCV_BUILD_PLUGIN

//==============================================================================

namespace StoneyDSP {
/** @addtogroup StoneyDSP
 *  @{
 */

namespace StoneyVCV {
/** @addtogroup StoneyVCV
 *  @{
 */

namespace Tools {
/** @addtogroup Tools
 *  @{
 */
const extern ::StoneyDSP::float_t vMin;
const extern ::StoneyDSP::float_t vMax;
const extern ::StoneyDSP::float_t vNominal;
const extern ::StoneyDSP::float_t vBias;
const extern ::StoneyDSP::float_t vGround;
const extern ::StoneyDSP::float_t vFloor;

  /// @} group Tools
} // namespace Tools

// Declare an abstract base class with a pure virtual destructor.
// It's the simplest possible abstract class.
template <typename T>
struct Engine
{
public:
    Engine() {
        DBG("Creating StoneyDSP::StoneyVCV::Engine");
    };
    virtual ~Engine() noexcept = 0;                                             // pure virtual
    virtual void processSample(T* sample) = 0;                                  // pure virtual
};

template<class T>
::StoneyDSP::StoneyVCV::Engine<T>::~Engine() noexcept
{
    DBG("Destroying StoneyDSP::StoneyVCV::Engine");
}

template struct ::StoneyDSP::StoneyVCV::Engine<::StoneyDSP::float_t>;
template struct ::StoneyDSP::StoneyVCV::Engine<::StoneyDSP::double_t>;

  /// @} group StoneyVCV
} // namespace StoneyVCV

  /// @} group StoneyDSP
} // namespace StoneyDSP
