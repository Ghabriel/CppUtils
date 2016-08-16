/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef SUBPACK_HPP
#define SUBPACK_HPP

#include <tuple>

namespace utils {
    namespace __detail {
        template<std::size_t I, std::size_t... Is, typename T, typename... Args>
        std::tuple<Args...> internal_without_first(const std::index_sequence<I, Is...>&,
            const std::tuple<T, Args...>& t) {

            return std::make_tuple(std::get<Is>(t)...);
        }

        template<typename T, typename... Args>
        std::tuple<Args...> without_first(const std::tuple<T, Args...>& t) {
            return internal_without_first(std::make_index_sequence<1 + sizeof...(Args)>(), t);
        }



        template<std::size_t N>
        struct internal_subpack {
            template<typename T, typename... Args>
            auto operator()(const std::tuple<T, Args...>& t) const {
                return internal_subpack<N-1>()(without_first(t));
            }
        };

        template<>
        struct internal_subpack<0> {
            template<typename... Args>
            std::tuple<Args...> operator()(const std::tuple<Args...>& t) const {
                return t;
            }
        };
    }

    template<std::size_t N, typename... Args>
    auto subpack(const std::tuple<Args...>& tuple) {
        return __detail::internal_subpack<N>()(tuple);
    }
}

#endif
