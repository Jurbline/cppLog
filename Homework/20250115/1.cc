#include <iostream>

using std::cout;
using std::endl;

class Circle
{
public:
    Circle()
    :_radius(0)
    {

    }
    Circle(double r)
    :_radius(r)
    {

    }
    double getArea()
    {
        return 3.14*_radius*_radius;
    }
    double getPerimeter()
    {
        return 2*3.14*_radius;
    }
    void show()
    {
        cout << "Radius = " << _radius << endl;
        cout << "Area = " << getArea() << endl;
        cout << "getPerimeter = " << getPerimeter() << endl;
    }
private:
    double _radius;
};
void test()
{
    cout << "cc" << endl;
    Circle cc;
    cc.show();
    cout << endl << "cc1" << endl;
    Circle cc1(3);
    cc1.show();
}
int main()
{
    test();
    return 0;
}

