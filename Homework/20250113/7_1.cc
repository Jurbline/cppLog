#include<iostream>

using std::cout;
using std::endl;

class A
{
 public:
    int x;
    A(int a = 0) 
	{
		x = a;
	}
    void display() 
	{ 
		cout<< "A.x = " << x << endl;
	}
};
class B
:virtual public A
{ 
public:
	int x;
    B(int a = 0) 
	{
		x=a;
	}
 	

	void display() 
	{
		cout<<"B.x = " << x << endl; 
	}

};

class C
:virtual public A
,public B
{   

 public:
    C(int a, int b, int c) 
	: A(a)
	, B(b)
    {    
		y=c;  
	}
	

   	int gety() 
   	{ 
   		return y;
   	}

private:
	int y;
};
int main()
{ 
	C myc(1,2,3);
 	myc.x = 10;
 	myc.display();

	return 0;

}
