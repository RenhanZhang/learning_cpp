#include <iostream>

// This file demonstrates that array will be passed
// as point to a function, no matter what the original
// size is.

using namespace std;

void Foo(char a[]) {
	cout << "Arbitratry array size:" << sizeof(a) << endl;
}

void Bar(char a[30]) {
	cout << "Bounded array size:" << sizeof(a) << endl;
}

void Baz(char a[20]) {
	cout << "Bounded array size:" << sizeof(a) << endl;
}

int main() {
	char a[30] = {0};
	Foo(a);
	Bar(a);
	Baz(a);
}