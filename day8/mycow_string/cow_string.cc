#include <cstdio>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class CowString
{
    class Cowchar
    {
    public:
        Cowchar(CowString &cowString, size_t idx)
            : _cowString(cowString), _idx(idx)
        {
            // cout<<"Cowchar(CowString &, size_t)"<<endl;
        }

        char &operator=(const char &ch);
        operator char() { return _cowString._pstr[_idx]; }

    private:
        CowString &_cowString;
        size_t _idx;
    };

public:
    CowString()
        : _pstr(new char[1 + 4]() + 4)
    {
        initRefcount();
        cout << "CowString()" << endl;
    }

    CowString(const char *pstr)
        : _pstr(new char[strlen(pstr) + 5]() + 4)
    {
        cout << "CowString(const char *)" << endl;
        initRefcount();
        strcpy(_pstr, pstr);
    }

    CowString(const CowString &rhs)
        : _pstr(rhs._pstr)
    { //O(1)时间复杂度
        cout << "CowString(const CowString & )" << endl;
        increaseRefcount();
    }

    CowString &operator=(const CowString &rhs)
    {
        cout << "CowString & operator=(const CowString &)" << endl;
        if (this != &rhs)
        {
            release();
            _pstr = rhs._pstr;
            increaseRefcount();
        }
        return *this;
    }

    const char *c_str() const { return _pstr; }

    size_t size() const { return strlen(_pstr); }

    ~CowString() { release(); }

    int refcount() const { return *(int *)(_pstr - 4); }

    // char &operator[](int idx);
    Cowchar operator[](size_t idx);

#if 1
    const char &operator[](size_t idx) const
    {
        cout << "const char & operator[](int idx) const" << endl;
        return _pstr[idx];
    }
#endif

    friend std::ostream &operator<<(std::ostream &os, const CowString &rhs);

private:
    void initRefcount() { *(int *)(_pstr - 4) = 1; }

    void increaseRefcount() { ++*(int *)(_pstr - 4); }

    void decreaseRefcount() { --*(int *)(_pstr - 4); }

    void release()
    {
        decreaseRefcount();
        if (0 == refcount())
        {
            delete[](_pstr - 4);
            cout << ">> delete heap data!" << endl;
        }
    }

private:
    char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const CowString &rhs)
{
    return os << rhs._pstr;
}

//只要字符串的引用计数大于1， 就会进行深拷贝
//
//问题：下标访问运算符无法区分出接下来的操作是读操作还是写操作
//
//解决方法：不使用下标运算符进行区分读写，而是用赋值运算符区分读写操作

CowString::Cowchar CowString::operator[](size_t idx)
{
    return Cowchar(*this, idx);
}

char &CowString::Cowchar::operator=(const char &ch)
{
    if (_idx < _cowString.size())
    {
        if (_cowString.refcount() > 1)
        {
            _cowString.decreaseRefcount();
            char *ptmp = new char[_cowString.size() + 5]() + 4;
            strcpy(ptmp, _cowString._pstr);
            ptmp[_idx] = ch;
            _cowString._pstr = ptmp;
            _cowString.initRefcount();
        }
        return _cowString._pstr[_idx];
    }
    else
    {
        static char nullchar = '\0';
        return nullchar;
    }
}

void func(const CowString &str)
{
    cout << str[0] << endl;
}

int main(void)
{
    CowString s1 = "hello,world";

    //CowString s2 = "hello,world";
    CowString s2 = s1;

    CowString s3 = "shenzhen";
    cout << "s3 = " << s3 << endl;
    s3 = s1;

    cout << "执行赋值操作之后:" << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refcount = " << s1.refcount() << endl;
    cout << "s2's refcount = " << s2.refcount() << endl;
    cout << "s3's refcount = " << s3.refcount() << endl;

    cout << "\n 修改共享字符串的内容之后:" << endl;
    s3[0] = 'X';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refcount = " << s1.refcount() << endl;
    cout << "s2's refcount = " << s2.refcount() << endl;
    cout << "s3's refcount = " << s3.refcount() << endl;

    cout << "\n 执行读操作之后:" << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refcount = " << s1.refcount() << endl;
    cout << "s2's refcount = " << s2.refcount() << endl;
    cout << "s3's refcount = " << s3.refcount() << endl;

    return 0;
}
