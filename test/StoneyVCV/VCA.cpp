/*******************************************************************************
 * @file VCA.cpp
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

#if defined (STONEYVCV_BUILD_VCA) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//==============================================================================

#include "StoneyVCV/plugin.hpp"
#include "StoneyVCV/VCA.hpp"

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace VCA {
struct VCASpec final : ::StoneyDSP::StoneyVCV::Spec
{
public:
    ::std::string slug;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 1U;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 2U;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 1U;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 1U;
    ::rack::math::Vec size;
    VCASpec()
    :   slug("VCA"),
        size(
            ::rack::window::mm2px(30.479999995F).
            ::rack::window::mm2px(128.693333312F)
        )
    {};
private:
    // STONEYDSP_DECLARE_NON_CONSTRUCTABLE(VCASpec)
    STONEYDSP_DECLARE_NON_COPYABLE(VCASpec)
    STONEYDSP_DECLARE_NON_MOVEABLE(VCASpec)
};
}
}
}


//==============================================================================

// Tests go here...

TEST_CASE( "VCA", "[VCA]" ) {

    std::shared_ptr<::StoneyDSP::StoneyVCV::VCA::VCASpec> spec = std::make_shared<::StoneyDSP::StoneyVCV::VCA::VCASpec>();

    //==========================================================================

    SECTION( "files" ) {
        REQUIRE( STONEYVCV_VCA_HPP_INCLUDED == 1 );
    }

    //==========================================================================

    SECTION( "VCAModule" ) {
        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_PARAMS == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_INPUTS == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_OUTPUTS == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::NUM_LIGHTS == spec.get()->NUM_LIGHTS );
        }
        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::VCA::VCAModule* test_vcaModule = new ::StoneyDSP::StoneyVCV::VCA::VCAModule;
            REQUIRE( test_vcaModule->getNumParams() == spec.get()->NUM_PARAMS );
            REQUIRE( test_vcaModule->getNumInputs() == spec.get()->NUM_INPUTS );
            REQUIRE( test_vcaModule->getNumOutputs() == spec.get()->NUM_OUTPUTS );
            REQUIRE( test_vcaModule->getNumLights() == spec.get()->NUM_LIGHTS );
            delete test_vcaModule;
        }
    }

    //==========================================================================

    SECTION( "VCAModuleWidget" ) {
        // ::StoneyDSP::StoneyVCV::VCA::VCAModule* test_vcaModule = new ::StoneyDSP::StoneyVCV::VCA::VCAModule;
        // ::rack::app::ModuleWidget* test_vcaModuleWidget = new ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget(dynamic_cast<::StoneyDSP::StoneyVCV::VCA::VCAModule*>(test_vcaModule));
        // std::shared_ptr<::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget> test_vcaModuleWidget = std::make_shared<::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget>();
        // REQUIRE( test_vcaModuleWidget.get()->box.size.x == 5.08F );
        // REQUIRE( test_vcaModuleWidget.get()->box.size.y == 128.5F );
        // delete test_vcaModuleWidget;
        // delete test_vcaModule;

        // REQUIRE_THAT(
        //     test_vcaModuleWidget.box.size.x,
        //     Catch::Matchers::WithinRel(5.08 * 3.0, 0.001)
        // );

        // REQUIRE_THAT(
        //     test_vcaModuleWidget.box.size.y,
        //     Catch::Matchers::WithinRel(128.5, 0.001)
        // );


        // ::StoneyDSP::StoneyVCV::VCA::VCAModule* test_vcaModule = NULL;
        // test_vcaModule = dynamic_cast<::StoneyDSP::StoneyVCV::VCA::VCAModule*>(new ::StoneyDSP::StoneyVCV::VCA::VCAModule);
        // ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget* test_vcaModuleWidget = new ::StoneyDSP::StoneyVCV::VCA::VCAModuleWidget(test_vcaModule);

        // delete test_vcaModuleWidget;
        // delete test_vcaModule;
    }

    //==========================================================================

    SECTION( "instance" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA->slug == spec.get()->slug );
    }

    //==========================================================================

    spec.reset();
}

//==============================================================================

#endif

//==============================================================================
