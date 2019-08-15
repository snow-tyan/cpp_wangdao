#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

class Point
{
public:
    Point(int ix = 0, int iy = 0)
        : _ix(ix), _iy(iy)
    {
        cout << "Point(int,int)" << endl;
    }

    void print() const
    {
        cout << "(" << _ix
             << "," << _iy
             << ")" << endl;
    }

    ~Point() { cout << "~Point()" << endl; }

private:
    int _ix;
    int _iy;
};

void test0()
{
    shared_ptr<Point> sp(new Point(1, 2));
    cout << "sp' use_count = " << sp.use_count() << endl;
    cout << "*sp = ";
    sp->print();
    
    sp.reset(new Point(1, 3));
    cout << "sp' use_count = " << sp.use_count() << endl;
    cout << "*sp = ";
    sp->print();
}

int main(void)
{
    test0();

    return 0;
}
