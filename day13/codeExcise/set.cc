#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

template <typename Container>
void display(const Container &c)
{
    typename Container::const_iterator cit = c.begin();
    while (cit != c.end())
    {
        cout << *cit << " ";
        ++cit;
    }
    cout << endl;
}

void test0()
{
    vector<int> ivec{1, 3, 5, 9, 7};
    display(ivec);
}

void test1()
{
    set<int> iset{1, 3, 5, 7, 9};
    display(iset);
}

void test2()
{
    int arr[] = {3, 6, 1, 2, 6, 5, 7, 9, 8, 3};
    set<int> iset(arr, arr + 10);
    display(iset);

    set<int>::iterator iter = iset.begin();
    cout << *iter << endl;

    iset.erase(iter);
    display(iset);
}

void test3()
{
    int arr[] = {3, 6, 1, 2, 6, 5, 7, 9, 8, 3};
    set<int> iset(arr, arr + 10);
    display(iset);

    std::pair<set<int>::iterator, bool> ret = iset.insert(2);
    // auto ret = iset.insert(2);
    if (ret.second)
    {
        cout << "insert success!" << endl;
        cout << *ret.first << endl;
    }
    else
    {
        cout << "insert failed" << endl;
        cout << *ret.first << endl;
    }

    ret = iset.insert(4);
    if (ret.second)
    {
        cout << "insert success!" << endl;
        cout << *ret.first << endl;
    }
    else
    {
        cout << "insert failed" << endl;
        cout << *ret.first << endl;
    }

    //查找元素
    //1. count
    if (iset.count(2))
    {
        cout << "serch success!" << endl;
    }
    else
    {
        cout << "serch failed" << endl;
    }

    //2.find
    set<int>::iterator iter2 = iset.find(3);
    if (iter2 != iset.end())
    {
        cout << "serch success!" << endl;
        cout << *iter2 << endl;
    }
    else
    {
        cout << "serch failed" << endl;
    }
}

void test4()
{
    std::pair<int, string> p1(1, "ShenZhen");
    auto p2 = std::make_pair(2, "GuangZhou");
    auto p3(std::make_pair(3, "BeiJing"));
    cout << p1.first << " --> " << p1.second << endl;
    cout << p2.first << " --> " << p2.second << endl;
    cout << p3.first << " --> " << p3.second << endl;
}

class Point
{
public:
    Point(int ix, int iy)
        : _ix(ix), _iy(iy)
    {
        // cout << "Point(int,int)" << endl;
    }

    double getDistance() const
    {
        return sqrt(_ix * _ix + _iy * _iy);
    }
    //输出流
    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);

private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    return os << "(" << rhs._ix
              << "," << rhs._iy
              << ")";
}
#if 1
bool operator<(const Point &lhs, const Point &rhs)
{
    return lhs.getDistance() < rhs.getDistance();
}
#endif
#if 1
bool operator>(const Point &lhs, const Point &rhs)
{
    return lhs.getDistance() > rhs.getDistance();
}
#endif
//比较规则
struct Comparator
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        return lhs.getDistance() > rhs.getDistance();
    }
};

void test5()
{
    // set<Point> iset{
    set<Point, std::greater<Point>> iset{
        // set<Point,Comparator> iset{
        Point(1, 2),
        Point(2, 1),
        Point(2, 5),
        Point(-2, 10),
        Point(2, 2),
        Point(2, 2),
        Point(3, 2)};
    display(iset);

#if 1
    //查找元素:
    if (iset.count(Point(11, 12)))
    {
        cout << "查找元素成功！" << endl;
    }
    else
    {
        cout << "set没有该元素" << endl;
    }

    auto it2 = iset.find(Point(10, 2));
    if (it2 == iset.end())
    {
        cout << "set没有该元素" << endl;
    }
    else
    {
        cout << "查找元素成功！" << endl;
        cout << "*it2 = " << *it2 << endl;
    }
#endif
}

int main()
{
    // test0();
    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}