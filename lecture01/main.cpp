// Lecture 01
#include <iostream>
#include <string>

template<typename T>
struct ValCat {
    static constexpr char const* p = "PR value";
}; // struct ValCat

template<typename T>
struct ValCat<T&> {
    static constexpr char const* p = "L value";
}; // struct ValCal<T&>

template<typename T>
struct ValCat<T&&> {
    static constexpr char const* p = "X value";
}; // class ValCat<T&&>

#define print_val_cat(expr) \
    std::cout << "Value category of '" #expr "' is " << ValCat<decltype(expr)>::p << '\n';
int temp_g;

int& foo1() {
    // int temp{5};
    return temp_g;
}

int bar() { return 1; }

std::string name = "taha";

std::string get_int() { return ::name; }

int x;

int* foo2() { return nullptr; }

enum Colour { RED, GREEN, BLUE }; // enum Colour

enum Pos { ON, OFF, HOLD }; // enum Pos

int main() {
    int const xx = -5;
    {
        std::string temp = get_int();
        if (temp.size() < 5)
            std::cout << "inside\n";
    }
    if (int* p = foo2())
        std::cout << "inside2\n";

    enum Colour mycolour = RED;
    enum Pos    mypos    = OFF;
    int         xy       = mycolour;
    std::cout << xy;
    int  x{5};
    int* ptv_x{&x};
    std::cout << "ptr_x " << ptv_x << '\n' << "*ptr_x " << *ptv_x << '\n';
    int& ref_x{x};
    ref_x++;
    std::cout << "x " << x << '\n';
    std::cout << "ref_x " << ref_x << '\n';
    print_val_cat(*ptv_x);
    print_val_cat(ptv_x);
    print_val_cat(x);
    print_val_cat(++x);
    print_val_cat(foo1());
    print_val_cat(bar());
    int a1;      // default initialization, a1 has (indeterminate)garbage value
    int a2 = 10; // copy initialization
    int a3(5);   // direct initialization
    int a4{45};  // brace initialization, generally known as uniform or list initialization
    int a5{};    // value initialization
    std::cout << "a2 " << a2 << '\n' << "a3 " << a3 << '\n' << "a4 " << a4 << '\n';
    int arr_a[5]{};
    for (int i{0}; i < 5; ++i)
        std::cout << "a[" << i << "] = " << arr_a[i] << '\n';
    auto* temp = &x;
    std::cout << "temp " << temp << '\n' << "x " << x << '\n' << "*temp " << *temp << '\n';
    bool flag{}; // flag = false
    std::cout << std::boolalpha << flag << '\n';
    int* ptr3_x = (int*)flag; // implicit typecasting from bool to pointer
    if (ptr3_x == nullptr)
        std::cout << ptr3_x << '\n';
    return 0;
}
