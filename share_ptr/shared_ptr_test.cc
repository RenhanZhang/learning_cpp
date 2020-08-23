#include "shared_ptr.h"
#include <iostream>

class A {
public:
	A(int x) : v(x) {}
	void print() { std::cout << v << std::endl; }
private:
	int v;
};

class B {
public:
	B(int i, int& j, A&& a) {}
	void print() { std::cout << "B printing." << std::endl; }
};

void Test_ArrowOperator() {
	auto ptr = make_shared<A>(2);
	ptr->print();
}

void Test_Dereference() {
	auto ptr = make_shared<A>(3);
	(*ptr).print();
}

void Test_CopyConstruct() {
	auto ptr1 = make_shared<A>(4);
	shared_ptr<A> ptr2 = ptr1;
	shared_ptr<A> ptr3 = ptr2;

    ptr1->print();
    ptr2->print();
    ptr3->print();
}

void Test_Construcor() {
	A a(5);
	int j = 2;
	auto ptr = make_shared<B>(0, j, std::move(a));
	ptr->print();
}

int main() {
	Test_ArrowOperator();
	Test_Dereference();
	Test_Construcor();
}