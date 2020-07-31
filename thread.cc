#include <thread>
#include <atomic>
#include <iostream>

using namespace std;

void foo(int a) {
	cout << a << endl;
}

void bar() {
	cout << "bar" << endl;
}

int main() {
	for (int i = 0; i < 100; i++) {
			thread a(foo, 3);
	        thread b(bar);
	        a.join();
	        b.join();
	        cout << "===========" << endl;
	}
}