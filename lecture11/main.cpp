// Lecture 11
#include <iostream>

class Myclass {
public:
    Myclass() { std::cout << "default constructor, this = " << this << '\n'; }

    ~Myclass() { std::cout << "destructor,   this = " << this << '\n'; }
}; // class Myclass

Myclass g1;
Myclass g2;
Myclass g3;

void foo() {
    std::cout << "foo starts here\n";
    static Myclass l1;
    std::cout << "foo is ending\n";
    return;
}

class yas {
public:
    yas() : _data{1}, _temp1{5}, _temp2(4), _debug(0) {}

    void print() const { std::cout << _debug++; }

    int         _data, _temp1, _temp2;
    mutable int _debug;
}; // class Yas

int main() {
    yas temp;
    std::cout << temp._data << ' ' << temp._temp1 << '\n';

    std::cout << "main starts here\n";
    foo();
    foo();
    foo();
    static Myclass sl1;
    std::cout << "&g1 = " << &g1 << '\n'
              << "&g2 = " << &g2 << '\n'
              << "&g3 = " << &g3 << '\n'
              << "main is ending\n";

    return 0;
}

Myclass g4;
