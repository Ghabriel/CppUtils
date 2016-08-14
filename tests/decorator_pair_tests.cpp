#include <iostream>
#include <unordered_set>
#include "decorator_pair.hpp"
#include "macros.hpp"

int main(int, char**) {
    auto p1 = utils::make_decorator(5, 3);
    auto p2 = utils::make_decorator(5, 10);
    auto p3 = utils::make_decorator(7, 2);
    auto p4 = utils::make_decorator(3, 42);
    TRACE(p1 == p2);
    TRACE(p1 < p3);
    TRACE(p1 > p4);
    TRACE(p2 < p3);
    TRACE(p2 > p4);
    TRACE(p3 > p4);
    TRACE(p1 == 5);
    TRACE(static_cast<int>(p1));

    std::unordered_set<decltype(p1)> set;
    set.insert(p1);
    set.insert(p2);
    set.insert(p3);
    set.insert(p4);
    TRACE(set.size());
    BLANK
    for (auto& pair : set) {
        TRACE(pair.first);
        TRACE(pair.second);
        BLANK
    }
}
