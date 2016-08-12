/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator>
#include <string>

namespace utils {
    template<typename T>
    class reverse_iterator {
    public:
        reverse_iterator(const T& value) : value(value) {};
        auto begin() { return value.rbegin(); }
        auto begin() const { return value.rbegin(); }
        auto end() { return value.rend(); }
        auto end() const { return value.rend(); }

    private:
        const T& value;
    };

    template<typename T>
    reverse_iterator<T> make_reverse(const T& iterable) {
        return iterable;
    }
}

#endif
