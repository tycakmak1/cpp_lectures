# LECTURE 15
## Operator Overloading
Compile time mechanism. has nothing to do with runtime.

There are two types of operator functions;
1. Global Operator Function
2. Member Operator Function (has to be non-static)

### General Rules of Operator Overloading
- This mechanism is only viable to class types. It also viable for enum type but that's an exception to this rule.
- One of the operands must be class type. IF both of them are primitive types, it cannot be done.
- Must be one of the existing operators in the C++. In other words, a non-existing operator cannot be overloaded.
- There are some operators that cannot be overloaded;
    - Dot `.` Operator
    - `sizeof` Operator
    - Ternary (`?:`) Operator
    - Scope Resolution (`::`) Operator
    - `.*` Operator
    - `typeid` Operator
- There are certain rules that must be followed for naming operator functions. Keyword operator followed by the token of the operator.
    - `operator+`
    - `operator==`
    - `operator++`
    - `operator()`
    - `operator&`
    - `operator=`   // This is the assignment operator, it's also a special member function.
- All operator functions can be called by their names. In some cases it is necessary to do so.
    ```cpp
    int main() {
        using namespace std;
        int x = 10;
        double y = 4.5;
        cout << x << " " << y << '\n';
        operator<<(cout.operator<<(x), " ").operator<<(y).operator(endl);
        return 0;
    }
    ```
- For some operators we can only create member operator functions;
    - `[]`
    - `->`
    - `type cast`
    - `()`
    - `=`
- Operator functions cannot take default arguments, there is only one exception to this rule, which is `()`.
- Arity of operators must stay the same. Meaning, if an operator is binary, then it's overload also must be binary.
    ```cpp
    a < b
    operator<(T& a, T& b);      // VALID
    operator<(T& a);            // INVALID
    ```
- If an operator overload is a member operator overload, then the function will always be called for the left hand side operand.
    RHS operand will be passed as an argument to the function.
- There are four operator tokens such that they are two different operators. Thus they can be overloaded both with two
    parameters and one.
    - `operator+`
        ```cpp
        a + b   // Addition
        +a      // Sign Operator
        ```
    - `operator-`
        ```cpp
        a - b   // Subtraction
        -b      // Sign Operator
        ```
    - `operator&`
        ```cpp
        a & b   // Bitwise and
        &a      // Address Operator
        ```
    - `operator*`
        ```cpp
        a * b   // Multiplication
        *a      // Dereferencing
        ```

- Function overloading and operator overloading are different, but related to each other.
- Operator precedence or operator associativity cannot be changed.
- Value categories of overloaded operator functions must be the same with the original value category.
    - `++x` must have the `T&` return type, because `++x` has the L value category.
    - `x++` must have the `T` return type, because `x++` has the PR value category.
    - `operator[]` must be L value, since it yields an instance.
    - `operator=` must have `T&` with the same logic.
    - Sign operators must have `T`.

##### ###REMARK###
> `const` correctness is important in operator overloading.
> ```cpp
> class Myclass {
> public:
>     // Since the addition does not change the valueo of *this, it must be const.
>     Myclass operator+(Myclass const& other) const { return { _x + other._x, _y + other._y }; }
> 
>     // But the assignment operator will change the value of *this, so it cannot be const.
>     Myclass& operator=(Myclass const& other) {
>         _x = other._x;
>         _y = other._y;
>         return *this;
>     }
> 
>     int _x, _y;
> }; // class Myclass

##### Then Why Do We Have Global Operator Functions?
1. Because, we can overload the user defined types but not the existing types.
    ```cpp
    class T;
    T + 5;  // Can be achieved by member operator overloading.
    5 + T;  // Cannot be achieved by member operator functions. To do this
            // we use global operator functions, and we call global operator functions by their names.
    ```
2. For scenarios such that we have to use two different class types as operands.
    ```cpp
    class T;
    T x;
    std::cout << x; // cout and x have different class types.
    ```

#### Some Advices on How to Decide Whether an Operator Function Should be Member or Global
1. Symmetric binary operators should be global.<br>
    `a < b` and `b < a`<br>
    `<` is a symmetric binary operator. Operation performed is the same for both styles.

##### ###WARNING###
> Do not define both a member and a global operator function exactly the same. This will cause
> ambiguity error.
> ```cpp
> class Myclass {
> public:
>     Myclass operator+(int) const&;
> }; // class Myclass
>
> Myclass operator+(Myclass const&, int);
>
> // This will cause ambiguity error.
> ```

2. If the operation changes the class instance, as a general rule it should be a member.
3. Unary and asymmetric binary operators, should be members. Again, as a general rule.

##### ###REMARK###
> Existence of two operators in a compound operator does not imply the existence of the compound
> operator itself.
> ```cpp
> class Myclass {
> public:
>     Myclass& operator=(Myclass const&);
>
>     bool operator<(Myclass const&) const;
> }; // class Myclass
> ```
> Having these two operators does not imply `<=` can be used.

##### ###REMARK###
> If you are overloading `<<` and `>>` for input/output for a class, include `iosfwd` instead of `iostream` if you are defining the
> operators in the implementation (cpp) file. If you are defining them inline then you have to use `iostream`. The difference
> between `iosfwd` and `iostream` is that `iosfwd` contains the forward declarations of `iostream`, so it is lighter.
> ```cpp
> // Myclass.h
> #include <iosfwd>
> class Myclass {
> public:
>     friend std::ostream& operator<<(std::ostream&, Myclass const&);
> }; // class Myclass
>
> // Myclass.cpp
> #include <iostream>
> std::ostream& operator<<(std::ostream& out, Myclass const& m) {
>     //.. code goes here
>     return out;
> }
> ```
> but for inline definitions
> ```cpp
> // Myclass.h
> #include <iostream>
> class Myclass {
> public:
>     friend std::ostream& operator<<(std::ostream& out, Myclass const& m) {
>         //.. code goes here
>         return out;
>     }
> }; // class Myclass
> ```
> or
> ```cpp
> // Myclass.h
> #include <iostream>
> class Myclass {
> public:
>     friend inline std::ostream& operator<<(std::ostream& out, Myclass const& m);
> }; // class Myclass
>
> std::ostream& operator<<(std::ostream& out, Myclass const& m) {
>     //.. code goes here
>     return out;
> }
> ```

##### ###REMARK###
> When overloading comparison operators, the most common practice is defining `==` and `<` operators and, using them in
> other overloads. Since they are symmetric binary operators, they are generally defined as global operators.
> ```cpp
> bool operator==(T const& t1, T const& t2) {
>     return t1.val == t2.val;
> }
> bool operator<(T const& t1, T const& t2) {
>     return t1.val < t2.val;
> }
>
> For other operators we use these two again;
> bool operator!=(T const& t1, T const& t2) {
>     return !(t1 == t2);
> }
>
> bool operator>(T const& t1, T const& t2) {
>     return t2 < t1;
> }
> ```
> ##### ###REMARK###
> > With C++20, if you overload the `==` operator, compiler will default the `!=`. Meaning you will not have to overload `!=`
> > operator. With C++20 there is also `<=>` operator.

4. Assignment operators should be member operators, but arithmetic operators should be global operators.
5. When overloading `+=` and `+` operators, first overload `+=` and then call `+=` inside the `+` operator.
    ```cpp
    class T {
        int _val;
    public:
        T& operator+=(T const& t) {
            _val += t._val;
            return *this;
        }
    }; // class T
    inline T operator+(T const& lhs, T const& rhs) {
        return T{lhs} += rhs;
    }
    ```
6. Suffix/postfix and prefix increment and decrement operators have the same syntax, how to differentiate them in operator function?
    ```cpp
    class T {
        int _val;
    public:
        // This is prefix
        T& operator++() & {
            ++_val;
            return *this;
        }

        // This is postfix
        T operator++(int) {
            T return_val{*this};
            ++*this;
            return return_val;
        }
    }; // class T
    ```

These operator functions will be studied separately.
- `[]`      Index Operator Function
- `*` `->`  Dereference and Arrow Operator Functions
- `()`      Function Call Operator Function
- Type Casting Operator Functions

### Index Operator Overloading
- Must be a member function.
- Must return an L-Value reference.
##### ###REMARK###
> For Array-Like Classes there are two overloads of `[]` operator. One for `const` objects and one for non-const objects.<br>
> `const` overload will return a `T const&` and non-const overload will return `T&`. This way trying to change an element of a `const
> object will cause a syntax error.
> ```cpp
> class Name
> {
> public:
>     Name(char const* p) : mp{new char[strlen(p) + 1]} {
>         std::strcpy(mp, p);
>     }
>
>     void print() const {
>         std::cout << mp << '\n';
>     }
>
>     char& operator[](std::size_t idx) {
>         return mp[idx];
>     }
>
>     char const& operator[](std::size_t idx) const {
>         return mp[idx];
>     }
> private:
>     char* mp;
> }; // class Name
>
> int main() {
>     Name const myname{"jack"};
>     myname.print();   // This line will print out jack.
>     myname[0] = 'y';  // This line will cause a syntax error because myname is const.
> }
> ```

### Array-Like Classes
- `std::vector`
- `std::deque`
- `std::string`
- `std::array`
- `std::bitset`
- `std::map`<br>

These classes have overloads for `[]` operator.

### Pointer-Like Classes
They store the location information of elements in a container.<br>
`std::iterator`
```cpp
std::vector<std::string>           svec  = {"john", "jack", "jane"};
auto                               iter1 = svec.begin();
std::vector<std::string>::iterator iter2 = svec.begin() + 1;
std::cout << *iter1 << ' ' << *iter2 << ' ' << iter2->size(); // This line will print "john jack 4".
```
`iter1` and `iter2` belongs to `iterator` class. It is a pointer-like class.

### Smart Pointers
They act like `iterators`, both have `*` `->` and `++` operators overloaded. Iterators are used to grant access to the elements of
the data.<br>
Smart pointers are used to point to dynamic instances.
