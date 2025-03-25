// Lecture 21
#include <iostream>

class Member {
public:
    Member() { std::cout << "Member default ctor\n"; }

    ~Member() { std::cout << "Member dtor\n"; }
}; // class Member

class Base {
public:
    Base(int x) { std::cout << "Base(int x) x = " << x << "\n"; }

    ~Base() { std::cout << "Base dtor\n"; }
}; // class Base

class Der : public Base {
public:
    Der() : Base(0) { std::cout << "Der default ctor\n"; }

    ~Der() { std::cout << "Der dtor\n"; }

private:
    Member _x;
}; // class Der

class Dez : public Der {
public:
    Dez() { std::cout << "Dez created\n"; }
}; // class Dez

void foo(Base var) {}

void bar(Base* ptr) {}

void baz(Base& ref) {}

int main() {
    // Base mybase;
    // std::cout << "\n";
    Der myder;
    std::cout << "\n";

    // Dez  mydez;

    // foo(mybase);
    // foo(myder);
    // foo(mydez);

    // bar(&mybase);
    // bar(&myder);
    // bar(&mydez);

    // baz(mybase);
    // baz(myder);
    // baz(mydez);
    return 0;
}
