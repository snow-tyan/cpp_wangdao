#pragma once
#include "TaskQueue.hh"
#include "Thread.hh"
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

namespace ThreadPool_OO
{
class Task;

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task *task);

private:
    friend class WorkThread;
    
    void threadFunc();//子线程要执行的任务
    Task *getTask();

private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;//存放线程
    TaskQueue _taskque;
    bool _isExit;
};

}//end of namespace ThreadPool_OO