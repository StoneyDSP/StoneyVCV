/*******************************************************************************
 * @file HP2.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 0.0.1
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

#if defined (STONEYVCV_BUILD_HP2) && defined (STONEYVCV_BUILD_TESTS)

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "StoneyVCV/HP2.hpp"

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP2 {
struct HP2Spec final :
    ::StoneyDSP::StoneyVCV::Spec
{
public:
    std::string slug;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 0U;
    ::rack::math::Vec size;
    HP2Spec()
    :   slug("HP2"),
        size(
            ::rack::window::mm2px(5.079999999F * 2.0F),
            ::rack::window::mm2px(128.693333312F)
        )
    {};
private:
    // STONEYDSP_DECLARE_NON_CONSTRUCTABLE(HP2Spec)
    STONEYDSP_DECLARE_NON_COPYABLE(HP2Spec)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP2Spec)
};
}
}
}

// Tests go here...

TEST_CASE( "HP2", "[HP2]" ) {

    std::shared_ptr<::StoneyDSP::StoneyVCV::HP2::HP2Spec> spec = std::make_shared<::StoneyDSP::StoneyVCV::HP2::HP2Spec>();

    SECTION( "files" ) {
        REQUIRE( STONEYVCV_HP2_HPP_INCLUDED == 1 );
    }
    SECTION( "HP2Module" ) {
        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_PARAMS == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_INPUTS == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_OUTPUTS == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_LIGHTS == spec.get()->NUM_LIGHTS );
        }
        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::HP2::HP2Module* test_hp2Module = new ::StoneyDSP::StoneyVCV::HP2::HP2Module;
            REQUIRE( test_hp2Module->getNumParams() == spec.get()->NUM_PARAMS );
            REQUIRE( test_hp2Module->getNumInputs() == spec.get()->NUM_INPUTS );
            REQUIRE( test_hp2Module->getNumOutputs() == spec.get()->NUM_OUTPUTS );
            REQUIRE( test_hp2Module->getNumLights() == spec.get()->NUM_LIGHTS );
            delete test_hp2Module;
        }
    }
    SECTION( "instance" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2 != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2->slug == spec.get()->slug );
    }

    spec.reset();
}

#endif
