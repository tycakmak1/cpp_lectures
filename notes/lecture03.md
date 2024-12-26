# LECTURE 03

## Basic Types

- bool<br><br>
- char
- signed char
- unsigned char<br><br>
- short
- unsigned short
- int
- unsigned int<br><br>
- long
- unsigned long<br><br>
- long long
- unsigned long long<br><br>

`sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)`

`float`        (4 bytes)<br>
`double`       (8 bytes)<br>
`long double`

4.5  means `double`<br>
4.5F means `float`

|Types                   |Suffix                                                                   |
|------------------------|-------------------------------------------------------------------------|
|unsigned                |U                                                                        |
|long                    |L                                                                        |
|float                   |F    (has to contain . , e.g. 34F is a syntax error, correct way is 34.F)|
|unsigned long           |UL  or LU                                                                |
|unsigned long long      |ULL or LLU                                                               |

##### ###REMARK###
> - When `signed` or `unsigned` used without any type keywords like `signed x` or `unsigned x`, it
>     automatically becomes `signed int x` and `unsigned int x` respectively.
> - Using scientific notation in real numbers eliminates the necessity of `.`.
>     ```c
>     10e2, 10e2F
>     ```
> - If you exceed the value limits of `int` or `float`, variable type automatically changes to the
>     respective bigger types, depending on which type can contain that value.
> - To make reading large numbers easier, `'` (digit separator) can be used.<br>
>     `int x = 784'123` would mean int x = 784123; but it is much easier to read the number. This is not exclusive to decimals.
<br><br>

|C                   |C++             |                  |
|--------------------|----------------|------------------|
|Decimal             |Decimal         |41 (default)      |
|Octal               |Octal           |041               |
|Hexadecimal         |Hexadecimal     |0x41              |
|                    |Binary          |0b1001            |

Default type of variables are int.
```c
ival * 1000  int operation
ival * 1000L long operation (typecasting)
```

##### ###REMARK###
> Variable types are critically important for function overloading.

## Scope
- Names have scope.
- In C
    - Block Scope
    - File Scope
    - Function Prototype Scope
    - Function Scope
- In C++
    - Block Scope
    - Namespace Scope
    - Class Scope
    - Function Prototype Scope
    - Function Scope
- Name Lookup

## Expression<br>
Most widely used statement form is expression statement.
#### Expression Statement
If you put a ';' at the end of an expression it becomes an expression statement. e.g. `x = 5;`<br>
Every expression has a data type(int, double, ...) and a value category (PR, X, L (primary val cats) or R, GL (secondary val cats)).

##### ###REMARK###
Priority operator does not change the value category.
>`x = 9;` and `(((((((((x))))))))) = 9;` are the same thing.

## constexpr
##### ###REMARK###
>    constant (`const`) and constant expression (`constexpr`) are different from each other.
>
>    C definition: If the value of an expression is known by the compiler at the compile time then that expression is a
>    constant expression (`constexpr`).
>
>    In C there are some places that constexpr must be used;
>   - `int a[constexpr]` because compiler has to know the size of the array (if compiler does
>       not support variable length array).
>   - Initializations of global variables.
>   - Case label expressions in `switch`.
>   - Bitfield member
>
>    In C++ importance of constepxr is much greater than in C.

## Operators
- By Operand(s)
    - Unary
    - Binary
    - Ternary    (the ternary/conditional operator)
- By Position
    - Prefix     `*ptr` or `++x` or `--x` etc.
    - Postfix    `x++` or `x--` etc.
    - Infix      `a + b` or `a * b` etc.

### Operator Precedence in C
For more details check [CppReference C Operator Precedence](https://en.cppreference.com/w/c/language/operator_precedence)
|Precedence|Operator&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|Description|Associativity|
|:--------:|--------|-----------|-------------|
|1|`++` `--`[^1]<br>`()`<br>`[]`<br>`.`<br>`->`<br>`(type){list}`|Suffix/postfix incerement and decrement<br>Function call<br>Array subscripting<br>Structure and union member access<br>Structure and union member access through pointer<br>Compound literal|Left-to-right|
|2|`++` `--`[^1]<br>`+` `-`<br>`!` `~`<br>`(type)`<br>`*`<br>`&`<br>`sizeof` [^2]<br>`_Alignof`|Prefix increment and decrement<br>Unary plus and minus<br>Logical `NOT` and bitwise `NOT`<br>Cast<br>Indirection (dereference)<br>Address-of<br>Size-of<br>Alignment requirement|Right-to-left
|3|`*` `/` `%`|Multiplication, division, and remainder|Left-to-right|
|4|`+` `-`|Addition and subtraction|Left-to-right|
|5|`<<` `>>`[^3]|Bitwise left shift and right shift|Left-to-right|
|6|`<` `<=`<br>`>` `>=`<br><br>|Relational operators for less than and less than or equal to respectively<br>Relational operators for greater than and greater than or equal to respectively|Left-to-right|
|7|`==` `!=`|For relational equal and not equal|Left-to-right|
|8|`&`|Bitwise `AND`|Left-to-right|
|9|`^`|Bitwise `XOR`|Left-to-right|
|10| `\|`|Bitwise `OR`|Left-to-right|
|11|`&&`|Logical `AND`[^4]|Left-to-right|
|12|`\|\|`|Logical `OR`[^4]|Left-to-right|
|13|`?:`[^5]|Ternary conditional|Right-to-left|
|14|`=`<br>`+=` `-=`<br>`*=` `/=` `%=`<br>`<<=` `>>=`<br>`&=` `^=` `\|=`[^6]|Simple assignment<br>Assignment by sum and difference<br>Assignment by product, quotient and remainder<br>Assignment by bitwise left shift and bitwise right shift<br>Assignment by bitwise `AND`, `XOR`, and `OR`|Right-to-left|
|15|`,`[^7]|Comma|Left-to-right|

### Operator Precedence in C++
For more details check [CppReference C++ Operator Precedence](https://en.cppreference.com/w/cpp/language/operator_precedence)
|Precedence|Operator|Description|Associativity|
|----------|--------|-----------|-------------|
|1|`a::b`|Scope resolution|Left-to-right|
|2|`a++` `a--`[^1]<br>`type(a)` `type{a}`<br>`a()`<br>`a[]`<br>`a.b` `a->b`|Suffix/postfix increment and decrement<br>Functional cast<br>Function call<br>Subscript<br>Member access|Left-to-right|
|3|`++a` `--a`[^1]<br>`+a` `-a`<br>`!a` `~a`<br>`(type)a`<br>`*a`<br>`&a`<br>`sizeof`[^2]<br>`co_await`<br>`new` `new[]`<br>`delete` `delete[]`|Prefix increment and decrement<br>Unary plus and minus<br>Logical `NOT` and bitwise `NOT`<br>C-style cast<br>Indirection (dereference)<br>Address-of<br>Size-of<br>await-expression<br>Dynamic memory allocation<br>Dynamic memory deallocation|Right-to-left|
|4|`a.*b` `a->*b`|Pointer to member|Left-to-right|
|5|`a * b` `a / b` `a % b`|Multiplication, division, and remainder|Left-to-right|
|6|`a + b` ` a - b`|Addition and subtraction|Left-to-right|
|7|`a << b` `a >> b`[^3]|Bitwise left shift and right shift|Left-to-right|
|8|`a <=> b`|Three-way comparison operator (C++20)|Left-to-right|
|9|`a < b` `a <= b`<br>`a > b` `a >= b`|Relational operators|Left-to-right|
|10|`=` `!=`| Equality operators|Left-to-right|
|11|`a & b`|Bitwise `AND`|Left-to-right|
|12|`a ^ b`|Bitwise `XOR`|Left-to-right|
|13|`a \| b`|Bitwise `OR`|Left-to-right|
|14|`a && b`[^4]|Logical `AND`|Left-to-right|
|15|`a \|\| b`[^4]|Logical `OR`|Left-to-right|
|16|`a ? b : c`[^5]<br>`throw`<br>`co_yield`<br>`a = b`[^6]<br>`a += b` `a -= b`<br>`a *= b` `a /= b` `a %= b`<br>`a <<= b` `a >>= b`<br>`a &= b` `a ^= b` `a \|= b`|Ternary conditional<br>`throw operator`<br>`yield expression`(C++20)<br>Direct assignment<br>Compound assignment by sum and difference<br>Compound assignment by product, quotient, and remainder<br>Compound assignment by bitwise left shift and right shift<br>Compound assignment by bitwise `AND`, `XOR`, and `OR`|Right-to-left|
|17|`,`[^7]|Comma operator|Left-to-right|

##### ###REMARK###
> Yielded value, generated value, return value are the same thing.

## Sequence Point(also called sequencing in C++)
Expressions causing a side effect before this point, must be completed after this point
```c
x = 10;
x++;
//-------------sequence point
x;                              // x is 11 from here

int x = 5, y = ++x, z = y + x;  // Comma separator creates a sequence point, therefore
                                // at the end of this line x is 6, y is 6, z is 12.
                                // Expression in if, switch, while, do-while and
                                // semicolons in for are sequence points. Left hand
                                // operand of && operator is a sequence point.
```

## Order of Evaluation
```c
f1() + f2() * 5;    // f1 will be evaluated first, then f2, then multiplication and finally addition
```

##### ###REMARK###
> Token
> - Identifier
> - Operator
> - String Literal (e.g. "mike")
> - Keywords

##### ###REMARK###
> Do not compare two real numbers.

##### ###QUESTION###
```c
#include <stdio.h>

int main(void) {
    int x = 10, y = 20;
    int z;

    z = x, y;
    printf("z = %zu\n", z);                // This will output         z = 10

    z = (x, y);
    printf("z = %zu\n", z);                // This will output         z = 20
        
    return 0;
}
```

[^1]:
    `++` `--`<br>
    Postfix and prefix operators have side effects, they change the value of their operand.

    ```c
    int x = 10;
    int y = x++;    // In this, y will be 10, and x will be increased to 11.
    int x = 10;
    int y = ++x;    // In this, y will be 11, and x will be increased to 11.         
                    // In both examples x has the value 11 because of the side effect but, in the first example
                    // it happens after y is initialized.
    ```

[^2]:
    1. `sizeof`
    2. `sizeof` is a keyword and is an operator, not a function.
    3. `sizeof` is a compile time operator, which means expressions generated by `sizeof` are `constexpr`, so they can be used in
    array declarations.
    4. Value generated by `sizeof` has the value type `size_t` (it can be `unsigned int`, `unsigned long`, `unsigned long long`).
    5. Operand of `sizeof` operator is unevaluated context.
    6. `()` used in `sizeof` are not part of the operator, they are only necessary when the operand is a typename.

        ```cpp
        sizeof 5;
        sizeof(int);
        sizeof(double);
        ```

[^3]:
    Bitshift Operators<br>
    1. Value of the right operand of bitshift operators must be smaller than the number of bits of the left operand.
    2. Value of the right operand must be non-negative.
    3. Left operand will be promoted.
    4. Left operand must be positive (in C).
    5. Whether it's an arithmetic bitshift or logic bitshift, is implementation defined (meaning it depends on the compiler).

[^4]:
    Short Circuit Behavior;<br>
    for `&&` if the left operand is false, right operand is not calculated.<br>
    for `||` if the left operand is true,  right operand is not calculated.

[^5]:
    Ternary Operators

    ```cpp
    // assignments
    z = x > y ? a : b;
    // function calls
    function(a > b ? a : b)
    // return statements
    return x > 10 ? x : b;
    ```

[^6]: Return value of every assignment operator is the value that is assigned to the variable.

[^7]:
    Comma Operator<br>
    Is a binary operator that evaluates its first operand and discards the result, it then evaluates the
    second operand and returns this value and type.
    Separator comma and operator comma are different from each other.

    ```c
    int num1 = (5, 10);         // 10 is assigned to num
    int num2 = (f1(), f2());    // f1() is called(evaluated) first followed by f2(). The returned value of f2() is
                                // assigned to num2.
    ```
