#include "String.h"

namespace mystring
{

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
        cout << "String & operator=(const String &)" << endl;
        delete[] _pstr; //回收左操作申请的空间
        //再进行深拷贝
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}

String &String::operator=(const char *pstr)
{
    cout << "String & operator=(const char *)" << endl;
    _pstr = new char[strlen(pstr) + 1]();
    strcpy(_pstr, pstr);
    return *this;
}

String::String(String &&rhs)
    : _pstr(rhs._pstr)
{
    rhs._pstr = nullptr;
    cout << "String(const String &&)" << endl;
}

String &String::operator=(String &&rhs)
{
    if (this != &rhs)
    {//自复制
        delete [] _pstr;//回收左操作申请的空间
        _pstr = rhs._pstr;
        rhs._pstr = nullptr;
    }
    cout << "String &operator=(String &&)" << endl;
    return *this;
}

String::~String()
{
    if (_pstr)
        delete[] _pstr;
    cout << "~String()" << endl;
}

const void String::print() const
{
    cout << _pstr << endl;
}

String &String::operator+=(const String &rhs)
{
    strcat(_pstr, rhs._pstr);
    return *this;
}
String &String::operator+=(const char *pstr)
{
    strcat(_pstr, pstr);
    return *this;
}

char &String::operator[](std::size_t index)
{
    // cout<<"char &operator[](std::size_t)"<<endl;
    if (index < size())
    {
        return _pstr[index];
    }
    else
    {
        static char nullchar = '\0';
        return nullchar;
    }
}
const char &String::operator[](std::size_t index) const
{
    // cout<<"const char &operator[](std::size_t) const"<<endl;
    return _pstr[index];
}

std::size_t String::size() const
{
    return strlen(_pstr);
}
const char *String::c_str() const
{
    return _pstr;
}

bool operator==(const String &lhs, const String &rhs)
{
    return !strcmp(lhs._pstr, rhs._pstr) ? true : false;
}
bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs)
{
    return (strcmp(lhs._pstr, rhs._pstr) < 0) ? true : false;
}
bool operator>(const String &lhs, const String &rhs)
{
    return (strcmp(lhs._pstr, rhs._pstr) > 0) ? true : false;
}
bool operator<=(const String &lhs, const String &rhs)
{
    return (strcmp(lhs._pstr, rhs._pstr) <= 0) ? true : false;
}
bool operator>=(const String &lhs, const String &rhs)
{
    return (strcmp(lhs._pstr, rhs._pstr) >= 0) ? true : false;
}

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    return os << rhs._pstr;
}

void ReadValidString(std::istream &is, String &rhs)
{
    vector<char> vec;
    char ch;
    while (is >> ch)
    {
        if (is.good())
        {
            vec.push_back(ch);
        }
        else if (is.bad())
        {
            cout << "istream has corrupted!" << endl;
            return;
        }
        else if (is.fail())
        {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "is.fail()" << endl;
            continue;
        }
    }
    if (rhs._pstr)
    {
        delete[] rhs._pstr;
    }
    rhs._pstr = new char[vec.size() + 1]();
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        cout << *iter;
        sprintf(rhs._pstr, "%s%c", rhs._pstr, *iter);
    }
    cout << endl;
}
std::istream &operator>>(std::istream &is, String &rhs)
{
    ReadValidString(is, rhs);
    return is;
}

String operator+(const String &lhs, const String &rhs)
{
    String newString = lhs; //String对象，析构函数回收
    newString += rhs;
    return newString;
}
String operator+(const String &lhs, const char *pstr)
{
    String newString = lhs;
    newString += pstr;
    return newString;
}
String operator+(const char *pstr, const String &rhs)
{
    String newString = pstr;
    newString += rhs;
    return newString;
}

} // end of namespace mystring