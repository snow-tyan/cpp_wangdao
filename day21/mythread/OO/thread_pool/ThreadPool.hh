#pragma once
#include "TaskQueue.hh"
#include "Thread.hh"
#include "Task.hh"
#include <vector>
#include <memory>
using std::unique_ptr;
using std::vector;

namespace myThread
{

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task *);

private:
    friend class WorkThread;
    void threadPoolFunc();
    Task *getTask();

private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
    bool _isExit;
};

} //end of namespace myThread