// Lecture 18
#include "Date.h"
#include "Myclass.h"

#include <iostream>
#include <string>

class MyClass1 {
    class Nested {
        void foo(); // VALID
        void bar(); // VALID

    }; // class Nested

    // void Nested::bar() { return; } // INVALID

}; // class Myclass

void MyClass1::Nested::foo() { return; } // VALID

class Member {
public:
    Member() { std::cout << "Member default constructor\n"; }

    Member(Member const&) { std::cout << "Member copy constructor\n"; }
}; // class Member

class A {
public:
    A() = default;

    A(A const&) {}

private:
    Member _x;
}; // class A

class B {
public:
    B() : _x() {}

private:
    Member _x;
}; // class B

int main() {
    Myclass mc1, mc2;
    mc1.foo();
    mc1.print();
    mc2.foo(0);
    mc2.print();
    mc1.foo(0);
    mc1.print();

    A a1;
    A a2{a1};

    B b1;
    B b2{b1};
    return 0;
}
