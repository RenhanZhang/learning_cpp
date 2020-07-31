#include <iostream>

using namespace std;

class Singleton {
    public:
        static Singleton* getInstance() {
            if (instance == 0) {
                instance = new Singleton();
            }
            return instance;
        };

        void print() {
            cout << "Singleton print" << endl;
        }
    private:
        static Singleton* instance;

        /* Private constructor to prevent instancing. */
        Singleton();
};

/* Null, because instance will be initialized on demand. */
Singleton* Singleton::instance = 0;

Singleton::Singleton()
{}

int main()
{
    //new Singleton(); // Won't work
    Singleton* s = Singleton::getInstance(); // Ok
    Singleton* r = Singleton::getInstance();

    /* The addresses will be the same. */
    std::cout << s << std::endl;
    std::cout << r << std::endl;
}