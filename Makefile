all:
	g++ tests/debug_iterators.cpp -I include/ -o main -std=c++17

clang:
	clang++ tests/debug_iterators.cpp -I include/ -o main -std=c++17

production:
	g++ tests/debug_iterators.cpp -I include/ -o main -std=c++17 -O3 -fdevirtualize-at-ltrans -fipa-pta -fuse-linker-plugin
