#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;

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
void test()
{
    vector<unique_ptr<Point>> vec;
    unique_ptr<Point> up(new Point(1,2));
    unique_ptr<Point> up2(new Point(3,4));
    unique_ptr<Point> up3(new Point(5,6));
    unique_ptr<Point> up4(new Point(7,8));
    vec.push_back(std::move(up));
    vec.push_back(std::move(up2));
    vec.push_back(std::move(up3));
    vec.push_back(std::move(up4));
    vec.push_back(unique_ptr<Point>(std::move(new Point(9,10))));
    for(size_t i = 0;i < vec.size();++i)
    {
        vec[i]->print();
    }
    

}
int main()
{
    test();
    return 0;
}

