#include <iostream>
#include <memory>
#include <pthread.h>
using std::cout;
using std::endl;
using std::shared_ptr;

class Child;
class Parent
{
public:
    Parent()
    {
        cout << "Parent()" << endl;
    }
    ~Parent()
    {
        cout << "~Parent()" << endl;
    }
    shared_ptr<Child> _spChild;
};
class Child
{
public:
    Child()
    {
        cout << "Child()" << endl;
    }
    ~Child()
    {
        cout << "~Child()" << endl;
    }
    shared_ptr<Parent> _spParent;
};
void test()
{
    shared_ptr<Parent> parentPtr(new Parent());
    shared_ptr<Child> childPtr(new Child());

    parentPtr->_spChild = childPtr;
    childPtr->_spParent = parentPtr;
}
int main()
{
    test();
    return 0;
}

