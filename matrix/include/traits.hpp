#pragma once

#include <complex>
#include <type_traits>

template<typename T>
struct is_complex
{
    static const bool value = false;
};

template<>
struct is_complex<std::complex<float>>
{
    static const bool value = true;
};

template<>
struct is_complex<std::complex<double>>
{
    static const bool value = true;
};

template<typename T>
struct is_complex_v
{
    static const bool value = is_complex<T>::value;
};
