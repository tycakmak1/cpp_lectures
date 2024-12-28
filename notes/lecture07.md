# LECTURE 07
## Type Casting
##### ###REMARK###
> - TYPE CASTING DOES NOT CHANGE THE VARIABLE'S ACTUAL TYPE BUT CREATES A TEMPORARY OBJECT IN THAT TYPE TO USE.
> - EVERY TYPE CAST IS A POTENTIAL ERROR. MUST BE VERY CAREFUL IN EVERY WAY.

In C there is only one way to do explicit type cast. `(target type)expression`.<br>
In C++ there are several ways, all differ from each other.

1. Old Way `(target type)expression`
    ```cpp
    double x = 5.2;
    int y = (int)x;
    // OR
    (double)i1 / i2;    // Here only i1 is treated as double.
    ```

2. New Ways
    1. `static_cast<target_type>(operand)`
        ```cpp
        int x = 10;
        int y = 3;
        double dval = x / y;    // This will cause data loss, to prevent it, type cast must be used.
        double dval = static_cast<double>(x) / y;
        int ival = static_cast<int>(dval);
        enum class Pos { ON, OFF, HOLD }; // enum class Pos
        Pos mypos = Pos::OFF;
        ival = mypos;           // This will cause an error, because implicit cast from scoped enums to
                                // arithmetic types does not exist.
        ival = static_cast<int>(mypos)
        ```
    2. `const_cast<target_type>(operand)`<br>
        `const_cast` only takes pointers and references as it's operand.
        ```cpp
        char* mystrchr(char const* p, int c) {      // Here first parameter is left const because this function
            while (*p) {                            // is not gonna change the variable. But the return type is not
                if (*p == c) {                      // const because the original variable may or may not be const.
                    return p;                       // This is an error because function's return type is char* but
                    return const_cast<char*>(p);    // p is char const*, to overcome this we use const_cast.
                }
                ++p;
            }
            if (c == '\0') {
                return const_cast<char*>(p);
            }
            return nullptr;
        }
        ```
    3. `reinterpret_cast<target_type>(operand)`
        ```cpp
        double dval = 3.33;
        char*  ptr  = &dval;      // This is a syntax error because dval is double and ptr is char*.
        char*  ptr  = reinterpret_cast<char*>(&dval);
        ```
    4. `dynamic_cast<target_type>(operand)`<br>
        This one is about run-time polymorphism and will be studied under classes.

## Function Overloading (compile time mechanism, it has nothing to do with the runtime)
Three necessities for function overloading;
1. Names  must be the same
2. Scopes must be the same
3. Function signatures must be different (Function Signature: number of parameters and the type of parameters of a function)

##### ###REMARK###
> Overloaded functions can have different return types.
> ```cpp
> int func(int);
> double func(int, int);
> // is a valid overload
> ```
##### ###REMARK###
> - Top level `const` does not cause different signatures. It just causes redeclaration.
>   ```cpp
>   int func(int);
>   int func(int const);
>   ```
> - Low level `const` does cause different signatures. It's also one of the most used function overloading scenarios. It is
    frequently called `const overloading` (not an official term).
>   ```cpp
>   int func(int*);
>   int func(int const*);
>   ```
> - Some examples and edge cases.
>   ```cpp
>   int    func(int);
>   double func(int, int);
>   // Is a valid overload
>   ```
>   ```cpp
>   typedef double flt_type;
>   int func(double);
>   int func(flt_type);
>   // Is not an overload. type aliases do not cause overload.
>   ```
>   ```cpp
>   void f(char);
>   void f(signed char);
>   void f(unsigned char);
>   // In here we have 3 overloads, because char, signed char and unsigned char are distinct types.
>   ```
>   ```cpp
>   int f(int);
>   int f(signed int);
>   int f(unsigned int);
>   // In here we have 2 overloads because int and signed int are not distinct types.
>   ```
>   ```cpp
>   void f(std::int32_t);
>   void f(int);
>   // Is implementation defined, because just from these two lines we dont now if int32_t and int
>   // same or not.
>   ```
>   ```cpp
>   int f(int*);
>   int f(int&);
>   // Is also a function overload.
>   ```
>   ```cpp
>   void foo(int p[]);
>   void foo(int p[20]);
>   void foo(int* p);
>   // Only one overload here, they are all the same.
>   ```
>   ```cpp
>   void foo(int(int));
>   void foo(int(*)(int));
>   // Is not an overload because, int(int) is a function type, int(*)(int) is a pointer to function.
>   // They seem different but, function to pointer decay happens, no overload. this is redeclaration.
>   ```
>   ```cpp
>   void foo(int (*)[5]);
>   void foo(int (*)[6]);
>   void foo(int (*)[7]);
>   void foo(int (*)[8]);
>   // Here we have four overloads.
>   ```

### Function Overload Resolution (usually referred to as Overload Resolution)
It happens in three steps;
1. Candidate Functions
    In this step, compiler finds all the functions with the same name in the call. These functions are called
    candidate functions.
2. Viable Functions
    Compiler checks the candidate functions if they would be viable to use if they were the only one to exist.<br>
    If there are no viable functions, then no match error.<br>
    If there are more than one viable function to call but no criteria for the compiler to choose between the viable functions, then
    ambiguity error.

    ```cpp
    // e.g. for no match
    int foo(int);
    foo();          // Function call, no match error.

    // e.g. for ambiguity
    int bar(int);
    int bar(double);
    bar(2U);        // Function call, ambiguity error,
                    // Because there are no criterias for the compiler to choose between bar(int) and bar(double).
                    // Because they both are viable for 2U.
    ```
3. Preference Order
    1. Standard Conversion
        1. Exact Match (wins against promotion) Argument type and parameter type are the same.<br>
            There are exceptions that are considered as exact match;
            - `const` conversion (conversion from `T*` to `T const*`)
            - Array decay
            - Function to pointer conversion
        2. Promotion (loses against exact match but wins against conversion)
            - Integral Promotion (conversion of `short`, `char`, `signed char`, `unsigned char`, `bool` to `int`)
            - Float promotion (conversion of `float` to `double`)
        3. (only) Conversion (loses against promotion but wins against user-defined conversion)
    2. User-Defined Conversion (loses against standard conversion but wins against variadic conversion)
    3. Variadic Conversion (last choice)
