#include <cassert>
#include <iostream>
#include <optional>
#include <type_traits>
#include <vector>
#include "iterators.hpp"

VectorIterator<int> get_test_iterator() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    return VectorIterator(a);
}

VectorIterator<int> get_test_iterator_2() {
    std::vector<int> a = {10, 11, 12, 13, 14, 15, 16, 17, 18};
    return VectorIterator(a);
}

void test_count() {
    auto iter = get_test_iterator();

    assert(iter.count() == 9);
}

int main(int, char**) {
    test_count();
}
