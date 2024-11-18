#include "StoneyDSP/DSP/Oscillator.hpp"

template <class T>
StoneyDSP::DSP::Oscillator<T>::Oscillator()
{}

template <class T>
StoneyDSP::DSP::Oscillator<T>::~Oscillator()
{}

template struct StoneyDSP::DSP::Oscillator<float>;
template struct StoneyDSP::DSP::Oscillator<double>;
