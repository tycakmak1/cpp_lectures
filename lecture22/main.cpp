// Lecture 22
#include <iostream>

struct Car {
    virtual void start() { std::cout << "Car has started\n"; }

    virtual void run() { std::cout << "Car is running\n"; }

    virtual void stop() { std::cout << "Car has stopped\n"; }
};

struct Merc : public Car {
    void start() { std::cout << "Merc has started\n"; }

    void run() { std::cout << "Merc is running\n"; }

    void stop() { std::cout << "Merc has stopped\n"; }
};

void car(Car& cr) {
    cr.start();
    cr.run();
    cr.stop();
}

int main() {
    Car  c;
    Merc m;

    car(c);
    car(m);
}
