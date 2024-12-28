// Lecture 16
#include <array>
#include <iostream>
#include <string>

class Counter {
public:
    explicit Counter(int x = 0) : _val{x} {
        std::cout << "a Counter object created   at " << this << " with value " << _val << '\n';
    }

    ~Counter() {
        std::cout << "a Counter object destroyed at " << this << " with value " << _val << '\n';
    }

    Counter& operator++() {
        ++_val;
        return *this;
    }

    Counter operator++(int) {
        Counter retval = *this;
        ++*this;
        return retval;
    }

    int get() const { return _val; }

    friend std::ostream& operator<<(std::ostream& os, Counter const& c) { return os << c._val; }

    void set(int x) { _val = x; }

private:
    int _val;
}; // class Counter

class CounterPtr {
public:
    CounterPtr() : _ptr{nullptr} {}

    CounterPtr(Counter* p) : _ptr{p} {}

    ~CounterPtr() {
        if (_ptr)
            delete _ptr;
    }

    CounterPtr(CounterPtr const&)            = delete;
    CounterPtr& operator=(CounterPtr const&) = delete;

    CounterPtr(CounterPtr&& other) : _ptr{other._ptr} { other._ptr = nullptr; }

    Counter& operator*() { return *_ptr; }

    Counter* operator->() { return _ptr; }

private:
    Counter* _ptr;
}; // class CounterPtr

template<typename T>
class SmartPtr {
public:
    SmartPtr() : _ptr{nullptr} {}

    SmartPtr(T* p) : _ptr{p} {}

    ~SmartPtr() {
        if (_ptr)
            delete _ptr;
    }

    SmartPtr(SmartPtr const&)            = delete;
    SmartPtr& operator=(SmartPtr const&) = delete;

    SmartPtr(SmartPtr&& other) : _ptr{other._ptr} { other._ptr = nullptr; }

    T& operator*() { return *_ptr; }

    T* operator->() { return _ptr; }

private:
    T* _ptr;
}; // class SmartPtr

class Yasin {
public:
    Yasin(double data) : _x{data} {}

    operator double() const { return _x; }

    Yasin(Yasin const& other) : _x{other._x} { std::cout << "copy ctor called\n"; }

    friend std::ostream& operator<<(std::ostream& os, Yasin const& temp) { return os << temp._x; }

private:
    double _x;
}; // class Yasin

namespace yas {
enum class Colour { BLUE, BLACK, GREEN }; // enum class Colour
} // namespace yas

std::ostream& operator<<(std::ostream& os, yas::Colour const& col) {
    static constexpr char const* p[] = {"Blue", "Black", "Green"};
    return os << p[static_cast<int>(col)];
}

int main() {
    enum yas::Colour col = yas::Colour::BLUE;
    // using enum yas::Colour; // This is avaliable with C++20
    std::cout << col << '\n';
    std::cout << "main started\nfirst block\n";
    {
        CounterPtr p1 = new Counter{35};
        ++*p1;
        std::cout << p1->get() << '\n';
        p1->operator++();
    }
    std::cout << "\n\nsecond block\n\n";
    {
        SmartPtr<Counter> p2 = new Counter{38};
        ++*p2;
        std::cout << p2->get() << '\n';
        p2->operator++();
    }
    std::cout << "\n\nthird block\n\n";
    {
        SmartPtr<std::string> p3 = new std::string{"taha yasin"};
        std::cout << *p3 << '\n';
        *p3 = "yasin taha";
        std::cout << *p3 << '\n' << p3->size() << '\n';
    }
    std::cout << "\n\n";
    Yasin  temp{5.3};
    int    x = 5 + static_cast<double>(temp);
    double y = x + static_cast<double>(temp);
    std::cout << x << '\n';
    std::cout << y << '\n';
    std::array<Yasin, 3> a{3.5, 5.2, 7.3};
    for (int i = 0; i < a.size(); i++)
        std::cout << "a[" << i << "] = " << a[i] << '\n';
    for (Yasin const& i : a)
        std::cout << i << '\n';
    std::cout << "main ends here\n";
    return 0;
}
