#include "Thread.hh"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace thread_OO;

class myThread
    : public Thread
{
    void run() override
    {
        cout << "i am child thread" << endl;
        ::srand(::clock());
        int cnt = 10;
        while (cnt--)
        {
            int num = ::rand() % 100;
            cout << ">> num = " << num << endl;
            ::sleep(1);
        }
    }
};

int main()
{
    // myThread th1;
    // myThread th2(th1);//error
    unique_ptr<Thread> thread(new myThread()); //基类的指针指向派生类对象
                                               //会通过虚表找虚函数
    thread->start();//产生子线程
    thread->join();
    cout << "i am main thread" << endl;

    return 0;
}
