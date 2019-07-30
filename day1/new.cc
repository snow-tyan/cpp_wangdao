#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;

int fun1()
{
    int temp=1;
    return temp;
}

int & fun2()
{
    int temp=3;
    return temp;//返回局部变量的引用
}

int & fun3()
{
    int *pint=new int(1);
    return *pint;//返回堆空间变量的引用
}

int test()
{
    int a=10,b=20;
    int c=a+fun3()+b;
    cout<<"c= "<<c<<endl;
    return 0;
}

int main()
{
    test();
    return 0;
}
