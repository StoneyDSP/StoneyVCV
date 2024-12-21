/*******************************************************************************
 * @file HP4.cpp
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

//==============================================================================

#if defined (STONEYVCV_BUILD_HP4) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include <StoneyVCV/HP4.hpp>

//==============================================================================

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP4 {
struct HP4Spec final :
    ::StoneyDSP::StoneyVCV::Spec {
public:
    ::std::string slug;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 0U;
    ::rack::math::Vec size;
    HP4Spec()
    :   slug("HP4"),
        size(
            ::rack::window::mm2px(5.079999999F * 4.0F),
            ::rack::window::mm2px(128.693333312F)
        )
    {};
private:
    // STONEYDSP_DECLARE_NON_CONSTRUCTABLE(HP4Spec)
    STONEYDSP_DECLARE_NON_COPYABLE(HP4Spec)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP4Spec)
};
}
}
}

//==============================================================================

// Tests go here...

TEST_CASE( "HP4", "[HP4]" ) {

    std::shared_ptr<::StoneyDSP::StoneyVCV::HP4::HP4Spec> spec = std::make_shared<::StoneyDSP::StoneyVCV::HP4::HP4Spec>();

    //==========================================================================

    SECTION( "files" ) {
        REQUIRE( STONEYVCV_HP4_HPP_INCLUDED == 1 );
    }

    //==========================================================================

    SECTION( "HP4Module" ) {

        //======================================================================

        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_PARAMS == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_INPUTS == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_OUTPUTS == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP4::HP4Module::NUM_LIGHTS == spec.get()->NUM_LIGHTS );
        }

        //======================================================================

        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::HP4::HP4Module* test_hp4Module = new ::StoneyDSP::StoneyVCV::HP4::HP4Module;
            REQUIRE( test_hp4Module->getNumParams() == spec.get()->NUM_PARAMS );
            REQUIRE( test_hp4Module->getNumInputs() == spec.get()->NUM_INPUTS );
            REQUIRE( test_hp4Module->getNumOutputs() == spec.get()->NUM_OUTPUTS );
            REQUIRE( test_hp4Module->getNumLights() == spec.get()->NUM_LIGHTS );
            delete test_hp4Module;
        }
    }

    //==========================================================================

    // SECTION( "HP4ModuleWidget" ) {
    //     // ::StoneyDSP::StoneyVCV::HP4::HP4Module* test_hp4Module = new ::StoneyDSP::StoneyVCV::HP4::HP4Module;
    //     // ::rack::app::ModuleWidget* test_hp4ModuleWidget = new ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget(dynamic_cast<::StoneyDSP::StoneyVCV::HP4::HP4Module*>(test_hp4Module));
    //     // std::shared_ptr<::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget> test_hp4ModuleWidget = std::make_shared<::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget>();
    //     // REQUIRE( test_hp4ModuleWidget.get()->box.size.x == 5.08F );
    //     // REQUIRE( test_hp4ModuleWidget.get()->box.size.y == 128.5F );
    //     // delete test_hp4ModuleWidget;
    //     // delete test_hp4Module;

    //     // REQUIRE_THAT(
    //     //     test_hp4ModuleWidget.box.size.x,
    //     //     Catch::Matchers::WithinRel(5.08 * 3.0, 0.001)
    //     // );

    //     // REQUIRE_THAT(
    //     //     test_hp4ModuleWidget.box.size.y,
    //     //     Catch::Matchers::WithinRel(128.5, 0.001)
    //     // );


    //     // ::StoneyDSP::StoneyVCV::HP4::HP4Module* test_hp4Module = NULL;
    //     // test_hp4Module = dynamic_cast<::StoneyDSP::StoneyVCV::HP4::HP4Module*>(new ::StoneyDSP::StoneyVCV::HP4::HP4Module);
    //     // ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget* test_hp4ModuleWidget = new ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget(test_hp4Module);

    //     // delete test_hp4ModuleWidget;
    //     // delete test_hp4Module;
    // }

    //==========================================================================

    // SECTION( "HP4ModuleWidget" ) {
    //     ::StoneyDSP::StoneyVCV::HP4::HP4Module* test_hp4Module = new ::StoneyDSP::StoneyVCV::HP4::HP4Module;
    //     ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget* test_hp4ModuleWidget = new ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget(test_hp4Module);
    //     delete test_hp4ModuleWidget;
    //     delete test_hp4Module;
    // }

    //==========================================================================

    SECTION( "instance" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4 != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4->slug == spec.get()->slug );
    }

    //==========================================================================

    spec.reset();
}

//==============================================================================

#endif

//==============================================================================
