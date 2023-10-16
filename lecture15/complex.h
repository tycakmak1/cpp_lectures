#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

namespace complex
{
class Complex
{
public:
    Complex() : _x{ 0 }, _y{ 0 } {}

    Complex(double x, double y) : _x{ x }, _y{ y } {}

    Complex(Complex const& other) : _x{ other._x }, _y{ other._y } {}

    Complex operator=(Complex const& z)
    {
        _x = z._x;
        _y = z._y;
        return *this;
    }

    Complex& operator++()
    {
        ++_x;
        ++_y;
        return *this;
    }

    Complex operator++(int)
    {
        Complex return_val{ *this };
        ++*this;
        return return_val;
    }

    Complex operator--()
    {
        --_x;
        --_y;
        return *this;
    }

    Complex operator--(int)
    {
        Complex return_val{ *this };
        --*this;
        return return_val;
    }

    Complex& operator+=(Complex const& other)
    {
        _x += other._x;
        _y += other._y;
        return *this;
    }

    Complex& operator-=(Complex const& other)
    {
        _x -= other._x;
        _y -= other._y;
        return *this;
    }

    Complex& operator*=(Complex const& other)
    {
        Complex tmp{ *this };
        _x = tmp._x * other._x - tmp._y * other._y;
        _y = tmp._x * other._y + tmp._y * other._x;
        return *this;
    }

    void print() const&
    {
        std::cout << "const&  x = " << _x << " y = " << _y << '\n';
        return;
    }

    void print() const&&
    {
        std::cout << "const&& x = " << _x << " y = " << _y << '\n';
        return;
    }

    friend std::ostream& operator<<(std::ostream& out, Complex const& z) // usually called inserter
    {
        return out << "z = (" << z._x << ", " << z._y << ")\n";
    }

    friend std::istream& operator>>(std::istream& in, Complex& z) // usually called extractor
    {
        return in >> z._x >> z._y;
    }

private:
    double _x, _y;
}; // class Complex

Complex operator*(Complex const&, Complex const&);
Complex operator-(Complex const&, Complex const&);
Complex operator+(Complex const&, Complex const&);
} // namespace complex
#endif // COMPLEX_H
