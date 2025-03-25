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

- When initializing a derived class instance, base class of that class will be initialized first.
```cpp
class Base {
public:
    Base() { std::cout << "Base default ctor called\n"; }

    ~Base() { std::cout << "Base dtor called\n"; }
}; // class Base

class Der : public Base {
public:
    Der() { std::cout << "Der default ctor called\n"; }

    ~Der() { std::cout << "Der dtor called\n"; }
}; // class Der

int main() {
    Base mybase;
    std::cout << '\n';
    Der myder;
    std::cout << "\n";
}
```
Will have the output of
> Base default ctor called
>
> Base default ctor called<br>
> Der default ctor called
>
> Der dtor called<br>
> Base dtor called<br>
> Base dtor called

- Even if the default constructor of the base class is not called inside the default constructor of
the derived class, the compiler will automatically do so.
- When composition and inheritance are used together, call order of the classes will be as follows;
    1. Default constructor of the base class
    2. Default constructor of the member class
    3. Default constructor of the derived class
    ```cpp
    class Member {
    public:
        Member() { std::cout << "Member default ctor\n"; }

        ~Member() { std::cout << "Member dtor\n"; }
    }; // class Member

    class Base {
    public:
        Base() { std::cout << "Base default ctor\n"; }

        ~Base() { std::cout << "Base dtor\n"; }
    }; // class Base

    class Der : public Base {
    public:
        Der() { std::cout << "Der default ctor\n"; }

        ~Der() { std::cout << "Der dtor\n"; }
    private:
        Member _x;
    }; // class Der

    int main() {
        Der myder;
        std::cout << "\n";
    }
    ```
    Will have the following output;
    > Base default ctor<br>
    > Member default ctor<br>
    > Der default ctor
    >
    > Der dtor<br>
    > Member dtor<br>
    > Base dtor

#### What Happens if the base class does not have a default constructor?
Calling the available constructors of the base class with values from the default constructor of the
derived class fixes this.
```cpp
class Base {
public:
    Base(int x) { std::cout << "Base(int x) x = " << x << "\n"; }

    ~Base() { std::cout << "Base dtor\n"; }
}; // class Base

class Der : public Base {
public:
    Der() : Base(0) { std::cout << "Der default ctor\n"; }

    ~Der() { std::cout << "Der dtor\n"; }
}; // class Der

int main() { Der myder; }
```
Will have the following outpu;
> Base(int x) x = 0<br>
> Member default ctor<br>
> Der default ctor
>
> Der dtor<br>
> Member dtor<br>
> Base dtor

##### ###REMARK###
> - Having member variables in the derived class to initialize the members of the base class is a
> common pattern.
> - Derived classes can call the constructors of their direct base class, but not the constructors
> of their indirect base class(es).
>    ```cpp
>    class Base {}; // class Base
>
>    class Der : public Base {
>    public:
>        Der() {}
>    }; // class Der
>
>    class Dez : public Der {
>    public:
>        Dez() : Der() {}        // VALID
>
>        Dez() : Base() {}       // INVALID
>    }; // class Dez
>    ```

### Special Member Functions in Inheritance
