#include <cstdint>
#include <iostream>

struct Node;
using nodeptr_t = Node*;

nodeptr_t ptrDiff(nodeptr_t ptr1, nodeptr_t ptr2) {
    return reinterpret_cast<nodeptr_t>(
        reinterpret_cast<uint64_t>(ptr1) ^ reinterpret_cast<uint64_t>(ptr2));
}

struct Node {
    uint16_t  _data{};
    nodeptr_t _ptrdiff{ptrDiff(nullptr, nullptr)};

    void addNode(uint16_t data) {
        if (_ptrdiff == nullptr) {
            nodeptr_t next = ptrDiff(this, nullptr);
            _ptrdiff       = ptrDiff(nullptr, next);
            next->_data    = data;
        }
        // else if()
    }

    void printNode(uint8_t const& nodeIndex) {
        nodeptr_t iter{this};
        for (uint8_t idx{}; idx < nodeIndex && iter != nullptr;
             idx++ && (iter = ptrDiff(nullptr, _ptrdiff))) {}
        std::cout << iter->_data << '\n';
    }
};

int main() {
    nodeptr_t head = new Node{0U};
    head->addNode(1U);
    head->printNode(0);

    // std::cout << (ptrDiff(nullptr, nullptr) == nullptr) << '\n';
}
