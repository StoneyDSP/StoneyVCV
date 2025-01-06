/*******************************************************************************
 * @file src/StoneyVCV/plugin.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @copyright Copyright (c) 2024 MIT License
 *
 ******************************************************************************/

#if defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================

#include <StoneyVCV/plugin.hpp>

//==============================================================================

#include <StoneyVCV.hpp>

//==============================================================================

#include <rack.hpp>

//==============================================================================

namespace StoneyDSP {

//==============================================================================

namespace StoneyVCV {

//==============================================================================

namespace Plugin {

//==============================================================================

/**
 * @brief The `StoneyDSP` VCV Rack Plugin instance.
 */
::rack::plugin::Plugin* pluginInstance;

//==============================================================================

} // namespace Plugin

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

    DBG("Initializing plugin: StoneyVCV");

    ::StoneyDSP::StoneyVCV::Plugin::pluginInstance = p;

#ifdef STONEYVCV_BUILD_VCA
    p->addModel(::StoneyDSP::StoneyVCV::VCA::modelVCA);
#endif

#ifdef STONEYVCV_BUILD_HP4
    p->addModel(::StoneyDSP::StoneyVCV::HP4::modelHP4);
#endif

#ifdef STONEYVCV_BUILD_HP2
    p->addModel(::StoneyDSP::StoneyVCV::HP2::modelHP2);
#endif

#ifdef STONEYVCV_BUILD_HP1
    p->addModel(::StoneyDSP::StoneyVCV::HP1::modelHP1);
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

#endif // defined (STONEYVCV_BUILD_MODULES)

//==============================================================================

#endif // defined (STONEYVCV_BUILD_PLUGIN)

//==============================================================================
