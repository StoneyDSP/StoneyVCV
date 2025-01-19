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

const ::NVGcolor bgLight = ::nvgRGBA(235, 235, 235, 255);
const ::NVGcolor bgPortLight = ::nvgRGBA(31, 31, 31, 255); // is dark
const ::NVGcolor bgGradientLightS0 = ::nvgRGBA(235, 235, 235, 0);
const ::NVGcolor bgGradientLightS1 = ::nvgRGBA(225, 225, 225, 255);

const ::NVGcolor bgDark = ::nvgRGBA(43, 43, 43, 255);
const ::NVGcolor bgPortDark = ::nvgRGBA(237, 237, 237, 255); // is light
const ::NVGcolor bgGradientDarkS0 = ::nvgRGBA(42, 42, 43, 0);
const ::NVGcolor bgGradientDarkS1 = ::nvgRGBA(23, 23, 23, 255);

const ::NVGcolor borderColor = nvgRGBAf(0.5F, 0.5F, 0.5F, 0.5F);

const float MIN_WIDTH = 15.0F; //::rack::window::mm2px(5.079999999F);
const float MIN_HEIGHT = 380.0F; // ::rack::window::mm2px(128.693333312F);

//==============================================================================

} // namespace Panels

//==============================================================================

} // namespace StoneyVCV

//==============================================================================

} // namespace StoneyDSP

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
