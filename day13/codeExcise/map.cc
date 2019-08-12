#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::map;
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
    map<int, string> imap;
    imap.insert(pair<int, string>(1,"BeiJing"));
    imap.insert(std::make_pair(2,"ShangHai"));
    imap.insert(std::make_pair(3,"GuangZhou"));
    imap.insert(std::make_pair(4,"ShenZhen"));
    display(imap);
}

void test1()
{
    map<int, string> imap{
		std::make_pair(4, "ShenZhen"),
		pair<int, string>(1, "BeiJing"),
		std::make_pair(2, "ShangHai"),
		std::make_pair(2, "GuangZhou"),
	};
    display(imap);

    pair<map<int, string>::iterator,bool> ret
        = imap.insert(std::make_pair(3,"GuangZhou"));
    if(ret.second)
    {
        cout<<"map insert success!"<<endl;
        cout<<ret.first->first<<" ---> "<<ret.first->second<<endl;
    }
    else
    {
        cout<<"map insert failed"<<endl;
    }
    display(imap);
    cout<<"--------------------"<<endl;
    auto iter=imap.begin();
    cout<<iter->first<<" ---> "<<iter->second<<endl;
    iter = imap.insert(iter,std::make_pair(5,"WuHan"));
    cout<<iter->first<<" ---> "<<iter->second<<endl;
    display(imap);
    cout<<"----After insert----"<<endl;

    vector<pair<int, string>> ivec{
        std::make_pair(14, "深圳"),
		pair<int, string>(11, "北京"),
		std::make_pair(12, "上海"),
		std::make_pair(12, "广州")
    };
    imap.insert(ivec.begin(),ivec.end());
    display(imap);
    cout<<"-----After erase-----"<<endl;
    imap.erase(12);
    display(imap);
    cout<<"-----After modify-----"<<endl;
    imap[11]="NanJing";//modify
    imap[14]="HangZhou";//modify
    imap[12]="Hefei";//创建新元素
    display(imap);
}

void test2()
{
    map<string, string> imap{
        std::make_pair("0755", "ShenZhen"),
		pair<string, string>("010", "BeiJing"),
		std::make_pair("021", "ShangHai"),
		std::make_pair("020", "GuangZhou"),
    };
    display(imap);

    //查找
    map<string, string>::iterator iter=imap.find("121");//失败返回尾后迭代器
    if(iter!=imap.end())
    {
        cout<<"serch success!"<<endl;
        cout<<iter->first<<" ---> "<<iter->second<<endl;
    }
    else
    {
        cout<<"serch failed"<<endl;
    }
    display(imap);
    cout<<"访问一个不存在的key"<<endl;
    imap["121"];
    display(imap);


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
	//map<Point, int, std::greater<Point>> points =
	map<Point, int, Comparator> points =
	{
		std::make_pair(Point(1, 2), 1),
		std::make_pair(Point(2, 2), 1),
		std::make_pair(Point(3, 2), 1),
		std::make_pair(Point(4, 2), 1),
	};

	display(points);
}
#endif
int main()
{
    // test0();
    // test1();
    // test2();
    test3();

    return 0;
}