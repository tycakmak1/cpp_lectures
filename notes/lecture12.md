# LECTURE 12

### Special Member Functions
Default constructor that has been defaulted by the compiler is the;
- Non-Static
- Public
- Inline<br>
function of the class.

##### ###REMARK###
> If defaulting of a special member function by a compiler breaks a rule of the language, then instead of a syntax error,<br>
> compiler deletes that function.
> 
> Why would there be a syntax error?
>     - A member is unable to default initialize.
>     - Calling of a non-existing function.
>     - Calling of a private function.
>     - Calling of a deleted function.
> ```cpp
> class Myclass {
> public:
> private:
>     const int _x;
> }; // class Myclass
> ```
> Here default constructor is `deleted`, because `int const` cannot be default initialized.<br>
> Note that, this `class` definition is not a syntax error but, creating an instance of Myclass with default initialization would
> cause a syntax error, because Myclass does not have a default constructor.
> ```cpp
> class Foo {
>     Foo();
> }; // class Foo
>
> class Myclass {
>     Foo _x;
> }; // class Myclass
>
> int main() {
>     Myclass m1;
>     return 0;
> }
> ```
> Here default constructor of Foo is private, so default initializing of a Foo instance would cause a syntax error.

#### Copy constructor
When a class instance is initiated with the value of another instance of the same class, copy constructor is called.
```cpp
Student mike;               // Calls default constructor.
Student jake{mike};         // Calls copy constructor.
Student steve(mike);        // Calls copy constructor.
Student daniel = mike;      // Calls copy constructor.
```

Default copy constructor that defaulted by the compiler is the
- Non-Static
- Public
- Inline<br>
function of the class.

##### ###REMARK###
> If the special member function that's been defined by the compiler is working for you, let the compiler define it. This is called
> rule of zero.
> ##### So when should we write the copy constructor?
> When the class has a pointer/reference variable in it. Because copy constructor copies the
> values of the members, so copying the value of a pointer/reference results with that
> pointer/reference member having the same value with the original instance. So they point
> to the same thing, and when changing values in that location, they both get changed.
> This type of copying called shallow/memberwise copy. Instead of this we do deep copy,
> which is creating a new instance and copying the values from the original instance.
> ```cpp
> class String {
> public:
>     String() = default;
>
>     String(char const* p) : _len{std::strlen(p)}, _p{static_cast<char*>(std::malloc(_len + 1))} {
>         if (!_p) {
>             throw std::runtime_error{"cannot allocate memory"};
>         }
>         std::strcpy(_p, p);
>     }
>
>     String(String const& other) : _len{other._len}, _p{static_cast<char*>(std::malloc(_len + 1))} {
>         if (!_p) {
>             throw std::runtime_error{"cannot allocate memory"};
>         }
>         std::strcpy(_p, other._p);
>     }
>
>     String& operator=(String const& other) {
>         if (this == &other) { // Removal of this control mechanism, creates a dangling handle problem caused by
>                               // self assignment. There is an alternative to this, 
>             return *this;     // Copy & Swap Idiom, a topic for later.
>         }
>         std::free(_p);
>         _len = other._len;
>         _p   = static_cast<char*>(std::malloc(_len + 1));
>         if (!_p) {
>             throw std::runtime_error{"cannot allocate memory"};
>         }
>         std::strcpy(_p, other._p);
>         return *this;
>     }
>
>     ~String() { std::free(_p); }
>
>     void print() const { std::cout << "[" << _p << "]\n"; }
>
>     std::size_t length() const { return _len; }
>
> private:
>     std::size_t _len{};
>     char*       _p{};
> }; // class String
>
> void func(String s) {
>     std::cout << "func called\n";
>     s.print();
> }
>
> int main() {
>     String str{"hello world!"};
>     str.print();
>     auto len = str.length();
>     std::cout << "len = " << len << '\n';
>     func(str);
>     std::cout << "back to main\n";
>     str.print();
>     std::cout << str.length();
> }
> ```
> So, deep copy is necessary when a class contains a handle (pointer or reference).<br>
> There are classes that have pointers in them but, for those classes deep copy constructor is not necessary to be defined
> explicitly, because those classes already have built-in deep copy constructortor.

Three possible statuses for copy constructor;
1. Compiler Defined(Rule of Zero)
2. Explicitly Defined
3. Deleted (This is done to prevent copying)

When defining an explicit destructor, instead of letting the compiler define a copy constructor, there should also be an explicit copy
constructor.

In old C++, these three functions were related to each other,
- Destructor
- Copy constructor
- Copy Assignment<br>
That's why these three were usually called Big 3. In modern C++, with the addition of move members, they are referred to as
Big 5. The reason it is called as is, if you define one of them then you should also define the others.

#### Copy Assignment
Unlike copy constructor, in copy assignment, there are no instances being created. It works on already existing instances. It must
be named as `operator=`.
```cpp
class Myclass
{
public:
    Myclass() = default;                        // Default Constructor
    Myclass operator=(Myclass const& other) {   // Copy    Assignment
        _x = other._x;
        _y = other._y;
        return *this;
    }
private:
    int _x, _y;
}; // class Myclass

Myclass x{};
Myclass y{};

y = x;                                          // Copy Assignment
```

If copy assignment operator is implicitly defined by the compiler, then it is
- Non-Static
- Public
- Inline<br>
function of the class.

##### ###REMARK###
> Self Assignment
> ```cpp
> int main() {
>     int x = 10;
>     x = x;    // Self Assignment
>     return 0;
> }
> // To prevent this, assignment can be checked for sel assigning.
> T operator=(T const& other) {
>     if(this == &other) {  // Self Assignment control
>         return *this;
>     }
>     //.. Copy operations
>     return *this;
> }
> ```

#### Move Members
```cpp
class Myclass
{
public:
    Myclass();                              // Default constructor
    ~Myclass();                             // Destructor

    Myclass(Myclass const&);                // Copy constructor
    Myclass(Myclass&&);                     // Move constructor

    Myclass& operator=(Myclass const&);     // Copy Assignment
    Myclass& operator=(Myclass&&);          // Move Assignment
}; // class Myclass
```
