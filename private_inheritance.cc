class Base {
public:
  int a;
protected:
  int b;
};

class Derived : private Base {
public:
    // using Base::a;
    void print() {
    	int c = a;
    	int d = b;
    }
};

class DerivedDerived : public Derived {
public:
    void print() {
    	int c = a;
    	int d = b;
    }
};

int main() {
	Derived d;
    //d.a;
}