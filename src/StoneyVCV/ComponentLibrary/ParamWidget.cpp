/*******************************************************************************
 * @file src/StoneyVCV/ComponentLibrary/Widget.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2025 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================

#include <StoneyVCV/ComponentLibrary/ParamWidget.hpp>

//==============================================================================

#include <StoneyVCV.hpp>
#include <StoneyVCV/ComponentLibrary.hpp>
#include <StoneyVCV/ComponentLibrary/Widget.hpp>

//==============================================================================

#include <string>

//==============================================================================

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::ThemedParamPanelWidget()
:   ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget(),
    type(::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::Type::KNOB),
    fontSize(8.0F),
    labelText(""),
    prefersDarkPanelsPtr(nullptr)
{
    DBG("Constructing StoneyVCV::ComponentLibrary::ThemedParamPanelWidget");

    // Initial theme
    this->prefersDarkPanelsPtr = static_cast<const bool *>(&::rack::settings::preferDarkPanels);

    // Assertions...
    assert(this->prefersDarkPanelsPtr != nullptr);
}

::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::~ThemedParamPanelWidget() noexcept
{
    DBG("Destroying StoneyVCV::ComponentLibrary::ThemedParamPanelWidget");
    assert(!this->parent);

    this->clearChildren();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::step()
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::step();
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::draw(const ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::DrawArgs &args)
{
    return ::StoneyDSP::StoneyVCV::ComponentLibrary::TransparentWidget::draw(args);
}

const bool &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::getPrefersDarkPanels() const noexcept
{
    return *this->prefersDarkPanelsPtr;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::setFontSize(const float & newFontSize) noexcept
{
    this->fontSize = newFontSize;
}

const float &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::getFontSize() const noexcept
{
    return this->fontSize;
}

void ::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::setLabelText(const ::std::string & newLabelText) noexcept
{
    this->labelText = newLabelText;
}

const ::std::string &::StoneyDSP::StoneyVCV::ComponentLibrary::ThemedParamPanelWidget::getLabelText() const noexcept
{
    return this->labelText;
}

//==============================================================================

#endif // defined (STONEYVCV_BUILD_COMPONENTLIBRARY)

//==============================================================================
