/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#include <iostream>
#include "macros.hpp"
#include "sequence.hpp"

template<std::size_t... Is>
void print_sequence(const std::index_sequence<Is...>& seq) {
    EXPAND(ECHO(Is));
}

int main(int, char**) {
    print_sequence(utils::sequence<2,5>());
}
