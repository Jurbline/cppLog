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
class Cylinder
:public Circle
{
public:
    Cylinder(double r,double h)
    :Circle(r)
    ,_high(h)
    {

    }
    double getVolume()
    {
        double temp = getArea();
        return temp*_high;
    }
    void showVolume()
    {
        show();
        cout << "High = " << _high << endl;
        cout << "Volume = " << getVolume() << endl;
    }
private:
    double _high;
};
void test()
{
    cout << "cc" << endl;
    Circle cc;
    cc.show();
    cout << endl << "cc1" << endl;
    Circle cc1(3);
    cc1.show();
    cout << endl << "cl" << endl;
    Cylinder cl(5,3);
    cl.showVolume();
}
int main()
{
    test();
    return 0;
}

