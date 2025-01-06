# LECTURE 18
## Nested Types
##### ###REMARK###
> Member functions of a nested type can be defined inside of the class declaration, or can be
> declared in the class declaration and defined outside of the enclosing class. Notice the
> detail "enclosing class" in the previous sentence.
> ```cpp
> class Myclass {
>     class Nested {
>         void foo(); // VALID
>         void bar(); // VALID
>     }; // class Nested
>
>     void Nested::bar() { return; } // INVALID
>
> }; // class Myclass
>
> void Myclass::Nested::foo() { return; } // VALID
> ```

### Pimple Idiom
- Also called Handle Body Idiom, Cheshire Cat Idiom, Opaque Pointer Idiom.
- It aims to minimize the dependency between modules. It is achieved by hiding the private members of the class. Since size of
    pointers to all types of variables are the same binary compatibility is still intact.
    ```cpp
    #include "Date.h"
    
    class Myclass {
    private:
        std::string _str;
        Date        _date;
    }; // class Myclass
    
    // Myclass.h
    class Myclass {
        void foo();
    
    private:
        class Pimple;
        Pimple* _p;
    }; // class Myclass
    
    // Myclass.cpp
    #include "Date.h"class Myclass
    {
        void foo();
    private:
        class Pimple;
        Pimple* _p;
    }; // class Myclass
    
    // Myclass.cpp
    #include <string>
    #include "Myclass.h"
    #include "Date.h"
    class Myclass::Pimple
    {
    public:
        void foo()
        {
            _str = "Hello World!\n";
            _date = Date{22, 10, 2023};
        }
    private:
        std::string _str;
        Date _date;
    }; // class Myclass:Pimple
    
    void Myclass::foo()
    {
        _p->foo();
    }
    #include "Myclass.h"
    
    #include <string>
    
    class Myclass::Pimple {
        friend void Myclass::foo();
        std::string _str;
        Date        _date;
    }; // class Myclass::Pimple
    
    void Myclass::foo() {
        pimple->_str;  // Since _str and _date are private members of
        pimple->_date; // Myclass::Pimple this is how they can be accessed.
    }
    ```
    Alternatively same functions can be re-declared inside Pimple and can be used directly.
    ```cpp
    // Myclass.h
    class Myclass {
        void foo();
    
    private:
        class Pimple;
        Pimple* _p;
    }; // class Myclass
    
    // Myclass.cpp
    #include "Date.h"
    #include "Myclass.h"
    
    #include <string>
    
    class Myclass::Pimple {
    public:
        void foo() {
            _str  = "Hello World!\n";
            _date = Date{22, 10, 2023};
        }
    
    private:
        std::string _str;
        Date        _date;
    }; // class Myclass:Pimple
    
    void Myclass::foo() { _p->foo(); }
    ```
    This way there are less derefences.

- For Pimple Idiom to be used, constructor of the enclosing type must initialize the pointer and the destructor of enclosing type
    must also delete the pimple object.
    ```cpp
    // Myclass.h
    #include "Date.h"

    class Myclass {
        Myclass();
        ~Myclass();
        class Pimple;
        Pimple* _p;
    }; // class Myclass

    // Myclass.cpp
    #include "Myclass.h"

    class Myclass::Pimple {
    public:
        Pimple();

    private:
        std::string _str;
        Date        _date;
    }; // class Myclass::Pimpla

    Myclass::Myclass() : _p{new Pimple} {}

    Myclass::~Myclass() { delete _p; }

    Myclass::Pimple::Pimple() : _str{"Hello World!"}, _date{23, 10, 2023} {}
    ```

## Composition
A class having another class or classess as it's member or members. Broadly speaking, object composition models a "has-a"
relationship between two objects, e.g. a car "has-a" transmission.
##### ###REMARK###
> Public interface of the member class is not part of the enclosing class.
> ```cpp
> class Member {
> public:
>     void foo() {}
>
>     void bar() {}
> }; // class Member
>
> class Owner {
> private:
>     Member _x;
> }; // class Owner
>
> int main() {
>     Owner a;
>     // a.foo();        // syntax error
>     // a.bar();        // syntax error
> }
> ```
> BUT
> member functions of owner class can use it's members to acces their own public interfaces.
> ```cpp
> class Member {
>     int  _ival;
>     void baz();
>
> public:
>     void foo() {}
>
>     void bar() {}
> }; // class Member
>
> class Owner {
> public:
>     void func() {
>         _x.foo(); // VALID
>         _x.bar(); // VALID
>         _x._ival; // INVALID
>         _x.baz(); // INVALID
>     }
>
> private:
>     Member _x;
> }; // class Owner
>
> int main() {
>     Owner a;
>     // a.foo();         // still a syntax error
>     // a.bar();         // still a syntax error
> }
> ```
> ##### ###REMARK###
> > - Members of a class instance is created before the constructors block.
> > - If the default constructor of a class is defaulted(defined by the compiler) then the data members will be default initialized.
> > - If the copy constructor of a class does not initialize all members, compiler will call the default constructor for the missing
> >     members, which is dangerous.
> >     ```cpp
> >     class Member {
> >     public:
> >         Member() { std::cout << "Member default constructor\n"; }
> >         Member(Member const&) { std::cout << "Member copy constructor\n"; }
> >     }; // class Member
> >     
> >     class A {
> >     public:
> >         A() = default;
> >     
> >         A(A const&) {}
> >     
> >     private:
> >         Member _x;
> >     }; // class A
> >     
> >     class B {
> >         Member _x;
> >     }; // class B
> >     
> >     int main() {
> >         A a1;
> >         A a2{a1}; // Since _x is not properly initialized in copy
> >                   // constructor, compiler will call the default constructor for it.
> >         B b1;
> >         B b2{b1}; // Here default constructor will not be called.
> >     }
> >     ```
> >     Will have the following output because of copy constructor.<br>
> >         Member default constructor<br>
> >         Member default constructor<br>
> >         Member default constructor<br>
> >         Member copy constructor
