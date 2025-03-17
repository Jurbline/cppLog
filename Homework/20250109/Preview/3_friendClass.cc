#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

class Point;

class Line
{
    friend class Point;
public:
    //重载任然需要分别设置友元，但也可以通过友元类
    double distance(const Point &lhs,const Point &rhs);
    double distance(Point &lhs,int ix);
    void func(Point &lhs);
private:
    int _iz;
};
class Point
{
    friend double Line::distance(const Point &lhs,const Point &rhs);
    friend double Line::distance(Point &lhs,int ix);
    friend void Line::func(Point &lhs);
public:
    Point(int ix = 0,int iy = 0)
    :_ix(ix)
    ,_iy(iy)
    {
        cout << "Point(int ix = 0,int iy = 0)" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

    void setZ(Line &line,int iz)
    {
        line._iz = iz;
    }

    void print() const
    {
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }

private:
        int _ix;
        int _iy;
};

double Line::distance(const Point &lhs,const Point &rhs)
{
    return hypot(lhs._ix-rhs._ix,rhs._iy-rhs._iy);
}

double Line::distance(Point &lhs,int ix)
{
    lhs._ix = ix;
    return lhs._ix;
}

void test()
{
    Point pt1(1,2);
    cout << "pt1 = ";
    pt1.print();

    Point pt2(3,4);
    cout << "pt2 = ";
    pt2.print();

    cout << endl;

    //不必创建对象，通过Line().ditance可以直接调用类下的函数
    cout << endl << "The distance is : " << Line().distance(pt1,pt2) << endl;
}

int main()
{
    test();
    return 0;
}

