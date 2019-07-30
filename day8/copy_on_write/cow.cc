//copy on write
//add refCount before each string
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
        //Cowchar->char 类型转换
        operator char() { return _cowString._pstr[_idx]; }

    private:
        CowString &_cowString;
        size_t _idx;
    };

public:
    CowString();                             //默认构造函数
    CowString(const char *);                 //构造函数
    CowString(const CowString &);            //拷贝构造函数
    CowString &operator=(const CowString &); //赋值构造函数
    ~CowString();                            //析构函数

    const void print() const { cout << _pstr << endl; }
    const char *c_str() const { return _pstr; }
    size_t size() const { return strlen(_pstr); }
    int refCount() { return *(int *)(_pstr - 4); }

    friend std::ostream &operator<<(std::ostream &os, const CowString &rhs);
    const char &operator[](size_t idx) const;
    Cowchar operator[](size_t idx);

private:
    void initRefCount() { *(int *)(_pstr - 4) = 1; }

    void increaseRefCount() { ++*(int *)(_pstr - 4); }

    void decreaseRefCount() { --*(int *)(_pstr - 4); }

private:
    char *_pstr;
};

CowString::CowString()
    : _pstr(new char[1 + 4]() + 4) //加上一个int型的引用计数，后面的+4是偏移到_pstr的首地址
{
    // *(int*)(_pstr-4)=1;//对引用计数赋为1
    initRefCount();
    // _pstr='\0';
    cout << "CowString()" << endl;
}

CowString::CowString(const char *pstr)
    : _pstr(new char[strlen(pstr) + 5]() + 4)
{
    initRefCount();
    strcpy(_pstr, pstr);
    cout << "CowString(const char *)" << endl;
}

CowString::CowString(const CowString &rhs)
    : _pstr(rhs._pstr) //浅拷贝，只拷贝地址
{
    increaseRefCount();
    cout << "CowString(const CowString &)" << endl;
}

CowString &CowString::operator=(const CowString &rhs)
{
    if (this != &rhs)
    { //自复制
        decreaseRefCount();
        if (0 == refCount())
        {
            delete[](_pstr - 4); //回收左操作数申请的空间
        }
        //浅拷贝
        _pstr = rhs._pstr;  //_pstr已经指向新的字符串，引用计数也是新字符串的
        increaseRefCount(); //++refCount
    }
    cout << "CowString & operator=(const CowString &)" << endl;
    return *this;
}

CowString::~CowString()
{
    decreaseRefCount();
    if (0 == refCount())
    {
        delete[](_pstr - 4); //回收左操作申请的空间
        cout << "~CowString()" << endl;
    }
}

std::ostream &operator<<(std::ostream &os, const CowString &rhs)
{
    return os << rhs._pstr;
}

const char &CowString::operator[](size_t idx) const
{
    cout << "const char & operator[](int idx) const" << endl;
    return _pstr[idx];
}

CowString::Cowchar CowString::operator[](size_t idx)
{
    return Cowchar(*this, idx);
}

char &CowString::Cowchar::operator=(const char &ch)
{
    if (_idx < _cowString.size())
    {
        if (_cowString.refCount() > 1)
        {
            _cowString.decreaseRefCount();
            char *ptmp = new char[_cowString.size() + 5]() + 4;
            strcpy(ptmp, _cowString._pstr);
            ptmp[_idx] = ch;
            _cowString._pstr = ptmp;
            _cowString.initRefCount();
        }
        return _cowString._pstr[_idx];
    }
    else
    {
        static char nullchar = '\0';
        return nullchar;
    }
}

void test0()
{
    CowString s1("helloworld");
    cout << "s1 = ";
    s1.print();
    // CowString s2="helloworld";
    CowString s2(s1);
    cout << "s2 = ";
    s2.print();

    printf("s1. addr=%p\n", s1.c_str());
    printf("s2. addr=%p\n", s2.c_str());

    cout << "s1 refcnt = " << s1.refCount() << endl;
    cout << "s2 refcnt = " << s2.refCount() << endl;

    cout << "sizeof(s1) = " << sizeof(s1) << endl; //一个指针的大小
    cout << "s1.size() = " << s1.size() << endl;   //字符串的长度
}
#if 1
void test1()
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
    cout << "s1's refCount = " << s1.refCount() << endl;
    cout << "s2's refCount = " << s2.refCount() << endl;
    cout << "s3's refCount = " << s3.refCount() << endl;

    cout << "\n 修改共享字符串的内容之后:" << endl;
    s3[0] = 'X';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refCount = " << s1.refCount() << endl;
    cout << "s2's refCount = " << s2.refCount() << endl;
    cout << "s3's refCount = " << s3.refCount() << endl;

    cout << "\n 执行读操作之后:" << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refCount = " << s1.refCount() << endl;
    cout << "s2's refCount = " << s2.refCount() << endl;
    cout << "s3's refCount = " << s3.refCount() << endl;
}
#endif

void test2()
{
    CowString s1 = "hello";
    cout << "s1 = " << s1 << endl;
    cout << "s1 refcnt = " << s1.refCount() << endl;

    CowString s2(s1);

    cout << "s1 = " << s1 << endl;
    cout << "s1 refcnt = " << s1.refCount() << endl;

    CowString s3("how are you");
    s2 = s3;
    s1 = s3;

    cout << "s1 = " << s1 << endl;
    cout << "s1 refcnt = " << s1.refCount() << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s3 refcnt = " << s3.refCount() << endl;
}

int main()
{
    // test0();
    test1();
    // test2();
    return 0;
}