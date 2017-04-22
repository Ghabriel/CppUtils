#include <unordered_map>
#include <vector>
#include "simple_debug.hpp"

int main(int, char**) {
	std::unordered_map<char, long> m = {
		{'R', 1},
		{'G', 2},
		{'B', 3}
	};
	TRACE_MAP(m);
	BLANK;

	std::pair<long, std::string> p = {2, "Hello, world!"};
	TRACE_PAIR(p);
	BLANK;	

	std::vector<int> v = {42, 30, 7};
	TRACE_IT(v);
}
