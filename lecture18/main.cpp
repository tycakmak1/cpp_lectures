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
    MyClass mc;
    mc.print();
    return 0;
}