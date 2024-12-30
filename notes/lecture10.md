# LECTURE 10
## Classes

##### Myclass.h
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H
class MyClass {
public:
    void foo();
}; // class MyClass
#endif
```

##### Myclass.cpp
```cpp
#include "Myclass.h"

public void Myclass::foo(){}    // Using access modifiers like this is a syntax error.
```
If you want to see if a member function's access modifier then you can use user defined macros.
```cpp
#define PUBLIC
#define PRIVATE
#define PROTECTED

PUBLIC void Myclass::foo(){}    // When a macro is declared without initialization, preprocessor reads it,
                                // but compiler does not. So from compiler's viewpoint, this line is exactly
                                // the same with void Myclass::foo(){}.
```

##### ###REMARK###
> If an identifier used in a member function without declaration then it is searched in this
> order;
> 1. Inside the scope it is used
> 2. Enclosing scope
> 3. Enclosing scope<br>
>   After all the enclosing scopes ended
> 4. Class scope<br>
    This is the only difference between searching in a member function and searching in a global function.
> 5. Namespace scope
>
> #### Name lookup happens only once, if the identifier is not found, compiler does not repeat the name lookup.

##### ###REMARK###
> Member functions cannot be re-declared.

### `this` Keyword
- `this` keyword can only be used inside non-static member functions.
- Using it inside of a static member function is a syntax error.
- `this` is not the instance itself, rather it's the address of the instance.
##### ###REMARK###
> In some languages `this` correspondents are the object itself.<br>
> In C++ `this` is a pointer, `*this` is the object.

#### Chaining (Fluent API)
-  In C++ it is called chaining, in higher level languages like C# it's called fluent API.
```cpp
class MyClass {
public:
    MyClass& f1() {
        this;           // PR value expr. so &this would be a syntax error.
        //code
        return *this;
    }

    MyClass& f2() {
        //code
        return *this;
    }

    MyClass& f3() {
        //code
        return *this;
    }
}; // class MyClass

int main() {
    MyClass m;
    m.f1().f2().f3();   // This is called chaining.
                        // This works because f1 returns the MyClass instance used to call it, and so do f2 and f3.
    return 0;
}
```
Same can be achieved by using pointers as well.
```cpp
class MyClass {
public:
    MyClass* f1() {
        //.. code
        return this;
    }

    MyClass* f2() {
        //.. code
        return this;
    }

    MyClass* f3() {
        //.. code
        return this;
    }
}; // class MyClass

int main() {
    MyClass m;
    MyClass* ptv_m = &m;
    ptv_v->f1()->f2()->f3();    // This is called chaining.
                                // This works because f1 returns the address of MyClass instance
                                // used to call it, and so do f2 and f3.
    return 0;
}
```
##### ###REMARK###
>Public interface of a `class` consists of the public members of the `class` and the global functions defined in the `class` header file.

## Const Member Functions
```cpp
void foo(T* p);             // Function is called mutator,  parameter is called out parameter.
void bar(T const* p);       // Function is called accessor, parameter is called in  parameter.
```
Special case; if the function first takes the argument, uses it and then sets it, then it's argument is called in-out parameter.

#### How to send the pointer to the instance of a class as `const` to a member function?
To do this we use the const keyword
```cpp
class MyClass {
public:
    void set();
    void get() const;   // Since we are not gonna change any values in this
                        // function, we use const. This const makes the pointer of
                        // the instance const.
private:
    int _x;
}; // class MyClass
```
In this example `set()` is mutator, and `get()` is accessor.<br>
Non-static member functions can belong to one of the two categories;
1. `const` Member Functions
2. Non-`const` Member Functions
##### ###REMARK###
> ```cpp
> class MyClass {
> public:
>     void foo() {}
> 
>     void func() const {
>         foo();      // This here is a syntax error because, func takes "this" as const,
>                     // foo does not. In C++ there is no implicit conversion from
>                     // T const* to T*. Therefore this line creates an error.
>     }
> }; // class MyClass
> ```
##### ###REMARK###
> - `const` member functions cannot call non-`const` member functions, but non-`const` member functions can call `const` member functions.
> - A `const` instance of a class can only call `const` member functions.
> - `const` instance calling a non-`const` member function is a syntax error.
> - Using `this` in a `const` member function to change the value of that instance is a syntax error.
