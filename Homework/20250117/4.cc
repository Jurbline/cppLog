#include <iostream>
#include <string.h>
#include <ostream>

using std::ostream;
using std::string;
using std::cout;
using std::endl;

class String
{
public:
    friend std::ostream &operator<<(std::ostream &os,const String &rhs);
    String()
    :_pstr(nullptr)
    {
        cout << "String()" << endl;
    }
    String(const char *pstr)//c风格
    :_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *pstr)" << endl;
        strcpy(_pstr,pstr);
    }
    String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        cout << "String(const String &rhs)" << endl;
        strcpy(_pstr,rhs._pstr);
    }
    String(String &&rhs)
    :_pstr(rhs._pstr)
    {
        cout << "String(String &&rhs)" << endl;
        rhs._pstr = nullptr;
    }
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &rhs)" << endl;
        if(this != &rhs)
        {
            delete [] _pstr;
            _pstr = nullptr;
            _pstr = new char[strlen(rhs._pstr) + 1];
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }
    String &operator=(String &&rhs)
    {
        cout << "String &operator=(String &&rhs)" << endl;
        if(this != &rhs)
        {
            delete [] _pstr;
            _pstr = nullptr;
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;
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
private:
    char *_pstr;
};

    std::ostream &operator<<(std::ostream &os,const String &rhs)
    {
        if(rhs._pstr)
        {
            os << rhs._pstr;
        }
        return os;
    }
void test()
{
    String s1("test");
    cout << "s1 = " << s1 << endl;
    String s2 = s1;
    cout << "s2 = " << s2 << endl;
    String s3("test2");
    s3 = s1;
    cout << "s3 = " << s3 << endl;

    String s4 = "hello";
    cout << "s4 = " << s4 << endl;
    s4 = "world";
    cout << "s4 = " << s4 << endl;

}
int main()
{
    test();
    return 0;
}

