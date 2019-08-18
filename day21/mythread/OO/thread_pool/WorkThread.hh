#pragma once
#include "Thread.hh"
#include "ThreadPool.hh"
#include <iostream>
using std::cout;
using std::endl;

namespace myThread
{

class WorkThread
    : public Thread
{
public:
    WorkThread(ThreadPool &threadpool, const string &name)
        : _threadpool(threadpool), Thread(name)
    {
        cout << "WorkdThread(ThreadPool &)" << endl;
    }

    ~WorkThread()
    {
        cout << "~WorkThread()" << endl;
    }

private:
    void run() override
    {
        _threadpool.threadPoolFunc();
    }

private:
    ThreadPool &_threadpool;
};

} //end of namespace myThread