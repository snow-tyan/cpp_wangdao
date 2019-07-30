#include "mystring.h"
#define DEBUG

String::String()
    : _pstr(new char())
{
    strcpy(_pstr, "");
    // cout << "String()" << endl;
}

String::String(const char *pstr)
    : _pstr(new char[strlen(pstr) + 1]())
{
    strcpy(_pstr, pstr);
    _back=strlen(pstr);
    // cout << "String(const char *)" << endl;
}

String::String(const String &rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]()) //深拷贝
{
    strcpy(_pstr, rhs._pstr);
    _back=strlen(rhs._pstr);
    // cout << "String(const String &)" << endl;
}

//从pstr开始向后复制count个字符
String::String(const char *pstr, size_type count)
    : _pstr(new char[count + 1]())
{
    strncpy(_pstr, pstr, count);
    _back=count;
}

//从下表idx开始向后复制的字符
String::String(const String &rhs, size_type idx)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
{
    if (!(strlen(rhs._pstr) < idx)) //合法的idx
    {
        strcpy(_pstr, rhs._pstr + idx);
        _back=strlen(rhs._pstr)-idx;
    }
#ifdef DEBUG
    else
    {
        cout<<"ERROR IDX"<<endl;
    }
#endif
}

String::String(const String &rhs, size_type idx, size_type len)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
{
    if (!(strlen(rhs._pstr) < idx)) //合法的idx
    {
        if((idx + len) <= strlen(rhs._pstr))//合法的长度
        {
            strncpy(_pstr, rhs._pstr + idx, len);
            _back=len;
        }
        else
        {
            strcpy(_pstr, rhs._pstr + idx);
            _back=strlen(rhs._pstr)-idx;
        }
    }
#ifdef DEBUG
    else
    {
        cout<<"ERROR IDX"<<endl;
    }
#endif
}

//赋值运算符=
String &String::operator=(const String &rhs)
{
    if (this != &rhs)
    { //自复制跳过此步
        // cout << "Computer & operator=(const String &)" << endl;
        delete[] _pstr; //回收左操作申请的空间
        //再进行深拷贝
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
        _back=strlen(rhs._pstr);
    }
    return *this;
}

String &operator=(const char *pstr)
{
    
}

//赋值count个ch
String &String::assign(size_type count, char ch)
{
    delete[] _pstr;
    _pstr = new char[count + 1]();
    for (size_type i = 0; i < count; ++i)
    {
        sprintf(_pstr, "%s%c", _pstr, ch);
        _back=count;
    }
    return *this;
}

String &String::assign(const String &rhs)
{
    if (this != &rhs)
    { //自复制跳过此步
        delete[] _pstr;
        _pstr=new char[strlen(rhs._pstr)+1]();
        strcpy(_pstr,rhs._pstr);
        _back=strlen(rhs._pstr);
    }
    return *this;
}

size_type String::size()
{
    return _back-_front;
}
size_type String::length()
{
    return _back-_front;
}

String::~String()
{
    if (_pstr)
        delete[] _pstr;
    // cout << "~String()" << endl;
}

void String::print() const
{
    cout << _pstr << endl;
}

//返回从pos开始count个长度字串
String String::substr(size_type pos, size_type count)
{
    if (count > size() - pos)
    {
        count = size() - pos;
    }
    if (pos <= size())
    {
        String str;
        str._pstr = new char[count + 1]();
        strncpy(str._pstr, _pstr + pos, count);
        str._back = count;
        return str;
    }
#ifdef DEBUG
    else
    {
        cout << "ERROR POS" << endl;
        exit(-1);
    }
#endif
}