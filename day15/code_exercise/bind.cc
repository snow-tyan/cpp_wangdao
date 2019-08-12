#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream_iterator;
using namespace std::placeholders; //提供占位符 _1, _2 ...
#if 0
bool isShorter(const string &lhs, const string &rhs)
{
    return lhs.size() < rhs.size();
}

void test0()
{
    vector<string> words = {"hello", "world", "how", "are", "u", "hi_india_mi_fans", "ARE_U_OK?", "I_am_fine_thanks"};
    std::copy(words.begin(), words.end(), ostream_iterator<string>(cout, "   "));
    cout<<endl;

    std::sort(words.begin(),words.end(),isShorter);
    std::copy(words.begin(), words.end(), ostream_iterator<string>(cout, "   "));
    cout<<endl;

    std::sort(words.begin(),words.end(),std::bind(isShorter,_2,_1));
    std::copy(words.begin(), words.end(), ostream_iterator<string>(cout, "   "));
    cout<<endl;
}

void printTest(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
 
int g(int n1)
{
    return n1;
}
 
struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};
 
void test1()
{
    // 演示参数重排序和按引用传递
    int n = 7;
    // （ _1 与 _2 来自 std::placeholders ，并表示将来会传递给 f1 的参数）
    auto f1 = std::bind(printTest, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001); // 1 为 _1 所绑定， 2 为 _2 所绑定，不使用 1001
                    // 进行到 printTest(2, 42, 1, n, 7) 的调用
 
    // 嵌套 bind 子表达式共享占位符
    auto f2 = std::bind(printTest, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12); // 进行到 printTest(12, g(12), 12, 4, 5); 的调用
 
    // 绑定指向成员函数指针
    Foo foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);
 
    // 绑定指向数据成员指针
    auto f4 = std::bind(&Foo::data, _1);
    std::cout << f4(foo) << '\n';
}
#endif
void display()
{
	cout << "dispaly()" << endl;
}

void print()
{
	cout << "print()" << endl;
}

//函数类型
typedef void(*Function)();

class Example
{
public:
	Example()=default;

	void display()
	{
		cout << "Example::display()" << endl;
	}

	int add(int x, int y)
	{
		return x + y;
	}

	int _data = 10;
};
 
int test2(void)
{
	void(*f)() = display;
	f();
	
	f = print;
	f();

	return 0;
}

void test3()
{
	//f称为回调函数
	Function f = display;// 注册回调函数
	f();//执行回调函数

	f = print;
	f();
}

void test4()
{
	//函数类型的容器 ,function是类模板
	std::function<void()> f{display};
	f();

	f = print;
	f();

	Example e;
	//bind是函数模板, 其返回值是函数对象
	f = std::bind(&Example::display, e);//display是无参函数
    //但是Example::display隐含一个参数this指针，使用bind需传递一个对象。

	f();
}

int add(int x, int y)
{
    cout << "x = " << x << "  "
         << "y = " << y << endl;
    return x + y;
}

void test5()
{
	auto f = std::bind(add, 1, 2);
	cout << " f() = " << f() << endl;
	cout << " f(2, 3, 4) = " << f(2, 3, 4) << endl;//无效参数

	//占位符
	using namespace std::placeholders;
	auto f2 = std::bind(add, 1, _1);
	cout << "f2(100) = " << f2(100) << endl;

	auto f3 = std::bind(add, _1, 10);
	cout << "f3(100) = " << f3(100) << endl;

	Example e;
	//对于成员函数而言，绑定时, this指针所在的位置可以
	//传递地址，也可以传递对象本身
	//
	//如果使用地址传递，当函数被调用时，要确保对象生命周期还存在
	//如果对象的生命周期已经结束，再调用函数时有可能会出问题
	auto f4 = std::bind(&Example::add, &e, _1, _2);
	cout << "f4(11, 12) = " << f4(11, 12) << endl;

	auto f5 = std::bind(&Example::add, &e, 10, 20);
	cout << "f5() = " << f5() << endl;

	cout << "e._data = " << e._data << endl;
	auto f6 = std::bind(&Example::_data,&e);
	cout << "f6() = " << f6() << endl << endl;

	auto f7 = std::bind(&Example::add, e, _1, _2);
	cout << "f7(11, 12) = " << f7(11, 12) << endl;
}

void func(int x1, int x2, int x3, int & x4)
{
	cout << "(" << x1 
		 << ", " << x2 
		 << ", " << x3 
		 << ", " << x4 
		 << ")" << endl;
}

void test6()
{
	using namespace std::placeholders;
	int a = 10;
	//std::ref 引用的包装器
	//
	//占位符本身所在的位置代表形参对应的位置,
	//占位符的数字代表的是实参的位置
	auto f = std::bind(func, _3, _4, a, std::ref(a));
	a = 20;

	f(11, 22, 33, 44);
}

int main()
{
    // test0();
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}