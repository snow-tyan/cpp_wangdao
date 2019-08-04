//纯虚函数的申明和定义
#include <iostream> 
using namespace std;

class A						//类A定义
{
public:
	virtual void disp() = 0;//纯虚函数，类A作为抽象类
};

class B:public A			//B由抽象类A派生而来
{
public:
	virtual void disp()		//此处virtual可省略，继承
	{
		cout << "This is from B" << endl;
	}
};

class C: public B			//类C从类B派生而来
{
public:
	virtual void disp()
	{
		cout << "This is from C" << endl;
	}
};

void display(A *a)			//display函数，以A类指针对参数
{
	a->disp();
}

int main()
{
	B *pB = new B;				//正确。但如果删除B类中disp()的定义就会编译出错, 因为删除后，B就还包含纯虚函数。
	C *pC = new C;			//正确。如果删除C类中的disp()的定义，但保留B中的定义，依然正确，因为B中的disp()不是纯虚函数了
							//但如果B, C类中都没有disp()的定义，就会编译出错，因为C还是纯虚函数。

	display(pB);			//取决于为指针赋值的数据类型
	display(pC);

	return 0;
}
