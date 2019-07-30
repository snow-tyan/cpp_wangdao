//方法二：静态成员函数+atexit
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

class singleton
{
public:
    static singleton *getInstance()
    {
        if (nullptr == _pInstance)
        {
            atexit(destory); //程序执行结束会调用destory从而delete掉_pInstance
            _pInstance = new singleton();
        }
        return _pInstance;
    }

    static void destory()
    {
        if (_pInstance)
            delete _pInstance;
    }

private:
    singleton() { cout << "singleton()" << endl; }
    ~singleton() { cout << "~singleton()" << endl; }

private:
    static singleton *_pInstance;
};

singleton *singleton::_pInstance = getInstance(); //饿汉模式

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