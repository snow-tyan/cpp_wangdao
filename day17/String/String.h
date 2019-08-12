#pragma once
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

namespace mystring
{

class String
{
public:
    String();                          //默认构造函数
    String(const char *);              //构造函数
    //复制控制函数
    String(const String &);            //拷贝构造函数
    String &operator=(const String &); //赋值构造函数
    String &operator=(const char *);
    //移动控制函数，移动语义一定会修改，不能是const
    String(String &&);
    String &operator=(String &&);
    ~String(); //析构函数

    const void print() const;

    String &operator+=(const String &);
    String &operator+=(const char *);

    char &operator[](std::size_t index);//subscipt
    const char &operator[](std::size_t index) const;

    std::size_t size() const;//strlen
    const char *c_str() const;

    //logical operators' overload
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &);
    friend void ReadValidString(std::istream &is, String &);
    friend std::istream &operator>>(std::istream &is, String &);

private:
    char *_pstr; //私有数据成员
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

} // end of namespace mystring