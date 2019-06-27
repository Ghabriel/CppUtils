#include <cassert>
#include <deque>
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

// void test_count() {
//     auto iter = get_test_iterator();

//     assert(iter.count() == 9);
// }

// void test_last() {
//     auto iterA = get_test_iterator();
//     auto iterB = get_test_iterator_2();

//     assert(iterA.last() == 9);
//     assert(iterB.last() == 18);
// }

// void test_nth() {
//     auto iterA = get_test_iterator();
//     auto iterB = get_test_iterator_2();

//     assert(iterA.nth(2) == 3);
//     assert(iterA.nth(3) == 7);
//     assert(iterB.nth(0) == 10);
//     assert(iterB.nth(0) == 11);
//     assert(iterB.nth(5) == 17);
// }

// void test_step_by() {
//     auto iterA = get_test_iterator();
//     assert(iterA.step_by(2).count() == 5);

//     iterA = get_test_iterator();
//     assert(iterA.step_by(2).nth(1) == 3);
// }


void test_filter() {
    std::cout << "A\n";
    auto count = get_test_iterator()
        .filter([](auto value) { return value > 3; })
        .filter([](auto value) { return value < 8; })
        .count();

    assert(count == 4);

    // auto filter_predicate = [](auto value) { return value > 3 && value < 8; };

    // auto iterA = get_test_iterator();
    // assert(iterA.filter(filter_predicate).count() == 4);

    // iterA = get_test_iterator();
    // auto vec = iterA
    //     .step_by(3)
    //     .filter(filter_predicate)
    //     .collect<std::vector<int>>();
    // std::vector<int> expected_vec = {4, 7};
    // assert(vec == expected_vec);
}

// void test_filter_map() {
//     auto iterA = get_test_iterator();

//     auto vec = iterA
//         .filter_map([](auto value) {
//             if (value > 2 && value < 5) {
//                 return std::optional<std::string>(std::string(value, 'a'));
//             }

//             return std::optional<std::string>();
//         })
//         .collect<std::vector<std::string>>();

//     std::vector<std::string> expected_vec = {"aaa", "aaaa"};
//     assert(vec == expected_vec);
// }

// void test_enumerate() {
//     auto iterA = get_test_iterator();

//     using ValueType = std::vector<std::pair<size_t, std::string>>;

//     auto vec = iterA
//         .step_by(2)
//         .filter([](auto value) { return value <= 5; })
//         .map([](auto value) { return std::string(value, 'a'); })
//         .enumerate()
//         .collect<ValueType>();

//     ValueType expected_vec = {
//         std::make_pair(0, "a"),
//         std::make_pair(1, "aaa"),
//         std::make_pair(2, "aaaaa"),
//     };

//     assert(vec == expected_vec);
// }

// void test_peekable() {
//     auto iterA = get_test_iterator();
//     auto peekable = iterA.peekable();

//     assert(*peekable.peek() == 1);
//     assert(*peekable.next() == 1);
//     assert(*peekable.next() == 2);
//     assert(*peekable.peek() == 3);
//     assert(*peekable.peek() == 3);
//     assert(*peekable.next() == 3);
// }


// void test_collect() {
//     auto iterA = get_test_iterator();

//     auto as_deque = iterA.collect<std::deque<int>>();
//     std::deque<int> expected_deque = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//     assert(as_deque == expected_deque);
// }

int main(int, char**) {
    // test_count();
    // test_last();
    // test_nth();
    // test_step_by();
    test_filter();
    // test_filter_map();
    // test_enumerate();
    // test_collect();
}
