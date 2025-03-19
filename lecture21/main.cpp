// Lecture 21
#include <iostream>

class Base {}; // class Base

class Der : public Base {}; // class Der

class Dez : public Der {}; // class Dez

void foo(Base var) {}

void bar(Base* ptr) {}

void baz(Base& ref) {}

int main() {
    Base mybase;
    Der  myder;
    Dez  mydez;

    foo(mybase);
    foo(myder);
    foo(mydez);

    bar(&mybase);
    bar(&myder);
    bar(&mydez);

    baz(mybase);
    baz(myder);
    baz(mydez);
    return 0;
}
