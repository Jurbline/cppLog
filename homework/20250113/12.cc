#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Person
{
public:
    Person(const char* name = "",int age = 0)
    {
        cout << "Person(const char*,int)" << endl;
        _name = new char[strlen(name) + 1];
        strcpy(_name,name);
        _age = age;
    }
    //拷贝构造函数
    Person(const Person &rhs)
    {
        _name = new char[strlen(rhs._name) + 1];
        strcpy(_name,rhs._name);
        _age = rhs._age;
    }
    //赋值运算符
    Person &operator=(const Person &rhs)
    {
        if(this != &rhs)
        {
            delete [] _name;
            _name = new char[strlen(rhs._name) + 1];
            strcpy(_name,rhs._name);
            _age = rhs._age;
        }
        return *this;
    }
    void printName()
    {
        cout << _name << endl;
    }
    void printAge()
    {
        cout << _age << endl;
    }
    void display()
    {
        cout << "name: " << _name <<",age = " << _age << endl;
    }
    ~Person()
    {
        cout << "~Person()" << endl;
        delete [] _name;
    }
private:
    char* _name;
    int _age;
};

class Employee
:public Person
{
public:
    Employee(const char* str = "",int age = 0,const char* department = "",double wage = 0.0)
    :Person(str,age)
    {
        cout << "Employee(const char*,int,const char*,double)" << endl;
        _department = new char[strlen(department) + 1];
        strcpy(_department,department);
        _wage = wage;
        _totalWage += wage;
        ++_count;
    }

    Employee(const Employee &rhs)
    :Person(rhs)
    {
        _department = new char[strlen(rhs._department) + 1];
        strcpy(_department,rhs._department);
        _wage = rhs._wage;
        _totalWage += _wage;
        ++_count;
    }

    Employee &operator=(const Employee &rhs)
    {
        if(this != &rhs)
        {
            Person::operator=(rhs);
            _totalWage -= _wage;
            delete [] _department;
            _department = new char[strlen(rhs._department) + 1];
            strcpy(_department,rhs._department);
            _wage = rhs._wage;
            _totalWage += _wage;
        }
        return *this;
    }

    void display()
    {
        cout << "name = ";
        printName();
        cout << "age = ";
        printAge();
        cout << "department = " << _department << endl;
        cout << "wage = " << _wage << endl;
    }
    ~Employee()
    {
        cout << "~Employee()" << endl;
        _totalWage -= _wage;
        --_count;
        delete [] _department;
    }
    static double averageWage()
    {
        if(_count == 0) return 0.0;
        return _totalWage/_count;
    }
private:
    char* _department;
    int _wage;
    static int _count;
    static double _totalWage;
};

double Employee::_totalWage = 0.0;
int Employee::_count = 0;

void test()
{
    cout << endl;

    Employee e1("hkc",21,"Student",19999.0);
    cout << endl;
    cout << "Employee e1(\"hkc\",21,\"Student\",19999.0)" <<endl;
    cout << "e1:" << endl;
    e1.display();
    cout << endl;

    Employee e2("hkc1",22,"Student",18888.0);
    cout << endl;
    cout << "Employee e2(\"hkc1\",22,\"Student\",18888.0)" <<endl;
    cout << "e2:" << endl;
    e2.display();
    cout << endl;

    Employee e3 = e2;
    cout << endl;
    cout << "Employee e3 = e2" << endl;
    cout << "e3:" << endl;
    e3.display();
    cout << endl;

    Employee e4;
    cout << endl;
    e4 = e1;
    cout << "e4 = e1" << endl;
    cout << "e4:" << endl;
    e4.display();
    cout << endl;

    cout << "Average wage is: " << Employee::averageWage() << endl;
}
int main()
{
    test();
    return 0;
}

