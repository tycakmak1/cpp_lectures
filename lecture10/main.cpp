// Lecture 10
#include "cakmak.h"
#include "taha.h"
#include "yasin.h"

#include <iostream>

class Myclass {
public:
    int m_data{};

    void f1() {
        std::cout << "Hello World!\n";
        return;
    }
}; // class Myclass

class Car {
public:
    Car() {
        _make  = "No information given";
        _model = "No information given";
        _year  = -1;
    }

    Car(char const* make, char const* model, int year) {
        _make  = make;
        _model = model;
        _year  = year;
    }

    void set_info(char const* make, char const* model, int year) {
        _make  = make;
        _model = model;
        _year  = year;
    }

    void get_info() const {
        std::cout << "Make  : " << _make << "\nModel : " << _model << "\nYear  : " << _year << '\n';
    }

    void f1() { std::cout << _year + 13 << '\n'; }

private:
    char const* _make;
    char const* _model;
    int         _year;
}; // class Car

class Ptr {
public:
    Ptr* f1() {
        std::cout << "f1, this = " << this << '\n';
        return this;
    }

    Ptr* f2() {
        std::cout << "f2, this = " << this << '\n';
        return this;
    }

    Ptr* f3() {
        std::cout << "f3, this = " << this << '\n';
        return this;
    }
}; // class Ptr

void f1(int x = 5) { std::cout << x * x << '\n'; }

void fconst(int const* p) {
    std::cout << "const int*\n";
    return;
}

void fconst(int* p) {
    std::cout << "int*\n";
    return;
}

constexpr int foo(int a, int b) { return a * a + b * b; }

int main() {
    int temp = 5;
    fconst(&temp);
    int const* ptv_temp = &temp;
    int        temp2    = 6;

    Ptr  temp_ptr;
    Ptr* ptv_temp_tr = &temp_ptr;
    (&temp_ptr)->f1()->f2()->f3();
    ptv_temp_tr->f1()->f2()->f3();
    Ptr* (Ptr::*ptf_ptr_f1)() = &Ptr::f1;
    Ptr* (Ptr::*ptf_ptr_f2)() = &Ptr::f2;
    Ptr* (Ptr::*ptf_ptr_f3)() = &Ptr::f3;
    std::cout << "ptf_ptr_f1 = " << ptf_ptr_f1 << '\n';
    std::cout << "ptf_ptr_f2 = " << ptf_ptr_f2 << '\n';
    std::cout << "ptf_ptr_f3 = " << ptf_ptr_f3 << '\n';
    (((temp_ptr.*ptf_ptr_f1)()->*ptf_ptr_f2)()->*ptf_ptr_f3)();

    void (Car::*ptf_get_info)() const = &Car::get_info;
    Car temp_car1("Aubi", "A3 Sportback", 2021);
    (temp_car1.*ptf_get_info)();
    temp_car1.f1();
    Car temp_car3;
    (temp_car3.*ptf_get_info)();
    int  xx     = 5;
    int* ptv_xx = &xx;
    std::cout << &*ptv_xx << '\n';

    constexpr int x = foo(1, 2);
    int const     arr[x]{0, 1, 2, 3, 4};
    int const     yy     = 5;
    int const*    ptv_yy = &yy;

    std::cout << "*ptv_yy = " << *ptv_yy << "\nptv_yy = " << ptv_yy << '\n';

    void (*ptf_f1)(int)        = f1;
    void (Myclass::*ptf_f11)() = &Myclass::f1;
    Myclass a{};
    a.m_data = 5;
    (a.*ptf_f11)();
    Myclass* ptv_a = &a;

    ((&a)->*ptf_f11)();
    (ptv_a->*ptf_f11)();
    std::cout << "\n\n";
    std::cout << "&func = " << &func << '\n';
    f2();
    f3();
    return 0;
}
