#include <iostream>

using namespace std;

class A {
	public:
		A() {
			cout << "Default constructor" << endl;
		}
		A(const A& a) {
			cout << "Copied" << endl;
		}
		A& operator =(A& a) {
			cout << "Copy assignment" << endl;
			return *this;
		}		
		A& operator =(A&& a) {
			cout << "Move assignment" << endl;
			return *this;
		}
		A(A&& a) {
			cout << "Move constructor" << endl;
		}
	};

A GetA() {
	// A a = A();
	// cout << "xxxxxxxx" << endl;
	// return a;
	return A();
}

int main() {
	// GetA();
	//A a = GetA();
	A a;
	a = GetA();
}
