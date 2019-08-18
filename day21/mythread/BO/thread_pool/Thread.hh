#pragma once
#include <pthread.h>
#include "Noncopyable.hh"
#include <iostream>
#include <string>
#include <functional>
using std::string;

namespace myThread
{

extern __thread const char * threadName;
using ThreadCallBack = std::function<void()>;

class Thread
    : public Noncopyable
{
public:
    //基类必须有默认构造
    Thread(ThreadCallBack &&cb, const string &name = string())
        : _pthid(0), _isRunning(false), _cb(std::move(cb)), _name(name)
    {
        std::cout << "Thread()" << std::endl;
    }

    void start();
    void join();

    ~Thread();

private:    
    //threadFunc必须是只带一个void *类型的参数，返回void *类型的函数
    //设为static，以消除this指针的影响
    static void *threadFunc(void *arg);

private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallBack _cb;
    string _name;
};

} //end of namespace myThread