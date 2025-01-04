/*******************************************************************************
 * @file src/StoneyVCV/HP1.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 2.0.2
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_HP1)

//==============================================================================

#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/HP1.hpp>

//==============================================================================

#include <rack.hpp>
#include <StoneyDSP/Core.hpp>

#include <array>

//==============================================================================

namespace StoneyDSP {
namespace StoneyVCV {
namespace HP1 {

//==============================================================================

::rack::plugin::Model* modelHP1 = ::StoneyDSP::StoneyVCV::HP1::createModelHP1(
/** name        */"HP1",
/** description */"1hp Panel Spacer.",
/** manualUrl   */"https://stoneydsp.github.io/StoneyVCV/md_docs_2HP1.html",
/** hidden      */false
);

//==============================================================================

static const ::rack::math::Vec HP1Dimensions = (
    ::rack::window::mm2px(5.079999999F),
    ::rack::window::mm2px(128.693333312F)
);

//==============================================================================

} // namespace HP1
} // namespace StoneyVCV
} // namespace StoneyDSP

//==============================================================================

::StoneyDSP::StoneyVCV::HP1::HP1Module::HP1Module()
{
    // Assertions
    DBG("Constructing StoneyVCV::HP1::HP1Module");
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxParams::NUM_PARAMS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxInputs::NUM_INPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxOutputs::NUM_OUTPUTS == 0U);
    assert(::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxLights::NUM_LIGHTS == 0U);

    // Configure the number of Params, Outputs, Inputs, and Lights.
    this->config(
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxParams::NUM_PARAMS,
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxInputs::NUM_INPUTS,
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxOutputs::NUM_OUTPUTS,
        ::StoneyDSP::StoneyVCV::HP1::HP1Module::IdxLights::NUM_LIGHTS
    );
}

::StoneyDSP::StoneyVCV::HP1::HP1Module::~HP1Module()
{
    DBG("Destroying StoneyVCV::HP1::HP1Module");
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP1::HP1Widget::HP1Widget()
:   hp1WidgetFrameBuffer(new ::rack::widget::FramebufferWidget),
    panelBorder(
        ::rack::createWidget<::rack::app::PanelBorder>(
            ::rack::math::Vec(0.0F, 0.0F)
        )
    )
{
    // Assertions
    DBG("Constructing StoneyVCV::HP1::HP1Widget");
    assert(this->hp1WidgetFrameBuffer != nullptr);
    assert(this->panelBorder != nullptr);

    // Widget
    this->hp1WidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->hp1WidgetFrameBuffer);

    // Border
    this->panelBorder->setSize(this->getSize());
    this->hp1WidgetFrameBuffer->addChild(this->panelBorder);
}

::StoneyDSP::StoneyVCV::HP1::HP1Widget::~HP1Widget()
{
    // Assertions
    DBG("Destroying StoneyVCV::HP1::HP1Widget");
    assert(!this->parent);

    // Children
    this->panelBorder->clearChildren();
    this->hp1WidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::HP1::HP1Widget::step()
{
    const auto& size = this->getSize();

    this->panelBorder->setSize(size);
    this->hp1WidgetFrameBuffer->setSize(size);

    return ::rack::Widget::step();
}

void ::StoneyDSP::StoneyVCV::HP1::HP1Widget::draw(const ::StoneyDSP::StoneyVCV::HP1::HP1Widget::DrawArgs& args)
{
    const auto& minWidth = ::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH;
    const auto& minHeight = ::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT;
    const auto& borderColor = ::StoneyDSP::StoneyVCV::Panels::borderColor;
    const auto& bgBlack = ::StoneyDSP::StoneyVCV::Panels::bgBlack;
    const auto& bgWhite = ::StoneyDSP::StoneyVCV::Panels::bgWhite;
    const auto& bgColor = ::rack::settings::preferDarkPanels ? bgBlack : bgWhite;
    const auto& bgGradientS0 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS0 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS0;
    const auto& bgGradientS1 = ::rack::settings::preferDarkPanels ? ::StoneyDSP::StoneyVCV::Panels::bgGradientBlackS1 : ::StoneyDSP::StoneyVCV::Panels::bgGradientWhiteS1;

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

    // Draw line
    ::nvgBeginPath(args.vg);
    ::nvgMoveTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */minWidth + (minWidth * 0.5F));           /** 1.5 screws down  */
    ::nvgLineTo(args.vg,
        /** x */minWidth * 0.5F,                         /** 0.5 screws right */
        /** y */size.y - (minWidth + (minWidth * 0.5F)));/** 1.5 screws up  */
    ::nvgStrokeColor(args.vg, borderColor);
    ::nvgStrokeWidth(args.vg, 1.0F);
    ::nvgStroke(args.vg);

    ::StoneyDSP::ignoreUnused(minHeight);

    return ::rack::Widget::draw(args);
}

//==============================================================================

::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget::HP1ModuleWidget(::StoneyDSP::StoneyVCV::HP1::HP1Module* module)
:   size(
        15.0F,
        380.0F
    ),
    // Panel
    panel(
        ::rack::createPanel<::rack::app::ThemedSvgPanel>(
            // Light-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/HP1-light.svg"
            ),
            // Dark-mode panel
            ::rack::asset::plugin(
                ::StoneyDSP::StoneyVCV::Plugin::pluginInstance, "res/HP1-dark.svg"
            )
        )
    ),
    hp1Widget(::rack::createWidget<::StoneyDSP::StoneyVCV::HP1::HP1Widget>(::rack::math::Vec(0.0F, 0.0F))),
    hp1ModuleWidgetFrameBuffer(new ::rack::widget::FramebufferWidget),
    screwsPositions{
        ::rack::math::Vec( // Top
            this->size.x * 0.5F,
            this->size.x * 0.5F
        ),
        ::rack::math::Vec( // Bottom
            this->size.x * 0.5F,
            ::rack::RACK_GRID_HEIGHT - (this->size.x * 0.5F)
        )
    },
    screws{
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[0]),
        ::rack::createWidgetCentered<::rack::componentlibrary::ThemedScrew>(this->screwsPositions[1])
    },
    lastPrefersDarkPanels(::rack::settings::preferDarkPanels)
{
    // Assertions
    DBG("Constructing StoneyVCV::HP1::HP1ModuleWidget");
    // assert(module != nullptr);
    assert(this->hp1Widget != nullptr);
    assert(this->hp1ModuleWidgetFrameBuffer != nullptr);
    assert(this->screws[0] != nullptr);
    assert(this->screws[1] != nullptr);
    assert(this->panel != nullptr);

    this->setModule(module);
    this->setSize(this->size);
    this->setPanel(this->panel);
    this->getPanel()->setSize(this->getSize());

    // Frame Buffer
    this->hp1ModuleWidgetFrameBuffer->setSize(this->getSize());
    this->addChild(this->hp1ModuleWidgetFrameBuffer);

    // Widget
    this->hp1Widget->setSize(this->getSize());
    this->hp1ModuleWidgetFrameBuffer->addChild(this->hp1Widget);

    //
    for(auto screw : this->screws) {
        this->addChild(screw);
    }

    assert(static_cast<unsigned int>(this->getSize().x) == 1U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().x) == 1U * static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_WIDTH));
    assert(static_cast<unsigned int>(this->getPanel()->getSize().y) == static_cast<unsigned int>(::StoneyDSP::StoneyVCV::Panels::MIN_HEIGHT));
}

::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget::~HP1ModuleWidget()
{
    // Assertions
    DBG("Destroying StoneyVCV::HP1::HP1ModuleWidget");
    assert(!this->parent);

    // Children
    this->hp1Widget->clearChildren();
    this->hp1ModuleWidgetFrameBuffer->clearChildren();
    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget::step()
{
    if(this->lastPrefersDarkPanels != ::rack::settings::preferDarkPanels) {
        this->hp1ModuleWidgetFrameBuffer->setDirty();
        this->lastPrefersDarkPanels = ::rack::settings::preferDarkPanels;
    }

    return ::rack::Widget::step();
}

//==============================================================================

::rack::plugin::Model* ::StoneyDSP::StoneyVCV::HP1::createModelHP1(
    ::std::string name,
    ::std::string description,
    ::std::string manualUrl,
    bool hidden
) noexcept(false) // STONEYDSP_NOEXCEPT(false)
{
    DBG("Creating StoneyVCV::HP1::modelHP1");

    ::rack::plugin::Model* modelHP1 = ::rack::createModel<
        ::StoneyDSP::StoneyVCV::HP1::HP1Module,
        ::StoneyDSP::StoneyVCV::HP1::HP1ModuleWidget
    >("HP1");

    if(modelHP1 == nullptr)
        throw ::rack::Exception("createModelHP1 generated a nullptr");

    if(!description.empty())
        modelHP1->description = description;
    if(!manualUrl.empty())
        modelHP1->manualUrl = manualUrl;
    if(!name.empty())
        modelHP1->name = name;
    if(!hidden)
        modelHP1->hidden = hidden;

    return modelHP1;
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_HP1)

//==============================================================================
