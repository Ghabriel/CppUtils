#include <iostream>
#include <vector>
#include "crtp_iterators.hpp"

VectorIterator<int> get_test_iterator() {
    std::vector<int> vec;

    for (int i = 0; i < 1e8; i++) {
        vec.push_back(i);
    }

    return VectorIterator(vec);
}

int main(int, char**) {
    auto count = get_test_iterator()
        .filter([](auto value) { return value % 2 == 0; })
        .filter([](auto value) { return value % 3 == 0; })
        .count();

    std::cout << count << std::endl;
}
