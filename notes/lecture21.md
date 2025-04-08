# LECTURE 21
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
> - `private` members of a class is accessible only to the class itself, if there are no `friend`
declarations.
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

#### Copy Constructor
Since derived classes can call the special members of their direct base classes, Copy Constructor
will do the same.

```cpp
class Base {
    public:
    Base() { std::cout << "Base default ctor\n"; }

    Base(Base const& other) { std::cout << "Base copy ctor\n"; }

    Base& operator=(Base const& other) {
        std::cout << "Base copy assignment\n";
        return *this;
    }

    Base(Base&& other) { std::cout << "Base move ctor\n"; }

    Base& operator=(Base&& other) {
        std::cout << "Base move assignement\n";
        return *this;
    }
}; // class Base

class Der : public Base {
    public:
    Der() { std::cout << "Der default ctor\n"; }

    Der(Der const& other) : Base(other) { std::cout << "Der copy ctor\n"; }

    Der& operator=(Der const& other) {
        std::cout << "Der copy assignment\n";
        Base::operator=(other);
        return *this;
    }

    Der(Der&& other) : Base(std::move(other)) { std::cout << "Der move ctor\n"; }

    Der& operator=(Der&& other) {
        std::cout << "Der move assignment\n";
        Base::operator=(std::move(other));
        return *this;
    }
}; // class Der

int main() {
    Der d1;
    Der d2 = d1;
}
```
The code block above will have the following output
> Base default ctor<br>
> Der default ctor<br>
> Der copy ctor<br>
> Base copy ctor

This behaviour wil be observed with all of the special member functions (Copy Members, Move Members).

##### ###REMARK###
> This behaviour will also be observed if the functions are defined by the compiler.<br>

### `using` Declarations Inside a Class
In a scenario where there are two member functions with the same name, one in the base class the
other in the derived class, how do we make sure we call the one from the base class?
```cpp
class Base {
public:
    void func(int);
}; // class Base

class Der : public Base {
public:
    void func(double);
}; // class Der

int main() {
    Der d;
    d.func(12);
    d.func(12.5);
}
```

In the code above, both calls will go to the ```void Der::func(double)``` inside the `Der` class.
To make sure that the `d.func(12);` calls the `void Base::func(int)`, we can either use scope
resolution operator `::` or we can inject the name `Base::func` inside the derived class.
```cpp
class Base {
public:
    void func(int);
}; // class Base

class Der : public Base {
public:
    using Base::func;
    void func(double);
}; // class Der

int main() {
    Der d;
    d.func(12);
    d.func(12.5);
}
```
Now `d.func(12)` will call the `void Base::func(int)` and `d.func(12.5)` will call the
`void Der::func(double)`

This kind of `using` declaration can also be used to access protected members of the base class via
client code of the derived class.
```cpp
class Base {
public:
protected:
    void func(int);
}; // class Base

class Der : public Base {
public:
    using Base::func;
}; // class Der

class Dez : public Base {
    using Base::func;
}; // class Dez

int main() {
    Der d1;
    d1.func(5);
    Dez d2;
    // d2.func(5);  // INVALID because of access modifiers
}
```

This `using` declaration feature existed before the modern C++, but with modern C++ it gained an
important addition, Inherited Constructor.

#### Inherited Constructor
```cpp
class Base {
public:
    Base(int);
    Base(int, int);
    Base(double);
}; // class Base

class Der : public Base {
public:
    using Base::Base;   // With this declaration, all constructors of the base class will
                        // be inherited by Der.
}; // class Der
```

##### ###REMARK###
> `using` declaration can be used for data members as well.

### Runtime Polymorphism
Member functions of a base class can have one of the three possible categories.<br>
1. Said function can provide the derived classes with both an interface and an implementation.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
2. Said function can provide the derived classes with both an interface and a default
implementation.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;i.e. `override`
3. Said function can provide the derived classes only with an interface.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;i.e. `override`
```cpp
class Airplane {
public:
    void take_off();            // 1st category
    virtual void fly();         // 2nd category
    virtual void land() = 0;    // 3rd category, also called pure virtual function
}; // class Airplane
```
