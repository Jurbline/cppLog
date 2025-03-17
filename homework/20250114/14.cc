#include <iostream>

using std::endl;
using std::cout;

class Base
{
public:
	Base(int i) 
	{
		b = i;
	}
    Base()
    :b(0)
    {

    }
    virtual void Print()
    {	cout << "Base 's Print() called." << endl;}
protected:
	int b;
};

class Derived1
:public Base
{
public:
	void Print()
	{
		cout<<"Derived1's Print() called."<<endl;
	}
};

class Derived2
:public Base
{
public:
    void Print()
    {
        cout << "Derived2's Print() called. "<< endl;
    }
};

void fun(Base &obj)
{      
	obj.Print();
}

int main(void)
{ 
    Derived1 d1;
    Derived2 d2;
    fun(d1);
    fun(d2);
	return 0;
}
