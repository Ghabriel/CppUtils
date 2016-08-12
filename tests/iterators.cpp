#include <iostream>
#include <iterator>
#include <vector>
#include "utils.hpp"

int main(int, char**) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{4, 5, 6};
    std::vector<int> c{7, 8, 9};
    for (int x : utils::make_composite(a, b, c)) {
        std::cout << x << std::endl;
    }
    std::cout << "------------" << std::endl;
    for (int x : utils::make_reverse(a)) {
        std::cout << x << std::endl;
    }
}
