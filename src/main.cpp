#include <iostream>
#include <tuple>
// #include "bimap.hpp"
#include "macros.hpp"

int main(int, char**) {
    // utils::bimap<std::size_t, std::string> bimap;
    // bimap[0] = "first";
    // bimap[1] = "second";
    // // bimap["third"] = 2;

    // bimap.debug();
    // ECHO("####################################");
    // ECHO("####################################");

    // // TRACE(bimap[0]);
    // // TRACE(bimap[1]);
    // // TRACE(bimap[2]);

    // // TRACE(bimap["first"]);
    // TRACE(bimap["second"]);
    // // TRACE(bimap["third"]);

    std::string x = "abc";
    auto t = std::make_tuple(2, 'a', true, x, 5.2);
    // TRACE(t);
    ECHO(t);
    ECHO(2, 'a', true, x, 5.2);
}
