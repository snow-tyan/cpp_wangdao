#include "Thread.hh"

namespace myThread
{
    
//线程局部存储
__thread const char *threadName;

struct ThreadData
{
    ThreadData(const string &name, void *arg = nullptr)
        : _name(name)
    {
        _pArg = static_cast<Thread *>(arg);
    }
    void runInThread()
    {
        threadName = (_name == string() ? "Anonymous" : _name.c_str());
        if (_pArg)
        {
            _pArg->run();
        }
    }
    string _name;
    Thread *_pArg;
};

void Thread::start()
{
    ThreadData *pdata = new ThreadData(_name, this);
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
        pthread_detach(_pthid);
    }
    // std::cout << "~Thread()" << std::endl;
}

void *Thread::threadFunc(void *arg)
{
    ThreadData *pdata = static_cast<ThreadData *>(arg);
    if (pdata)
    {
        pdata->runInThread();
    }
    return nullptr;
}

} //end of namespace myThread