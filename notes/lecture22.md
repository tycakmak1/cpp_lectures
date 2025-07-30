# LECTURE 22
### Runtime Polymorphism

##### ###REMARK###
> - If a `class` has a `virtual` or a pure `virtual` function, it's a polymorphic class.
> - If a `class` has or inherits a pure `virtual` function but does not define an implementation for
it, then that class is an abstract `class`. If a `class` is not abstract, then it is a concrete `class`.
Difference between abstract and concrete classes is that creating an instance from an abstract `class`
is not permitted. Trying to do so is a syntax error.


##### ###REMARK###
> For a function to be overridden both the overriding and the overridden fuction must have the same;
> 1. Return Type
> 2. Name
> 3. Signature

```cpp
class Base {
public:
    void foo() {}

    virtual void bar() {}
}; // class Base

class Der : public Base {
public:
    int foo() { return 5; } // not an override but valid
                            // having the same return type as Base::foo() would also be valid

    void bar() override {} // override
}; // class Der
```

Virtual functions are member functions whose behavior can be overridden in derived classes. As opposed
to non-virtual functions, the overriding behavior is preserved even if there is no compile-time information
about the actual type of the class. That is to say, if a derived class is handled using pointer or
reference to the base class, a call to an overridden virtual function would invoke the behaviour
defined in the derived class. Such a function call is known as virtual function call or virtual call.
Virtual function call is suppressed if the function is selected using qualified name lookup
(that is, if the function's name appears to the right of the scope resolution operator `::`)

```cpp
#include <iostream>

class Base {
public:
    void foo() { func(); }

    virtual void func() { std::cout << "Base::func()\n"; }
}; // class Base

class Der : public Base {
public:
    void func() override { std::cout << "Der::func()\n"; }
}; // class Der

int main() {
    Der   d;
    Base* ptr = &d;
    Base& ref = d;

    d.foo(); // Will output Der::func()
    std::cout << '\n';

    ptr->func(); // Will output Der::func()
    ref.func();  // Will output Der::func()
    ptr->foo();  // Will output Der::func()
    ref.foo();   // Will output Der::func()
    std::cout << '\n';

    ptr->Base::func(); // Will output Base::func()
    ref.Base::func();  // Will output Base::func()
    ptr->Base::foo();  // Will output Base::func()
    ref.Base::foo();   // Will output Base::func()
    std::cout << '\n';

    Base b = d; // up-casting or object slicing. should be avoided
    b.func();   // Will output Base::func()
    b.foo();    // Will output Base::func()
}
```

##### ###REMARK###
> - In a member function declaration or definition, `override` specifier ensures that the function is
>   `virtual` and is overriding a `virtual` function from a base class. The program is ill-formed
>   (a compile-time error is generated) if this is not true.
> - An overriding function that has the `override` specifier is itself also a `virtual` function.

```cpp
class Base {
public:
    virtual void func(int);
}; // class Base

class Der : public Base {
public:
    void func(int) override {} // override specifier makes this this function a virtual function as well
}; // class Der

class Dez : public Der {
public:
    void func(int) override {}
}; // class Dez
```

##### ###REMARK###
> A derived `class` can `override` the `virtual` function of a base `class` even if the said `virtual`
> function of the base `class` is a `private` or a `protected` member function.
