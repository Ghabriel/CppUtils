#include <memory>
#include <iostream>
#include "macros.hpp"
#include "pointer_holder.hpp"

int main(int, char**) {
    std::string target = "Hello, world!";
    auto container = utils::hold(target);
    container = "test";
    TRACE(target);
    TRACE(container->size());
}
