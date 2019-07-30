#pragma once
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
typedef std::size_t size_type;
static const size_type npos = -1;

class String
{
public:
    String();                  //默认构造函数
    String(const char *pstr);  //构造函数
    String(const String &rhs); //拷贝构造函数
    //extra String constructor
    String(const char *pstr, size_type count);
    String(const String &rhs, size_type idx);
    String(const String &rhs, size_type idx, size_type len);

    String &operator=(const String &rhs); //赋值构造函数
    String &operator=(const char *pstr);

    String substr(size_type pos = 0, size_type count = npos);
    String &assign(size_type count, char ch); //赋值
    String &assign(const String &rhs);        //拷贝赋值

    size_type size(); //长度
    size_type length();

    ~String(); //析构函数

    void print() const;

private:
    //私有数据成员
    char *_pstr;
    size_type _front = 0, _back = 0;
};