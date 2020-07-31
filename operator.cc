#include <iostream>

using namespace std;

class A {
public:
	int operator* (int b) {
		return 1;
	}
};

int main() {
	A a;
	int b = 2;
	cout << a * b << endl;
}