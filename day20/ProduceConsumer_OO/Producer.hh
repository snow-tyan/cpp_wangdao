#pragma once
// #include "TaskQueue.hh"
#include "Thread.hh"

namespace PC_OO
{
class TaskQueue;//前向声明，降低头文件依赖性

class Producer
:public Thread
{
public:
    Producer(TaskQueue &taskQueue);
    ~Producer(){}

private:
    void run() override;

private:
    TaskQueue & _taskQueue;
};


}//end of namespace PC_OO