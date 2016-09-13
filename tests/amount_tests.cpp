#include <iostream>
#include "amount.hpp"
#include "macros.hpp"

template<typename T1, typename T2>
constexpr bool same = std::is_same<T1, T2>::value;

int main(int, char**) {
	utils::Speed speed = 10_m / 2_s;
	// utils::Acceleration accel = 10_m / 2_s; // nope
	utils::Acceleration accel = speed / 2_s;

	auto force = 2_kg * accel;
	TRACE(speed.value);
	TRACE(accel.value);
	TRACE(force.value);
	ECHO(same<decltype(force), utils::Newton>);
}
