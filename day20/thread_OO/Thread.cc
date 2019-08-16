#include "Thread.hh"

namespace thread_OO
{

void *Thread::threadFunc(void *arg)
{
    Thread *pArg = static_cast<Thread *>(arg); //强转
    if (pArg)
    {
        //run()方法调用，必须通过一个对象来完成
        //pArg是线程对象的指针
        pArg->run(); //线程要执行的任务
    }

    return nullptr;
}

void Thread::start()
{
    pthread_create(&_pthid, nullptr, threadFunc, this);
    //第四个参数把当前线程对象的地址传递给threadFunc
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
}

} //end of namespace thread_OO