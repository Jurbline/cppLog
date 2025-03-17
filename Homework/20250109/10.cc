#include <iostream>
#include <string.h>
#include <limits>

using std::cout;
using std::endl;
using std::string;

class String 
{
public:
	String()
    :_pstr(new char[1]{'\0'})
    {

    }
	String(const char *str)
    {
        if(str)
        {
            size_t len= strlen(str) + 1;
            _pstr = new char[len];
            strcpy(_pstr,str);
        }
        else
        {
            _pstr = new char[1]{'\0'};
        }
    }
	String(const String &str)
    {
        size_t len = strlen(str._pstr) + 1;
        _pstr = new char[len];
        strcpy(_pstr,str._pstr);
    }
	~String()
    {
        delete [] _pstr;
    }
	String &operator=(const String &str)
    {
        if(this != &str)
        {
            delete [] _pstr;
            size_t len = strlen (str._pstr) + 1;
            _pstr = new char[len];
            strcpy(_pstr,str._pstr);
        }
        return *this;
    }
	String &operator=(const char *str)
    {
        delete [] _pstr;
        size_t len = strlen(str) + 1;
        _pstr = new char[len];
        strcpy(_pstr,str);
        return *this;
    }

	String &operator+=(const String &rhs)
    {
        size_t len1 = strlen(_pstr);
        size_t len2 = strlen(rhs._pstr);
        char *newStr = new char[len1 + len2 + 1];
        strcpy(newStr,_pstr);
        strcpy(newStr + len1,rhs._pstr);
        delete [] _pstr;
        _pstr = newStr;
        return *this;

    }
	String &operator+=(const char *str)
    {
        size_t len1 = strlen(_pstr);             
        size_t len2 = strlen(str);         
        char *newStr = new char[len1 + len2 + 1];
        strcpy(newStr,_pstr);                    
        strcpy(newStr + len1,str);         
        delete [] _pstr;                         
        _pstr = newStr;                          
        return *this;                            
    }
    char &operator[](std::size_t index) 
    {
        static char empty = '\0';
        if (index >= strlen(_pstr)) 
        {
            return empty;
        }
        return _pstr[index];
    }

    const char &operator[](std::size_t index) const 
    {
        static const char empty = '\0';
        if (index >= strlen(_pstr)) 
        {
            return empty;
        }
        return _pstr[index];
    }
	/* char &operator[](std::size_t index) */
    /* { */
        /* size_t len = strlen(_pstr); */
        /* if(index < len) */
        /* { */
            /* return _pstr[index]; */
        /* } */
    /* } */
	/* const char &operator[](std::size_t index) const */
    /* { */
        /* return _pstr[index]; */
    /* } */
	
	std::size_t size() const
    {
        return strlen(_pstr);
    }
	const char* c_str() const
    {
        return _pstr;
    }
	
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);
	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);
	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);
    friend String operator+(const String &lhs, const String &rhs);
    friend String operator+(const String &lhs, const char *str);
    friend String operator+(const char *, const String &);

private:
	char * _pstr;
};
    bool operator==(const String &lhs, const String &rhs)
    {
        return strcmp(lhs._pstr,rhs._pstr) == 0;
    }
	bool operator!=(const String &lhs, const String &rhs)
    {
        return !(lhs==rhs);
    }
	bool operator<(const String &lhs, const String &rhs)
    {
        return strcmp(lhs._pstr , rhs._pstr) < 0;
    }
	bool operator>(const String &lhs, const String &rhs)
    {
        return strcmp(lhs._pstr , rhs._pstr) > 0;
    }
	bool operator<=(const String &lhs, const String &rhs)
    {
        return !(lhs > rhs);
    }
	bool operator>=(const String &lhs, const String &rhs)
    {
        return !(lhs < rhs);
    }
	std::ostream &operator<<(std::ostream &os, const String &s)
    {
        os << s._pstr;
        return os;
    }
    /* void readString(std::istream &is,String &s) */
    /* { */
    /*     char tmp[1024]; */
    /*     while(is >> s,!is.eof()) */
    /*     { */
    /*         if(is.bad()) */
    /*         { */
    /*             std::cerr << "Stream is bad!" << endl; */
    /*         } */
    /*         else if(is.fail()) */ 
    /*         { */
    /*             is.clear(); */
    /*             is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); */
    /*             cout << "The string is too long,pls input a correct string" << endl; */
    /*         } */
    /*         else */
    /*         { */
    /*             s= String(tmp); */
    /*             break; */
    /*         } */
    /*     } */
    /* } */
	std::istream &operator>>(std::istream &is, String &s)
    {
        /* is >> s._pstr; */
        /* readString(is,s); */
        char tmp[1024];
        is.getline(tmp,1024);
        s = String(tmp);
        return is;
    }
    String operator+(const String &lhs, const String &rhs)
    {
        size_t len1 = strlen(lhs._pstr);
        size_t len2 = strlen(rhs._pstr);
        char* newStr = new char[len1 + len2 + 1];
        strcpy(newStr , lhs._pstr);
        strcpy(newStr + len1,rhs._pstr);
        String tmp(newStr);
        delete[] newStr;
        return tmp;
    }
    String operator+(const String &lhs, const char *str)
    {
        size_t len1 = strlen(lhs._pstr);
        size_t len2 = strlen(str);
        char* newStr = new char[len1 + len2 +1];
        strcpy(newStr , lhs._pstr);
        strcpy(newStr + len1 , str);
        String tmp(newStr);
        delete [] newStr;
        return tmp;
    }
    String operator+(const char *str, const String &rhs)
    {
        size_t len1 = strlen(str);
        size_t len2 = strlen(rhs._pstr);
        char* newStr = new char[len1 + len2 + 1];
        strcpy(newStr , str);
        strcpy(newStr + len1 , rhs._pstr);
        String tmp(newStr);
        delete [] newStr;
        return tmp;
    }   
    int main()
    {
        String s1;
        String s2("Hello Wangdao!");
        String s3 = s2;  // 拷贝构造
        String s4;
        s4 = s2;  // 赋值操作符

        //测试size和c_str
        std::cout << "s1 size: " << s1.size() << ", c_str: " << s1.c_str() << std::endl;
        std::cout << "s2 size: " << s2.size() << ", c_str: " << s2.c_str() << std::endl;

        //测试拼接操作符
        s1 = s2 + " I love you!";
        std::cout << "s1 + s2 = " << s1 << std::endl;

        //测试+=操作符
        s2 += " upupup";
        std::cout << "s2 += str " << s2 << std::endl;

        //测试关系操作符
        std::cout << "s2 == s3: " << (s2 == s3) << std::endl;
        std::cout << "s2 != s3: " << (s2 != s3) << std::endl;
        std::cout << "s2 < s3: " << (s2 < s3) << std::endl;

        //测试输入输出流
        String s5;
        std::cout << "Pls enter a string: ";
        std::cin >> s5;
        std::cout << "String: " << s5 << std::endl;

        return 0;
    }

