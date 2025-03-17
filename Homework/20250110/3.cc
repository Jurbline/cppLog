#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;

class Singleton
{
    /* friend class AutoRelease; */
public:
    static Singleton *getInstance()
    {
        if(_pInstance == nullptr)
        {
            atexit(destroy);
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    static Singleton *_pInstance;
    Singleton()
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }
};
/* Singleton *Singleton::_pInstance = nullptr; */
Singleton *Singleton::_pInstance = Singleton::getInstance();
/* class AutoRelease */
/* { */
/* public: */
/*     AutoRelease() */
/*     { */
/*         cout << "AutoRelease()" << endl; */
/*     } */
/*     ~AutoRelease() */
/*     { */
/*         cout << "~AutoRelease()" << endl; */
/*         if(Singleton::_pInstance) */
/*         { */
/*             delete Singleton::_pInstance; */
/*             Singleton::_pInstance = nullptr; */
/*         } */
/*     } */
/* }; */

void test()
{
    Singleton::getInstance();
    Singleton::getInstance();
    Singleton::getInstance();
    Singleton::getInstance();
    Singleton::getInstance();
    /* AutoRelease ar; */
}
int main()
{
    test();
    return 0;
}
