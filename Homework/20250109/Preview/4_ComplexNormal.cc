#include <iostream>

using std::cout;
using std::endl;

//复数

class Complex
{
public:
    Complex(double dreal = 0.0 , double dimag = 0.0)
    :_dreal(dreal)
    ,_dimag(dimag)
    {
        cout << "Complex(double dreal = 0.0 , double dimag = 0.0)" << endl;
    }

    void print() const
    {
        cout << _dreal << "+" << _dimag << "i" << endl;
    }

    ~Complex()
    {
        cout << "~Complex()" << endl;
    }
    
    double getReal() const
    {
        return _dreal;
    }
    double getImag() const
    {
        return _dimag;
    }
private:
    double _dreal;
    double _dimag;
};

Complex operator+(const Complex &lhs,const Complex &rhs)
{
    cout << "Complex operator+(const Complex &lhs,const Complex &rhs)" << endl;
    double real = lhs.getReal() + rhs.getReal();
    double imag = lhs.getImag() + rhs.getImag();
    return Complex(real,imag);
    /* return Complex(lhs._dreal + rhs._dreal,lhs._dimag+rhs._dimag); */
}

void test()
{
    Complex com1(1,2);
    cout << "com1 = ";
    com1.print();

    Complex com2(3,4);
    cout << "com2 = ";
    com2.print();

    cout << endl;
    Complex com3 = com1 + com2;
    cout << "com3 = ";
    com3.print();
}

int main()
{
    test();
    return 0;
}

