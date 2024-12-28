# LECTURE 04

## Type Conversion

### Implicit Type Conversion

- If ranks are different but signs are same, operations will be performed on higher rank.
- If ranks and signs are both different, operation will be performed on higher unsigned rank.
    - `unsigned long + int` => Operation will be performed on `unsigned long`.
    - `long + unsigned int` => If the higher rank can store all the values in lower unsigned rank,<br>
                               then the operation will be performed on the higher rank,<br>
                               else it will be performed on the higher rank.<br>
- If ranks are the same but one of them is signed and the other one is unsigned, operation will be performed on unsigned.
    - `unsigned long + long` => Operation will be performed on `unsigned long`.

## Control Statements
- `if`
- `for`
- `while`
- `do-while`
- `switch`
- `goto`
- `return`
- `break`
- `continue`

## Maximal Munch
Compiler tries to produce longest tokens.<br>
    `x+++y` would mean `x++ + y` because,<br>
        `x` is an identifier, `x+` is meaningless so `x` is the first token,<br>
        `+` is an operator, `++` is an operator, `+++` is meaningless so the second token is `++`,<br>
        `+` is an operator, `+y` is meaningless so the third token is `+`,<br>
        `y` is an identifier and is the fourth token.<br>
    So `x+++y` becomes `x++ + y`.<br>

##### ###REMARK###
> After declaration of an array, `a[5]` and `int 5[a]` are the same thing, because `[]` is a pointer operator.<br>
> The `[]` operator sums the left operand and the operand between `[]` and deferences the sum.
> ```c
>     int a[6]{};
>     int coders[4]{};
>     // a[5]  is identical to *(a + 5)
>     // 5[a] is identical to *(5 + a)
>     auto x = 2["coders"] - 3["coders"]; // Here x will be an int and it will have the value of 1.
> ```

## Pointers
### Object Pointers -> Address of objects, variables.
- `T*` is the type of address of `T` data type. e.g. `int*`, `double*`, etc.<br>
- Pointers can be L value or R value. Pointer variable name can be used for L value type pointer.
- Every object pointer no matter the data type it points to, has the same size, but function pointer and object pointer does
not have to have the same size.
```c
int* p;     // pointer to int or p points to 'insert variable name here'
int* x, y;  // here x is a pointer but y is int
```
- A pointer can be valid or invalid. Validity does not relate to syntax.
```c
int* ptr;               // Is an INVALID pointer because it has garbage(indetermined) value.
int a[5] = {0};
int* p = &a[5];         // Is a VALID pointer. The end of an array is always a VALID pointer.
```
- If the object that the pointer points to is dead, than the pointer is invalid.
    ##### ###REMARK###
    > ```c 
    > #include <stdio.h>
    > int main(void) {
    >     int* p1 = nullptr;    // Is a VALID pointer
    >     int* p2;
    >     p2;                   // Here p2 is a wild pointer.
    >     if (true) {
    >         int x = 10;
    >         p2    = &x;
    >         p2;               // Here p2 is still a VALID pointer.
    >     }
    >     p2;                   // Here p2 is a dangling pointer. Dangling pointers are INVALID pointers.
    > }
    > ```

### Pointer Operators
- `&` Address of Operator
    - It's operand has to be an L value expr
    - `&x` is an R value expr
- `*` Indirection (Dereferencing) Operator
    - Yields the value of the object that the pointer points to

###### ###REMARK###
> Pointer returning functions must never return the adress of automatic local variables.
> They can return;
> 1. The address of global variable.
> 2. The address of static local variable.
> 3. The address of a string literal.
> 4. The address of a dynamic variable.
> 5. The address of a parameter, iff the parameter is the object itself.

### Important Topics Related to Pointers
- Functions with pointer parameters
- Pointers and `const` keyword
- Address returning functions
- String literals
- Type alias declarations(`typedef` declarations)
- Pointer Arithmetic
- Pointer Arrays
- Pointer to Pointer
- Void Pointers
    - `void*` and `void**` difference
- Function Pointers
    - Function Pointer Arrays
    - Functions Returning Function Pointers
    - Call Back
- Multi-Dimensional Arrays
    - Functions Taking Multi-Dimensional Arrays as Parameter
- Dynamic Memory Management
- Array Decay / Function to Pointer Conversion
