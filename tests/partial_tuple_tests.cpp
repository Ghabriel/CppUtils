/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#include <iostream>
#include "macros.hpp"
#include "partial_tuple.hpp"
#include "type.hpp"

int main(int, char**) {
    std::tuple<int, char, bool, char> t(2, 'a', true, 'z');
    auto s = utils::partial_tuple(std::make_index_sequence<2>(), t);
    TRACE(std::get<0>(t));
    TRACE(std::get<1>(t));
    TRACE(std::get<2>(t));
    TRACE(std::get<3>(t));
    BLANK;
    TRACE(std::tuple_size<decltype(s)>::value);
    TRACE(std::get<0>(s));
    TRACE(std::get<1>(s));
    BLANK;
    TRACE(utils::type(t));
    TRACE(utils::type(s));
}
