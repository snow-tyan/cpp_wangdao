#include "String.h"
using namespace mystring;

void test0()
{
    String s1("Hello");
    cout<<"s1=";
    s1.print();
    String s2("World!");
    String s3=" ";

    s1+=s3;
    s1+=s2;
    cout<<"s1=";
    s1.print();
    cout<<"s1.size()="<<s1.size()<<endl;
    cout<<s1.c_str()<<endl;

    s1[0]='h';
    s1[6]='w';
    cout<<"s1=";
    s1.print();

    for(int i=0;i!=s1.size();++i)
    {
        cout<<s1[i]<<" ";
    }
    cout<<endl;
}

void test1()
{
    const String s1("hello");
    String s2(s1);

    cout<<((s1==s2)?"s1 == s2":"s1 != s2")<<endl;
    cout<<"After modify"<<endl;
    s2[0] -= 32;
    cout<<"s1 = ";
    s1.print();
    cout<<"s2 = ";
    s2.print();
    if (s1 > s2)
    {
        cout << "s1 > s2" << endl;
    }
    else
    {
        cout << "s1 <= s2" << endl;
    }

}

void test2()
{
    String s1;
    std::cin >> s1;
    cout<<"in test2(): ";
    cout<<s1 << endl;
    cout<<s1.size()<<endl;
    // s1.print();
}

void test3()
{
    String s1("Hello");
    String s2(" World");
    cout<<s1+s2<<endl;

    cout<<s1+" Beijing"<<endl;
    cout<<"nihao"+s2<<endl;
}

int main(void)
{
    // test0();
    // test1();
    test2();
    // test3();
    
    return 0;
}