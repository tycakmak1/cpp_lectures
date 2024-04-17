// Lecture 03
#include <iostream>

struct Point {
    double _x, _y;
}; // struct Point

std::ostream& operator<<(std::ostream& out, Point const p) {
    return (
        (p._y == 0)
            ? (out << p._x << " +i" << p._y)
            : ((p._y < 0) ? (out << p._x << " -i" << -p._y) : (out << p._x << " +i" << p._y)));
}

Point times(Point p) { return {p._x * 2, p._y * 2}; }

int main() {
    int x{10};
    // if(int num{x}; ++num == 11)// same as if(int num{x}; num++, num == 11)
    // this is only available with C++17
    int num{x};
    if (++num == 11) {
        std::cout << "suck it num = " << num << "\n";
    }
    int y = x++;
    std::cout << "x " << x << " y " << y << "\n";

    unsigned int z = 15;
    std::cout << "z " << z << "\n";

    int  a[5] = {1, 2, 3};
    int* p_a  = a;
    auto t    = sizeof p_a++;
    std::cout << "x " << t << " *p_a " << *p_a << "\n";
    Point p1{3, 4};
    std::cout << p1 << "\n";
    int temp{}, *ptr_temp = &temp;
    if (p1 = {5, 12}, x != 10) {
        std::cout << x << "\n";
        std::cout << p1 << "\n";
    }
    return 0;
}
