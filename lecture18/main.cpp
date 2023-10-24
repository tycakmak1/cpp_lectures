// Lecture 18
#include "Date.h"
#include "MyClass.h"

#include <iostream>
#include <string>

class MyClass1
{
    class Nested
    {
        void foo(); // VALID
        void bar(); // VALID

    }; // class Nested

    // void Nested::bar() { return; } // INVALID

}; // class MyClass

void MyClass1::Nested::foo() { return; } // VALID

int main()
{
    MyClass mc1, mc2;
    mc1.foo();
    mc1.print();
    mc2.foo(0);
    mc2.print();
    mc1.foo(0);
    mc1.print();
    return 0;
}