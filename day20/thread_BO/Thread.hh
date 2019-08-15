#pragma once
#include "Noncopyable.hh"
#include <pthread.h>
#include <functional>

namespace thread_BO
{

class Thread
    : public Noncopyable
{
public:
    using threadCallBack = std::function<void()>;
    Thread(threadCallBack &&cb)
        : _pthid(0), _isRunning(false), _cb(std::move(cb))
    {}

    void start();
    void join();

    ~Thread();

private:
    //消除成员函数默认带一个this指针的影响，设为static
    static void * threadFunc(void * arg);

private:
    pthread_t _pthid;
    bool _isRunning;
    threadCallBack _cb;//回调函数
};

}//end of namespace thread_OO