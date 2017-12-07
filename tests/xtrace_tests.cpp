/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#include <deque>
#include <list>
#include <unordered_map>
#include <vector>
#include "debug.hpp"
#include "xtrace.hpp"

class A {};

template<typename T>
class B {};

template<typename T>
class C {
 public:
	T* begin() const { return nullptr; }
};

template<typename T>
class D {
 public:
	T* begin() const { return nullptr; }
	T* end() const { return nullptr; }
};

class E {};

std::string operator<<(dbg::XTraceFormatter, const E&) {
	return "[instance of E]";
}

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

	std::array<int, 4> i = {1, 2, 3, 4};
	XTRACE(i);

	std::deque<int> j = {1, 2, 3};
	XTRACE(j);

	std::list<int> k = {42, 42};
	XTRACE(k);

	std::map<char, unsigned> l = {
		{'R', 0},
		{'G', 128},
		{'B', 256}
	};
	XTRACE(l);

	std::unordered_map<char, unsigned> m = {
		{'R', 0},
		{'G', 128},
		{'B', 256}
	};
	XTRACE(m);

	std::vector<std::unique_ptr<int>> n;
	n.emplace_back(new int(10));
	n.emplace_back(new int(15));
	XTRACE(n);

	void* o = &b;
	XTRACE(o);

	A p;
	XTRACE(p);

	B<int> q;
	XTRACE(q);

	B<void> r;
	XTRACE(r);

	B<std::nullptr_t> s;
	XTRACE(s);

	C<int> t;
	XTRACE(t);

	D<int> u;
	XTRACE(u);

	const int* v = new int(42);
	XTRACE(v);
	delete v;

	E w;
	XTRACE(w);

	std::weak_ptr<int> x;
	{
		auto temp = std::make_shared<int>(42);
		x = temp;
		XTRACE(x);
	}
	XTRACE(x);
}
