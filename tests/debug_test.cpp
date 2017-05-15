/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#include "debug.hpp"

/*
 * A basic example of the DEBUG macro. The output of this program will be:
 * Segmentation fault.
 *   Location: tests/debug_test.cpp:15
 *   Function: main
 */

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
    ECHO("Hello, world!");
}
