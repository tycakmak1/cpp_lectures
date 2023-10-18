// Lecture 05
#include <iostream>

int y      = 5;
int* pptr  = &y;
using lref = int&;
using rref = int&&;

int main()
{
    char const name[5] = "jack";
    int num            = 5;

    lref lnum1   = num;
    lref& lnum2  = num;
    lref&& lnum3 = num;
    rref rnum1   = 5;

    rref& lnum4  = num;
    rref&& rnum2 = 6;
    char c       = 0b1100;

    int ac = +c;
    std::cout << "ac " << ac << "\n"
              << "c " << (int)c << "\n";
    int const dizi[5]{};
    auto& rdizi = dizi;
    int val{};
    auto aval = val;
    std::cout << "&val  " << &val << "\n"
              << "&aval " << &aval << "\n";
    std::cout << val << "\n";
    int ival = 35;
    int* p1  = &ival;
    int*& rp = p1;
    *rp      = 36;
    std::cout << ival << "\n";
    int x = 10;
    rp    = &x;
    std::cout << ival << "\n";
    std::cout << *p1 << "\n";
    std::cout << "(x) " << (x) << "\n"
              << "x " << x << "\n";

    int arr1[4]{1, 2, 3, 4};
    int(&r_arr1)[4] = arr1;
    int& ra1        = arr1[0];
    int* pa1        = arr1;
    int(*pa2)[4]    = &arr1;

    int& r_x1     = x;
    int const* cp = &x;
    int* r_x2     = &r_x1;
    int& rx       = x;
    int* ptr_rx   = &rx;
    int* ptr_x    = &x;
    auto r2x      = *ptr_rx;
    auto* r3x     = &x;
    auto*& r4x    = ptr_rx; // lref lnum1 = num;
    if (pptr == nullptr)
        std::cout << "true dat1"
                  << "\n";
    pptr = &x;
    if (pptr == nullptr)
        std::cout << "true dat2"
                  << "\n";

    std::cout << "*pptr " << *pptr << "\n"
              << "*::pptr " << *::pptr << "\n";

    int a[5][10];
    int(*p11)[10] = &a[1];
    int(&ra)[10]  = a[1];

    int b[5][10][20];
    int(&p2)[20] = b[1][2];

    int ival1          = 10;
    double const& dref = ival1;
    ++ival1;
    std::cout << "dref " << dref << "\n"
              << "ival1 " << ival1 << "\n";

    std::cout << "x " << x << "\n"
              << "rx " << rx << "\n"
              << "ptr_x " << ptr_x << "\n"
              << "ptr_rx " << ptr_rx << "\n"
              << "*ptr_x " << *ptr_x << "\n"
              << "*ptr_rx " << *ptr_rx << "\n";
    return 0;
}