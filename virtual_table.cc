#include <iostream>

using namespace std;

class A {
public:
	virtual void Foo() {};	
};

class B {
	virtual void Foo() {};	
	virtual void Bar() {};	
};

int main() {
	cout << sizeof(class A) << endl;
	cout << sizeof(class B) << endl;
}