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
    ptr->Base::foo();  // Will output Der::func()
    ref.Base::foo();   // Will output Der::func()
    std::cout << '\n';

    Base b = d; // up-casting a.k.a. object slicing. should be avoided
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
    void func(int) override {} // override specifier makes this function a virtual function as well
}; // class Der

class Dez : public Der {
public:
    void func(int) override {}
}; // class Dez
```

##### ###REMARK###
> C++ is a statically typed language but it also supports dynamic typing to a certain extent, for
> instance NVI (Non-Virtual Interface).

##### ###REMARK###
> Function Overriding doesn't get affected by access modifiers. Meaning a derived `class` can override
> a `private` or a `protected` `virtual` function of it's base `class`. This is because access control
> is a compile time mechanism. As an addition, from Assembly perspective, access control doesn't exist.


```cpp
class Base {
    public:
    virtual void func(uint16_t x = 10) { std::cout << "Base::func(uint16_t x) x = " << x << '\n'; }
}; // class Base

class Der : public Base {
    public:
    virtual void func(uint16_t x = 20) { std::cout << "Der::func(uint16_t x) x = " << x << '\n'; }
}; // class Der

int main() {
    Der   myder;
    Base& ref = myder;

    ref.func(); // will call the Der::func but will use the default argument of Base::func. This is
                // is because default argument does not relate to dynamic type, it is about static type.
}
```

##### ###REMARK###
> If the call that would normally trigger a Virtual Dispatch is made from the ctor of the base `class`
> then that call will be calling the funtion from the base `class`. This happens because of the way
> derived `class` instances created in C++. First the base `class` inside the derived `class` is created.
> Then the derived `class` will be created. Since the derived `class` instance doesn't exist yet, it's
> functions cannot be called. Compiler deliberately blocks this from happening as it would create a
> runtime error. Same rule and reason applies for the dtors as well.


#### Covariance
As stated before, for function override, both the overriding and the overridden functions must have;
1. Same return type
2. Same name
3. Same signature

For the return type, there is an exception. Overriding function can return a pointer to the derived
`class` instead of a pointer to the base `class`. Same rule applies for references as well.
e.g.
```cpp
class Base {
public:
    virtual Base* foo();
    virtual Base& bar();
}; // class Base

class Der : public Base {
public:
    Der* foo() override; // valid, even though return types don't match with the overridden function
    Der& bar() override; // valid, even though return types don't match with the overridden function
}; // class Der
```
#### Virtual Constructor Idiom (Clone Idiom)
There are three functions that cannot be `virtual`
1. Global Functions
2. Static Member Functions
3. Constructors


```cpp
class Car {
public:
    virtual Car* clone() = 0;
}; // class Car

class Merdedes : public Car {
public:
    Merdedes* clone() override { return new Merdedes(*this); }
}; // class Merdedes
```

To make the new instance of the `class` identical to the existing one, we call the copy constructor
by passing `*this` to the copy ctor. If we just want a new object without copying `return new Merdedes;`
would be enough. The name clone implies that it's identical copy is needed.

#### Virtual Destructor
```cpp
class Base {
public:
    ~Base() { std::cout << "Base dtor\n"; }
}; // class Base

class Der : public Base {
public:
    ~Der() { std::cout << "Der dtor\n"; }
}; // class Der

int main() {
    Base* baseptr = new Der;

    delete baseptr;
}
```
Becase `~Base()` is NOT overridden, this code snippet will have the following output
> Base dtor
```cpp
class Base {
public:
    virtual ~Base() { std::cout << "Base dtor\n"; }
}; // class Base

class Der : public Base {
public:
    ~Der() override { std::cout << "Der dtor\n"; }
}; // class Der

int main() {
    Base* baseptr = new Der;

    delete baseptr;
}
```
Because `~Base()` is overridden, this code snippet will have the following output
> Der dtor<br>
> Base dtor

##### ###REMARK###
> On the subject of destructors of polymorphic classes.<br>
> They are either;
> 1. public and virtual
> 2. protected and non-virtual

To override a global function, a function inside the base `class` with global parameters can be declared
and overridden.
e.g.
```cpp
#include <iostream>

class Car {
public:
    virtual ~Car()               = default;
    virtual void         start() = 0;
    friend std::ostream& operator<<(std::ostream& os, Car const& car);

private:
    virtual void print(std::ostream& os) const = 0;
}; // class Car

std::ostream& operator<<(std::ostream& os, Car const& car) {
    car.print(os);
    return os;
}

class Audi : public Car {
public:
    void start() override { std::cout << "Aubi started\n"; }

    void print(std::ostream& os) const override { os << "This is an Aubi\n"; }
}; // class Aubi
```
