# LECTURE 08
### Exceptions to the overload resolution(function scope resolution)
1.
```cpp
void f(bool);
void f(void*);

int x{};
f(&x);  // Ambiguity error is expected since both overloads require conversion BUT compiler chooses f(void*).
```

2.
```cpp
void func(int const&);
void func(int&&);

f(10);  // Ambiguity error is expected since both overloads are viable BUT func(int&&) will be called.
```

3.
```cpp
void f(int&);
void f(int const&);
void f(int&&);

int       x{10};
int const cx{45};

f(10);  // Calls f(int&&).
f(x);   // Calls f(int&).
f(cx);  // Calls f(int const&).
```

4.
```cpp
void bar(int&) { std::cout << 3 << '\n'; }

void bar(int&&) { std::cout << 4 << '\n'; }

void foo(int& x) {
    std::cout << 1 << '\n';
    bar(x);
}

void foo(int&& x) {
    std::cout << 2 << '\n';
    bar(x);
}

foo(10);    // IMPORTANT. foo(10) calls foo(int&&) but bar(x) calls bar(int&) because x is an L value expression.
```

##### ###REMARK###
> `const` keyword with `typealiases` create top level `const`.
> ```cpp
> using iptr = int*;
> int        x{};
> iptr const ptr = &x;  // Here iptr const means int* const ptr = &x;
> ```
> Same also goes for C style `typealiases`
> ```cpp
> typedef int* iptr;
> int        x{};
> iptr const ptr = &x;  // Here const iptr means int* const ptr = &x;
> ```

##### ###REMARK###
> For function overloads with multiple parameters, the rule is;<br>
> It must have at least one parameter better than the other overloads, and the remaining parameters cannot be worse than the
> other functions.
> ```cpp
> void f(int, double, long);
> void f(char, int, double);
> void f(long, unsigned int, float);
> 
> f(12, 4L, 3);       // This line will call void f(int, double, long).
> f(2.3, true, 12);   // This line will call void f(char, int, double).
> f(34L, 3.4L, 12);   // This line will call void f(long, unsigned int, float).
> ```

## One Definition Rule (ODR)
Only one definition of any variable, function, class type, enumeration type, concept or template is allowed in any one translation
unit (some of these may have multiple declarations, but only one definition is allowed).<br>
Programs in violation of ODR are ill-formed.

##### ###REMARK###
> Some objects do not defy the ODR when defined in different header files if and only if they are defined exactly the same
> token-by-token;
> - `class` Definitions
> - Inline Function Definitions
> - Inline Variable Definitions (C++17 Feature)
> - `constexpr` Functions
> - `constexpr` Variables
> - `class` Templates
> - Functions Templates

## Inline Functions
- Inline function and inline expansion are two different things and must not be confused.
- Inline expansion is the act done by the compiler which consists of switching the body of the function with it's call place.

```cpp
int func(int x) { return x * x; }

int a = func(5);    // Compiler expands this line to int a = 5 * 5.
                    // This expansion is not always done and cannot be forced. Compiler decides it.
```

##### ###REMARK###
> - Inline functions and inlined functions are different things.
> - `inline` keyword lets us define the function in the header file.
> - `inline` keyword requests this function to be inlined by the compiler, but compiler does not have to comply.
> - `inline` keyword does not affect the inline expansion.
> - `inline` keyword does not defile the ODR.
> - Defining a function in a header file requires the inclusion of other header files that contain the complete types.
> - Member functions are inline functions even if the keyword is not used.

##### ###REMARK###
> Things that are in the header file but do not defile the ODR;
> - `inline` Functions
> - `constexpr` Functions
> - `class` Definitions
> - Templates
>   - Function Templates
>   - `class` Templates
>   - Alias Templates
>   - Variable Templates

##### ###REMARK###
> When used in global scope, `static` keyword creates internal linkage.

##### ###REMARK###
> ###### Incomplete Types
> ```cpp
> struct Tah;
> 
> Tah  f1(Tah);
> Tah* f2(Tah&);
> 
> typedef Tah* TahPtr;
> using TahRef = Tah&;
> 
> extern Tah Tahx;
> extern Tah arr[];
> 
> struct X {
>     Tah* _ptr;
>     Tah& _ref;
> }; // struct X
> 
> class Yasin {
>     static Tah var;
> }; // struct Yasin
> 
> inline void foo() { Tah* ptr = nullptr; }
> 
> // These are all legal.
> ```
