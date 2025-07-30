#ifndef GUARD_ED45D3BD_EA8B_4BE2_912B_AF36A9C23A2F
#define GUARD_ED45D3BD_EA8B_4BE2_912B_AF36A9C23A2F

#include <iosfwd>

namespace car {

class Car {
public:
    virtual void start();
    virtual void run();
    virtual void stop();
    virtual void lock();
    void         foo();
}; // class Car

class Mercedes : public Car {
public:
    void start() override;
    void run() override;
    void lock() override;
    void stop() override;
}; // class Mercedes

class MercedesA180 : public Mercedes {
public:
    void run() override;

private:
    void lock() override;
}; // class MercedesA180

class Audi : public Car {
public:
    void start() override;
    void run() override;
    void lock() override;
    void stop() override;
}; // class Audi

} // namespace car
#endif // GUARD_ED45D3BD_EA8B_4BE2_912B_AF36A9C23A2F
