// Lecture 15
#include "complex.h"

#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class MyClass {
public:
    MyClass() { std::cout << "MyClass default ctor called\n"; };

    MyClass(MyClass const& other) : _x{other._x}, _y{other._y} {
        std::cout << "copy ctor called\n";
    }

    MyClass(int x, int y) : _x{x}, _y{y} {}

    MyClass operator+(MyClass const& other) const& {
        std::cout << "inside the MyClass::operator+\n";
        return {_x + other._x, _y + other._y};
    }

    MyClass& operator=(MyClass const& other) {
        std::cout << "inside the MyClass::operator=\n";
        _x = other._x;
        _y = other._y;
        return *this;
    }

    void print() const& {
        std::cout << "const&  x = " << this->_x << " y = " << this->_y << '\n';
        return;
    }

    void print() const&& {
        std::cout << "const&& x = " << this->_x << " y = " << this->_y << '\n';
        return;
    }

private:
    int _x, _y;
}; // class MyClass

class Name {
public:
    Name(char const* p) : mp{new char[strlen(p) + 1]} { std::strcpy(mp, p); }

    void print() const { std::cout << mp << '\n'; }

    char& operator[](std::size_t idx) { return mp[idx]; }

    char const& operator[](std::size_t idx) const { return mp[idx]; }

private:
    char* mp;
}; // class Name

static MyClass stemp1;
MyClass        stemp2;

int main() {
    static MyClass stemp3;
    stemp1.print();
    stemp2.print();
    stemp3.print();
    std::array<int, 3> a1{};
    std::cout << a1[0] << '\n';
    std::cout << "Hello World!\n";
    MyClass m1{1, 2}, m2{3, 4};
    m1 + m2;
    m1.print();
    MyClass{3, 5}.print();
    MyClass{3, 5};
    complex::Complex c1{4, 5}, c2{1, 1};
    complex::Complex c3{c1 + c2};
    c3.print();
    (c1 + c2).print();
    (c1 * c2).print();
    operator<<(std::cout.operator<<(5), '\n');
    // cout << c3 << '\n';
    std::cout << "c3 = " << c3 << "\n++c3 = " << ++c3 << "\nc3++ = " << c3++;
    operator<<(std::cout, c3);
    complex::Complex c4 = c3++;
    operator<<(std::cout, c4);
    operator<<(std::cout, c3);

    std::vector<std::string>           svec  = {"john", "jack", "jane"};
    auto                               iter1 = svec.begin();
    std::vector<std::string>::iterator iter2 = svec.begin() + 1;
    std::cout << *iter1 << ' ' << *iter2 << ' ' << iter2->size() << '\n';
    int                a[5]{0, 1, 2, 3, 4};
    std::array<int, 5> b{0, 1, 2, 3, 4};

    return 0;
}
