/*******************************************************************************
 * @file src/StoneyVCV/HP4.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_HP4)

//==============================================================================

#include <StoneyVCV/HP4.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

//==============================================================================

#include <array>

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP4 {

//==============================================================================

::rack::plugin::Model* modelHP4 = ::StoneyDSP::StoneyVCV::HP4::createModelHP4(
/** name        */"HP4",
/** description */"4hp Panel Spacer.",
/** manualUrl   */"https://stoneydsp.github.io/StoneyVCV/md_docs_2HP4.html",
/** hidden      */false
);

//==============================================================================

static const ::rack::math::Vec HP4Dimensions = (
    ::rack::window::mm2px(20.3199999965F), // 5.079999999F * 4.0F
    ::rack::window::mm2px(128.693333312F)
);

//==============================================================================

} // namespace HP4
} // namespace StoneyVCV
} // namespace StoneyDSP

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4Module::HP4Module()
{
    // Assertions
    DBG("Constructing StoneyVCV::HP4::HP4Module");
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxParams::NUM_PARAMS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxInputs::NUM_INPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxOutputs::NUM_OUTPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxLights::NUM_LIGHTS == 0U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    this->config(
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxParams::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxInputs::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxOutputs::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::HP4::HP4Module::IdxLights::NUM_LIGHTS
    );
}

::StoneyDSP::StoneyVCV::HP4::HP4Module::~HP4Module() noexcept
{
    DBG("Destroying StoneyVCV::HP4::HP4Module");
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4Widget::HP4Widget()
:   hp4WidgetFrameBuffer(new ::rack::widget::FramebufferWidget),
    panelBorder(
      ::rack::createWidget<::rack::app::PanelBorder>(
        ::rack::math::Vec(0.0F, 0.0F)
      )
    )
{
    // Assertions
    DBG("Constructing StoneyVCV::HP4::HP4Widget");
    assert(this->hp4WidgetFrameBuffer != nullptr);
    assert(this->panelBorder != nullptr);

    // Widgets
    this->hp4WidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->hp4WidgetFrameBuffer);

    // Border
    this->panelBorder->setSize(this->getSize());
    this->hp4WidgetFrameBuffer->addChild(this->panelBorder);
}

::StoneyDSP::StoneyVCV::HP4::HP4Widget::~HP4Widget() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::HP4::HP4Widget");
    assert(!this->parent);

    // Children
    this->panelBorder->clearChildren();
    this->hp4WidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::HP4::HP4Widget::step()
{
    const auto& size = this->getSize();

    this->panelBorder->setSize(size);
    this->hp4WidgetFrameBuffer->setSize(size);

    return ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::HP4::HP4Widget::draw(const ::StoneyDSP::StoneyVCV::HP4::HP4Widget::DrawArgs& args)
{
    const auto& minWidth = ::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH;
    const auto& minHeight = ::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT;
    const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& bgDark = ::StoneyDSP::StoneyVCV::Panels::bgDark;
    const auto& bgLight = ::StoneyDSP::StoneyVCV::Panels::bgLight;
    const auto& bgColor = ::rack::settings::preferDarkPanels ? bgDark : bgLight;
    const auto& bgGradientS0 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS0;
    const auto& bgGradientS1 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientDarkS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientLightS1;

    const auto& size = this->getSize();

    // Draw Themed BG
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg,
        /** x */0.0F,
        /** y */0.0F,
        /** w */size.x,
        /** h */size.y
        );
    ::nvgFillColor(args.vg, bgColor);
    ::nvgFill(args.vg);

    // Draw themed BG gradient
    const auto& bgGradient = ::nvgLinearGradient(args.vg,
        /** x  */size.x * 0.5,
        /** Y  */0.0F,
        /** w  */size.x * 0.5,
        /** h  */size.y,
        /** s1 */bgGradientS0,
        /** s2 */bgGradientS1
    );
    ::nvgBeginPath(args.vg);
    ::nvgRect(args.vg,
        /** x */0.0F,
        /** y */0.0F,
        /** w */size.x,
        /** h */size.y
        );
    ::nvgFillPaint(args.vg, bgGradient);
    ::nvgFill(args.vg);

    // Draw line L
    ::nvgBeginPath(args.vg);
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
    ::nvgMoveTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */minWidth + (minWidth * 0.5F));           /** 1.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */size.y - (minWidth + (minWidth * 0.5F)));/** 1.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line R
    ::nvgBeginPath(args.vg);
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
    ::nvgMoveTo(args.vg,
        /** x */size.x - (minWidth * 0.5F),              /** 0.5 screws left  */
        /** y */minWidth + (minWidth * 0.5F));           /** 1.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth * 0.5F),              /** 0.5 screws left  */
        /** y */size.y - (minWidth + (minWidth * 0.5F)));/** 1.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line T
    ::nvgBeginPath(args.vg);
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
    ::nvgMoveTo(args.vg,
        /** x */minWidth + (minWidth * 0.5F),            /** 1.5 screws right */
        /** y */minWidth * 0.5F);                        /** 0.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth + (minWidth * 0.5F)), /** 1.5 screws left  */
        /** y */minWidth * 0.5F);                        /** 0.5 screws down  */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    // Draw line B
    ::nvgBeginPath(args.vg);
    ::nvgLineCap(args.vg, NVG_ROUND);                    /** rounded lines */
    ::nvgLineJoin(args.vg, NVG_ROUND);                   /** set the line join to round corners */
    ::nvgMoveTo(args.vg,
        /** x */minWidth + (minWidth * 0.5F),            /** 1.5 screws right */
        /** y */size.y - (minWidth * 0.5F));             /** 0.5 screws up    */
    ::nvgLineTo(args.vg,
        /** x */size.x - (minWidth + (minWidth * 0.5F)), /** 1.5 screws left  */
        /** y */size.y - (minWidth * 0.5F));             /** 0.5 screws up    */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    ::StoneyDSP::ignoreUnused(minHeight);

    return ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::HP4ModuleWidget(::StoneyDSP::StoneyVCV::HP4::HP4Module* module)
:   size(
        60.0F,
        380.0F
    ),
    // Panel
    panel(::rack::createPanel<::rack::app::ThemedSvgPanel>(
        // Light-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/HP4-light.svg"
        ),
        // Dark-mode panel
        ::rack::asset::plugin(
            ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/HP4-dark.svg"
        )
    )),
    hp4Widget(::rack::createWidget<::StoneyDSP::StoneyVCV::HP4::HP4Widget>(::rack::math::Vec(0.0F, 0.0F))),
    hp4ModuleWidgetFrameBuffer(new ::rack::widget::FramebufferWidget),
    screwsPositions{
        ::rack::math::Vec( // top-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // top-right
            (this->size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)
        ),
        ::rack::math::Vec( // bottom-left
            (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F),
            (this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
        ::rack::math::Vec( // bottom-right
            (this->size.x - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F)),
            (this->size.y - (::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH * 0.5F))
        ),
    },
    screws{
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[2]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[3])
    },
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels)
{
    // Assertions
    DBG("Constructing StoneyVCV::HP4::HP4ModuleWidget");
    // assert(module != nullptr);
    assert(this->hp4Widget != nullptr);
    assert(this->hp4ModuleWidgetFrameBuffer != nullptr);
    assert(this->screws[0] != nullptr);
    assert(this->screws[1] != nullptr);
    assert(this->screws[2] != nullptr);
    assert(this->screws[3] != nullptr);
    assert(this->panel != nullptr);

    this->setModule(module);
    this->setSize(this->size);
    this->setPanel(this->panel);
    this->getPanel()->setSize(this->getSize());

    // Frame Buffer
    this->hp4ModuleWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->hp4ModuleWidgetFrameBuffer);

    // Widget
    this->hp4Widget->setSize(this->getSize());
    this->hp4ModuleWidgetFrameBuffer->addChild(this->hp4Widget);

    // Screws
    for(auto screw : this->screws) {
        this->addChild(screw);
    }

    assert(static_cast<unsigned int>(this->getSize().x) == 4U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().x) == 4U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::~HP4ModuleWidget() noexcept
{
    // Assertions
    DBG("Destroying StoneyVCV::HP4::HP4ModuleWidget");
    assert(!this->parent);

    // Children
    this->hp4Widget->clearChildren();
    this->hp4ModuleWidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget::step()
{
    if(this->lastPrefersDarkPanels != ::rack::settings::preferDarkPanels) {
        this->hp4ModuleWidgetFrameBuffer->setDirty();
        this->lastPrefersDarkPanels = ::rack::settings::preferDarkPanels;
    }

    return ::rack::Widget::step();
}

//==============================================================================

/**
 *
 */
::rack::plugin::Model* ::StoneyDSP::StoneyVCV::HP4::createModelHP4(
    ::std::string name,
    ::std::string description,
    ::std::string manualUrl,
    bool hidden
) noexcept(false) // STONEYDSP_NOEXCEPT(false)
{
    DBG("Creating StoneyVCV::HP4::modelHP4");

    ::rack::plugin::Model* modelHP4 = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::HP4::HP4Module,
        ::StoneyDSP::StoneyVCV::HP4::HP4ModuleWidget
    >("HP4");

    if(modelHP4 == nullptr)
        throw ::rack::Exception("createModelHP4 generated a nullptr");

    if(!description.empty())
        modelHP4->description = description;
    if(!manualUrl.empty())
        modelHP4->manualUrl = manualUrl;
    if(!name.empty())
        modelHP4->name = name;
    if(!hidden)
        modelHP4->hidden = hidden;

    return modelHP4;
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_HP4)

//==============================================================================
