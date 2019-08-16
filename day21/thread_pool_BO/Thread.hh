#pragma once
#include "Noncopyable.hh"
#include <pthread.h>
#include <functional>
#include <iostream>

namespace ThreadPool_OO
{

class Thread
    : public Noncopyable
{
public:
    using threadCallBack = std::function<void()>;
    Thread(threadCallBack &&cb)//注册回调函数
        : _pthid(0), _isRunning(false), _cb(std::move(cb))
    {
        std::cout<<"Thread(threadCallBack &&)"<<std::endl;
    }

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