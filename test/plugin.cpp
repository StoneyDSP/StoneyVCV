#include <catch2/catch_test_macros.hpp>

#include "plugin.hpp"

// Tests go here...

TEST_CASE("plugin", "[plugin]") {

    SECTION( "files" ) {
        REQUIRE(STONEYVCV_PLUGIN_HPP_INCLUDED == 1);
    }

    SECTION( "pluginInstance" ) {
        REQUIRE(::StoneyDSP::VCVRack::pluginInstance == nullptr);
    }

    SECTION("modules") {
#ifdef STONEYVCV_EXPERIMENTAL
    // EXPERIMENTAL MODULES HERE...
#endif

#if (STONEYVCV_VERSION_MAJOR >= 0) && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 1)
        SECTION( "HP1" ) {
            REQUIRE(::StoneyDSP::VCVRack::modelHP1 != nullptr);
        }
#elif (STONEYVCV_VERSION_MAJOR) >= 0 && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 0)
    #warning "No modules found..."
#endif
    }
}
