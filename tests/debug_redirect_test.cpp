/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#include <fstream>
#include <vector>
#include "debug.hpp"

int main(int, char**) {
    auto stream = std::ofstream("dump.txt");
    DEBUG_REDIRECT(stream);

    char k = 'A';
    TRACE_L("label", k);
    ECHO("Test message");
}
