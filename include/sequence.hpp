/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <utility>

namespace utils {
    namespace {
        template<typename T, T N, typename = void>
        struct padded {
            template<T Head, T... Tail>
            auto operator()(const std::integer_sequence<T, Head, Tail...>&) const {
                return padded<T, N-1>()(std::integer_sequence<T, Tail...>());
            }
        };

        template<typename T, T N>
        struct padded<T, N, typename std::enable_if<N == 0>::type> {
            template<T... Args>
            std::integer_sequence<T, Args...> operator()(const std::integer_sequence<T, Args...>& seq) const {
                return seq;
            }
        };        
    }

    template<typename T, T Min, T Max>
    auto sequence() {
        return padded<T, Min>()(std::make_integer_sequence<T, Max+1>());
    }

    template<std::size_t Min, std::size_t Max>
    auto sequence() {
        return sequence<std::size_t, Min, Max>();
    }
}

#endif
