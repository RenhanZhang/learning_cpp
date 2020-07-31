#include <iostream>

class Base {
	public:
      Base() = default;		
      Base(int i) {}		
	  void print() {
	    std::cout << "Baseeee" << std::endl;
	  }
	private:
	  int j;  
};

class Derived : public Base {
public:
	  // void print() {
	  //   std::cout << "Derived" << std::endl;
	  // }
};

int main() {
	Derived d;
	Derived* d2 = &d;
	d2->print();
}