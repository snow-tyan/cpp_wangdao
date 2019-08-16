#pragma once
#include "Noncopyable.hh"
#include <pthread.h>

namespace PC_OO
{

class Thread
    : public Noncopyable
{
public:
    Thread():_pthid(0),_isRunning(false){}

    void start();
    void join();

    virtual ~Thread();//出现纯虚函数，析构函数也要设为virtual

private:
    virtual void run() = 0;//任务
    //消除成员函数默认带一个this指针的影响，设为static
    static void * threadFunc(void * arg);

private:
    pthread_t _pthid;
    bool _isRunning;
};

}//end of namespace PC_OO