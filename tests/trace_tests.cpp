/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#include <unordered_map>
#include <vector>
#include "debug.hpp"

struct Custom {
	std::string operator<<(char c) const {
		return "[char #" + std::to_string(c) + "]";
	}
};

int main(int, char**) {
	char k = 'A';
	TRACE(k);
	TRACE(k, Custom());
	TRACE_L("label", k, Custom());

	std::vector<int> v = {42, 30, 7};
	TRACE_IT(v);
}
