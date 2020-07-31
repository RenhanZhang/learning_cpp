#include <iostream>

using namespace std;

template<typename T>
class UniquePtr {
	public: 
		explicit UniquePtr(T* t) : t_(t) {}

	    UniquePtr(UniquePtr<T>&) = delete;

        // For conversion from derived class
	    // See https://lokiastari.com/blog/2015/01/23/c-plus-plus-by-example-smart-pointer-part-iii/
	    template<typename U>
	    UniquePtr(UniquePtr<T>&& uptr) {
	    	t_ = uptr.t_;
	    	uptr.t_ = nullptr;
	    }

	    UniquePtr& operator=(UniquePtr<T>&) = delete;

        // For conversion from derived class
	    // See https://lokiastari.com/blog/2015/01/23/c-plus-plus-by-example-smart-pointer-part-iii/
	    template<typename U>
	    UniquePtr& operator=(UniquePtr<U>&& uptr) {
	    	// important
	    	if (this != &uptr) {
	    		delete t_;

	    		t_ = uptr.t_;
	    		uptr.t_ = nullptr;
	    		return *this;	    		
	    	}

	    	return *this;
	    }

	    explicit operator bool() {
	    	return t_;
	    }

	    T& operator*() {
	    	return *t_;
	    }

	    T* operator->() {
			return t_;
		}

	    ~UniquePtr() {
	    	delete t_;
	    }

private:
	T* t_;
};

class B {
public:
	void print() {
		cout << "printing" << endl;
	}
};

void copy_constructor() {
	UniquePtr<B> p(new B);

	// UniquePtr<B> p2 = p;
}

void copy_assignment() {
	UniquePtr<B> p(new B);

	UniquePtr<B> p2(new B);
	
	// p2 = p;	
}

void move_constructor() {
	UniquePtr<B> p(new B);

	UniquePtr<B> p2 = std::move(p);
}

void move_assignment() {
	UniquePtr<B> p(new B);

	UniquePtr<B> p2(new B);
	p2 = std::move(p);
}

int main() {
	B* b = nullptr;
	delete b;
	//copy_constructor(); 

	//copy_assignment();

	move_constructor();

	//move_assignment();

	// p->print();

	// (*(p.operator->())).print();

	//p.operator->print();

	// p.operator ->();
}