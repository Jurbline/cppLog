#include <iostream>
#include <set>
#include <math.h>

using std::set;
using std::cout;
using std::endl;

template <typename Container>
void display(const Container &con)
{
    for(auto &it : con)
    {
        cout << it << " ";
    }
    cout << endl;
}
class Point
{
public:

    friend std::ostream &operator<<(std::ostream &os,const Point &rhs);
    friend bool operator<(const Point &lhs,const Point &rhs);
    friend struct Compare;

    Point(int ix = 0,int iy = 0)
    :_ix(ix)
    ,_iy(iy)
    {

    }
    int getX() const
    {
        return _ix;
    }
    int getY() const
    {
        return _iy;
    }
    double Instance() const
    {
        return hypot(_ix,_iy);
    }
    ~Point()
    {

    }
private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os,const Point &rhs)
{
    os << "(" << rhs._ix
    << "," << rhs._iy << ")";
    return os;
}
//1.
//重载小于符号
bool operator<(const Point &lhs,const Point &rhs)
{
    if(lhs.Instance() < rhs.Instance())
    {
        return true;
    }
    else if(lhs.Instance() == rhs.Instance())
    {
        if(lhs._ix < rhs._ix)
        {
            return true;
        }
        else if(lhs._ix == rhs._ix)
        {
            if(lhs._iy < rhs._iy)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}
//2.
//函数对象
struct Compare
{
    bool operator()(const Point &lhs,const Point &rhs)
    {
        if(lhs.Instance() < rhs.Instance())
        {
            return true;
        }
        else if(lhs.Instance() == rhs.Instance())
        {
            if(lhs._ix < rhs._ix)
            {
                return true;
            }
            else if(lhs._ix == rhs._ix)
            {
                if(lhs._iy < rhs._iy)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
//3.
//命名空间扩展

namespace std
{
template <>
struct less<Point>
{
    bool operator()(const Point &lhs,const Point &rhs) const
    {
        if(lhs.Instance() < rhs.Instance())
        {
            return true;
        }
        else if(lhs.Instance() == rhs.Instance())
        {
            if(lhs.getX() < rhs.getX())
            {
                return true;
            }
            else if(lhs.getX() == rhs.getX())
            {
                if(lhs.getY() < rhs.getY())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

};
}
void test()
{
    set<Point> number = {
        Point(1,2),
        Point(3,4),
        Point(-5,-6),
        Point(3,4),
        Point(-7,8),
        Point(9,-10)
    };
    display(number);
}
int main()
{
    test();
    return 0;
}

