/***************************************************************************//**
 * @file Oscillator.hpp
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 0.0.0
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#define STONEYDSP_DSP_OSCILLATOR_HPP_INCLUDED 1

//==============================================================================

#ifndef STONEYDSP_CORE_HPP_INCLUDED
 #include "StoneyDSP/Core.hpp"
#endif

#ifndef STONEYDSP_SIMD_HPP_INCLUDED
 #include "StoneyDSP/SIMD.hpp"
#endif

//==============================================================================

namespace StoneyDSP {
/** @addtogroup StoneyDSP
 *  @{
 */
namespace DSP {
/** @addtogroup DSP
 *  @{
 */

template <class T>
class PhaseDriver
{
public:
    T phase = 0.f;
	T freq = 0.f;
    // For optimizing in serial code
	int channels = 0;

    PhaseDriver() = default;
    ~PhaseDriver() = default;

private:
    STONEYDSP_DECLARE_NON_COPYABLE(PhaseDriver)
    STONEYDSP_DECLARE_NON_MOVEABLE(PhaseDriver)
    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

template class ::StoneyDSP::DSP::PhaseDriver<::StoneyDSP::double_t>;
template class ::StoneyDSP::DSP::PhaseDriver<::StoneyDSP::float_t>;
template class ::StoneyDSP::DSP::PhaseDriver<::StoneyDSP::SIMD::double_2>;
template class ::StoneyDSP::DSP::PhaseDriver<::StoneyDSP::SIMD::float_4>;

template <class T>
class Oscillator : StoneyDSP::DSP::PhaseDriver<T>
{
public:
    Oscillator() = default;
    ~Oscillator() = default;

private:
    STONEYDSP_DECLARE_NON_COPYABLE(Oscillator)
    STONEYDSP_DECLARE_NON_MOVEABLE(Oscillator)
    STONEYDSP_PREVENT_HEAP_ALLOCATION
};

template class ::StoneyDSP::DSP::Oscillator<::StoneyDSP::double_t>;
template class ::StoneyDSP::DSP::Oscillator<::StoneyDSP::float_t>;
template class ::StoneyDSP::DSP::Oscillator<::StoneyDSP::SIMD::double_2>;
template class ::StoneyDSP::DSP::Oscillator<::StoneyDSP::SIMD::float_4>;

  /// @} group DSP
} // namespace DSP

  /// @} group StoneyDSP
} // namespace StoneyDSP
