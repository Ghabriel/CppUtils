/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#include "debug.hpp"

int main(int, char**) {
    int i = 1;
    DEBUG_EXEC(
        i = 2;
        ECHO("Debug is enabled.");
    );
    std::cout << "i = " << i << std::endl;
}
