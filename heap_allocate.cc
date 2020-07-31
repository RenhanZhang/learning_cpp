#include <iostream>

class A {
	public:
		A(char c) {
			x = c;
		}

	char x;
};

int main() {
	A* a = new A;
		std::cout << a->x << std::endl;
}