#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

class Point
{
    friend double distance(const Point &lhs,const Point &rhs);
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

    void print() const
    {
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }

private:
        int _ix;
        int _iy;
};

double distance(const Point &lhs,const Point &rhs)
{
    return hypot(lhs._ix-rhs._ix,rhs._iy-rhs._iy);
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

    cout << endl << "The distance is : " << distance(pt1,pt2) << endl;
}

int main()
{
    test();
    return 0;
}

