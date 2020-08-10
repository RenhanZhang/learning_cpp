#include <iostream>

using namespace std;

void foo() {
    extern int y;
    cout << "y=" << y;
    
	int a[40] = {1, 2, 3};
	for (int i : a) {
		// cout << i;
	}

	int b[3] = {1, 2, 3};
	cout << "typeid(a).name() = " << typeid(a).name() << endl;
	cout << "typeid(b).name() = " << typeid(b).name() << endl;	
	cout << "Equals: " << (typeid(a) == typeid(b)) << endl;
}

int y = 888;

int main() {
	int a[3] = {1, 2, 3};
	foo();

	cout << "y=" << y;
}