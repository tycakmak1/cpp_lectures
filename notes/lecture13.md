# LECTURE 13

## Classes
### Special Member Functions
#### Move Members
- A class can be open to copy and open to move.
- A class can be closed to copy and open to move.
- A class can be closed to copy and closed to move.

Move members must leave the object they steal the resource from, in a valid state. An object whose resource is stolen, can be
reused in an assignment to it.

##### ###REMARK###
> Resource of a `const` object cannot be stolen (rules of the language prohibits this), nor you should try to steal it.

##### ###REMARK###
> `std::move()` is a `const` qualified function. So when the argument of move is a const, it also returns `const`.
> ```cpp
> class Myclass {
> public:
>     Myclass() = default;
>     Myclass(Myclass const&) {
>         std::cout << "copy constructor\n";
>     }
>     Myclass(Myclass&&) {
>         std::cout << "move constructor\n";
>     }
> }; // class MyCMyclasslass
>
> int main() {
>     Myclass x;
>     Myclass y = std::move(x);       // This line will call the move constructor.
>     Myclass const z;                // Since Myclass has no data members, this initialization is VALID.
>     Myclass t = std::move(z);       // This line will call the copy constructor, because resource of a
>     return 0;                       // const variable cannot be stolen.
> }
> ```

##### ###REMARK###
> CHECK THE `Special Member Functions.jgp` BEFORE DEFINING SPECIAL MEMBER FUNCTIONS.<br>
> To summarize;
> - If any of the destructor / copy constructor / copy assignment is declared, then move members are not declared.
> - There are no scenarios destructor does not exist.
> - Default constructor either defaulted or not declared.
> - If either of the move members is declared then copy members are deleted.

### placement `new`
> Constructors cannot be called by their names.
> ```cpp
> class Myclass;
> Myclass x;
> Myclass* ptr = &x;
> x.Myclass();                // Always a syntax error.
> ptr->Myclass();             // Always a syntax error.
> ```
> Destructors can be called by their names, but must not. There is only one exception to this rule, placement new operator,<br>
> a topic for later.
> ```cpp
> class Myclass;
> Myclass x;
> Myclass* ptr = &x;
> x.~Myclass();               // Can be done, but must not.
> ptr->~Myclass();            // Can be done, but must not.
> ```

#### ###REMARK####
> WHEN DEFINING COPY OR MOVE ASSIGNMENT, ALWAYS CHECK FOR SELF ASSIGNMENT, TO PREVENT DANGLING POINTERS.

### Delegating Constructor
    Is the constructor that calls another constructor.
```cpp
class Myclass {
public:
    Myclass(int x) : Myclass(x, 0, 0) {}
    Myclass(int x, int y, int z) : _x{x} , _y{y}, _z{z} {}
private:
    int _x, _y, _z;
}; // class Myclass
```
##### ###REMARK###
> Constructor Initializer List cannot be used in a delegating constructor.<br>
> Calling a constructor must be the only thing that delegating constructor should do.

### Temporary Objects
Life of a temporary object ends after the enclosing expression that contains the expression that creates the temporary object.
```cpp
class Myclass {
public:
    Myclass() {
        std::cout << "default constructor this = " << this << '\n';
    }
    Myclass(int a, int b) {
        std::cout << "a = " << a << " b = " << b << " this = " << this << '\n';
    }
    ~Myclass() {
        std::cout << "destructor this = " << this << '\n';
    }
    void foo() {
        std::cout << "Myclass foo() this = " << this << '\n';
    }
private:
    int _x{}, _y{};

}; // class Myclass

int main() {
    std::cout << "main starts here\n";
    Myclass{}.foo();                    // Yes this is VALID and a pr value expression,
                                        // this line creates a temporary object.
    std::cout << "main continues\n";
    return 0;
}
```
This code snippet will have the following output;
> main starts here<br>
> default constructor this =    // address goes here<br>
> Myclass foo() this =          // same address as before goes here<br>
> destructor this =             // same address as before goes here<br>
> main continues

BUT, binding it to an r value expression like,
```cpp
int main() {
    std::cout << "main starts here\n";
    Myclass&& x = Myclass{3, 5};
    std::cout << "main continues\n";
    return 0;
}
```
Would have the following output;
> main starts here<br>
> a = 3 b = 5 this =        // address<br>
> main continues<br>
> destructor this =         // same address as before

So binding a temp object to an r value expression extends the life of that temp object, untill the end of that reference's scope.<br>
This is called life extension.

### Reference Qualifiers
Non-static member functions can be called with L and R val. expr. class instances.
```cpp
class Myclass {
public:
    void foo() {};
    void bar() {};
}; // class Myclass

int main() {
    Myclass mx;
    mx.foo();           // L val. expr. VALID
    mx.bar();           // L val. expr. VALID
    Myclass{}.foo();    // R val. expr. VALID
    Myclass{}.bar();    // R val. expr. VALID
    return 0;
}
```

BUT there are such cases;
1. We want to disable the calling of functions for R value expression class instances.
2. We want to disable the calling of functions for R value expression and L value expression class instances.
3. We want to define different implementations.

```cpp
// Here foo() & is an L value reference qualifier.
void Myclass::foo() & { std::cout << "Myclass foo() & this = " << this << '\n'; }

// Here bar() && is an R value reference qualifier.
void Myclass::bar() && { std::cout << "Myclass bar() && this = " << this << '\n'; }

// Calling these functions in the following style would be;
Myclass x;
x.foo();                        // VALID
x.bar();                        // INVALID
Myclass{}.foo();                // INVALID
Myclass{}.bar();                // VALID
std::move(x).foo();             // INVALID
std::move(x).bar();             // VALID
```

##### ###REMARK###
> Member functions can be overloaded with reference qualifiers.

##### Why Do We Need Reference Qualifiers?
To prevent problems like assigning a value to an r value expression.
```cpp
Myclass x;
Myclass{} = x;  // This is not a syntax error, but it is illogical. To turn this into a syntax error,
                // we define assignment operator of the class as L value reference qualified.
// Like this
Myclass& Myclass::operator=(Myclass const&) & = default;
```

###REMARK###
> If one of the overloads of a member function is reference qualified, then all overloads of that function must be
> qualified.

### Conversion Constructors
```cpp
class Myclass {
public:
    Myclass();      // Default constructor
    Myclass(T);     // Also constructor but, ctors with one parameter are usually called conversion
                    // constructors. Because it creates an implicit conversion from T to Myclass.
}; // class Myclass

Myclass x;
x = 5;              // Implicit Conversion
```

##### ###REMARK###
> This type of conversion is called User-Defined Conversion(UDC).<br>
> Compiler can perform an implicit conversion in two ways;
> 1. Standard Conversion + User-Defined Conversion
> 2. User-Defined Conversion + Standard Conversion<br>
>
> Both are implicit conversions, but compiler cannot perform an implicit conversion in the form of;<br>
> User-Defined Conversion + User-Defined Conversion.
> ```cpp
> class A {};
> 
> class B {
> public:
>     B(A);
> }; // class B
> 
> class C {
> public:
>     C(B);
> }; // class C
>
> A ax;
> B bx  = ax;   // VALID, compiler performs UDC implicitly.
> C cx  = bx;   // VALID, compiler performs UDC implicitly.
> C cx1 = ax;   // INVALID, because this needs UDC + UDC. To perform this we can use explicit cast.
> C cx1 = static_cast<B>(ax); // VALID, compiler performs a standard conversion.
> ```
>
> To prevent the compiler performing an implicit conversion, we use `explicit` keyword in constructor definition. Means that
> constructor does not allow implicit conversion, only explicit conversion.
> ```cpp
> class Myclass {
> public:
>     Myclass();
>     explicit Myclass(T);
> }; // class Myclass
> ```
> Some important rules about `explicit`;
> 1. If it's defined in class definition (inline definition), `explicit` keyword does not have to be in the definition.
> ```cpp
> class Myclass {
> public:
>     Myclass();
>     explicit Myclass(T);
> }; // class Myclass
>
> Myclass::Myclass(T x){}                 // This is the correct way.
> explicit Myclass::Myclass(T x){}        // This is the wrong way.
> ```
> 2. If copy initialization requires an implicit conversion, explicit conversion constructor will cause a syntax error.
> ```cpp
> class Myclass {
> public:
>     Myclass();
>     explicit Myclass(int);
> }; // class Myclass
> int main() {
>     Myclass m = 10;                 // This is a syntax error.
> }
> ```
> 3. Explicit functions are omitted from viable functions list in function overloading resolution.
> 4. Conversion constructors can have more than 1 parameters, but in practice this is rare.


##### ###REMARK###
> 99% of the time we want conversion ctors to be `explicit`.

### Copy Elision
Not performing the copying, or escaping from the copying. Sometimes referred to as copy elimination. There is a copy performing
code but compiler produces a code that does not copy, hence the naming. With the C++17, some of the copy elision scenarios are
switched from optional (usually called optimization) to mandatory.

```cpp
class Myclass {
public:
    Myclass() { std::cout << "Myclass default constructor\n"; }

    Myclass(Myclass const&) { std::cout << "Myclass copy constructor\n"; }
};

void func(Myclass) {}

// This one is usually called Return Value Optimiziation, RVO.
Myclass foo() { return Myclass{}; }

//There is another type of RVO, which is called Named Return Value Optimization, NRVO.
Myclass bar() {
    Myclass m;
    return m;
}

int main() {
    func(Myclass{});
    Myclass m1 = foo();         // RVO
    Myclass m2 = bar();         // NRVO
    return 0;
}
```
Expected output for this code snippet is
> Myclass default constructor<br>
> Myclass copyctor<br>
> Myclass default constructor<br>
> Myclass copyctor

BUT it actually is
> Myclass default constructor<br>
> Myclass default constructor

Copy constructor is not called because compiler decides that since the temp object is not gonna be used, instead of creating that
temp object in `main()` and pass it to the `func(Myclass)` by value, it creates the temp object in the scope of `func(Myclass)`.<br>
In other words compiler elides copying, hence the name Copy Elision.<br>
This exact example was considered as optimization but with C++17 it is mandatory. So if copy constructor to be deleted, it would be a
syntax error on standarts before C++17.
