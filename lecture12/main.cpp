// Lecture 12
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

class MyClass
{
public:
    MyClass()
    {
        _x = 0;
        _y = 4;
    }

    void print() const { std::cout << "x = " << _x << " y = " << _y << " this = " << this << '\n'; }

    void set(int x, int y)
    {
        _x = x;
        _y = y;
        return;
    }

private:
    int _x{}, _y{};
}; // class MyClass1

class String
{
public:
    String() = default;

    String(char const* p) : _len{ std::strlen(p) }, _p{ static_cast<char*>(std::malloc(_len + 1)) }
    {
        if (!_p)
        {
            throw std::runtime_error{ "cannot allocate memory" };
        }
        std::strcpy(_p, p);
    }

    String(String const& other)
    : _len{ other._len }, _p{ static_cast<char*>(std::malloc(_len + 1)) }
    {
        if (!_p)
        {
            throw std::runtime_error{ "cannot allocate memory" };
        }
        std::strcpy(_p, other._p);
    }

    String& operator=(String const& other)
    {
        if (this == &other) // Removal of this control mechanism, creates a dangling handle problem
                            // caused by self assignment. There is an alternative to this, copy &
                            // swap idiom, a topic for later.
        {
            return *this;
        }
        std::free(_p);
        _len = other._len;
        _p   = static_cast<char*>(std::malloc(_len + 1));
        if (!_p)
        {
            throw std::runtime_error{ "cannot allocate memory" };
        }
        std::strcpy(_p, other._p);
        return *this;
    }

    ~String() { std::free(_p); }

    void print() const { std::cout << "[" << _p << "]\n"; }

    std::size_t length() const { return _len; }

private:
    std::size_t _len{};
    char* _p{};
}; // class String

void func(String s)
{
    std::cout << "func called\n";
    s.print();
}

int main()
{
    MyClass m;
    m.print();
    MyClass& rtv_m = m;
    rtv_m.set(7, 24);
    rtv_m.print();
    m.print();
    std::cout << "\n\n";

    String str{ "hello world!" };
    str.print();
    auto len = str.length();
    std::cout << "len = " << len << '\n';
    func(str);
    std::cout << "back to main\n";
    str.print();
    std::cout << str.length();
    std::cout << "\n\n";

    String s{ "goodbye world!" };
    s.print();
    s   = str;
    s   = s;
    str = str;
    s.print();
    str.print();

    return 0;
}
