#include <iostream>
#include <ostream>
#include <tuple>
// #include "bimap.hpp"
#include "macros.hpp"
#include "type.hpp"

namespace test {
    class A {};
}

struct Printable {};

inline std::ostream& operator<<(std::ostream& stream, const Printable& p) {
    return stream << "printable";
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

    // test::A t;
    // ECHO(utils::type(t));
    // ECHO(typeid(t).name());

    Printable p;
    TRACE(p);

    std::tuple<int, char, bool> t(2, 'a', true);
    TRACE(t);

    ECHO("potato");
    ECHO(&t);
}
