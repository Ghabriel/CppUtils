#include <iostream>
#include <vector>
#include "macros.hpp"
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

template<typename T1, typename... T>
class E {};

class Test {};

class BigClassName {};

namespace example {
	class Something {};

	namespace inner {
		class Hello {};
	}
}

namespace {
	class Scoped {};
}

template<typename T>
void printType(T value) {
	T var = value;
	ECHO(typeid(var).name());
}

template<typename T>
void printType() {
	T var;
	ECHO(typeid(var).name());
}

int main(int, char**) {
    // A<volatile int, B<int**, const int>> x[3];
    // std::cout << utils::type(x) << std::endl;

    // D<int**, const long double, volatile unsigned short, std::reference_wrapper<bool>, std::nullptr_t> y;
    // std::cout << utils::type(y) << std::endl;

    // A<B<C,D<C,C,C,C>>, D<B<C,C>,A<C,D<>>>> z;
    // std::cout << utils::type(z) << std::endl;

	// int x = 1;
	// example::Something y;
	// char str[20];
	// C c[20];

	// printType<int>();
	// printType<int&>(x);
	// printType<int*>();
	// printType<const int>(x);
	// printType<const int*>(nullptr);
	// printType<volatile int>();
	// printType<const volatile int>(x);
	// printType<const volatile int&>(x);
	// printType<C>();
	// printType<BigClassName>();
	// printType<example::Something>();
	// printType<Scoped>();
	// printType<example::Something&>(y);
	// BLANK
	// printType<D<int&>>();
	// printType<D<char,char,char>>();
	// printType<A<char,char>>();
	// printType<E<char,char,char>>();
	// printType<example::inner::Hello>();
	// // TRACE(utils::type(D<char,char,char>()));
	// // TRACE(utils::type(E<char,char,char>()));
	// printType<int* const * const>(nullptr);
	// printType<decltype(str)>();
	// printType<decltype(c)>();
	// BLANK
	// char (*argFn)(bool, int);
	// char (*noArgFn)();
	// void (*procedure)();
	// auto lambdaArg = [](bool, int) { return 'a'; };
	// auto lambdaNoArg = []() { return 'a'; };
	// auto lambdaProcedure = [](){};
	// printType<decltype(argFn)>();
	// ECHO(typeid(*argFn).name());
	// printType<decltype(noArgFn)>();
	// printType<decltype(procedure)>();
	// ECHO(typeid(lambdaArg).name());
	// ECHO(typeid(lambdaNoArg).name());
	// ECHO(typeid(lambdaProcedure).name());

	// BLANK
	// ECHO("----------------------------");
	// BLANK

	ECHO(utils::type(example::Something()));
}
