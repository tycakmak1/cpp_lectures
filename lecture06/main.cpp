// Lecture 06
#include "test.h"

#include <iostream>

enum Color : uint8_t
{
    Black = 0,
    White = 1,
    Blue  = 2
}; // enum Color

enum class Colors : uint8_t
{
    red    = 0,
    black  = 1,
    yellow = 2
}; // enum class Colors

int g = 10;

void func(int a = g++)
{
    std::cout << "func called, a = " << a << '\n';
    return;
}

void func_test(int a, int b, int c = 10);
void func_test(int a, int b = 5, int c);

int main()
{
    int x1 = -5;
    int x2 = 3;
    std::cout << static_cast<decltype(10.)>(x1 * x2) << '\n';
    decltype(x1 + 5) z = 10;
    auto *x = &x1, y = x2;
    decltype(x2) a;         // here x2 is an identifier, so decltype(x2) = int
    decltype((x2)) b  = x2; // here (x)2 is an L val. expre., so decltype((x2)) = int&
    unsigned short x3 = x1;
    std::cout << x1 << ' ' << x3 << '\n';

    int const t1{};
    decltype(t1) t2 = 10;

    std::cout << "g = " << g << '\n';
    func();
    g = 15;
    std::cout << "g = " << g << '\n';
    func();

    func_test(1, 2);

    return 0;
}
