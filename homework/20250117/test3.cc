#include <iostream>
#include <vector>
#include <memory>

class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    void print() const {
        std::cout << "Point(" << x << ", " << y << ")\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Point>> points;

    points.push_back(std::make_unique<Point>(1, 2));
    points.push_back(std::make_unique<Point>(3, 4));
    points.push_back(std::make_unique<Point>(5, 6));

    // 简单的 for 循环遍历 vector
    for (size_t i = 0; i < points.size(); ++i) {
        points[i]->print();  // 使用 unique_ptr -> 访问成员函数
    }

    return 0;
}

