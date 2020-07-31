// #include <iostream>
#include <vector>

// using namespace std;

// To see the disembly code:
// 1. gcc -g -c reference_size.cc
// 2. objdump -d -S reference_size.o

void Foo(int& i, int j) {
	i = 2;
	int b = 3;
	int* c = &b;
}

int main() {
	int i = 0;
	Foo(i, 233);
	// std::cout << i << std::endl;
	// std::vector<int&> a;
}