#include <utility>
#include <iostream>
#include <memory>

template<typename V>
class shared_ptr {
public:
	shared_ptr(V* v);

    shared_ptr(const shared_ptr& other);

    V* operator->() { return v; }

    V& operator*() {return *v; }

    virtual ~shared_ptr();

private:
    int* count;
    V* v;    
};

template<typename V>
shared_ptr<V>::shared_ptr(V* ptr) {
	count = new int(1);
	v = ptr;
}

template<typename V>
shared_ptr<V>::shared_ptr(const shared_ptr& other) {
	count = other.count;
	(*count) += 1;
	v = other.v;
}

template<typename V>
shared_ptr<V>::~shared_ptr() {
	*count -= 1;
	if (*count == 0) {
		std::cout << "Deleting underlying ptrs" << std::endl;
		delete count;
		delete v;
	}
}

// Util function to create a shared ptr;
template<typename V, typename... Args>
shared_ptr<V> make_shared(Args&&... args) {
	shared_ptr<V> result(new V(std::forward<Args>(args)...));
	return result;
}
