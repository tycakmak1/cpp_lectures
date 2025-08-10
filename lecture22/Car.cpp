#include "Car.h"

#include <iostream>

namespace car {

std::ostream& operator<<(std::ostream& os, Car const& c) {
    c.print(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, Car const* cPtr) {
    cPtr->print(os);
    return os;
}

void Merdedes::start() { std::cout << "Merdedes::start()\n"; }

void Merdedes::run() { std::cout << "Merdedes::run()\n"; }

void Merdedes::stop() { std::cout << "Merdedes::stop()\n"; }

void Merdedes::lock() { std::cout << "Merdedes::lock()\n"; }

void Merdedes::print(std::ostream& os) const { os << "This is a Merdedes\n"; }

Merdedes* Merdedes::clone() { return new Merdedes(*this); }

void MerdedesA180::start() { std::cout << "MerdedesA180::start()\n"; }

void MerdedesA180::run() { std::cout << "MerdedesA180::run()\n"; }

void MerdedesA180::stop() { std::cout << "MerdedesA180::stop()\n"; }

void MerdedesA180::lock() { std::cout << "MerdedesA180::lock()\n"; }

MerdedesA180* MerdedesA180::clone() { return new MerdedesA180(*this); }

void MerdedesA180::print(std::ostream& os) const { os << "This is a MerdedesA180\n"; }

void Aubi::start() { std::cout << "Aubi::start()\n"; }

void Aubi::run() { std::cout << "Aubi::run()\n"; }

void Aubi::lock() { std::cout << "Aubi::lock()\n"; }

void Aubi::stop() { std::cout << "Aubi::stop()\n"; }

Aubi* Aubi::clone() { return new Aubi(*this); }

void Aubi::print(std::ostream& os) const { os << "This is a Aubi\n"; }

} // namespace car
