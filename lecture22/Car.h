#ifndef GUARD_ED45D3BD_EA8B_4BE2_912B_AF36A9C23A2F
#define GUARD_ED45D3BD_EA8B_4BE2_912B_AF36A9C23A2F

#include <iosfwd>

namespace car {

class Car {
public:
    virtual void         start() = 0;
    virtual void         run()   = 0;
    virtual void         stop()  = 0;
    virtual void         lock()  = 0;
    virtual Car*         clone() = 0;
    friend std::ostream& operator<<(std::ostream& os, Car const& c);
    friend std::ostream& operator<<(std::ostream& os, Car const* cPtr);

private:
    virtual void print(std::ostream& os) const = 0;
}; // class Car

class Merdedes : public Car {
public:
    void      start() override;
    void      run() override;
    void      lock() override;
    void      stop() override;
    Merdedes* clone() override;
    void      print(std::ostream& os) const override;
}; // class Merdedes

class MerdedesA180 : public Merdedes {
public:
    void          start() override;
    void          run() override;
    void          lock() override;
    void          stop() override;
    MerdedesA180* clone() override;
    void          print(std::ostream& os) const override;
}; // class MerdedesA180

class Aubi : public Car {
public:
    void  start() override;
    void  run() override;
    void  lock() override;
    void  stop() override;
    Aubi* clone() override;
    void  print(std::ostream& os) const override;
}; // class Aubi

} // namespace car
#endif // GUARD_ED45D3BD_EA8B_4BE2_912B_AF36A9C23A2F
