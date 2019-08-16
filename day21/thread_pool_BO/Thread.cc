#include "Thread.hh"

namespace ThreadPool_BO
{
    
namespace current_thread
{
//线程局部存储
__thread const char * threadName = "Anonymous";

} //end of namespace current_thread

using ThreadCallback = std::function<void()>;

struct ThreadData
{
    ThreadData(const std::string name, ThreadCallback &&cb)
        : _name(name), _cb(cb) {}

    //子线程中执行
    void runInThread()
    {
        current_thread::threadName = (_name == std::string() ? "Anonymous" : _name.c_str());

        if (_cb)
        {
            _cb();
        }
    }

    std::string _name;
    ThreadCallback _cb;
};

void *Thread::threadFunc(void *arg)
{
    ThreadData *pdata = static_cast<ThreadData *>(arg); //强转
    if (pdata)
    {
        pdata->runInThread();
    }

    delete pdata;//回收堆空间内存
    return nullptr;
}

void Thread::start()
{
    ThreadData * pdata = new ThreadData(_name, std::move(_cb));
    pthread_create(&_pthid, nullptr, threadFunc, pdata);
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