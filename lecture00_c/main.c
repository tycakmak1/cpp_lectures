// this is a testing ground for C
#include <stdio.h>

int g = 10;

void func(void* p) { return; }

int main()
{
    int* p = NULL;
    func(p);

    return 0;
}
