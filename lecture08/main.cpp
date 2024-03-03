// Lecture 08
#include <iostream>

void bar(int&) { std::cout << 3 << '\n'; }

void bar(int&&) { std::cout << 4 << '\n'; }

void foo(int& x)
{
    std::cout << 1 << '\n';
    bar(x);
}

void foo(int&& x)
{
    std::cout << 2 << '\n';
    bar(x);
}

void f(int&& x) { std::cout << x << "int&&\n"; }

static void f(int& x) { std::cout << x << "int&\n"; }

struct Tah;

Tah* f1() { return nullptr; }

int* f2() { return nullptr; }

int main()
{
    Tah* (*p_f1)() = f1;
    int* (*p_f2)() = f2;
    foo(10);
    std::cout << '\n';
    int x{10};
    foo(x);
    f(x);
    std::cout << '\n';
    int&& r = 10;
    std::cout << &r << '\n';
    std::cout << __cplusplus << '\n';
    std::cout << "x: " << x << '\n';
    std::cout << sizeof(x *= 5) << '\n';
    std::cout << "x: " << x << '\n';

    int a[5]{0, 1, 2, 3, 4};
    int b[5]{};
    int* p1_a = a;
    int* p1_b = b;
    int n     = 5;
    while (n--)
        *p1_b++ = *p1_a++;
    n = 5;
    while (n--)
        std::cout << "a[" << n << "] = " << *--p1_a << "\tb[" << n << "] = " << *--p1_b << '\n';
    for (int i{0}; i < 5; i++)
        std::cout << a[i] << ' ' << b[i] << '\n';

    return 0;
}
