#include "Myclass.h"

#include "Date.h"

#include <iostream>
#include <string>

class Myclass::Pimple {
public:
    Pimple();
    void foo();

private:
    friend void Myclass::print() const;
    friend void Myclass::foo();
    std::string _str;
    Date        _date;
}; // class Myclass::Pimple

Myclass::Myclass() : _p{new Pimple} {}

Myclass::Pimple::Pimple() : _str{"Hello World!"}, _date{23, 10, 2023} {}

void Myclass::foo() {
    _p->_str  = "Hello World!, Myclass::foo()";
    _p->_date = Date{23, 10, 2023};
}

void Myclass::foo(int) { _p->foo(); }

void Myclass::print() const { std::cout << _p->_str << ", " << _p->_date << '\n'; }

void Myclass::Pimple::foo() {
    _str  = "Hello World!, Myclass::Pimple::foo()";
    _date = Date{23, 10, 2023};
}
