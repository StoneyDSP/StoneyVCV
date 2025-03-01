/*******************************************************************************
 * @file test/StoneyVCV/HP1.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

//==============================================================================

#if defined (STONEYVCV_BUILD_HP1) && defined (STONEYVCV_BUILD_TESTS)

//==============================================================================

#include <StoneyVCV/HP1.hpp>

//==============================================================================

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//==============================================================================

#include "test.hpp"

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP1 {
struct HP1Spec final :
    ::StoneyDSP::StoneyVCV::Spec
{
public:
    ::std::string slug, name, description, manualUrl;
    bool hidden;
    static constexpr ::StoneyDSP::size_t NUM_PARAMS = 0;
    static constexpr ::StoneyDSP::size_t NUM_INPUTS = 0;
    static constexpr ::StoneyDSP::size_t NUM_OUTPUTS = 0;
    static constexpr ::StoneyDSP::size_t NUM_LIGHTS = 0;
    ::rack::math::Vec size;
    HP1Spec()
    :   slug("HP1"),
        name("HP1"),
        description("1hp Panel Spacer."),
        manualUrl("https://stoneydsp.github.io/StoneyVCV/md_docs_2HP1.html"),
        hidden(false),
        size(
            15.0F, // ::rack::window::mm2px(5.079999999F),
            380.0F //::rack::window::mm2px(128.693333312F)
        )
    {};
    ~HP1Spec() = default;
private:
    STONEYDSP_DECLARE_NON_COPYABLE(HP1Spec)
    STONEYDSP_DECLARE_NON_MOVEABLE(HP1Spec)
};
}
}
}

//==============================================================================

// Tests go here...

TEST_CASE( "HP1", "[HP1]" ) {

    ::std::unique_ptr<::StoneyDSP::StoneyVCV::HP1::HP1Spec> spec = ::std::make_unique<::StoneyDSP::StoneyVCV::HP1::HP1Spec>();

    //==========================================================================

    SECTION( "files" ) {
        REQUIRE(STONEYVCV_HP1_HPP_INCLUDED == 1);
    }

    //==========================================================================

    SECTION( "HP1Module" ) {

        //======================================================================

        SECTION( "statics" ) {
            REQUIRE( ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_PARAMS == spec.get()->NUM_PARAMS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_INPUTS == spec.get()->NUM_INPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_OUTPUTS == spec.get()->NUM_OUTPUTS );
            REQUIRE( ::StoneyDSP::StoneyVCV::HP1::HP1Module::NUM_LIGHTS == spec.get()->NUM_LIGHTS );
        }

        //======================================================================

        SECTION( "methods" ) {
            ::StoneyDSP::StoneyVCV::HP1::HP1Module* test_hp1Module = new ::StoneyDSP::StoneyVCV::HP1::HP1Module;
            REQUIRE( test_hp1Module->getNumParams() == static_cast<int>(spec.get()->NUM_PARAMS) );
            REQUIRE( test_hp1Module->getNumInputs() == static_cast<int>(spec.get()->NUM_INPUTS) );
            REQUIRE( test_hp1Module->getNumOutputs() == static_cast<int>(spec.get()->NUM_OUTPUTS) );
            REQUIRE( test_hp1Module->getNumLights() == static_cast<int>(spec.get()->NUM_LIGHTS) );
            delete test_hp1Module;
        }
    }

    //==========================================================================

    // SECTION( "HP1ModuleWidget" ) {
    //     ::StoneyDSP::StoneyVCV::HP1::HP1Module* test_hp1Module = new ::StoneyDSP::StoneyVCV::HP1::HP1Module;
    //     ::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget* test_hp1ModuleWidget = new ::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget(test_hp1Module);
    //     delete test_hp1ModuleWidget;
    //     delete test_hp1Module;
    // }

    //==========================================================================

    SECTION( "createModelHP1" ) {

        ::rack::plugin::Model* test_modelHP1 = ::StoneyDSP::StoneyVCV::HP1::createModelHP1();
        REQUIRE( test_modelHP1 != nullptr );

        SECTION( "createModule" ) {

            auto test_module = test_modelHP1->createModule();
            REQUIRE( test_module != nullptr );

            // SECTION( "createModuleWidget" ) {
            //     auto test_moduleWidget = test_modelHP1->createModuleWidget(test_module);
            //     REQUIRE( test_moduleWidget != nullptr );
            // }
        }
    }

    //==========================================================================

    SECTION( "modelHP1" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::HP1::modelHP1 != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP1::modelHP1->slug == spec.get()->slug );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP1::modelHP1->name == spec.get()->name );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP1::modelHP1->description == spec.get()->description );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP1::modelHP1->manualUrl == spec.get()->manualUrl );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP1::modelHP1->hidden == spec.get()->hidden );
    }

    //==========================================================================

    spec.reset();
}

//==============================================================================

#endif

//==============================================================================
