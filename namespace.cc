#include <iostream>

using namespace std;

namespace Foo {
	namespace {
		void anonymous_print() {
			cout << "anonymous_print" << endl;
		}
	}
		void print() {
			cout << "foo->print" << endl;
		}	
}

int main() {
	Foo::anonymous_print();
	Foo::print();
}