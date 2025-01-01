#ifndef GUARD_BAC70BAE_9FD9_4D5F_BAC1_7803114BAEFB
#define GUARD_BAC70BAE_9FD9_4D5F_BAC1_7803114BAEFB

class Myclass {
public:
    Myclass();
    void foo();
    void foo(int);
    void print() const;

private:
    // std::string _str;
    // Date _date;
    class Pimple;
    Pimple* _p;
}; // class Myclass

#endif // GUARD_BAC70BAE_9FD9_4D5F_BAC1_7803114BAEFB
