.PHONY: clang production crtp crtp-O3 polymorphic polymorphic-O3

all:
	g++ tests/debug_iterators.cpp -I include/ -o main -std=c++17

clang:
	clang++ tests/debug_iterators.cpp -I include/ -o main -std=c++17

production:
	g++ tests/debug_iterators.cpp -I include/ -o main -std=c++17 -O3 -fdevirtualize-at-ltrans -fipa-pta -fuse-linker-plugin

crtp:
	g++ tests/crtp_test.cpp -I include/ -o crtp -std=c++17

crtp-O3:
	g++ tests/crtp_test.cpp -I include/ -o crtp -std=c++17 -O3

polymorphic:
	g++ tests/polymorphic_test.cpp -I include/ -o polymorphic -std=c++17

polymorphic-O3:
	g++ tests/polymorphic_test.cpp -I include/ -o polymorphic -std=c++17 -O3

polymorphic-ultimate:
	g++ tests/polymorphic_test.cpp -I include/ -o polymorphic -std=c++17 -O3 -fdevirtualize-at-ltrans -fipa-pta -fuse-linker-plugin -march=native -flto
