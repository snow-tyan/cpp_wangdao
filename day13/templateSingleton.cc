#include <iostream>
using std::cout;
using std::endl;

template <typename... Args>
class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(!_pInstance)
        {
            _pInstance=new Singleton();
        }
        return _pInstance;
    }

    static void destory()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }

private:
    Singleton(){}
    ~Singleton(){}

private:
    static Singleton * _pInstance;
};

template <typename... Args>
Singleton * Singleton<Args>::_pInstance=nullptr;

int main()
{


    printf("s1 = %p\n",s1);
    printf("s2 = %p\n",s2);
    printf("s3 = %p\n",s3);

    return 0;
}