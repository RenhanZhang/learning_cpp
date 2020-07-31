#include <iostream>

using namespace std;

class A {
	public:
		A() {
			cout << "Default" << endl;
		}
		A(const A& a) {
			cout << "Copied" << endl;
		}
		// A(A&& a) = delete;
};

void CallCopy(A a) {}
void CallRef(const A& a) {}

A GetA() {
	return A();
}

int main() {
	cout << "CallCopy" << endl;
	A a = GetA();
	CallCopy(a);

	cout << "CallRef" << endl;
	CallRef(GetA());	
}
