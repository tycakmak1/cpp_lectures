// Lecture 20
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string           str{"hello world"};
    std::string::iterator iter = str.begin();
    std::cout << *iter << '\n';
    std::cout << *++iter << '\n';
    std::vector<uint8_t> vec{0U, 1U, 2U, 3U, 4U};
    vec.erase(vec.begin());
    for (auto i : vec) {
        std::cout << static_cast<uint16_t>(i) << ' ';
    }
    std::cout << "\b\nvec.cap  " << vec.capacity() << '\n';
    std::cout << "vec.size " << vec.size() << '\n';
    for (auto i : vec) {
        std::cout << i << ' ';
    }
    std::cout << "\b\n";

    str.erase(str.begin());
    str.erase(str.end() - 1U);
    std::cout << str << '\n';
    str = "hello world";
    str.erase(1U);
    std::cout << '|' << str << "|\n";
    std::getline(std::cin, str, ',');
    std::cout << '|' << str << "|\n";
    return 0;
}
