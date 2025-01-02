# LECTURE 16
## Operator Overloading
### Overloading `*` and `->` Operators
`->` operator is a binary operator but it is overloaded as if it's a unary operator.
```cpp
class A {
public:
    void foo();

    void bar();
}; // class A

class Ptr {
public:
    A& operator*();

    A* operator->();
}; // class Ptr

int main() {
    Ptr p;
    *p;
    p->foo();              // These two lines are same.
    p.operator->()->foo(); // These two lines are same.
}

class Counter {
public:
    explicit Counter(int x = 0) : _val{x} {
        std::cout << "a Counter object created   at " << this << " with value " << _val << '\n';
    }

    ~Counter() {
        std::cout << "a Counter object destroyed at " << this << " with value " << _val << '\n';
    }

    Counter& operator++() {
        ++_val;
        return *this;
    }

    Counter operator++(int) {
        Counter retval = *this;
        ++*this;
        return retval;
    }

    int get() const { return _val; }

    friend std::ostream& operator<<(std::ostream& os, Counter const& c) { return os << c._val; }

    void set(int x) { _val = x; }

private:
    int _val;
}; // class Counter

class CounterPtr {
public:
    CounterPtr() : _ptr{nullptr} {}

    CounterPtr(Counter* p) : _ptr{p} {}

    ~CounterPtr() {
        if (ptr)
            delete _ptr;
    }

    CounterPtr(CounterPtr const&) = delete;

    CounterPtr& operator=(CounterPtr const&) = delete;

    CounterPtr(CounterPtr&& other) : _ptr{other._ptr} { other._ptr = nullptr; }

    Counter& operator*() { return *_ptr; }

    Counter* operator->() { return _ptr; }

private:
    Counter* _ptr;
}; // class CounterPtr

int main() {
    std::cout << "main started\n";
    {
        CounterPtr p = new Counter{35};
        ++*p;
        p->get();
        p->operator++();
    }
    std::cout << "main ends here\n";
    return 0;
}
```

This is fine but this solution requires us to write a pointer class for every object we
define. Instead we use generic programming.
```cpp
class Counter {}; // Same as above example.

template<typename T>
class SmartPtr {
public:
    SmartPtr() : _ptr{nullptr} {}

    SmartPtr(T* p) : _ptr{p} {}

    ~SmartPtr() {
        if (ptr)
            delete _ptr;
    }

    SmartPtr(SmartPtr const&) = delete;

    SmartPtr& operator=(SmartPtr const&) = delete;

    SmartPtr(SmartPtr&& other) : _ptr{other._ptr} { other._ptr = nullptr; }

    T& operator*() { return *_ptr; }

    T* operator->() { return _ptr; }

private:
    T* _ptr;
}; // class SmartPtr

int main() {
    std::cout << "main started\n";
    {
        CounterPtr p1 = new Counter{35};
        ++*p1;
        std::cout << p1->get() << '\n';
        p1->operator++();
    }
    std::cout << "\n\n";
    {
        SmartPtr<Counter> p2 = new Counter{38};
        ++*p2;
        std::cout << p2->get() << '\n';
        p2->operator++();
    }
    std::cout << "main ends here\n";
    return 0;
}
```
Template is a powerful tool of C++.

```cpp
class A {
public:
    void foo();
    void bar();
}; // class A

class Ptr {
public:
    A& operator*();
    A* operator->();
}; // class Ptr

int main() {
    Ptr p;
    p.operator->()->foo();        // VALID,   because p.operator->() yields A*.
    p.operator->()->operator->(); // INVALID, because p.operator->() yields A*.
}
```
### Function Call Operator Overloading
`()` is one of the operators that are most widely overloaded. It is widely used in generic programming. The necessity of this
operator overload will be inspected under Generic Programming (a topic for later).

```cpp
func();
```
Here `func` can be one of the following;
|                                                                    |C           |C++|
|---|:-:|:-:|
|`func` can be a function name                                         |yes         |yes|
|`func` can be a function pointer                                      |yes         |yes|
|`func` can be a functional macro(almost never used in C++)            |yes         |yes|
|`func` can be an object instance which overloaded the () operator     |no          |yes|

Classes that have overloded the `()` operator are called
1. Functor Class
2. Function Object Class

##### ###REMARK###
> Operator functions cannot take default arguments, except the `operator()`.
> ```cpp
> class Myclass {
> public:
>     int operator()(int x = 10) {
>         std::cout << "Myclass::operator()(int x = 10) called.\n";
>         return x * x;
>     }
> }; // class Myclass
>
> int main() {
>     Myclass test;
>     auto    val1 = test();             // val1 = 100
>     auto    val2 = test(5);            // val2 = 25
>     auto    val3 = text.operator()(6); // val3 = 36
> }
> ```
> Since operator functions are also functions, they can be overloaded.

### Typecasting Operator Overloading
```cpp
class Myclass {
public:
    operator double() const { return _x; }

private:
    double _x;
}; // class Myclass
```
- Notice that we do not specify a return value, but we actually do. Since writing it as `double operator double()` would be
    meaningless.
- This is a user defined conversion (UDC). Compiler can perform this implicitly when it is necessary, to prevent that we declare it
    using `explicit` keyword.
- Without this definition, we cannot perform explicit typecasting, or the compiler cannot perform implicit typecasting.
- Can be overloaded.
- Target type can be another class.
- Since they do not change the instance, it is a good practice to define them as const member functions.
- Can be called by it's name,
    ```cpp
    int x = m.operator int();
    ```
- It provides conversion from the class to a specified type. Not the other way around, that is achieved with conversion constructors.

##### ###REMARK###
> If a conversion is done by one of the following sequences, than it is done by the compiler implicitly.
> 1. Standard Conversion + UDC
> 2. UDC + SC<br>
> #### BUT NEVER UDC + UDC.

# ###IMPORTANT###
> There is a special case for `operator bool()`, even if the operator bool is defined `explicit`, the compiler will perform implicit
> typecasting in a `boolean` context.
> ```cpp
> class Myclass {
> public:
>     operator bool() const {}
> }; // class Myclass
>
> int main() {
>     Myclass m;
>     int x = m;      // This is VALID because UDC + SC, Myclass to bool and bool to int.
>     if(m) {}        // This is VALID because Myclass has bool typecasting operator.
> }
> ```
> If `operator bool()` were to be defined as `explicit`, then
> ```cpp
> class Myclass {
> public:
>     explicit operator bool() const {}
> }; // class Myclass
> 
> int main() {
>     Myclass m;
>     int x = m;    // This becomes INVALID because compiler cannot implicitly typecast to bool.
>     if(m) {}      // This is still VALID.
> }
> ```

###### ###REMARK###
Operator overloading mechanism can also be used for enum types, but since enums are not classes
their operator functions must be global operator functions.
```cpp
enum class Weekday : int {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
}; // enum class Weekday

Weekday& operator++(Weekday& wd, int) {
    //.. code goes here
    return wd;
}

Weekday operator++(Weekday& wd) {
    Weekday ret_val{wd};
    //.. code goes here
    return ret_val;
}

int main() {
    Weekday wd{Weekday::MONDAY};
    ++wd;
    wd++;
}
```

## Namespaces
- They exist to prevent name clashing.
    ```cpp
    namespace ns1 {
    int x = 5;
    } // namespace ns1

    namespace ns2 {
    void x();
    } // namespace ns2
    ```
- Scope resolution operator is used to access the names inside of a namespace.
    ```cpp
    namespace ns {
    int x = 5;
    } // namespace ns

    int a = x;      // This is INVALID.
    int b = ns::x;  // This is VALID.
    ```
- It is not neccessary to use qualified expressions to acces to a name inside of a namespace, from that same namespace.
    ```cpp
    namespace ns {
    int x = 5;
    int a = x;      // This is VALID.
    int b = ns::x;  // This is also VALID, but unnecessary.
    }
    ```
- Can be nested.
    ```cpp
    namespace ns1 {
    namespace ns2 {
    int x;
    } // namespace ns2
    } // namespace ns1
    ns1::ns2::x;    // To access the x inside the ns2 namespace which is inside the ns1 namespace.
    ```
- They are still part of the global scope.
- They do not have access modifiers.
- They can only be in global scope or in another namespace.
- Namespace declarations are cumulative. Thanks to this we can have multiple header files using the same namespace
    (`std::vector`, `std::string`, etc).
    ```cpp
    namespace ns {
    int a, b, c;
    } // namespace ns

    namespace ns
    {
    double x, y;
    } // namespace ns
    ```
    Is the same with
    ```cpp
    namespace ns1 {
    int a, b, c;
    double x, y;
    } // namespace ns
    ```
    This can be extended through different files i.e. a namespace can start in the header file and continue in the implementation
    (.cpp) file. This let's us access the names in the namespace without using qualifiers.
- In functions that belong to a namespace, after the qualifier of the function name, it is not necessary to use qualifiers for other
    names in that namespace.
    ```cpp
    namespace ns {
    class Myclass{};
    void func(Myclass x);
    Myclass func(Myclass x);
    } // namespace ns

    void ns::func(ns::MyClassx) {}  // These two declarations are the same.
    void ns::func(Myclass x) {}     // These two declarations are the same.
    ```
    But this rule does not apply to the return type.
    ```cpp
    Myclass ns::func(Myclass x) {}  // This is a syntax error.
    ```
    There are two ways to get around this;
    1. `auto ns::func(Myclass x) -> Myclass {}` This is trailing return type, most commonly used in generic programming.
    2. `ns::Myclass ns::func(Myclass x) {}`
