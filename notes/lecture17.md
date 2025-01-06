# LECTURE 17
## Namespaces

There are three ways to use a name in the namespace without qualifying.
1. `using` Declaration

- using declaration is a declaration and just like every other declaration it has a scope.<br>
`using std::cout;`
- The name that was used in the `using` declaration is injected to the namespace it was declared in.
    ```cpp
    namespace ns {
    int x = 10;
    } // namespace ns

    int main()
    {
        using ns::x;
        int x = 20; // This will cause a syntax error because x already exists
        return 0;   // in the scope of main because of the using declaration.
    }
    ```
    This can also happen in a global namespace.
    ```cpp
    int x = 10;

    int main() {
        using ::x;
        int x = 21; // This will cause a syntax error because x already exists
        return 0;   // in the scope of main because of the using declaration.
    }
    ```
    ```cpp
    int x = 10;

    namespace ns {
    using ::x;
    } // namespace ns

    int main() {
        using ns::x;    // This is also viable because, in ns namespace, with using ::x
                        // the x that is in the global namespace was injected to the ns
        return 0;       // namespace. Thus ns namespace has a name x.
    }
    ```
- Using declaration of names that belong to different namespaces cause name masking.
    ```cpp
    namespace ns1 {
    int x = 10;
    } // namespace ns1

    namespace ns2 {
    int x = 11;
    } // namespace ns2

    int main()
    {
        using ns1::x;   // Using these two together causes redeclaration of x.
        using ns2::x;   // Using these two together causes redeclaration of x.
        return 0;
    }
    ```
- Using declaration with functions.
    ```cpp
    namespace ns1 {
    void func(int) { std::cout << "ns1::func(int)\n"; }
    } // namespace ns1

    namespace ns2 {
    void func(int, int) { std::cout << "ns2::func(int, int)\n"; }
    } // namespace ns2

    void func() { std::cout << "global func()\n"; }
    int main()
    {
        using ns1::func;    // This is function overloading because now both Functions
                            // exist in the main scope.
        using ns2::func;    // This is function overloading because now both functions
                            // exist in the main scope.
        //func();           // This will cause a syntax error because global func is
                            // being masked by using ns1::func
                            // using and ns2::func. to get around this we can use
                            // using ::func.
        ::func();           // This is also a way to call global func.
        func(12);           // This will call ns1::func(int)
        func(12, 13);       // This will call ns2::func(int, int)
        return 0;
    }
    ```
- With the C++17 standard using declarations can be separated by coma.
    ```cpp
    using ns1::func;
    using ns2::func;
    ```
    and
    ```cpp
    using ns1::func, ns2::func;
    ```
    are the same.

- Can be used for nested namespaces.
    ```cpp
    namespace ns1 {
    int a, b;
    namespace ns2 {
    double x, y;
    } // namespace ns2
    } // namespace ns1

    using ns1::ns2::x;      // This is valid.
    ```

2. `using namespace` (directive) Declaration
- this is also a declaration, so it also has a scope.
    ```cpp
    namespace ns {
    int a, b;
    void foo() {}
    } // namespace ns

    int main()
    {
        using namespace ns; // Without this, the following three lines are invalid.
        a = 1;
        b = 2;
        foo();
    }
    ```

- Unlike `using` declaration, `using namespace` declaration does not inject. It only makes the inside of the namespace visible in
    the scope of `using` declaration, but even without the injection name masking and ambiguity errors can exist.
    ```cpp
    namespace ns1 {
    int x = 5;
    } // namespace ns1

    namespace ns2 {
    double x = 4.9;
    } // namespace ns2

    using namespace ns1;
    using namespace ns2;

    int main() {
        ++x;        // This causes ambiguity error because there are two viable names. One in ns1, one in ns2.
        return 0;
    }
    ```
    ```cpp
    namespace ns {
    int x = 5;
    } // namespace ns

    int main() {
        using namespace ns;
        int x = 6;
        std::cout << x << '\n'; // This line will print out 6. Because the x inside the main masks the one in ns.
    }
    ```
- Using declaration vs using namespace declaration.
    ```cpp
    namespace ns {
    int x;
    } // namespace ns

    int main() {
        using ns::x;    // This is INVALID because the x in ns namespace is injected to the scope of main and causes
        int x = 5;      // redeclaration.
        // BUT
        using namespace ns; // This is VALID because the x in ns namespace is not injected to the scope of main,
        int x = 5;          // it is only visible.
        return 0;
    }
    ```
##### ###REMARK###
> As a general rule keep the scopes of using declarations and using namespace declarations as tight as possible to prevent
> errors. Safest way is always to use the qualifiers.

3. ADL (Argument Dependent Lookup)
```cpp
namespace ns {
class Data {}; // class Data

void foo(Data) {}

void bar(int) {}
} // namespace ns

int main() {
    ns::Data x;
    foo(x); // Syntax error expected but it is perfectly legal.
    bar(3); // Syntax error.
    return 0;
}

```
##### ###REMARK###
> If a name that is part of an argument of a function call has a `type` that is declared in a namespace, then the function will be
> searched in that namespace as well. Notice that we specified as `type` not as a `class`. This means it is also applicable for
> `enum`, `enum class` and `template specializations`(e.g. `std::vector<int>`).

```cpp
namespace ns {
class A {}; // class A

void func(A) {}
} // namespace ns

void func(ns::A) {}

int main() {
    ns::A x;
    func(x); // Ambiguity error.
}
```

```cpp
int main() {
    std::cout << "Hello World!\n";      // This line has ADL. Because the << operator used in here belongs to
                                        // the std scope but it's not a member function. It's the same as
    operator<<(Std::cout, "Hello World\n"); // this line.
                                        // But we did not specify the namespace before operator<<.
                                        // This is thanks to the ADL. Since a name in the argument of a function
                                        // call is declared in a namespace that namespace will also be searched for
                                        // the function.
    return 0;
}
```

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
int main() {
    std::vector<int> ivec(100);
    sort(begin(ivec), end(ivec));   // All three of the names in this line is unqualified but it is VALID.
                                    // This happens because ivec has a type that was declared in std, and the return
                                    // types of begin() and end() functions are again declared inside of the
                                    // std namespace. That's why this line is VALID.
    return 0;
}
```

### Anonymous(Unnamed) Namespaces
- Creates internal linkage. Meaning there can be variables, functions or classes with the same name but in different files. Since
    it is an internal linkage, it does not defile ODR.
- Main usage is to define names internally. When used globally, static keyword creates internal linkage but it cannot be used for
    classes, this idiom can be used for class definitions as well.
- From compiler's perspective the namespace has a name but after the closing bracket of the namespace, there is a using
    namespace declaration for that same namespace. This declaration is done globally, therefore no need to qualify the names
    inside of it toaccess them.
- Even though it is not necessary, scope resolution operator can be used to access the names inside the anonymous namespace.
    ```cpp
    namespace {
    int x = 5;
    } // namespace
    
    int main() {
        int a = x;   // VALID, both mean the same thing.
        int b = ::x; // VALID, both mean the same thing.
        return 0;
    }
    ```
- Since it is still a namespace, they are cumulative as well.

###### ###REMARK###
> With modern C++ there is an opportunity to define nested namespaces in a different way.
> ```cpp
> namespace ns1 {
> namespace ns2 {
> int x;
> } // namespace ns2
> } // namespace ns1
>
> ns1::ns2::x = 5;
>
> namespace ns1::ns2 {
> int x;
> } // namespace ns1::ns2
>
> ns1::ns2::x = 5;
> ```
> Can also be used in cumulative ways.
> ```cpp
> namespace ns1 {
> int x = 5;
> } // namespace ns1
>
> namespace ns1::ns2 {
> int y = 6;
> } // namespace ns1::ns2
> ```

### Inline Namespace
- Names inside of an inline namespace are visible from the enclosing namepace.
```cpp
namespace ns1 {
inline namespace ns2 {
int x = 5;
} // namespace ns2
} // namespace ns1

int main() {
    int t1 = ns1::ns2::x; // VALID, both mean the same thing because of "inline".
    int t2 = ns1::x;      // VALID, both mean the same thing because of "inline".
}
```
This can also be achieved with a using declaration.
```cpp
namespace ns1 {
namespace ns2 {
int x = 5;
} // namespace ns2

using namespace ns2;
} // namespace ns1

int main() {
    int t1 = ns1::ns2::x; // VALID, both mean the same thing.
    int t2 = ns1::x;      // VALID, both mean the same thing.
}
```
- Since this is equivalent of a using namespace declaration in the enclosing namespace, using a name to declare a variable
    inside the enclosing namespace with a same name from the inner namespace will cause ambiguity.
- There are scenarios where using a `using namespace` declaration instead of using `inline namespace` will prevent ADL from happening.
- Became a popular tool for version control.
    ```cpp
    #define VERSION_1 // or VERSION_2

    namespace ns {
    #ifdef VERSION_1
    inline namespace version_1 {
    class Myclass {
        //.. code goes here
        //.. code goes here
    }; // class Myclass
    } // namespace version_1
    #endif
    #ifdef VERSION_2
    inline namespace version_2 {
    class Myclass {
        //..different code goes here
        //..different code goes here
    }; // class Myclass
    } // namespace version_2
    #endif
    } // namespace ns

    int main() {
        ns::Myclass m; // VALID
        return 0;
    }
    ```
- With C++20, there is another tool to define inline namespaces.
    ```cpp
    namespace ns1::ns2::inline ns3 {
    int x = 5;
    } // namespace ns1::ns2::inline ns3

    int main() {
        int a = ns1::ns2::x;
        return 0;
    }
    ```

### Namespace Aliases
- Generally used to make it easier to read nested namespaces.
```cpp
namespace ns1 {
namespace ns2 {
namespace ns3 {
int x = 5;
} // namespace ns3
} // namespace ns2
} // namespace ns1

int main() {
    namespace ns123 = ns1::ns2::ns3;
    int a           = ns1::ns2::ns3::x; // VALID, both mean the same thing.
    int b           = ns123::x;         // VALID, both mean the same thing.
    return 0;
}
```
- Used to be used for version control, but now inline namespaces are better alternatives to this.
```cpp
namespace taha_yasin_cakmak_pro_xyz_lib
{
int x = 5;
} // namespace taha_yasin_cakmak_pro_xyz_lib
namespace tyc = taha_yasin_cakmak_pro_xyz_lib;
int main()
{
int a = taha_yasin_cakmak_pro_xyz_lib::x;   // VALID, both mean the same thing.
int b = tyc::x;                             // VALID, both mean the same thing.
return 0;
}
```

## Nested Types(Type Member)
```cpp
class Myclass {
    class Nested {}; // class Nested
}; // class Myclass
```
- Name lookup for the names used inside of a member function and the name lookup for the names used inside of the class
    definition are different from each other.
    ```cpp
    class Myclass {
    public:
        void foo();
        void bar();

    private:
        int _x;
    }; // class Myclass

    void Myclass::foo() {
        bar();  // VALID
        _x = 5; // VALID
        return;
    }
    ```

    BUT

    ```cpp
    class Myclass {
    public:
        void foo() {
            Word x = 5; // VALID
        }

        Word          _x; // INVALID
        Myclass::Word _y; // INVALID
        typedef int   Word;
    }; // class Myclass
    ```

    ```cpp
    class Myclass {
    public:
        static inline int _sta_x = foo(); // INVALID, it would be VALID if foo were to be defined before _sta_x.

        static int foo() { return 5; }
    }; // class Myclass
    ```

- Member functions of the enclosing type cannot access to the private part of the nested type. To be able to do this, function of
    the enclosing type must be a friend function of the nested type. BUT nested type can access to the private part of the
    enclosing type, because it is a member of the enclosing type.
    ```cpp
    class Myclass {
        class Nested {}; // class Nested
    public:
        static Nested foo();
    }; // class Myclass

    int main() {
        Myclass::Nested x = Myclass::foo(); // INVALID, access control.
        auto            y = Myclass::foo(); // VALID, no name = no access control.
        return 0;
    }
    ```

- Member functions of the enclosing type can use the name in the public area of the nested type without using qualifiers, but
    for the return value of the member functions it must be qualified.
    ```cpp
    class Myclass {
    public:
        class Nested {}; // class Nested

        Nested foo(Nested);
    }; // class Myclass

    Nested foo(Nested x) {  // Return type is invalid but parameter is VALID. Because return type of the function
                            // is not part of the class scpoe, therefore it must be qualified.
        Nested y;           // VALID, scope of the function is part of the class scope.
        return y;
    }

    Myclass::Nested foo(Nexted x) // VALID
    {
        Nested y;
        return y;
    }
    ```
    Another alternative would be using a trailing return type.
    ```cpp
    auto foo(Nested x) -> Nested { // VALID
        Nested y;
        return y;
    }
    ```
