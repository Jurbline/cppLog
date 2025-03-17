#include <iostream>
#include <memory>

class Point {
public:
    // 将构造函数设为 public，这样可以在外部调用
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
    // 手动创建 Point 对象，并使用 unique_ptr 管理它
    std::unique_ptr<Point> up(new Point(1, 2));

    // 调用 print 函数
    up->print();

    return 0;
}

