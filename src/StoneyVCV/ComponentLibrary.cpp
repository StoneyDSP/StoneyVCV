/*******************************************************************************
 * @file src/StoneyVCV/ComponentLibrary.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <StoneyVCV.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

//==============================================================================

#include <string>

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

namespace Panels {

//==============================================================================

const ::NVGcolor bgWhite = ::nvgRGBA(235, 235, 235, 255);
const ::NVGcolor bgPortWhite = ::nvgRGBA(31, 31, 31, 255); // is dark
const ::NVGcolor bgGradientWhiteS0 = ::nvgRGBA(235, 235, 235, 0);
const ::NVGcolor bgGradientWhiteS1 = ::nvgRGBA(225, 225, 225, 255);

const ::NVGcolor bgBlack = ::nvgRGBA(43, 43, 43, 255);
const ::NVGcolor bgPortBlack = ::nvgRGBA(237, 237, 237, 255); // is light
const ::NVGcolor bgGradientBlackS0 = ::nvgRGBA(42, 42, 43, 0);
const ::NVGcolor bgGradientBlackS1 = ::nvgRGBA(23, 23, 23, 255);

const ::NVGcolor borderColor = nvgRGBAf(0.5F, 0.5F, 0.5F, 0.5F);

const float MIN_WIDTH = 15.0F; //::rack::window::mm2px(5.079999999F);
const float MIN_HEIGHT = 380.0F; // ::rack::window::mm2px(128.693333312F);

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

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
