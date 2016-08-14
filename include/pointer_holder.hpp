/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef POINTER_HOLDER_HPP
#define POINTER_HOLDER_HPP

#include <ostream>

namespace utils {
    template<typename T>
    class pointer_holder {
    public:
        explicit pointer_holder(T& data) : data(&data) {}
        pointer_holder<T>& operator=(const T& newData) {
            *data = newData;
            return *this;
        }

        T& operator*() const {
            return *data;
        }

        T* operator->() const {
            return data;
        }

    private:
        T* data;
    };

    template<typename T>
    pointer_holder<T> hold(T& data) {
        return pointer_holder<T>(data);
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& stream, const pointer_holder<T>& holder) {
        return stream << *holder;
    }
}

#endif
