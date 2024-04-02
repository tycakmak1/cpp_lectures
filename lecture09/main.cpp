// Lecture 09
#include "foo.h"

#include <iostream>

void write();

int g1                  = 10;
int g2                  = 20;
constexpr int const* p1 = &g1;

class MyClass {
    int _x, _y;

public:
    void addresses() {
        std::cout << "&_a = " << &_a << "\n&_b = " << &_b << "\n&_x = " << &_x << "\n&_y = " << &_y
                  << '\n';
    }

    int _a, _b;
}; // class MyClass

int main() {
    MyClass mc;
    mc.addresses();
    std::cout << "main.cpp &foo = " << &foo << '\n';
    std::printf("%p\n", &foo);
    constexpr int x = 5;
    int arr[x];
    write();
    static int a            = 15;
    constexpr int const* p2 = &::g2;
    constexpr int const* p3 = &a;
    return 0;
}
