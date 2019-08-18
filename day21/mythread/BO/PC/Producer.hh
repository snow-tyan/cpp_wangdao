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
{
public:
    void produce(TaskQueue &taskQue)
    {
        ::srand(::clock());
        int cnt = 5;
        while(cnt--)
        {
            int num = ::rand() % 100;
            taskQue.push(num);
            cout << ">> producer thread " << threadName
                 << " push num = " << num << " :cnt = " << cnt << endl;
            ::usleep(100000);            
        }
    }
};

}//end of namespace myThread