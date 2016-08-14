#include <iostream>
#include "macros.hpp"

int main(int, char**) {
    DEBUG int a = 1;
    DEBUG int* b = nullptr;
    DEBUG int c = 1;
    DEBUG delete b;
    DEBUG int d = 2;
    DEBUG int e = *b;
    DEBUG int f = 2;
    DEBUG int g = 5;
    DEBUG int h = 42;

    TRACE(a);
    TRACE(b);
    TRACE(c);
    TRACE(d);
    TRACE(e);
    TRACE(f);
    TRACE(g);
    TRACE(h);
}
