// #pragma once

// #define RACK_SDK_RACK_HPP_INCLUDED 1

// #include <Rack-SDK/rack/rack.hpp>

#pragma once

/*
The following headers are the "public" API of Rack.

Directly including Rack headers other than rack.hpp in your plugin is unsupported/unstable, since filenames and locations of symbols may change in any Rack version.
*/

#ifdef PRIVATE
#warning "Plugins must only include rack.hpp. Including other Rack headers is unsupported."
#endif

/** Functions with the PRIVATE attribute should not be called by plugins.
*/
#ifdef __clang__
#define PRIVATE __attribute__((deprecated("Using internal Rack function or symbol")))
#else
#define PRIVATE __attribute__((error("Using internal Rack function or symbol")))
#endif


#include <Rack-SDK/rack/common.hpp>
#include <Rack-SDK/rack/math.hpp>
#include <Rack-SDK/rack/string.hpp>
#include <Rack-SDK/rack/system.hpp>
#include <Rack-SDK/rack/mutex.hpp>
#include <Rack-SDK/rack/random.hpp>
#include <Rack-SDK/rack/network.hpp>
#include <Rack-SDK/rack/asset.hpp>
#include <Rack-SDK/rack/window/Window.hpp>
#include <Rack-SDK/rack/context.hpp>
#include <Rack-SDK/rack/audio.hpp>
#include <Rack-SDK/rack/midi.hpp>
#include <Rack-SDK/rack/settings.hpp>
#include <Rack-SDK/rack/helpers.hpp>
#include <Rack-SDK/rack/componentlibrary.hpp>

#include <Rack-SDK/rack/widget/TransparentWidget.hpp>
#include <Rack-SDK/rack/widget/OpenGlWidget.hpp>
#include <Rack-SDK/rack/widget/OpaqueWidget.hpp>
#include <Rack-SDK/rack/widget/FramebufferWidget.hpp>
#include <Rack-SDK/rack/widget/TransformWidget.hpp>
#include <Rack-SDK/rack/widget/event.hpp>
#include <Rack-SDK/rack/widget/ZoomWidget.hpp>
#include <Rack-SDK/rack/widget/SvgWidget.hpp>
#include <Rack-SDK/rack/widget/Widget.hpp>

#include <Rack-SDK/rack/ui/Tooltip.hpp>
#include <Rack-SDK/rack/ui/MenuLabel.hpp>
#include <Rack-SDK/rack/ui/MenuEntry.hpp>
#include <Rack-SDK/rack/ui/List.hpp>
#include <Rack-SDK/rack/ui/TooltipOverlay.hpp>
#include <Rack-SDK/rack/ui/Slider.hpp>
#include <Rack-SDK/rack/ui/Scrollbar.hpp>
#include <Rack-SDK/rack/ui/ProgressBar.hpp>
#include <Rack-SDK/rack/ui/MenuSeparator.hpp>
#include <Rack-SDK/rack/ui/MenuOverlay.hpp>
#include <Rack-SDK/rack/ui/Label.hpp>
#include <Rack-SDK/rack/ui/TextField.hpp>
#include <Rack-SDK/rack/ui/SequentialLayout.hpp>
#include <Rack-SDK/rack/ui/MenuItem.hpp>
#include <Rack-SDK/rack/ui/Button.hpp>
#include <Rack-SDK/rack/ui/ChoiceButton.hpp>
#include <Rack-SDK/rack/ui/OptionButton.hpp>
#include <Rack-SDK/rack/ui/RadioButton.hpp>
#include <Rack-SDK/rack/ui/Menu.hpp>
#include <Rack-SDK/rack/ui/ScrollWidget.hpp>

#include <Rack-SDK/rack/app/SliderKnob.hpp>
#include <Rack-SDK/rack/app/MultiLightWidget.hpp>
#include <Rack-SDK/rack/app/MidiDisplay.hpp>
#include <Rack-SDK/rack/app/CircularShadow.hpp>
#include <Rack-SDK/rack/app/AudioDisplay.hpp>
#include <Rack-SDK/rack/app/LedDisplay.hpp>
#include <Rack-SDK/rack/app/ModuleLightWidget.hpp>
#include <Rack-SDK/rack/app/LightWidget.hpp>
#include <Rack-SDK/rack/app/RailWidget.hpp>
#include <Rack-SDK/rack/app/PortWidget.hpp>
#include <Rack-SDK/rack/app/CableWidget.hpp>
#include <Rack-SDK/rack/app/Switch.hpp>
#include <Rack-SDK/rack/app/RackScrollWidget.hpp>
#include <Rack-SDK/rack/app/Knob.hpp>
#include <Rack-SDK/rack/app/Scene.hpp>
#include <Rack-SDK/rack/app/RackWidget.hpp>
#include <Rack-SDK/rack/app/ParamWidget.hpp>
#include <Rack-SDK/rack/app/SvgKnob.hpp>
#include <Rack-SDK/rack/app/SvgPanel.hpp>
#include <Rack-SDK/rack/app/SvgPort.hpp>
#include <Rack-SDK/rack/app/SvgSwitch.hpp>
#include <Rack-SDK/rack/app/SvgScrew.hpp>
#include <Rack-SDK/rack/app/ModuleWidget.hpp>
#include <Rack-SDK/rack/app/SvgSlider.hpp>
#include <Rack-SDK/rack/app/SvgButton.hpp>

#include <Rack-SDK/rack/engine/Param.hpp>
#include <Rack-SDK/rack/engine/ParamHandle.hpp>
#include <Rack-SDK/rack/engine/LightInfo.hpp>
#include <Rack-SDK/rack/engine/PortInfo.hpp>
#include <Rack-SDK/rack/engine/Light.hpp>
#include <Rack-SDK/rack/engine/Cable.hpp>
#include <Rack-SDK/rack/engine/Port.hpp>
#include <Rack-SDK/rack/engine/ParamQuantity.hpp>
#include <Rack-SDK/rack/engine/Module.hpp>
#include <Rack-SDK/rack/engine/Engine.hpp>

#include <Rack-SDK/rack/plugin.hpp>
#include <Rack-SDK/rack/plugin/callbacks.hpp>

#include <Rack-SDK/rack/dsp/common.hpp>
#include <Rack-SDK/rack/dsp/window.hpp>
#include <Rack-SDK/rack/dsp/ode.hpp>
#include <Rack-SDK/rack/dsp/minblep.hpp>
#include <Rack-SDK/rack/dsp/fft.hpp>
#include <Rack-SDK/rack/dsp/ringbuffer.hpp>
#include <Rack-SDK/rack/dsp/resampler.hpp>
#include <Rack-SDK/rack/dsp/fir.hpp>
#include <Rack-SDK/rack/dsp/approx.hpp>
#include <Rack-SDK/rack/dsp/midi.hpp>
#include <Rack-SDK/rack/dsp/vumeter.hpp>
#include <Rack-SDK/rack/dsp/filter.hpp>
#include <Rack-SDK/rack/dsp/digital.hpp>
#include <Rack-SDK/rack/dsp/convert.hpp>

#include <Rack-SDK/rack/simd/Vector.hpp>
#include <Rack-SDK/rack/simd/functions.hpp>


namespace rack {


// Import some namespaces for convenience
using namespace logger;
using namespace math;
using namespace window;
using namespace widget;
using namespace ui;
using namespace app;
using plugin::Plugin;
using plugin::Model;
using namespace engine;
using namespace componentlibrary;


} // namespace rack
