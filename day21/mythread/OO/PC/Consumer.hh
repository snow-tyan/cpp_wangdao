#pragma once
#include "TaskQueue.hh"
#include "Thread.hh"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;

namespace myThread
{

class Consumer
    :public Thread
{
public:
    Consumer(TaskQueue &taskQue, const string &name = string())
        : _taskQue(taskQue), Thread(name) {}
    ~Consumer(){}

private:
    void run() override
    {
        ::srand(::clock());
        int cnt = 5;
        while(cnt--)
        {
            int num = _taskQue.pop();
            cout << ">>> consumer thread " << threadName
                 << " get num = " << num << " :cnt = " << cnt << endl;
        }
        // ::usleep(100000);
    }

private:
    TaskQueue &_taskQue;
};

}//end of namespace myThread