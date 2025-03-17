#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Computer
{
public:
    Computer(int price,const char *brand)
    :_price(price)
    ,_brand(new char [strlen(brand) + 1]())
    {
        cout << "Computer(int price,char *brand)" << endl;
        strcpy(_brand,brand);
    }
    static void *operator new(size_t sz)
    {
        cout << "void *operator new(size_t sz)" << endl;
        void *pret = malloc(sz);

        return pret;
    }
    static void operator delete(void *pst)
    {
        cout << "void operator delete(void *pst)" << endl;
        free(pst);
    }
    void print() const
    {
        cout << "_price = " << _price << ","
        << "_brand = " << _brand << endl;
    }
    void destroy()
    {
        delete this;
    }
private:

    int _price;
    char *_brand;

    ~Computer()
    {
        cout << "~Computer()" << endl;
        if(_brand)
        {
            delete [] _brand;
            _brand = nullptr;
        }
    }
};
void test()
{
    /* Computer test(88888888,"wangdao");//error */
    /* test->print(); */
}
int main()
{
    Computer *pcom = new Computer(88888888,"wangdao");
    pcom->print();
    pcom->destroy();
    return 0;
}

