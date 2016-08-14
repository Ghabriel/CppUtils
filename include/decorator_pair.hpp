/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef DECORATOR_PAIR_HPP
#define DECORATOR_PAIR_HPP

#include <utility>

namespace utils {
    template<typename T1, typename T2>
    struct decorator_pair {
        T1 first;
        T2 second;
        operator T1() const { return first; }
        bool operator==(const T1& rhs) const { return first == rhs; }
        bool operator!=(const T1& rhs) const { return first != rhs; }
        bool operator<=(const T1& rhs) const { return first <= rhs; }
        bool operator>=(const T1& rhs) const { return first >= rhs; }
        bool operator<(const T1& rhs) const { return first < rhs; }
        bool operator>(const T1& rhs) const { return first > rhs; }
    };

    template<typename T1, typename T2>
    decorator_pair<T1,T2> make_decorator(const T1& first, const T2& second) {
        return {first, second};
    }
}

namespace std {
    template<typename T1, typename T2>
    struct hash<utils::decorator_pair<T1,T2>> {
        std::size_t operator()(const utils::decorator_pair<T1,T2>& pair) const {
            return std::hash<T1>()(pair.first);
        }
    };
}

#endif
