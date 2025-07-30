#include "Car.h"

#include <iostream>

namespace car {

void Car::start() { std::cout << "Car::start()\n"; }

void Car::run() { std::cout << "Car::run()\n"; }

void Car::stop() { std::cout << "Car::stop()\n"; }

void Car::lock() { std::cout << "Car::lock()\n"; }

void Car::foo() { Car::stop(); }

void Mercedes::start() { std::cout << "Mercedes::start()\n"; }

void Mercedes::run() { std::cout << "Mercedes::run()\n"; }

void Mercedes::stop() { std::cout << "Mercedes::stop()\n"; }

void Mercedes::lock() { std::cout << "Mercedes::lock()\n"; }

void MercedesA180::run() { std::cout << "MercedesA180::run()\n"; }

void MercedesA180::lock() { std::cout << "MercedesA180::lock()\n"; }

void Audi::start() { std::cout << "Audi::start()\n"; }

void Audi::run() { std::cout << "Audi::run()\n"; }

void Audi::lock() { std::cout << "Audi::lock()\n"; }

void Audi::stop() { std::cout << "Audi::stop()\n"; }

} // namespace car
