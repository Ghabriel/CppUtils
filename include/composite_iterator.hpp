/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef COMPOSITE_ITERATOR_HPP
#define COMPOSITE_ITERATOR_HPP

#include <functional>
#include <vector>

namespace utils {
    template<typename T, template<typename...> class C>
    class composite_iterator {
    public:
        template<typename... Args>
        void init(const C<T>& iterable, Args&&... args) {
            iterables.push_back(iterable);
            init(args...);
        }

        void init() {
            index = 0;
            currValue = iterables[index].get().begin();
        }

        composite_iterator<T, C>& begin() {
            init();
            return *this;
        }

        composite_iterator<T, C>& end() {
            index = iterables.size() - 1;
            currValue = iterables[index].get().end();
            return *this;
        }

        composite_iterator<T, C>& operator++() {
            ++currValue;
            if (currValue == iterables[index].get().end() && index < iterables.size() - 1) {
                index++;
                currValue = iterables[index].get().begin();
            }
            return *this;
        }

        const T& operator*() {
            return *currValue;
        }

        bool operator==(const composite_iterator<T, C>& other) const {
            return index == other.index && currValue == other.currValue;
        }

        bool operator!=(const composite_iterator<T, C>& other) const {
            return !(*this == other);
        }

    private:
        std::vector<std::reference_wrapper<const C<T>>> iterables;
        std::size_t index;
        typename C<T>::const_iterator currValue;
    };

    template<typename T, template<typename...> class C, typename... Args>
    composite_iterator<T, C> make_composite(const C<T>& iterable, Args&&... args) {
        composite_iterator<T, C> instance;
        instance.init(iterable, args...);
        return instance;
    }
}

#endif