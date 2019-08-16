#pragma once
#include "TaskQueue.hh"
#include <unistd.h>//sleep
#include <ctime>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

namespace PC_BO
{

class Producer
{
public:
    void produce(TaskQueue &taskQueue)
    {
        ::srand(::clock());
        int cnt = 10;
        while (cnt--)
        {
            int num = ::rand() % 100;
            taskQueue.push(num);
            cout << ">> produce thread, push num = " << num << endl;
            ::sleep(1);
        }
    }
};

}//end of namespace PC_BO