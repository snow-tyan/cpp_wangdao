#include "WorkThread.hh"
#include "ThreadPool.hh"
#include <iostream>
using std::cout;
using std::endl;

namespace ThreadPool_OO
{

WorkThread::WorkThread(ThreadPool &threadpool)
:_threadpool(threadpool)
{
    cout << "WorkThread(ThreadPool &)" << endl;
}

WorkThread::~WorkThread()
{
    cout << "~WorkThread()" << endl;
}

void WorkThread::run()
{
    _threadpool.threadFunc();
}

}//end of namespace ThreadPool_OO