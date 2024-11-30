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

::StoneyDSP::VCVRack::HP1::HP1()
{}

::StoneyDSP::VCVRack::HP1::~HP1()
{}

/**
 *
 */
::rack::plugin::Model* ::StoneyDSP::VCVRack::createHP1() // STONEYDSP_NOEXCEPT(false)
{

    ::rack::plugin::Model* modelHP1 = ::rack::createModel<::StoneyDSP::VCVRack::HP1, ::StoneyDSP::VCVRack::HP1ModuleWidget>("HP1");

    // STONEYDSP_THROW_IF_FAILED_VOID(modelHP1 == nullptr, bad_alloc);
    return modelHP1;
}

//==============================================================================

::rack::plugin::Model* modelHP1 = ::StoneyDSP::VCVRack::createHP1();

//==============================================================================
