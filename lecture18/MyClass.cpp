#include "MyClass.h"

#include "Date.h"

#include <iostream>
#include <string>

class MyClass::Pimple
{
public:
    Pimple();
    void foo();

private:
    friend void MyClass::print() const;
    friend void MyClass::foo();
    std::string _str;
    Date _date;
}; // class MyClass::Pimple

MyClass::MyClass() : _p{new Pimple} {}

MyClass::Pimple::Pimple() : _str{"Hello World!"}, _date{23, 10, 2023} {}

void MyClass::foo()
{
    _p->_str  = "Hello World!, MyClass::foo()";
    _p->_date = Date{23, 10, 2023};
}

void MyClass::foo(int) { _p->foo(); }

void MyClass::print() const { std::cout << _p->_str << ", " << _p->_date << '\n'; }

void MyClass::Pimple::foo()
{
    _str  = "Hello World!, MyClass::Pimple::foo()";
    _date = Date{23, 10, 2023};
}
