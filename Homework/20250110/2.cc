#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
    friend class AutoRelease;
public:
    static Singleton *getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
private:
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(Singleton::_pInstance)
            {
                delete Singleton::_pInstance;
                Singleton::_pInstance = nullptr;
            }
        }
    };

    static AutoRelease _ar;
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
Singleton *Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_ar;
void test()
{
    Singleton::getInstance();
}
int main()
{
    test();
    return 0;
}

