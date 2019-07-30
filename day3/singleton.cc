#include <iostream>
using std::cout;
using std::endl;

class singleton
{
public:
    static singleton *getInstance()
    {
        if (nullptr == _pInstance)
            _pInstance = new singleton();
        return _pInstance;
    }

    static void destroy()
    {
        if (_pInstance)
            delete _pInstance;
    }

private:
    singleton() { cout << "singleton()" << endl; }
    ~singleton() { cout << "~singleton()" << endl; }

private:
    //数据成员
    static singleton *_pInstance;
};

singleton *singleton::_pInstance = nullptr; //静态数据成员在类外初始化

int main()
{
    singleton *s1 = singleton::getInstance();
    singleton *s2 = singleton::getInstance();
    singleton *s3 = singleton::getInstance();

    cout << "s1=" << s1 << endl
         << "s2=" << s2 << endl
         << "s3=" << s3 << endl;

    singleton::destroy();

    return 0;
}