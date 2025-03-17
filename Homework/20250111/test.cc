#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

class String
{
    friend std::ostream &operator<<(std::ostream &os, const String &rhs);

public:
    String()
        : _pstr(new char[5]() + 4)
    {
        cout << "String()" << endl;
        *(int *)(_pstr - 4) = 1;
    }
    ~String()
    {
        cout << "~String()" << endl;
        if (--*(int *)(_pstr - 4) == 0)
        {
            delete[] (_pstr - 4);
        }
    }
    String(const char *pstr)
        : _pstr(new char[5 + strlen(pstr)]() + 4)
    {
        cout << "String(const char *pstr)" << endl;
        strcpy(_pstr, pstr);
        *(int *)(_pstr - 4) = 1;
    }
    // 拷贝构造函数
    String(const String &rhs)
        : _pstr(rhs._pstr)
    {
        cout << "String(const String &rhs)" << endl;
        ++*(int *)(_pstr - 4);
    }
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &rhs)" << endl;
        if (this != &rhs)
        {
            --*(int *)(this->_pstr - 4);
            if (*(int *)(this->_pstr - 4) == 0)
            {
                delete[] (this->_pstr - 4);
            }

            this->_pstr = rhs._pstr;
            ++*(int *)(this->_pstr - 4);
        }
        return *this;
    }

    // 定义代理类
    class CharProxy
    {
    public:
        CharProxy(String &str, size_t idx)
            : _str(str), _idx(idx) {}

        // 赋值操作符（写操作）
        CharProxy &operator=(char ch)
        {
            if (_idx < _str.size())
            {
                if (*(int *)(_str._pstr - 4) > 1) // 如果共享计数 > 1，进行深拷贝
                {
                    char *ptmp = new char[_str.size() + 5] + 4;
                    strcpy(ptmp, _str._pstr);
                    --*(int *)(_str._pstr - 4);
                    _str._pstr = ptmp;
                    *(int *)(_str._pstr - 4) = 1;
                }
                _str._pstr[_idx] = ch;
            }
            return *this;
        }

        // 隐式转换为 char（读操作）
        operator char() const
        {
            if (_idx < _str.size())
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
        String &_str; // 引用外部的 String 对象
        size_t _idx;  // 下标
    };

    // 返回代理对象
    CharProxy operator[](size_t idx)
    {
        return CharProxy(*this, idx);
    }

    const char &operator[](size_t idx) const
    {
        if (idx < size())
        {
            return _pstr[idx];
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        }
    }

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

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    if (rhs._pstr)
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

    cout << endl
         << "执行s3 = s1" << endl;
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

    cout << endl
         << "对s3[0]执行写操作" << endl;
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

    cout << endl
         << "对s1[0]执行读操作" << endl;
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

