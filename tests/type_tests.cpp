#include <iostream>
#include <vector>
#include "type.hpp"

template<typename T>
void report(const T& t) {
    std::cout << typeid(t).name() << std::endl;
    std::cout << type(t) << std::endl;
}

template<typename T1, typename T2>
class A {};

template<typename T1, typename T2>
class B {};

class C {};

template<typename... T>
class D {};

int main(int, char**) {
    A<volatile int, B<int**, const int>> x[3];
    std::cout << utils::type(x) << std::endl;

    D<int**, const long double, volatile unsigned short, std::reference_wrapper<bool>, std::nullptr_t> y;
    std::cout << utils::type(y) << std::endl;

    A<B<C,D<C,C,C,C>>, D<B<C,C>,A<C,D<>>>> z;
    std::cout << utils::type(z) << std::endl;
}
