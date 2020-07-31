#include <iostream>

using namespace std;

class A {
public:
	virtual void foo() {
		cout << "A" << endl;
	}
};

class B : virtual public A {
public:	
	void foo() override {
		cout << "B" << endl;
	}
};

class C : virtual public A {
public:	
	void foo() override {
		cout << "C" << endl;
	}
};

class D : public B, C {
public:	
	void foo() override {
		cout << "D" << endl;
	}
};

int main() {
	A* a = new D;
	a->foo();
}