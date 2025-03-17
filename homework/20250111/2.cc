#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
class String
{
    friend std::ostream &operator<<(std::ostream &os,const String &rhs);
public:

class ReadWrite
{
public:
    ReadWrite(String &str,size_t idx)
    :_str(str)
    ,_idx(idx)
    {

    }
    ReadWrite &operator=(char str)
    {
        if(_idx < _str.size())
        {
            if(_str._pstr[_idx] == str)
            {
                return *this;
            }
        
            if(*(int *)(_str._pstr - 4) > 1)
            {
                char *ptmp = new char[_str.size() + 5]() + 4;
                strcpy(ptmp,_str._pstr);
                --*(int *)(_str._pstr - 4);
                _str._pstr = ptmp;
                *(int *)(_str._pstr - 4) = 1;
            }
            _str._pstr[_idx] = str;
        }
        return *this;
    }
    operator char() const
    {
        if(_idx < _str.size())
        {
            return _str._pstr[_idx];
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        }
    }
private:
    String &_str;
    size_t _idx;
};
    ReadWrite operator[](size_t idx)
{
    return ReadWrite(*this,idx);
}
    String()
    :_pstr(new char[5]() + 4)
    {
        cout << "String()" << endl;
        *(int *)(_pstr - 4) = 1;
    }
    ~String()
    {
        cout << "~String()" << endl;
        if(--*(int *)(_pstr - 4) == 0)
        {
            delete [] (_pstr - 4);
        }
    }
    String(const char *pstr)
    :_pstr(new char[5 + strlen(pstr)]() + 4)
    {
        cout << "String(const char *pstr)" << endl;
        strcpy(_pstr,pstr);
        *(int *)(_pstr - 4) = 1;
    }
    //拷贝构造函数
    String(const String &rhs)
    :_pstr(rhs._pstr)
    {
        cout << "String(const String &rhs)" << endl;
        ++*(int *)(_pstr - 4);
    }
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &rhs)" << endl;
        if(this != &rhs)
        {
            --*(int *)(this->_pstr - 4);
            if(*(int *)(this->_pstr - 4) == 0)
            {
                delete [] (this->_pstr - 4);
            }

            this->_pstr = rhs._pstr;
            ++*(int *)(this->_pstr - 4);
        }
        return *this;
    }
    const char &operator[](size_t idx) const
    {
        if(idx < size())
        {
            return _pstr[idx];
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        }
    }
    /* char &operator[](size_t idx) */
    /* { */
    /*     if(idx < size()) */
    /*     { */
            /* char& oldChar = _pstr[idx]; */
            /* char newChar = oldChar; */
            /* if(oldChar == newChar) */
            /* { */
            /*     return oldChar; */
            /* } */
            /* if(*(int *)(this->_pstr - 4) > 1) */
            /* { */
            /*     char *ptmp = new char[size() + 5] + 4; */
            /*     strcpy(ptmp,_pstr); */
            /*     --*(int *)(this->_pstr - 4); */
                /* _pstr = ptmp; */
                /* *(int *)(this->_pstr - 4) = 1; */
            /* } */
        /* } */
        /* return _pstr[idx]; */
    /* } */

    size_t size() const
    {
        return strlen(_pstr);
    }

    const char *c_str() const
    {
        return _pstr;
    }

    int getRefCount()
    {
        return *(int *)(_pstr - 4);
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
    String s1("hello");
    cout << "s1 = " << s1 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    printf("&s1 = %p\n", s1.c_str());

    cout << endl;
    String s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());

    cout << endl;
    String s3("wangdao");
    cout << "s3 = " << s3 << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("&s3 = %p\n", s3.c_str());

    cout << endl << "执行s3 = s1" << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    printf("&s3 = %p\n", s3.c_str());

    cout << endl << "对s3[0]执行写操作" << endl;
    s3[0] = 'H';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    printf("&s3 = %p\n", s3.c_str());

    cout << endl << "对s1[0]执行读操作" << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    printf("&s3 = %p\n", s3.c_str());

    cout << endl << "对s1进行自赋值操作" << endl;
    s1[0] = 'h';
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    printf("&s3 = %p\n", s3.c_str());
}
int main()
{
    test();
    return 0;
}

