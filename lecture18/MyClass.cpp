#include "MyClass.h"

#include "Date.h"

#include <iostream>
#include <string>

class MyClass::Pimple
{
public:
    Pimple() : _str{"Hello World!"}, _date{23, 10, 2023} {}

private:
    friend void MyClass::print() const;
    friend void MyClass::foo();
    std::string _str;
    Date _date;
}; // class MyClass::Pimple

MyClass::MyClass() : _p{new Pimple} {}

void MyClass::foo()
{
    _p->_str  = "Hello World\n";
    _p->_date = Date{23, 10, 2023};
}

void MyClass::print() const { std::cout << _p->_str << '\n' << _p->_date << '\n'; }