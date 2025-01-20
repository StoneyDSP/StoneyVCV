/*******************************************************************************
 * @file test/StoneyVCV/LFO.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

//==============================================================================

#if defined (STONEYVCV_BUILD_LFO) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include <StoneyVCV/LFO.hpp>

//==============================================================================

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//==============================================================================

#include "test.hpp"

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace LFO {
struct LFOSpec final : ::StoneyDSP::StoneyVCV::Spec
{
public:
    const ::std::string slug, name , description, manualUrl;
    const bool hidden;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 4U;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 4U;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 4U;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 2U;
    const ::rack::math::Vec size;
    LFOSpec()
    :   slug("LFO"),
        name("LFO"),
        description("Low-frequency Oscillator. Supports polyphony."),
        manualUrl("https://stoneydsp.github.io/StoneyVCV/md_docs_2LFO.html"),
        hidden(false),
        size(
            135.0F, // ::rack::window::mm2px(30.479999995F),
            380.0F //::rack::window::mm2px(128.693333312F)
        )
    {};
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
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::NUM_PARAMS == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::NUM_INPUTS == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::NUM_OUTPUTS == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::LFO::LFOModule::NUM_LIGHTS == spec.get()->NUM_LIGHTS );
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

    SECTION( "createModelLFO" ) {

        ::rack::plugin::Model* test_modelLFO = ::StoneyDSP::StoneyVCV::LFO::createModelLFO();
        REQUIRE( test_modelLFO != nullptr );

        SECTION( "createModule" ) {

            auto test_module = test_modelLFO->createModule();
            REQUIRE( test_module != nullptr );

            // SECTION( "createModuleWidget" ) {
            //     auto test_moduleWidget = test_modelLFO->createModuleWidget(test_module);
            //     REQUIRE( test_moduleWidget != nullptr );
            // }
        }
    }

    //==========================================================================

    SECTION( "modelLFO" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO->slug == spec.get()->slug );
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO->name == spec.get()->name );
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO->description == spec.get()->description );
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO->manualUrl == spec.get()->manualUrl );
        REQUIRE( ::StoneyDSP::StoneyVCV::LFO::modelLFO->hidden == spec.get()->hidden );
    }

    //==========================================================================

    spec.reset();
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_LFO) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================
