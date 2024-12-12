/**
 * @file LFO.cpp
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

#if (STONEYVCV_BUILD_LFO == 1) && (STONEYVCV_BUILD_TESTS == 1)

//==============================================================================

#include <catch2/catch_test_macros.hpp>
// for floating point comparisons
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//==============================================================================

#include "StoneyVCV/plugin.hpp"
#include "StoneyVCV/LFO.hpp"

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace LFO {
struct LFOSpec final : ::StoneyDSP::StoneyVCV::Spec
{
public:
    std::string slug;
    static constexpr int NUM_PARAMS = 0;
    static constexpr int NUM_INPUTS = 0;
    static constexpr int NUM_OUTPUTS = 0;
    static constexpr int NUM_LIGHTS = 0;
    LFOSpec() : slug("LFO") {};
private:
    // STONEYDSP_DECLARE_NON_CONSTRUCTABLE(LFOSpec)
    STONEYDSP_DECLARE_NON_COPYABLE(LFOSpec)
    STONEYDSP_DECLARE_NON_MOVEABLE(LFOSpec)
};
}
}
}

//==============================================================================

// Tests go here...

TEST_CASE( "LFO", "[LFO]" ) {

    std::shared_ptr<::StoneyDSP::StoneyVCV::LFO::LFOSpec> spec = std::make_shared<::StoneyDSP::StoneyVCV::LFO::LFOSpec>();

    //==========================================================================

    SECTION( "files" ) {
        REQUIRE( STONEYVCV_LFO_HPP_INCLUDED == 1 );
    }

    //==========================================================================

    SECTION( "LFOModule" ) {
        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::PARAMS_LEN == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::INPUTS_LEN == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::OUTPUTS_LEN == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::LIGHTS_LEN == spec.get()->NUM_LIGHTS );
        }
        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::LFO::LFOModule* test_lfoModule = new ::StoneyDSP::StoneyVCV::LFO::LFOModule;
            REQUIRE( test_lfoModule->getNumParams() == spec.get()->NUM_PARAMS );
            REQUIRE( test_lfoModule->getNumInputs() == spec.get()->NUM_INPUTS );
            REQUIRE( test_lfoModule->getNumOutputs() == spec.get()->NUM_OUTPUTS );
            REQUIRE( test_lfoModule->getNumLights() == spec.get()->NUM_LIGHTS );
            delete test_lfoModule;
        }
    }

    //==========================================================================

    SECTION( "LFOModuleWidget" ) {
        // ::StoneyDSP::StoneyVCV::LFO::LFOModule* test_lfoModule = new ::StoneyDSP::StoneyVCV::LFO::LFOModule;
        // ::rack::app::ModuleWidget* test_lfoModuleWidget = new ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget(dynamic_cast<::StoneyDSP::StoneyVCV::LFO::LFOModule*>(test_lfoModule));
        // std::shared_ptr<::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget> test_lfoModuleWidget = std::make_shared<::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget>();
        // REQUIRE( test_lfoModuleWidget.get()->box.size.x == 5.08F );
        // REQUIRE( test_lfoModuleWidget.get()->box.size.y == 128.5F );
        // delete test_lfoModuleWidget;
        // delete test_lfoModule;

        // REQUIRE_THAT(
        //     test_lfoModuleWidget.box.size.x,
        //     Catch::Matchers::WithinRel(5.08 * 3.0, 0.001)
        // );

        // REQUIRE_THAT(
        //     test_lfoModuleWidget.box.size.y,
        //     Catch::Matchers::WithinRel(128.5, 0.001)
        // );


        // ::StoneyDSP::StoneyVCV::LFO::LFOModule* test_lfoModule = NULL;
        // test_lfoModule = dynamic_cast<::StoneyDSP::StoneyVCV::LFO::LFOModule*>(new ::StoneyDSP::StoneyVCV::LFO::LFOModule);
        // ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget* test_lfoModuleWidget = new ::StoneyDSP::StoneyVCV::LFO::LFOModuleWidget(test_lfoModule);

        // delete test_lfoModuleWidget;
        // delete test_lfoModule;
    }

    //==========================================================================

    SECTION( "instance" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO->slug == spec.get()->slug );
    }

    //==========================================================================

    spec.reset();
}

//==============================================================================

#endif

//==============================================================================
