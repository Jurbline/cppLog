#include <iostream>
#include <memory>
#include <pthread.h>

using std::cout;
using std::endl;
using std::shared_ptr;

class Child;//类的前向声明

class Parent
{
public:
    Parent()
    {
        cout <<"Parent()" << endl;
    }

    ~Parent()
    {
        cout <<"~Parent()" << endl;
    }

    shared_ptr<Child> _spChild;
};

class Child
{
public:
    Child()
    {
        cout <<"Child()" << endl;
    }

    ~Child()
    {
        cout <<"~Child()" << endl;
    }

    shared_ptr<Parent> _spParent;
};

//内存泄漏
void test()
{
    shared_ptr<Parent> parentPtr(new Parent());
    shared_ptr<Child> childPtr(new Child());
    cout << "parentPtr.use_count() = " 
        << parentPtr.use_count() << endl;
    cout << "childPtr.use_count() = " 
        << childPtr.use_count() << endl;

    //parentPtr、childPtr、_spParent、_spChild
    parentPtr->_spChild = childPtr;//赋值操作
    childPtr->_spParent = parentPtr;//赋值
    cout << "parentPtr.use_count() = " 
        << parentPtr.use_count() << endl;
    cout << "childPtr.use_count() = " 
        << childPtr.use_count() << endl;

    //最终靠两个栈对象parentPtr与childPtr销毁的时候，将引用计数
    //减一，不足以将堆空间回收，所以造成了内存泄漏
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

