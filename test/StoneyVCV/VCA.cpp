/*******************************************************************************
 * @file test/StoneyVCV/VCA.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

//==============================================================================

#if defined (STONEYVCV_BUILD_VCA) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include <StoneyVCV/VCA.hpp>

//==============================================================================

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//==============================================================================

#include "test.hpp"

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace VCA {
struct VCASpec final : ::StoneyDSP::StoneyVCV::Spec
{
public:
    const ::std::string slug, name , description, manualUrl;
    const bool hidden;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 1U;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 2U;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 1U;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 2U;
    const ::rack::math::Vec size;
    VCASpec()
    :   slug("VCA"),
        name("VCA"),
        description("Voltage-controlled Amplifier. Supports polyphony."),
        manualUrl("https://stoneydsp.github.io/StoneyVCV/md_docs_2VCA.html"),
        hidden(false),
        size(
            45.0F, // ::rack::window::mm2px(30.479999995F),
            380.0F //::rack::window::mm2px(128.693333312F)
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
        REQUIRE(STONEYVCV_VCA_HPP_INCLUDED == 1);
    }

    //==========================================================================

    SECTION( "VCAModule" ) {
        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxParams::NUM_PARAMS == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxInputs::NUM_INPUTS == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxOutputs::NUM_OUTPUTS == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::VCA::VCAModule::IdxLights::NUM_LIGHTS == spec.get()->NUM_LIGHTS );
        }
        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::VCA::VCAModule* test_vcaModule = new ::StoneyDSP::StoneyVCV::VCA::VCAModule;
            REQUIRE( test_vcaModule->getNumParams() == static_cast<int>(spec.get()->NUM_PARAMS) );
            REQUIRE( test_vcaModule->getNumInputs() == static_cast<int>(spec.get()->NUM_INPUTS) );
            REQUIRE( test_vcaModule->getNumOutputs() == static_cast<int>(spec.get()->NUM_OUTPUTS) );
            REQUIRE( test_vcaModule->getNumLights() == static_cast<int>(spec.get()->NUM_LIGHTS) );
            delete test_vcaModule;
        }
    }

    //==========================================================================

    // SECTION( "VCAModuleWidget" ) {
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
    // }

    //==========================================================================

    SECTION( "createModelVCA" ) {

        ::rack::plugin::Model* test_modelVCA = ::StoneyDSP::StoneyVCV::VCA::createModelVCA();
        REQUIRE( test_modelVCA != nullptr );

        SECTION( "createModule" ) {

            auto test_module = test_modelVCA->createModule();
            REQUIRE( test_module != nullptr );

            // SECTION( "createModuleWidget" ) {
            //     auto test_moduleWidget = test_modelVCA->createModuleWidget(test_module);
            //     REQUIRE( test_moduleWidget != nullptr );
            // }
        }
    }

    //==========================================================================

    SECTION( "modelVCA" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA->slug == spec.get()->slug );
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA->name == spec.get()->name );
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA->description == spec.get()->description );
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA->manualUrl == spec.get()->manualUrl );
        REQUIRE( ::StoneyDSP::StoneyVCV::VCA::modelVCA->hidden == spec.get()->hidden );
    }

    //==========================================================================

    spec.reset();
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_VCA) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================
