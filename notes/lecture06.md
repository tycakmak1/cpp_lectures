# LECTURE 06
## Type Deduction
### Universal Reference (Forwarding Reference) (`auto&& name = expression`)
- If the `expression` is L value expression then, auto = T&.
- If the `expression` is R value expression then, auto = T.
```cpp
int    x  = 10;
auto&& r1 = x;      // As if it is int&  r1 = x, so auto = int&.
auto&& r2 = 10;     // As if it is int&& r2 = 10, so auto = int.
```

### `decltype(x)` Type Deduction
`auto` can only be used in variable declarations, but `decltype` can be used anywhere to specify a type.

`decltype()` works in two different ways;
1. If the operand is an identifier, it gives out the type of the operand.
    ```cpp
    int x         = 5;
    decltype(x) y = 10;             // As if it is int y = 10, decltype(x) = int.
    int         x = 5;
    using mytype  = decltype(x);    // As if it is using mytype = int, so decltype(x) = int.

    struct Data {
        int a, b, c;
    };

    Data            d;
    Data*           pd = &d;
    decltype(d.a)   x;              // As if it is int x, so decltype(d.a) = int.
    decltype(pd->a) y;
        ```
2. If the operand is an expression,
    1. If it's a  PR val. expr. then T.
    2. If it's an L  val. expr. then T&.
    3. If it's an X  val. expr. then T&&.
    ```cpp
    int            x = 5;
    decltype(x++)  y;           // As if it is int y, so decltype(x++) = int.
    decltype(++x)  z   = x;     // As if it is int& z, so decltype(++x) = int&.
    int            x   = 5;
    int*           ptr = &x;
    decltype(*ptr) r   = x;     // As if it is int& r, so decltype(*ptr) = int&.
    int            f1();
    int&           f2();
    int&&          f3();

    int main() {
    f1();                   // PR value
    f2();                   // L  value
    f3();                   // X  value
    decltype(f1()) x = 5;   // As if it is int   x, so decltype(f1()) = int.
    decltype(f2()) y = x;   // As if it is int&  y, so decltype(f2()) = int&.
    decltype(f3()) z = 5;   // As if it is int&& z, so decltype(f3()) = int&&.
    return 0;
    }
    ```

```cpp
int            a[5]{};
decltype(a)    b;                   // Here a is an identifier, so decltype(a) = int[5].
decltype(a[0]) c = a[1];            // Here a[0] is an L val. expr., so decltype(a[0]) = int&.
```

##### ###REMARK###
```cpp
int           x;
decltype(x)   a;                    // Here x is an identifier, so decltype(x) = int.
decltype((x)) b;                    // Here (x) is an L val. expre., so decltype((x)) = int&.
```

##### ###REMARK###
Operand of the decltype is unevaluated context. operand of the sizeof is also unevaluated.
```cpp
int x = 10;
decltype(x++) y = 5;
decltype(++x) z = y;
int main()
{
    std::cout << x << "\n"; // Outputs 10, because operand of declytpe is unevaluated.
    return 0;
}
```

##### ###REMARK###
In auto top level const is lost, but in decltype it is not.
```cpp
int const   x{};
decltype(x) y = 10;         // As if it is int const y = 10, so decltype(x) = int const.
```

## Default Arguments of Functions
Parameter (Formal Parameter)
Argument  (Actual Parameter)

##### ###REMARK###
> ```cpp
> int foo(int x);             // Here x is a parameter of the function foo.
> foo(5);                     // Here 5 is the argument.
> 
> int func(int, int, int = 10);
> 
> func(x, y, z);              // func(x, y, z);
> func(x, y);                 // func(x, y, 10);
> ```

##### ###REMARK###
> ```cpp
> int func(int, int = 5, int);    // Syntax error. Every following argument after a default argument  must also have a
>                                 // default argument. But there is an exception to this.
> int func(int, int, int = 10);
> int func(int, int = 5, int);    // Since the 3rd parameter already has a default value, redeclaring it as
>                                 // int func(int, int = 5, int = 10) would be a syntax error.
>                                 // So calling func as func(1) would mean func(1, 5, 10).
> ```

##### ###REMARK###
> Default arguments do not have to be a constant expression.
> ```cpp
> int f1(int x = 0);
> void f2(int y = f1());
> f2();                           // f2(f1()) ==> f2(f1(0))
> ```

##### ###REMARK###
> Declaration of default arguments both in the function declaration and in the function definition causes syntax error.
> ```cpp
> int func(int x = 5);
> int func(int x = 5) {
>     // code
>     return x;
> }
> // this is a syntax error
> ```
> ```cpp
> int func(int x);
> int func(int x = 5) {
>     // code
>     return x;
> }
> // this is well-formed
> ```
> ```cpp
> int func(int x = 5);
> int func(int x) {
>     // code
>     return x;
> }
> // this is also well-formed
> ```

##### ###REMARK###
> ```cpp
> int func(int, int, int = 10);
> int func(int, int, int = 10);           // Is a syntax error because it's a redefinition.
> int func(int, int = 5, int = 10);       // Is a syntax error because it's a redefinition.
> int func(int, int = 5, int);            // Is well-formed.
> ```
> This style is especially useful if you are using a function from a header file that does not belong to you. Instead of changing
> the function in the header file, you can redeclare it in your own program.
> ```cpp
> void func(int x, int y = x);            // Is a syntax error.
> ```

## Enumerators
There are two different enum types in C++ enum and scoped enum(usually called enum class by developers but correct name is
scoped enum).

### Old Enum
```cpp
enum Colour1 { RED, GREEN, BLUE }; // enum Colour1
enum Colour2 : unsigned char { RED, GREEN, BLUE }; // enum Colour2
```
- `underlying_type` is determined by the compiler. In C, `underlying_type` has to be `int`. In C++ it is dependent on `int`, it
defaults to `int` but if `int` is not enough then it is chosen accordingly by the compiler. Can also be specified explicitly in C++.
```cpp
enum Colour1 : unsigned char;
enum Colour2 : unsigned int { GREY, BLACK, MAGENTA }; // enum Colour2
```
#### Problems of the Old Enum
- Old enumerators cannot be used as an incomplete type, because `underlying_type` is dependent on the compiler.
- `underlying_type` cannot be specified by developer.
- Implicit type casting from arithmetic types to enum type does not exist but it does from enum to arithmetic types.<br>
THIS IS A HUGE PROBLEM. ONE OF THE MAIN REASONS THAT SCOPED ENUM EXISTS.
- Implicit type casting between two different enum's also does not exist.
- THEY DO NOT HAVE SCOPE. ONE OF THE MAIN REASONS THAT SCOPED ENUM EXISTS. When defined globally, components of
different enum's with same names would clash(called name clashing / name masking / name hiding).
```cpp
enum TrafficLight { RED, YELLOW, GREEN };
enum ScreenColour { GREY, WHITE, RED };
// To prevent name clashing developers would define the components more uniquely.
enum TrafficLigt { TRAFFIC_LIGHT_RED, TRAFFIC_LIOGHT_YELLOW, TRAFFIC_LIOGHT_GREEN };
enum ScreenColour { SCREEN_COLOUR_GREY, SCREEN_COLOUR_WHITE, SCREEN_COLOUR_YELLOW };
// If not done like this, RED in TrafficLight and red in ScreenColour would clash.
```

### Scoped Enum
```cpp
enum class Colour1 { WHITE, GREY, BLACK, GREEN };                   // enum class Colour1
enum class Colour2 : unsigned char { WHITE, GREY, BLACK, GREEN };   // enum class Colour2
```

- It's `underlying_type` defaults to int, but can be specified by declaration or definition.
- To access it's elements, scope resolution operator(`::`) must be used.
    ```cpp
    enum class Colour { WHITE, GREY, BLACK, GREEN };    // enum class Colour1
    Colour temp = WHITE;            // Is a syntax error because white is not defined.
    Colour temp = Colour::WHITE;    // Is the proper way.
    auto c1 = GREY;                 // Is still a syntax error, same reason.
    auto c2 = Colour::GREY;         // Is the proper way.
    ```
    This prevents the name clashing problems, which was the aim.

- Implicit type casting from scoped enum to arithmetic types do not exist. explicit does.
    ```cpp
    enum class Colour { RED, GREEN, BLUE }; // enum class Colour
    Colour mycolour{Colour::red};
    int x = mycolour;           // Is a syntax error because implicit type casting does not exist for scoped enums.
    int x = static_cast<int>(mycolour);  // Is correct, because the casting is done explicitly.
    ```

##### ###REMARK###
> Using enum declaration can grant access to the elements of a scoped enum without scope resolution operator. This is available
> with C++20.
> ```cpp
> enum class Colour { RED, GREEN, BLUE }; // enum class Colour
> using enum Colour;    // By using this, in the scope of this declaration, you can access the elements of Colour
>                       // without using scope resolution operator.
> auto   c1 = RED;
> Colour c2 = GREEN;
> ```

##### ###REMARK###
> If you use two "`using enum`" declarations in the same scope, you would create an error if those two scoped enums have a name
> clash. Compiler checks this on the compile time.

##### ###REMARK###
> Can also be used like this
> ```cpp
> enum class Colour { RED, GREEN, BLUE }; // enum class Colour
> using Colour::red;
> Colour c1 = RED;  // Is valid because of the "using Colour::RED".
> Colour c2 = BLUE; // Is invalid because blue is undefined in this scope. It has to be Colour c2 = Colour::BLUE.
> 
> using Colour::RED, Colour::BLUE;
> Colour c1 = RED;  // Is valid because of the "using Colour::RED".
> Colour c2 = BLUE; // Is valid because of the "using Colour::BLUE".
> ```
