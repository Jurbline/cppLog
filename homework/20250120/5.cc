#include <iostream>
#include <cassert>
#include <string>

using std::string;
using std::cout;
using std::endl;

template <typename T>
class Singleton
{
public:
    static T *getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new T();
        }
        return _pInstance;
    }
    template <typename Arg1,typename Arg2>
        static T *getInstance(Arg1 arg1,Arg2 arg2)
        {
            if(_pInstance == nullptr)
            {
                _pInstance = new T(arg1,arg2);
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
    static T *_pInstance;
    Singleton()
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }
};
template <typename T>
T *Singleton<T>::_pInstance = nullptr;

class Point
{
public:
    Point(int ix = 0,int iy = 0)
    :_ix(ix)
    ,_iy(iy)
    {
        cout << "Point(int,int)" << endl;
    }
    
    void print() const
    {
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};
class Computer
{
public:
    Computer(const string brand,int price)
    :_brand(brand)
    ,_price(price)
    {
        cout << "Computer(const string,int)" << endl;
    }

    void print() const
    {
        cout << "Brand = " << _brand << " Price = " << _price << endl;
    }

    ~Computer()
    {
        cout << "~Computer()" << endl;
    }
private:
    string _brand;
    int _price;
};

Point pt(1, 2);
Point pt2(3, 4);

Computer com("Mac", 8888);

int main(void)
{
    Computer *pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    pc1->print();
    pc2->print();
    assert(pc1 == pc2);
    
    Point *pt3 = Singleton<Point>::getInstance(1, 2);
    Point *pt4 = Singleton<Point>::getInstance(1, 2);
    pt3->print();
    pt4->print();
    assert(pt3 == pt4);
    
    return 0;
} 

