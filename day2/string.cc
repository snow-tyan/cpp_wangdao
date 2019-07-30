#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class String
{
public:
    String();                          //默认构造函数
    String(const char *);              //构造函数
    String(const String &);            //拷贝构造函数
    String &operator=(const String &); //赋值构造函数
    String &operator=(const char *);
    ~String(); //析构函数
    void print() const;
    
private:
    char *_pstr; //私有数据成员
};

String::String()
    : _pstr(new char())
{
    strcpy(_pstr, "");
    cout << "String()" << endl;
}

String::String(const char *pstr)
    : _pstr(new char[strlen(pstr) + 1]())
{
    strcpy(_pstr, pstr);
    cout << "String(const char *)" << endl;
}

String::String(const String &rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]()) //深拷贝
{
    strcpy(_pstr, rhs._pstr);
    cout << "String(const String &)" << endl;
}

String &String::operator=(const String &rhs)
{
    if (this != &rhs)
    { //自复制
        cout << "Computer & operator=(const String &)" << endl;
        delete[] _pstr; //回收左操作申请的空间
        //再进行深拷贝
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}

String::~String()
{
    if (_pstr)
        delete[] _pstr;
    cout << "~String()" << endl;
}

inline void String::print() const
{
    cout << _pstr << endl;
}

void test0()
{
    String str1;
    cout << "str1=";
    str1.print();

    String str2 = "Hello,world";
    String str3("wangdao");

    cout << "str2=";
    str2.print();
    cout << "str3=";
    str3.print();

    String str4 = str3;
    cout << "str4=";
    str4.print();

    str4 = str2;
    cout << "str4=";
    str4.print();
}

int main(void)
{
    // test0();
    

    return 0;
}