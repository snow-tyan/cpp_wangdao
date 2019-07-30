#include "line.h"
using std::cout;
using std::endl;

namespace pimpl
{

class line::lineImpl //外部类
{
    class point //内部类，只为外部类服务
    {
    public:
        point(int ix, int iy)
            : _ix(ix), _iy(iy) { cout << "point(int, int)" << endl; }

        ~point() { cout << "~point()" << endl; }

        void print() const
        {
            cout << "(" << _ix << "," << _iy << ")";
        }

    private:
        int _ix = 0, _iy = 0;
    };

public:
    lineImpl(int x1, int y1, int x2, int y2)
        : _pt1(x1, y1), _pt2(x2, y2)
    {
        cout << "lineImpl(int, int, int, int)" << endl;
    }

    ~lineImpl() { cout << "~lineImpl()" << endl; }

    void printLine() const
    {
        _pt1.print();
        cout << " ---> ";
        _pt2.print();
        cout << endl;
    }

private:
    point _pt1, _pt2;
};

line::line(int x1, int y1, int x2, int y2)
    : _pImpl(new lineImpl(x1, y1, x2, y2))
{
    cout << "line(int, int, int, int)" << endl;
}

line::~line()
{
    if (_pImpl)
    {
        delete _pImpl;
    }
    cout << "~line()" << endl;
}

void line::printLine() const
{
    _pImpl->printLine();
}

} // namespace pimpl