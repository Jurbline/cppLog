#include <iostream>
#include <memory>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const string &brand,int price)
    :_brand(brand)
    ,_price(price)
    {
        cout << "Computer(const string,int)" << endl;
    }
    ~Computer()
    {
        cout << "~Computer()" << endl;
    }
    void print()
    {
        cout << "Brand = " << _brand << ",Pirce = " << _price << endl;
    }
private:
    string _brand;
    int _price;
};

template <typename T>
class RAII
{
public:
    RAII(T *pdata)
    :_pdata(pdata)
    {
        cout << "RAII()" << endl;
    }
    ~RAII()
    {
        cout << "~RAII()" << endl;
        if(_pdata)
        {
            delete _pdata;
            _pdata = nullptr;
        }
    }
    T *get()
    {
        return _pdata;
    }
    T *operator->()
    {
        return _pdata;
    }
    T &operator*()
    {
        return *_pdata;
    }
    void reset(T *pdata)
    {
        if(_pdata)
        {
            delete _pdata;
            _pdata = nullptr;
        }
        _pdata = pdata;
    }
    RAII(const RAII &rhs) = delete;
    RAII &operator=(const RAII &rhs) = delete;
private:
    T *_pdata;
};
void test()
{
    RAII<Computer> cm(new Computer("Xiaomi",1999));
    cm->print();
    (*cm).print();
}
int main()
{
    test();
    return 0;
}

