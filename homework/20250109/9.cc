#include <iostream>

using std::cout;
using std::endl;

class Base
{
    friend int operator+(Base &lhs,const Base &rhs);
public:
    Base(int x)
    :_x(x)
    {

    }
private:
    int _x;
};
int operator+(Base &lhs,const Base &rhs)
{
    return lhs._x+rhs._x;
}
void test()
{
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);

    cout << (x+y == j + i) << endl;
}

int main()
{
    test();
    return 0;
}

