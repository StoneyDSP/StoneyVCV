/***************************************************************************//**
 * @file HP1.cpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 0.0.0
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * therights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/orsell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************************/

//==============================================================================

#include "HP1.hpp"

//==============================================================================

::StoneyDSP::VCVRack::HP1Module::HP1Module()
{
    // Configure the number of Params, Outputs, Inputs, and Lights.
    config(
        ::StoneyDSP::VCVRack::HP1Module::PARAMS_LEN,   // numParams
        ::StoneyDSP::VCVRack::HP1Module::INPUTS_LEN,   // numInputs
        ::StoneyDSP::VCVRack::HP1Module::OUTPUTS_LEN,  // numOutputs
        ::StoneyDSP::VCVRack::HP1Module::LIGHTS_LEN    // numLights
    );
}

::StoneyDSP::VCVRack::HP1Module::~HP1Module()
{}

::StoneyDSP::VCVRack::HP1ModuleWidget::HP1ModuleWidget(::StoneyDSP::VCVRack::HP1Module* module)
{
    setModule(module);
    setPanel(::rack::createPanel(
        ::rack::asset::plugin(::StoneyDSP::VCVRack::pluginInstance, "res/HP1-light.svg"),
        ::rack::asset::plugin(::StoneyDSP::VCVRack::pluginInstance, "res/HP1-dark.svg")
    ));
}

::StoneyDSP::VCVRack::HP1ModuleWidget::~HP1ModuleWidget()
{}

/**
 *
 */
::rack::plugin::Model* ::StoneyDSP::VCVRack::createHP1() // STONEYDSP_NOEXCEPT(false)
{

    ::rack::plugin::Model* modelHP1 = ::rack::createModel<
        ::StoneyDSP::VCVRack::HP1Module,
        ::StoneyDSP::VCVRack::HP1ModuleWidget
    >("HP1");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP1 == nullptr, bad_alloc);
    return modelHP1;
}

//==============================================================================

namespace StoneyDSP {

namespace VCVRack {

::rack::plugin::Model* modelHP1 = ::StoneyDSP::VCVRack::createHP1();

}

}

//==============================================================================
