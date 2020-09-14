#include <iostream>

using namespace std;

class Singleton {
public:
	static Singleton* GetInstance() {
		if (instance == nullptr) {
			instance = new Singleton();
		}
		return instance;
	};

	void print() {
		cout << "Singleton print" << endl;
	}
private:
	static Singleton* instance;
	Singleton() = default;
};

Singleton* Singleton::instance = 0;