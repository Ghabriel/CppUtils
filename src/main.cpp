#include <iostream>
#include <tuple>
// #include "bimap.hpp"
#include "macros.hpp"
#include "type.hpp"

namespace test {
    class A {};
}

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

    test::A t;
    ECHO(utils::type(t));
    ECHO(typeid(t).name());
}
