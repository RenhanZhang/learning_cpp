#include "singleton.h"
#include <thread>
#include <vector>

void get_singleton() {
	Singleton::GetInstance()->print();
}

void multi_thread() {
	std::vector<std::thread*> t;

	for (int i = 0; i < 10000; i++) {
		t.push_back(new std::thread(get_singleton));
	}
	
	for (auto& th : t) {
		th->join();
		delete th;
	}
}

int main() {
	multi_thread();

	Singleton::GetInstance()->print();
	return 0;
}