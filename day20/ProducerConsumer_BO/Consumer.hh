#pragma once
#include "TaskQueue.hh"
#include <unistd.h> //sleep
#include <iostream>
using std::cout;
using std::endl;

namespace PC_BO
{

class Consumer
{
public:
    void consume(TaskQueue &taskQueue)
    {
        int cnt = 10;
        while (cnt--)
        {
            int num = taskQueue.pop();
            cout << ">>> consumer thread, get num = " << num << endl;
            ::sleep(2);
        }
    }
};

} // end of namespace PC_BO