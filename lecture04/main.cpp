// Lecture 04
#include <iostream>

int main()
{
    int x   = 5;
    int *ip = &x, *&r = ip;
    std::cout << "ip " << ip << " *ip " << *ip << "\n"
              << "r  " << r << " *r  " << *r << "\n";
    ip = nullptr;
    std::cout << ip << '\n';
    int const buf{ 5 };
    int const& ref_buf = buf;
    int const* ptr_buf = &buf;
}