# LECTURE 14
## Classes
### Static Data Members of Classes
```cpp
class Myclass {
    int  a;     // Data Member
    void foo(); // Member Function

    struct Data {}; // Member Type
}; // class Myclass
```

Static data members of classes are the elements of the class, not the instance. They can be accessed via class instances or pointers
to class instances but doing in that form is misleading. Instead, we use the scope resolution operator `::`. It is misleading because
it creates the impression that an operation is performed on the instance, but when it's about static members, we are not. This is
why they are usually referred to as elements of the class, instead of the instance.
```cpp
class Myclass {
public:
    static int _sta_x;
}; // class Myclass

int main() {
    Myclass  m1;
    Myclass* ptv_m1 = &m1;
    m1._sta_x;      // Viable but misleading.
    ptv_m1->_sta_x; // Viable but misleading.
    // Instead we use scope resolution operator(::)
    Myclass::_sta_x;
    // but we cannot assign a value to it inside the class.
    // Because the line "static int _sta_x;" in class declaration is a non-defining
    // declaration.
    return 0;
}
```

#### How Do We Define Static Data Members?
Declaration is in the class, but definition can be in the .cpp file of the class header or in the global scope.
e.g. for .cpp definition
```cpp
// Myclass.h
class Myclass {
public:
    static int _sta_x;
}; // class Myclass

// Myclass.cpp
//#include "Myclass.h"
int Myclass:_sta_x;
int Myclass:_sta_x = 10;
int Myclass:_sta_x(10);
int Myclass:_sta_x{};
int Myclass:_sta_x{10};
```
e.g. for global scope definition
```cpp
// Myclass.h
class Myclass {
public:
        static int _sta_x;
}; // class Myclass
int Myclass::_sta_x;
int Myclass::_sta_x = 10;
int Myclass::_sta_x(10);
int Myclass::_sta_x{};
int Myclass::_sta_x {10};
```

- `static` keyword has to be used in declaration but not in definition.
- Static data member can be of an incomplete type.
    ```cpp
    class Myclass1;         // Incomplete type
    class Myclass2 {
        Myclass1 _data1;    // This is a syntax error. non-static data members must be complete types.
        static Myclass1 _sta_data2; // This is not a syntax error because static data members
                                    // can be of an incomplete type.
    }; // class Myclass2
    ```
- A class cannot contain a member with a type of itself, unless it is static.
    ```cpp
    class Myclass {
        Myclass        _x;      // This is a syntax error because Myclass is not complete.
        static Myclass _sta_x;  // This is allowed, because static data members can be an incomplete type.
    }; // class Myclass
    ```
- If the static data member is a const integral type then you can define it in the class definition (`enum`, `char`, `signed char`,
    `unsigned char`, `long, long long`, `bool` are also integral type).
    ```cpp
    class Myclass {
        static int                 _sta_x1 = 5;     // INVALID not const.
        static double const        _sta_x2 = 3.5;   // INVALID not an  integral type.
        static int const           _sta_x3 = 5;     // VALID const and integral type.
        static long const          _sta_x4 = 7;     // VALID const and integral type.
        static long long const     _sta_x5 = 8;     // VALID const and integral type.
        static char const          _sta_x6 = 0;     // VALID const and integral type.
        static signed char const   _sta_x7 = 9;     // VALID const and integral type.
        static unsigned char const _sta_x8 = 9;     // VALID const and integral type.
    }; // class Myclass
    ```
- Static data members and global variables can be defined with `inline` keyword. (C++17)
    Inline variable:
    ```cpp
    inline int _sta_x = 5;  // This guarantees that in the link phase there will only be one _sta_x.
    // file1.cpp
    inline int _sta_x = 6;
    // file2.cpp
    inline int _sta_x = 6;
    // file3.cpp
    inline int _sta_x = 6;
    // There will only be one _sta_x. This is about ODR.
    ```
    ```cpp
    // Myclass.h
    class Myclass {
    public:
        inline static int    _sta_x1 = 5;   // If inline keyword is used, const and integral type rule
        inline static double _sta_x2 = 5.3; // is not necessary. So both are valid now.
    }; // class Myclass
    ```
- Since static data members not actually part of the instances, they cannot be initialized with constructors.
    ```cpp
    class Myclass {
        int _x, _y;
        static int _sta_ival;
    public:
        Myclass(){}
        Myclass(int x, int y) : _x{x}, _y{y} {}                         // VALID
        Myclass(int x, int y, int z) : _x{x}, _y{y}, _sta_ival{z} {}    // INVALID
        Myclass() : _x{10}, _y{20}, _sta_ival{30} {}                    // INVALID
    }; // class Myclass
    ```

### Static Member Functions
```cpp
class Myclass {
public:
    void foo();         // Non-static member function.
    static void bar();  // Static member function.
}; // class Myclass
```
- In the class scope but do not have a "this pointer". meaning they are called without an address of an instance.
- Since they do not have a "this pointer", they cannot be const functions.
- To call them, an instance is not required.
    ```cpp
    class Myclass {
    public:
        void foo();
        static void bar();
    }; // class Myclass

    int main() {
        Myclass::foo(); // Syntax error.
        Myclass::bar(); // Valid.
    }
    ```

- To summarize, they are not related to the instance itself but to the class, just like the static data members.
- Since they are members of the class, they can access the private members of the class.
- Have access modifiers.
- They can be defined as inline functions in the class.
- The trick in PUBLIC and PRIVATE macros to determine the function's access modifier, can also be used for static.
- Since they do not have a this pointer, they cannot use non-static data members of the class as unqualified name, but static
    member functions can use unqualified names to access the static data members of the class.
- Just like static data members, they can be accessed using dot and arrow operators, but just like static data members, they should not.
- Pointers to static member functions are defined the same way as pointers to global functions.

##### ###REMARK###
> ```cpp
> class Myclass {
> public:
>     static int foo() { return 777; }
>
>     static int _sta_x;
> }; // class Myclass
>
> int foo() { return 5; }
>
> int Myclass::_sta_x = foo();   // This line will call the foo in class  scope.
> Myclass::_sta_x     = ::foo(); // This line will call the foo in global scope.
>
> int main() {
>     std::cout << "_sta_x = " << _sta_x
>               << '\n'; // Will have the output "_sta_x = 777". Because the name
>                        // in the expression that's  initializing the static data member
>                        // will be searched in class scope first.
> }
> ```

### Named Constructor Idiom
There are scenarios where we want to disable the object instantiation. To do that we declare constructors as private members of
the class, but to be able to use them under certain circumstances we define a public member function to call them. This is called
Named Constructor Idiom. It is a function that calls the constructors but is not categorized as special member function. It is one of
the typical scenarios that static member functions are used.
```cpp
class Complex {
    Complex(double x, double y) { std::cout << "Complex cartesian\n"; }

    Complex(double angle, double distance, int) { std::cout << "Complex polar\n"; }

public:
    static Complex create_cartesian(double x, double y) { return Complex(x, y); }

    static Complex create_polar(double angle, double distance) { return Complex(angle, distance, 0); }
}; // class Complex
```

### Static Global Functions



### Friend Declarations
- Private members of a class cannot be accessed except the class members. To give a global function the privilege to access the
private members of a class, we use the `friend` keyword.
- `friend` keyword works either all-in or none, it cannot be choosen which members it gives access to. It grants access to all of the
private members.
- Friendship can also be granted to a class.

Friend declaration can be used to;
1. Grant private member access to a function in a namespace.
    ```cpp
    class Myclass {
        void foo();
        int  _sta_x;
    public:
        friend void func(Myclass);
    }; // class Myclass
    void func(Myclass pm) {
        Myclass m;
        pm.foo();   // Without the friend declaration, would be an access control error.
        pm._sta_x;  // Without the friend declaration, would be an access control error.
        m.foo();    // Without the friend declaration, would be an access control error.
        m._sta_x;   // Without the friend declaration, would be an access control error.
    }
    ```
2. Grant private member access to a member function of a different class.
    ```cpp
    class Myclass {
        friend std::ostream& operator<<(std::ostream&, Myclass const&);

        int _x;
    }; // class Myclass

    std::ostream& operator<<(std::ostream& out, Myclass const&) { return out << _x; }

    // OR

    class Myclass {
        friend std::ostream& operator<<(std::ostream& out, Myclass const& m) { return out << _x; }

        int _x;
    }; // class Myclass
    ```
3. Grant private member access to every function of a different class.
    ```cpp
    class A;

    class B {
        friend class A; // With this expression class B grants friendship to class A.
    }; // class B
    ```

##### ###REMARK###
> - `friend` functions can be defined in the class, BUT THEY STILL ARE GLOBAL FUNCTIONS.
> - These kind of `friend` functions are called hidden friend functions and they are frequently used.
> ```cpp
> class Myclass {
>     void foo();
>     int _sta_x;
> public:
>     // This functions is still a global funtion, so it can be called without a class instance.
>     friend void func(Myclass x) { return x._sta_x; }
> }; // class Myclass
> ```
> ##### ###REMARK###
> > Hidden friend functions can be defined in the public, private and protected sections of a class. Since they are not
> > member functions, they do not get affected by the access modifiers.
> > ```cpp
> > class Myclass {
> > public:
> >     friend void foo() { std::cout << "foo()\n"; }
> > protected:
> >     friend void bar() { std::cout << "bar()\n"; }
> > private:
> >     friend void baz() { std::cout << "baz()\n"; }
> > }; // class Myclass
> > void foo();            // VALID
> > void bar();            // VALID
> > void baz();            // VALID
> > ```

- Friend declaration can be done in public and private sections of the class, and it would not have any difference.
- The downside of friend declaration is that when a change made in the private section of a class, friend functions of that class
    MUST be revisited.

Some rules about friend declaration;
1. `class A` granting friendship to `class B`, does not imply that `class B` grants a friendship to `class A`.
2. Friend of a friend is not a friend. Meaning friendship is not transitive. Meaning, `class A` granting friendship to `class B`, and
    `class B` granting friendship to `class C` does not imply that `class A` grants friendship to `class C`.
3. Friends of base classes are not friends of derived classes.
