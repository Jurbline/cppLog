#include <iostream>
#include <memory>

class Point {
public:
    Point(int ix = 0, int iy = 0)
        : _ix(ix), _iy(iy) {
        std::cout << "Point(int, int)" << std::endl;
    }

    void print() const {
        std::cout << "(" << _ix << "," << _iy << ")" << std::endl;
    }

    ~Point() {
        std::cout << "~Point()" << std::endl;
    }

private:
    int _ix;
    int _iy;
};

int main() {
    // 手动创建多个 unique_ptr，并分别初始化不同的 Point 对象
    std::unique_ptr<Point> up1(new Point(1, 2));
    std::unique_ptr<Point> up2(new Point(3, 4));
    std::unique_ptr<Point> up3(new Point(5, 6));
    std::unique_ptr<Point> up4(new Point(7, 8));
    std::unique_ptr<Point> up5(new Point(9, 10));

    // 使用 print() 函数打印每个 Point 对象
    up1->print();
    up2->print();
    up3->print();
    up4->print();
    up5->print();

    // unique_ptr 会在超出作用域时自动销毁并释放内存
    return 0;
}

