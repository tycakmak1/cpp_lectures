# LECTURE 01

- Syntax Error
- Well-formed - Ill-formed
- Valid code  - Invalid code
- Legal code  - Illegal code

<br>

- Undefined Behavior (UB)
    - Unspecified Behavior
        - Implementation Defined

In C there is name shadowing, in C++ it does not exist.<br>
In C, `int func()` and `func()` (without an explicit data type declaration) are the same, but in C++ this does not happen.

## Diffrences About Types and Type Castings
- _Bool in C is actually a signed int.
- In C++ bool is an actual logic data type.
- Size of bool is 1 byte.
- There is implicit type conversion from arithmetic values to bool and from bool to arithmetic.
    ```cpp
    int  x     = 15;
    int  y     = 0;
    bool flag1 = x;			// flag1 is true
    bool flag2 = y;			// flag2 is false
    int  z     = flag1;			// value of z is 1
    int  t     = flag2;			// value of t is 0
    ```

###### <turquoise>###REMARK###</turquoise> <white>There is implicit conversion from pointer to bool but not from bool to pointer.</white>
###### <turquoise>###REMARK###</turquoise> <white>The most dangerous situation is having a valid code by accident.</white>

```cpp
struct Data1
{
    int a,b;
}; // struct Data1

struct Data1 i;

typedef struct
{
    int a,b;
}Data2; // struct Data2

Data2 i;
```

- In C++ you do not need to use typedef.
- In C++ structures are also classes.
- In C structures do not have access control(public, private, etc.), in C++ they do.
- Typedef also exists in C++, but there is an alternative to this, the "using" keyword.

## Const Semantics
- In C constant variables do not have to be initialized, but in C++ they have to.
- In C constant variables cannot be used in declarations like `int a[x]`. Applies if variable length array is not used by the
compiler.
- In C++ constant variables can be used in declarations like `int a[x]`. Applies if variable length array is not used by the
compiler.

    ```cpp
    int get_size() { return 100; }

    int main() {
        int const size = 100;
        int const ds = get_size();
        // Both of them are constants but size can be used in array declaration but ds cannot.
        // Again this is about the variable length array.
    }
    ```

- In C++ there is const, constexpr, consteval.
- Internal linkage and external linkage is important.
    
- In C there is implicit conversion from T const* to T* but in C++ this is illegal.
    ```cpp
    int* const ptr1;        // Top-level const, also called the right const because const is on the right of *.
    int const* ptr2;        // Low-level const, also called the left  const because const is on the left  of *.

    void foo(T* p);         // mutator or out param
    void foo(T const* p);   // in param
    ```

## Scope Leakage
- Is the scenario where the variable is accessible from outside of it's intended use.
    ```cpp
    int i;
    // code..
    // code..

    for(i = 0; i < 10; i++) {
        // code..
        // code..
    }
    // The variable i is only used in the above loop but it is accesible from outside of the loop.
    // Since it is accesible from outside of the loop it is a scope leakage.
    ```

- In C there is implicit conversion from T to T*, but in C++ there is not.
- In C there is implicit conversion from T1* to T2*, but in C++ there is not.
- In C there is implicit conversion from void* to T*, but in C++ there is not.
- In C++ there is implicit conversion from T* to void*.
- In C there is implicit conversion from arithmetic variables to enum variables, but in C++ there is not.
- In C there is implicit conversion between different enum variables, but in C++ there is not.
