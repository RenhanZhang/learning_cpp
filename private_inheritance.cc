// This class illustrates private inheritance.
class Base {
public:
  int a;
protected:
  int b;
};

class PrivatelyDerived : private Base {
public:
    // If you want to make PrivatelyDerived::a accessible outside
    // of this class, try
    // using Base::a;
    void print() {
    	int c = a;
    	int d = b;
    }
};

class PubliclyDerived : public Base {
public:
    void print() {
    	int c = a;
    	int d = b;
    }
};

int main() {
	PrivatelyDerived d;
    //d.a;   // ERROR

    PubliclyDerived pd;
    pd.a;    // OK
}