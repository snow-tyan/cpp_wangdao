#pragma once
#include "TaskQueue.hh"
#include "Thread.hh"
#include <vector>
#include <memory>
#include <functional>
using std::vector;
using std::unique_ptr;

namespace ThreadPool_BO
{

class ThreadPool
{
public:
    using Task = std::function<void()>;
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task &&task);

private:
    void threadFunc();//子线程要执行的任务
    Task getTask();

private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;//存放线程
    TaskQueue _taskque;
    bool _isExit;
};

}//end of namespace ThreadPool_BO