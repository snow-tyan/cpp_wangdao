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

class Task
{
public:
    void run()
    {
        ::srand(::clock()); //时钟频率作为随机数种子
        int cnt = 3;
        while (cnt--)
        {
            int num = ::rand() % 100;
            cout << "sub thread " << threadName
                 << " put num = " << num << " :cnt = " << cnt << endl;
            ::sleep(1);
        }
        // ::sleep(1);
    }
};

int main()
{
    Task *task = new Task();
    unique_ptr<Thread> thread1(new Thread(std::bind(&Task::run, task)));
    unique_ptr<Thread> thread2(new Thread(std::bind(&Task::run, task), "2"));

    thread1->start();
    thread2->start();
    thread1->join();
    thread2->join();

    cout << "main thread" << endl;

    return 0;
}