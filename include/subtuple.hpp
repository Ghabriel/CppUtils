/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef SUBPACK_HPP
#define SUBPACK_HPP

#include <tuple>
#include "partial_tuple.hpp"
#include "sequence.hpp"

namespace utils {
    template<std::size_t Min, std::size_t Max, typename... Args>
    auto subtuple(const std::tuple<Args...>& tuple) {
        return partial_tuple(sequence<Min, Max>(), tuple);
    }

    template<std::size_t Min, typename... Args>
    auto subtuple(const std::tuple<Args...>& tuple) {
        return subtuple<Min, sizeof...(Args) - 1>(tuple);
    }
}

#endif
