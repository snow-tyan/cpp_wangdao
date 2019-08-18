#include "ThreadPool.hh"
#include "Task.hh"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
using namespace myThread;

class MyTask
    : public Task
{
public:
    void process() override
    {
        ::srand(::clock());
        int cnt = 5;
        while (cnt--)
        {
            int num = ::rand() % 100;
            cout << ">> sub thread " << threadName
                 << " put num = " << num << " :cnt = " << cnt << endl;
            ::sleep(1);
        }
    }
};

int main()
{
    ThreadPool threadpool(4, 10);
    threadpool.start();

    unique_ptr<MyTask> task(new MyTask());

    int cnt = 20; //添加20个任务
    while (cnt--)
    {
        threadpool.addTask(task.get());
        cout << "main thread add task, cnt = " << cnt << endl;
    }

	threadpool.stop();

    return 0;
}