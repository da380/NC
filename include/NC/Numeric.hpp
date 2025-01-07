#pragma once

#include <complex>
#include <concepts>

namespace NC {

// Concept for integral types.
template <typename T>
concept Integral = std::integral<T>;

// Concept for floating point types.
template <typename T>
concept Real = std::floating_point<T>;

// Concept for complex types.
template <typename T> struct ComplexType : public std::false_type {};

template <typename T>
struct ComplexType<std::complex<T>> : public std::bool_constant<NC::Real<T>> {};

template <typename T>
concept Complex = ComplexType<T>::value;

// Extract base type from a complex type. If the type is not
// complex the input type is returned.
template <typename T>
  requires Real<T> or Complex<T>
struct RemoveComplexHelper {
  using value_type = T;
};

template <typename T>
  requires Real<T> or Complex<T>
struct RemoveComplexHelper<std::complex<T>> {
  using value_type = T;
};

template <typename T>
  requires Real<T> or Complex<T>
using RemoveComplex = typename RemoveComplexHelper<T>::value_type;

// Concept for real or complex numbers.
template <typename T>
concept RealOrComplex = Real<T> or Complex<T>;

// Concept for Numeric types, i.e., integers, reals or complex numbers.
template <typename T>
concept Numeric = Integral<T> or RealOrComplex<T>;

} // namespace NC