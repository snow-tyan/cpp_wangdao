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

class Producer
    :public Thread
{
public:
    Producer(TaskQueue &taskQue, const string &name = string())
        : _taskQue(taskQue), Thread(name) {}
    ~Producer() {}

private:
    void run() override
    {
        ::srand(::clock());
        int cnt = 5;
        while(cnt--)
        {
            int num = ::rand() % 100;
            _taskQue.push(num);
            cout << ">> producer thread " << threadName
                 << " push num = " << num << " :cnt = " << cnt << endl;
            ::usleep(100000);            
        }
    }

private:
    TaskQueue &_taskQue;
};

}//end of namespace myThread