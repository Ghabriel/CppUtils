#include <optional>
#include <vector>

template<typename T>
class Iterator;

namespace iter {
    template<typename T, typename P>
    class FilterIterator : public Iterator<T> {
      public:
        FilterIterator(Iterator<T>& source, P predicate) : source(source), predicate(predicate) { }

        virtual std::optional<T> next() final override {
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
}

template<typename T>
class Iterator {
 public:
    virtual ~Iterator() = default;
    virtual std::optional<T> next() = 0;

    size_t count() {
        return fold(0, [](auto acc, auto) { return acc + 1; });
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

    template<typename Result, typename F>
    Result fold(Result init, F fn) {
        for_each([&init, fn](T value) {
            init = fn(init, value);
        });

        return init;
    }
};

template<typename T>
class VectorIterator : public Iterator<T> {
 public:
    VectorIterator(const std::vector<T>& vector) : vector(vector) { }

    virtual std::optional<T> next() final override {
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
