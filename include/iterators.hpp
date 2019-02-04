#include <iostream>
#include <optional>
#include <type_traits>
#include <vector>

template<typename T>
class Iterator;

namespace iter {
    template<typename T>
    class StepIterator : public Iterator<T> {
      public:
        StepIterator(Iterator<T>& source, size_t step) : source(source), step(step) { }

        virtual std::optional<T> next() override {
            if (!generated_first) {
                generated_first = true;
                return source.next();
            }

            return source.nth(step - 1);
        }

      private:
        Iterator<T>& source;
        size_t step;
        bool generated_first = false;
    };

    template<typename T> 
    class ChainIterator : public Iterator<T> {
      public:
        ChainIterator(Iterator<T>& first, Iterator<T>& second) : first(first), second(second) { }

        virtual std::optional<T> next() override {
            std::optional<T> next = first.next();

            if (next.has_value()) {
                return next;
            }

            return second.next();
        }

      private:
        Iterator<T>& first;
        Iterator<T>& second;
    };

    template<typename T, typename U>
    class ZipIterator : public Iterator<std::pair<T, U>> {
        using TargetType = std::pair<T, U>;
      public:
        ZipIterator(Iterator<T>& first, Iterator<U>& second) : first(first), second(second) { }

        virtual std::optional<TargetType> next() override {
            std::optional<T> first_next = first.next();

            if (!first_next.has_value()) {
                return std::optional<TargetType>();
            }

            std::optional<T> second_next = second.next();

            if (!second_next.has_value()) {
                return std::optional<TargetType>();
            }

            return std::optional<TargetType>(std::make_pair(*first_next, *second_next));
        }

      private:
        Iterator<T>& first;
        Iterator<U>& second;
    };

    template<typename T, typename F>
    class MapIterator : public Iterator<std::invoke_result_t<F, T>> {
        using TargetType = std::invoke_result_t<F, T>;
      public:
        MapIterator(Iterator<T>& source, F fn) : source(source), fn(fn) { }

        virtual std::optional<TargetType> next() override {
            std::optional<T> next_value = source.next();

            if (!next_value.has_value()) {
                return std::optional<TargetType>();
            }

            return std::optional<TargetType>(fn(*next_value));
        }

      private:
        Iterator<T>& source;
        F fn;
    };

    template<typename T, typename P>
    class FilterIterator : public Iterator<T> {
      public:
        FilterIterator(Iterator<T>& source, P predicate) : source(source), predicate(predicate) { }

        virtual std::optional<T> next() override {
            while (true) {
                std::optional<T> next_value = source.next();

                if (!next_value.has_value()) {
                    return std::optional<T>();
                }

                if (predicate(*next_value)) {
                    return std::optional<T>(*next_value);
                }
            }
        }

      private:
        Iterator<T>& source;
        P predicate;
    };

    template<typename T, typename F>
    class FilterMapIterator : public Iterator<typename std::invoke_result_t<F, T>::value_type> {
        using TargetType = typename std::invoke_result_t<F, T>::value_type;
      public:
        FilterMapIterator(Iterator<T>& source, F fn) : source(source), fn(fn) { }

        virtual std::optional<TargetType> next() override {
            while (true) {
                std::optional<T> next_value = source.next();

                if (!next_value.has_value()) {
                    return std::optional<TargetType>();
                }

                std::optional<TargetType> result = fn(*next_value);

                if (result.has_value()) {
                    return *result;
                }
            }
        }

      private:
        Iterator<T>& source;
        F fn;
    };

    template<typename T>
    class RangeIterator {
      public:
        RangeIterator(Iterator<T>& source) : source(source), cached_next(source.next()) { }

        RangeIterator& operator++() {
            return *this;
        }

        T operator*() {
            auto next = std::move(cached_next);
            cached_next = source.next();
            return *next;
        }

        bool operator==(const std::optional<T>& end) {
            // return !cached_next.has_value() && !end.has_value();
            return !cached_next.has_value();
        }

        bool operator!=(const std::optional<T>& end) {
            return !(*this == end);
        }

      private:
        Iterator<T>& source;
        std::optional<T> cached_next;
    };
}

template<typename T>
class Iterator {
 public:
    virtual std::optional<T> next() = 0;

    size_t count() {
        return fold(0, [](auto acc, auto) { return acc + 1; });
    }

    std::optional<T> last() {
        std::optional<T> last_value;
        std::optional<T> next_value = next();

        while (next_value.has_value()) {
            last_value = std::move(next_value);
            next_value = next();
        }

        return last_value;
    }

    std::optional<T> nth(size_t n) {
        std::optional<T> next_value = next();

        for (size_t i = 0; i < n; i++) {
            next_value = next();
        }

        return next_value;
    }

    iter::StepIterator<T> step_by(size_t step) {
        return iter::StepIterator(*this, step);
    }

    iter::ChainIterator<T> chain(Iterator<T>& other) {
        return iter::ChainIterator(*this, other);
    }

    template<typename U>
    iter::ZipIterator<T, U> zip(Iterator<U>& other) {
        return iter::ZipIterator(*this, other);
    }

    template<typename F>
    iter::MapIterator<T, F> map(F fn) {
        return iter::MapIterator(*this, fn);
    }

    template<typename F>
    void for_each(F fn) {
        std::optional<T> next_value = next();

        while (next_value.has_value()) {
            fn(*next_value);
            next_value = next();
        }
    }

    template<typename P>
    iter::FilterIterator<T, P> filter(P predicate) {
        return iter::FilterIterator(*this, predicate);
    }

    template<typename F>
    iter::FilterMapIterator<T, F> filter_map(F fn) {
        return iter::FilterMapIterator(*this, fn);
    }

    template<typename Result, typename F>
    Result fold(Result init, F fn) {
        for_each([&init, fn](T value) {
            init = fn(init, value);
        });

        return init;
    }

    T sum() {
        return fold(0, [](auto acc, auto value) { return acc + value; });
    }

    template<typename Container>
    Container collect() {
        Container container;
        auto back_inserter = std::back_inserter(container);

        for (auto value : *this) {
            *back_inserter = value;
            ++back_inserter;
        }

        return container;
    }

    iter::RangeIterator<T> begin() {
        return iter::RangeIterator(*this);
    }

    std::optional<T> end() {
        return std::optional<T>();
    }
};

template<typename T>
class VectorIterator : public Iterator<T> {
 public:
    VectorIterator(const std::vector<T>& vector) : vector(vector) { }

    virtual std::optional<T> next() override {
        if (next_index >= vector.size()) {
            return std::optional<T>();
        }

        next_index++;
        return std::optional<T>(vector[next_index - 1]);
    }

 private:
    std::vector<T> vector;
    size_t next_index = 0;
};
