#include <iostream>
#include <cassert>

template <typename T>
class Singleton
{
public:
    // 获取单例对象
    static T* getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new T();  // 创建单例对象
        }
        return _instance;
    }

    // 带参数的获取单例对象
    template <typename Arg1, typename Arg2>
    static T* getInstance(Arg1 arg1, Arg2 arg2)
    {
        if (_instance == nullptr)
        {
            _instance = new T(arg1, arg2);  // 使用参数创建单例对象
        }
        return _instance;
    }

    // 禁止拷贝和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    // 私有构造函数，防止外部创建实例
    Singleton() {}

    // 存储单例对象的指针
    static T* _instance;
};

// 定义静态成员变量
template <typename T>
T* Singleton<T>::_instance = nullptr;

// 示例类：Point
class Point
{
public:
    Point(int x, int y) : _x(x), _y(y)
    {
        std::cout << "Point(" << x << ", " << y << ") created" << std::endl;
    }

    void print() const
    {
        std::cout << "Point(" << _x << ", " << _y << ")" << std::endl;
    }

private:
    int _x, _y;
};

// 示例类：Computer
class Computer
{
public:
    Computer(std::string brand, int price) : _brand(brand), _price(price)
    {
        std::cout << "Computer(" << _brand << ", " << _price << ") created" << std::endl;
    }

    void print() const
    {
        std::cout << "Computer: " << _brand << " " << _price << std::endl;
    }

private:
    std::string _brand;
    int _price;
};

int main()
{
    // 获取 Computer 类型的单例
    Computer* pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer* pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    pc1->print();
    pc2->print();

    // 确保 pc1 和 pc2 是同一个实例
    assert(pc1 == pc2);

    // 获取 Point 类型的单例
    Point* pt3 = Singleton<Point>::getInstance(1, 2);
    Point* pt4 = Singleton<Point>::getInstance(1, 2);
    pt3->print();
    pt4->print();

    // 确保 pt3 和 pt4 是同一个实例
    assert(pt3 == pt4);

    return 0;
}

