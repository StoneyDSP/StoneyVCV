#include <catch2/catch_test_macros.hpp>

#include "HP1.hpp"

// Tests go here...

TEST_CASE("HP1", "[HP1]") {

    SECTION( "files" ) {
        REQUIRE(STONEYVCV_HP1_HPP_INCLUDED == 1);
    }

    SECTION( "instance" ) {
        REQUIRE(::StoneyDSP::VCVRack::modelHP1 != nullptr);
    }

}
