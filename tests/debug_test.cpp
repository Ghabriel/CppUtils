#include <typeinfo>
#include <unordered_map>
#include <vector>
#include "debug.hpp"

struct Custom {
	std::string operator()(char c) const {
		return "[char #" + std::to_string(c) + "]";
	}
};

int main(int, char**) {
	char k = 'A';
	TRACE(k);
	TRACE(k, Custom());

	std::vector<int> v = {42, 30, 7};
	TRACE_IT(v);
}
