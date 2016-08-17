/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef PARTIAL_TUPLE_HPP
#define PARTIAL_TUPLE_HPP

#include <tuple>

namespace utils {
    template<std::size_t... Is, typename... Args>
    auto partial_tuple(const std::index_sequence<Is...>&, const std::tuple<Args...>& t) {
        return std::make_tuple(std::get<Is>(t)...);
    }
}

#endif
