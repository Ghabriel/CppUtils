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
    // A<volatile int, B<int**, const int>> v[3];
    // A<C, int> v;
    D<int**, const long double, volatile unsigned short, std::reference_wrapper<bool>, std::nullptr_t> v;
    std::cout << utils::type(v) << std::endl;
}
