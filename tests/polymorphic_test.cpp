#include <chrono>
#include <iostream>
#include <vector>
#include "polymorphic_iterators.hpp"

class Clock {
    using TClock = std::chrono::high_resolution_clock;
    using Precision = std::chrono::milliseconds;
 public:
    void start() {
        startTime = TClock::now();
    }

    long long measure() {
        TClock::time_point endTime = TClock::now();
        TClock::duration elapsedTime = endTime - startTime;
        long long result = std::chrono::duration_cast<Precision>(elapsedTime).count();
        startTime = std::move(endTime);

        return result;
    }

 private:
    TClock::time_point startTime;
};

VectorIterator<int> get_test_iterator() {
    std::vector<int> vec;
    vec.reserve(1e8);

    for (int i = 0; i < 1e8; i++) {
        vec.push_back(i);
    }

    return VectorIterator(vec);
}

int main(int, char**) {
    Clock clock;
    clock.start();

    auto testIterator = get_test_iterator();
    std::cout << "VectorIterator creation: " << clock.measure() << "ms\n";

    auto count = testIterator
        // .filter([](auto value) { return value % 2 == 0; })
        .filter([](auto value) { return value % 3 == 0; })
        .count();
    std::cout << "count: " << clock.measure() << "ms\n";

    std::cout << count << std::endl;
}
