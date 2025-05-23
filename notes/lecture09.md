# LECTURE 09
## `constexpr` Keyword
`const` and `constexpr` are different from each other
If a `const` variable defined with a constant expression(e.g. `int x = 5;`,
here 5 is the constant expression), then expression generated by the variable is `constexpr`.
If it's initialized with a variable expression than the expression generated by the variable is not `constexpr`.
```cpp
int const x = 5;
int const y = foo();    // foo is a function that returns int
int       arr1[x]{};    // Is valid because here the expression x is constexpr.
int       arr2[y]{};    // Is invalid because here the expression y is not constexpr and compiler has to know
                        // the size of the array at the compile time. This is about variable length array.
```

##### ###REMARK###
> ```cpp
> constexpr int x = 10;   // constexpr variables must be initialized with constant expressions.
> ```

##### ###REMARK###
> ```cpp
> int const     a = 5;    // Declaration type(value type) of a is int const.
> constexpr int b = 5;    // Declaration type(value type) of b is int const.
> ```

##### ###REMARK###
> `constexpr` creates a top level const.
> ```cpp
> int g = 10;
> constexpr int*       p1 = &g; // p1 is a const pointer to an int.
> constexpr int const* p2 = &g; // p2 is a const pointer to int const. This can be done if the rhs of "=" is
>                               // known at the compile
> ```

##### ###REMARK###
> Expressions generated by variables defined with `const` keyword, may or may not generate a constant expression,
> but expressions generated by variables defined with `constexpr` keyword, always generate a constant expression.

### `constexpr` Functions
They exist mainly because of efficiency reasons. They are implicitly inline.

##### ###REMARK###
> `constexpr` functions cannot have static variables defined in them.

For a function to be defined as constexpr function it must be;
1. It's return type
2. Types of it's parameters
3. Types of it's local variables

all must be literal types. arithmetic types, pointer types are literal types.    
For a class to be a literal type there are conditions it must satisfy (topic for later).

Arrays can also be `constexpr`.
```cpp
constexpr int primes[] = {2, 3, 5, 7};
constexpr int a        = primes[2];
```

## Classes
A `class` is a user defined type.<br>
`class` Definition
- Data Members
- Member Functions
- Type Member / Member Type / Nested Type

`class` Members
- Data Members
    - Non-Static Data Members (including `bit-fields`)
    - Static Data Members
- Member Functions
    - Non-Static Member Function
    - Static Member Function    
- Type Members

`class` have access control;
- `public`
- `private`
- `protected`

Name Lookup
Context Control
Access Control
```cpp
class Myclass {
public:
    void        foo();  // Non-static member function.
    static void bar();  // Static     member function.
    // Non-static member functions have a hidden parameter. Which is the pointer of the instance that calls it.
    // For this example it is Myclass*, so void foo() is actually void foo(Myclass*).
private:
    int        _x;      // Non-static data member.
    static int _y;      // Static     data member.
}

Myclass mc;
mc._x;          // Dot operator.
&mc->_x;        // Arrow operator.
Myclass::_y;    // Scope resolution operator.
```
##### ###REMARK###
> Access modifiers do not create different scopes or affect scopes in any way.

##### ###REMARK###
> Memory location of data members of a `class` may or may not be the same with their declaration order. This is
> implementation defined (compiler dependent).

If a function is part of a class then it is called a member function.<br>
If it belongs to the global scope then it is called global function or free function or stand-alone function.
