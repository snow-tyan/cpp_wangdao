#pragma once
#include "Thread.hh"

namespace ThreadPool_OO
{
class ThreadPool;

class WorkThread
:public Thread
{
public:
    WorkThread(ThreadPool &threadpool);
    ~WorkThread();
    
private:
    void run() override;

private:
    ThreadPool & _threadpool;
};

}//end of namespace ThreadPool_OO