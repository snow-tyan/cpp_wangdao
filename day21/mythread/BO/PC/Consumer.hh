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
{
public:
    void consume(TaskQueue &taskQue)
    {
        ::srand(::clock());
        int cnt = 5;
        while(cnt--)
        {
            int num = taskQue.pop();
            cout << ">>> consumer thread " << threadName
                 << " get num = " << num << " :cnt = " << cnt << endl;
        }
        // ::usleep(100000);
    }
};

}//end of namespace myThread