#include <iostream>

class A {
	public:

	char x;
};

class B {
	public:

	char y;
};

class C : public A, public B {
public:
	char z;
};

int main() {
	C c;
	A* a = &c;
	B* b = &c;

	std::cout << ((void*) a == (void*) b) << std::endl;
	std::cout << &C::x << std::endl;
std::cout << &C::y << std::endl;
	std::cout << &C::z << std::endl;
}