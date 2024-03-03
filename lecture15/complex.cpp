#include "complex.h"

namespace complex
{
Complex operator+(Complex const& z1, Complex const& z2) { return Complex{z1} += z2; }

Complex operator-(Complex const& z1, Complex const& z2) { return Complex{z1} -= z2; }

Complex operator*(Complex const& z1, Complex const& z2) { return Complex{z1} *= z2; }
} // namespace complex
