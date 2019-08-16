#pragma once
#include "Thread.hh"

namespace PC_OO
{
class TaskQueue;

class Consumer
:public Thread
{
public:
    Consumer(TaskQueue &taskQueue);
    ~Consumer(){}

private:
    void run() override;

private:
    TaskQueue & _taskQueue;
};


}//end of namespace PC_OO