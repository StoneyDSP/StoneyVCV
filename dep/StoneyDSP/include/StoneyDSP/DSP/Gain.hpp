/***************************************************************************//**
 * @file simd.hpp
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
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

#pragma once

#define STONEYDSP_DSP_GAIN_HPP_INCLUDED 1

//==============================================================================

#ifndef STONEYDSP_CORE_HPP_INCLUDED
 #include "StoneyDSP/Core.hpp"
#endif

#ifndef STONEYDSP_SIMD_HPP_INCLUDED
 #include "StoneyDSP/SIMD.hpp"
#endif

//==============================================================================

namespace StoneyDSP {

namespace DSP {

template <typename T, typename S = T>
class Gain {
public:
    T currentGain;
    Gain();
    Gain(T newGain);
    ~Gain();
    const T& getGain() const;
    void setGain(const T& newGain);
    void processSample(S sample);
private:
    STONEYDSP_DECLARE_NON_COPYABLE(Gain)
    STONEYDSP_DECLARE_NON_MOVEABLE(Gain)
    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

}
}

template <typename T, typename S>
::StoneyDSP::DSP::Gain<T, S>::Gain()
 : currentGain((T)0.0)
{

}

template <typename T, typename S>
::StoneyDSP::DSP::Gain<T, S>::Gain(T newGain)
 : currentGain(newGain)
{

}

template <typename T, typename S>
::StoneyDSP::DSP::Gain<T, S>::~Gain()
{

}

template <typename T, typename S>
void ::StoneyDSP::DSP::Gain<T, S>::processSample(S sample)
{
    sample *= getGain();
}

template <class T, class S>
const T& ::StoneyDSP::DSP::Gain<T, S>::getGain() const
{
    return currentGain;
}

template <class T, class S>
void ::StoneyDSP::DSP::Gain<T, S>::setGain(const T& newGain)
{
    currentGain = newGain;
}

//==============================================================================

template class ::StoneyDSP::DSP::Gain<::StoneyDSP::double_t>;
template class ::StoneyDSP::DSP::Gain<::StoneyDSP::float_t>;
template class ::StoneyDSP::DSP::Gain<::StoneyDSP::SIMD::double_2>;
template class ::StoneyDSP::DSP::Gain<::StoneyDSP::SIMD::float_4>;

//==============================================================================
