/*******************************************************************************
 * @file test/StoneyVCV/HP2.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

//==============================================================================

#if defined (STONEYVCV_BUILD_HP2) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include <StoneyVCV/HP2.hpp>

//==============================================================================

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//==============================================================================

#include "test.hpp"

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP2 {
struct HP2Spec final :
    ::StoneyDSP::StoneyVCV::Spec
{
public:
    ::std::string slug, name, description, manualUrl;
    bool hidden;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 0U;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 0U;
    ::rack::math::Vec size;
    HP2Spec()
    :   slug("HP2"),
        name("HP2"),
        description("2hp Panel Spacer."),
        manualUrl("https://stoneydsp.github.io/StoneyVCV/md_docs_2HP2.html"),
        hidden(false),
        size(
            30.0F, // ::rack::window::mm2px(10.1599999984F),
            380.0F //::rack::window::mm2px(128.693333312F)
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

//==============================================================================

// Tests go here...

TEST_CASE( "HP2", "[HP2]" ) {

    std::shared_ptr<::StoneyDSP::StoneyVCV::HP2::HP2Spec> spec = std::make_shared<::StoneyDSP::StoneyVCV::HP2::HP2Spec>();

    //==========================================================================

    SECTION( "files" ) {
        REQUIRE( STONEYVCV_HP2_HPP_INCLUDED == 1 );
    }

    //==========================================================================

    SECTION( "HP2Module" ) {

        //======================================================================

        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_PARAMS == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_INPUTS == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_OUTPUTS == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP2::HP2Module::NUM_LIGHTS == spec.get()->NUM_LIGHTS );
        }

        //======================================================================

        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::HP2::HP2Module* test_hp2Module = new ::StoneyDSP::StoneyVCV::HP2::HP2Module;
            REQUIRE( test_hp2Module->getNumParams() == static_cast<int>(spec.get()->NUM_PARAMS) );
            REQUIRE( test_hp2Module->getNumInputs() == static_cast<int>(spec.get()->NUM_INPUTS) );
            REQUIRE( test_hp2Module->getNumOutputs() == static_cast<int>(spec.get()->NUM_OUTPUTS) );
            REQUIRE( test_hp2Module->getNumLights() == static_cast<int>(spec.get()->NUM_LIGHTS) );
            delete test_hp2Module;
        }
    }

    // //==========================================================================

    // SECTION( "HP2ModuleWidget" ) {
    //     ::StoneyDSP::StoneyVCV::HP2::HP2Module* test_hp2Module = new ::StoneyDSP::StoneyVCV::HP2::HP2Module;
    //     ::StoneyDSP::StoneyVCV::HP2::HP2ModuleWidget* test_hp2ModuleWidget = new ::StoneyDSP::StoneyVCV::HP2::HP2ModuleWidget(test_hp2Module);
    //     delete test_hp2ModuleWidget;
    //     delete test_hp2Module;
    // }

    //==========================================================================

    SECTION( "createModelHP2" ) {

        ::rack::plugin::Model* test_modelHP2 = ::StoneyDSP::StoneyVCV::HP2::createModelHP2();
        REQUIRE( test_modelHP2 != nullptr );

        SECTION( "createModule" ) {

            auto test_module = test_modelHP2->createModule();
            REQUIRE( test_module != nullptr );

            // SECTION( "createModuleWidget" ) {
            //     auto test_moduleWidget = test_modelHP2->createModuleWidget(test_module);
            //     REQUIRE( test_moduleWidget != nullptr );
            // }
        }
    }

    //==========================================================================

    SECTION( "modelHP2" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2 != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2->slug == spec.get()->slug );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2->name == spec.get()->name );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2->description == spec.get()->description );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2->manualUrl == spec.get()->manualUrl );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP2::modelHP2->hidden == spec.get()->hidden );
    }

    //==========================================================================

    spec.reset();
}

#endif
