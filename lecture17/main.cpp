// Lecture 17
#include <iostream>

namespace ns {
int y = 10;
} // namespace ns

namespace yas {
int y = 11;
} // namespace yas

namespace ns {
void func(int) { std::cout << "ns::func(int)\n"; }
} // namespace ns

namespace yas {
void func(int, int) { std::cout << "yas::func(int, int)\n"; }
} // namespace yas

namespace ns1 {
inline namespace ns2 {
int x = 7;
} // namespace ns2
} // namespace ns1

void func() { std::cout << "global func()\n"; }

int main() {
    int t1 = ns1::ns2::x;
    int t2 = ns1::x;
    using ::func;
    using ns::func;
    using yas::func;
    ::func();
    func();
    func(12);
    func(12, 13);

    return 0;
}
