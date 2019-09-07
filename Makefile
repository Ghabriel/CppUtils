.PHONY: clang production crtp crtp-O3 polymorphic polymorphic-O3 plain plain-O3 super_plain super_plain-O3

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

plain:
	g++ tests/plain_test.cpp -I include/ -o plain -std=c++17

plain-O3:
	g++ tests/plain_test.cpp -I include/ -o plain -std=c++17 -O3

super_plain:
	g++ tests/super_plain_test.cpp -I include/ -o super_plain -std=c++17

super_plain-O3:
	g++ tests/super_plain_test.cpp -I include/ -o super_plain -std=c++17 -O3
