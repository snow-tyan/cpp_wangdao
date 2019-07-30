//方法一：嵌套类 + 静态成员
#include <iostream>
using std::cout;
using std::endl;

class singleton
{
    class autoRelease
    {
    public:
        autoRelease()
        {
            cout << "autoRelease()" << endl;
        }
        ~autoRelease()
        {
            cout << "~autoRelease()" << endl;
            if (_pInstance)//_pInstance是static的，可以直接拿到
            //若不是static,需要通过传一个singleton的引用拿到_pInstance
            {
                delete _pInstance;
            }
        }
    };

public:
    static singleton *getInstance()
    {
        if (nullptr == _pInstance)
        {
            _pInstance = new singleton();
        }
        return _pInstance;
    }
#if 0
    static void destroy()
    {
        if (_pInstance)
        {
            delete _pInstance;
        }
    }
#endif

private:
    singleton() { cout << "singleton()" << endl; }
    ~singleton() { cout << "~singleton()" << endl; }

private:
    //数据成员
    static singleton *_pInstance;
    static autoRelease _autoRelease;//若不是static,singleton类结束就销毁
};

// singleton *singleton::_pInstance = nullptr; //静态数据成员在类外初始化

singleton *singleton::_pInstance = getInstance(); //饿汉模式
singleton::autoRelease singleton::_autoRelease;

int main()
{
    singleton *s1 = singleton::getInstance();
    singleton *s2 = singleton::getInstance();
    singleton *s3 = singleton::getInstance();

    cout << "s1=" << s1 << endl
         << "s2=" << s2 << endl
         << "s3=" << s3 << endl;

    // singleton::destroy();

    return 0;
}