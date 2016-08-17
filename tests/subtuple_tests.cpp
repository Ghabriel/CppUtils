/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#include <iostream>
#include "macros.hpp"
#include "subtuple.hpp"
#include "type.hpp"

int main(int, char**) {
    std::tuple<int, char, bool, char, int> t(2, 'a', true, 'z', 42);
    auto s = utils::subtuple<1,3>(t);
    TRACE(std::get<0>(t));
    TRACE(std::get<1>(t));
    TRACE(std::get<2>(t));
    TRACE(std::get<3>(t));
    TRACE(std::get<4>(t));
    BLANK;
    TRACE(std::get<0>(s));
    TRACE(std::get<1>(s));
    TRACE(std::get<2>(s));
    BLANK;
    TRACE(utils::type(t));
    TRACE(utils::type(s));
}
