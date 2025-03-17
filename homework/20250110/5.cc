#include <iostream>

using std::cout;
using std::endl;

class Point
{
    friend Point operator+(const Point &lhs,const Point &rhs);
public:
    Point(int ix = 0,int iy = 0)
    :_ix(ix)
    ,_iy(iy)
    {
        cout << "Point(int,int)" << endl;
    }
    
    void print()
    {
        cout << "(" << _ix
        << "," << _iy << ")" << endl;
    }

    Point &operator+=(const Point &rhs)
    {
        cout << "Point &operator+=(const Point &rhs)" << endl;
        _ix += rhs._ix;
        _iy += rhs._iy;
        return *this;
    }
//前置++，无(int)
    Point &operator++()//隐含this指针
    {
        ++_ix;
        ++_iy;
        return *this;
    }

    Point operator++(int)
    {
        Point tmp(*this);
        ++_ix;
        ++_iy;
        return tmp;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};

Point operator+(const Point &lhs,const Point &rhs)
{
    return Point(lhs._ix+rhs._ix,lhs._iy+rhs._iy);
}
void test()
{
    Point pt1(1,2);
    cout << "pt1 = ";
    pt1.print();
    cout << endl;
    Point pt2(3,4);
    cout << "pt2 = ";
    pt2.print();
    cout << endl;
    Point pt3 = pt1 + pt2;
    cout << "pt3 = ";
    pt3.print();
    cout << endl;
    pt2 += pt1;
    cout << "pt2 += pt1 =";
    pt2.print();
    cout << endl;


    cout << "Before pt3++ = ";
    pt3.print();
    pt3++;
    cout << "After pt3++ = ";
    pt3.print();
    cout << endl;
    cout << "Before ++pt2 = ";
    pt2.print();
    ++pt2;
    cout << "After ++pt2 = ";
    pt2.print();
}

int main()
{
    test();
    return 0;
}

