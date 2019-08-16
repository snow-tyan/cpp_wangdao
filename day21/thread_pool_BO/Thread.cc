#include "Thread.hh"

namespace ThreadPool_BO
{

void *Thread::threadFunc(void *arg)
{
    Thread *pArg = static_cast<Thread *>(arg); //强转
    if (pArg)
    {
        pArg->_cb(); //回调函数的执行
    }

    return nullptr;
}

void Thread::start()
{
    pthread_create(&_pthid, nullptr, threadFunc, this);
    _isRunning = true;
}

void Thread::join()
{
    if (_isRunning)
    {
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

Thread::~Thread()
{
    if (_isRunning)
    {
        //When a detached thread terminates, its resources are automatically 
        //released back to the system  without the need for another thread 
        //to join with the terminated thread.
        pthread_detach(_pthid);
    }
    std::cout<<"~Thread()"<<std::endl;
}

} //end of namespace ThreadPool_BO