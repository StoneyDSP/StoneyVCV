/*******************************************************************************
 * @file test/StoneyVCV/HP4.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
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

#include "test.hpp"

//==============================================================================

// Spec goes here...

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP4 {
struct HP4Spec final :
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
    HP4Spec()
    :   slug("HP4"),
        name("HP4"),
        description("4hp Panel Spacer."),
        manualUrl("https://stoneydsp.github.io/StoneyVCV/md_docs_2HP4.html"),
        hidden(false),
        size(
            60.0F, // ::rack::window::mm2px(5.079999999F * 4.0F),
            380.0F //::rack::window::mm2px(128.693333312F)
        )
    {};
    ~HP4Spec() = default;
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
            REQUIRE( test_hp4Module->getNumParams() == static_cast<int>(spec.get()->NUM_PARAMS) );
            REQUIRE( test_hp4Module->getNumInputs() == static_cast<int>(spec.get()->NUM_INPUTS) );
            REQUIRE( test_hp4Module->getNumOutputs() == static_cast<int>(spec.get()->NUM_OUTPUTS) );
            REQUIRE( test_hp4Module->getNumLights() == static_cast<int>(spec.get()->NUM_LIGHTS) );
            delete test_hp4Module;
        }
    }

    //==========================================================================

    // SECTION( "HP4ModuleWidget" ) {
    //     ::StoneyDSP::StoneyVCV::HP4::HP4Module* test_hp4Module = new ::StoneyDSP::StoneyVCV::HP4::HP4Module;
    //     ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget* test_hp4ModuleWidget = new ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget(test_hp4Module);
    //     delete test_hp4ModuleWidget;
    //     delete test_hp4Module;
    // }

    //==========================================================================

    SECTION( "createModelHP4" ) {

        ::rack::plugin::Model* test_modelHP4 = ::StoneyDSP::StoneyVCV::HP4::createModelHP4();
        REQUIRE( test_modelHP4 != nullptr );

        SECTION( "createModule" ) {

            auto test_module = test_modelHP4->createModule();
            REQUIRE( test_module != nullptr );

            // SECTION( "createModuleWidget" ) {
            //     auto test_moduleWidget = test_modelHP4->createModuleWidget(test_module);
            //     REQUIRE( test_moduleWidget != nullptr );
            // }
        }
    }

    //==========================================================================

    SECTION( "modelHP4" ) {
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4 != nullptr );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4->slug == spec.get()->slug );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4->name == spec.get()->name );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4->description == spec.get()->description );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4->manualUrl == spec.get()->manualUrl );
        REQUIRE( ::StoneyDSP::StoneyVCV::HP4::modelHP4->hidden == spec.get()->hidden );
    }

    //==========================================================================

    spec.reset();
}

//==============================================================================

#endif

//==============================================================================
