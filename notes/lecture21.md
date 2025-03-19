# LECTURE 20
## Inheritance
The term inheritance means more in C++ than it does in OOP.

### `public` Inheritance
This is the 'is a' relationship inheritance from OOP, e.g. a Mercedes 'is a' Car. So Car is the base
class and Mercedes is the derived class.
```cpp
class Base {
public:
    void f1();
    void f2();
}; // class Base

// public inheritance
class Derived1 : public Base {
public:
    void f3();
}; // class Derived1

// private inheritance
class Derived2 : private Base {
public:
    void f3();
}; // class Derived2

// protected inheritance
class Derived3 : protected Base {
public:
    void f3();
}; // class Derived3
```
- Base `class` must be a complete type.
- If the type of derivation is not specified the default type for derivation is `private`, if the
derived type is a `class`.<br>If the derived type is `struct` then the default type for derivation
is `public`.
- Type of the inheritance does not mean that only members in that section of the base `class` will
be inherited. All the members of the base `class` will be inherited. But this does not allow the
derived `class` to access to the private members<br>of the base `class`.
```cpp
class Base {
public:
    int foo;
}; // class Base

class Der : public Base {
public:
    void foo(int, int);
}; // class Der

int main() {
    Der myder;

    myder.foo(12, 24);  // since foo inside the Der class masks the foo
    myder.Base::foo(12);// this is how we access foo inside the Base class
}
```
##### ###REMARK###
> - `public` members of a class is accessible to everyone.
> - `protected` members of a class is accessible to derived classes and the class itself.
> - `private` members of a class is accessible only to the class itself, if there are no `friend` declarations.
> ```cpp
> class Base {
> public:
>     void foo() {}
>
> protected:
>     void bar() {}
>
> private:
>     void baz() {}
> };
>
> class Der : public Base {
>     void func() {
>         foo();    // VALID
>         bar();    // VALID
>     }
> };
> ```

### Upcasting
Castings that are done from derived class to the base class are called upcasting (also called slicing).
Slicing is where you assign an object of a derived class to an instance of a base class, thereby
losing part of the information. Some of it is sliced away.<br>
When object slicing (upcasting) is done, compiler uses the base class that is inside the derived class.
This means, a function that takes an instance of a base class, can also take an instance of the derived class.
```cpp
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

    foo(mybase);  // VALID, will call foo(Base var)
    foo(myder);   // VALID, will call foo(Base var)
    foo(mydez);   // VALID, will call foo(Base var)

    bar(&mybase); // VALID, will call bar(Base* ptr)
    bar(&myder);  // VALID, will call bar(Base* ptr)
    bar(&mydez);  // VALID, will call bar(Base* ptr)

    baz(mybase);  // VALID, will call baz(Base& ref)
    baz(myder);   // VALID, will call baz(Base& ref)
    baz(mydez);   // VALID, will call baz(Base& ref)

    return 0;
}
```

##### ###REMARK###
> Downcasting is the opposite of upcasting. It is the casting from a base class to a derived class.
