// Lecture 19
#include <array>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << '\n';
    std::cout << "sizeof(char*) = " << sizeof(char*) << '\n';
    char        s[] = "tycakmak1";
    std::string str1{"tycakmak1"};
    std::string str2(20, '\0');
    std::cout << str2 << '\n';
    std::vector<int>   vec;
    std::array<int, 5> arr;

    while (!str1.empty()) {
        std::cout << str1 << '\n';
        str1.erase(str1.begin());
    }
    std::cout << str1.capacity() << '\n';
    auto cap = str1.capacity();
    for (;;) {
        str1.push_back('.');
        if (str1.capacity() > cap) {
            std::cout << static_cast<void*>(str1.data()) << '\n';
            std::cout << "size = " << str1.size() << " capacity = " << str1.capacity() << '\n';
            static_cast<void>(getchar());
            cap = str1.capacity();
            std::cout << static_cast<void*>(str1.data()) << '\n';
        }
    }
    return 0;
}
