#include "Thread.hh"

#include <unistd.h> //sleep
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace myThread;

class MyThread
    : public Thread
{
public:
    //派生类没有显示定义构造函数，基类必须有默认构造函数。
    //派生类有显示定义构造函数，基类成员的初始化都要放在派生类的初始化表达式中
    MyThread(const string &name = string())
        : Thread(name) //调用基类的构造函数
    {}

    void run() override
    {
        ::srand(::clock()); //时钟频率作为随机数种子
        int cnt = 3;
        while (cnt--)
        {
            int num = ::rand() % 100;
            cout << "sub thread " << threadName
                 << " put num = " << num << " :cnt = " << cnt << endl;
            // ::sleep(1);
        }
        // ::sleep(1);
    }
};

int main()
{
    unique_ptr<Thread> thread1(new MyThread());
    unique_ptr<Thread> thread2(new MyThread("2"));
    thread1->start();
    thread2->start();
    thread1->join();
    thread2->join();
    cout << "main thread" << endl;

    return 0;
}