#pragma once
#include "Noncopyable.hh"
#include <pthread.h>
#include <functional>

namespace PC_BO
{

class Thread
    : public Noncopyable
{
public:
    using threadCallBack = std::function<void()>;
    Thread(threadCallBack &&cb)
        : _pthid(0), _isRunning(false), _cb(std::move(cb)) {}

    void start();
    void join();

    ~Thread();//出现纯虚函数，析构函数也要设为virtual

private:
    //消除成员函数默认带一个this指针的影响，设为static
    static void * threadFunc(void * arg);

private:
    pthread_t _pthid;
    bool _isRunning;
    threadCallBack _cb;
};

} //end of namespace PC_BO