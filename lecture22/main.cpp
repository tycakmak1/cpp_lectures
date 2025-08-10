// Lecture 22
#include "Car.h"

#include <cstdint>
#include <iostream>

void car_program(car::Car* const ptr) {
    std::cout << "car_program_ptr\n";
    ptr->start();
    ptr->run();
    ptr->stop();
    ptr->lock();
    std::cout << *ptr;
    std::cout << '\n';
}

void car_program(car::Car& ref) {
    std::cout << "car_program_ref\n";
    ref.start();
    ref.run();
    ref.stop();
    ref.lock();
    std::cout << ref;
    std::cout << '\n';
}

int main() {
    car::Merdedes     m;
    car::Aubi         a;
    car::MerdedesA180 mA180;

    car_program(&m);     // will call the derived functions of the respective classes
    car_program(&a);     // will call the derived functions of the respective classes
    car_program(&mA180); // will call the derived functions of the respective classes

    car_program(m);     // will call the derived functions of the respective classes
    car_program(a);     // will call the derived functions of the respective classes
    car_program(mA180); // will call the derived functions of the respective classes
}
