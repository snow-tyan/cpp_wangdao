//方法二：静态成员函数+atexit
#include <cstdlib>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

class singleton
{
public:
    static singleton *getInstance()
    {
        pthread_once(&_pOnce, init);
        return _pInstance;
    }

    static void init()
    {
        atexit(destory);
        _pInstance = new singleton();
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
    static pthread_once_t _pOnce;
};

singleton *singleton::_pInstance = nullptr; //懒汉模式
pthread_once_t singleton::_pOnce = PTHREAD_ONCE_INIT;

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