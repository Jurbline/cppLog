#include <string.h>
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

class String
{
public:
    String()
    : _pstr(nullptr)
    {
        cout << "String()" << endl;
    }

    String(const char *pstr)
    : _pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }

    //将拷贝构造函数与赋值运算符函数称为具有复制控制语义的函数
    //拷贝（复制）构造函数
    String(const String &rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(_pstr, rhs._pstr);
    }

    //赋值运算符函数
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)//1、自赋值
        {
            delete [] _pstr;//2、释放做操作数
            _pstr = nullptr;

            //3、深拷贝
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;//4、返回*this
    }

    //具备移动语义函数优先于具备复制控制语义的函数
    //
    //将移动构造函数与移动赋值函数称为具有移动语义的函数
    //移动构造函数
    String(String &&rhs)
    : _pstr(rhs._pstr)
    {
        cout << "String(string  &&)" << endl;
        rhs._pstr = nullptr;
    }

    //移动赋值函数
    String &operator=(String &&rhs)
    {
        cout << "String &operator=(String &&)" << endl;
        if(this != &rhs)//1、自移动
        {
            delete [] _pstr;//2、释放左操作数
            _pstr = nullptr;

            //3、浅拷贝
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;//4、返回*this
    }

    ~String()
    {
        cout << "~String()" << endl;
        if(_pstr)
        {
            delete [] _pstr;
            _pstr = nullptr;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
private:
    char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    if(rhs._pstr)
    {
        os << rhs._pstr;
    }

    return os;
}

void test()
{
    String s1("hello");
    cout << "s1 = " << s1 << endl;

    cout << endl;
    String s2 = s1;//拷贝构造函数 
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;

    cout << endl;
    String s3("world");
    cout << "s3 = " << s3 << endl;

    cout << endl;
    s3 = s1;//赋值运算符函数
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
}

void test2()
{
    //隐式转换  String("wangdao")
    //拷贝构造  String s1 = String("wangdao");
    String s1 = "wangdao";
    cout << "s1 = " << s1 << endl;

    cout << endl;
    String s2("world");
    cout << "s2 = " << s2 << endl;

    cout << endl;
    /* s2 = String("hello"); */
    s2 = "hello";
    cout << "s2 = " << s2 << endl;

    cout << endl << "========" << endl;
    String("hello") =  String("hello");
    cout << "1111" << endl;

    cout << endl << "+++++++++" << endl;
    //std::move的作用就是将一个左值转换为右值引用，而该右值引用
    //此时又是一个右值,即：将左值转换为右值
    //底层实现是做了一个强转static_cast<T &&>(lvaue)
    //
    //move本身具备移动的概念吗？能移动什么东西吗？
    s1 = std::move(s1);
    cout << "s1 = " << s1 << endl;

    cout << endl << "------" << endl;
    std::move(s2);
    cout << "s2 = " << s2 << endl;

    cout << endl << ">>>>>>>" << endl;
    s1 = std::move(s2);
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "1222222" << endl;
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}


