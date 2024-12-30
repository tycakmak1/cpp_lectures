# LECTURE 11
## Classes
### Const Member Functions(continued)
#### `mutable` Keyword
```cpp
class Myclass {
public:
    void print()const {
        //..
        _debug++;   // Since print is a const member func, it cannot change the value of
                    // _debug. To get around that we define _debug as mutable int _debug.
                    // This let's const member funcs to change the values of the instance.
                    // This also let's us change those values by using "." (dot operator).
    }
private:
    int _dd, _mm, _yy;
    mutable int _debug;
}; // class Myclass

int main() {
    Myclass const m;
    m._debug = 5;   // Because _debug is mutable, this assignment is not a syntax error even
                    // though m is const.
    return 0;
}
```
##### ###REMARK###
> Non-static data members of a `class` may not be directly related to the observable state of the instance.

## Constructor(ctor) and Destructor(dtor)
Constructors
- Their names must be the same with the class name.
- They do not have a return type.
- They are non-static member functions of the class, meaning they can and do use `this` pointer.
- Cannot be a `static` member function.
- Cannot be a `const`  member function.
- Cannot be a global function.
- Can be overloaded.
- Does not have to be a public member function of the class, can be private or protected.
- `.` or `->` cannot be used to call a constructor.

Destructors
- Their names must be the same with the class name, but with one addition `~`.
- They do not have a return type.
- They are non-static member functions of the class, meaning they can and do use `this` pointer.
- Cannot be a static member function.
- Cannot be a const  member function.
- Cannot be a global function.
- Cannot be overloaded.
- Cannot have a parameter.
- Does not have to be a public member function of the class, can be private or protected.
- `.` or `->` can be used to call a destructor but must be very careful when doing so.

    Default Constructor
        For a ctor to be a default ctor, either it must not have any parameters,
        or every parameter of that ctor must have default values.

### Special Member Functions
Definitions of these functions can be written by the compiler under certain circumstances (called defaulting).<br>

Can happen in two different ways;
1. According to the rules of C++, compiler can (implicitly) declare these functions and can define them.
2. We can declare them and expect compiler to write their code.

There are 6 special member functions;
- Default ctor
- Destructor
- Copy Ctor
- Move Ctor             (added with C++11)
- Copy Assignment
- Move Assignment       (added with C++11)
- Copy Members
    - Copy Ctor
    - Copy Assignment
- Move Members
    - Move Ctor
    - Move Assignment

##### ###REMARK###
> - Global objects are constructed before the main function and destroyed after the main function.
>     If the number of global objects is  more than one, then they are constructed by their 
>     declaration order. The first object to be constructed is the last object to be destroyed.
> - Order of construction of global object instances from different source files is compiler dependent.
> - Static local class instances will not be constructed if the function is not called. Therefore will not be destroyed either.
>   They will be constructed when the function is called and will be destroyed after the main ends.
>     ##### ###REMARK### about static local object instances
>     > Only the first call to that function will result with instance creation, following calls will not create it again.
> - Non-static local variables are constructed when their scope begins, and are destroyed at the end of their scope.
> - Initializing a reference to an object instance does not call the constructor.
>
> ```cpp
> class Myclass {
>     Myclass();
>     ~Myclass();
> }; // class Myclass
> int main() {
>     Myclass  x;         // Will     call the constructor.
>     Myclass& r1_x = x;  // Will not call the constructor.
>     Myclass& r2_x = x;  // Will not call the constructor.
>     Myclass& r3_x = x;  // Will not call the constructor.
>     return 0;
> }
> ```

Construction of the elements of a class array is ordered by the array order.<br>
First element will be constructed first but destroyed last, and last element will be constructed last but destroyed first.

##### ###REMARK###
```cpp
class Myclass {
public:
    Myclass() {}
    Myclass(int x) { std::cout << "Myclass(int x) x = " << x << '\n'; }
}; // class Myclass
int main() {
    Myclass x1;         // Default initialization. Will call the default constructor.
    Myclass x2(10);     // Direct initialization. Will call Myclass(int).
    Myclass x3{10};     // Direct list(brace) initialization. Will call Myclass(int).
    Myclass x4 = 92;    // Copy initialization. Will call copy constructor
    Myclass x5();       // Function declaration, not a class object instantiation.
    return 0;
}
```

##### ###REMARK###
> A class does not have to have a default constructor.

##### ###REMARK###
> - Automatic storage duration objects are located in stack.
> - Static storage duration objects
> - Dynamic storage duration objects are located in free store (in C free store is called heap).

##### ###REMARK###
> - What does `new` operator do?<br>
>   `new` operator is used to create dynamic objects.<br>
>   `new` operator and `operator new()` are different from each other. <br>
>   `operator new()` is the C++ counterpart of `malloc()` in C.<br>
>   `operator new()` and `malloc()` allocate a space in the memmory and return the address with one difference, if `malloc()` fails to
>   allocate the space it returns `NULL`, if `operator new()` fails to allocate the space it throws an exception.
>
>   `new` operator uses `operator new()` to allocate a space on the memmory and then type casts
>   the returned value from `operator new()`, and calls the constructor of that class.
>   ```cpp
>   struct Myclass;
>   Myclass* m1 = new Myclass;
>   // This line actually does the following
>   static_cast<Myclass*>(operator new(sizeof(Myclass)))->Myclass();
>   // Constructors cannot be called by using . or -> operators. This demonstration is written like
>   // this to explain what compiler does. This code would be invalid if it were to be written by a developer.
>   ```
>
> - How to delete a dynamic object?<br>
>   `delete` operator takes the address of an instance and calls the destructor.<br>
>   `delete` operator and `operator delete()` are different from each other.<br>
>   `operator delete()` is the C++ counterpart of `free()` in C.
>   ```cpp
>   delete m1;
>   // This line actually does the following
>   m1->~Myclass();
>   operator delete(m1);
>   ```
>
> This was just a small peak at the dynamic instances.

##### ###REMARK###
> Special member functions can have one of the following states;
> 1. Not  Declared
> 2. User Declared
>     1. User Declared - Defined
>     2. User Declared - Defaulted
>     3. User Declared - Deleted
> 3. Implicitly Declared                    // Defined by the compiler.
>     1. Implicitly Declared - Defaulted
>     2. Implicitly Declared - Deleted

Constructor Initializer List (Member Initializer List)
1. Can only be used for ctors.
2. A ctor initializes the non-static data members of the instance it's going to construct.
3. Construction order of data members of a class, is always in the order of definition in the class.
4. Even if the ctor does not do anything in it's block, the block must exist.

```cpp
class Myclass {
public:
    Myclass() : _x{5}, _y{6}, _z(7) {   // This here is the ctor initializer list.
        //..
    }
private:
    int _x, _y, _z;
}; // class Myclass
```

##### ###REMARK###
> If there are members that are initialized in the Initializer List and some members that are not initilized then those members
> will be default initialized. This may cause syntax errors in some scenarios (e.g. `const` data members, reference data
> members, etc.).
> ```cpp
> class Myclass {
> public:
>     Myclass() : _x{10} {} // Because _x is initialized but _y is not, _y will be default initialized.
> private:
>     int _x, _y;
> }; // class Myclass
> ```

##### ###REMARK###
> - Using Initializer List and assigning the values inside of the ctor is different.
> - Initializer List initializes the members, but assigning their values inside the constructor is initializing them with default
>   values and then assigning the values to them.
> - That's why first choice must always be the ctor initializer list.

#### ###REMARK###
> - Data members of a class will always be initialized in the declaration order.
> - Initializer List order does not effect the member initialization order.

### Default Member Initializer (In-Class Initializer) ==> Not Actually an Initializer
```cpp
class Myclass {
public:
    Myclass() : _y{10} {}       // _x is not initialized here but since it has a Default Member Initializer,
                                // it will be initialized with 20.
private:
    int _x {20};                // Default Member Initializer. Could also be used with "="
                                // (e.g. int _x = 20) but () cannot be used.
    int _y;
}; // class Myclass
```
##### ###REMARK###
> Constructor Initializer List overrides the Default Member Initializer.
