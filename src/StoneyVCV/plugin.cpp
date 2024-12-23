/*******************************************************************************
 * @file plugin.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.1
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================

#include <StoneyVCV/plugin.hpp>

//==============================================================================

#include <rack.hpp>

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

/**
 * @brief The `StoneyDSP` VCV Rack Plugin instance.
 */
::rack::plugin::Plugin* pluginInstance;

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================

#if defined (STONEYVCV_BUILD_MODULES)

/**
 * @brief The `StoneyDSP` VCV Rack Plugin Initialiser.
 *
 * @param p
 */
void init(::rack::plugin::Plugin* p) {

    ::StoneyDSP::StoneyVCV::pluginInstance = p;

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 2)

    #ifdef STONEYVCV_BUILD_VCA
        p->addModel(::StoneyDSP::StoneyVCV::VCA::modelVCA);
    #endif

#endif // STONEYVCV_VERSION_PATCH >= 2

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH >= 1)

    #ifdef STONEYVCV_BUILD_HP4
        p->addModel(::StoneyDSP::StoneyVCV::HP4::modelHP4);
    #endif

    #ifdef STONEYVCV_BUILD_HP2
        p->addModel(::StoneyDSP::StoneyVCV::HP2::modelHP2);
    #endif

    #ifdef STONEYVCV_BUILD_HP1
        p->addModel(::StoneyDSP::StoneyVCV::HP1::modelHP1);
    #endif

#endif

#if (STONEYVCV_VERSION_MAJOR >= 2U) && (STONEYVCV_VERSION_MINOR >= 0) && (STONEYVCV_VERSION_PATCH < 1U)
    #warning "No modules found..."
#endif

#ifdef STONEYVCV_EXPERIMENTAL

    #warning "Building experimental modules..."
    // EXPERIMENTAL MODULES HERE...

    #ifdef STONEYVCV_BUILD_LFO
        p->addModel(::StoneyDSP::StoneyVCV::LFO::modelLFO);
    #endif

#endif // STONEYVCV_EXPERIMENTAL

    // Any other plugin initialization may go here.
    // As an alternative, consider lazy-loading assets and lookup tables when
    // your module is created to reduce startup times of Rack.
}

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

namespace Panels {

//==============================================================================

::NVGcolor bgBlack = ::nvgRGBA(43, 43, 43, 255);
::NVGcolor bgWhite = ::nvgRGBA(235, 235, 235, 255);
::NVGcolor borderColor = nvgRGBAf(0.5F, 0.5F, 0.5F, 0.5F);
::NVGcolor bgGradientBlackS0 = ::nvgRGB(42, 42, 43);
::NVGcolor bgGradientBlackS1 = ::nvgRGB(23, 23, 23);
::NVGcolor bgGradientWhiteS0 = ::nvgRGB(235, 235, 235);
::NVGcolor bgGradientWhiteS1 = ::nvgRGB(225, 225, 225);
::StoneyDSP::float_t MIN_WIDTH = ::rack::window::mm2px(5.079999999F);
::StoneyDSP::float_t MIN_HEIGHT = ::rack::window::mm2px(128.693333312F);

//==============================================================================

void addScrewsToWidget(::rack::widget::Widget* widget)
{
    const auto& size = widget->getSize();

    const ::rack::math::Vec screwsPositions [4] = {
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
        ::rack::math::Vec( // top-right
            (size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))),
        ::rack::math::Vec(// bottom-right
            (size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)))
    };
    ::rack::ThemedScrew* screws [4] = {
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[0]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[1]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[2]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(screwsPositions[3])
    };
    for(auto screw : screws) {
        widget->addChild(screw);
    }
}

//==============================================================================

} // namespace Panels

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================

#endif // defined (STONEYVCV_BUILD_MODULES)

//==============================================================================

#endif // defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================
