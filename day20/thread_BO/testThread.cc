#include "Thread.hh"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace thread_BO;

class Task
{
public:
    void process()
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
    Task *task = new Task();
    unique_ptr<Thread> thread(new Thread(
        std::bind(&Task::process, task))); //类的成员函数隐含一个this指针参数
    thread->start();
    thread->join();
    cout << "i am main thread" << endl;

    return 0;
}
