#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::multiset;
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
    multiset<int> imultiset{1, 3, 5, 7, 7, 9, 9};
    display(imultiset);
}

void test2()
{
    int arr[] = {3, 6, 1, 2, 6, 5, 7, 9, 8, 3};
    multiset<int> imultiset(arr, arr + 10);
    display(imultiset);

    multiset<int>::iterator iter = imultiset.begin();
    cout << *iter << endl;

    imultiset.erase(iter);
    display(imultiset);
}

void test3()
{
    int arr[] = {3, 6, 1, 2, 6, 5, 7, 9, 8, 3};
    multiset<int> imultiset(arr, arr + 10);
    display(imultiset);

    auto ret = imultiset.insert(2);
    cout << "insert success!" << endl;
    cout << *ret << endl;

    ret = imultiset.insert(4);
    cout << "insert success!" << endl;
    cout << *ret << endl;

    //查找元素
    //1. count
    if (imultiset.count(10))
    {
        cout << "serch success!" << endl;
    }
    else
    {
        cout << "serch failed" << endl;
    }

    //2.find
    multiset<int>::iterator iter2 = imultiset.find(13);
    if (iter2 != imultiset.end())
    {
        cout << "serch success!" << endl;
        cout << *iter2 << endl;
    }
    else
    {
        cout << "serch failed" << endl;
    }

    //范围查找:
    //lowerbound 下边界 [
    auto lowerbound = imultiset.lower_bound(6);
    cout << "*lowerbound = " << *lowerbound << endl;
    //upperbound 上边界 )
    auto upperbound = imultiset.upper_bound(6);
    cout << "*upperbound = " << *upperbound << endl;
    while (lowerbound != upperbound)
    {
        cout << *lowerbound << " ";
        ++lowerbound;
    }
    cout << endl;
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
#if 1
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
    // multiset<Point> imultiset{
    multiset<Point, std::greater<Point>> imultiset{
        // multiset<Point,Comparator> imultiset{
        Point(1, 2),
        Point(2, 1),
        Point(2, 5),
        Point(-2, 10),
        Point(2, 2),
        Point(2, 2),
        Point(3, 2)};
    display(imultiset);

#if 1
    //查找元素:
    std::size_t cnt;
    if (cnt = imultiset.count(Point(2, -1)))
    {
        cout << "查找元素成功！" << cnt << endl;
    }
    else
    {
        cout << "multiset没有该元素" << endl;
    }

    auto it2 = imultiset.find(Point(2, -1));
    if (it2 == imultiset.end())
    {
        cout << "multiset没有该元素" << endl;
    }
    else
    {
        cout << "查找元素成功！" << endl;
        cout << "*it2 = " << *it2 << endl;
    }
#endif
}
#endif
int main()
{
    // test0();
    // test1();
    // test2();
    test3();
    // test4();
    // test5();

    return 0;
}