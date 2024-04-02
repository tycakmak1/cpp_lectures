// Lecture 13
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

class Car {
public:
    Car() : _year{-1}, _doorNumber{-1} { std::cout << "Default Ctor Called\n"; }

    Car(int year, int door_number) : _year{year}, _doorNumber{door_number} {
        std::cout << "Ctor Called\n";
    }

    Car(Car const& rhs) : _year{rhs._year}, _doorNumber{rhs._doorNumber} {
        std::cout << "Copy constructor is called\n";
        print();
    }

    Car& operator=(Car const& rhs) {
        _year       = rhs._year;
        _doorNumber = rhs._doorNumber;
        std::cout << "Copy assignment is called\n";
        print();
        return *this;
    }

    Car(Car&& other) : _year{std::move(other._year)}, _doorNumber{std::move(other._doorNumber)} {}

    Car& operator=(Car&& other) {
        _year       = std::move(other._year);
        _doorNumber = std::move(other._doorNumber);
        std::cout << "move asssignment is called\n";
        return *this;
    }

    void print() { std::cout << "year = " << _year << " door number = " << _doorNumber << '\n'; }

private:
    int _year, _doorNumber;
}; // class Car

class String {
public:
    String() = default;

    String(char const* p) : _len{std::strlen(p)}, _p{static_cast<char*>(std::malloc(_len + 1))} {
        if (!_p)
            throw std::runtime_error{"cannot allocate memory"};
        std::strcpy(_p, p);
    }

    String(String const& other) : _len{other._len}, _p{static_cast<char*>(std::malloc(_len + 1))} {
        if (!_p)
            throw std::runtime_error{"cannot allocate memory"};
        std::strcpy(_p, other._p);
    }

    String& operator=(String const& other) {
        if (this == &other) // Removal of this control mechanism, creates a dangling
                            // handle problem caused by self assignment.
            return *this;   // There is an alternative to this, copy & swap idiom, a
                            // topic for later.
        std::free(_p);
        _len = other._len;
        _p   = static_cast<char*>(std::malloc(_len + 1));
        if (!_p)
            throw std::runtime_error{"cannot allocate memory"};
        strcpy(_p, other._p);
        return *this;
    }

    String(String&& other)
    : _len{std::move(other._len)}
    , _p{std::move(other._p)} // move ctor
    {
        other._len = 0;
        other._p   = nullptr;
    }

    String& operator=(String&& other) // move assignment
    {
        if (this == &other)
            return *this;
        free(_p);
        _len       = other._len;
        _p         = other._p;
        other._len = 0;
        other._p   = nullptr;
        return *this;
    }

    ~String() {
        if (_p)
            std::free(_p);
    }

    void print() const { std::cout << "[" << _p << "]\n"; }

    std::size_t length() const { return _len; }

private:
    std::size_t _len{};
    char* _p{};
}; // class String

class MyClass {
public:
    MyClass() : _x{}, _y{} { std::cout << "default ctor this = " << this << '\n'; }

    MyClass(int a, int b) : _x{a}, _y{b} {
        std::cout << "int ctor a = " << a << " b = " << b << " this = " << this << '\n';
    }

    MyClass(MyClass const& other) : _x{other._x}, _y{other._y} { std::cout << "Copy Ctor\n"; }

    MyClass(MyClass&& other) : _x{std::move(other._x)}, _y{std::move(other._y)} {
        std::cout << "Move Ctor\n";
    }

    ~MyClass() { std::cout << "destructor this = " << this << '\n'; }

    MyClass& operator=(MyClass const& other) {
        std::cout << "Copy Assignment\n";
        _x = other._x;
        _y = other._y;
        return *this;
    }

    MyClass& operator=(MyClass&& other) {
        std::cout << "Move Assignment\n";
        _x = std::move(other._x);
        _y = std::move(other._y);
        return *this;
    }

    void foo() & { std::cout << "Myclass foo() &       this = " << this << '\n'; }

    void foo() const& { std::cout << "Myclass foo() const&  this = " << this << '\n'; }

    void foo() && { std::cout << "Myclass foo() &&      this = " << this << '\n'; }

    void foo() const&& { std::cout << "Myclass foo() const&& this = " << this << '\n'; }

private:
    int _x, _y;
}; // class MyClass

int main() {
    /*std::cout << "Hello World!\n";

    Car car1{ 2021, 5 };
    Car car2{car1};
    Car car3;
    car3 = std::move(car2);
    cout << "car2 = ";
    car2.print();*/

    // std::cout << "main starts here\n";
    // Myclass&& x = Myclass{ 3,5 };
    // Yes this is valid and a pr value expression, this line creates a temporary object.
    // std::cout << "main continues\n";

    MyClass t1;
    MyClass t2{3, 4};
    t1 = t2;
    MyClass t3{std::move(t2)};
    t3         = {3, 4};
    MyClass t4 = MyClass{3, 4};
    // THIS HERE IS ABOUT REFERENCE QUALIFIERS
    // MyClass{3, 4}.foo();
    // MyClass x;
    // const MyClass cx;
    // x.foo();
    // cx.foo();
    // std::move(x).foo();
    // std::move(cx).foo();

    return 0;
}
