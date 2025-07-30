// Lecture 22
#include "Car.h"

#include <iostream>

void car_program_ptr(car::Car* const ptr) {
    std::cout << "car_program_ptr\n";
    ptr->start();
    ptr->run();
    ptr->stop();
    ptr->lock();
    ptr->foo();
    std::cout << '\n';
}

void car_program_ref(car::Car& ref) {
    std::cout << "car_program_ref\n";
    ref.start();
    ref.run();
    ref.stop();
    ref.lock();
    ref.foo();
    std::cout << '\n';
}

void car_program(car::Car car) {
    std::cout << "car_program\n";
    car.start();
    car.run();
    car.stop();
    car.lock();
    car.foo();
    std::cout << '\n';
}

int main() {
    car::Mercedes     m;
    car::Audi         a;
    car::MercedesA180 mA180;

    car_program_ptr(&m);     // will call the derived functions of the respective classes
    car_program_ptr(&a);     // will call the derived functions of the respective classes
    car_program_ptr(&mA180); // will call the derived functions of the respective classes

    car_program_ref(m);     // will call the derived functions of the respective classes
    car_program_ref(a);     // will call the derived functions of the respective classes
    car_program_ref(mA180); // will call the derived functions of the respective classes

    car_program(m);
    car_program(a);
    car_program(mA180);
}
