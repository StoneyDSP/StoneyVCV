/*******************************************************************************
 * @file test/StoneyVCV/plugin.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
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
        REQUIRE(::StoneyDSP::StoneyVCV::Plugin::pluginInstance == nullptr);
    }

    //// assert(box.size.y == ::rack::RACK_GRID_HEIGHT);

    SECTION("modules") {
#ifdef STONEYVCV_EXPERIMENTAL
    // EXPERIMENTAL MODULES HERE...
    #ifdef STONEYVCV_BUILD_LFO
        SECTION( "LFO" ) {
            REQUIRE(::StoneyDSP::StoneyVCV::LFO::modelLFO != nullptr);
        }
    #endif
#endif

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH >= 2U)
    #ifdef STONEYVCV_BUILD_VCA
        SECTION( "VCA" ) {
            REQUIRE(::StoneyDSP::StoneyVCV::VCA::modelVCA != nullptr);
        }
    #endif
#endif

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH >= 1U)
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
#endif

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0U) && (STONEYVCV_VERSION_PATCH < 1U)
    #warning "No modules found..."
#endif
    }
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_PLUGIN) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================
