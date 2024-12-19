/*******************************************************************************
 * @file plugin.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 0.0.0
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * therights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/orsell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_PLUGIN) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include "StoneyVCV/plugin.hpp"

//==============================================================================

#include <catch2/catch_test_macros.hpp>

//==============================================================================

// Tests go here...

TEST_CASE("plugin", "[plugin]") {

    SECTION( "files" ) {
        REQUIRE(STONEYVCV_PLUGIN_HPP_INCLUDED == 1);
    }

    SECTION( "pluginInstance" ) {
        REQUIRE(::StoneyDSP::StoneyVCV::pluginInstance == nullptr);
    }

    //// assert(box.size.y == ::rack::RACK_GRID_HEIGHT);

    SECTION("modules") {
#ifdef STONEYVCV_EXPERIMENTAL
    // EXPERIMENTAL MODULES HERE...
#ifdef STONEYVCV_BUILD_VCA
        SECTION( "VCA" ) {
            REQUIRE(::StoneyDSP::StoneyVCV::VCA::modelVCA != nullptr);
        }
#endif
#ifdef STONEYVCV_BUILD_LFO
        SECTION( "LFO" ) {
            REQUIRE(::StoneyDSP::StoneyVCV::LFO::modelLFO != nullptr);
        }
#endif
#endif

#if (STONEYVCV_VERSION_MAJOR >= 0) && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 1)
#ifdef STONEYVCV_BUILD_HP4
        SECTION( "HP4" ) {
            REQUIRE(::StoneyDSP::StoneyVCV::HP4::modelHP4 != nullptr);
        }
#endif
#ifdef STONEYVCV_BUILD_HP2
        SECTION( "HP2" ) {
            REQUIRE(::StoneyDSP::StoneyVCV::HP2::modelHP2 != nullptr);
        }
#endif
#ifdef STONEYVCV_BUILD_HP1
        SECTION( "HP1" ) {
            REQUIRE(::StoneyDSP::StoneyVCV::HP1::modelHP1 != nullptr);
        }
#endif
#elif (STONEYVCV_VERSION_MAJOR) >= 0 && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 0)
    #warning "No modules found..."
#endif
    }
}

//==============================================================================

#endif

//==============================================================================
