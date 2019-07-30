#include "mystring.h"

void test0()
{
    String str1;
    cout << "str1=";
    str1.print();

    String str2 = "Hello,world";
    String str3("wangdao");

    cout << "str2=";
    str2.print();
    cout << "str3=";
    str3.print();

    String str4 = str3;
    cout << "str4=";
    str4.print();

    str4 = str2;
    cout << "str4=";
    str4.print();

    str1.assign(5,'h');
    cout << "str1=";
    str1.print();

    String str5;
    str5.assign(str2);
    cout << "str5=";
    str5.print();

}

void test1()
{
    const char *cp = "Hello World!!!";
    char noNull[] = {'H', 'i'};
    String s1(cp);
    cout<<"s1=";
    s1.print();
    String s2(noNull, 2);
    cout<<"s2=";
    s2.print();
    String s3(noNull);
    cout<<"s3=";
    s3.print();
    String s4(cp + 6, 5);
    cout<<"s4=";
    s4.print();
    String s5(s1, 6, 5);
    cout<<"s5=";
    s5.print();
    String s6(s1, 6);
    cout<<"s6=";
    s6.print();
    String s7(s1, 6, 20);
    cout<<"s7=";
    s7.print();
    String s8(s1, 16);
    cout<<"s8=";
    s8.print();
}

void test2()
{
    String s("Hello World");
    s.print();
    String s2 = s.substr(0, 5);
    s2.print();
    String s3 = s.substr(6);
    s3.print();
    String s4 = s.substr(6, 11);
    s4.print();
    cout << s4.size() << endl;
    String s5 = s.substr(12);
}

void test3()
{

}

int main(void)
{
    // test0();
    // test1();
    // test2();
    test3();

    return 0;
}
