/**
 * @file HP2.cpp
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

#if (STONEYVCV_BUILD_HP2 == 1) && (STONEYVCV_BUILD_TESTS == 1)

#include <catch2/catch_test_macros.hpp>
// for floating point comparisons
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "HP2.hpp"

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
struct HP2Spec final : ::StoneyDSP::StoneyVCV::Spec {
public:
    std::string slug;
    static constexpr int NUM_PARAMS = 0;
    static constexpr int NUM_INPUTS = 0;
    static constexpr int NUM_OUTPUTS = 0;
    static constexpr int NUM_LIGHTS = 0;
    HP2Spec() : slug("HP2") {};
private:
    // STONEYDSP_DECLARE_NON_CONSTRUCTABLE(HP2Spec)
    STONEYDSP_DECLARE_NON_COPYABLE(HP2Spec)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP2Spec)
};
}
}

// Tests go here...

TEST_CASE( "HP2", "[HP2]" ) {

    std::shared_ptr<::StoneyDSP::StoneyVCV::HP2Spec> spec = std::make_shared<::StoneyDSP::StoneyVCV::HP2Spec>();

    SECTION( "files" ) {
        REQUIRE( STONEYVCV_HP2_HPP_INCLUDED == 1 );
    }
    SECTION( "HP2Module" ) {
        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2Module::PARAMS_LEN == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2Module::INPUTS_LEN == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2Module::OUTPUTS_LEN == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2Module::LIGHTS_LEN == spec.get()->NUM_LIGHTS );
        }
        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::HP2Module* test_hp2Module = new ::StoneyDSP::StoneyVCV::HP2Module;
            REQUIRE( test_hp2Module->getNumParams() == spec.get()->NUM_PARAMS );
            REQUIRE( test_hp2Module->getNumInputs() == spec.get()->NUM_INPUTS );
            REQUIRE( test_hp2Module->getNumOutputs() == spec.get()->NUM_OUTPUTS );
            REQUIRE( test_hp2Module->getNumLights() == spec.get()->NUM_LIGHTS );
            delete test_hp2Module;
        }
    }
    SECTION( "instance" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::modelHP2 != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::modelHP2->slug == spec.get()->slug );
    }

    spec.reset();
}

#endif
