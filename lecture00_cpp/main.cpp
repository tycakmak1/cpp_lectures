// this is a testing ground for C++
#include <iostream>

enum class Pos { OFF, ON, HOLD }; // /enum class Pos

int func(int a) { return 1; }

int func(int const a);

void f(void* p) { return; }

void bar(int const&&) { return; }

// int foo(int, int = 10);
// int foo(int = 5, int);

class Myclass {
public:
    static int tyc() { return 5; }

    static inline int _sta_x = tyc(); // VALID

}; // class Myclass

void bar() {
    std::printf("bar");
    return;
}

void foo() {
    bar();
    std::printf("foo");
}

int main() {
    int  a;
    int* p1{&a};
    f(p1);
    Pos mypos = Pos::ON;
    int ival  = static_cast<int>(mypos);

    std::cout << ival << '\n';

    if (true) {
        std::cout << "true\n";
    }
    foo();
    return 0;
}
