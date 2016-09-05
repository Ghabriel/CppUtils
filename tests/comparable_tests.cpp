#include <iostream>
#include "comparable.hpp"
#include "macros.hpp"

class A : public utils::comparable<A> {
public:
	A(int value) : value(value) {}
	bool operator<(const A& other) const {
		return value < other.value;
	}

private:
	int value;
};

int main(int, char**) {
	A a(1);
	A b(2);
	TRACE(a < b);
	TRACE(a > b);
	TRACE(a <= b);
	TRACE(a >= b);
	TRACE(a == b);
	TRACE(a != b);
}
