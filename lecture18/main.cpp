// Lecture 18
#include <iostream>

class MyClass
{
    class Nested
    {
        void foo(); // VALID
        void bar(); // VALID

    }; // class Nested

    // void Nested::bar() { return; } // INVALID

}; // class MyClass

void MyClass::Nested::foo() { return; } // VALID

int main() { return 0; }