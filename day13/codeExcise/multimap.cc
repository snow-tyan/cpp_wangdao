#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::multimap;
using std::string;
using std::vector;
using std::pair;

template <typename Container>
void display(const Container &c)
{
    typename Container::const_iterator cit = c.begin();
    while (cit != c.end())
    {
        cout << cit->first << " ---> " << cit->second << endl;
        ++cit;
    }
}

void test0()
{
    multimap<int, string> imultimap;
    imultimap.insert(pair<int, string>(1,"BeiJing"));
    imultimap.insert(std::make_pair(2,"ShangHai"));
    imultimap.insert(std::make_pair(2,"GuangZhou"));
    imultimap.insert(std::make_pair(4,"ShenZhen"));
    display(imultimap);
}

void test1()
{
    multimap<int, string> imultimap{
		std::make_pair(4, "ShenZhen"),
		pair<int, string>(1, "BeiJing"),
		std::make_pair(2, "ShangHai"),
		std::make_pair(2, "GuangZhou"),
	};
    display(imultimap);

    auto ret = imultimap.insert(std::make_pair(3, "GuangZhou"));
    cout << ret->first << " ---> " << ret->second << endl;

    display(imultimap);
    cout<<"--------------------"<<endl;
    auto iter=imultimap.begin();
    cout<<iter->first<<" ---> "<<iter->second<<endl;
    iter = imultimap.insert(iter,std::make_pair(5,"WuHan"));
    cout<<iter->first<<" ---> "<<iter->second<<endl;
    display(imultimap);
    cout<<"----After insert----"<<endl;

    vector<pair<int, string>> ivec{
        std::make_pair(14, "深圳"),
		pair<int, string>(11, "北京"),
		std::make_pair(12, "上海"),
		std::make_pair(12, "广州")
    };
    imultimap.insert(ivec.begin(),ivec.end());
    display(imultimap);
    cout<<"-----After erase-----"<<endl;
    imultimap.erase(12);
    display(imultimap);
}
#if 1
void test2()
{
    multimap<string, string> imultimap{
        std::make_pair("0755", "ShenZhen"),
		pair<string, string>("010", "BeiJing"),
		std::make_pair("021", "ShangHai"),
		std::make_pair("020", "GuangZhou"),
    };
    display(imultimap);

    //查找
    multimap<string, string>::iterator iter=imultimap.find("121");//失败返回尾后迭代器
    if(iter!=imultimap.end())
    {
        cout<<"serch success!"<<endl;
        cout<<iter->first<<" ---> "<<iter->second<<endl;
    }
    else
    {
        cout<<"serch failed"<<endl;
    }
    display(imultimap);

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

void test3()
{
	//multimap<Point, int, std::greater<Point>> points =
	multimap<Point, int, Comparator> points =
	{
        std::make_pair(Point(2, 2), 3),
		std::make_pair(Point(1, 2), 1),
		std::make_pair(Point(2, 2), 1),
		std::make_pair(Point(3, 2), 1),
		std::make_pair(Point(4, 2), 1),
        std::make_pair(Point(2, 2), 2),
        
	};

	// display(points);
    auto ret = points.equal_range(Point(2, 2));
    while(ret.first != ret.second) {
		cout << ret.first->first << " ---> "<<ret.first->second<<endl;
		++ret.first;
	}
}
#endif
#endif
int main()
{
    // test0();
    // test1();
    // test2();
    test3();

    return 0;
}