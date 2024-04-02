// Lecture 14
#include <iostream>
#include <vector>

class MyClass {
public:
    friend int get_mx();

    friend int get_mx(MyClass mc) { return mc._x; }

    void print() const& {
        std::cout << "mx = " << _x << " my = " << _y << " _x = " << _sta_x << " this = " << this
                  << '\n';
    }

    MyClass(int x, int y) : _x{x}, _y{y} {}

    // inline static int x = 5; // ==> this is available with C++17
    static int _sta_x;

    static int foo() { return 777; }

private:
    int _x, _y;
}; // class MyClass

int MyClass::_sta_x{};

int get_mx() {
    MyClass x{3, 5};
    return x._x;
}

int foo() { return 5; }

// example for Named Ctor Idiom
class Complex {
    Complex(double x, double y) { std::cout << "Complex cartesian\n"; }

    Complex(double angle, double distance, int) { std::cout << "Complex polar\n"; }

public:
    static Complex create_cartesian(double x, double y) { return Complex(x, y); }

    static Complex create_polar(double angle, double distance) {
        return Complex(angle, distance, 0);
    }
}; // class Complex

class A;

class B {
    friend class A;
}; // class B

int main() {
    MyClass m1{10, 20};
    m1._sta_x;
    MyClass m2{11, 21};
    m1._sta_x = ::foo();
    m1.print();
    m1.print();
    // Myclass::x = 7;
    m1.print();
    m2.print();
    std::cout << "_x changed to 19\n";
    // Myclass::x = 19;
    m1.print();
    m2.print();
    int temp = -123;
    std::cout << temp % 10 << '\n';

    Complex c1 = Complex::create_cartesian(3.5, 5.3);
    Complex c2 = Complex::create_polar(3.5, 5.3);

    return 0;
}
