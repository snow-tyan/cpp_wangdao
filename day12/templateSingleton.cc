#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class Singleton
{
    class AutoRelease
    {
    public:
        AutoRelease() { cout<<"AutoRelease()"<<endl; }
        ~AutoRelease()
        {
            if (_pInstance)
                delete _pInstance;
            cout << "~AutoRelease()" << endl;
        }
    };

public:
    template <typename... Args>
    static T *getInstance(Args... args)
    {
        if (!_pInstance)
        {
            _auto;
            _pInstance = new T(args...);
        }
        return _pInstance;
    }

    static void destory()
    {
        if (_pInstance)
        {
            delete _pInstance;
        }
    }

private:
    Singleton() {}
    ~Singleton() {}

private:
    static T *_pInstance;
    static AutoRelease _auto;
};

template <typename T>
T *Singleton<T>::_pInstance = nullptr;

template <typename T>
typename Singleton<T>::AutoRelease Singleton<T>::_auto;

class Point
{
public:
    Point(int ix, int iy) : _ix(ix), _iy(iy) {}

    ~Point() {}

private:
    int _ix;
    int _iy;
};

int main()
{
    Point *pt1 = Singleton<Point>::getInstance(1, 2);
    Point *pt2 = Singleton<Point>::getInstance(1, 2);
    cout << pt1 << endl
         << pt2 << endl;

    return 0;
}