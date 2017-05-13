/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#include "debug.hpp"
#include "xtrace.hpp"

int main(int, char**) {
	char a = 'A';
	XTRACE(a);

	unsigned b = 42;
	XTRACE(b);

	int* c = new int(42);
	XTRACE(c);
	delete c;

	auto d = std::make_shared<int>(42);
	XTRACE(d);

	std::vector<int> e = {42, 30, 7};
	XTRACE(e);

	std::pair<int, std::string> f = {42, "Hello, world!"};
	XTRACE(f);

	auto g = std::tuple<std::vector<char>, int, bool>{{'A', 'Z'}, 42, true};
	XTRACE(g);

	std::reference_wrapper<decltype(g)> h = g;
	XTRACE(h);
}
